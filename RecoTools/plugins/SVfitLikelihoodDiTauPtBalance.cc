#include "UWAnalysis/RecoTools/plugins/SVfitLikelihoodDiTauPtBalance.h"

#include "UWAnalysis/RecoTools/interface/svFitAuxFunctions.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include <TMath.h>

#include <string>

using namespace SVfit_namespace;

template <typename T1, typename T2>
SVfitLikelihoodDiTauPtBalance<T1,T2>::SVfitLikelihoodDiTauPtBalance(const edm::ParameterSet& cfg)
  : SVfitDiTauLikelihoodBase<T1,T2>(cfg)
{
// nothing to be done yet...
}

template <typename T1, typename T2>
SVfitLikelihoodDiTauPtBalance<T1,T2>::~SVfitLikelihoodDiTauPtBalance()
{
// nothing to be done yet...
}

//-------------------------------------------------------------------------------
// Compute likelihood for tau leptons produced in decay of particle of mass M
// to have transverse momenta leg1Pt, leg2Pt
//
// The form of the likelihood function has been determined numerically by:
//  o making a Taylor expansion of Jacobian peak smeared by Gaussian distribution
//  o fitting the first five terms of the Taylor expansion plus a gamma distribution
//    to the tau lepton Pt distribution in simulated Z --> tau+ tau- and H/A --> tau+ tau- events
//  o parametrizing the fit coefficients as function of tau+ tau- mass
//    of the Z --> tau+ tau- and H/A --> tau+ tau- events
//
//-------------------------------------------------------------------------------

double smearedKinematicDistribution(double x, double M, double s) 
{
  double num_first_term = TMath::Exp(-0.5*square(x)/square(s))
                         *8*s*(fourth(M) + 2*square(M)*(2*square(s) + square(x)) + 6*(square(s) + square(x))*(8*square(s) + square(x)));

  double num_second_term = TMath::Exp(-square(M - 2*x)/(8*square(s)))
                          *s*(15*fourth(M) + 14*cube(M) + 48*(square(s)+square(x))*(8*square(s)+square(x)) 
                             + 4*square(M)*(20*square(s) + 7*square(x)) + 24*M*(7*square(s)*x + cube(x)));

  double num_third_term = 4*TMath::Sqrt(TMath::TwoPi())
                         *x*(fourth(M) + 6*square(M)*square(s) + 90*fourth(s) + 2*(square(M) + 30*square(s))*square(x) + 6*fourth(x))
                         *(TMath::Erf((M - 2*x)/(2*TMath::Sqrt2()*s)) + TMath::Erf(x/(TMath::Sqrt2()*s)));
  double num_factor = 1/(2*TMath::Sqrt(TMath::TwoPi()));
  double numerator = num_factor*(num_first_term - num_second_term + num_third_term);
 
  // now compute normalization factor
  double den_first_term = (2*TMath::Sqrt(1.0/TMath::PiOver2()) 
                         *TMath::Exp(-square(M)/(8*square(s)))
                         *M*s*(11*fourth(M) + 44*square(M)*square(s) + 240*fourth(s)));
  double den_second_term = TMath::Erf(M/(2*TMath::Sqrt2()*s))
                          *(11*fourth(M)*square(M) - 32*fourth(M)*square(s) - 96*square(M)*fourth(s) - 960*fourth(s)*square(s));
  double denominator = (1./16)*(den_first_term + den_second_term);

  return numerator/denominator;
}

double movingTauLeptonPtPDF(double tauPt, double diTauMass)
{
  double smearNorm = 0.52 + 0.000658*diTauMass;
  double smearWidth = 1.8 + 0.018*diTauMass;
  double M = 2.3 + 1.04*diTauMass;
  double gammaScale = 6.74 + 0.020*diTauMass;
  double gammaShape = 2.2 + 0.0364*diTauMass;
  
  return smearNorm*smearedKinematicDistribution(tauPt, M, smearWidth) 
        + (1 - smearNorm)*TMath::GammaDist(tauPt, gammaShape, 0., gammaScale);
}

template <typename T1, typename T2>
double SVfitLikelihoodDiTauPtBalance<T1,T2>::operator()(const CompositePtrCandidateT1T2MEt<T1,T2>& diTau, 
					     const SVfitDiTauSolution& solution) const
{
//--- compute negative log-likelihood for two tau leptons 
//    to have transverse momenta leg1Pt, leg2Pt

  if ( verbosity_ ) std::cout << "<SVfitLikelihoodDiTauPtBalance::operator()>:" << std::endl;

  double diTauMass = solution.p4().mass();
  if ( verbosity_ ) std::cout << " diTauMass = " << diTauMass << std::endl;

  double leg1Pt = solution.leg1().p4().pt();
  double leg2Pt = solution.leg2().p4().pt();
  if ( verbosity_ ) {
    std::cout << " leg1Pt = " << leg1Pt << std::endl;
    std::cout << " leg2Pt = " << leg2Pt << std::endl;
  }

  double prob = movingTauLeptonPtPDF(leg1Pt, diTauMass)*movingTauLeptonPtPDF(leg2Pt, diTauMass);
  if ( verbosity_ ) std::cout << "--> prob = " << prob << std::endl;

  if ( !(prob > 0.) ) {
    //edm::LogWarning ("SVfitLikelihoodDiTauPtBalance::operator()") 
    //  << " Unphysical solution --> returning very large negative number !!";
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

typedef SVfitLikelihoodDiTauPtBalance<pat::Electron, pat::Tau> SVfitLikelihoodElecTauPairPtBalance;
typedef SVfitLikelihoodDiTauPtBalance<pat::Muon, pat::Tau> SVfitLikelihoodMuTauPairPtBalance;
typedef SVfitLikelihoodDiTauPtBalance<pat::Tau, pat::Tau> SVfitLikelihoodDiTauPairPtBalance;
typedef SVfitLikelihoodDiTauPtBalance<pat::Electron, pat::Muon> SVfitLikelihoodElecMuPairPtBalance;
typedef SVfitLikelihoodDiTauPtBalance<pat::Muon, pat::Muon> SVfitLikelihoodMuPairPtBalance;
typedef SVfitLikelihoodDiTauPtBalance<reco::Candidate, reco::Candidate> SVfitLikelihoodDiCandidatePairPtBalance;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_EDM_PLUGIN(SVfitElecTauPairLikelihoodBasePluginFactory, SVfitLikelihoodElecTauPairPtBalance, "SVfitLikelihoodElecTauPairPtBalance");
DEFINE_EDM_PLUGIN(SVfitMuTauPairLikelihoodBasePluginFactory, SVfitLikelihoodMuTauPairPtBalance, "SVfitLikelihoodMuTauPairPtBalance");
DEFINE_EDM_PLUGIN(SVfitDiTauPairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauPairPtBalance, "SVfitLikelihoodDiTauPairPtBalance");
DEFINE_EDM_PLUGIN(SVfitElecMuPairLikelihoodBasePluginFactory, SVfitLikelihoodElecMuPairPtBalance, "SVfitLikelihoodElecMuPairPtBalance");
DEFINE_EDM_PLUGIN(SVfitMuPairLikelihoodBasePluginFactory, SVfitLikelihoodMuPairPtBalance, "SVfitLikelihoodMuPairPtBalance");
DEFINE_EDM_PLUGIN(SVfitDiCandidatePairLikelihoodBasePluginFactory, SVfitLikelihoodDiCandidatePairPtBalance, "SVfitLikelihoodDiCandidatePairPtBalance");

