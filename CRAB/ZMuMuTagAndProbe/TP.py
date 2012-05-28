

import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V10::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

       '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/178/098/78673382-F6F5-E011-8431-BCAEC518FF69.root',
       '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/178/098/72FA2E53-DBF3-E011-8C39-BCAEC53296F4.root',
       '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/178/098/626E4CC3-CFF4-E011-B927-003048F1DBAE.root',
       '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/178/098/5AB6073B-AEF3-E011-9BD3-BCAEC5329724.root',
       '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/178/098/4E2882E1-81F3-E011-B7A6-001D09F29146.root',
       '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/178/098/42A8A5D7-CFF4-E011-958C-003048F01184.root',
       '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/178/098/400F3553-7FF3-E011-B6D0-BCAEC518FF8F.root',
       '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/178/098/28427520-F2F3-E011-8E6C-002481E0D90C.root'
       
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',['HLT_IsoMu12',
                                     'HLT_IsoMu24',
                                     'HLT_IsoMu24_eta2p1'
                                     ]
    )



#tagAndProbe 

process.load("UWAnalysis.Configuration.zMuMuTagAndProbe_cff")
process.tagAndProbe = cms.Path(process.tagAndProbeSequence)


addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonHLTMu8ZZ',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['ID','ISO'],
                              ['userFloat("isZZMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.25'],
                              ['hltSingleMuIsoL3IsoFiltered12','hltSingleMuIsoL3IsoFiltered24','hltL3IsoL1sMu14Eta2p1L1f0L2f14QL2IsoL3f24L3IsoFiltered'],
                              ['hltDiMuonL3PreFiltered8','hltDiMuonL3PreFiltered7','hltDiMuonL3p5PreFiltered8']

)

addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonHLTMu13ZZ',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['ID','ISO'],
                              ['userFloat("isZZMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.25'],
                              ['hltSingleMuIsoL3IsoFiltered24','hltL3IsoL1sMu14Eta2p1L1f0L2f14QL2IsoL3f24L3IsoFiltered'],
                              ['hltSingleMu13L3Filtered13']

)
addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonHLTMu17ZZ',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['ID','ISO'],
                              ['userFloat("isZZMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.25'],
                              ['hltL3IsoL1sMu14Eta2p1L1f0L2f14QL2IsoL3f24L3IsoFiltered'],
                              ['hltSingleMu13L3Filtered17']

)

addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonZ2',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['ID','ISO'],
                              ['userFloat("isZZMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
                              ['hltSingleMuIsoL3IsoFiltered12','hltSingleMuIsoL3IsoFiltered24','hltL3IsoL1sMu14Eta2p1L1f0L2f14QL2IsoL3f24L3IsoFiltered'],
                              ['hltDiMuonL3PreFiltered8','hltDiMuonL3PreFiltered7','hltDiMuonL3p5PreFiltered8']

)

addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonHttL1_14',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['WW','ISO'],
                              ['userFloat("isWWMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
                              ['hltL3IsoL1sMu14Eta2p1L1f0L2f14QL2IsoL3f24L3IsoFiltered'],
                              ['hltSingleMuIsoL1s14L3IsoFiltered15eta2p1']
                       
)

addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonHttMu12',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['WW','ISO'],
                              ['userFloat("isWWMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
                              ['hltSingleMuIsoL3IsoFiltered12'],
                              ['hltSingleMuIsoL3IsoFiltered12']

                       
)

addTagAndProbePlotter(process,'MuonTagAndProbePlotter',
                              'MuonHttMu15',
                              'patMuonsForAnalysis',
                              'selectedTagAndProbeMuTracks',
                              ['WW','ISO'],
                              ['userFloat("isWWMuon")>0.5','(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0))/pt()<0.1'],
                              ['hltSingleMuIsoL3IsoFiltered24'],
                              ['hltSingleMuIsoL3IsoFiltered15']

)



# 
# addTagAndProbePlotter(process,'MuonMisIDTagAndProbePlotter',
#                               'TauMisID',
#                               'patOverloadedTaus',
#                               'selectedTagAndProbeMuTracks',
#                               ['DM','ISO','MUVETO'],
#                               ['tauID("decayModeFinding")>0.5','isolationPFChargedHadrCandsPtSum()+max(0.0,isolationPFGammaCandsEtSum()-0.35*particleIso())<2.0','tauID("againstMuonTight")>0.5'],
#                               ['hltSingleMuIsoL3IsoFiltered24'],
#                               ['hltOverlapFilterIsoMu15IsoPFTau15','hltOverlapFilterIsoMu12IsoPFTau10']
# )

addEventSummary(process,False,'summary','tagAndProbe')









