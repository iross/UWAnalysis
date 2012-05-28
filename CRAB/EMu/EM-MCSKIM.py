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
    '/store/user/bachtis/Z11-SKIM/1/SKIM-82CAEBE7-36F8-E011-97B5-E0CB4E19F969.root'
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
process.eventSelectionEleUp    = createSystematics(process,process.selectionSequence,'EleUp',1.00,1.06,1.0,0,1.0)
process.eventSelectionEleDown  = createSystematics(process,process.selectionSequence,'EleDown',1.0,0.94,1.0,0,1.0)
process.eventSelectionJetUp    = createSystematics(process,process.selectionSequence,'JetUp',1.00,1.0,1.0,3,1.0)
process.eventSelectionJetDown  = createSystematics(process,process.selectionSequence,'JetDown',1.0,1.0,1.0,-3,1.0)
process.eventSelectionUncUp    = createSystematics(process,process.selectionSequence,'UncUp',1.00,1.0,1.0,0,1.3)
process.eventSelectionUncDown  = createSystematics(process,process.selectionSequence,'UncDown',1.0,1.0,1.0,0,0.7)

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
addEleMuEventTree(process,'eleMuEventTreeJetUp','eleMuonsSortedJetUp')
addEleMuEventTree(process,'eleMuEventTreeJetDown','eleMuonsSortedJetDown')
addEleMuEventTree(process,'eleMuEventTreeUncUp','eleMuonsSortedUncUp')
addEleMuEventTree(process,'eleMuEventTreeUncDown','eleMuonsSortedUncDown')















