#ifndef UWAnalysis_NtupleTools_NtupleFillerBaseTest_h 
#define UWAnalysis_NtupleTools_NtupleFillerBaseTest_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TBranch.h"
#include "TTree.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

template<typename T>

class NtupleFillerBaseTest {

    public:
        NtupleFillerBaseTest() {}
        NtupleFillerBaseTest(const edm::ParameterSet&,TTree*) {}

        ~NtupleFillerBaseTest(){}

        virtual void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)=0;
        virtual void fillTest(const T& cand, const edm::Event& iEvent, const edm::EventSetup& iSetup)=0;
};

#include "FWCore/PluginManager/interface/PluginFactory.h"


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/GenMET.h"

//typedef NtupleFillerBaseTest<reco::Candidate> NtupleFillerBaseTest;
typedef NtupleFillerBaseTest<PATMuMuMuMuQuad> FillerBaseMMMM;
typedef NtupleFillerBaseTest<PATEleEleEleEleQuad> FillerBaseEEEE;
typedef NtupleFillerBaseTest<PATMuMuEleEleQuad> FillerBaseMMEE;
typedef NtupleFillerBaseTest<PATEleEleMuMuQuad> FillerBaseEEMM;

//typedef edmplugin::PluginFactory<NtupleFillerBaseTest*(const edm::ParameterSet&,TTree*)> NtupleFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseMMMM*(const edm::ParameterSet&,TTree*)> MMMMFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseEEEE*(const edm::ParameterSet&,TTree*)> EEEEFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseMMEE*(const edm::ParameterSet&,TTree*)> MMEEFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseEEMM*(const edm::ParameterSet&,TTree*)> EEMMFillerFactory;

#endif
