import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_311_V2::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
		'file:r172286l131.root',
		'file:r172819l220.root',
		'file:r171050l514.root',
		'file:r171282l39.root'
#    '/store/data/Run2011A/DoubleMu/AOD/PromptReco-v4/000/167/098/7211E94D-7D9A-E011-A713-003048F1BF66.root'
#		'/store/data/Run2011A/DoubleMu/AOD/PromptReco-v1/000/161/312/82DF8BDA-E957-E011-8BB6-001617C3B79A.root',
#        '/store/data/Run2011A/DoubleMu/AOD/PromptReco-v1/000/161/312/76829660-F457-E011-AB0D-003048F118C6.root',
#        '/store/data/Run2011A/DoubleMu/AOD/PromptReco-v1/000/161/312/449EDD53-7959-E011-AF38-003048F024C2.root'
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',
                      [
									"HLT_DoubleMu3",
						  			"HLT_DoubleMu7",
									"HLT_Mu13_Mu8",
									"HLT_Ele10_LW_LR1",
									"HLT_Ele15_SW_LR1",
									"HLT_Ele15_SW_CaloEleID_L1R",
									"HLT_Ele17_SW_TightEleID_L1R",
									"HLT_Ele17_SW_TighterEleIdIsol_L1R",
									"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL",
									"HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"
                      ])

#EventSelection
process.load("UWAnalysis.Configuration.zzLLLLAnalysis_cff")
process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence) ##changing to multiples see below
process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)


from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold')
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold')
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold')
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold')
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCandsAboveThreshold')
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeID','MMEEzzEleId')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCandsAboveThreshold')
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeID','MMMMzzMuIDSecondPair')

#Add event counter
addEventSummary(process,False,'MMMT','eventSelectionMMMT')
addEventSummary(process,False,'MMTT','eventSelectionMMTT')
addEventSummary(process,False,'MMET','eventSelectionMMET')
addEventSummary(process,False,'MMEM','eventSelectionMMEM')
addEventSummary(process,False,'MMEE','eventSelectionMMEE')
addEventSummary(process,False,'MMMM','eventSelectionMMMM')
