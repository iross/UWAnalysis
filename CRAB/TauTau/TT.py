import FWCore.ParameterSet.Config as cms
import sys



process = cms.Process("ANALYSIS")




process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/099/88FDF12C-D17F-E011-8317-003048F1C832.root',
        '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/098/DCA6F527-DA7F-E011-BFD8-003048F117B4.root',
        '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/093/5811266A-C27F-E011-A7DC-0030487A1990.root',
        '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/088/FA043C42-E47F-E011-85B8-003048F118E0.root',
        '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/071/7450CA91-C37F-E011-8B41-001617DBD472.root',
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *

defaultReconstruction(process,'HLT',[
'HLT_DoubleIsoPFTau20_Trk5',
'HLT_DoubleIsoPFTau35_Trk5_eta2p1',
'HLT_IsoPFTau40_IsoPFTau30_Trk5_eta2p1'
'HLT_DoubleIsoPFTau40_Trk5_eta2p1'
    ])


#EventSelection
process.load("UWAnalysis.Configuration.zTauTauAnalysis_cff")

process.metCalibration.applyCalibration = cms.bool(False)


process.eventSelection = cms.Path(process.selectionSequence) ##changing to multiples see below


#Systematic Shifts 1sigma
#process.eventSelectionMuUp    = createSystematics(process,process.selectionSequence,'MuUp',1.01,1.0,1.0,1.0,1.0)
#process.eventSelectionMuDown  = createSystematics(process,process.selectionSequence,'MuDown',0.99,1.0,1.0,1.0,1.0)

#Add event counter
addEventSummary(process)

#ntupleization

from UWAnalysis.Configuration.tools.ntupleTools import addTauTauEventTree 

addTauTauEventTree(process,'diTauEventTree')












