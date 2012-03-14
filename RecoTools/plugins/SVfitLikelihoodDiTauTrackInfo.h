#ifndef TauAnalysis_CandidateTools_SVfitLikelihoodDiTauTrackInfo_h
#define TauAnalysis_CandidateTools_SVfitLikelihoodDiTauTrackInfo_h

/** \class SVfitLikelihoodDiTauTrackInfo
 *
 * Plugin for computing likelihood for tracks of particles produced in the decay of a tau lepton pair
 * to be compatible with the reconstructed primary event vertex position
 * and hypothetic secondary (tau lepton decay) vertices,
 * computed for given decay kinematics of the tau lepton pair
 *
 * \author Evan Friis, Christian Veelken; UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitLikelihoodDiTauTrackInfo.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UWAnalysis/RecoTools/interface/SVfitDiTauLikelihoodBase.h"
#include "UWAnalysis/RecoTools/interface/SVfitLegLikelihoodBase.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/SVfitDiTauSolution.h"

#include <iomanip>

template <typename T1, typename T2>
  class SVfitLikelihoodDiTauTrackInfo : public SVfitDiTauLikelihoodBase<T1,T2>
{
 public:
  SVfitLikelihoodDiTauTrackInfo(const edm::ParameterSet&);
  ~SVfitLikelihoodDiTauTrackInfo();

  void beginJob();
  void beginEvent(const edm::Event&, const edm::EventSetup&);
  void beginCandidate(const CompositePtrCandidateT1T2MEt<T1,T2>&);

  void print(std::ostream&) const;

  bool isFittedParameter(int) const;
  bool supportsPolarization() const;

  double operator()(const CompositePtrCandidateT1T2MEt<T1,T2>&, const SVfitDiTauSolution&) const;

 private:
  SVfitLegLikelihoodBase<T1>* leg1Likelihood_;
  SVfitLegLikelihoodBase<T2>* leg2Likelihood_;
  bool useLifetimeConstraint_;

  static const int verbosity_ = 0;
};

#endif
