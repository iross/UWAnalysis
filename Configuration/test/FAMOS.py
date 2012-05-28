import FWCore.ParameterSet.Config as cms

process = cms.Process("FAMOS")

# Number of events to be generated
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                 fileNames = cms.untracked.vstring(
                           $inputFileNames
                       )
)

# Include the RandomNumberGeneratorService definition
process.load("FastSimulation.Configuration.RandomServiceInitialization_cff")

# Famos sequences (NO HLT)
process.load("FastSimulation.Configuration.CommonInputs_cff")
process.load("FastSimulation.Configuration.FamosSequences_cff")

# Parametrized magnetic field (new mapping, 4.0 and 3.8T)
#process.load("Configuration.StandardSequences.MagneticField_40T_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.VolumeBasedMagneticFieldESProducer.useParametrizedTrackerField = True

# If you want to turn on/off pile-up
process.famosPileUp.PileUpSimulator.averageNumber = 5.0
# You may not want to simulate everything for your study
process.famosSimHits.SimulateCalorimetry = True
process.famosSimHits.SimulateTracking = True

# Get frontier conditions    - not applied in the HCAL, see below
# Values for globaltag are "STARTUP31X_V2::All","MC_3XY_V26::All"
process.GlobalTag.globaltag = "MC_3XY_V26::All"

# Apply ECAL miscalibration
process.ecalRecHit.doMiscalib = True
process.hbhereco.doMiscalib = True
process.horeco.doMiscalib = True
process.hfreco.doMiscalib = True

# Apply Tracker misalignment
process.famosSimHits.ApplyAlignment = True
process.misalignedTrackerGeometry.applyAlignment = True
process.misalignedDTGeometry.applyAlignment = True
process.misalignedCSCGeometry.applyAlignment = True

#  Attention ! for the HCAL IDEAL==STARTUP
#process.caloRecHits.RecHitsFactory.HCAL.Refactor = 1.0
#process.caloRecHits.RecHitsFactory.HCAL.Refactor_mean = 1.0
#process.caloRecHits.RecHitsFactory.HCAL.fileNameHcal = "hcalmiscalib_0.0.xml"


process.genParticleCandidates.src = cms.InputTag("embeddedTaus")
process.genParticles.src = cms.InputTag("embeddedTaus")
process.famosSimHits.SourceLabel = cms.InputTag("embeddedTaus")

# Famos with everything !
process.p1 = cms.Path(process.famosWithEverything)

# To write out events
process.load("FastSimulation.Configuration.EventContent_cff")
process.o1 = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('$outputFileName')
)
process.outpath = cms.EndPath(process.o1)

# Make the job crash in case of missing product
process.options = cms.untracked.PSet( Rethrow = cms.untracked.vstring('ProductNotFound') )

print process.dumpPython()
