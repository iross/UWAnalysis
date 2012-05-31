import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_311_V2::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v1/000/161/312/7609160B-EE57-E011-9149-001617E30D12.root',
    '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v1/000/161/312/7284A8EE-0558-E011-9AC0-003048F1C424.root',
#    '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v1/000/161/312/70491EF9-F957-E011-9024-003048F11942.root'
)
#skipEvents = cms.untracked.uint32(400)

)


process.load("PhysicsTools.PatAlgos.patSequences_cff")

from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',
                      ["HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL",
                       "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1",
                       "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2",
                       "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3",
                       "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4"])
                      
#EventSelection
process.load("UWAnalysis.Configuration.zEleEleAnalysis_cff")
process.eventSelection = cms.Path(process.zEleEleSelectionSequence) ##changing to multiples see below

from UWAnalysis.Configuration.tools.ntupleTools import addEleEleEventTree
addEleEleEventTree(process,'eleEleEventTree')


addEventSummary(process)





