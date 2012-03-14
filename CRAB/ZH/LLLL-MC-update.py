import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V10::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
)

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
		#'file:pickevents.root'
		'/store/mc/Summer11/ZZJetsTo4L_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E23A3C95-74BA-E011-8A75-00237DA435CA.root'
		#'/store/mc/Summer11/ZZJetsTo4L_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEE3ABB5-79BA-E011-B754-78E7D1E4B4C6.root'
		#	    '/store/mc/Summer11/GluGluToHToZZTo4L_M-210_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/8C877260-B298-E011-887C-00215E21EB7E.root'
#	    '/store/mc/Summer11/GluGluToZZTo4L_7TeV-gg2zz-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/C4E48AAF-AB9D-E011-952F-00215E21D5C4.root'
#	'/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0E4D251E-B59C-E011-B922-90E6BA442F1E.root'
#	'/store/mc/Summer11/ZZTo2e2mu_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/0AC98E6F-DFAD-E011-91A1-90E6BA442EFE.root'
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
process.load("UWAnalysis.Configuration.zzLLLLAnalysisFinalSelUpdate_cff")
process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
#process.eventSelectionMMTTTauUp = createSystematics(process,process.eventSelectionMMTT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMTTTauDown  = createSystematics(process,process.eventSelectionMMTT,'TauDown',1.00,1.0,0.97,1.0,1.0)
process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
#process.eventSelectionMMMTTauUp = createSystematics(process,process.eventSelectionMMMT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMMTTauDown = createSystematics(process,process.eventSelectionMMMT,'TauDown',1.00,1.0,1.03,1.0,1.0)
process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
#process.eventSelectionMMETTauUp = createSystematics(process,process.eventSelectionMMET,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionMMETTauDown = createSystematics(process,process.eventSelectionMMET,'TauDown',1.00,1.0,0.97,1.0,1.0)
process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
#process.eventSelectionEEMTTauUp = createSystematics(process,process.eventSelectionEEMT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionEEMTTauDown = createSystematics(process,process.eventSelectionEEMT,'TauDown',1.00,1.0,0.97,1.0,1.0)
process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
#process.eventSelectionEEETTauUp = createSystematics(process,process.eventSelectionEEET,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionEEETTauDown = createSystematics(process,process.eventSelectionEEET,'TauDown',1.00,1.0,0.97,1.0,1.0)
process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
#process.eventSelectionEETTTauUp = createSystematics(process,process.eventSelectionEETT,'TauUp',1.00,1.0,1.03,1.0,1.0)
#process.eventSelectionEETTTauDown = createSystematics(process,process.eventSelectionEETT,'TauDown',1.00,1.0,0.97,1.0,1.0)
process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)

createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep++ pdgId = {Z0}",
                           "drop pdgId = {Z0} & status = 2",
                           "keep pdgId = {tau+}",
                           "keep pdgId = {tau-}",
                           "keep pdgId = {mu+}",
                           "keep pdgId = {mu-}",
                           "drop pdgId = 11",
                           "drop pdgId = -11"
                          ]
)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCandsAboveThreshold')
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel')
addMuMuTauTauEventTree(process,'muMuTauTauEventTreeID','MMTTzzTauID')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeTauUp','MMTTzzTauIDTauUp')
#addMuMuTauTauEventTree(process,'muMuTauTauEventTreeTauDown','MMTTzzTauIDTauDown')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCandsAboveThreshold')
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel')
addMuMuMuTauEventTree(process,'muMuMuTauEventTreeID','MMMTzzTauID')
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeTauUp','MMMTzzTauIDTauUp')
#addMuMuMuTauEventTree(process,'muMuMuTauEventTreeTauDown','MMMTzzTauIDTauDown')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCandsAboveThreshold')
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel')
addMuMuEleTauEventTree(process,'muMuEleTauEventTreeID','MMETzzTauID')
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeTauUp','MMETzzTauIDTauUp')
#addMuMuEleTauEventTree(process,'muMuEleTauEventTreeTauDown','MMETzzTauIDTauDown')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCandsAboveThreshold')
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel')
addMuMuEleMuEventTree(process,'muMuEleMuEventTreeID','MMEMzzEleId')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCandsAboveThreshold')
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeFinal','MMEEFinalSel')
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeID','MMEEzzEleId')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCandsAboveThreshold')
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeFinal','MMMMFinalSel')
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeID','MMMMzzMuIDSecondPair')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCandsAboveThreshold')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeID','EETTzzTauID')
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeTauUp','EETTzzTauIDTauUp')
#addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeTauDown','EETTzzTauIDTauDown')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCandsAboveThreshold')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeID','EEETzzTauID')
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeTauUp','EEETzzTauIDTauUp')
#addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeTauDown','EEETzzTauIDTauDown')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCandsAboveThreshold')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeID','EEMTzzTauID')
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeTauUp','EEMTzzTauIDTauUp')
#addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeTauDown','EEMTzzTauIDTauDown')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCandsAboveThreshold')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeID','EEEMzzMuID')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCandsAboveThreshold')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinal','EEEEFinalSel')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeID','EEEEzzEleIDSecond')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCandsAboveThreshold')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMFinalSel')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeID','EEMMzzMuIDSecondPair')

#Add event counter
addEventSummary(process,False,'MMMT','eventSelectionMMMT')
addEventSummary(process,False,'MMTT','eventSelectionMMTT')
addEventSummary(process,False,'MMET','eventSelectionMMET')
addEventSummary(process,False,'MMEM','eventSelectionMMEM')
addEventSummary(process,False,'MMEE','eventSelectionMMEE')
addEventSummary(process,False,'MMMM','eventSelectionMMMM')
addEventSummary(process,False,'EEMT','eventSelectionEEMT')
addEventSummary(process,False,'EEET','eventSelectionEEET')
addEventSummary(process,False,'EETT','eventSelectionEETT')
addEventSummary(process,False,'EEEM','eventSelectionEEEM')
addEventSummary(process,False,'EEEE','eventSelectionEEEE')
addEventSummary(process,False,'EEMM','eventSelectionEEMM')

