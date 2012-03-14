#ifndef TauAnalysis_CandidateTools_SVfitLegLikelihoodBase_h
#define TauAnalysis_CandidateTools_SVfitLegLikelihoodBase_h

/** \class SVfitLegLikelihoodBase
 *
 * Abstract base-class for plugins computing likelihood for one tau lepton decay "leg";
 * used by SVfit algorithm
 *
 * \author Evan Friis, Christian Veelken; UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitLegLikelihoodBase.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UWAnalysis/RecoTools/interface/SVfitAlgorithm.h"
#include "UWAnalysis/RecoTools/interface/svFitAuxFunctions.h"

#include "UWAnalysis/DataFormats/interface/SVfitLegSolution.h"

#include <string>
#include <iostream>

template <typename T>
class SVfitLegLikelihoodBase
{
 public:
  SVfitLegLikelihoodBase(const edm::ParameterSet& cfg)
  {
    pluginType_ = cfg.getParameter<std::string>("pluginType");
  }
  virtual ~SVfitLegLikelihoodBase() {}

  virtual void beginJob() {}
  virtual void beginEvent(const edm::Event&, const edm::EventSetup&) {}
  virtual void beginCandidate(const T&) {}

  virtual void print(std::ostream& stream) const
  {
    stream << "<SVfitLegLikelihoodBase::print>:" << std::endl;
    stream << " pluginType = " << pluginType_ << std::endl;
  }

  virtual bool isFittedParameter(int legIndex, int parIndex) const
  {
    if ( (legIndex == SVfit_namespace::kLeg1 && parIndex == SVfit_namespace::kLeg1thetaRest) ||
	      (legIndex == SVfit_namespace::kLeg2 && parIndex == SVfit_namespace::kLeg2thetaRest) )
      return true;
    else if ( (legIndex == SVfit_namespace::kLeg1 && parIndex == SVfit_namespace::kLeg1nuInvMass) ||
	      (legIndex == SVfit_namespace::kLeg2 && parIndex == SVfit_namespace::kLeg2nuInvMass) )
      return !SVfit_namespace::isMasslessNuSystem<T>();
    else
      return false;
  }

  virtual bool supportsPolarization() const
  {
    return false;
  }

  virtual double operator()(const T&, const SVfitLegSolution&) const = 0;
 protected:
  std::string pluginType_;
};

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

typedef SVfitLegLikelihoodBase<pat::Electron> SVfitElectronLikelihoodBase;
typedef SVfitLegLikelihoodBase<pat::Muon> SVfitMuonLikelihoodBase;
typedef SVfitLegLikelihoodBase<pat::Tau> SVfitTauLikelihoodBase;

#include "DataFormats/Candidate/interface/Candidate.h"

typedef SVfitLegLikelihoodBase<reco::Candidate> SVfitCandidateLikelihoodBase;

#include "FWCore/PluginManager/interface/PluginFactory.h"

typedef edmplugin::PluginFactory<SVfitElectronLikelihoodBase* (const edm::ParameterSet&)> SVfitElectronLikelihoodBasePluginFactory;
typedef edmplugin::PluginFactory<SVfitMuonLikelihoodBase* (const edm::ParameterSet&)> SVfitMuonLikelihoodBasePluginFactory;
typedef edmplugin::PluginFactory<SVfitTauLikelihoodBase* (const edm::ParameterSet&)> SVfitTauLikelihoodBasePluginFactory;
typedef edmplugin::PluginFactory<SVfitCandidateLikelihoodBase* (const edm::ParameterSet&)> SVfitCandidateLikelihoodBasePluginFactory;

#endif
