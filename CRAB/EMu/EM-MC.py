import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
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
               
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'HLT',[
'HLT_Mu17_Ele8_CaloIdL',
'HLT_Mu8_Ele17_CaloIdL'
    ])

#EventSelection
process.load("UWAnalysis.Configuration.zEleMuAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

#Systematic Shifts 1sigma
#process.eventSelectionMuUp    = createSystematics(process,process.selectionSequence,'MuUp',1.01,1.0,1.0,1.0,1.0)
#process.eventSelectionMuDown  = createSystematics(process,process.selectionSequence,'MuDown',0.99,1.0,1.0,1.0,1.0)
process.eventSelectionEleUp    = createSystematics(process,process.selectionSequence,'EleUp',1.00,1.06,1.0,0,1.0)
process.eventSelectionEleDown  = createSystematics(process,process.selectionSequence,'EleDown',1.0,0.94,1.0,0,1.0)
process.eventSelectionJetUp    = createSystematics(process,process.selectionSequence,'JetUp',1.00,1.0,1.0,3,1.0)
process.eventSelectionJetDown  = createSystematics(process,process.selectionSequence,'JetDown',1.0,1.0,1.0,-3,1.0)
process.eventSelectionUncUp    = createSystematics(process,process.selectionSequence,'UncUp',1.00,1.0,1.0,0,1.3)
process.eventSelectionUncDown  = createSystematics(process,process.selectionSequence,'UncDown',1.0,1.0,1.0,0,0.7)


createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep++ pdgId = {Z0}",
                           "drop pdgId = {Z0} & status = 2",
                           "keep pdgId = {tau+}",
                           "keep pdgId = {tau-}",
                           "keep pdgId = {mu+}",
                           "keep pdgId = {mu-}",
                           "drop pdgId = 11",
                           "drop pdgId = -11"
                          ]
)


createGeneratedParticles(process,
                         'genTauCands',
                          [
                           "keep pdgId = {tau+} & mother.pdgId()= {Z0}",
                           "keep pdgId = {tau-} & mother.pdgId() = {Z0} "
                          ]
)


#Add event counter
addEventSummary(process)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addEleMuEventTree 

addEleMuEventTree(process,'eleMuEventTree')


#Final trees afor shapes after shifts
addEleMuEventTree(process,'eleMuEventTreeNominal','eleMuonsSorted')
#addEleMuEventTree(process,'eleMuEventTreeMuUp','eleMuonsSortedMuUp')
#addEleMuEventTree(process,'eleMuEventTreeMuDown','eleMuonsSortedMuDown')
addEleMuEventTree(process,'eleMuEventTreeEleUp','eleMuonsSortedEleUp')
addEleMuEventTree(process,'eleMuEventTreeEleDown','eleMuonsSortedEleDown')
addEleMuEventTree(process,'eleMuEventTreeJetUp','eleMuonsSortedJetUp')
addEleMuEventTree(process,'eleMuEventTreeJetDown','eleMuonsSortedJetDown')
addEleMuEventTree(process,'eleMuEventTreeUncUp','eleMuonsSortedUncUp')
addEleMuEventTree(process,'eleMuEventTreeUncDown','eleMuonsSortedUncDown')















