import FWCore.ParameterSet.Config as cms
import sys
sys.setrecursionlimit(10000)

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START311_V2::All'

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FE3430A0-BE9C-E011-AF2D-E0CB4E19F972.root',
#       '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FE0F6638-C09C-E011-BCCA-001A4BD25578.root',
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',
                      [
						  "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL",
						  "HLT_DoubleMu7"
						  ])


#EventSelection
process.load("UWAnalysis.Configuration.incZ_cff")
process.eventSelectionEE = cms.Path(process.zEleEleSelectionSequence) ##changing to multiples see below
process.eventSelectionMM = cms.Path(process.zMuMuSelectionSequence) ##changing to multiples see below

createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep++ pdgId = {Z0}",
                           "drop pdgId = {Z0} & status = 2",
                           "drop pdgId = {Z0} & status = 2",
                           "keep pdgId = {mu+}",
                           "keep pdgId = {mu-}",
                          ]
)



#from UWAnalysis.Configuration.tools.ntupleTools import addEleEleEventTree
#addEleEleEventTree(process,'eleEleEventTree','EEaboveThresh')
from UWAnalysis.Configuration.tools.ntupleTools import addMuMuEventTree
addMuMuEventTree(process,'muMuEventTree','MMaboveThresh')

addEventSummary(process,False,'EE','eventSelectionEE')
addEventSummary(process,False,'MM','eventSelectionMM')













