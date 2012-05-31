import FWCore.ParameterSet.Config as cms
import sys



process = cms.Process("ANALYSIS")




process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/B8EB8FFB-2B95-E011-93F2-E0CB4E29C50E.root',
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/AE38393C-2795-E011-8716-E0CB4EA0A8DF.root',
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/88725DD9-2E95-E011-8FE8-E0CB4E1A11A1.root',
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/6E60897C-3195-E011-81C0-003048678948.root',
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/66A01010-3495-E011-BE5F-E0CB4EA0A8DF.root',
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/52577935-3A95-E011-BAD0-003048678948.root',
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/40FC1A01-4495-E011-AEAA-E0CB4E1A1167.root',
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/32651D27-2F95-E011-9954-E0CB4E1A1195.root',
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/2EBD908E-3795-E011-994C-E0CB4E1A1195.root',


        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *

defaultReconstruction(process,'HLT',['HLT_IsoMu17','HLT_IsoMu24'])


#EventSelection
process.load("UWAnalysis.Configuration.muJetAnalysis_cff")



process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below


#Add event counter
addEventSummary(process)

#ntupleization
from UWAnalysis.Configuration.tools.ntupleTools import addMuJetEventTree
addMuJetEventTree(process,'muJetEventTree')










