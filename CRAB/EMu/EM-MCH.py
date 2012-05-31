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
'HLT_Mu17_Ele8_CaloIdL',
'HLT_Mu8_Ele17_CaloIdL'
    ])


#EventSelection
process.load("UWAnalysis.Configuration.zEleMuAnalysis_cff")
process.metCalibration.applyCalibration = cms.bool(True)
process.metCalibration.calibrationScheme = cms.string("Phil_H")


process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

#Systematic Shifts 1sigma
process.eventSelectionEleUp    = createSystematics(process,process.selectionSequence,'EleUp',1.00,1.06,1.0,0,1.0)
process.eventSelectionEleDown  = createSystematics(process,process.selectionSequence,'EleDown',1.0,0.94,1.0,0,1.0)
process.eventSelectionMetUp    = createRecoilSystematics(process,process.selectionSequence,'MetUp',1.0,0.0)
process.eventSelectionMetDown  = createRecoilSystematics(process,process.selectionSequence,'MetDown',-1.0,0.0)
process.eventSelectionMetRUp    = createRecoilSystematics(process,process.selectionSequence,'MetRUp',0.0,1.0)
process.eventSelectionMetRDown  = createRecoilSystematics(process,process.selectionSequence,'MetRDown',0.0,-1.0)


createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep pdgId = 25",
                           "keep pdgId = 35",
                           "keep abs(pdgId) = 36",
                          ]
)




#Add event counter
addEventSummary(process,True)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addEleMuEventTree 

addEleMuEventTree(process,'eleMuEventTree')


#Final trees afor shapes after shifts
addEleMuEventTree(process,'eleMuEventTreeNominal','eleMuonsSorted')
#addEleMuEventTree(process,'eleMuEventTreeMuUp','eleMuonsSortedMuUp')
#addEleMuEventTree(process,'eleMuEventTreeMuDown','eleMuonsSortedMuDown')
addEleMuEventTree(process,'eleMuEventTreeEleUp','eleMuonsSortedEleUp')
addEleMuEventTree(process,'eleMuEventTreeEleDown','eleMuonsSortedEleDown')
addEleMuEventTree(process,'eleMuEventTreeMetUp','eleMuonsSortedMetUp')
addEleMuEventTree(process,'eleMuEventTreeMetDown','eleMuonsSortedMetDown')
addEleMuEventTree(process,'eleMuEventTreeMetRUp','eleMuonsSortedMetRUp')
addEleMuEventTree(process,'eleMuEventTreeMetRDown','eleMuonsSortedMetRDown')















