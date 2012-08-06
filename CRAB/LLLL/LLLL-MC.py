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
            #'file:/hdfs/store/user/dbelknap/GluGluToHToZZTo4L_M-125_8TeV-powheg-pythia6/GGH_HZZ4L_M-125_2012-06-20-PatTuple-MC-b497351/4cb1f8ea0bfd28794ef77b00678681f4/output_101_2_67C.root'
            #'file:/hdfs/store/user/belknap/2012-08-01-PatTuple-MC/ZZJetsTo4L_pythia/1/patTuple_cfg-1CFB3C62-3B94-E111-AD52-008CFA008768.root'
            'file:/hdfs/store/user/iross/ZZTo4mu_8TeV-powheg-pythia6/ZZ4M_powheg_2012-07-24-PatTuple-ZZ-samples-4b2f7ef/6f82f02dd7e65e9c006918dbe04173e9/output_100_1_gLg.root'
            #'file:/hdfs/store/user/iross/DoubleMu/data_DoubleMu_Run2012B_PromptReco_v1_a_2012-05-29-8TeV-PatTuple-67c1f94/a7f10efca7dd683ad59c7e946715fa59/output_49_0_TNg.root',
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
process.load("UWAnalysis.Configuration.zzLLLL_2012_cff")
process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMEEonly = cms.Path(process.MMEEonlyselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
#process.eventSelectionEEES = cms.Path(process.EEESselectionSequence)
#process.eventSelectionESEE = cms.Path(process.ESEEselectionSequence)
#process.eventSelectionMMES = cms.Path(process.MMESselectionSequence)
#process.eventSelectionESMM = cms.Path(process.ESMMselectionSequence)
process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)
#process.eventSelectionMMM = cms.Path(process.MMMSeq)
#process.eventSelectionMME = cms.Path(process.MMESeq)
#process.eventSelectionEEM = cms.Path(process.EEMSeq)
#process.eventSelectionEEE = cms.Path(process.EEESeq)
#process.eventSelectionMM = cms.Path(process.ZMMSeq)
#process.eventSelectionEE = cms.Path(process.ZEESeq)
#process.eventSelectionEEES = cms.Path(process.EEESselectionSequence)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeFinal','MMEEFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeID','MMEEzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTree','MMEEonlyzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTreeFinal','MMEEonlyFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTreeID','MMEEonlyzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeID','MMMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedMuID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeFinal','MMMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinal','EEEEFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinalTest','EEEEFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinalTest','EEMMFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
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


#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeID','EEMMzzMuIDSecondPair','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')

#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleSCEleEleEventTree
#addEleSCEleEleEventTree(process,'eleSCEleEleEventTree','ESEEzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleSCEleEleEventTree(process,'eleSCEleEleEventTreeFinal','ESEEFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleSCEleEleEventTree(process,'eleSCEleEleEventTreeFinalTest','ESEEFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleSCEventTree
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTree','EEESzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinal','EEESFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinalTest','EEESFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleSCEventTree
#addMuMuEleSCEventTree(process,'muMuEleSCEventTree','MMESzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addMuMuEleSCEventTree(process,'muMuEleSCEventTreeFinal','MMESFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addMuMuEleSCEventTree(process,'muMuEleSCEventTreeFinalTest','MMESFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleSCMuMuEventTree
#addEleSCMuMuEventTree(process,'eleSCMuMuEventTree','ESMMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleSCMuMuEventTree(process,'eleSCMuMuEventTreeFinal','ESMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleSCMuMuEventTree(process,'eleSCMuMuEventTreeFinalTest','ESMMFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#
## Store all Gen Level particles. For H -> ZZ or ZZ only.
#process.genlevel = cms.EDAnalyzer("GenLevelFiller", gensrc = cms.InputTag("genParticles"))
#process.genParticles = cms.Path( process.genlevel )


#Add event counter
addEventSummary(process,True,'MMMT','eventSelectionMMMT')
addEventSummary(process,True,'MMTT','eventSelectionMMTT')
addEventSummary(process,True,'MMET','eventSelectionMMET')
addEventSummary(process,True,'MMEM','eventSelectionMMEM')
addEventSummary(process,True,'MMEE','eventSelectionMMEE')
addEventSummary(process,True,'MMMM','eventSelectionMMMM')
addEventSummary(process,True,'EEMT','eventSelectionEEMT')
addEventSummary(process,True,'EEET','eventSelectionEEET')
addEventSummary(process,True,'EETT','eventSelectionEETT')
addEventSummary(process,True,'EEEM','eventSelectionEEEM')
addEventSummary(process,True,'EEEE','eventSelectionEEEE')
addEventSummary(process,True,'EEMM','eventSelectionEEMM')
#addEventSummary(process,True,'EEES','eventSelectionEEES')
#addEventSummary(process,True,'ESEE','eventSelectionESEE')
#addEventSummary(process,True,'MMES','eventSelectionMMES')
#addEventSummary(process,True,'ESMM','eventSelectionESMM')
#addEventSummary(process,True,'MM','eventSelectionEE')
#addEventSummary(process,True,'EE','eventSelectionMM')
#addEventSummary(process,False,'EEES','eventSelectionEEES')
