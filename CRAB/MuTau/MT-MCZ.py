import FWCore.ParameterSet.Config as cms
import sys



process = cms.Process("ANALYSIS")




process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

'/store/mc/Spring11/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/AODSIM/PU_S1_START311_V1G1-v1/0008/40891DE2-2151-E011-8693-0024E8767D1E.root',


                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0019/522CB69B-0A52-E011-9824-00215E221680.root',
                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0018/82C72ED4-D451-E011-8632-E41F1318174C.root',
                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0012/2A805599-5B51-E011-9E58-00215E21DAC8.root',
                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0009/E8209BC5-0351-E011-A606-E41F13181CA4.root',
                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0009/08E5C9ED-1851-E011-A6EA-00215E21D972.root',
                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0007/74D2E0EC-D650-E011-8074-E41F131817C4.root',
                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0005/00221554-5B50-E011-95A1-00215E21D702.root',
                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0004/7C9B8FF3-3750-E011-8418-00215E222370.root',
                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0002/BC29F492-D94F-E011-8D96-00215E21DC72.root',
                '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0002/0039B50B-F74F-E011-9B68-00215E222022.root',
        
#        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0035/DCD56E0B-1A55-E011-8C22-00E08178C119.root',
#        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0030/10B61982-9553-E011-B51B-003048D47A84.root',
#        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/FECDC0C7-3453-E011-B7F7-00E08178C06D.root',
#        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/EA240914-3553-E011-B0F4-003048635DE8.root',
#        '/store/mc/Spring11/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/AODSIM/PU_S1_START311_V1G1-v1/0029/DEE04EC9-3453-E011-BAC4-003048D45F2A.root',
                
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *

defaultReconstructionMC(process,'HLT',['HLT_IsoMu12_LooseIsoPFTau10_v2'])


#EventSelection
process.load("UWAnalysis.Configuration.zMuTauAnalysis_cff")

process.metCalibration.applyCalibration = cms.bool(True)
process.metCalibration.calibrationScheme = cms.string("BothLegsTauTau")


process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below


#Systematic Shifts 1sigma
#process.eventSelectionMuUp    = createSystematics(process,process.selectionSequence,'MuUp',1.01,1.0,1.0,1.0,1.0)
#process.eventSelectionMuDown  = createSystematics(process,process.selectionSequence,'MuDown',0.99,1.0,1.0,1.0,1.0)
process.eventSelectionTauUp    = createSystematics(process,process.selectionSequence,'TauUp',1.00,1.0,1.09,1.0,1.0)
process.eventSelectionTauDown  = createSystematics(process,process.selectionSequence,'TauDown',1.0,1.0,0.91,1.0,1.0)
process.eventSelectionJetUp    = createSystematics(process,process.selectionSequence,'JetUp',1.00,1.0,1.0,1.09,1.0)
process.eventSelectionJetDown  = createSystematics(process,process.selectionSequence,'JetDown',1.0,1.0,1.0,0.91,1.0)
process.eventSelectionUncUp    = createSystematics(process,process.selectionSequence,'UncUp',1.00,1.0,1.0,1.0,1.3)
process.eventSelectionUncDown  = createSystematics(process,process.selectionSequence,'UncDown',1.0,1.0,1.0,1.0,0.7)




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
addEventSummary(process,True)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addMuTauEventTree 

addMuTauEventTree(process,'muTauEventTree')


#Final trees afor shapes after shifts
addMuTauEventTree(process,'muTauEventTreeNominal','diTausOS','diMuonsSorted')
addMuTauEventTree(process,'muTauEventTreeMuUp','diTausOSMuUp','diMuonsSortedMuUp')
addMuTauEventTree(process,'muTauEventTreeMuDown','diTausOSMuDown','diMuonsSortedMuDown')
addMuTauEventTree(process,'muTauEventTreeTauUp','diTausOSTauUp','diMuonsSortedTauUp')
addMuTauEventTree(process,'muTauEventTreeTauDown','diTausOSTauDown','diMuonsSortedTauDown')
addMuTauEventTree(process,'muTauEventTreeJetUp','diTausOSJetUp','diMuonsSortedJetUp')
addMuTauEventTree(process,'muTauEventTreeJetDown','diTausOSJetDown','diMuonsSortedJetDown')
addMuTauEventTree(process,'muTauEventTreeUncUp','diTausOSUncUp','diMuonsSortedUncUp')
addMuTauEventTree(process,'muTauEventTreeUncDown','diTausOSUncDown','diMuonsSortedUncDown')














