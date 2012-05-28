import FWCore.ParameterSet.Config as cms
import sys
sys.setrecursionlimit(10000)

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START311_V2::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/mc/Spring11/DYToEE_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0000/A6F5F681-E34D-E011-B129-00215E2220A0.root',
#    '/store/mc/Spring11/DYToEE_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0000/9253AF04-184E-E011-88EF-E41F131817D8.root',
#    '/store/mc/Spring11/DYToEE_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0000/1EDB1E9D-0B4E-E011-AA67-00215E2222E0.root',
 #   '/store/mc/Spring11/DYToEE_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0000/1663E6CF-0E4E-E011-8A25-E41F1318180C.root',
 #   '/store/mc/Spring11/DYToEE_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0000/12BCA95D-094E-E011-AFBF-00215E2211B8.root'
    
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'REDIGI311X')


#EventSelection
process.load("UWAnalysis.Configuration.zEleEleAnalysis_cff")
process.eventSelection = cms.Path(process.zEleEleSelectionSequence) ##changing to multiples see below



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



from UWAnalysis.Configuration.tools.ntupleTools import addEleEleEventTree
addEleEleEventTree(process,'eleEleEventTree')
addEventSummary(process)

















