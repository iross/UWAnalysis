#ifndef TauAnalysis_CandidateTools_SVfitLeptonLikelihoodPolarization_h
#define TauAnalysis_CandidateTools_SVfitLeptonLikelihoodPolarization_h

/** \class SVfitLeptonLikelihoodPolarization
 *
 * Plugin for computing likelihood for tau lepton decay "leg"
 * to be compatible with decay tau- --> e- nu nu (tau- --> mu- nu nu)
 * of polarized tau lepton into electron (muon),
 * assuming  matrix element of V-A electroweak decay
 * 
 * \author Christian Veelken, UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitLeptonLikelihoodPolarization.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UWAnalysis/RecoTools/interface/SVfitLegLikelihoodPolarizationBase.h"

template <typename T>
class SVfitLeptonLikelihoodPolarization : public SVfitLegLikelihoodPolarizationBase<T>
{
 public:
  SVfitLeptonLikelihoodPolarization(const edm::ParameterSet&);
  ~SVfitLeptonLikelihoodPolarization();

 private:
  double negLogLikelihoodPolarized(const T&, const SVfitLegSolution&, double) const;

  bool useCollApproxFormulas_;

  static const int verbosity_ = 0;
};

#endif
