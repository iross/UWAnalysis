#ifndef UWAnalysis_NtupleTools_NtupleFillerBaseMultiCand_h
#define UWAnalysis_NtupleTools_NtupleFillerBaseMultiCand_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TBranch.h"
#include "TTree.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

template<typename T>

class NtupleFillerBaseMultiCand {

    public:
        NtupleFillerBaseMultiCand() {}
        NtupleFillerBaseMultiCand(const edm::ParameterSet&,TTree*) {}

        ~NtupleFillerBaseMultiCand(){}

        virtual void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)=0;
        virtual void fill(const T& cand, const edm::Event& iEvent, const edm::EventSetup& iSetup)=0;
};

#include "FWCore/PluginManager/interface/PluginFactory.h"


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/GenMET.h"

//typedef NtupleFillerBaseMultiCand<reco::Candidate> NtupleFillerBaseMultiCand;
typedef NtupleFillerBaseMultiCand<PATMuMuMuMuQuad> FillerBaseMMMM;
typedef NtupleFillerBaseMultiCand<PATEleEleEleEleQuad> FillerBaseEEEE;
typedef NtupleFillerBaseMultiCand<PATMuMuEleEleQuad> FillerBaseMMEE;
typedef NtupleFillerBaseMultiCand<PATEleEleMuMuQuad> FillerBaseEEMM;

typedef NtupleFillerBaseMultiCand<PATMuMuMuTauQuad> FillerBaseMMMT;
typedef NtupleFillerBaseMultiCand<PATMuMuTauTauQuad> FillerBaseMMTT;
typedef NtupleFillerBaseMultiCand<PATMuMuEleTauQuad> FillerBaseMMET;
typedef NtupleFillerBaseMultiCand<PATMuMuEleMuQuad> FillerBaseMMEM;
typedef NtupleFillerBaseMultiCand<PATEleEleMuTauQuad> FillerBaseEEMT;
typedef NtupleFillerBaseMultiCand<PATEleEleTauTauQuad> FillerBaseEETT;
typedef NtupleFillerBaseMultiCand<PATEleEleEleTauQuad> FillerBaseEEET;
typedef NtupleFillerBaseMultiCand<PATEleEleEleMuQuad> FillerBaseEEEM;

typedef NtupleFillerBaseMultiCand<PATEleEleEleTri> FillerBaseEEE;
typedef NtupleFillerBaseMultiCand<PATEleEleMuTri> FillerBaseEEM;
typedef NtupleFillerBaseMultiCand<PATMuMuEleTri> FillerBaseMME;
typedef NtupleFillerBaseMultiCand<PATMuMuMuTri> FillerBaseMMM;

typedef NtupleFillerBaseMultiCand<PATMuPair> FillerBaseMM;
typedef NtupleFillerBaseMultiCand<PATElecPair> FillerBaseEE;

typedef NtupleFillerBaseMultiCand<pat::Electron> FillerBaseE;
typedef NtupleFillerBaseMultiCand<pat::Muon> FillerBaseM;
typedef NtupleFillerBaseMultiCand<pat::Tau> FillerBaseT;

//typedef edmplugin::PluginFactory<NtupleFillerBaseMultiCand*(const edm::ParameterSet&,TTree*)> NtupleFillerFactory;
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

typedef edmplugin::PluginFactory<FillerBaseE*(const edm::ParameterSet&,TTree*)> EFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseM*(const edm::ParameterSet&,TTree*)> MFillerFactory;
typedef edmplugin::PluginFactory<FillerBaseT*(const edm::ParameterSet&,TTree*)> TFillerFactory;

#endif
