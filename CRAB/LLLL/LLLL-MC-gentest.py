import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V25::All'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            #		'file:segfaultmaybe.root'
            #'file:pickevents.root'
            #		'file:/scratch/iross/zz4l_sync.root'
#			'file:/hdfs/store/user/iross/uf_zz2e2t_patTuple/output_8_1_RNG.root',
			'file:/scratch/iross/zz4l_sync_fall11_take2.root'
#            'file:/scratch/iross/zz4l_sync_2.root'
            #		'file:eemm_ZZ4Lfall_50evts.root'
            ),
        inputCommands=cms.untracked.vstring(
            'keep *',
            'drop *_finalState*_*_*',
            'drop *_patFinalStateEvent*_*_*'
            )
        )

#process.load("PhysicsTools.PatAlgos.patSequences_cff")

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

createGeneratedParticlesPATtuple(process,
        'genDaughters',
        [
            "keep++ pdgId = 25",
            "drop pdgId = {tau+}",
            "drop pdgId = {tau-}",
            "keep pdgId = {mu+}",
            "keep pdgId = {mu-}",
            "keep pdgId = 11",
            "keep pdgId = -11"
            ]
        )

#EventSelection
process.load("UWAnalysis.Configuration.zzGenTest_cff")
#process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
#process.eventSelectionMMTTTauUp = createSystematics(process,process.eventSelectionMMTT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMTTTauDown  = createSystematics(process,process.eventSelectionMMTT,'TauDown',1.00,1.0,0.97,1.0,1.0)
#process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
#process.eventSelectionMMMTTauUp = createSystematics(process,process.eventSelectionMMMT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMMTTauDown = createSystematics(process,process.eventSelectionMMMT,'TauDown',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
#process.eventSelectionMMETTauUp = createSystematics(process,process.eventSelectionMMET,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMETTauDown = createSystematics(process,process.eventSelectionMMET,'TauDown',1.00,1.0,0.97,1.0,1.0)
#process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
#process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
#process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
#process.eventSelectionEEMTTauUp = createSystematics(process,process.eventSelectionEEMT,'TauUp',1.00,1.0,1.03,1.0,1.0)

#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
#addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeTauUp','MMTTzzTauIDTauUp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeTauDown','MMTTzzTauIDTauDown','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
#addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeTauUp','MMMTzzTauIDTauUp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeTauDown','MMMTzzTauIDTauDown','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
#addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeTauUp','MMETzzTauIDTauUp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeTauDown','MMETzzTauIDTauDown','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
#addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
#addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuEleEleEventTree(process,'muMuEleEleEventTreeFinal','MMEEFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuEleEleEventTree(process,'muMuEleEleEventTreeID','MMEEzzEleId','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
#addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeID','MMMMzzCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedMuID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeFinal','MMMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addMuMuMuMuEventTree(process,'muMuMuMuEventTreeID','MMMMzzMuIDSecondPair','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeTauUp','EETTzzTauIDTauUp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeTauDown','EETTzzTauIDTauDown','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeTauUp','EEETzzTauIDTauUp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeTauDown','EEETzzTauIDTauDown','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeTauUp','EEMTzzTauIDTauUp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeTauDown','EEMTzzTauIDTauDown','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
#addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinal','EEEEFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinalTest','EEEEFinalSelTemp','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeID','EEEEzzEleIDSecond','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCandsAboveThreshold','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeID','EEMMzzMuIDSecondPair','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel')
#from UWAnalysis.Configuration.tools.ntupleTools import addMuMuEventTree
#addMuMuEventTree(process,'muMuEventTreeTest','MMMMbestTest')

#Add event counter
#addEventSummary(process,False,'MMMT','eventSelectionMMMT')
#addEventSummary(process,False,'MMTT','eventSelectionMMTT')
#addEventSummary(process,False,'MMET','eventSelectionMMET')
#addEventSummary(process,False,'MMEM','eventSelectionMMEM')
#addEventSummary(process,False,'MMEE','eventSelectionMMEE')
addEventSummary(process,False,'MMMM','eventSelectionMMMM')
#addEventSummary(process,False,'EEMT','eventSelectionEEMT')
#addEventSummary(process,False,'EEET','eventSelectionEEET')
#addEventSummary(process,False,'EETT','eventSelectionEETT')
#addEventSummary(process,False,'EEEM','eventSelectionEEEM')
#addEventSummary(process,False,'EEEE','eventSelectionEEEE')
#addEventSummary(process,False,'EEMM','eventSelectionEEMM')
