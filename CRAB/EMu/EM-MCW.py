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

        '/store/mc/Spring11/GluGluHToTauTau_M-115_7TeV-powheg-pythia6/AODSIM/PU_S1_START311_V1G1-v1/0024/C6AF6C43-C852-E011-A026-00215E21DC72.root',
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

defaultReconstructionMC(process,'HLT',[
 'HLT_Mu17_Ele8_CaloIdL',
 'HLT_Mu8_Ele17_CaloIdL'
    ])



#EventSelection
process.load("UWAnalysis.Configuration.zEleMuAnalysis_cff")
process.metCalibration.applyCalibration = cms.bool(True)
process.metCalibration.calibrationScheme = cms.string("Phil_W")


process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

#Systematic Shifts 1sigma
process.eventSelectionEleUp    = createSystematics(process,process.selectionSequence,'EleUp',1.00,1.06,1.0,0,1.0)
process.eventSelectionEleDown  = createSystematics(process,process.selectionSequence,'EleDown',1.0,0.94,1.0,0,1.0)
process.eventSelectionMetUp    = createRecoilSystematics(process,process.selectionSequence,'MetUp',1.0,0.0)
process.eventSelectionMetDown  = createRecoilSystematics(process,process.selectionSequence,'MetDown',-1.0,0.0)
process.eventSelectionMetRUp    = createRecoilSystematics(process,process.selectionSequence,'MetRUp',0.0,1.0)
process.eventSelectionMetRDown  = createRecoilSystematics(process,process.selectionSequence,'MetRDown',0.0,-1.0)


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
                           "keep pdgId = {tau+}",
                           "keep pdgId = {tau-}",
                           "keep pdgId = {mu+}",
                           "keep pdgId = {mu-}",
                           "keep pdgId = 11",
                           "keep pdgId = -11"
                          ]
)


#Add event counter
addEventSummary(process,True)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addEleMuEventTree 

addEleMuEventTree(process,'eleMuEventTree')


#Final trees afor shapes after shifts
addEleMuEventTree(process,'eleMuEventTreeNominal','eleMuonsSorted')
#addEleMuEventTree(process,'eleMuEventTreeMuUp','eleMuonsSortedMuUp')
#addEleMuEventTree(process,'eleMuEventTreeMuDown','eleMuonsSortedMuDown')
addEleMuEventTree(process,'eleMuEventTreeEleUp','eleMuonsSortedEleUp')
addEleMuEventTree(process,'eleMuEventTreeEleDown','eleMuonsSortedEleDown')
addEleMuEventTree(process,'eleMuEventTreeMetUp','eleMuonsSortedMetUp')
addEleMuEventTree(process,'eleMuEventTreeMetDown','eleMuonsSortedMetDown')
addEleMuEventTree(process,'eleMuEventTreeMetRUp','eleMuonsSortedMetRUp')
addEleMuEventTree(process,'eleMuEventTreeMetRDown','eleMuonsSortedMetRDown')
















