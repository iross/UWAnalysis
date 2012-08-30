import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START52_V9::All'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(500)
        )

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
#'file:/scratch/iross/zz4l_sync_summer12.root'
#'file:/scratch/iross/testwFSR_2.root',
'file:/hdfs/store/user/iross/SMHiggsToZZTo4L_M-125_8TeV-jhu-pythia6/H125_JHU_2012-07-16-PatTuple-1f0f3f6/bc6b6dd8d7fa684bedbf49c29900433d/output_17_1_FY7.root'
#'file:/hdfs/store/user/iross/ZZTo4mu_8TeV-powheg-pythia6/ZZ4M_powheg_2012-06-08-8TeV-PatTuple-4495432/0651de2bb07022ffcd3866fd2307fdf9/output_94_1_CC6.root',
#'file:/hdfs/store/user/iross/ZZTo4mu_8TeV-powheg-pythia6/ZZ4M_powheg_2012-06-08-8TeV-PatTuple-4495432/0651de2bb07022ffcd3866fd2307fdf9/output_64_1_uXI.root'
#'file:/hdfs/store/user/iross/ZZTo4e_8TeV-powheg-pythia6/ZZ4E_powheg_2012-06-08-8TeV-PatTuple-4495432/0651de2bb07022ffcd3866fd2307fdf9/output_8_1_hZH.root',
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
            #								"HLT_DoubleMu3",
            #								"HLT_DoubleMu7",
            "HLT_Mu13_Mu8",
            "HLT_Mu17_Mu8",
            #								"HLT_Ele10_LW_LR1",
            #								"HLT_Ele15_SW_LR1",
            #								"HLT_Ele15_SW_CaloEleID_L1R",
            #								"HLT_Ele17_SW_TightEleID_L1R",
            #								"HLT_Ele17_SW_TighterEleIdIsol_L1R",
            #								"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL",
            "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"
            ]
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
process.load("UWAnalysis.Configuration.zzLLLL_2012_loose_cff")
#process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
#process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
#process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
#process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
#process.eventSelectionMMEEonly = cms.Path(process.MMEEonlyselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
#process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
#process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
#process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
#process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
#process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)
#process.eventSelectionMMM = cms.Path(process.MMMSeq)
#process.eventSelectionMME = cms.Path(process.MMESeq)
#process.eventSelectionEEM = cms.Path(process.EEMSeq)
#process.eventSelectionEEE = cms.Path(process.EEESeq)
#process.eventSelectionMM = cms.Path(process.ZMMSeq)
#process.eventSelectionEE = cms.Path(process.ZEESeq)
#process.eventSelectionEEES = cms.Path(process.EEESselectionSequence)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
#addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
#addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
#addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
#addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeFinal','MMEEFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeID','MMEEzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
#addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTree','MMEEonlyzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTreeFinal','MMEEonlyFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTreeID','MMEEonlyzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeID','MMMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedMuID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeFinal','MMMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)

from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinal','EEEEFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinalTest','EEEEFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinalTest','EEMMFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuEventTree
#addMuMuMuEventTree(process,'muMuMuEventTree','triMMMthirdMuID',leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEventTree
#addMuMuEleEventTree(process,'muMuEleEventTree','triMMEthirdEleID',leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuEventTree
#addEleEleMuEventTree(process,'eleEleMuEventTree','triEEMthirdMuID',leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEventTree
#addEleEleEleEventTree(process,'eleEleEleEventTree','triEEEthirdEleID',leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEventTree
#addEleEleEventTree(process,'eleEleEventTree','ZEEFinal',leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEventTree
#addMuMuEventTree(process,'muMuEventTree','ZMMFinal',leadingOnly=False)


#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleSCEventTree
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTree','EEESzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinal','EEESFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinalTest','EEESFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addGenLevel
#addGenLevel(process,'GenLevelCandidates','genParticles',MC=True,leadingOnly=False)

#process.genlevel = cms.EDAnalyzer("GenLevelFiller", gensrc = cms.InputTag("genParticles"))
#process.genParticles = cms.Path( process.genlevel )


#Add event counter
#addEventSummary(process,True,'MMMT','eventSelectionMMMT')
#addEventSummary(process,True,'MMTT','eventSelectionMMTT')
#addEventSummary(process,True,'MMET','eventSelectionMMET')
#addEventSummary(process,True,'MMEM','eventSelectionMMEM')
addEventSummary(process,True,'MMEE','eventSelectionMMEE')
addEventSummary(process,True,'MMMM','eventSelectionMMMM')
#addEventSummary(process,True,'EEMT','eventSelectionEEMT')
#addEventSummary(process,True,'EEET','eventSelectionEEET')
#addEventSummary(process,True,'EETT','eventSelectionEETT')
#addEventSummary(process,True,'EEEM','eventSelectionEEEM')
addEventSummary(process,True,'EEEE','eventSelectionEEEE')
#addEventSummary(process,True,'EEMM','eventSelectionEEMM')
#addEventSummary(process,True,'MM','eventSelectionEE')
#addEventSummary(process,True,'EE','eventSelectionMM')
#addEventSummary(process,False,'EEES','eventSelectionEEES')
