import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'START42_V13::All'
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'/store/results/higgs/DoubleMu/StoreResults-DoubleMu_2011B_PR_v1_PFiso1_embedded_trans1_tau123_pttau1_18tau2_8_v1-f456bdbb960236e5c696adfe9b04eaae/DoubleMu/USER/StoreResults-DoubleMu_2011B_PR_v1_PFiso1_embedded_trans1_tau123_pttau1_18tau2_8_v1-f456bdbb960236e5c696adfe9b04eaae/0000/4E721C2D-4A0F-E111-B83B-0023AEFDEE9C.root'

        )
)



process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'EmbeddedRECO',[
'HLT_Mu17_Ele8_CaloIdL',
'HLT_Mu8_Ele17_CaloIdL'
    ])

process.recoPAT = cms.Path(process.ak5PFJets+process.pfMet+process.PFTau+process.patElectronId+process.patDefaultSequence)


process.jetTracksAssociatorAtVertex.tracks = cms.InputTag("tmfTracks")

#EventSelection
process.load("UWAnalysis.Configuration.zEleMuAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below

process.eventSelectionEleUp    = createSystematics(process,process.selectionSequence,'EleUp',1.00,1.0,1.00,0,1.0,0.01601,0.04745)
process.eventSelectionEleDown  = createSystematics(process,process.selectionSequence,'EleDown',1.0,1.0,1.00,0,1.0,-0.01601,-0.04745)

#Add event counter
addEventSummary(process)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addEleMuEventTree 

addEleMuEventTree(process,'eleMuEventTree')
addEleMuEventTree(process,'eleMuEventTreeEleUp','eleMuonsSortedEleUp')
addEleMuEventTree(process,'eleMuEventTreeEleDown','eleMuonsSortedEleDown')














