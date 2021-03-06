import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_52_V8::All'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(2000)
        )

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
#            'file:/hdfs/store/user/iross/DoubleMu/data_DoubleMu_Run2012B_PromptReco_v1_a_2012-06-08-8TeV-PatTuple-data-4495432/c7a1c2223886075833473549ad1960ce/output_86_1_JSc.root'
#            'file:/hdfs/store/user/iross/DoubleElectron/data_DoubleElectron_Run2012B_PromptReco_v1_a_2012-06-08-8TeV-PatTuple-data-4495432/c7a1c2223886075833473549ad1960ce/output_8_2_736.root'
#            'file:/hdfs/store/user/tapas/2012-07-18-8TeV-PatTuple/data_DoubleMu_Run2012A_PromptReco_v1_Run190456_193683/1/patTuple_cfg-DAF9D1BD-8F97-E111-A628-BCAEC5329709.root'
#            'file:/hdfs/store/user/tapas/2012-07-25-8TeV-PatTuple/data_DoubleElectron_Run2012A_PromptReco_v1_Run190456_193683/1/patTuple_cfg-00CDF016-F499-E111-8EB7-001D09F290BF.root'
'file:/scratch/iross/seriosly.root',
'file:/scratch/iross/seriosly_2.root',
#'file:/scratch/iross/muEG2012EventFSR.root'
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
        EAtarget="2012Data" # Available targets: Fal11MC, Summer11MC, 2011Data, 2012Data
        )

#EventSelection
process.load("UWAnalysis.Configuration.zzLLLL_2012_loose_cff")
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMEEonly = cms.Path(process.MMEEonlyselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)
process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
process.eventSelectionMMM = cms.Path(process.MMMSeq)
process.eventSelectionMME = cms.Path(process.MMESeq)
process.eventSelectionEEM = cms.Path(process.EEMSeq)
process.eventSelectionEEE = cms.Path(process.EEESeq)
process.eventSelectionMM = cms.Path(process.ZMMSeq)
process.eventSelectionEE = cms.Path(process.ZEESeq)
#process.eventSelectionEEES = cms.Path(process.EEESselectionSequence)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeFinal','MMEEZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeFinal','MMMMZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTreeFinal','MMEEonlyZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTree','MMEEonlyzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinal','EEEEZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuEventTree
addMuMuMuEventTree(process,'muMuMuEventTree','triMMMthirdMuID',leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEventTree
addMuMuEleEventTree(process,'muMuEleEventTree','triMMEthirdEleID',leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuEventTree
addEleEleMuEventTree(process,'eleEleMuEventTree','triEEMthirdMuID',leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEventTree
addEleEleEleEventTree(process,'eleEleEleEventTree','triEEEthirdEleID',leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEventTree
addEleEleEventTree(process,'eleEleEventTree','ZEEFinal',leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEventTree
addMuMuEventTree(process,'muMuEventTree','ZMMFinal',leadingOnly=False)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleSCEventTree
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTree','EEESzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinal','EEESFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinalTest','EEESFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)

#Add event counter
addEventSummary(process,True,'MMEE','eventSelectionMMEE')
addEventSummary(process,True,'EEEE','eventSelectionEEEE')
addEventSummary(process,True,'EEMM','eventSelectionEEMM')
addEventSummary(process,True,'MMMM','eventSelectionMMMM')
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
#addEventSummary(process,False,'EEES','eventSelectionEEES')
