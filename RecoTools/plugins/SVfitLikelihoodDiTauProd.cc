#include "UWAnalysis/RecoTools/plugins/SVfitLikelihoodDiTauProd.h"

#include "UWAnalysis/RecoTools/interface/SVfitAlgorithm.h"
#include "UWAnalysis/RecoTools/interface/svFitAuxFunctions.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include "LHAPDF/LHAPDF.h"

#include <TMath.h>

#include <limits>

using namespace SVfit_namespace;

namespace LHAPDF {
  void initPDFSet(int nset, const std::string& filename, int member);
  double xfx(int nset, double x, double Q, int fl);
}

template <typename T1, typename T2>
SVfitLikelihoodDiTauProd<T1,T2>::SVfitLikelihoodDiTauProd(const edm::ParameterSet& cfg)
  : SVfitDiTauLikelihoodBase<T1,T2>(cfg),
    process_(kUndefined),
    cfgError_(0)
{
  std::string process_string = cfg.getParameter<std::string>("process");
  if      ( process_string == "Z0"    ) process_ = kZ0;
  else if ( process_string == "Higgs" ) process_ = kHiggs;
  else {
    edm::LogError ("SVfitLikelihoodDiTauProd") 
      << " Invalid Configuration Parameter process = " << process_string << " !!";
    cfgError_ = 1;
  }
  
  pdfSet_ = cfg.getParameter<std::string>("pdfSet");

  sqrtS_ = cfg.getParameter<double>("sqrtS");
}

template <typename T1, typename T2>
SVfitLikelihoodDiTauProd<T1,T2>::~SVfitLikelihoodDiTauProd()
{
// nothing to be done yet...
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauProd<T1,T2>::beginJob()
{
  LHAPDF::initPDFSet(0, pdfSet_, 0); // use "best-fit" PDF values
}

double getPDFprob(int flavor, double xPlus, double xMinus, double Q) 
{
//--- compute probability to find either to gluons or two quarks of flavor q and qBar in pp system 
//
//    NOTE: 
//        (1) the Z0 can be produced by annihilation of q + qBar "opposite flavor" quark pairs only;
//            the (MSSM) Higgs is produced by gluon-gluon fusion
//        (2) the flavors are encoded as:
//                -6: tbar
//                -5: bbar
//                -4: cbar
//                -3: sbar
//                -2: ubar
//                -1: dbar
//                 0: gluon
//                 1: down
//                 2: up
//                 3: strange
//                 4: charm
//                 5: bottom
//                 6: top
//                 7: photon
//           ( cf. http://projects.hepforge.org/lhapdf/manual ,
//                 http://projects.hepforge.org/lhapdf/cc/namespaceLHAPDF.html )
//            --> need to add -LHAPDF::TBAR to flavor |q| when computing index for PDF value look-up

  //std::cout << "<getPDFprob>:" << std::endl;

  flavor = TMath::Abs(flavor);

  double prob = 0.;
  if ( flavor == LHAPDF::UP   || flavor == LHAPDF::CHARM   || flavor == LHAPDF::TOP    ||
       flavor == LHAPDF::DOWN || flavor == LHAPDF::STRANGE || flavor == LHAPDF::BOTTOM ) {
    prob = (LHAPDF::xfx(0, xPlus, Q, +flavor)/xPlus)*(LHAPDF::xfx(0, xMinus, Q, -flavor)/xMinus)
          + (LHAPDF::xfx(0, xPlus, Q, -flavor)/xPlus)*(LHAPDF::xfx(0, xMinus, Q, +flavor)/xMinus);
  } else if ( flavor == LHAPDF::GLUON ) {
    prob = 2.*(LHAPDF::xfx(0, xPlus, Q, flavor)/xPlus)*(LHAPDF::xfx(0, xMinus, Q, flavor)/xMinus);
  } else {
    edm::LogError ("getPDFprob") 
      << " Invalid flavor type = " << flavor << " !!";
  }

  //std::cout << "--> prob = " << prob << std::endl;
  
  return prob;
}

double compZ0CrossSection(double qF, double vF, double aF, double theta, double sHat, double tauLeptonPol)
{
  // theta = angle of tau- wrt. beam axis (computed in Z0 rest-frame)
  // mZ = nomimal Z0 mass ( constant defined in UWAnalysis/RecoTools/interface/svFitAuxFunctions.h )
  // sHat = fitted Z mass

  double qF2 = square(qF);
  double vF2 = square(vF);
  double aF2 = square(aF);

  double qTau2 = square(qTau);
  double vTau2 = square(vTau);
  double aTau2 = square(aTau);

  double mZ2 = square(mZ);
  double reChi = sHat*(sHat - mZ2)/(square(sHat - mZ2) + square(sHat*gammaZ/mZ));
  double Chi2 = (square(sHat*(sHat - mZ2)) + square(sHat*gammaZ/mZ))/square(square(sHat - mZ2) + square(sHat*gammaZ/mZ));

  double c = TMath::Pi()*square(alphaZ)/(2*sHat);

  double F0 = c*(qF2*qTau2 + 2*reChi*qF*qTau*vF*vTau + Chi2*(vF2 + aF2)*(vTau2 + aTau2));
  double F1 = c*(2*reChi*qF*qTau*aF*aTau + Chi2*2*vF*aF*2*vTau*aTau);
  double F2 = c*(2*reChi*qF*qTau*vF*aTau + Chi2*(vF2 + aF2)*2*vTau*aTau);
  double F3 = c*(2*reChi*qF*qTau*aF*vTau + Chi2*2*vF*aF*2*(vTau2 + aTau2));

  double cosTheta = TMath::Cos(theta);
  double cosTheta2 = square(cosTheta);

  double crossSection = (1. + cosTheta2)*(F0 - tauLeptonPol*F2) + 2*cosTheta*(F1 - tauLeptonPol*F3);

//--- normalize integral over Z0 cross-section to unit area,
//    in order to give "equal strength" to Z0 and Higgs hypotheses
  double norm = (8./3.)*(F0 - tauLeptonPol*F2);

  return crossSection/norm;
}

double compZ0CrossSectionUpType(double theta, double sHat, double tauLeptonPol)
{
  return compZ0CrossSection(qUp, vUp, aUp, theta, sHat, tauLeptonPol);
}

double compZ0CrossSectionDownType(double theta, double sHat, double tauLeptonPol)
{
  return compZ0CrossSection(qDown, vDown, aDown, theta, sHat, tauLeptonPol);
}

double compHiggsCrossSection()
{
  return 1./TMath::Pi();
}

double compTheta(const reco::Candidate::LorentzVector& p4DiTau, const reco::Candidate::LorentzVector& p4TauLepton)
{
//--- compute production angle of tau lepton in rest-frame of tau+ tau- pair 
//    (i.e. either the Z0 or the Higgs rest-frame)

  return boostToCOM(p4DiTau, p4TauLepton).theta();
}

template <typename T1, typename T2>
double SVfitLikelihoodDiTauProd<T1,T2>::operator()(const CompositePtrCandidateT1T2MEt<T1,T2>& diTau, 
						   const SVfitDiTauSolution& solution) const
{
  //std::cout << "<SVfitLikelihoodDiTauProd::operator()>:" << std::endl;

  if ( cfgError_ ) {
    edm::LogError ("SVfitLikelihoodDiTauProd<T1,T2>::operator()") 
      << " Error in Configuration ParameterSet --> -log(likelihood) value will NOT be computed !!";
    return std::numeric_limits<float>::min();
  }
  
  double mass = solution.p4().mass();

  double eta = solution.p4().eta();

  double xPlus = (mass/sqrtS_)*TMath::Exp(+eta);
  //std::cout << " xPlus = " << xPlus << std::endl;
  double xMinus = (mass/sqrtS_)*TMath::Exp(-eta);
  //std::cout << " xMinus = " << xMinus << std::endl;

  double upTypePdfSum   = getPDFprob(LHAPDF::UP, xPlus, xMinus, mass) 
                         + getPDFprob(LHAPDF::CHARM, xPlus, xMinus, mass) + getPDFprob(LHAPDF::TOP, xPlus, xMinus, mass);
  double downTypePdfSum = getPDFprob(LHAPDF::DOWN, xPlus, xMinus, mass) 
                         + getPDFprob(LHAPDF::STRANGE, xPlus, xMinus, mass) + getPDFprob(LHAPDF::BOTTOM, xPlus, xMinus, mass);

  double upTypeCrossSection = 0.;
  double downTypeCrossSection = 0.;
  if ( process_ == kZ0    ) {
    double sHat = square(mass);
    
    const SVfitLegSolution* tauMinusSolution = 0;
    if      ( diTau.leg1()->charge() < 0. ) tauMinusSolution = &solution.leg1();
    else if ( diTau.leg2()->charge() < 0. ) tauMinusSolution = &solution.leg2();
   
    if ( tauMinusSolution ) {
      double tauMinusPol = getTauLeptonPolarization(tauMinusSolution->polarizationHypothesis(), qTau);
      double tauMinusTheta = compTheta(solution.p4(), tauMinusSolution->p4());
      upTypeCrossSection = compZ0CrossSectionUpType(tauMinusTheta, sHat, tauMinusPol);
      downTypeCrossSection = compZ0CrossSectionDownType(tauMinusTheta, sHat, tauMinusPol);
    } else {
      double leg1Theta = compTheta(solution.p4(), solution.leg1().p4());
      double leg2Theta = compTheta(solution.p4(), solution.leg2().p4());
      upTypeCrossSection = compZ0CrossSectionUpType(leg1Theta, sHat, 0.) + compZ0CrossSectionUpType(leg2Theta, sHat, 0.);
      downTypeCrossSection = compZ0CrossSectionDownType(leg1Theta, sHat, 0.) + compZ0CrossSectionUpType(leg2Theta, sHat, 0.);
    }
  } else if ( process_ == kHiggs ) {
    upTypeCrossSection = compHiggsCrossSection();
    downTypeCrossSection = compHiggsCrossSection();
  }

  double prob = upTypeCrossSection*upTypePdfSum + downTypeCrossSection*downTypePdfSum; 
  if ( verbosity_ ) std::cout << "--> prob = " << prob << std::endl;

  if ( !(prob > 0.) ) {
    edm::LogWarning ("SVfitLikelihoodDiTauProd::operator()") 
      << " Unphysical solution --> returning very large negative number !!";
    return std::numeric_limits<float>::min();
  }
  
  double logLikelihood = TMath::Log(prob);
  if ( verbosity_ ) std::cout << " -logLikelihood = " << -logLikelihood << std::endl;
  
  return -logLikelihood;
}

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/Candidate/interface/Candidate.h"

typedef SVfitLikelihoodDiTauProd<pat::Electron, pat::Tau> SVfitLikelihoodElecTauPairProd;
typedef SVfitLikelihoodDiTauProd<pat::Muon, pat::Tau> SVfitLikelihoodMuTauPairProd;
typedef SVfitLikelihoodDiTauProd<pat::Tau, pat::Tau> SVfitLikelihoodDiTauPairProd;
typedef SVfitLikelihoodDiTauProd<pat::Electron, pat::Muon> SVfitLikelihoodElecMuPairProd;
typedef SVfitLikelihoodDiTauProd<reco::Candidate, reco::Candidate> SVfitLikelihoodDiCandidatePairProd;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_EDM_PLUGIN(SVfitElecTauPairLikelihoodBasePluginFactory, SVfitLikelihoodElecTauPairProd, "SVfitLikelihoodElecTauPairProd");
DEFINE_EDM_PLUGIN(SVfitMuTauPairLikelihoodBasePluginFactory, SVfitLikelihoodMuTauPairProd, "SVfitLikelihoodMuTauPairProd");
DEFINE_EDM_PLUGIN(SVfitDiTauPairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauPairProd, "SVfitLikelihoodDiTauPairProd");
DEFINE_EDM_PLUGIN(SVfitElecMuPairLikelihoodBasePluginFactory, SVfitLikelihoodElecMuPairProd, "SVfitLikelihoodElecMuPairProd");
DEFINE_EDM_PLUGIN(SVfitDiCandidatePairLikelihoodBasePluginFactory, SVfitLikelihoodDiCandidatePairProd, "SVfitLikelihoodDiCandidatePairProd");
