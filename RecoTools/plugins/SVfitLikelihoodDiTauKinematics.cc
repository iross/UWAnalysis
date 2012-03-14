#include "UWAnalysis/RecoTools/plugins/SVfitLikelihoodDiTauKinematics.h"

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
SVfitLikelihoodDiTauKinematics<T1,T2>::SVfitLikelihoodDiTauKinematics(const edm::ParameterSet& cfg)
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
}

template <typename T1, typename T2>
SVfitLikelihoodDiTauKinematics<T1,T2>::~SVfitLikelihoodDiTauKinematics()
{
  delete leg1Likelihood_;
  delete leg2Likelihood_;
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauKinematics<T1,T2>::beginJob()
{
  leg1Likelihood_->beginJob();
  leg2Likelihood_->beginJob();
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauKinematics<T1,T2>::beginEvent(edm::Event& evt, const edm::EventSetup& es)
{
  leg1Likelihood_->beginEvent(evt, es);
  leg2Likelihood_->beginEvent(evt, es);
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauKinematics<T1,T2>::beginCandidate(const CompositePtrCandidateT1T2MEt<T1,T2>& diTau)
{
  leg1Likelihood_->beginCandidate(*diTau.leg1());
  leg2Likelihood_->beginCandidate(*diTau.leg2());
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauKinematics<T1,T2>::print(std::ostream& stream) const
{
  SVfitDiTauLikelihoodBase<T1,T2>::print(stream);
  leg1Likelihood_->print(stream);
  leg2Likelihood_->print(stream);
}

template <typename T1, typename T2>
bool SVfitLikelihoodDiTauKinematics<T1,T2>::isFittedParameter(int index) const
{
  if      ( index == SVfit_namespace::kLeg1thetaRest        || 
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
bool SVfitLikelihoodDiTauKinematics<T1,T2>::supportsPolarization() const
{
  return ( leg1Likelihood_->supportsPolarization() || leg2Likelihood_->supportsPolarization() );
}

template <typename T1, typename T2>
double SVfitLikelihoodDiTauKinematics<T1,T2>::operator()(const CompositePtrCandidateT1T2MEt<T1,T2>& diTau, 
							 const SVfitDiTauSolution& solution) const
{
  SVfitLegSolution::polarizationHypothesisType leg1PolarizationHypothesis = solution.leg1().polarizationHypothesis();
  SVfitLegSolution::polarizationHypothesisType leg2PolarizationHypothesis = solution.leg2().polarizationHypothesis();

//--- check that polarization hypothesis for tau lepton decay "legs"
//    is either "unknown" for both legs for "unknown" for none of the legs
  if ( leg1PolarizationHypothesis == SVfitLegSolution::kUnknown ) assert(leg2PolarizationHypothesis == SVfitLegSolution::kUnknown);
  if ( leg2PolarizationHypothesis == SVfitLegSolution::kUnknown ) assert(leg1PolarizationHypothesis == SVfitLegSolution::kUnknown);
  
//--- compute negative log-likelihood for tau lepton pair hypothesis given as function argument
//    (sum of log-likelihoods for the two tau lepton decay "legs")
  double negativeLogLikelihood = (*leg1Likelihood_)(*diTau.leg1(), solution.leg1())
                                + (*leg2Likelihood_)(*diTau.leg2(), solution.leg2());
  
  return negativeLogLikelihood;
}

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/Candidate/interface/Candidate.h"

typedef SVfitLikelihoodDiTauKinematics<pat::Electron, pat::Tau> SVfitLikelihoodElecTauPairKinematics;
typedef SVfitLikelihoodDiTauKinematics<pat::Muon, pat::Tau> SVfitLikelihoodMuTauPairKinematics;
typedef SVfitLikelihoodDiTauKinematics<pat::Tau, pat::Tau> SVfitLikelihoodDiTauPairKinematics;
typedef SVfitLikelihoodDiTauKinematics<pat::Electron, pat::Muon> SVfitLikelihoodElecMuPairKinematics;
typedef SVfitLikelihoodDiTauKinematics<pat::Muon, pat::Muon> SVfitLikelihoodMuPairKinematics;
typedef SVfitLikelihoodDiTauKinematics<reco::Candidate, reco::Candidate> SVfitLikelihoodDiCandidatePairKinematics;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_EDM_PLUGIN(SVfitElecTauPairLikelihoodBasePluginFactory, SVfitLikelihoodElecTauPairKinematics, "SVfitLikelihoodElecTauPairKinematics");
DEFINE_EDM_PLUGIN(SVfitMuTauPairLikelihoodBasePluginFactory, SVfitLikelihoodMuTauPairKinematics, "SVfitLikelihoodMuTauPairKinematics");
DEFINE_EDM_PLUGIN(SVfitDiTauPairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauPairKinematics, "SVfitLikelihoodDiTauPairKinematics");
DEFINE_EDM_PLUGIN(SVfitElecMuPairLikelihoodBasePluginFactory, SVfitLikelihoodElecMuPairKinematics, "SVfitLikelihoodElecMuPairKinematics");
DEFINE_EDM_PLUGIN(SVfitMuPairLikelihoodBasePluginFactory, SVfitLikelihoodMuPairKinematics, "SVfitLikelihoodMuPairKinematics");
DEFINE_EDM_PLUGIN(SVfitDiCandidatePairLikelihoodBasePluginFactory, SVfitLikelihoodDiCandidatePairKinematics, "SVfitLikelihoodDiCandidatePairKinematics");
