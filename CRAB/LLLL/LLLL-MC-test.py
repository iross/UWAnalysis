import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V25::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#		'file:segfaultmaybe.root'
		#'file:pickevents.root'
#		'/store/mc/Summer11/ZZTo4L_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v3/0000/EEBA75B2-F3EE-E011-AC0D-001A92810AB8.root'
#		'/store/mc/Summer11/ZZJetsTo4L_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E23A3C95-74BA-E011-8A75-00237DA435CA.root'
#		'file:/afs/hep.wisc.edu/cms/iross/EWKZZ/CMSSW_4_1_8_patch7/src/ZZ/Gen/test/Sherpa_RECO.root'
		#'/store/mc/Summer11/ZZJetsTo4L_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEE3ABB5-79BA-E011-B754-78E7D1E4B4C6.root'
				'/store/mc/Fall11/GluGluToHToZZTo4L_M-210_7TeV-powheg-pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/16F0F32D-3EF3-E011-BEF7-00215E21D4D4.root'
#				'file:/afs/hep.wisc.edu/cms/iross/EWKZZ/CMSSW_4_2_8_patch7/src/ZZ/Gen/test/Sherpa_RECO.root'
)
    )

process.load("PhysicsTools.PatAlgos.patSequences_cff")

from UWAnalysis.Configuration.tools.analysisTools import *

defaultReconstructionMC(process,'HLT',
                        [
                         "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL",
                         "HLT_DoubleMu7"
                         ]
                        )

#EventSelection
process.load("UWAnalysis.Configuration.zzLLLLAnalysisStdIso_cff")
#process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
#process.eventSelectionMMTTTauUp = createSystematics(process,process.eventSelectionMMTT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMTTTauDown  = createSystematics(process,process.eventSelectionMMTT,'TauDown',1.00,1.0,0.97,1.0,1.0)
process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
#process.eventSelectionMMMTTauUp = createSystematics(process,process.eventSelectionMMMT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMMTTauDown = createSystematics(process,process.eventSelectionMMMT,'TauDown',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
#process.eventSelectionMMETTauUp = createSystematics(process,process.eventSelectionMMET,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMETTauDown = createSystematics(process,process.eventSelectionMMET,'TauDown',1.00,1.0,0.97,1.0,1.0)
#process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
#process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
#process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
#process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
#process.eventSelectionEEMTTauUp = createSystematics(process,process.eventSelectionEEMT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionEEMTTauDown = createSystematics(process,process.eventSelectionEEMT,'TauDown',1.00,1.0,0.97,1.0,1.0)
#process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
#process.eventSelectionEEETTauUp = createSystematics(process,process.eventSelectionEEET,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionEEETTauDown = createSystematics(process,process.eventSelectionEEET,'TauDown',1.00,1.0,0.97,1.0,1.0)
#process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
#process.eventSelectionEETTTauUp = createSystematics(process,process.eventSelectionEETT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionEETTTauDown = createSystematics(process,process.eventSelectionEETT,'TauDown',1.00,1.0,0.97,1.0,1.0)
#process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
#process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
#process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)

print process.eventSelectionMMMT.moduleNames()

createGeneratedParticles(process,
                         'genDaughters',
                          [
							  "keep++ pdgId = 25",
							  "keep++ pdgId = {Z0}",
							  # "drop pdgId = {Z0} & status = 2",
							  "keep pdgId = {tau+}",
							  "keep pdgId = {tau-}",
							  "keep pdgId = {mu+}",
							  "keep pdgId = {mu-}",
							  "keep pdgId = 11",
							  "keep pdgId = -11"
							  ]
						  )

#from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
#addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeTauUp','MMTTzzTauIDTauUp')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeTauDown','MMTTzzTauIDTauDown')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold')
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel')
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID')
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeTauUp','MMMTzzTauIDTauUp')
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeTauDown','MMMTzzTauIDTauDown')
#rom UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
#addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold')
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel')
#ddMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID')
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeTauUp','MMETzzTauIDTauUp')
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeTauDown','MMETzzTauIDTauDown')
#rom UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
#addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold')
#addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel')
#ddMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId')
#rom UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
#addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCandsAboveThreshold')
#addMuMuEleEleEventTree(process,'muMuEleEleEventTreeFinal','MMEEFinalSel')
#ddMuMuEleEleEventTree(process,'muMuEleEleEventTreeID','MMEEzzEleId')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCandsAboveThreshold')
#addMuMuMuMuEventTree(process,'muMuMuMuEventTreeFinal','MMMMFinalSel')
#ddMuMuMuMuEventTree(process,'muMuMuMuEventTreeID','MMMMzzMuIDSecondPair')
#rom UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold')
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel')
#ddEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID')
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeTauUp','EETTzzTauIDTauUp')
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeTauDown','EETTzzTauIDTauDown')
#rom UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold')
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel')
#ddEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID')
##addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeTauUp','EEETzzTauIDTauUp')
##addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeTauDown','EEETzzTauIDTauDown')
#rom UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold')
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel')
#ddEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID')
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeTauUp','EEMTzzTauIDTauUp')
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeTauDown','EEMTzzTauIDTauDown')
#rom UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold')
#addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel')
#ddEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID')
#rom UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
#addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCandsAboveThreshold')
#addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinal','EEEEFinalSel')
#ddEleEleEleEleEventTree(process,'eleEleEleEleEventTreeID','EEEEzzEleIDSecond')
#rom UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
#ddEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCandsAboveThreshold')
#addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMFinalSel')
#ddEleEleMuMuEventTree(process,'eleEleMuMuEventTreeID','EEMMzzMuIDSecondPair')


#Add event counter
addEventSummary(process,False,'MMMT','eventSelectionMMMT')
#addEventSummary(process,False,'MMTT','eventSelectionMMTT')
#addEventSummary(process,False,'MMET','eventSelectionMMET')
#addEventSummary(process,False,'MMEM','eventSelectionMMEM')
#addEventSummary(process,False,'MMEE','eventSelectionMMEE')
#addEventSummary(process,False,'MMMM','eventSelectionMMMM')
#addEventSummary(process,False,'EEMT','eventSelectionEEMT')
#addEventSummary(process,False,'EEET','eventSelectionEEET')
#addEventSummary(process,False,'EETT','eventSelectionEETT')
#addEventSummary(process,False,'EEEM','eventSelectionEEEM')
#addEventSummary(process,False,'EEEE','eventSelectionEEEE')
#addEventSummary(process,False,'EEMM','eventSelectionEEMM')

