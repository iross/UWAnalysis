

import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V12::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/mc/Summer11/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/AODSIM/PU_S3_START42_V11-v1/0000/F441FDD0-BB76-E011-AEA9-003048D3C7BC.root',
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
defaultReconstructionMC(process,'HLT',['HLT_IsoMu12_v1',
                                     'HLT_IsoMu12_v2',
                                     'HLT_IsoMu12_LooseIsoPFTau10_v2',
                                     'HLT_IsoMu24_v1',
                                     'HLT_IsoMu24_v2',
                                     'HLT_IsoMu24_v3',
                                     'HLT_IsoMu24_v4',
                                     'HLT_IsoMu24_v5',
                                     'HLT_IsoMu15_LooseIsoPFTau15_v1',
                                     'HLT_IsoMu15_LooseIsoPFTau15_v2',
                                     'HLT_IsoMu15_LooseIsoPFTau15_v3',
                                     'HLT_IsoMu15_LooseIsoPFTau15_v4',
                                     'HLT_DoubleMu7_v1',
                                     'HLT_DoubleMu7_v2',
                                     'HLT_Mu13_Mu8_v2'
                                     ]
    )



#tagAndProbe 

process.load("UWAnalysis.Configuration.zMuMuTagAndProbe_cff")
process.tagAndProbe = cms.Path(process.tagAndProbeSequence)



addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonID',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['SIP3DTest','WW','ISO'],
                              ['userFloat("SIP3D")<1','userFloat("isWWMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
                              ['hltSingleMuIsoL3IsoFiltered24'],
                              ['hltSingleMuIsoL3IsoFiltered24']
                       
)

addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonHLTIsoMu12',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['WW','ISO'],
                              ['userFloat("isWWMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
                              ['hltSingleMuIsoL3IsoFiltered12'],
                              ['hltSingleMuIsoL3IsoFiltered12']
                       
)


addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonHLTIsoMu15',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['WW','ISO'],
                              ['userFloat("isWWMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
                              ['hltSingleMuIsoL3IsoFiltered24'],
                              ['hltSingleMuIsoL3IsoFiltered15']
)


addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonHLTMu8',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['WW','ISO'],
                              ['userFloat("isWWMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
                              ['hltSingleMuIsoL3IsoFiltered24'],
                              ['hltDiMuonL3PreFiltered8','hltDiMuonL3PreFiltered7']

)


addTagAndProbePlotter(process,'MuonMisIDTagAndProbePlotter',
                              'TauMisID',
                              'patOverloadedTaus',
                              'selectedTagAndProbeMuTracks',
                              ['DM','ISO','MUVETO'],
                              ['tauID("decayModeFinding")>0.5','isolationPFChargedHadrCandsPtSum()+max(0.0,isolationPFGammaCandsEtSum()-0.35*particleIso())<2.0','tauID("againstMuonTight")>0.5'],
                              ['hltSingleMuIsoL3IsoFiltered24'],
                              ['hltOverlapFilterIsoMu15IsoPFTau15']
)

addEventSummary(process,False,'summary','tagAndProbe')







