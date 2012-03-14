#ifndef TauAnalysis_CandidateTools_SVfitEventVertexRefitter_h
#define TauAnalysis_CandidateTools_SVfitEventVertexRefitter_h

/** \class SVfitEventVertexRefitter
 *
 * Class to refit position of primary event vertex,
 * excluding the tracks associated to tau decay products
 *
 * \author Evan Friis, Christian Veelken; UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitEventVertexRefitter.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

class SVfitEventVertexRefitter
{
 public:
  SVfitEventVertexRefitter(const edm::ParameterSet&);
  ~SVfitEventVertexRefitter();

  void beginEvent(const edm::Event&, const edm::EventSetup&);

  /// Refit the primary vertex after subtracting the tau associated tracks.
  TransientVertex refit(const std::vector<reco::TrackBaseRef>& leg1Tracks,
			const std::vector<reco::TrackBaseRef>& leg2Tracks);

  /// Refit a three prong tau.
  TransientVertex fitSecondaryVertex(
      const std::vector<reco::TrackBaseRef>& tracks) const;

 private:
  edm::InputTag srcPrimaryEventVertex_;
  edm::InputTag srcBeamSpot_;

  const reco::Vertex* primaryEventVertex_;
  const reco::BeamSpot* beamSpot_;

  const TransientTrackBuilder* trackBuilder_;

  const KalmanVertexFitter* vertexFitAlgorithm_;

  unsigned minNumTracksRefit_;
};

#endif
