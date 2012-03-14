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
		'/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/179/889/EE2FFC4D-2A03-E111-B07B-BCAEC54DB5D4.root'
		)
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionSKIM(process)


#OK the strategy will be that we apply first thresholds
#If those pass we run PAT and do tighter selection

process.muons10 = cms.EDFilter("MuonRefSelector",
                                 src = cms.InputTag("muons"),
                                 cut = cms.string('pt>10&&abs(eta)<2.4&&isGlobalMuon&&isTrackerMuon'),
                                 filter = cms.bool(True)  
                             )

process.isolatedMuons = cms.EDFilter("PATMuonSelector",
                                           src = cms.InputTag("patMuons"),
                                           cut = cms.string('(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt<0.35'),
                                           filter = cms.bool(True)
)                                           

process.dimuons = cms.EDProducer("CandViewShallowCloneCombiner",
    checkCharge = cms.bool(False),
    cut = cms.string('mass > 40'),
    decay = cms.string('isolatedMuons@+ isolatedMuons@-')
)
process.dimuonsFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("dimuons"),
    minNumber = cms.uint32(1)
)
process.skimMM = cms.Path(process.muons10*
						process.recoPAT*
						process.isolatedMuons*
						process.dimuons*
						process.dimuonsFilter
                            )



process.out = cms.OutputModule("PoolOutputModule",
                                   fileName = cms.untracked.string('skim.root'),
                                   outputCommands = cms.untracked.vstring('keep *_*_*_*',
                                                                          'drop *_*_*_SKIM'),
                                   SelectEvents = cms.untracked.PSet(
                                      SelectEvents=cms.vstring("skimMM")
                                   )
                                  )

process.e = cms.EndPath(process.out)


process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)

    )











