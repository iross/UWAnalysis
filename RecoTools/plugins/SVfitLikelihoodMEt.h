#ifndef TauAnalysis_CandidateTools_SVfitLikelihoodMEt_h
#define TauAnalysis_CandidateTools_SVfitLikelihoodMEt_h

/** \class SVfitLikelihoodMEt
 *
 * Plugin for computing likelihood for neutrinos produced in tau lepton decays
 * to match missing transverse momentum reconstructed in the event
 *
 * \author Evan Friis, Christian Veelken; UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitLikelihoodMEt.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/Common/interface/Handle.h"

#include "UWAnalysis/RecoTools/interface/SVfitDiTauLikelihoodBase.h"
#include "UWAnalysis/RecoTools/interface/SVfitLegLikelihoodBase.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/SVfitDiTauSolution.h"

#include <TFormula.h>

template <typename T1, typename T2>
class SVfitLikelihoodMEt : public SVfitDiTauLikelihoodBase<T1,T2>
{
 public:
  SVfitLikelihoodMEt(const edm::ParameterSet&);
  ~SVfitLikelihoodMEt();

  void beginEvent(const edm::Event&, const edm::EventSetup&);
  void beginCandidate(const CompositePtrCandidateT1T2MEt<T1,T2>&);

  bool isFittedParameter(int) const;

  double operator()(const CompositePtrCandidateT1T2MEt<T1,T2>&, const SVfitDiTauSolution&) const;
 private:
  TFormula* parSigma_;
  TFormula* parBias_;

  TFormula* perpSigma_;
  TFormula* perpBias_;

  double qX_;
  double qY_;
  double qT_;

  edm::InputTag srcPFCandidates_;
  edm::Handle<reco::PFCandidateCollection> pfCandidates_;

  static const int verbosity_ = 0;
};

#endif
