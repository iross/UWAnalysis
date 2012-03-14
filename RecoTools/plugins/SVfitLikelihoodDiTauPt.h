#ifndef TauAnalysis_CandidateTools_SVfitLikelihoodDiTauPt_h
#define TauAnalysis_CandidateTools_SVfitLikelihoodDiTauPt_h

/** \class SVfitLikelihoodDiTauPt
 *
 * Plugin for computing likelihood for tau+ tau- pair to have a certain transverse momentum
 * 
 * \author Christian Veelken; UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitLikelihoodDiTauPt.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UWAnalysis/RecoTools/interface/SVfitDiTauLikelihoodBase.h"
#include "UWAnalysis/RecoTools/interface/SVfitLegLikelihoodBase.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/SVfitDiTauSolution.h"

#include <TFormula.h>

#include <iostream>

template <typename T1, typename T2>
class SVfitLikelihoodDiTauPt : public SVfitDiTauLikelihoodBase<T1,T2>
{
 public:
  SVfitLikelihoodDiTauPt(const edm::ParameterSet&);
  ~SVfitLikelihoodDiTauPt();

  void print(std::ostream&) const;

  double operator()(const CompositePtrCandidateT1T2MEt<T1,T2>&, const SVfitDiTauSolution&) const;
 private:
  TFormula* pdf_;
  std::map<int, TFormula*> pdfParameters_;
  int parseError_;
};

#endif
