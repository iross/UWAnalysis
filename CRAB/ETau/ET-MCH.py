import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0035/DCD56E0B-1A55-E011-8C22-00E08178C119.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0030/10B61982-9553-E011-B51B-003048D47A84.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/FECDC0C7-3453-E011-B7F7-00E08178C06D.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/EA240914-3553-E011-B0F4-003048635DE8.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/DEE04EC9-3453-E011-BAC4-003048D45F2A.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/B0334413-3553-E011-96FA-0025B3E05D3E.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/AC57C215-3553-E011-9554-0025B3E06468.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/9C953B14-3553-E011-85B9-00E0817917E3.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/8EC598C7-3453-E011-AC82-002481E14F8C.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/8A6E8413-3553-E011-A301-0025B3E0653C.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/5288CBC7-3453-E011-B3A2-00E0817918A7.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/147EE7CB-3453-E011-BB8B-003048D477A0.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/0AA3BCC7-3453-E011-AF5C-00E08178C0FB.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/F6335026-6153-E011-9A97-00E08178C0F9.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/D0B6DE5C-3053-E011-8240-0025B3E05BFC.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/CA0406EC-2C53-E011-8F9F-00E08177F14F.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/C4657B5E-3053-E011-8C8E-003048D45F62.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/BACE1CDB-5D53-E011-966C-0025B3E06388.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/BA436444-6053-E011-9EEA-002481E75CDE.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/AEB3EE46-1A53-E011-906A-003048636236.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/AE37AAE5-2C53-E011-90DB-003048D476CC.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/A03B7B78-2D53-E011-8D43-0025B3E05BB8.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/9CCA92B8-2253-E011-B590-003048D4624C.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/901E9BED-2E53-E011-B24A-0025B3E05D74.root',
        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0028/86CEA7D4-5D53-E011-8869-003048D45FD2.root',
        )
)


process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'HLT',[
'HLT_Ele15_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_LooseIsoPFTau20_v2'
                                         ])




#EventSelection
process.load("UWAnalysis.Configuration.zEleTauAnalysis_cff")

process.metCalibration.applyCalibration = cms.bool(True)
process.metCalibration.calibrationScheme = cms.string("BothLegsTauTau")


process.eventSelection = cms.Path(process.selectionSequence)

#Systematic Shifts
process.eventSelectionEleUp     = createSystematics(process,process.selectionSequence,'EleUp',1.00,1.06,1.0,1.0,1.0)
process.eventSelectionEleDown   = createSystematics(process,process.selectionSequence,'EleDown',1.0,0.94,1.0,1.0,1.0)
process.eventSelectionTauUp    = createSystematics(process,process.selectionSequence,'TauUp',1.00,1.0,1.09,1.0,1.0)
process.eventSelectionTauDown  = createSystematics(process,process.selectionSequence,'TauDown',1.0,1.0,0.91,1.0,1.0)
process.eventSelectionJetUp    = createSystematics(process,process.selectionSequence,'JetUp',1.00,1.0,1.0,1.09,1.0)
process.eventSelectionJetDown  = createSystematics(process,process.selectionSequence,'JetDown',1.0,1.0,1.0,0.91,1.0)
process.eventSelectionUncUp    = createSystematics(process,process.selectionSequence,'UncUp',1.00,1.0,1.0,1.0,1.3)
process.eventSelectionUncDown  = createSystematics(process,process.selectionSequence,'UncDown',1.0,1.0,1.0,1.0,0.7)

createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep++ pdgId = 25",
                           "keep++ pdgId = 35",
                           "keep++ pdgId = 36",
                           "keep pdgId = {tau+}",
                           "keep pdgId = {tau-}"
                          ]
)


addEventSummary(process)


from UWAnalysis.Configuration.tools.ntupleTools import addEleTauEventTree

addEleTauEventTree(process,'eleTauEventTree')
addEleTauEventTree(process,'eleTauEventTreeNominal','eleTausOS','osDiElectrons')
addEleTauEventTree(process,'eleTauEventTreeEleUp','eleTausOSEleUp','osDiElectronsEleUp','eleTracksSortedEleUp','eleGSFTracksSortedEleUp')
addEleTauEventTree(process,'eleTauEventTreeEleDown','eleTausOSEleDown','osDiElectronsEleDown','eleTracksSortedEleDown','eleGSFTracksSortedEleDown')
addEleTauEventTree(process,'eleTauEventTreeTauUp','eleTausOSTauUp','osDiElectronsTauUp','eleTracksSortedTauUp','eleGSFTracksSortedTauUp')
addEleTauEventTree(process,'eleTauEventTreeTauDown','eleTausOSTauDown','osDiElectronsTauDown','eleTracksSortedTauDown','eleGSFTracksSortedTauDown')
addEleTauEventTree(process,'eleTauEventTreeJetUp','eleTausOSJetUp','osDiElectronsJetUp','eleTracksSortedJetUp','eleGSFTracksSortedJetUp')
addEleTauEventTree(process,'eleTauEventTreeJetDown','eleTausOSJetDown','osDiElectronsJetDown','eleTracksSortedJetDown','eleGSFTracksSortedJetDown')
addEleTauEventTree(process,'eleTauEventTreeUncUp','eleTausOSUncUp','osDiElectronsUncUp','eleTracksSortedUncUp','eleGSFTracksSortedUncUp')
addEleTauEventTree(process,'eleTauEventTreeUncDown','eleTausOSUncDown','osDiElectronsUncDown','eleTracksSortedUncDown','eleGSFTracksSortedUncDown')









