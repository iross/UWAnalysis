import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("SKIM")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/099/88FDF12C-D17F-E011-8317-003048F1C832.root',

        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionSKIM(process)


#OK the strategy will be that we apply first thresholds
#If those pass we run PAT and do tighter selection

process.electrons14 = cms.EDFilter("GsfElectronSelector",
                                 src = cms.InputTag("gsfElectrons"),
                                 cut = cms.string('pt>18&&abs(eta)<2.5&&((isEB()&&abs(deltaEtaSuperClusterTrackAtVtx())<0.007&&abs(deltaPhiSuperClusterTrackAtVtx())<0.15)||(isEE()&&abs(deltaEtaSuperClusterTrackAtVtx())<0.009&&abs(deltaPhiSuperClusterTrackAtVtx())<0.10))'),
                                 filter = cms.bool(True)  
                             )


process.electrons10 = cms.EDFilter("GsfElectronSelector",
                                 src = cms.InputTag("gsfElectrons"),
                                 cut = cms.string('pt>10&&abs(eta)<2.5&&((isEB()&&abs(deltaEtaSuperClusterTrackAtVtx())<0.007&&abs(deltaPhiSuperClusterTrackAtVtx())<0.15)||(isEE()&&abs(deltaEtaSuperClusterTrackAtVtx())<0.009&&abs(deltaPhiSuperClusterTrackAtVtx())<0.10))'),
                                 filter = cms.bool(True)  
                             )




process.muons14 = cms.EDFilter("MuonRefSelector",
                                 src = cms.InputTag("muons"),
                                 cut = cms.string('pt>14&&abs(eta)<2.1&&isGlobalMuon&&isTrackerMuon&&numberOfMatches()>=1'),
                                 filter = cms.bool(True)  
                             )

process.muons10 = cms.EDFilter("MuonRefSelector",
                                 src = cms.InputTag("muons"),
                                 cut = cms.string('pt>10&&abs(eta)<2.1&&isGlobalMuon&&isTrackerMuon&&numberOfMatches>=1'),
                                 filter = cms.bool(True)  
                             )


process.jet18 = cms.EDFilter("CandViewRefSelector",
                                 src = cms.InputTag("ak5PFJets"),
                                 cut = cms.string('pt>18&&abs(eta)<2.5'),
                                 filter = cms.bool(True) 
                             )

process.selectedTaus = cms.EDFilter("PATTauSelector",
                                           src = cms.InputTag("patTaus"),
                                           cut = cms.string('pt>18&&abs(eta)<2.3&&(tauID("byVLooseCombinedIsolationDeltaBetaCorr"))&&tauID("againstMuonLoose")&&tauID("againstElectronLoose")'),
                                           filter = cms.bool(True)
)                                           

process.isolatedElectrons = cms.EDFilter("PATElectronSelector",
                                           src = cms.InputTag("patElectrons"),
                                           cut = cms.string('(chargedHadronIso)/pt<0.2'),
                                           filter = cms.bool(True)
)                                           

process.isolatedMuons = cms.EDFilter("PATMuonSelector",
                                           src = cms.InputTag("patMuons"),
                                           cut = cms.string('chargedHadronIso/pt<0.2'),
                                           filter = cms.bool(True)
)                                           

                                                                                         

process.skimETau = cms.Path(process.electrons14*
                            process.jet18*
                            process.recoPAT*
                            process.selectedTaus*
                            process.isolatedElectrons
                            )

process.skimMuTau = cms.Path(process.muons14*
                            process.jet18*
                            process.recoPAT*
                            process.selectedTaus*
                            process.isolatedMuons
                            )

process.skimEMu = cms.Path(process.muons10*
                           process.electrons10
                            )



process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('skim.root'),
                                   outputCommands = cms.untracked.vstring('keep *_*_*_*',
                                                                          'drop *_*_*_SKIM'),
                                   SelectEvents = cms.untracked.PSet(
                                      SelectEvents=cms.vstring("skimETau","skimMuTau","skimEMu")
                                   )
                                  )

process.e = cms.EndPath(process.out)


process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)

    )











