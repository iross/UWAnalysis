import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/099/88FDF12C-D17F-E011-8317-003048F1C832.root',
                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/098/DCA6F527-DA7F-E011-BFD8-003048F117B4.root',
                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/093/5811266A-C27F-E011-A7DC-0030487A1990.root',
                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/088/FA043C42-E47F-E011-85B8-003048F118E0.root',
                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/071/7450CA91-C37F-E011-8B41-001617DBD472.root',
)

)





process.load("PhysicsTools.PatAlgos.patSequences_cff")

from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',
                      [
                        "HLT_IsoMu12_LooseIsoPFTau10_v4",
                        "HLT_IsoMu15_LooseIsoPFTau15_v2",
                        "HLT_IsoMu15_LooseIsoPFTau15_v4",
                        "HLT_IsoMu15_LooseIsoPFTau15_v5",
                        "HLT_IsoMu15_LooseIsoPFTau15_v6"

                      ])

#EventSelection
process.load("UWAnalysis.Configuration.zMuTauAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence)

addEventSummary(process)



from UWAnalysis.Configuration.tools.ntupleTools import addMuTauEventTree

addMuTauEventTree(process,'muTauEventTree')
addMuTauEventTree(process,'muTauEventTreeNominal','diTausOS','diMuonsSorted')





#addRunRangePlotter(process,['HLT_Mu9','HLT_Mu11','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v2'])

