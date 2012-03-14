#ifndef TauAnalysis_CandidateTools_SVfitLikelihoodDiTauBreitWigner_h
#define TauAnalysis_CandidateTools_SVfitLikelihoodDiTauBreitWigner_h

/** \class SVfitLikelihoodDiTauBreitWigner
 *
 * Plugin for computing likelihood for invariant mass of tau lepton pair
 * to be compatible with Breit-Wigner resonance of mass M and width Gamma
 * 
 * \author Christian Veelken; UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitLikelihoodDiTauBreitWigner.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UWAnalysis/RecoTools/interface/SVfitDiTauLikelihoodBase.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/SVfitDiTauSolution.h"

template <typename T1, typename T2>
class SVfitLikelihoodDiTauBreitWigner : public SVfitDiTauLikelihoodBase<T1,T2>
{
 public:
  SVfitLikelihoodDiTauBreitWigner(const edm::ParameterSet&);
  ~SVfitLikelihoodDiTauBreitWigner();

  double operator()(const CompositePtrCandidateT1T2MEt<T1,T2>&, const SVfitDiTauSolution&) const;
 private:
  double M2_;
  double Gamma2_;
};

#endif
