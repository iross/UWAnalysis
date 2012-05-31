import FWCore.ParameterSet.Config as cms
import sys
sys.setrecursionlimit(10000)

process = cms.Process("ANALYSIS")


process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FE3430A0-BE9C-E011-AF2D-E0CB4E19F972.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FE0F6638-C09C-E011-BCCA-001A4BD25578.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FE00C119-C09C-E011-988B-485B39800BDF.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FC670FEA-C89C-E011-9A58-E0CB4EA0A91A.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FAFB4D5F-C49C-E011-9AF2-90E6BA442F04.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FA959D55-CB9C-E011-AC42-0030487E3026.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FA3AF934-BE9C-E011-9999-001EC9D8D48B.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FA2E9C28-C09C-E011-AFA7-E0CB4E1A1145.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FA111869-C19C-E011-95F1-485B39800B86.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/F8ECBBB4-C19C-E011-9D1C-485B39800B84.root',
              '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/F8DC1569-BE9C-E011-9AC0-001A4BA9B790.root',
       
        
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")
from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'HLT',['HLT_DoubleMu7',
                                     'HLT_Mu13_Mu8'
                                    ])
#EventSelection
process.load("UWAnalysis.Configuration.zMuMuAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

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

from UWAnalysis.Configuration.tools.ntupleTools import *

addMuMuEventTree(process,'muMuEventTree')
addEventSummary(process)

















