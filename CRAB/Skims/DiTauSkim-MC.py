import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("SKIM")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'/store/mc/Fall11/VBF_HToTauTau_M-160_7TeV-powheg-pythia6-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/00EB5690-D3F9-E011-A63D-20CF305B04DA.root' 
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


#Counter
process.counter  = cms.EDProducer("EventCounter",
                          name=cms.string("processedEvents"),
)                          

process.countPath = cms.Path(process.counter)



process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('skim.root'),
                                   outputCommands = cms.untracked.vstring('keep *_*_*_*',
                                                                          'drop *_*_*_SKIM',
                                                                          'keep *_MEtoEDMConverter*_*_SKIM'),
                                   SelectEvents = cms.untracked.PSet(
                                      SelectEvents=cms.vstring("skimETau","skimMuTau","skimEMu")
                                   )
                                  )


process.MEtoEDMConverter = cms.EDProducer("MEtoEDMConverter",
                                          Name = cms.untracked.string('MEtoEDMConverter'),
                                          Verbosity = cms.untracked.int32(0), # 0 provides no output
                                          # 1 provides basic output
                                          # 2 provide more detailed output
                                          Frequency = cms.untracked.int32(50),
                                          MEPathToSave = cms.untracked.string(''),
                                          deleteAfterCopy = cms.untracked.bool(True)
)



process.e = cms.EndPath(process.MEtoEDMConverter*process.out)


process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)

    )











