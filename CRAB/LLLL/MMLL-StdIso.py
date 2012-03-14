import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_311_V2::All'

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
		'file:e862270386.root',
		'file:e876658967.root',
		'file:e559839432.root',
		'file:e218903169.root',
		'file:e140063742.root'
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
									"HLT_Mu17_Mu8",
									"HLT_Ele10_LW_LR1",
									"HLT_Ele15_SW_LR1",
									"HLT_Ele15_SW_CaloEleID_L1R",
									"HLT_Ele17_SW_TightEleID_L1R",
									"HLT_Ele17_SW_TighterEleIdIsol_L1R",
									"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL",
									"HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"
                      ])

#EventSelection
process.load("UWAnalysis.Configuration.zzLLLLAnalysisStdIso_cff")
process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence) ##changing to multiples see below
process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)


from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuTauTauEventTree(process,'muMuTauTauEventTree2','MMTTzzCleanedCandsMMMass','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree2','MMMTzzCleanedCandsMMMass','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuEleTauEventTree(process,'muMuEleTauEventTree2','MMETzzCleanedCandsMMMass','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuEleMuEventTree(process,'muMuEleMuEventTree2','MMEMzzCleanedCandsMMMass','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCandsAboveThreshold','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuEleEleEventTree(process,'muMuEleEleEventTree2','MMEEzzCleanedCandsEleEleQ','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeID','MMEEzzEleId','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCandsAboveThreshold','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree2','MMMMzzCleanedCandsMuMuQ','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeID','MMMMzzMuIDSecondPair','EEEEzzCleanedCandsAboveThreshold','EEMMzzCleanedCandsAboveThreshold','MMEEzzCleanedCandsAboveThreshold','MMMMzzCleanedCandsAboveThreshold')


#Add event counter
addEventSummary(process,False,'MMMT','eventSelectionMMMT')
addEventSummary(process,False,'MMTT','eventSelectionMMTT')
addEventSummary(process,False,'MMET','eventSelectionMMET')
addEventSummary(process,False,'MMEM','eventSelectionMMEM')
addEventSummary(process,False,'MMEE','eventSelectionMMEE')
addEventSummary(process,False,'MMMM','eventSelectionMMMM')
