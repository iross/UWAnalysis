#include "UWAnalysis/RecoTools/plugins/SVfitLikelihoodDiTauBreitWigner.h"

#include "UWAnalysis/RecoTools/interface/SVfitAlgorithm.h"
#include "UWAnalysis/RecoTools/interface/svFitAuxFunctions.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include <TMath.h>

using namespace SVfit_namespace;

template <typename T1, typename T2>
SVfitLikelihoodDiTauBreitWigner<T1,T2>::SVfitLikelihoodDiTauBreitWigner(const edm::ParameterSet& cfg)
  : SVfitDiTauLikelihoodBase<T1,T2>(cfg)
{
  M2_ = square(cfg.getParameter<double>("M"));
  Gamma2_ = square(cfg.getParameter<double>("Gamma"));
}

template <typename T1, typename T2>
SVfitLikelihoodDiTauBreitWigner<T1,T2>::~SVfitLikelihoodDiTauBreitWigner()
{
// nothing to be done yet...
}

template <typename T1, typename T2>
double SVfitLikelihoodDiTauBreitWigner<T1,T2>::operator()(const CompositePtrCandidateT1T2MEt<T1,T2>& diTau, 
							  const SVfitDiTauSolution& solution) const
{
//--- compute negative log-likelihood for invariant mass of tau lepton pair
//    to be compatible with Breit-Wigner resonance of mass M and width Gamma

  double diTauMass2 = square((solution.leg1().p4() + solution.leg2().p4()).mass());

  return -TMath::Log(Gamma2_/(square(diTauMass2 - M2_) + M2_*Gamma2_));
}

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/Candidate/interface/Candidate.h"

typedef SVfitLikelihoodDiTauBreitWigner<pat::Electron, pat::Tau> SVfitLikelihoodDiTauBreitWignerElecTau;
typedef SVfitLikelihoodDiTauBreitWigner<pat::Muon, pat::Tau> SVfitLikelihoodDiTauBreitWignerMuTau;
typedef SVfitLikelihoodDiTauBreitWigner<pat::Tau, pat::Tau> SVfitLikelihoodDiTauBreitWignerDiTau;
typedef SVfitLikelihoodDiTauBreitWigner<pat::Electron, pat::Muon> SVfitLikelihoodDiTauBreitWignerElecMu;
typedef SVfitLikelihoodDiTauBreitWigner<reco::Candidate, reco::Candidate> SVfitLikelihoodDiTauBreitWignerDiCandidate;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_EDM_PLUGIN(SVfitElecTauPairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauBreitWignerElecTau, "SVfitLikelihoodDiTauBreitWignerElecTau");
DEFINE_EDM_PLUGIN(SVfitMuTauPairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauBreitWignerMuTau, "SVfitLikelihoodDiTauBreitWignerMuTau");
DEFINE_EDM_PLUGIN(SVfitDiTauPairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauBreitWignerDiTau, "SVfitLikelihoodDiTauBreitWignerDiTau");
DEFINE_EDM_PLUGIN(SVfitElecMuPairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauBreitWignerElecMu, "SVfitLikelihoodDiTauBreitWignerElecMu");
DEFINE_EDM_PLUGIN(SVfitDiCandidatePairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauBreitWignerDiCandidate, "SVfitLikelihoodDiTauBreitWignerDiCandidate");
