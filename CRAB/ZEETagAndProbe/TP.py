\
import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
       '/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/177/878/B299A0DC-21F1-E011-B9C6-003048F11112.root',
       '/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/177/878/9A02D8E7-10F1-E011-A7C9-003048D2BC42.root',
       '/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/177/878/8C1C01C6-2FF1-E011-998B-E0CB4E4408E7.root',
       '/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/177/878/7A8CC2DC-21F1-E011-AAF0-003048F1C836.root',
       '/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/177/878/7A50C1A2-02F1-E011-95E3-003048CF99BA.root',
       '/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/177/878/5C5B6AC1-25F1-E011-8372-BCAEC518FF80.root',
       '/store/data/Run2011B/DoubleElectron/AOD/PromptReco-v1/000/177/878/5AC7ABDA-1FF1-E011-9FF3-001D09F2AD84.root'
       
        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',[
    'HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC8_Mass30',
    'HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30'
    ])



#tagAndProbe 

process.load("UWAnalysis.Configuration.zEETagAndProbe_cff")
process.tagAndProbe = cms.Path(process.tagAndProbeSequence)


addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electron2l2t17L',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['CIC','ISO'],
                              ['gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(electronID("cicTight")==1||electronID("cicTight")==3||electronID("cicTight")==5||electronID("cicTight")==7||electronID("cicTight")==9||electronID("cicTight")==11||electronID("cicTight")==13||electronID("cicTight")==15)','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.25'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter'],
                              ['hltEle17CaloIdLCaloIsoVLPixelMatchFilterDoubleEG125','hltEle17CaloIdLCaloIsoVLPixelMatchFilter']
                                                            
)
addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electron2l2t8L',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['CIC','ISO'],
                              ['gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(electronID("cicTight")==1||electronID("cicTight")==3||electronID("cicTight")==5||electronID("cicTight")==7||electronID("cicTight")==9||electronID("cicTight")==11||electronID("cicTight")==13||electronID("cicTight")==15)','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.25'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter'],
                              ['hltEle17CaloIdIsoEle8CaloIdIsoPixelMatchDoubleFilter','hltEle8CaloIdLCaloIsoVLPixelMatchFilter']
                                                            
)
addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electron2l2tZ2L',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['CIC','ISO'],
                              ['gsfTrack().trackerExpectedHitsInner().numberOfHits()<1&&(electronID("cicTight")==1||electronID("cicTight")==3||electronID("cicTight")==5||electronID("cicTight")==7||electronID("cicTight")==9||electronID("cicTight")==11||electronID("cicTight")==13||electronID("cicTight")==15)','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.1'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter'],
                              ['hltEle17CaloIdIsoEle8CaloIdIsoPixelMatchDoubleFilter','hltEle8CaloIdLCaloIsoVLPixelMatchFilter']
                                                            
)
addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electron2l2t17T',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['CIC','ISO'],
                              ['gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(electronID("cicTight")==1||electronID("cicTight")==3||electronID("cicTight")==5||electronID("cicTight")==7||electronID("cicTight")==9||electronID("cicTight")==11||electronID("cicTight")==13||electronID("cicTight")==15)','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.25'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter'],
                              ['hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolFilter']
                                                            
)
addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electron2l2t8T',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['CIC','ISO'],
                              ['gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(electronID("cicTight")==1||electronID("cicTight")==3||electronID("cicTight")==5||electronID("cicTight")==7||electronID("cicTight")==9||electronID("cicTight")==11||electronID("cicTight")==13||electronID("cicTight")==15)','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.25'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter'],
                              ['hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolDoubleFilter']
                                                            
)
addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electron2l2tZ2T',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['CIC','ISO'],
                              ['gsfTrack().trackerExpectedHitsInner().numberOfHits()<1&&(electronID("cicTight")==1||electronID("cicTight")==3||electronID("cicTight")==5||electronID("cicTight")==7||electronID("cicTight")==9||electronID("cicTight")==11||electronID("cicTight")==13||electronID("cicTight")==15)','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.1'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter'],
                              ['hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolDoubleFilter']
                                                            
)
addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electronHtt15',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['WWID','ISO'],
                              ['userFloat("WWID")>0','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.1'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter'],
                              ['hltEle15CaloIdVTTrkIdTCaloIsoTTrkIsoTTrackIsolFilter']


)
addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electronHtt18',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['WWID','ISO'],
                              ['userFloat("WWID")>0','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.1'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter'],
                              ['hltEle18CaloIdVTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter']

)
addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electronHtt20',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['WWID','ISO'],
                              ['userFloat("WWID")>0','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.1'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter'],
                              ['hltEle20CaloIdVTCaloIsoTTrkIdTTrkIsoTTrackIsoFilterL1SingleEG18orL1SingleEG20']

)

# addTagAndProbePlotter(process,'ElectronMisIDTagAndProbePlotter',
#                               'TauMisID',
#                               'patOverloadedTaus',
#                               'selectedTagAndProbeEleTracks',
#                               ['DM','ISO','ELEVETO'],
#                               ['tauID("decayModeFinding")>0.5','tauID("byLooseIsolation")>0.5','tauID("againstElectronTight")>0.5'],
#                               ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle32CaloIdTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter'],
#                               ['hltOverlapFilterIsoEle15IsoPFTau15','hltOverlapFilterIsoEle18IsoPFTau20']
# 
# )


addEventSummary(process,False,'summary','tagAndProbe')











