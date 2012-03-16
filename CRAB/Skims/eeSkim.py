import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("SKIM")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#		'file:pickevents.root'
	'file:e140063742.root'
#		'/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/178/866/867CDBF8-B4FA-E011-A5FF-001D09F28F25.root'
#		'/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/180/252/CED88138-4305-E111-BE64-003048CF99BA.root'
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionSKIM(process)


#OK the strategy will be that we apply first thresholds
#If those pass we run PAT and do tighter selection

process.electrons10 = cms.EDFilter("GsfElectronSelector",
                                 src = cms.InputTag("gsfElectrons"),
                                 cut = cms.string('pt>10&&abs(eta)<2.5'),
                                 filter = cms.bool(True)  
                             )

process.idedElectrons = cms.EDFilter("PATElectronSelector",
                                           src = cms.InputTag("convRejElectrons"),
#                                           cut = cms.string('gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(electronID("cicTight")==1||electronID("cicTight")==3||electronID("cicTight")==5||electronID("cicTight")==7||electronID("cicTight")==9||electronID("cicTight")==11||electronID("cicTight")==13||electronID("cicTight")==15)'),
                                           cut = cms.string('pt>10'),
                                           filter = cms.bool(True)
)                                           
process.isolatedElectrons = cms.EDFilter("PATElectronSelector",
                                           src = cms.InputTag("idedElectrons"),
#                                           src = cms.InputTag("patElectrons"),
#                                           cut = cms.string('(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt<0.5'),
                                           cut = cms.string('(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt<0.50'),
                                           filter = cms.bool(True)
)                                           

process.dimuons = cms.EDProducer("CandViewShallowCloneCombiner",
    checkCharge = cms.bool(False),
    cut = cms.string('mass > 40'),
    decay = cms.string('isolatedElectrons@+ isolatedElectrons@-')
)
process.dimuonsFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("dimuons"),
    minNumber = cms.uint32(1)
)
process.skimEE = cms.Path(
		process.electrons10*
		process.recoPAT*
		process.idedElectrons*
		process.isolatedElectrons*
		process.dimuons*
		process.dimuonsFilter
		)

process.out = cms.OutputModule("PoolOutputModule",
		fileName = cms.untracked.string('skim.root'),
                                   outputCommands = cms.untracked.vstring('keep *_*_*_*',
                                                                          'drop *_*_*_SKIM'),
                                   SelectEvents = cms.untracked.PSet(
                                      SelectEvents=cms.vstring("skimEE")
                                   )
                                  )

process.e = cms.EndPath(process.out)


process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
    )

