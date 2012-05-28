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
process.load("UWAnalysis.Configuration.zMuMuPrediction_NON_DY_cff")

process.zMuTau = cms.Path(
    process.startupSequence*
    process.skimHLT*
    process.produceAndDiscriminateHPSPFTaus*
    process.producePrePat*
    process.patDefaultSequence*
    process.producePostPat*
    process.selectZToMuTau

)

#Event Summary
from UWAnalysis.RecoTools.tools.EventSummaryMaker import *
evSummary = EventSummaryMaker(process.zMuTau)
process.ntuple.Filters = evSummary.getCounters(process)

process.analysis = cms.Path(process.analyzeZToMuTau)
process.schedule = cms.Schedule(process.zMuTau,process.analysis)


process.ntuple.fileName = cms.string("$outputFileName")


from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *


#use HPS
from PhysicsTools.PatAlgos.tools.tauTools import *
switchToPFTauHPS(process,process.patTaus)


#remove MC matching
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process,['Muons','Taus'])

