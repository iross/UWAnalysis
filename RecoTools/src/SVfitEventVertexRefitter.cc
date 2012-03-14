#include "UWAnalysis/RecoTools/interface/SVfitEventVertexRefitter.h"

#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "UWAnalysis/RecoTools/interface/FetchCollection.h"

#include <TMath.h>

SVfitEventVertexRefitter::SVfitEventVertexRefitter(const edm::ParameterSet& cfg)
  : beamSpot_(0),
    trackBuilder_(0)
{
  srcPrimaryEventVertex_ = cfg.getParameter<edm::InputTag>("srcPrimaryVertex");
  srcBeamSpot_ = cfg.getParameter<edm::InputTag>("srcBeamSpot");

  vertexFitAlgorithm_ = new KalmanVertexFitter(true);

  minNumTracksRefit_ = ( cfg.exists("minNumTracksRefit") ) ?
    cfg.getParameter<unsigned>("minNumTracksRefit") : 2;
}

SVfitEventVertexRefitter::~SVfitEventVertexRefitter()
{
  delete vertexFitAlgorithm_;
}

void SVfitEventVertexRefitter::beginEvent(const edm::Event& evt, const edm::EventSetup& es)
{
//--- get primary event vertex
  edm::Handle<reco::VertexCollection> vertices;
  pf::fetchCollection(vertices, srcPrimaryEventVertex_, evt);
  primaryEventVertex_ = &((*vertices)[0]);
  if ( !primaryEventVertex_ ) {
    edm::LogError ("SVfitEventVertexRefitter::beginEvent")
      << " Failed to access primaryEventVertex !!";
  }

//--- get beamspot
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  pf::fetchCollection(beamSpotHandle, srcBeamSpot_, evt);
  beamSpot_ = beamSpotHandle.product();
  if ( !beamSpot_ ) {
    edm::LogError ("SVfitEventVertexRefitter::beginEvent")
      << " Failed to access BeamSpot !!";
  }

//--- get pointer to TransientTrackBuilder
  edm::ESHandle<TransientTrackBuilder> trackBuilderHandle;
  es.get<TransientTrackRecord>().get("TransientTrackBuilder", trackBuilderHandle);
  trackBuilder_ = trackBuilderHandle.product();
  if ( !trackBuilder_ ) {
    edm::LogError ("SVfitEventVertexRefitter::beginEvent")
      << " Failed to access TransientTrackBuilder !!";
  }
}

//-------------------------------------------------------------------------------
// auxiliary functions to compare two Tracks by reference/by match in eta-phi
template<typename T>
struct RefToBase_less : public std::binary_function<edm::RefToBase<T>, edm::RefToBase<T>, bool>
{
  inline bool operator()(const edm::RefToBase<T> &r1, const edm::RefToBase<T> &r2) const
  {
    return r1.id() < r2.id() || (r1.id() == r2.id() && r1.key() < r2.key());
  }
};

bool tracksMatchByDeltaR(const reco::TrackBaseRef& trk1, const reco::TrackBaseRef& trk2)
{
  if ( reco::deltaR(*trk1, *trk2) < 0.01 && trk1->charge() == trk2->charge() &&
       TMath::Abs(trk1->pt() - trk2->pt()) < 0.05*(trk1->pt() + trk2->pt()) )
    return true;
  else
    return false;
}

// auxiliary function to exclude tracks associated to tau lepton decay "leg"
// from primary event vertex refit
typedef std::map<reco::TrackBaseRef, reco::TransientTrack, RefToBase_less<reco::Track> > TransientTrackMap;
void removeTracks(TransientTrackMap& pvTracks_toRefit, const std::vector<reco::TrackBaseRef>& legTracks)
{
  for ( std::vector<reco::TrackBaseRef>::const_iterator legTrack = legTracks.begin();
	legTrack != legTracks.end(); ++legTrack ) {

//--- remove track from list of tracks included in primary event vertex refit
//    if track matches by reference or in eta-phi
//    any of the tracks associated to tau lepton decay "leg"
    TransientTrackMap::iterator pvTrack_match = pvTracks_toRefit.find(*legTrack);
    if ( pvTrack_match != pvTracks_toRefit.end() ) {
      pvTracks_toRefit.erase(pvTrack_match);
    } else {
      for ( TransientTrackMap::iterator pvTrack = pvTracks_toRefit.begin();
	    pvTrack != pvTracks_toRefit.end(); ++pvTrack ) {
	if ( tracksMatchByDeltaR(pvTrack->first, *legTrack) ) {
	  pvTracks_toRefit.erase(pvTrack);
	  break;
	}
      }
    }
  }
}
//-------------------------------------------------------------------------------

TransientVertex SVfitEventVertexRefitter::refit(const std::vector<reco::TrackBaseRef>& leg1Tracks,
						const std::vector<reco::TrackBaseRef>& leg2Tracks)
{
//--- return (invalid) dummy vertex in case primary event vertex cannot be refitted,
//    due to insufficient information
  if ( !(primaryEventVertex_ && beamSpot_ && trackBuilder_) ) return TransientVertex();

  std::vector<reco::TransientTrack> pvTracks_original;
  TransientTrackMap pvTrackMap_refit;
  for ( reco::Vertex::trackRef_iterator pvTrack = primaryEventVertex_->tracks_begin();
	pvTrack != primaryEventVertex_->tracks_end(); ++pvTrack ) {
    reco::TransientTrack pvTrack_transient = trackBuilder_->build(pvTrack->castTo<reco::TrackRef>());
    pvTracks_original.push_back(pvTrack_transient);
    pvTrackMap_refit.insert(std::make_pair(*pvTrack, pvTrack_transient));
  }

//--- exclude tracks associated to any one of the two tau lepton decay "legs"
//    from the primary event vertex refit
  removeTracks(pvTrackMap_refit, leg1Tracks);
  removeTracks(pvTrackMap_refit, leg2Tracks);

  std::vector<reco::TransientTrack> pvTracks_refit;
  for ( TransientTrackMap::iterator pvTrack = pvTrackMap_refit.begin();
	pvTrack != pvTrackMap_refit.end(); ++pvTrack ) {
    pvTracks_refit.push_back(pvTrack->second);
  }

//--- refit primary event vertex with "cleaned" track collection;
//    in case there are not "enough" tracks left to do the refit
//    after excluding the tracks associated to tau lepton decay "leg",
//    refit the primary event vertex with all tracks used in the original primary event vertex fit
  if ( pvTracks_refit.size() >= minNumTracksRefit_ ) {
    return vertexFitAlgorithm_->vertex(pvTracks_refit, *beamSpot_);
  } else {
    edm::LogWarning ("SVfitEventVertexRefitter::refit")
      << "Insufficient tracks remaining after excluding tracks associated to tau decay products"
      << " --> skipping primary event vertex refit !!";
    // CV: need to enlarge errors on reconstructed event vertex position
    //     in SVfitLikelihoodDiTauTrackInfo in this case <-- FIXME
    return vertexFitAlgorithm_->vertex(pvTracks_original, *beamSpot_);
  }
}

TransientVertex SVfitEventVertexRefitter::fitSecondaryVertex(
      const std::vector<reco::TrackBaseRef>& tracks) const {
  // Return a null vertex if this is not a refittable tau.
  if (tracks.size() < 2)
    return TransientVertex();

  // Build the transient tracks
  std::vector<reco::TransientTrack> transTracks;
  for(size_t trk = 0; trk < tracks.size(); ++trk) {
    transTracks.push_back(trackBuilder_->build(
            tracks[trk].castTo<reco::TrackRef>()));
  }
  // Fit the vertex.
  return vertexFitAlgorithm_->vertex(transTracks);
}
