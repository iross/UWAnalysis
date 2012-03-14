#include "UWAnalysis/RecoTools/plugins/SVfitLikelihoodDiTauTrackInfo.h"

#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"

#include "UWAnalysis/RecoTools/plugins/SVfitLegLikelihoodTrackInfo.h"

#include "UWAnalysis/RecoTools/interface/SVfitAlgorithm.h"
#include "UWAnalysis/RecoTools/interface/svFitAuxFunctions.h"

#include "UWAnalysis/DataFormats/interface/tauAnalysisAuxFunctions.h"

using namespace SVfit_namespace;

template <typename T>
SVfitLegLikelihoodBase<T>* createLikelihoodPlugin(const edm::ParameterSet& cfg)
{
  std::string pluginType = cfg.getParameter<std::string>("pluginType");

  typedef edmplugin::PluginFactory<SVfitLegLikelihoodBase<T>* (const edm::ParameterSet&)> SVfitLegLikelihoodPluginFactory;
  SVfitLegLikelihoodPluginFactory* pluginFactory = SVfitLegLikelihoodPluginFactory::get();

//--- print error message in case plugin of specified type cannot be created
  if ( !pluginFactory->tryToCreate(pluginType, cfg) ) {
    edm::LogError ("createLikelihoodPlugin")
      << "Failed to create plugin of type = " << pluginType << " !!";
    std::cout << " category = " << pluginFactory->category() << std::endl;
    std::cout << " available plugins = { ";
    std::vector<edmplugin::PluginInfo> plugins = pluginFactory->available();
    unsigned numPlugins = plugins.size();
    for ( unsigned iPlugin = 0; iPlugin < numPlugins; ++iPlugin ) {
      std::cout << plugins[iPlugin].name_;
      if ( iPlugin < (numPlugins - 1) ) std::cout << ", ";
    }
    std::cout << " }" << std::endl;
  }

  return pluginFactory->create(pluginType, cfg);
}

template <typename T1, typename T2>
SVfitLikelihoodDiTauTrackInfo<T1,T2>::SVfitLikelihoodDiTauTrackInfo(const edm::ParameterSet& cfg)
  : SVfitDiTauLikelihoodBase<T1,T2>(cfg)
{
//--- initialize plugins computing likelihoods for the two tau lepton decay "legs"
//   (allow different plugin types to be used for both legs,
//    but also support case that only one common type of plugin is specified)
  edm::ParameterSet cfgLeg1Likelihood, cfgLeg2Likelihood;
  if ( cfg.exists("leg1") && cfg.exists("leg2") ) {
    cfgLeg1Likelihood = cfg.getParameter<edm::ParameterSet>("leg1");
    cfgLeg2Likelihood = cfg.getParameter<edm::ParameterSet>("leg2");
  } else {
    cfgLeg1Likelihood = cfg.getParameter<edm::ParameterSet>("leg");
    cfgLeg2Likelihood = cfg.getParameter<edm::ParameterSet>("leg");
  }

  leg1Likelihood_ = createLikelihoodPlugin<T1>(cfgLeg1Likelihood);
  leg2Likelihood_ = createLikelihoodPlugin<T2>(cfgLeg2Likelihood);

  useLifetimeConstraint_ = cfg.getParameter<bool>("useLifetimeConstraint");
}

template <typename T1, typename T2>
SVfitLikelihoodDiTauTrackInfo<T1,T2>::~SVfitLikelihoodDiTauTrackInfo()
{
  delete leg1Likelihood_;
  delete leg2Likelihood_;
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauTrackInfo<T1,T2>::beginJob()
{
  leg1Likelihood_->beginJob();
  leg2Likelihood_->beginJob();
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauTrackInfo<T1,T2>::beginEvent(const edm::Event& evt, const edm::EventSetup& es)
{
  leg1Likelihood_->beginEvent(evt, es);
  leg2Likelihood_->beginEvent(evt, es);
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauTrackInfo<T1,T2>::beginCandidate(const CompositePtrCandidateT1T2MEt<T1,T2>& diTau)
{
  leg1Likelihood_->beginCandidate(*diTau.leg1());
  leg2Likelihood_->beginCandidate(*diTau.leg2());
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauTrackInfo<T1,T2>::print(std::ostream& stream) const
{
  SVfitDiTauLikelihoodBase<T1,T2>::print(stream);
  leg1Likelihood_->print(stream);
  leg2Likelihood_->print(stream);
}

template <typename T1, typename T2>
bool SVfitLikelihoodDiTauTrackInfo<T1,T2>::isFittedParameter(int index) const
{
//--- check if tau decay leg1, leg2 has tracks passing the track selection;
//    do not include primary event (tau production) vertex position in fit parameters
//    in case none of the tau decay "legs" add track constraints
  bool isLeg1TrackInfo = leg1Likelihood_->isFittedParameter(SVfit_namespace::kLeg1, SVfit_namespace::kLeg1decayDistanceLab);
  bool isLeg2TrackInfo = leg2Likelihood_->isFittedParameter(SVfit_namespace::kLeg2, SVfit_namespace::kLeg2decayDistanceLab);

  if      ( index == SVfit_namespace::kPrimaryVertexShiftX  ||
	    index == SVfit_namespace::kPrimaryVertexShiftY  ||
	    index == SVfit_namespace::kPrimaryVertexShiftZ  )
    return (isLeg1TrackInfo || isLeg2TrackInfo);
  else if ( index == SVfit_namespace::kLeg1thetaRest        ||
            index == SVfit_namespace::kLeg1phiLab           ||
            index == SVfit_namespace::kLeg1decayDistanceLab ||
            index == SVfit_namespace::kLeg1nuInvMass        ||
	    index == SVfit_namespace::kLeg1thetaVMrho       ||
	    index == SVfit_namespace::kLeg1thetaVMa1        ||
	    index == SVfit_namespace::kLeg1thetaVMa1r       ||
	    index == SVfit_namespace::kLeg1phiVMa1r         )
    return leg1Likelihood_->isFittedParameter(SVfit_namespace::kLeg1, index);
  else if ( index == SVfit_namespace::kLeg2thetaRest        ||
            index == SVfit_namespace::kLeg2phiLab           ||
            index == SVfit_namespace::kLeg2decayDistanceLab ||
            index == SVfit_namespace::kLeg2nuInvMass        ||
	    index == SVfit_namespace::kLeg2thetaVMrho       ||
	    index == SVfit_namespace::kLeg2thetaVMa1        ||
	    index == SVfit_namespace::kLeg2thetaVMa1r       ||
	    index == SVfit_namespace::kLeg2phiVMa1r         )
    return leg2Likelihood_->isFittedParameter(SVfit_namespace::kLeg2, index);
  else return false;
}

template <typename T1, typename T2>
bool SVfitLikelihoodDiTauTrackInfo<T1,T2>::supportsPolarization() const
{
  return ( leg1Likelihood_->supportsPolarization() || leg2Likelihood_->supportsPolarization() );
}

double logExponentialDecay(double tauFlightPath, double p)
{
//--- compute negative log-likelihood for tau flight path
//   (distance between primary event (tau production) vertex and secondary (tau decay) vertex)
//    to be compatible with tau lepton lifetime,
//    taking into account time dilation factor of Lorentz boost by tau momentum
//
//    NOTE: the probability for a particle of lifetime c*tau and momentum p
//          to decay after a distance x0 is taken from the PDG:
//          K. Nakamura et al. (Particle Data Group), J. Phys. G 37, 075021 (2010);
//          formula 38.14, differentiated by d/dx0 in order to get the probability
//          for the tau lepton to decay **at** distance x0
//         (rather than the probability to decay at distance x0 or greater)
//
  double a = (p/tauLeptonMass)*cTauLifetime;
  if ( tauFlightPath < 0. ) tauFlightPath = 0.;
  return -TMath::Log(a) - tauFlightPath/a;
}

template <typename T1, typename T2>
double SVfitLikelihoodDiTauTrackInfo<T1,T2>::operator()(const CompositePtrCandidateT1T2MEt<T1,T2>& diTau,
							const SVfitDiTauSolution& solution) const
{
  if ( verbosity_ ) 
    std::cout << "<SVfitLikelihoodDiTauTrackInfo::operator()>:" << std::endl;

//--- compute negative log-likelihood for shift
//    of primary event (tau lepton production) vertex position
//    to be compatible with estimated covariance matrix,
//    determined by vertex refit
  double negLogLikelihood = 0;
  negLogLikelihood += -logGaussianNd(solution.eventVertexShiftSVrefitted(), solution.eventVertexErrSVrefitted());
  if ( verbosity_ ) 
    std::cout << " eventVertex: -log(likelihood) = " << negLogLikelihood << std::endl;

//--- compute negative log-likelihoods for tracks
//    of the two tau lepton decay "legs" to be compatible
//    with secondary (tau lepton decay) vertex positions
  AlgebraicVector3 pvPosition = solution.eventVertexPosSVrefitted() - solution.eventVertexShiftSVrefitted();
  dynamic_cast<SVfitLegLikelihoodTrackInfo<T1>*>(leg1Likelihood_)->setEventVertexPos(pvPosition);
  negLogLikelihood += (*leg1Likelihood_)(*diTau.leg1(), solution.leg1());
  dynamic_cast<SVfitLegLikelihoodTrackInfo<T2>*>(leg2Likelihood_)->setEventVertexPos(pvPosition);
  negLogLikelihood += (*leg2Likelihood_)(*diTau.leg2(), solution.leg2());

  if ( useLifetimeConstraint_ ) {
    negLogLikelihood -= logExponentialDecay(solution.leg1DecayDistance(), solution.leg1().p4().P());
    if ( verbosity_ ) 
      std::cout << " leg1DecayDistance = " << solution.leg1DecayDistance() << ": -log(likelihood) = "
		<< -logExponentialDecay(solution.leg1DecayDistance(), solution.leg1().p4().P()) << std::endl;
    negLogLikelihood -= logExponentialDecay(solution.leg2DecayDistance(), solution.leg2().p4().P());
    if ( verbosity_ ) 
      std::cout << " leg2DecayDistance = " << solution.leg2DecayDistance() << ": -log(likelihood) = "
		<< -logExponentialDecay(solution.leg2DecayDistance(), solution.leg2().p4().P()) << std::endl;
  }
  
  if ( verbosity_ ) 
    std::cout << "--> -log(likelihood) = " << negLogLikelihood << std::endl;
  
  return negLogLikelihood;
}

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

typedef SVfitLikelihoodDiTauTrackInfo<pat::Electron, pat::Tau> SVfitLikelihoodElecTauPairTrackInfo;
typedef SVfitLikelihoodDiTauTrackInfo<pat::Muon, pat::Tau> SVfitLikelihoodMuTauPairTrackInfo;
typedef SVfitLikelihoodDiTauTrackInfo<pat::Tau, pat::Tau> SVfitLikelihoodDiTauPairTrackInfo;
typedef SVfitLikelihoodDiTauTrackInfo<pat::Electron, pat::Muon> SVfitLikelihoodElecMuPairTrackInfo;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_EDM_PLUGIN(SVfitElecTauPairLikelihoodBasePluginFactory, SVfitLikelihoodElecTauPairTrackInfo, "SVfitLikelihoodElecTauPairTrackInfo");
DEFINE_EDM_PLUGIN(SVfitMuTauPairLikelihoodBasePluginFactory, SVfitLikelihoodMuTauPairTrackInfo, "SVfitLikelihoodMuTauPairTrackInfo");
DEFINE_EDM_PLUGIN(SVfitDiTauPairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauPairTrackInfo, "SVfitLikelihoodDiTauPairTrackInfo");
DEFINE_EDM_PLUGIN(SVfitElecMuPairLikelihoodBasePluginFactory, SVfitLikelihoodElecMuPairTrackInfo, "SVfitLikelihoodElecMuPairTrackInfo");
