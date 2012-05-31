#ifndef UWAnalysis_NtupleTools_NtupleFillerBase_h 
#define UWAnalysis_NtupleTools_NtupleFillerBase_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TBranch.h"
#include "TTree.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

class NtupleFillerBase {

 public:
  NtupleFillerBase() {}
  NtupleFillerBase(const edm::ParameterSet&,TTree*) {}

  ~NtupleFillerBase(){}

  virtual void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)=0;
};

#include "FWCore/PluginManager/interface/PluginFactory.h"

typedef edmplugin::PluginFactory<NtupleFillerBase*(const edm::ParameterSet&,TTree*)> NtupleFillerFactory;

#endif
