import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_52_V8::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(3000)
)

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            'file:/hdfs/store/user/iross/DoubleMu/data_DoubleMu_Run2012B_PromptReco_v1_a_2012-05-29-8TeV-PatTuple-67c1f94/a7f10efca7dd683ad59c7e946715fa59/output_49_0_TNg.root',
            ),
        inputCommands=cms.untracked.vstring(
            'keep *',
            'drop *_finalState*_*_*',
            'drop *_patFinalStateEvent*_*_*'
            )
        )

process.load("PhysicsTools.PatAlgos.patSequences_cff")

from UWAnalysis.Configuration.tools.analysisTools import *
defaultAnalysisPath(process,'HLT',
                      [
                                    "HLT_DoubleMu3",
                                    "HLT_DoubleMu7",
                                    "HLT_Mu13_Mu8",
                                    "HLT_Mu17_Mu8",
                                    "HLT_Ele10_LW_LR1",
                                    "HLT_Ele15_SW_LR1",
                                    "HLT_Ele15_SW_CaloEleID_L1R",
                                    "HLT_Ele17_SW_TightEleID_L1R",
                                    "HLT_Ele17_SW_TighterEleIdIsol_L1R",
                                    "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL",
                                    "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"
                      ])

#EventSelection
process.load("UWAnalysis.Configuration.zzLLLL_2012BG_cff")
process.eventSelectionMMMTantiIso1 = cms.Path(process.MMMTantiIso1Seq)
process.eventSelectionMMMTnoIsoSS = cms.Path(process.MMMTnoIsoSSSeq)
process.eventSelectionMMMTantiIso2 = cms.Path(process.MMMTantiIso2Seq)
process.eventSelectionMMMTantiIsoBoth = cms.Path(process.MMMTantiIsoBothSeq)
process.eventSelectionMMTTantiIso1 = cms.Path(process.MMTTantiIso1Seq)
process.eventSelectionMMTTnoIsoSS = cms.Path(process.MMTTnoIsoSSSeq)
process.eventSelectionMMTTantiIso2 = cms.Path(process.MMTTantiIso2Seq)
process.eventSelectionMMTTantiIsoBoth = cms.Path(process.MMTTantiIsoBothSeq)
process.eventSelectionMMETantiIso1 = cms.Path(process.MMETantiIso1Seq)
process.eventSelectionMMETnoIsoSS = cms.Path(process.MMETnoIsoSSSeq)
process.eventSelectionMMETantiIso2 = cms.Path(process.MMETantiIso2Seq)
process.eventSelectionMMETantiIsoBoth = cms.Path(process.MMETantiIsoBothSeq)
process.eventSelectionMMEMantiIso1 = cms.Path(process.MMEMantiIso1Seq)
process.eventSelectionMMEMnoIsoSS = cms.Path(process.MMEMnoIsoSSSeq)
process.eventSelectionMMEMantiIso2 = cms.Path(process.MMEMantiIso2Seq)
process.eventSelectionMMEMantiIsoBoth = cms.Path(process.MMEMantiIsoBothSeq)
process.eventSelectionMMEEantiIso1 = cms.Path(process.MMEEantiIso1Seq)
process.eventSelectionMMEEnoIsoSS = cms.Path(process.MMEEnoIsoSSSeq)
process.eventSelectionMMEEantiIso2 = cms.Path(process.MMEEantiIso2Seq)
process.eventSelectionMMEEantiIsoBoth = cms.Path(process.MMEEantiIsoBothSeq)
process.eventSelectionMMMMantiIso1 = cms.Path(process.MMMMantiIso1Seq)
process.eventSelectionMMMMnoIsoSS = cms.Path(process.MMMMnoIsoSSSeq)
process.eventSelectionMMMMantiIso2 = cms.Path(process.MMMMantiIso2Seq)
process.eventSelectionMMMMantiIsoBoth = cms.Path(process.MMMMantiIsoBothSeq)
process.eventSelectionEEMTantiIso1 = cms.Path(process.EEMTantiIso1Seq)
process.eventSelectionEEMTnoIsoSS = cms.Path(process.EEMTnoIsoSSSeq)
process.eventSelectionEEMTantiIso2 = cms.Path(process.EEMTantiIso2Seq)
process.eventSelectionEEMTantiIsoBoth = cms.Path(process.EEMTantiIsoBothSeq)
process.eventSelectionEEETantiIso1 = cms.Path(process.EEETantiIso1Seq)
process.eventSelectionEEETnoIsoSS = cms.Path(process.EEETnoIsoSSSeq)
process.eventSelectionEEETantiIso2 = cms.Path(process.EEETantiIso2Seq)
process.eventSelectionEEETantiIsoBoth = cms.Path(process.EEETantiIsoBothSeq)
process.eventSelectionEETTantiIso1 = cms.Path(process.EETTantiIso1Seq)
process.eventSelectionEETTnoIsoSS = cms.Path(process.EETTnoIsoSSSeq)
process.eventSelectionEETTantiIso2 = cms.Path(process.EETTantiIso2Seq)
process.eventSelectionEETTantiIsoBoth = cms.Path(process.EETTantiIsoBothSeq)
process.eventSelectionEEEMantiIso1 = cms.Path(process.EEEMantiIso1Seq)
process.eventSelectionEEEMnoIsoSS = cms.Path(process.EEEMnoIsoSSSeq)
process.eventSelectionEEEMantiIso2 = cms.Path(process.EEEMantiIso2Seq)
process.eventSelectionEEEMantiIsoBoth = cms.Path(process.EEEMantiIsoBothSeq)
process.eventSelectionEEEEantiIso1 = cms.Path(process.EEEEantiIso1Seq)
process.eventSelectionEEEEnoIsoSS = cms.Path(process.EEEEnoIsoSSSeq)
process.eventSelectionEEEEantiIso2 = cms.Path(process.EEEEantiIso2Seq)
process.eventSelectionEEEEantiIsoBoth = cms.Path(process.EEEEantiIsoBothSeq)
process.eventSelectionEEMMantiIso1 = cms.Path(process.EEMMantiIso1Seq)
process.eventSelectionEEMMnoIsoSS = cms.Path(process.EEMMnoIsoSSSeq)
process.eventSelectionEEMMantiIso2 = cms.Path(process.EEMMantiIso2Seq)
process.eventSelectionEEMMantiIsoBoth = cms.Path(process.EEMMantiIsoBothSeq)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
process.eventSelectionMMM = cms.Path(process.MMMSeq)
process.eventSelectionMME = cms.Path(process.MMESeq)
process.eventSelectionEEM = cms.Path(process.EEMSeq)
process.eventSelectionEEE = cms.Path(process.EEESeq)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_noIsoOS','MMMTnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_noIsoSS','MMMTnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_noIsoSScheck','MMMTnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_antiIso','MMMTantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_antiIso1','MMMTantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_antiIso2','MMMTantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_noIsoOS','MMTTnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_noIsoSS','MMTTnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_noIsoSScheck','MMTTnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_antiIso','MMTTantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_antiIso1','MMTTantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_antiIso2','MMTTantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_noIsoOS','MMETnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_noIsoSS','MMETnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_noIsoSScheck','MMETnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_antiIso','MMETantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_antiIso1','MMETantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_antiIso2','MMETantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_noIsoOS','MMEMnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_noIsoSS','MMEMnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_noIsoSScheck','MMEMnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_antiIso','MMEMantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_antiIso1','MMEMantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_antiIso2','MMEMantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_noIsoOS','MMEEnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_noIsoSS','MMEEnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_noIsoSScheck','MMEEnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_antiIso','MMEEantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_antiIso1','MMEEantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_antiIso2','MMEEantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_noIsoOS','MMMMnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_noIsoSS','MMMMnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_noIsoSScheck','MMMMnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_antiIso','MMMMantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_antiIso1','MMMMantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_antiIso2','MMMMantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_noIsoOS','EEMTnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_noIsoSS','EEMTnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_noIsoSScheck','EEMTnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_antiIso','EEMTantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_antiIso1','EEMTantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_antiIso2','EEMTantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_noIsoOS','EEETnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_noIsoSS','EEETnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_noIsoSScheck','EEETnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_antiIso','EEETantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_antiIso1','EEETantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_antiIso2','EEETantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_noIsoOS','EETTnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_noIsoSS','EETTnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_noIsoSScheck','EETTnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_antiIso','EETTantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_antiIso1','EETTantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_antiIso2','EETTantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_noIsoOS','EEEMnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_noIsoSS','EEEMnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_noIsoSScheck','EEEMnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_antiIso','EEEMantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_antiIso1','EEEMantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_antiIso2','EEEMantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_noIsoOS','EEEEnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_noIsoSS','EEEEnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_noIsoSScheck','EEEEnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_antiIso','EEEEantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_antiIso1','EEEEantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_antiIso2','EEEEantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_noIsoOS','EEMMnoIsoOSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_noIsoSS','EEMMnoIsoSSF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_noIsoSScheck','EEMMnoIsoSScheckF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_antiIso','EEMMantiIsoBothF','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_antiIso1','EEMMantiIso1F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_antiIso2','EEMMantiIso2F','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMMMFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuEventTree
addMuMuMuEventTree(process,'muMuMuEventTree','triMMMthirdMuID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEventTree
addMuMuEleEventTree(process,'muMuEleEventTree','triMMEthirdEleID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuEventTree
addEleEleMuEventTree(process,'eleEleMuEventTree','triEEMthirdMuID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEventTree
addEleEleEleEventTree(process,'eleEleEleEventTree','triEEEthirdEleID')

#Add event counter
addEventSummary(process,False,'MMMT','eventSelectionMMMTnoIsoSS')
addEventSummary(process,False,'MMTT','eventSelectionMMTTnoIsoSS')
addEventSummary(process,False,'MMET','eventSelectionMMETnoIsoSS')
addEventSummary(process,False,'MMEM','eventSelectionMMEMnoIsoSS')
addEventSummary(process,False,'MMEE','eventSelectionMMEEnoIsoSS')
addEventSummary(process,False,'MMMM','eventSelectionMMMMnoIsoSS')
addEventSummary(process,False,'EETT','eventSelectionEETTnoIsoSS')
addEventSummary(process,False,'EEET','eventSelectionEEETnoIsoSS')
addEventSummary(process,False,'EEMT','eventSelectionEEMTnoIsoSS')
addEventSummary(process,False,'EEEM','eventSelectionEEEMnoIsoSS')
addEventSummary(process,False,'EEEE','eventSelectionEEEEnoIsoSS')
addEventSummary(process,False,'EEMM','eventSelectionEEMMnoIsoSS')
