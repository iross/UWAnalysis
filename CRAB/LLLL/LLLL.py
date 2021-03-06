import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_P_V41_AN1::All'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(2000)
        )

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.categories.append('CalibrationChooser')
process.MessageLogger.cerr.CalibrationChooser = cms.untracked.PSet(
            limit=cms.untracked.int32(10)
            )
process.MessageLogger.categories.append('QuadCandEmbedder')
process.MessageLogger.cerr.QuadCandEmbedder = cms.untracked.PSet(
            limit=cms.untracked.int32(10)
            )

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            'file:/scratch/iross/testing.root',
#            'file:/hdfs/store/user/tapas/DoubleMu/Run2012D-PromptReco-v1/AOD/2013-04-01-8TeV-53X-PatTuple_Master/patTuple_cfg-FC8161A1-9640-E211-92E5-003048F118DE.root'
#            'file:/hdfs/store/user/tapas/DoubleElectron/Run2012D-16Jan2013-v1/AOD/2013-04-01-8TeV-53X-PatTuple_Master/patTuple_cfg-EA3FF9A5-836A-E211-9313-0025905964B6.root'
            ),
        inputCommands=cms.untracked.vstring(
            'keep *',
            'drop *_finalState*_*_*',
            'drop *_patFinalStateEvent*_*_*'
            )
        )

#process.source.secondaryFileNames = cms.untracked.vstring(
#        "file:/hdfs/store/data/Run2012C/DoubleMu/AOD/PromptReco-v2/000/201/278/487F6493-1EEE-E111-A398-001D09F297EF.root"
#        "file:/hdfs/store/data/Run2012B/DoubleElectron/AOD/13Jul2012-v1/00000/AAB0C291-89D4-E111-8D74-0026189438A0.root"
#        "file:/hdfs/store/data/Run2012B/DoubleElectron/AOD/13Jul2012-v1/00000/387EB788-6FD4-E111-9DBA-002618943944.root"
#        )

    # available calibration targets:
    # 2012 Data : 2012Jul13ReReco, Summer12_DR53X_HCP2012,
    #             Prompt, ReReco, ICHEP2012
    # 2012 MC   : Summer12, Summer12_DR53X_HCP2012
    #
    # 2011 Data : Jan16ReReco
    # 2011 MC   : Summer11, Fall11
from UWAnalysis.Configuration.tools.analysisTools import *
defaultAnalysisPath(process,'HLT',
        [
            "HLT_Mu17_Mu8",
            "HLT_Mu17_TkMu8",
            "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL",
            "HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL",
            "HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"
            ],
        EAtarget="2012Data", # Available targets: Fal11MC, Summer11MC, 2011Data, 2012Data
        calTarget = "Moriond2013",
        rochCor = "RochCor2012_dummy",
        isMC = False,
        isSync= False #use deterministic smearing in rochcor for syncing purposes? only gets applied to MC, I hope.
        )

#EventSelection
process.load("UWAnalysis.Configuration.zzLLLL_2012_loose_cff")
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMEEonly = cms.Path(process.MMEEonlyselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)
# process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
# process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
# process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
# process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
# process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
# process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
# process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
# process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
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

# from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
# addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
# addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
# addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
# addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
# addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
# addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
# addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
# addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
# addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)

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

#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuTree
#addMuTree(process,'finalMuons','goodPatMuons',leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleTree
#addEleTree(process,'finalElectrons','mvaedElectrons',leadingOnly=False)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleSCEventTree
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTree','EEESzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinal','EEESFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinalTest','EEESFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)

#Add event counter
addEventSummary(process,True,'MMEE','eventSelectionMMEE')
addEventSummary(process,True,'EEEE','eventSelectionEEEE')
addEventSummary(process,True,'EEMM','eventSelectionEEMM')
addEventSummary(process,True,'MMMM','eventSelectionMMMM')
# addEventSummary(process,True,'MMMT','eventSelectionMMMT')
# addEventSummary(process,True,'MMTT','eventSelectionMMTT')
# addEventSummary(process,True,'MMET','eventSelectionMMET')
# addEventSummary(process,True,'MMEM','eventSelectionMMEM')
# addEventSummary(process,True,'EEMT','eventSelectionEEMT')
# addEventSummary(process,True,'EEET','eventSelectionEEET')
# addEventSummary(process,True,'EETT','eventSelectionEETT')
# addEventSummary(process,True,'EEEM','eventSelectionEEEM')
addEventSummary(process,True,'MM','eventSelectionEE')
addEventSummary(process,True,'EE','eventSelectionMM')
#addEventSummary(process,False,'EEES','eventSelectionEEES')
