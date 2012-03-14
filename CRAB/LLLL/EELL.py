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
'/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/175/835/9212E97C-CDDB-E011-8A58-001D09F25479.root'
#        '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v6/000/172/620/E0BE6B50-1BC0-E011-975B-003048F1183E.root'
#		'/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v1/000/161/312/7609160B-EE57-E011-9149-001617E30D12.root',
#        '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v1/000/161/312/7284A8EE-0558-E011-9AC0-003048F1C424.root',
#        '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v1/000/161/312/70491EF9-F957-E011-9024-003048F11942.root'
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
process.load("UWAnalysis.Configuration.zzLLLLAnalysisFinalSel_cff")
process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)


from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree2','EETTzzCleanedCandsEEMass')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree2','EEETzzCleanedCandsEEMass')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree2','EEMTzzCleanedCandsEEMass')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree2','EEEMzzCleanedCandsEEMass')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCandsAboveThreshold')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree2','EEEEzzCleanedCandsEleEleQ')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeID','EEEEzzEleIDSecond')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCandsAboveThreshold')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree2','EEMMzzCleanedCandsMuMuQ')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeID','EEMMzzMuIDSecondPair')

#Add event counter
addEventSummary(process,False,'EEMT','eventSelectionEEMT')
addEventSummary(process,False,'EEET','eventSelectionEEET')
addEventSummary(process,False,'EETT','eventSelectionEETT')
addEventSummary(process,False,'EEEM','eventSelectionEEEM')
addEventSummary(process,False,'EEEE','eventSelectionEEEE')
addEventSummary(process,False,'EEMM','eventSelectionEEMM')

