import FWCore.ParameterSet.Config as cms
import sys



process = cms.Process("ANALYSIS")




process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'


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

defaultReconstructionMC(process,'HLT',['HLT_IsoMu15_LooseIsoPFTau15'])



#EventSelection
process.load("UWAnalysis.Configuration.zMuTauAnalysis_cff")

process.metCalibration.applyCalibration = cms.bool(True)


process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below


#Systematic Shifts 1sigma
process.eventSelectionTauUp    = createSystematics(process,process.selectionSequence,'TauUp',1.00,1.0,1.03,0,1.0)
process.eventSelectionTauDown  = createSystematics(process,process.selectionSequence,'TauDown',1.0,1.0,0.97,0,1.0)
process.eventSelectionJetUp    = createSystematics(process,process.selectionSequence,'JetUp',1.00,1.0,1.0,1,1.0)
process.eventSelectionJetDown  = createSystematics(process,process.selectionSequence,'JetDown',1.0,1.0,1.0,-1,1.0)
process.eventSelectionUncUp    = createSystematics(process,process.selectionSequence,'UncUp',1.00,1.0,1.0,0,1.1)
process.eventSelectionUncDown  = createSystematics(process,process.selectionSequence,'UncDown',1.0,1.0,1.0,0,0.9)




createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep++ pdgId = {Z0}",
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
                           "keep pdgId = {tau-} & mother.pdgId() = {Z0}"
                          ]
)


#Add event counter
addEventSummary(process)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addMuTauEventTree

addMuTauEventTree(process,'muTauEventTree')
addMuTauEventTree(process,'muTauEventTreeFinal','diTausOS','diMuonsSorted')


#Final trees afor shapes after shifts
addMuTauEventTree(process,'muTauEventTreeTauUp','diTausTauMuonVetoTauUp','diMuonsSortedTauUp')
addMuTauEventTree(process,'muTauEventTreeTauDown','diTausTauMuonVetoTauDown','diMuonsSortedTauDown')
addMuTauEventTree(process,'muTauEventTreeJetUp','diTausTauMuonVetoJetUp','diMuonsSortedJetUp')
addMuTauEventTree(process,'muTauEventTreeJetDown','diTausTauMuonVetoJetDown','diMuonsSortedJetDown')
addMuTauEventTree(process,'muTauEventTreeUncUp','diTausTauMuonVetoUncUp','diMuonsSortedUncUp')
addMuTauEventTree(process,'muTauEventTreeUncDown','diTausTauMuonVetoUncDown','diMuonsSortedUncDown')









