import FWCore.ParameterSet.Config as cms

process = cms.Process("TAU")

#Load Vertex Tools since we like and use them
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
############################

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("PhysicsTools.PatAlgos.patSequences_cff")


process.GlobalTag.globaltag = 'MC_3XY_V26::All'


process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )

process.source = cms.Source("PoolSource",
                 fileNames = cms.untracked.vstring(
                       $inputFileNames
                  )
)




#Load The Analysis sequences
process.load("UWAnalysis.RecoTools.tauRecoAnalysis_cfi")
process.load("RecoTauTag.Configuration.HPSPFTaus_cfi") 

process.p= cms.Path(
    process.tauGenJets+
    process.produceAndDiscriminateHPSPFTaus+
    process.TauEfficiency
)

process.tauAnalysis.FileName = cms.string('$outputFileName')
process.tauAnalysisMu.FileName = cms.string('MU-$outputFileName')
process.tauAnalysisEle.FileName = cms.string('ELE-$outputFileName')
process.standardTauAnalysis.FileName = cms.string('STD-$outputFileName')


#START OF SCHEDULE DEFINITION
process.schedule = cms.Schedule(
                 process.p
             )
             
#END OF SCHEDULE DEFINITION






