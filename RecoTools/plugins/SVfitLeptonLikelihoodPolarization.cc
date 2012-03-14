#include "UWAnalysis/RecoTools/plugins/SVfitLeptonLikelihoodPolarization.h"

#include "UWAnalysis/RecoTools/interface/svFitAuxFunctions.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include <TMath.h>

#include <limits>

using namespace SVfit_namespace;

template <typename T>
SVfitLeptonLikelihoodPolarization<T>::SVfitLeptonLikelihoodPolarization(const edm::ParameterSet& cfg)
  : SVfitLegLikelihoodPolarizationBase<T>(cfg)
{
  if ( verbosity_ ) std::cout << "<SVfitLeptonLikelihoodPolarization::SVfitLeptonLikelihoodPolarization>:" << std::endl;

  useCollApproxFormulas_ = cfg.getParameter<bool>("useCollApproxFormulas");
}

template <typename T>
SVfitLeptonLikelihoodPolarization<T>::~SVfitLeptonLikelihoodPolarization()
{
// nothing to be done yet...
}

template <typename T>
double SVfitLeptonLikelihoodPolarization<T>::negLogLikelihoodPolarized(
  const T& lepton, const SVfitLegSolution& solution, double tauLeptonPol) const
{
//--- compute negative log-likelihood for tau lepton decay "leg"
//    to be compatible with decay tau- --> e- nu nu (tau- --> mu- nu nu)
//    of polarized tau lepton into electron (muon),
//    assuming  matrix element of V-A electroweak decay
//
//    NOTE: The formulas taken from the paper
//           "Tau polarization and its correlations as a probe of new physics",
//           B.K. Bullock, K. Hagiwara and A.D. Martin,
//           Nucl. Phys. B395 (1993) 499.
//
  if ( verbosity_ ) {
    std::cout << "<SVfitLeptonLikelihoodPolarization::negLogLikelihoodPolarized>:" << std::endl;
    //std::cout << " lepton charge = " << lepton.charge() << std::endl;
    //std::cout << " lepton handedness = " << solution.polarizationHypothesisName() << std::endl;
    //std::cout << "--> lepton polarization = " << tauLeptonPol << std::endl;
  }
  
  double prob = 0.;

  if ( !useCollApproxFormulas_ ) {
    double emuMass2 = square(lepton.mass());                                 // electron/muon mass
    double Emax = (tauLeptonMass2 + emuMass2)/(2*tauLeptonMass);             // formula (2.6)    
    double E = solution.p4VisRestFrame().energy();                           // electron/muon energy (in tau lepton rest-frame)
    double p = solution.p4VisRestFrame().P();                                // electron/muon momentum (in tau lepton rest-frame)
    double theta = solution.thetaRest();
    double cosTheta = TMath::Cos(theta);
    double sinTheta = TMath::Sin(theta);
    double nuMass = solution.p4InvisRestFrame().mass();    
    if ( verbosity_ ) {
      std::cout << " emuMass2 = " << emuMass2 << std::endl;
      std::cout << " Emax = " << Emax << std::endl;
      std::cout << " E = " << E << std::endl;
      std::cout << " p = " << p << std::endl;
      std::cout << " theta = " << theta << std::endl;
      std::cout << " nuMass = " << nuMass << std::endl;
    }
    prob = p*E*(3*Emax - 2*E - emuMass2/E
               + tauLeptonPol*cosTheta*(p/E)*(Emax - 2*E + emuMass2/tauLeptonMass))
          *sinTheta*(nuMass/tauLeptonMass);                                  // formula (2.5)
  } else { 
    double z = solution.x();                                                 // tau lepton visible momentum fraction (in laboratory frame)
    double z2 = square(z);
    prob = (1./3.)*(1 - z)*((5 + 5*z - 4*z2) + tauLeptonPol*(1 + z - 8*z2)); // formula (2.8)
  }

  if ( verbosity_ ) std::cout << "--> prob = " << prob << std::endl;

  if ( !(prob > 0.) ) {
    edm::LogWarning ("SVfitLeptonLikelihoodPolarization::operator()") 
      << " Unphysical solution --> returning very large negative number !!";
    return std::numeric_limits<float>::min();
  }
  
  double logLikelihood = TMath::Log(prob);
  if ( verbosity_ ) std::cout << " -logLikelihood = " << -logLikelihood << std::endl;
  
  return -logLikelihood;
}

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

typedef SVfitLeptonLikelihoodPolarization<pat::Electron> SVfitElectronLikelihoodPolarization;
typedef SVfitLeptonLikelihoodPolarization<pat::Muon> SVfitMuonLikelihoodPolarization;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_EDM_PLUGIN(SVfitElectronLikelihoodBasePluginFactory, SVfitElectronLikelihoodPolarization, "SVfitElectronLikelihoodPolarization");
DEFINE_EDM_PLUGIN(SVfitMuonLikelihoodBasePluginFactory, SVfitMuonLikelihoodPolarization, "SVfitMuonLikelihoodPolarization");
