import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START311_V1::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/mc/Fall10/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/AODSIM/START38_V12-v1/0005/A01A0BAA-17C9-DF11-A121-00215E222772.root',
        '/store/mc/Fall10/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/AODSIM/START38_V12-v1/0004/FE6120D3-7AC8-DF11-A1D3-00215E21DE7C.root',
        )
)






process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'REDIGI38XPU')


#mu enriched fake rate 

process.load("UWAnalysis.Configuration.tauFakeRate_muEnriched_cff")
process.muEnrichedFakeRate = cms.Path(process.muEnrichedSequence)
#w jets fake rate 
process.load("UWAnalysis.Configuration.tauFakeRate_wJets_cff")
process.wJetsFakeRate = cms.Path(process.wJetsSequence)
#z jets fake rate 
process.load("UWAnalysis.Configuration.tauFakeRate_zJets_cff")
process.zJetsFakeRate = cms.Path(process.zJetsSequence)

addTauIDPlotter(process,'MuEnriched','patTaus','muEnrichedJetsForFakeRate',['leadingTrackFinding','byVLooseIsolation','byLooseIsolation','byMediumIsolation','byTightIsolation'])
addTauIDPlotter(process,'wJets','patTaus','wJetsForFakeRate',['leadingTrackFinding','byVLooseIsolation','byLooseIsolation','byMediumIsolation','byTightIsolation'])
addTauIDPlotter(process,'zJets','patTaus','zJetsForFakeRate',['leadingTrackFinding','byVLooseIsolation','byLooseIsolation','byMediumIsolation','byTightIsolation'])


#MC efficiency
process.generatedTaus = cms.EDFilter("TauGenJetDecayModeSelector",
    src = cms.InputTag("tauGenJets"),
    select = cms.vstring('oneProng0Pi0', 'oneProng1Pi0', 'oneProng2Pi0', 'oneProngOther','threeProng0Pi0', 'threeProng1Pi0', 'threeProngOther', 'rare'),
    filter = cms.bool(False)
)
process.generatedTausInAcceptance = cms.EDFilter("GenJetSelector",
    src = cms.InputTag("generatedTaus"),
    cut = cms.string('pt > 5.&&abs(eta)<2.4'),
    filter = cms.bool(False)
)


#MC fake rate
process.generatedJetsInAcceptance = cms.EDFilter("GenJetSelector",
    src = cms.InputTag("ak5GenJets"),
    cut = cms.string('pt > 5.&&abs(eta)<2.4'),
    filter = cms.bool(False)
)



process.gen = cms.Path(process.generatedTaus+process.generatedTausInAcceptance+process.generatedJetsInAcceptance)

hpsDiscriminators = ['leadingTrackFinding','byVLooseIsolation','byLooseIsolation','byMediumIsolation','byTightIsolation']


addTauIDPlotter(process,'MCeff','patTaus','generatedTausInAcceptance',hpsDiscriminators,0.0,0.0)
addTauIDPlotter(process,'MCeffthr15','patTaus','generatedTausInAcceptance',hpsDiscriminators,15.0,0.0)
addTauIDPlotter(process,'MCeffthrV20','patTaus','generatedTausInAcceptance',hpsDiscriminators,20.0,20.0)
addTauIDPlotter(process,'MCfakethr15','patTaus','generatedJetsInAcceptance',hpsDiscriminators,15.,0.)
addTauIDPlotter(process,'MCfakethr20','patTaus','generatedJetsInAcceptance',hpsDiscriminators,20.,0.)

#addTauIDPlotter(process,'MCeffEleVeto','patTaus','generatedJetsInAcceptance',hpsDiscriminators,20.,0.)
#addTauIDPlotter(process,'MCeffMuVeto','patTaus','generatedJetsInAcceptance',hpsDiscriminators,20.,0.)

#addTauTree(process,'tau')









