#ifndef UWAnalysis_RecoTools_CompositePtrCandidateT1T2MEtProducer_h
#define UWAnalysis_RecoTools_CompositePtrCandidateT1T2MEtProducer_h


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "UWAnalysis/RecoTools/interface/FetchCollection.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"


#include "UWAnalysis/RecoTools/interface/SVfitAlgorithm.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"


#include "UWAnalysis/RecoTools/interface/candidateAuxFunctions.h"
#include "UWAnalysis/RecoTools/interface/generalAuxFunctions.h"


template<typename T1, typename T2>
class PATCandidatePairSVFitter : public edm::EDProducer 
{
  typedef edm::Ptr<T1> T1Ptr;
  typedef edm::Ptr<T2> T2Ptr;
  typedef std::vector<edm::Ptr<pat::Jet> > JetPtrVector;
  typedef std::vector<CompositePtrCandidateT1T2MEt<T1,T2> > CompositePtrCandidateCollection;
  
 public:

  explicit PATCandidatePairSVFitter(const edm::ParameterSet& cfg)
  {
    src_     = cfg.getParameter<edm::InputTag>("src");
    srcPV_       =  cfg.getParameter<edm::InputTag>("srcPrimaryVertex") ;
    srcBeamSpot_ = cfg.getParameter<edm::InputTag>("srcBeamSpot") ;

    if ( cfg.exists("svFit") ) {
      printf("Will use SV FIt\n");
      edm::ParameterSet cfgSVfit = cfg.getParameter<edm::ParameterSet>("svFit");	
      std::vector<std::string> svFitAlgorithmNames = cfgSVfit.getParameterNamesForType<edm::ParameterSet>();
      for ( std::vector<std::string>::const_iterator svFitAlgorithmName = svFitAlgorithmNames.begin();
	    svFitAlgorithmName != svFitAlgorithmNames.end(); ++svFitAlgorithmName ) {
	edm::ParameterSet cfgSVfitAlgorithm = cfgSVfit.getParameter<edm::ParameterSet>(*svFitAlgorithmName);
	cfgSVfitAlgorithm.addParameter<std::string>("name", *svFitAlgorithmName);
	copyCfgParameter<edm::InputTag>(cfg, "srcPrimaryVertex", cfgSVfitAlgorithm);
	copyCfgParameter<edm::InputTag>(cfg, "srcBeamSpot", cfgSVfitAlgorithm);
	SVfitAlgorithm<T1,T2>* svFitAlgorithm = new SVfitAlgorithm<T1,T2>(cfgSVfitAlgorithm);
	svFitAlgorithms_.insert(std::pair<std::string, SVfitAlgorithm<T1,T2>*>(*svFitAlgorithmName, svFitAlgorithm));
	std::cout << "--> adding SVfit algorithm: name = " << (*svFitAlgorithmName) << std::endl;
      }
    }
  
    for ( typename std::map<std::string, SVfitAlgorithm<T1,T2>*>::iterator svFitAlgorithm = svFitAlgorithms_.begin();
	  svFitAlgorithm != svFitAlgorithms_.end(); ++svFitAlgorithm ) {
      svFitAlgorithm->second->beginJob();
    }
    

    produces<CompositePtrCandidateCollection>();
  }

    ~PATCandidatePairSVFitter(){}

  void beginJob()
  {

  }


  void produce(edm::Event& evt, const edm::EventSetup& es)
  {

    std::auto_ptr<CompositePtrCandidateCollection> out(new CompositePtrCandidateCollection);

    for ( typename std::map<std::string, SVfitAlgorithm<T1,T2>*>::iterator svFitAlgorithm = svFitAlgorithms_.begin();
	  svFitAlgorithm != svFitAlgorithms_.end(); ++svFitAlgorithm ) {
      svFitAlgorithm->second->beginEvent(evt, es);
    }

    // Get primary vertex
    const reco::Vertex* pv = NULL;
    if ( srcPV_.label() != "" ) {
       edm::Handle<reco::VertexCollection> pvs;
       pf::fetchCollection(pvs, srcPV_, evt);
       pv = &((*pvs)[0]);
    }

    // Get beamspot
    const reco::BeamSpot* beamSpot = NULL;
    if ( srcBeamSpot_.label() != "" ) {
       edm::Handle<reco::BeamSpot> beamSpotHandle;
       pf::fetchCollection(beamSpotHandle, srcBeamSpot_, evt);
       beamSpot = beamSpotHandle.product();
    }


    //get track builder
    const TransientTrackBuilder* trackBuilder = NULL;
       edm::ESHandle<TransientTrackBuilder> myTransientTrackBuilder;
       es.get<TransientTrackRecord>().get("TransientTrackBuilder", myTransientTrackBuilder);
       trackBuilder = myTransientTrackBuilder.product();
       if ( !trackBuilder ) {
	 edm::LogError ("produce") << " Failed to access TransientTrackBuilder !!";
       }

       edm::Handle<std::vector<CompositePtrCandidateT1T2MEt<T1,T2> > > cands;
       if(evt.getByLabel(src_,cands)) 
	 for (unsigned int i=0;i<cands->size();++i) {

	   CompositePtrCandidateT1T2MEt<T1,T2> compositePtrCandidate = cands->at(i);

	   if ( pv && beamSpot && trackBuilder ) {
	     for ( typename std::map<std::string, SVfitAlgorithm<T1,T2>*>::const_iterator svFitAlgorithm = svFitAlgorithms_.begin();
		   svFitAlgorithm != svFitAlgorithms_.end(); ++svFitAlgorithm ) {
	       std::vector<SVfitDiTauSolution> svFitSolutions = svFitAlgorithm->second->fit(compositePtrCandidate);
	       for ( std::vector<SVfitDiTauSolution>::const_iterator svFitSolution = svFitSolutions.begin();
		     svFitSolution != svFitSolutions.end(); ++svFitSolution ) {
		 compositePtrCandidate.addSVfitSolution(svFitAlgorithm->first, svFitSolution->polarizationHypothesisName(), *svFitSolution);
	       }
	     }

	   }

	   out->push_back(compositePtrCandidate);
	 }
    
  
    evt.put(out);
  }

 private:


  

  edm::InputTag src_;
  edm::InputTag srcPV_;
  edm::InputTag srcBeamSpot_;
  std::map<std::string, SVfitAlgorithm<T1,T2>*> svFitAlgorithms_;
  typedef std::vector<int> vint;

};



#endif

