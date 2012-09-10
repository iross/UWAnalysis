import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START52_V9::All'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
'file:/scratch/iross/sync4l_wFSR.root'
#'file:/hdfs/store/user/tapas/2012-07-24-8Tev-PatTuple/Zjets_M50/1/patTuple_cfg-04542532-9A9B-E111-95D3-0025B31E3D3C.root'
#'file:/hdfs/store/user/iross/ZZTo4mu_8TeV-powheg-pythia6/ZZ4M_powheg_2012-07-24-PatTuple-ZZ-samples-4b2f7ef/6f82f02dd7e65e9c006918dbe04173e9/output_98_1_Crv.root'
#'file:/scratch/iross/testwFSR_2.root',
#'file:/scratch/iross/zz4l_sync_summer12_vetoChargedOnlyEndcap.root'
#		'file:/scratch/iross/zz4l_sync_summer12_EEveto.root',
#			'file:/scratch/iross/zz4l_sync_fall11_take2.root'
#            'file:/scratch/iross/zz4l_sync_2.root'
            #		'file:eemm_ZZ4Lfall_50evts.root'
            ),
        inputCommands=cms.untracked.vstring(
            'keep *',
            'drop *_finalState*_*_*',
            'drop *_patFinalStateEvent*_*_*'
            )
        )

from UWAnalysis.Configuration.tools.analysisTools import *
defaultAnalysisPath(process,'HLT',
        [
            "HLT_Mu17_Mu8",
            "HLT_Mu17_TkMu8",
            "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL",
            "HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL",
            "HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"
            ],
        EAtarget = "2012Data" # Available targets: Fal11MC, Summer11MC, 2011Data, 2012Data
        )

#createGeneratedParticlesPATtuple(process,
#        'genDaughters',
#        [
#            "keep++ pdgId = 25",
#            "drop pdgId = {tau+}",
#            "drop pdgId = {tau-}",
#            "keep pdgId = {mu+}",
#            "keep pdgId = {mu-}",
#            "keep pdgId = 11",
#            "keep pdgId = -11"
#            ]
#        )

#EventSelection
process.load("UWAnalysis.Configuration.zh_cff")
process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
process.eventSelectionMM = cms.Path(process.ZMMSeq)
process.eventSelectionEE = cms.Path(process.ZEESeq)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)

from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEventTree
addEleEleEventTree(process,'eleEleEventTree','ZEEFinal',leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEventTree
addMuMuEventTree(process,'muMuEventTree','ZMMFinal',leadingOnly=True)

# Store all Gen Level particles. For H -> ZZ or ZZ only.
#process.genlevel = cms.EDAnalyzer("GenLevelFiller", gensrc = cms.InputTag("genParticles"))
#process.genParticles = cms.Path( process.genlevel )

#Add event counter
addEventSummary(process,True,'MMMT','eventSelectionMMMT')
addEventSummary(process,True,'MMTT','eventSelectionMMTT')
addEventSummary(process,True,'MMET','eventSelectionMMET')
addEventSummary(process,True,'MMEM','eventSelectionMMEM')
addEventSummary(process,True,'EEMT','eventSelectionEEMT')
addEventSummary(process,True,'EEET','eventSelectionEEET')
addEventSummary(process,True,'EETT','eventSelectionEETT')
addEventSummary(process,True,'EEEM','eventSelectionEEEM')
addEventSummary(process,True,'MM','eventSelectionEE')
addEventSummary(process,True,'EE','eventSelectionMM')
