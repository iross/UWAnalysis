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
    '/store/user/bachtis/sm105-SKIM/1/SKIM-22975A0D-D4F0-E011-9A65-E0CB4E1A119E.root'
    
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'HLT',['HLT_IsoMu15_LooseIsoPFTau15'])

#EventSelection
process.load("UWAnalysis.Configuration.zMuTauAnalysis_cff")

process.metCalibration.applyCalibration = cms.bool(True)
process.metCalibration.calibrationScheme = cms.string("Phil_H")


process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

process.eventSelectionTauUp    = createSystematics(process,process.selectionSequence,'TauUp',1.00,1.0,1.03,0,1.0)
process.eventSelectionTauDown  = createSystematics(process,process.selectionSequence,'TauDown',1.0,1.0,0.97,0,1.0)
#process.eventSelectionJetUp    = createSystematics(process,process.selectionSequence,'JetUp',1.00,1.0,1.0,1,1.0)
#process.eventSelectionJetDown  = createSystematics(process,process.selectionSequence,'JetDown',1.0,1.0,1.0,-1,1.0)
#process.eventSelectionUncUp    = createSystematics(process,process.selectionSequence,'UncUp',1.00,1.0,1.0,0,1.1)
#process.eventSelectionUncDown  = createSystematics(process,process.selectionSequence,'UncDown',1.0,1.0,1.0,0,0.9)
process.eventSelectionMetUp    = createRecoilSystematics(process,process.selectionSequence,'MetUp',1.0,0.0)
process.eventSelectionMetDown  = createRecoilSystematics(process,process.selectionSequence,'MetDown',-1.0,0.0)
process.eventSelectionMetRUp    = createRecoilSystematics(process,process.selectionSequence,'MetRUp',0.0,1.0)
process.eventSelectionMetRDown  = createRecoilSystematics(process,process.selectionSequence,'MetRDown',0.0,-1.0)


createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep pdgId = 25",
                           "keep pdgId = 35",
                           "keep abs(pdgId) = 36"
                          ]
)


#Add event counter
addEventSummary(process,True)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addMuTauEventTree 

addMuTauEventTree(process,'muTauEventTree')
addMuTauEventTree(process,'muTauEventTreeFinal','diTausOS','diMuonsSorted')


#Final trees afor shapes after shifts
addMuTauEventTree(process,'muTauEventTreeTauUp','diTausTauMuonVetoTauUp','diMuonsSortedTauUp')
addMuTauEventTree(process,'muTauEventTreeTauDown','diTausTauMuonVetoTauDown','diMuonsSortedTauDown')
addMuTauEventTree(process,'muTauEventTreeMetUp','diTausTauMuonVetoMetUp','diMuonsSortedMetUp')
addMuTauEventTree(process,'muTauEventTreeMetDown','diTausTauMuonVetoMetDown','diMuonsSortedMetDown')
addMuTauEventTree(process,'muTauEventTreeMetRUp','diTausTauMuonVetoMetRUp','diMuonsSortedMetRUp')
addMuTauEventTree(process,'muTauEventTreeMetRDown','diTausTauMuonVetoMetRDown','diMuonsSortedMetRDown')

















