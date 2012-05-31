import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        $inputFileNames
    )
)

process.load('UWAnalysis.MCTools.ZLTPhaseSpaceAnalyzer_cfi')
process.mcAnalysis.FileName=cms.string("$outputFileName")

process.zMuTau = cms.Path(
process.mcAnalysis
)


