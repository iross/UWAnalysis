import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START53_V10::All'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
#            'file:/scratch/iross/gg125_sync.root'
#            'file:/scratch/iross/gg125_sync_noSkim.root'
            'file:/scratch/iross/gg125_sync_noSkim_newPFProdtag.root'
#            'file:/scratch/iross/eeeeMysteries_patTuple.root'
#'file:/scratch/iross/gg125_sync_noSkim_newPFProdtag_fsrTest1.root'
#            'file:/scratch/iross/gg125_sync_noSkim_newPFProdtag.root'
#'file:/scratch/iross/sync4l_wFSR.root'
#'file:/hdfs/store/user/tapas/2012-07-24-8Tev-PatTuple/Zjets_M50/1/patTuple_cfg-04542532-9A9B-E111-95D3-0025B31E3D3C.root'
#'file:/hdfs/store/user/tapas/2012-10-02-8TeV-53X-PatTuple_ShareFSFix/ZZTo2e2mu_8TeV-powheg-pythia6/patTuple_cfg-E6FECB8F-DDEE-E111-9AE6-1CC1DE1D16AA.root'
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

#process.source.secondaryFileNames = cms.untracked.vstring(
#        'file:/hdfs/store/mc/Summer12_DR53X/GluGluToHToZZTo4L_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/FEEEEFFF-7FFB-E111-8FE2-002618943810.root',
#        )

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

process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
        calibratedPatElectrons = cms.PSet(
            initialSeed = cms.untracked.uint32(1),
            engineName = cms.untracked.string('TRandom3')
            )
        )

#EventSelection
process.load("UWAnalysis.Configuration.zzLLLL_2012_cff")
#process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
#process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
#process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
#process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMEEonly = cms.Path(process.MMEEonlyselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
#process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
#process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
#process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
#process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
#process.eventSelectionEEES = cms.Path(process.EEESselectionSequence)
#process.eventSelectionESEE = cms.Path(process.ESEEselectionSequence)
#process.eventSelectionMMES = cms.Path(process.MMESselectionSequence)
#process.eventSelectionESMM = cms.Path(process.ESMMselectionSequence)
process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)
process.eventSelectionMMM = cms.Path(process.MMMSeq)
process.eventSelectionMME = cms.Path(process.MMESeq)
process.eventSelectionEEM = cms.Path(process.EEMSeq)
process.eventSelectionEEE = cms.Path(process.EEESeq)
process.eventSelectionMM = cms.Path(process.ZMMSeq)
process.eventSelectionEE = cms.Path(process.ZEESeq)
#process.eventSelectionEEES = cms.Path(process.EEESselectionSequence)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeFinal','MMEEZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeFinal','MMMMZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTreeFinal','MMEEonlyZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTree','MMEEonlyzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinal','EEEEZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=True)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
#addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
#addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
#addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
#addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=True)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuEventTree
addMuMuMuEventTree(process,'muMuMuEventTree','triMMMthirdMuID',leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEventTree
addMuMuEleEventTree(process,'muMuEleEventTree','triMMEthirdEleID',leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuEventTree
addEleEleMuEventTree(process,'eleEleMuEventTree','triEEMthirdMuID',leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEventTree
addEleEleEleEventTree(process,'eleEleEleEventTree','triEEEthirdEleID',leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEventTree
addEleEleEventTree(process,'eleEleEventTree','ZEEFinal',leadingOnly=True)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEventTree
addMuMuEventTree(process,'muMuEventTree','ZMMFinal',leadingOnly=True)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeID','EEMMzzMuIDSecondPair','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')

#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleSCEleEleEventTree
#addEleSCEleEleEventTree(process,'eleSCEleEleEventTree','ESEEzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleSCEleEleEventTree(process,'eleSCEleEleEventTreeFinal','ESEEFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleSCEleEleEventTree(process,'eleSCEleEleEventTreeFinalTest','ESEEFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleSCEventTree
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTree','EEESzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinal','EEESFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleEleEleSCEventTree(process,'eleEleEleSCEventTreeFinalTest','EEESFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleSCEventTree
#addMuMuEleSCEventTree(process,'muMuEleSCEventTree','MMESzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addMuMuEleSCEventTree(process,'muMuEleSCEventTreeFinal','MMESFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addMuMuEleSCEventTree(process,'muMuEleSCEventTreeFinalTest','MMESFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleSCMuMuEventTree
#addEleSCMuMuEventTree(process,'eleSCMuMuEventTree','ESMMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleSCMuMuEventTree(process,'eleSCMuMuEventTreeFinal','ESMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)
#addEleSCMuMuEventTree(process,'eleSCMuMuEventTreeFinalTest','ESMMFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True)

# Store all Gen Level particles. For H -> ZZ or ZZ only.
# process.genlevel = cms.EDAnalyzer("GenLevelFiller", gensrc = cms.InputTag("genParticles"), isGGZZ=cms.bool(False))
# process.genParticles = cms.Path( process.genlevel )


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
#addEventSummary(process,True,'EEES','eventSelectionEEES')
#addEventSummary(process,True,'ESEE','eventSelectionESEE')
#addEventSummary(process,True,'MMES','eventSelectionMMES')
#addEventSummary(process,True,'ESMM','eventSelectionESMM')
#addEventSummary(process,True,'MM','eventSelectionEE')
#addEventSummary(process,True,'EE','eventSelectionMM')
#addEventSummary(process,False,'EEES','eventSelectionEEES')

