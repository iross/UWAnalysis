#ifndef TauAnalysis_CandidateTools_SVfitLegLikelihoodTrackInfo_h
#define TauAnalysis_CandidateTools_SVfitLegLikelihoodTrackInfo_h

/** \class SVfitLegLikelihoodTrackInfo
 *
 * Plugin for computing likelihood for tracks of tau lepton decay "leg"
 * to be compatible with originating from hypothetic secondary (tau lepton decay) vertex
 *
 * \author Evan Friis, Christian Veelken; UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitLegLikelihoodTrackInfo.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"

#include "UWAnalysis/RecoTools/interface/SVfitLegLikelihoodBase.h"
#include "UWAnalysis/RecoTools/interface/SVfitLegTrackExtractor.h"

#include "UWAnalysis/DataFormats/interface/SVfitLegSolution.h"

#include "UWAnalysis/RecoTools/interface/SVfitTrackExtrapolation.h"

template <typename T>
class SVfitLegLikelihoodTrackInfo : public SVfitLegLikelihoodBase<T>
{
 public:
  SVfitLegLikelihoodTrackInfo(const edm::ParameterSet&);
  ~SVfitLegLikelihoodTrackInfo();

  void beginEvent(const edm::Event&, const edm::EventSetup&);
  void beginCandidate(const T&);

  bool isFittedParameter(int, int) const;

  void setEventVertexPos(const AlgebraicVector3& pvPosition)
  {
    // "original" (unshifted) position of primary event (tau production) vertex
    pvPosition_ = pvPosition;
  }

  double operator()(const T&, const SVfitLegSolution&) const;
 private:
  SVfitLegTrackExtractor<T> trackExtractor_;

  const TransientTrackBuilder* trackBuilder_;

  mutable std::vector<reco::TransientTrack> selectedTracks_;

  unsigned minNumHits_;
  unsigned minNumPixelHits_;
  double maxChi2DoF_;
  double maxDeltaPoverP_;
  double minPt_;

  bool useLinearApprox_;
  AlgebraicVector3 pvPosition_;
  mutable std::vector<SVfit::track::TrackExtrapolation> selectedTrackInfo_;
  mutable bool isNewCandidate_;

  static const int verbosity_ = 0;
};

#endif
