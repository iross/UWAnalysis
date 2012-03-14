import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/user/bachtis/ZTT-SKIM/1/SKIM-74E6F2D1-B156-E011-BB15-0018F3D096D2.root',
    '/store/user/bachtis/ZTT-SKIM/1/SKIM-62E612E8-A656-E011-BEF0-0026189438DE.root'
    
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'HLT',['HLT_IsoMu12_LooseIsoPFTau10_v2'])

#EventSelection
process.load("UWAnalysis.Configuration.zMuTauAnalysis_cff")

process.metCalibration.applyCalibration = cms.bool(True)
process.metCalibration.calibrationScheme = cms.string("BothLegsTauTau")


process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

#Systematic Shifts 1sigma
#process.eventSelectionMuUp    = createSystematics(process,process.selectionSequence,'MuUp',1.01,1.0,1.0,1.0,1.0)
#process.eventSelectionMuDown  = createSystematics(process,process.selectionSequence,'MuDown',0.99,1.0,1.0,1.0,1.0)
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


#Add event counter
addEventSummary(process)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addMuTauEventTree 

addMuTauEventTree(process,'muTauEventTree')


#Final trees afor shapes after shifts
addMuTauEventTree(process,'muTauEventTreeNominal','diTausOS','diMuonsSorted')
addMuTauEventTree(process,'muTauEventTreeMuUp','diTausOSMuUp','diMuonsSortedMuUp')
addMuTauEventTree(process,'muTauEventTreeMuDown','diTausOSMuDown','diMuonsSortedMuDown')
addMuTauEventTree(process,'muTauEventTreeTauUp','diTausOSTauUp','diMuonsSortedTauUp')
addMuTauEventTree(process,'muTauEventTreeTauDown','diTausOSTauDown','diMuonsSortedTauDown')
addMuTauEventTree(process,'muTauEventTreeJetUp','diTausOSJetUp','diMuonsSortedJetUp')
addMuTauEventTree(process,'muTauEventTreeJetDown','diTausOSJetDown','diMuonsSortedJetDown')
addMuTauEventTree(process,'muTauEventTreeUncUp','diTausOSUncUp','diMuonsSortedUncUp')
addMuTauEventTree(process,'muTauEventTreeUncDown','diTausOSUncDown','diMuonsSortedUncDown')














