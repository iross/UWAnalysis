#ifndef TauAnalysis_CandidateTools_SVfitLikelihoodDiTauProd_h
#define TauAnalysis_CandidateTools_SVfitLikelihoodDiTauProd_h

/** \class SVfitLikelihoodDiTauProd
 *
 * Plugin for computing likelihood for production of tau lepton pair
 * via Z --> tau+ tau- or (MSSM) Higgs --> tau+ tau- processes
 * 
 * \author Christian Veelken; UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitLikelihoodDiTauProd.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UWAnalysis/RecoTools/interface/SVfitDiTauLikelihoodBase.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/SVfitDiTauSolution.h"

#include <string>

template <typename T1, typename T2>
class SVfitLikelihoodDiTauProd : public SVfitDiTauLikelihoodBase<T1,T2>
{
 public:
  SVfitLikelihoodDiTauProd(const edm::ParameterSet&);
  ~SVfitLikelihoodDiTauProd();

  void beginJob();

  double operator()(const CompositePtrCandidateT1T2MEt<T1,T2>&, const SVfitDiTauSolution&) const;

 private:
  enum { kUndefined, kZ0, kHiggs };
  int process_;

  std::string pdfSet_;
  
  double sqrtS_; // center-of-mass energy (in units of GeV)

  static const int verbosity_ = 0;

  int cfgError_;
};

#endif
