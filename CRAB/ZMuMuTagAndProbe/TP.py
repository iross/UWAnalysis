

import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V10::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/099/88FDF12C-D17F-E011-8317-003048F1C832.root',
                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/098/DCA6F527-DA7F-E011-BFD8-003048F117B4.root',
                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/093/5811266A-C27F-E011-A7DC-0030487A1990.root',
                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/088/FA043C42-E47F-E011-85B8-003048F118E0.root',
                '/store/data/Run2011A/TauPlusX/AOD/PromptReco-v4/000/165/071/7450CA91-C37F-E011-8B41-001617DBD472.root',
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',['HLT_IsoMu12_v1',
                                     'HLT_IsoMu12_v2',
                                     'HLT_IsoMu12_LooseIsoPFTau10_v4',
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
                              ['WW','ISO'],
                              ['userFloat("isWWMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
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
                              ['hltOverlapFilterIsoMu15IsoPFTau15','hltOverlapFilterIsoMu12IsoPFTau10']
)

addEventSummary(process,False,'summary','tagAndProbe')









