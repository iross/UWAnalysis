import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")


process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")



############################
# import particle data table
# needed for print-out of generator level information
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")


process.GlobalTag.globaltag = 'MC_3XY_V26::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    $inputFileNames
    )
)

#Load tau ID
process.load("RecoTauTag.Configuration.HPSPFTaus_cfi") 


#Load startup counter
process.load("UWAnalysis.Configuration.startUpSequence_cff")


process.load("UWAnalysis.Configuration.hlt_cff")


#load the preAnalysis
process.load("UWAnalysis.Configuration.prePatProduction_cff")
#load minimal PAT
process.load("UWAnalysis.Configuration.muTauPAT_cfi")

#Load post PAT
process.load("UWAnalysis.Configuration.postPatProduction_cff")
#load Selection
process.load("UWAnalysis.Configuration.zMuTauAnalysis_cff")



#MET corrections

process.patMETs.metSource = cms.InputTag("pfMet","","RECO")

#process.embeddedMuons = cms.EDProducer("MuonPairDaughterFetcher",
#                                       src = cms.InputTag("diMuonsOS")
#)                                       

process.reMET = cms.EDProducer("METRecalculator",
                               met =cms.InputTag("patMETs"),
                               originalObjects = cms.VInputTag(cms.InputTag("patMuons","","EMBEDDING")),
                               smearedObjects = cms.VInputTag(cms.InputTag("particleFlow"))
)                               

process.mumuPairs.srcLeg2 = cms.InputTag('cleanTrackCandidates')

#Change the di candidates to the new MET
process.diTaus.srcMET = cms.InputTag("reMET")


#ZMuMu Veto for the new candidates
process.mumuPairs2 = cms.EDProducer("DiCandidatePairProducer",
                            useLeadingTausOnly = cms.bool(False),
                            srcLeg1 = cms.InputTag('patMuons'),
                            srcLeg2 = cms.InputTag('trackCandidates'),
                            dRmin12 = cms.double(0.3),
                            srcMET = cms.InputTag('patMETs'),
                            srcGenParticles = cms.InputTag('genParticles'),
                            recoMode = cms.string(""),
                            verbosity = cms.untracked.int32(0)
                           ) 

process.mumuPairsOS2 = cms.EDFilter('DiCandidatePairSelector',
                               src = cms.InputTag("mumuPairs2"),
                               cut = cms.string('charge==0'),
                               filter = cms.bool(False)
)                               

process.zMuMuCands2 = cms.EDFilter('DiCandidatePairSelector',
                               src = cms.InputTag("mumuPairsOS2"),
                               cut = cms.string('mass>80&&mass<110'),
                               filter = cms.bool(False)
                           
)
process.zMuMuVeto2Filter  = cms.EDFilter("PATCandViewCountFilter",
               minNumber = cms.uint32(0),
               maxNumber = cms.uint32(0),
               src = cms.InputTag("zMuMuCands2")
)

process.zMuMu2Counter = cms.EDProducer('EventCounter',
                         name = cms.string("secondMuonVeto")
)

process.zMuMuVeto2 = cms.Sequence(process.mumuPairs2*process.mumuPairsOS2*process.zMuMuCands2*process.zMuMuVeto2Filter*process.zMuMu2Counter);




process.zMuTau = cms.Path(
    process.startupSequence*
    process.produceAndDiscriminateHPSPFTaus*
    process.producePrePat*
    process.patDefaultSequence*
    process.producePostPat*
#    process.embeddedMuons*
    process.reMET*
    process.zMuMuVeto2*
    process.selectZToMuTau
)

#Event Summary

from UWAnalysis.RecoTools.tools.EventSummaryMaker import *
evSummary = EventSummaryMaker(process.zMuTau)
process.ntuple.Filters = evSummary.getCounters(process)



process.analysis = cms.Path(process.analyzeZToMuTau)


process.schedule = cms.Schedule(process.zMuTau,process.analysis)



process.ntuple.fileName = cms.string("$outputFileName")





#use HPS
from PhysicsTools.PatAlgos.tools.tauTools import *
switchToPFTauHPS(process,process.patTaus)

