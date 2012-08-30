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

typedef NtupleFillerBaseTest<PATMuMuMuTauQuad> FillerBaseMMMT;
typedef NtupleFillerBaseTest<PATMuMuTauTauQuad> FillerBaseMMTT;
typedef NtupleFillerBaseTest<PATMuMuEleTauQuad> FillerBaseMMET;
typedef NtupleFillerBaseTest<PATMuMuEleMuQuad> FillerBaseMMEM;
typedef NtupleFillerBaseTest<PATEleEleMuTauQuad> FillerBaseEEMT;
typedef NtupleFillerBaseTest<PATEleEleTauTauQuad> FillerBaseEETT;
typedef NtupleFillerBaseTest<PATEleEleEleTauQuad> FillerBaseEEET;
typedef NtupleFillerBaseTest<PATEleEleEleMuQuad> FillerBaseEEEM;

typedef NtupleFillerBaseTest<PATEleEleEleTri> FillerBaseEEE;
typedef NtupleFillerBaseTest<PATEleEleMuTri> FillerBaseEEM;
typedef NtupleFillerBaseTest<PATMuMuEleTri> FillerBaseMME;
typedef NtupleFillerBaseTest<PATMuMuMuTri> FillerBaseMMM;

typedef NtupleFillerBaseTest<PATMuPair> FillerBaseMM;
typedef NtupleFillerBaseTest<PATElecPair> FillerBaseEE;

//typedef edmplugin::PluginFactory<NtupleFillerBaseTest*(const edm::ParameterSet&,TTree*)> NtupleFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseMMMM*(const edm::ParameterSet&,TTree*)> MMMMFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseEEEE*(const edm::ParameterSet&,TTree*)> EEEEFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseMMEE*(const edm::ParameterSet&,TTree*)> MMEEFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseEEMM*(const edm::ParameterSet&,TTree*)> EEMMFillerFactory;

typedef edmplugin::PluginFactory<FillerBaseMMMT*(const edm::ParameterSet&,TTree*)> MMMTFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseMMTT*(const edm::ParameterSet&,TTree*)> MMTTFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseMMET*(const edm::ParameterSet&,TTree*)> MMETFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseMMEM*(const edm::ParameterSet&,TTree*)> MMEMFillerFactory;

typedef edmplugin::PluginFactory<FillerBaseEEMT*(const edm::ParameterSet&,TTree*)> EEMTFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseEETT*(const edm::ParameterSet&,TTree*)> EETTFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseEEET*(const edm::ParameterSet&,TTree*)> EEETFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseEEEM*(const edm::ParameterSet&,TTree*)> EEEMFillerFactory;

typedef edmplugin::PluginFactory<FillerBaseEEE*(const edm::ParameterSet&,TTree*)> EEEFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseEEM*(const edm::ParameterSet&,TTree*)> EEMFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseMME*(const edm::ParameterSet&,TTree*)> MMEFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseMMM*(const edm::ParameterSet&,TTree*)> MMMFillerFactory;

typedef edmplugin::PluginFactory<FillerBaseMM*(const edm::ParameterSet&,TTree*)> MMFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseEE*(const edm::ParameterSet&,TTree*)> EEFillerFactory;

#endif
