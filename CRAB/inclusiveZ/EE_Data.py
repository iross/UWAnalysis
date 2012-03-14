import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1 

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
								'/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/180/252/CED88138-4305-E111-BE64-003048CF99BA.root'
#    '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/165/364/C24C1B99-AD84-E011-AB88-001D09F23A34.root',
#    '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/165/364/BAB3EE3C-7884-E011-AD96-003048D2BE06.root',
#    '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/165/364/B4C7EE71-8584-E011-979E-001D09F29597.root',
#    '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/165/364/9CD43191-7E84-E011-A184-001D09F2983F.root',
#    '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/165/364/9A210540-CF84-E011-BA5C-003048F024F6.root'
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
process.load("UWAnalysis.Configuration.incZ_cff")
process.eventSelectionEE = cms.Path(process.zEleEleSelectionSequence) ##changing to multiples see below

from UWAnalysis.Configuration.tools.ntupleTools import addEleEleEventTree
addEleEleEventTree(process,'eleEleEventTree','EEaboveThresh')


addEventSummary(process,False,'EEEE','eventSelectionEE')
