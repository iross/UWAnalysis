#include "UWAnalysis/RecoTools/plugins/SVfitLegLikelihoodTrackInfo.h"

#include "UWAnalysis/RecoTools/interface/svFitAuxFunctions.h"

#include "TrackingTools/Records/interface/TransientTrackRecord.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"

using namespace SVfit_namespace;

unsigned defaultMinNumHits = 5;
unsigned defaultMinNumPixelHits = 1;
double defaultMaxChi2DoF = 10.;
unsigned defaultMaxDeltaPoverP = 1.e+3;
double defaultMinPt = 5.;

//
//-------------------------------------------------------------------------------
//

template <typename T>
SVfitLegLikelihoodTrackInfo<T>::SVfitLegLikelihoodTrackInfo(const edm::ParameterSet& cfg)
: SVfitLegLikelihoodBase<T>(cfg),
    trackBuilder_(0)
{
  //std::cout << "<SVfitLegLikelihoodTrackInfo::SVfitLegLikelihoodTrackInfo>:" << std::endl;

  minNumHits_ = ( cfg.exists("minNumHits") ) ? cfg.getParameter<unsigned>("minNumHits") : defaultMinNumHits;
  minNumPixelHits_ = ( cfg.exists("minNumPixelHits") ) ? cfg.getParameter<unsigned>("minNumPixelHits") : defaultMinNumPixelHits;
  maxChi2DoF_ = ( cfg.exists("maxChi2DoF") ) ? cfg.getParameter<double>("maxChi2DoF") : defaultMaxChi2DoF;
  maxDeltaPoverP_ = ( cfg.exists("maxDeltaPoverP") ) ? cfg.getParameter<double>("maxDeltaPoverP") : defaultMaxDeltaPoverP;
  minPt_ = ( cfg.exists("minPt") ) ? cfg.getParameter<double>("minPt") : defaultMinPt;

  useLinearApprox_ = ( cfg.exists("useLinearApprox") ) ? cfg.getParameter<bool>("useLinearApprox") : true;
  //std::cout << " useLinearApprox = " << useLinearApprox_ << std::endl;
}

template <typename T>
SVfitLegLikelihoodTrackInfo<T>::~SVfitLegLikelihoodTrackInfo()
{
  // nothing to be done yet...
}

template <typename T>
void SVfitLegLikelihoodTrackInfo<T>::beginEvent(const edm::Event& evt, const edm::EventSetup& es)
{
  //--- get pointer to TransientTrackBuilder
  edm::ESHandle<TransientTrackBuilder> trackBuilderHandle;
  es.get<TransientTrackRecord>().get("TransientTrackBuilder", trackBuilderHandle);
  trackBuilder_ = trackBuilderHandle.product();
  if ( !trackBuilder_ ) {
    edm::LogError ("SVfitLegLikelihoodTrackInfo::beginEvent")
        << " Failed to access TransientTrackBuilder !!";
  }
}

template <typename T>
void SVfitLegLikelihoodTrackInfo<T>::beginCandidate(const T& leg)
{
  //std::cout << "<SVfitLegLikelihoodTrackInfo::beginCandidate>:" << std::endl;
  //std::cout << " trackBuilder = " << trackBuilder_ << std::endl;

  selectedTracks_.clear();

  std::vector<reco::TrackBaseRef> legTracks = trackExtractor_(leg);
  for ( std::vector<reco::TrackBaseRef>::const_iterator track = legTracks.begin();
       track != legTracks.end(); ++track ) {
    const reco::HitPattern& trackHitPattern = (*track)->hitPattern();
    if ( trackHitPattern.numberOfValidTrackerHits() >= (int)minNumHits_ &&
        trackHitPattern.numberOfValidPixelHits() >= (int)minNumPixelHits_ &&
        (*track)->normalizedChi2() < maxChi2DoF_ &&
        ((*track)->ptError()/(*track)->pt()) < maxDeltaPoverP_ &&
        (*track)->pt() > minPt_ ) {
      reco::TransientTrack transientTrack = trackBuilder_->build(track->get());
      selectedTracks_.push_back(transientTrack);
    }
  }

  isNewCandidate_ = true;
}

template <typename T>
bool SVfitLegLikelihoodTrackInfo<T>::isFittedParameter(int legIndex, int parIndex) const
{
  if ( selectedTracks_.size() > 0 && 
       (//(legIndex == SVfit_namespace::kLeg1 && parIndex == SVfit_namespace::kLeg1phiLab              ) ||
	(legIndex == SVfit_namespace::kLeg1 && parIndex == SVfit_namespace::kLeg1decayDistanceLab) ||
	//(legIndex == SVfit_namespace::kLeg2 && parIndex == SVfit_namespace::kLeg2phiLab              ) ||
	(legIndex == SVfit_namespace::kLeg2 && parIndex == SVfit_namespace::kLeg2decayDistanceLab)) )
    return true;
  else
    return SVfitLegLikelihoodBase<T>::isFittedParameter(legIndex, parIndex);
}

double compScalarProduct(const AlgebraicVector3& v1, const AlgebraicVector3& v2)
{
  return v1.At(0)*v2.At(0) + v1.At(1)*v2.At(1) + v1.At(2)*v2.At(2);
}

double compNorm(const AlgebraicVector3& v)
{
  return TMath::Sqrt(square(v.At(0)) + square(v.At(1)) + square(v.At(2)));
}

template <typename T>
double SVfitLegLikelihoodTrackInfo<T>::operator()(const T& leg, const SVfitLegSolution& solution) const
{
  //--- compute negative log-likelihood for tracks of tau lepton decay "leg"
  //    to be compatible with originating from hypothetic secondary (tau lepton decay) vertex
  //
  //    The likelihood is computed as the product of probabilities for the tracks
  //    to be compatible with the hypothetic secondary vertex of the tau lepton decay
  //   (distance of closest approach of track to secondary vertex divided by estimated uncertainties of track extrapolation)

  if ( verbosity_ ) 
    std::cout << "<SVfitLegLikelihoodTrackInfo::operator()>:" << std::endl;

  double logLikelihood = 0.;

  if ( useLinearApprox_ ) {

    //--- "linearize" computation of point of closest approach of track to hypothetic seconday (tau decay) vertex,
    //    in order to improve numerical convergence of Minuit fit;
    //    compute track direction and covariance matrix for one reference point
    //   ("original" primary event (tau production) vertex position
    //    plus expected "mean" tau lepton flight path, given by (visibleEnergy/tauMass)*c*tauLifetime)
    //    instead of doing a "full" helix track extrapolation for each hypothetic seconday (tau decay) vertex position;
    //    given the "linearized" track direction vector, approximate point of closest approach by:
    //
    //     primaryVertex + trackVector*scalarProduct(trackVector, secondaryVertex)/(|trackVector|*|secondaryVertex|)
    //
    if ( isNewCandidate_ ) {
      if ( verbosity_ ) 
	std::cout << "--> computing linear approximation of helix track extrapolation..." << std::endl;

      AlgebraicVector3 direction;
      direction(0) = leg.px()/leg.p();
      direction(1) = leg.py()/leg.p();
      direction(2) = leg.pz()/leg.p();

      //double decayDistance0 = (leg.energy()/SVfit_namespace::tauLeptonMass)*SVfit_namespace::cTauLifetime;
      //AlgebraicVector3 refPoint = pvPosition_ + decayDistance0*direction;
      // try with just the ref point.
      AlgebraicVector3 refPoint = pvPosition_;

      selectedTrackInfo_.clear();
      for ( std::vector<reco::TransientTrack>::const_iterator selectedTrack = selectedTracks_.begin();
           selectedTrack != selectedTracks_.end(); ++selectedTrack ) {
        selectedTrackInfo_.push_back(SVfit::track::TrackExtrapolation(*selectedTrack, refPoint));
      }

      isNewCandidate_ = false;
    }

    if ( verbosity_ ) 
      std::cout << "--> computing distance between extrapolated track and (hypothetic) tau decay vertex..." << std::endl;
    for ( std::vector<SVfit::track::TrackExtrapolation>::const_iterator selectedTrackInfo = selectedTrackInfo_.begin();
         selectedTrackInfo != selectedTrackInfo_.end(); ++selectedTrackInfo ) {

      if ( verbosity_ ) 
	std::cout << "--> SV is: " << solution.decayVertexPos() << std::endl;
      logLikelihood += selectedTrackInfo->logLikelihood(solution.decayVertexPos());
    }
  } else {
    if ( verbosity_ ) 
      std::cout << "--> computing distance to (hypothetic) tau decay vertex using full helix extrapolation of track..." << std::endl;
    for ( std::vector<reco::TransientTrack>::const_iterator selectedTrack = selectedTracks_.begin();
         selectedTrack != selectedTracks_.end(); ++selectedTrack ) {
      SVfit::track::TrackExtrapolation selectedTrackInfo(*selectedTrack, solution.decayVertexPos());

      AlgebraicVector3 displacement = solution.decayVertexPos() - selectedTrackInfo.dcaPosition();

      logLikelihood += selectedTrackInfo.logLikelihoodFromDisplacement(displacement);
    }
  }

  if ( verbosity_ ) 
    std::cout << "--> -log(likelihood) = " << -logLikelihood << std::endl;

  return -logLikelihood;
}

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/Candidate/interface/Candidate.h"

typedef SVfitLegLikelihoodTrackInfo<pat::Electron> SVfitElectronLikelihoodTrackInfo;
typedef SVfitLegLikelihoodTrackInfo<pat::Muon> SVfitMuonLikelihoodTrackInfo;
typedef SVfitLegLikelihoodTrackInfo<pat::Tau> SVfitTauLikelihoodTrackInfo;
typedef SVfitLegLikelihoodTrackInfo<reco::Candidate> SVfitCandidateLikelihoodTrackInfo;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_EDM_PLUGIN(SVfitElectronLikelihoodBasePluginFactory, SVfitElectronLikelihoodTrackInfo, "SVfitElectronLikelihoodTrackInfo");
DEFINE_EDM_PLUGIN(SVfitMuonLikelihoodBasePluginFactory, SVfitMuonLikelihoodTrackInfo, "SVfitMuonLikelihoodTrackInfo");
DEFINE_EDM_PLUGIN(SVfitTauLikelihoodBasePluginFactory, SVfitTauLikelihoodTrackInfo, "SVfitTauLikelihoodTrackInfo");
DEFINE_EDM_PLUGIN(SVfitCandidateLikelihoodBasePluginFactory, SVfitCandidateLikelihoodTrackInfo, "SVfitCandidateLikelihoodTrackInfo");
