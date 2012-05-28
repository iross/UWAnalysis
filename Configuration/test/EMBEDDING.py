import FWCore.ParameterSet.Config as cms

process = cms.Process("EMBEDDING")

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.RandomNumberGeneratorService = cms.Service(
        "RandomNumberGeneratorService",
            saveFileName = cms.untracked.string(''),
            embeddedTaus = cms.PSet(
                 initialSeed = cms.untracked.uint32(987346),
                 engineName = cms.untracked.string('TRandom3')
            )
)



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

#Load startup counter
process.load("UWAnalysis.RecoTools.startUpSequence_cff")

#load the preAnalysis
process.load("UWAnalysis.Configuration.prePatProduction_cff")
#load minimal PAT
process.load("UWAnalysis.Configuration.muTauPAT_cfi")

#Load post PAT
process.load("UWAnalysis.Configuration.postPatProduction_cff")
#load Selection
process.load("UWAnalysis.Configuration.zMuMuEmbedding_cff")


process.initialCounter.name = cms.string('mumuInitialEvents')

process.zMuMuE = cms.Path(
    process.startupSequence*
    process.producePrePat*
    process.produceAndDiscriminateHPSPFTaus*
    process.patDefaultSequence*
    process.producePostPat*
    process.embedZMuMu
)

process.reMET = cms.EDProducer('METRecalculator',
                               



process.output = cms.OutputModule("PoolOutputModule",                                 
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('zMuMuE')
    ),
    outputCommands = cms.untracked.vstring(
      'drop *_*_*_*',
      'keep *_embeddedTaus*_*_*',
      'keep *_pfMet_*_*',
      'keep *_patMuons_*_*',
      'keep *_isolatedMuons_*_*',
      'keep *_zCands_*_*',
      'keep *_MEtoEDMConverter_*_*',
      'keep *_cleanTrackCandidates_*_*',
      'keep *_particleFlow_*_*'
            ),
    fileName = cms.untracked.string('$outputFileName')
)


process.e  =  cms.EndPath(process.output)
process.schedule = cms.Schedule(process.zMuMuE,process.e)



from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *


#use HPS
from PhysicsTools.PatAlgos.tools.tauTools import *
switchToPFTauHPS(process,process.patTaus)


#remove MC matching
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process,['Muons','Taus'])

