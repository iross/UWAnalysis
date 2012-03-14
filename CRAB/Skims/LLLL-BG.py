import FWCore.ParameterSet.Config as cms
import sys


process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_311_V2::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
		'file:skim.root'
#		'/store/user/iross/MM_2011Bv1_skim/skim_117_1_PjN.root'
#		'/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/175/835/9212E97C-CDDB-E011-8A58-001D09F25479.root'
#		'/store/mc/Summer11/ZZJetsTo4L_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E23A3C95-74BA-E011-8A75-00237DA435CA.root'
		#'/store/mc/Summer11/ZZJetsTo4L_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEE3ABB5-79BA-E011-B754-78E7D1E4B4C6.root'
		#	    '/store/mc/Summer11/GluGluToHToZZTo4L_M-210_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/8C877260-B298-E011-887C-00215E21EB7E.root'
#	    '/store/mc/Summer11/GluGluToZZTo4L_7TeV-gg2zz-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/C4E48AAF-AB9D-E011-952F-00215E21D5C4.root'
#	'/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0E4D251E-B59C-E011-B922-90E6BA442F1E.root'
#	'/store/mc/Summer11/ZZTo2e2mu_7TeV-powheg-pythia6/AODSIM/PU_S4_START42_V11-v1/0000/0AC98E6F-DFAD-E011-91A1-90E6BA442EFE.root'
)
    )

process.load("PhysicsTools.PatAlgos.patSequences_cff")

from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',
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
process.load("UWAnalysis.Configuration.zzLLLLAnalysisBG_cff")
process.eventSelectionMMMTantiIso = cms.Path(process.MMMTantiIsoSeq)
process.eventSelectionMMMTantiIso2 = cms.Path(process.MMMTantiIso2Seq)
process.eventSelectionMMTTantiIso = cms.Path(process.MMTTantiIsoSeq)
process.eventSelectionMMTTantiIso2 = cms.Path(process.MMTTantiIso2Seq)
process.eventSelectionMMETantiIso = cms.Path(process.MMETantiIsoSeq)
process.eventSelectionMMETantiIso2 = cms.Path(process.MMETantiIso2Seq)
process.eventSelectionMMEMantiIso = cms.Path(process.MMEMantiIsoSeq)
process.eventSelectionMMEMantiIso2 = cms.Path(process.MMEMantiIso2Seq)
process.eventSelectionMMEEantiIso = cms.Path(process.MMEEantiIsoSeq)
process.eventSelectionMMEEantiIso2 = cms.Path(process.MMEEantiIso2Seq)
process.eventSelectionMMMMantiIso = cms.Path(process.MMMMantiIsoSeq)
process.eventSelectionMMMMantiIso2 = cms.Path(process.MMMMantiIso2Seq)
process.eventSelectionEEMTantiIso = cms.Path(process.EEMTantiIsoSeq)
process.eventSelectionEEMTantiIso2 = cms.Path(process.EEMTantiIso2Seq)
process.eventSelectionEEETantiIso = cms.Path(process.EEETantiIsoSeq)
process.eventSelectionEEETantiIso2 = cms.Path(process.EEETantiIso2Seq)
process.eventSelectionEETTantiIso = cms.Path(process.EETTantiIsoSeq)
process.eventSelectionEETTantiIso2 = cms.Path(process.EETTantiIso2Seq)
process.eventSelectionEEEMantiIso = cms.Path(process.EEEMantiIsoSeq)
process.eventSelectionEEEMantiIso2 = cms.Path(process.EEEMantiIso2Seq)
process.eventSelectionEEMMantiIso = cms.Path(process.EEMMantiIsoSeq)
process.eventSelectionEEMMantiIso2 = cms.Path(process.EEMMantiIso2Seq)
process.eventSelectionEEEEantiIso = cms.Path(process.EEEEantiIsoSeq)
process.eventSelectionEEEEantiIso2 = cms.Path(process.EEEEantiIso2Seq)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_noIso','MMMTnoIsoF')
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_antiIso','MMMTantiIsoBothF')
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_antiIso1','MMMTantiIso1F')
addMuMuMuTauEventTree(process,'muMuMuTauEventTree_antiIso2','MMMTantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_noIso','MMTTnoIsoF')
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_antiIso','MMTTantiIsoBothF')
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_antiIso1','MMTTantiIso1F')
addMuMuTauTauEventTree(process,'muMuTauTauEventTree_antiIso2','MMTTantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_noIso','MMETnoIsoF')
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_antiIso','MMETantiIsoBothF')
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_antiIso1','MMETantiIso1F')
addMuMuEleTauEventTree(process,'muMuEleTauEventTree_antiIso2','MMETantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_noIso','MMEMnoIsoF')
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_antiIso','MMEMantiIsoBothF')
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_antiIso1','MMEMantiIso1F')
addMuMuEleMuEventTree(process,'muMuEleMuEventTree_antiIso2','MMEMantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_noIso','MMEEnoIsoF')
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_antiIso','MMEEantiIsoBothF')
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_antiIso1','MMEEantiIso1F')
addMuMuEleEleEventTree(process,'muMuEleEleEventTree_antiIso2','MMEEantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_noIso','MMMMnoIsoF')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_antiIso','MMMMantiIsoBothF')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_antiIso1','MMMMantiIso1F')
addMuMuMuMuEventTree(process,'muMuMuMuEventTree_antiIso2','MMMMantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_noIso','EEMTnoIsoF')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_antiIso','EEMTantiIsoBothF')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_antiIso1','EEMTantiIso1F')
addEleEleMuTauEventTree(process,'eleEleMuTauEventTree_antiIso2','EEMTantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_noIso','EEETnoIsoF')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_antiIso','EEETantiIsoBothF')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_antiIso1','EEETantiIso1F')
addEleEleEleTauEventTree(process,'eleEleEleTauEventTree_antiIso2','EEETantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_noIso','EETTnoIsoF')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_antiIso','EETTantiIsoBothF')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_antiIso1','EETTantiIso1F')
addEleEleTauTauEventTree(process,'eleEleTauTauEventTree_antiIso2','EETTantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_noIso','EEEMnoIsoF')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_antiIso','EEEMantiIsoBothF')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_antiIso1','EEEMantiIso1F')
addEleEleEleMuEventTree(process,'eleEleEleMuEventTree_antiIso2','EEEMantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_noIso','EEMMnoIsoF')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_antiIso','EEMMantiIsoBothF')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_antiIso1','EEMMantiIso1F')
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree_antiIso2','EEMMantiIso2F')
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_noIso','EEEEnoIsoF')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_antiIso','EEEEantiIsoBothF')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_antiIso1','EEEEantiIso1F')
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree_antiIso2','EEEEantiIso2F')

#Add event counter
addEventSummary(process,False,'MMMT','eventSelectionMMMTantiIso')
addEventSummary(process,False,'MMTT','eventSelectionMMTTantiIso')
addEventSummary(process,False,'MMET','eventSelectionMMETantiIso')
addEventSummary(process,False,'MMEM','eventSelectionMMEMantiIso')
addEventSummary(process,False,'MMEE','eventSelectionMMEEantiIso')
addEventSummary(process,False,'EETT','eventSelectionEETTantiIso')
