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
'/store/results/higgs/DoubleMu/StoreResults-DoubleMu_2011B_PR_v1_PFiso1_embedded_trans1_tau116_ptmu1_13had1_17_v1-f456bdbb960236e5c696adfe9b04eaae/DoubleMu/USER/StoreResults-DoubleMu_2011B_PR_v1_PFiso1_embedded_trans1_tau116_ptmu1_13had1_17_v1-f456bdbb960236e5c696adfe9b04eaae/0000/B6571906-450F-E111-B9B9-0023AEFDEE80.root'
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *

defaultReconstruction(process,'EmbeddedRECO',['HLT_IsoMu12_LooseIsoPFTau10'])

process.recoPAT = cms.Path(process.ak5PFJets+process.pfMet+process.PFTau+process.patElectronId+process.patDefaultSequence)



#EventSelection
process.load("UWAnalysis.Configuration.zMuTauAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below


#Systematic Shifts 1sigma
#process.eventSelectionMuUp    = createSystematics(process,process.selectionSequence,'MuUp',1.01,1.0,1.0,1.0,1.0)
#process.eventSelectionMuDown  = createSystematics(process,process.selectionSequence,'MuDown',0.99,1.0,1.0,1.0,1.0)
process.eventSelectionTauUp    = createSystematics(process,process.selectionSequence,'TauUp',1.00,1.0,1.03,0,1.0)
process.eventSelectionTauDown  = createSystematics(process,process.selectionSequence,'TauDown',1.0,1.0,0.97,0,1.0)


#fix btagging
process.jetTracksAssociatorAtVertex.tracks = cms.InputTag("tmfTracks")

#Add event counter
addEventSummary(process)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addMuTauEventTree

addMuTauEventTree(process,'muTauEventTree')
addMuTauEventTree(process,'muTauEventTreeFinal','diTausOS','diMuonsSorted')


#Final trees afor shapes after shifts
addMuTauEventTree(process,'muTauEventTreeTauUp','diTausTauMuonVetoTauUp','diMuonsSortedTauUp')
addMuTauEventTree(process,'muTauEventTreeTauDown','diTausTauMuonVetoTauDown','diMuonsSortedTauDown')







