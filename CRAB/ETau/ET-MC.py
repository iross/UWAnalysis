import FWCore.ParameterSet.Config as cms

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
        '/store/mc/Summer11/GluGluToHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/2EBD908E-3795-E011-994C-E0CB4E1A1195.root',
        )
)


process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'HLT',[
                   'HLT_Ele18_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_MediumIsoPFTau20'
                   ])




#EventSelection
process.load("UWAnalysis.Configuration.zEleTauAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence)
#Systematic Shifts
# process.eventSelectionTauUp    = createSystematics(process,process.selectionSequence,'TauUp',1.00,1.0,1.03,0,1.0)
# process.eventSelectionTauDown  = createSystematics(process,process.selectionSequence,'TauDown',1.0,1.0,0.97,0,1.0)
# process.eventSelectionJetUp    = createSystematics(process,process.selectionSequence,'JetUp',1.00,1.0,1.0,1,1.0)
# process.eventSelectionJetDown  = createSystematics(process,process.selectionSequence,'JetDown',1.0,1.0,1.0,-1,1.0)
# process.eventSelectionUncUp    = createSystematics(process,process.selectionSequence,'UncUp',1.00,1.0,1.0,0,1.1)
# process.eventSelectionUncDown  = createSystematics(process,process.selectionSequence,'UncDown',1.0,1.0,1.0,0,0.9)

from UWAnalysis.Configuration.tools.ntupleTools import addEleTauEventTree

addEleTauEventTree(process,'eleTauEventTree')
# addEleTauEventTree(process,'eleTauEventTreeFinal','eleTausOS','osDiElectrons')
# addEleTauEventTree(process,'eleTauEventTreeTauUp','eleTausSortedTauUp','osDiElectronsTauUp','eleTracksSortedTauUp','eleGSFTracksSortedTauUp')
# addEleTauEventTree(process,'eleTauEventTreeTauDown','eleTausSortedTauDown','osDiElectronsTauDown','eleTracksSortedTauDown','eleGSFTracksSortedTauDown')
# addEleTauEventTree(process,'eleTauEventTreeJetUp','eleTausSortedJetUp','osDiElectronsJetUp','eleTracksSortedJetUp','eleGSFTracksSortedJetUp')
# addEleTauEventTree(process,'eleTauEventTreeJetDown','eleTausSortedJetDown','osDiElectronsJetDown','eleTracksSortedJetDown','eleGSFTracksSortedJetDown')
# addEleTauEventTree(process,'eleTauEventTreeUncUp','eleTausSortedUncUp','osDiElectronsUncUp','eleTracksSortedUncUp','eleGSFTracksSortedUncUp')
# addEleTauEventTree(process,'eleTauEventTreeUncDown','eleTausSortedUncDown','osDiElectronsUncDown','eleTracksSortedUncDown','eleGSFTracksSortedUncDown')




createGeneratedParticles(process,
                         'genTauCands',
                          [
                           "keep pdgId = {tau+} & mother.pdgId()= {Z0}",
                           "keep pdgId = {tau-} & mother.pdgId() = {Z0} "
                          ]
)



createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep++ pdgId = {Z0}",
                           "drop pdgId = {Z0} & status = 2",
                           "keep pdgId = {tau+}",
                           "keep pdgId = {tau-}",
                           "drop pdgId = {mu+}",
                           "drop pdgId = {mu-}",
                           "keep pdgId = 11",
                           "keep pdgId = -11"
                          ]
)
addEventSummary(process)











