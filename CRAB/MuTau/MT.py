import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'file:pickevents.root'
)

)





process.load("PhysicsTools.PatAlgos.patSequences_cff")

from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',
                      [
                         "HLT_IsoMu12_LooseIsoPFTau10",
                         "HLT_IsoMu15_LooseIsoPFTau15",
                         "HLT_IsoMu15_eta2p1_LooseIsoPFTau20"
                      ])

#EventSelection
process.load("UWAnalysis.Configuration.zMuTauAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence)

addEventSummary(process)



from UWAnalysis.Configuration.tools.ntupleTools import addMuTauEventTree

addMuTauEventTree(process,'muTauEventTree')
addMuTauEventTree(process,'muTauEventTreeFinal','diTausOS','diMuonsSorted')





#addRunRangePlotter(process,['HLT_Mu9','HLT_Mu11','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v2'])


