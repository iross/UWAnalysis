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



process.load("UWAnalysis.Configuration.prePatProduction_cff")
process.load("UWAnalysis.Configuration.muTauPAT_cfi")
process.load("UWAnalysis.Configuration.postPatProduction_cff")
process.load("UWAnalysis.RecoTools.muonTagAndProbe_cff")

process.zMuTau = cms.Path(
    process.producePrePat*
    process.patDefaultSequence*
    process.producePostPat*
    process.tagAndProbe
)



process.analysis.FileName = cms.string("$outputFileName")
