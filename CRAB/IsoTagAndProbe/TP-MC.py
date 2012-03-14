

import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'START42_V12::All'
process.GlobalTag.globaltag = 'GR_R_42_V10::All'
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/F441FDD0-BB76-E011-AEA9-003048D3C7BC.root',
#	'/store/mc/Summer11/QCD_Pt-15to20_MuPt5Enriched_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v2/0000/EA1255BD-3781-E011-83F2-00215E93F06C.root'
'/store/mc/Summer11/QCD_Pt-20to30_MuPt5Enriched_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v2/0000/0287E885-337F-E011-9504-00266CF2679C.root'
#'/store/mc/Summer11/QCD_Pt-15to30_TuneZ2_7TeV_pythia6/AODSIM/PU_S3_START42_V11-v2/0001/42BBCFD9-257E-E011-AC7F-E0CB4E55366A.root'

#                '/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/F2C4477C-C276-E011-BC02-0025901D4938.root',
#                '/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/F2AD28E1-CA76-E011-ABF4-0025901D4AF0.root',
#                '/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/F283DFF0-C976-E011-AC41-003048D4393E.root',
#                '/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/F27CA45F-CF76-E011-A04A-002481E0DC66.root',
#                '/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/F0F98170-F276-E011-9277-00266CF32920.root',
#                '/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/F0C6F93A-CF76-E011-BD04-003048F0E188.root',
#                '/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/F0895ABE-EB76-E011-B1AD-0025901D4124.root',
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")
from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',[
		'HLT_IsoMu17_v1',
		'HLT_IsoMu17_v2',
		'HLT_IsoMu17_v3',
		'HLT_IsoMu17_v4',
		'HLT_IsoMu17_v5',
		'HLT_IsoMu17_v6',
		'HLT_IsoMu17_v7',
		'HLT_IsoMu17_v8',
		'HLT_IsoMu17_v9',
		'HLT_IsoMu17_v10',
		'HLT_IsoMu17_v11',
		'HLT_IsoMu17_v12',
		'HLT_IsoMu17_v13',
		'HLT_DoubleMu7_v1',
		'HLT_DoubleMu7_v2',
		'HLT_Mu13_Mu8_v1',
		'HLT_Mu13_Mu8_v2',
		'HLT_Mu13_Mu8_v3',
		'HLT_Mu13_Mu8_v4',
		'HLT_Mu13_Mu8_v5',
		'HLT_Mu13_Mu8_v6'
		]
		)

#tagAndProbe 

process.load("UWAnalysis.Configuration.IsoTagAndProbe_cff")
process.tagAndProbe = cms.Path(process.tagAndProbeSequence)

#addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
#                              'MuonIsoDB',
#                              'patMuonsForAnalysis',
#                              'selectedTagAndProbeMuTracks',
#                              ['ISO'],
#                              ['(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
#                              ['hltSingleMuIsoL3IsoFiltered24'],
#                              ['hltSingleMuIsoL3IsoFiltered24']
#                       
#)
#addTagAndProbePlotter(process,'EleMuCrossTagAndProbePlotter',
#                              'MuonIsoRho',
#                              'patMuonsForAnalysis',
#                              'selectedTagAndProbeMuTracks',
#                              ['ISO'],
#                              ['(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
#                              ['hltSingleMuIsoL3IsoFiltered24'],
#                              ['hltSingleMuIsoL3IsoFiltered24']
#                       
#)
addTagAndProbePlotter(process,'EleMuCrossTagAndProbePlotter',
		'MuonIDPF',
		'patMuonsForAnalysis',
		'selectedTagAndProbeMuTracks',
		['ID','ISO03','ISO025','ISO02','ISO015','ISO01'],
		['isGlobalMuon()','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))/pt()<0.3','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))/pt()<0.25','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))/pt()<0.20','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))/pt()<0.15','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))/pt()<0.1'],
		[''],
		['']

		)
addTagAndProbePlotter(process,'EleMuCrossTagAndProbePlotter',
		'MuonIDPFAbs',
		'patMuonsForAnalysis',
		'selectedTagAndProbeMuTracks',
		['ID','ISO5','ISO4','ISO3','ISO2','ISO1'],
		['isGlobalMuon()','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))<5','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))<4','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))<3','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))<2','(chargedHadronIso+max(photonIso()+neutralHadronIso()-0.5*userIso(0),0.0))<1'],
		['*'],
		['*']

		)

addTagAndProbePlotter(process,'EleMuCrossTagAndProbePlotter',
		'MuonIDSTD',
		'patMuonsForAnalysis',
		'selectedTagAndProbeMuTracks',
		['ID','ISO015','ISO01','ISO005'],
		['isGlobalMuon()','((abs(eta())<1.479&&(isolationR03.sumPt+isolationR03.emEt+isolationR03.hadEt-(0.074+0.022)*userFloat("rho"))/pt()<0.15)||(abs(eta())>1.479&&(isolationR03.sumPt+isolationR03.emEt+isolationR03.hadEt-(0.045+0.030)*userFloat("rho"))/pt()<0.15))','((abs(eta())<1.479&&(isolationR03.sumPt+isolationR03.emEt+isolationR03.hadEt-(0.074+0.022)*userFloat("rho"))/pt()<0.1)||(abs(eta())>1.479&&(isolationR03.sumPt+isolationR03.emEt+isolationR03.hadEt-(0.045+0.030)*userFloat("rho"))/pt()<0.1))','((abs(eta())<1.479&&(isolationR03.sumPt+isolationR03.emEt+isolationR03.hadEt-(0.074+0.022)*userFloat("rho"))/pt()<0.05)||(abs(eta())>1.479&&(isolationR03.sumPt+isolationR03.emEt+isolationR03.hadEt-(0.045+0.030)*userFloat("rho"))/pt()<0.05))'],
		['hltSingleMuIsoL3IsoFiltered24'],
		['hltDiMuonL3PreFiltered7','hltDiMuonL3PreFiltered8']

		)

addEventSummary(process,False,'summary','tagAndProbe')


