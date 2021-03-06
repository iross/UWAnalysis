import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START53_V10::All'

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
#            "file:/hdfs/store/user/tapas/VBF_HToZZTo4L_M-125_8TeV-powheg-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM/2013-03-13-8TeV-53X-PatTuple_Master/patTuple_cfg-A4C793E2-76FA-E111-9DB7-003048678F8A.root"
#'file:/hdfs/store/user/tapas/ZZTo2e2mu_8TeV-powheg-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM/2013-03-13-8TeV-53X-PatTuple_Master/patTuple_cfg-F4F33693-E4EE-E111-AB4F-1CC1DE1CDD20.root'
            "file:/hdfs/store/user/tapas/GluGluToZZTo2L2L_TuneZ2star_8TeV-gg2zz-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM/2013-04-01-8TeV-53X-PatTuple_Master/patTuple_cfg-8062C0E8-CB0A-E211-86D0-848F69FD294F.root"
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
        EAtarget = "2012Data", # Available targets: Fal11MC, Summer11MC, 2011Data, 2012Data
        calTarget = "Summer12_DR53X_HCP2012",
        rochCor = "RochCor2012_errDown_dummy",
        isMC = True,
        isSync=False #use deterministic smearing in rochcor for syncing purposes?
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
process.load("UWAnalysis.Configuration.zzLLLL_2012_loose_cff")
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
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeFinal','MMEEZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeFinal','MMMMZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTreeFinal','MMEEonlyZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTree','MMEEonlyzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinal','EEEEZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=True,leadingOnly=False)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
#addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
#addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
#addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
#addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=False)

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

#temp--muon dump to debug rochcor
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuTree
#addMuTree(process,'finalMuons','goodPatMuons',leadingOnly=False)

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
process.genlevel = cms.EDAnalyzer("GenLevelFiller", gensrc = cms.InputTag("genParticles"))
process.genParticles = cms.Path( process.genlevel )


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

