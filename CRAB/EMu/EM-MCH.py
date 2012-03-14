import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(


                
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *

defaultReconstructionMC(process,'HLT',[
'HLT_Mu17_Ele8_CaloIdL_v2',
'HLT_Mu8_Ele17_CaloIdL_v2'
    ])


#EventSelection
process.load("UWAnalysis.Configuration.zEleMuAnalysis_cff")
process.metCalibration.applyCalibration = cms.bool(True)
process.metCalibration.calibrationScheme = cms.string("BothLegsTauTau")


process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

#Systematic Shifts 1sigma
#process.eventSelectionMuUp    = createSystematics(process,process.selectionSequence,'MuUp',1.01,1.0,1.0,1.0,1.0)
#process.eventSelectionMuDown  = createSystematics(process,process.selectionSequence,'MuDown',0.99,1.0,1.0,1.0,1.0)
process.eventSelectionEleUp    = createSystematics(process,process.selectionSequence,'EleUp',1.00,1.06,1.0,1.0,1.0)
process.eventSelectionEleDown  = createSystematics(process,process.selectionSequence,'EleDown',1.0,0.94,1.0,1.0,1.0)
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

from UWAnalysis.Configuration.tools.ntupleTools import addEleMuEventTree 

addEleMuEventTree(process,'eleMuEventTree')


#Final trees afor shapes after shifts
addEleMuEventTree(process,'eleMuEventTreeNominal','eleMuonsOS')
#addEleMuEventTree(process,'eleMuEventTreeMuUp','eleMuonsOSMuUp')
#addEleMuEventTree(process,'eleMuEventTreeMuDown','eleMuonsOSMuDown')
addEleMuEventTree(process,'eleMuEventTreeEleUp','eleMuonsOSEleUp')
addEleMuEventTree(process,'eleMuEventTreeEleDown','eleMuonsOSEleDown')
addEleMuEventTree(process,'eleMuEventTreeJetUp','eleMuonsOSJetUp')
addEleMuEventTree(process,'eleMuEventTreeJetDown','eleMuonsOSJetDown')
addEleMuEventTree(process,'eleMuEventTreeUncUp','eleMuonsOSUncUp')
addEleMuEventTree(process,'eleMuEventTreeUncDown','eleMuonsOSUncDown')















