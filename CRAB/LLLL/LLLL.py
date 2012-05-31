import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_311_V2::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'/store/data/Run2011A/DoubleMu/AOD/PromptReco-v4/000/167/098/7211E94D-7D9A-E011-A713-003048F1BF66.root'
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',
                      [
									"HLT_DoubleMu7",
									"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL",
									"HLT_Mu13_Mu8",
									"HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"

                      ])

#EventSelection
process.load("UWAnalysis.Configuration.zzLLLLAnalysis_cff")
process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence) ##changing to multiples see below
process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)


from UWAnalysis.Configuration.tools.ntupleTools import addMuMuTauTauEventTree
addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold')
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID')
from UWAnalysis.Configuration.tools.ntupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold')
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID')
from UWAnalysis.Configuration.tools.ntupleTools import addMuMuEleTauEventTree
addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold')
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID')
from UWAnalysis.Configuration.tools.ntupleTools import addMuMuEleMuEventTree
addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold')
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId')
from UWAnalysis.Configuration.tools.ntupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCandsAboveThreshold')
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeID','MMEEzzEleId')
from UWAnalysis.Configuration.tools.ntupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCandsAboveThreshold')
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeID','MMMMzzMuIDSecondPair')
from UWAnalysis.Configuration.tools.ntupleTools import addEleEleTauTauEventTree
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID')
from UWAnalysis.Configuration.tools.ntupleTools import addEleEleEleTauEventTree
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID')
from UWAnalysis.Configuration.tools.ntupleTools import addEleEleMuTauEventTree
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID')
from UWAnalysis.Configuration.tools.ntupleTools import addEleEleEleMuEventTree
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID')
from UWAnalysis.Configuration.tools.ntupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCandsAboveThreshold')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeID','EEEEzzEleIDsecond')
from UWAnalysis.Configuration.tools.ntupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCandsAboveThreshold')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeID','EEMMzzMuIDSecondPair')

#Add event counter
addEventSummary(process,False,'MMMT','eventSelectionMMMT')
addEventSummary(process,False,'MMTT','eventSelectionMMTT')
addEventSummary(process,False,'MMET','eventSelectionMMET')
addEventSummary(process,False,'MMEM','eventSelectionMMEM')
addEventSummary(process,False,'MMEE','eventSelectionMMEE')
addEventSummary(process,False,'MMMM','eventSelectionMMMM')
addEventSummary(process,False,'EEMT','eventSelectionEEMT')
addEventSummary(process,False,'EEET','eventSelectionEEET')
addEventSummary(process,False,'EETT','eventSelectionEETT')
addEventSummary(process,False,'EEEM','eventSelectionEEEM')
addEventSummary(process,False,'EEEE','eventSelectionEEEE')
addEventSummary(process,False,'EEMM','eventSelectionEEMM')
