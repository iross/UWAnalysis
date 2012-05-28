import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v6/000/172/791/1EB6CBA1-92C1-E011-8E64-485B3977172C.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v6/000/172/791/2E62C1E1-55C1-E011-B756-001D09F250AF.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v6/000/172/791/36E3712F-FBC1-E011-A530-001D09F252E9.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v6/000/172/791/3887F451-6AC1-E011-838A-001D09F23A34.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v6/000/172/791/40352BF6-8DC1-E011-8EBB-BCAEC5329717.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v6/000/172/791/4E3BE023-97C1-E011-AADD-BCAEC5329730.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v6/000/172/791/4E497E90-65C1-E011-A615-BCAEC5329709.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v6/000/172/791/507EA8FA-7BC1-E011-8021-003048F024C2.root',
       '/store/data/Run2011A/MuEG/AOD/PromptReco-v6/000/172/791/523BA244-6AC1-E011-8FB3-BCAEC518FF7C.root'
                
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',[
'HLT_Mu17_Ele8_CaloIdL',
'HLT_Mu8_Ele17_CaloIdL',
'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL',
'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL'
    ])

#EventSelection
process.load("UWAnalysis.Configuration.zEleMuAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

#Add event counter
addEventSummary(process)

#ntupleization
from UWAnalysis.Configuration.tools.ntupleTools import addEleMuEventTree 

addEleMuEventTree(process,'eleMuEventTree')

addEleMuEventTree(process,'eleMuEventTreeNominal','eleMuonsOS')


















