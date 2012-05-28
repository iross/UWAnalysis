import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
   '/store/user/bachtis/Z11-SKIM/1/SKIM-82CAEBE7-36F8-E011-97B5-E0CB4E19F969.root'
   
        )
)


process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'HLT',[
'HLT_Ele18_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_MediumIsoPFTau20'
                                         ])




#EventSelection
process.load("UWAnalysis.Configuration.zEleTauAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence)


#Systematic Shifts
process.eventSelectionTauUp    = createSystematics(process,process.selectionSequence,'TauUp',1.00,1.0,1.03,0,1.0)
process.eventSelectionTauDown  = createSystematics(process,process.selectionSequence,'TauDown',1.0,1.0,0.97,0,1.0)
process.eventSelectionJetUp    = createSystematics(process,process.selectionSequence,'JetUp',1.00,1.0,1.0,1,1.0)
process.eventSelectionJetDown  = createSystematics(process,process.selectionSequence,'JetDown',1.0,1.0,1.0,-1,1.0)
process.eventSelectionUncUp    = createSystematics(process,process.selectionSequence,'UncUp',1.00,1.0,1.0,0,1.1)
process.eventSelectionUncDown  = createSystematics(process,process.selectionSequence,'UncDown',1.0,1.0,1.0,0,0.9)

from UWAnalysis.Configuration.tools.ntupleTools import addEleTauEventTree

addEleTauEventTree(process,'eleTauEventTree')
addEleTauEventTree(process,'eleTauEventTreeFinal','eleTausOS','osDiElectrons')
addEleTauEventTree(process,'eleTauEventTreeTauUp','eleTausSortedTauUp','osDiElectronsTauUp','eleTracksSortedTauUp','eleGSFTracksSortedTauUp')
addEleTauEventTree(process,'eleTauEventTreeTauDown','eleTausSortedTauDown','osDiElectronsTauDown','eleTracksSortedTauDown','eleGSFTracksSortedTauDown')
addEleTauEventTree(process,'eleTauEventTreeJetUp','eleTausSortedJetUp','osDiElectronsJetUp','eleTracksSortedJetUp','eleGSFTracksSortedJetUp')
addEleTauEventTree(process,'eleTauEventTreeJetDown','eleTausSortedJetDown','osDiElectronsJetDown','eleTracksSortedJetDown','eleGSFTracksSortedJetDown')
addEleTauEventTree(process,'eleTauEventTreeUncUp','eleTausSortedUncUp','osDiElectronsUncUp','eleTracksSortedUncUp','eleGSFTracksSortedUncUp')
addEleTauEventTree(process,'eleTauEventTreeUncDown','eleTausSortedUncDown','osDiElectronsUncDown','eleTracksSortedUncDown','eleGSFTracksSortedUncDown')





createGeneratedParticles(process,
                         'genTauCands',
                          [
                           "keep++ pdgId = {tau+}",
                           "keep++ pdgId = {tau-}",
                           "drop pdgId = {tau+}",
                           "drop pdgId = {tau-}",
                           "drop pdgId = 15",
                           "drop pdgId = -15",
                           "drop pdgId = 13",
                           "drop pdgId = -13"
                          ]
)



createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep++ pdgId = {Z0}",
                           "drop pdgId = {Z0} & status = 2",
                           "drop pdgId = {tau+}",
                           "drop pdgId = {tau-}",
                           "keep pdgId = {mu+}",
                           "keep pdgId = {mu-}",
                           "keep pdgId = 11",
                           "keep pdgId = -11"
                          ]
)





addEventSummary(process,True)













