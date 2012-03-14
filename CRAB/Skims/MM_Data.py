import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
#		'/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/179/889/EE2FFC4D-2A03-E111-B07B-BCAEC54DB5D4.root'
#								'/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/175/832/FE2C5EC2-35DD-E011-8C5C-BCAEC53296FC.root'
								'file:skim.root'
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
process.eventSelectionMM = cms.Path(process.zMuMuSelectionSequence) ##changing to multiples see below

from UWAnalysis.Configuration.tools.ntupleTools import addMuMuEventTree
addMuMuEventTree(process,'muMuEventTree','MMaboveThresh')

addEventSummary(process,False,'MM','eventSelectionMM')
