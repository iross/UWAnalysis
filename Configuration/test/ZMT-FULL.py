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

# run the 3.3.x software on Summer 09 MC from 3.1.x:
#   - change the name from "ak" (3.3.x) to "antikt) (3.1.x)
#   - run jet ID (not run in 3.1.x)


#go to anti-kt jets
#from PhysicsTools.PatAlgos.tools.jetTools import *

#switchJetCollection(process,
#                    jetCollection = cms.InputTag('antikt5PFJets'),
#                    doJTA            = True,
#                    doBTagging       = True,
#                    jetCorrLabel     = None,
#                    doType1MET       = False,
#                    genJetCollection = cms.InputTag("antikt5GenJets")
#)

#use HPS
from PhysicsTools.PatAlgos.tools.tauTools import *
switchToPFTauHPS(process,process.patTaus)


#remove MC matching
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process,['Muons','Taus'])

