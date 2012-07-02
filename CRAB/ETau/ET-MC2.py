import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/user/bachtis/ZTT-SKIM/1/SKIM-06CDBE64-B97C-E011-A974-002481E0D480.root'
        )
)


process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'HLT',[
'HLT_Ele15_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_LooseIsoPFTau20_v2'
                                         ])




#EventSelection
process.load("UWAnalysis.Configuration.zEleTauAnalysis_cff")
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
                         'genTauCands',
                          [
                           "keep pdgId = {tau+} & mother.pdgId()= {Z0}",
                           "keep pdgId = {tau-} & mother.pdgId() = {Z0} "
                          ]
)



createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep++ pdgId = {Z0}",
                           "drop pdgId = {Z0} & status = 2",
                           "keep pdgId = {tau+}",
                           "keep pdgId = {tau-}",
                           "drop pdgId = {mu+}",
                           "drop pdgId = {mu-}",
                           "keep pdgId = 11",
                           "keep pdgId = -11"
                          ]
)





addEventSummary(process,True)


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










