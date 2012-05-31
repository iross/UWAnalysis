import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

#process.GlobalTag.globaltag = 'START42_V13::All'



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'/store/results/higgs/DoubleMu/StoreResults-DoubleMu_2011B_PR_v1_embedded_trans1_tau115_ptelec1_17had1_17_v2-f456bdbb960236e5c696adfe9b04eaae/DoubleMu/USER/StoreResults-DoubleMu_2011B_PR_v1_embedded_trans1_tau115_ptelec1_17had1_17_v2-f456bdbb960236e5c696adfe9b04eaae/0000/BE3ED666-570E-E111-AE13-0023AEFDEB8C.root'
        )
)


process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'EmbeddedRECO',[
                   'HLT_Ele15_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_LooseIsoPFTau15'
                   ])


process.recoPAT = cms.Path(process.ak5PFJets+process.pfMet+process.PFTau+process.patElectronId+process.patDefaultSequence)

#fix btagging
process.jetTracksAssociatorAtVertex.tracks = cms.InputTag("tmfTracks")



#EventSelection
process.load("UWAnalysis.Configuration.zEleTauAnalysis_cff")
process.eventSelection = cms.Path(process.selectionSequence)
process.eventSelectionTauUp    = createSystematics(process,process.selectionSequence,'TauUp',1.00,1.0,1.03,0,1.0)
process.eventSelectionTauDown  = createSystematics(process,process.selectionSequence,'TauDown',1.0,1.0,0.97,0,1.0)

from UWAnalysis.Configuration.tools.ntupleTools import addEleTauEventTree

addEleTauEventTree(process,'eleTauEventTree')
addEleTauEventTree(process,'eleTauEventTreeFinal','eleTausOS','osDiElectrons')
addEleTauEventTree(process,'eleTauEventTreeTauUp','eleTausSortedTauUp','osDiElectronsTauUp','eleTracksSortedTauUp','eleGSFTracksSortedTauUp')
addEleTauEventTree(process,'eleTauEventTreeTauDown','eleTausSortedTauDown','osDiElectronsTauDown','eleTracksSortedTauDown','eleGSFTracksSortedTauDown')


addEventSummary(process)











