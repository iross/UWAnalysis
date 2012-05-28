import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:pickevents.root'
        )
)





process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',["HLT_Ele15_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_LooseIsoPFTau20",
                                     "HLT_Ele15_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TightIsoPFTau20",
                                     "HLT_Ele18_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_MediumIsoPFTau20",
                                     "HLT_Ele20_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_MediumIsoPFTau20",                                    
                                     ])




#EventSelection
process.load("UWAnalysis.Configuration.zEleTauAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence)


from UWAnalysis.Configuration.tools.ntupleTools import addEleTauEventTree

addEleTauEventTree(process,'eleTauEventTree')
addEleTauEventTree(process,'eleTauEventTreeFinal','eleTausOS','osDiElectrons')

addEventSummary(process)








