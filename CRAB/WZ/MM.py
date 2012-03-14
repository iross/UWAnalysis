import FWCore.ParameterSet.Config as cms
import sys
sys.setrecursionlimit(10000)

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V10::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
		'/store/mc/Fall11/WZ_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8230D216-BDF1-E011-AEAF-003048678B1C.root'
#        '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/099/88FDF12C-D17F-E011-8317-003048F1C832.root',
#                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/098/DCA6F527-DA7F-E011-BFD8-003048F117B4.root',
#                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/093/5811266A-C27F-E011-A7DC-0030487A1990.root',
#                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/088/FA043C42-E47F-E011-85B8-003048F118E0.root',
#                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/071/7450CA91-C37F-E011-8B41-001617DBD472.root',
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")

from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',['HLT_DoubleMu7_v1',
                                     'HLT_DoubleMu7_v2',
                                     'HLT_Mu13_Mu8_v2',
                                     'HLT_Mu13_Mu8_v3',
                                     'HLT_Mu13_Mu8_v4'
                                    ])


#EventSelection
process.load("UWAnalysis.Configuration.zwMuMuMuAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

from UWAnalysis.Configuration.tools.wzNtupleTools import *

addMuMuMuEventTree(process,'muMuMuEventTree','zMuMuMuCandidates')
addEventSummary(process)


















