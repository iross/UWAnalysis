#ifndef UWAnalysis_RecoTools_CompositePtrCandidateT1T2MEtVertexAlgorithm_h
#define UWAnalysis_RecoTools_CompositePtrCandidateT1T2MEtVertexAlgorithm_h


#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/GsfTransientTrack.h"
#include "TrackingTools/TransientTrack/interface/BasicTransientTrack.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include <utility>
#include "DataFormats/CLHEP/interface/Migration.h"
#include "TrackingTools/PatternTools/interface/TransverseImpactPointExtrapolator.h"
#include "RecoVertex/VertexTools/interface/VertexDistance.h"

#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/VolumeBasedEngine/interface/VolumeBasedMagneticField.h"

#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/TrackerGeometryBuilder/interface/GluedGeomDet.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"

template <typename T1, typename T2>
class CompositePtrCandidateT1T2MEtVertexAlgorithm {

  typedef std::pair< std::vector<FreeTrajectoryState > , double > ExtractedTrackInfo;


public:
  CompositePtrCandidateT1T2MEtVertexAlgorithm(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using namespace edm;

    //get what we need
    Handle<reco::BeamSpot> theBeamSpotHandle;
    ESHandle<MagneticField> bFieldHandle;
    //    ESHandle<TrackerGeometry> trackerGeomHandle;
    //    ESHandle<GlobalTrackingGeometry> globTkGeomHandle;
    iEvent.getByLabel(std::string("offlineBeamSpot"), theBeamSpotHandle);
    iSetup.get<IdealMagneticFieldRecord>().get(bFieldHandle);
    //    iSetup.get<TrackerDigiGeometryRecord>().get(trackerGeomHandle);
    iSetup.get<GlobalTrackingGeometryRecord>().get(geomHandle);
    //    trackerGeom = trackerGeomHandle.product();
    magField = bFieldHandle.product();
    beamSpot = theBeamSpotHandle.product();

  }



  void calculateVertexVariables(CompositePtrCandidateT1T2MEt<T1,T2> & candidate) {
    //create the parameters
    float dca=0.0;
    float distance = 0.0;
    float dZ = 0.0;
    float z1 = 0.0;
    float z2 = 0.0;



    ExtractedTrackInfo info1 = getTrackInfo(*candidate.leg1());
    ExtractedTrackInfo info2 = getTrackInfo(*candidate.leg2());

    dZ = fabs(info1.second-info2.second);
    
    z1 = info1.second;
    z2 = info2.second;


    if(info1.first.size()>0 && info2.first.size()>0) {
      FreeTrajectoryState l1State = info1.first.at(0);
      FreeTrajectoryState l2State = info2.first.at(0);

      //Find Closest approach
 
      ClosestApproachInRPhi cApp;
      cApp.calculate(l1State, l2State);
      if( cApp.status() ) {
	dca = fabs( cApp.distance() );
	if(beamSpot!=0)
	  distance = sqrt( pow((cApp.crossingPoint().x()-beamSpot->position().x()),2)+pow((cApp.crossingPoint().y()-beamSpot->position().y()),2));
      }
    }
    candidate.setVertexVariables(dca,distance,dZ,z1,z2);
  }


 private:

  const MagneticField* magField;
  const reco::BeamSpot* beamSpot;
  edm::ESHandle<GlobalTrackingGeometry> geomHandle;


  ExtractedTrackInfo getTrackInfo(const pat::Tau& tau) const
  {
    //std::cout << "<SVfitLegTrackExtractor<pat::Tau>::operator()>:" << std::endl;
    std::vector<FreeTrajectoryState> states;
    double z=0.0;
    if(tau.leadPFChargedHadrCand().isNonnull()) {

      if(tau.leadPFChargedHadrCand()->trackRef().isNonnull()) {
	reco::TransientTrack track(tau.leadPFChargedHadrCand()->trackRef(),magField,geomHandle);
	FreeTrajectoryState state = track.impactPointTSCP().theState();
	states.push_back(state);
	//calculate Z at beamspot
	TransverseImpactPointExtrapolator extrapolator(magField);
	TrajectoryStateOnSurface closestOnTransversePlaneState = extrapolator.extrapolate(track.impactPointState(),GlobalPoint(beamSpot->position().x(),beamSpot->position().y(),0.0));
	z = closestOnTransversePlaneState.globalPosition().z();
      }
      if(tau.leadPFChargedHadrCand()->gsfTrackRef().isNonnull()) {
	reco::GsfTransientTrack track(tau.leadPFChargedHadrCand()->gsfTrackRef(),magField,geomHandle);
	FreeTrajectoryState state = track.impactPointTSCP().theState();
	states.push_back(state);
	//calculate Z at beamspot
	TransverseImpactPointExtrapolator extrapolator(magField);
	TrajectoryStateOnSurface closestOnTransversePlaneState = extrapolator.extrapolate(track.impactPointState(),GlobalPoint(beamSpot->position().x(),beamSpot->position().y(),0.0));
	z = closestOnTransversePlaneState.globalPosition().z();
      }
      

    }

    
    return std::make_pair(states,z);
  }



  ExtractedTrackInfo getTrackInfo(const pat::Electron& cand) const
  {
    //std::cout << "<SVfitLegTrackExtractor<pat::Tau>::operator()>:" << std::endl;
    std::vector<FreeTrajectoryState> states;
    double z=0.0;
    if(cand.gsfTrack().isNonnull()) {
      reco::GsfTransientTrack track(cand.gsfTrack(),magField,geomHandle);
      FreeTrajectoryState state = track.impactPointTSCP().theState();
      states.push_back(state);
      //calculate Z at beamspot
      TransverseImpactPointExtrapolator extrapolator(magField);
      TrajectoryStateOnSurface closestOnTransversePlaneState = extrapolator.extrapolate(track.impactPointState(),GlobalPoint(beamSpot->position().x(),beamSpot->position().y(),0.0));
      z = closestOnTransversePlaneState.globalPosition().z();
    }
   
    return std::make_pair(states,z);
  }



  ExtractedTrackInfo getTrackInfo(const pat::Muon& cand) const
  {
    //std::cout << "<SVfitLegTrackExtractor<pat::Tau>::operator()>:" << std::endl;
    std::vector<FreeTrajectoryState> states;
    double z=0.0;
    if(cand.innerTrack().isNonnull()) {
      reco::TransientTrack track(cand.innerTrack(),magField,geomHandle);
      FreeTrajectoryState state = track.impactPointTSCP().theState();
      states.push_back(state);
      //calculate Z at beamspot
      TransverseImpactPointExtrapolator extrapolator(magField);
      TrajectoryStateOnSurface closestOnTransversePlaneState = extrapolator.extrapolate(track.impactPointState(),GlobalPoint(beamSpot->position().x(),beamSpot->position().y(),0.0));
      z = closestOnTransversePlaneState.globalPosition().z();
    }
   
    return std::make_pair(states,z);
  }


  ExtractedTrackInfo getTrackInfo(const reco::Candidate& cand) const
  {
    //std::cout << "<SVfitLegTrackExtractor<pat::Tau>::operator()>:" << std::endl;
    std::vector<FreeTrajectoryState> states;
    double z=0.0;
    return std::make_pair(states,z);
  }

  ExtractedTrackInfo getTrackInfo(const pat::Jet& cand) const
  {
    //Leave it empty unless we need it 
    std::vector<FreeTrajectoryState> states;
    double z=0.0;
    return std::make_pair(states,z);
  }


  ExtractedTrackInfo getTrackInfo(const reco::RecoChargedCandidate& cand) const
  {
    //std::cout << "<SVfitLegTrackExtractor<pat::Tau>::operator()>:" << std::endl;
    std::vector<FreeTrajectoryState> states;
    double z=0.0;
    return std::make_pair(states,z);
  }

  ExtractedTrackInfo getTrackInfo(const reco::RecoEcalCandidate& cand) const
  {
    //std::cout << "<SVfitLegTrackExtractor<pat::Tau>::operator()>:" << std::endl;
    std::vector<FreeTrajectoryState> states;
    double z=0.0;
    return std::make_pair(states,z);
  }






};


#endif

