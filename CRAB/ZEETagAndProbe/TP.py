
import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_42_V19::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

       '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/166/346/5CA03BF3-D68E-E011-A3F8-0030487CD6E6.root',
       '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/166/346/74A4019A-398F-E011-8F2B-001D09F2437B.root',
       '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/166/346/74F0BF0D-208F-E011-A18E-001D09F25041.root',
       '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/166/346/78C0EFD5-D68E-E011-B1B4-001D09F2AD4D.root',
       '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/166/346/CEECBA31-D38E-E011-94FF-003048D2BCA2.root',
       '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/166/346/D857F287-D58E-E011-87B0-001D09F2906A.root',
       '/store/data/Run2011A/DoubleElectron/AOD/PromptReco-v4/000/166/374/582C192D-DD8E-E011-A5F5-001D09F24498.root'

        )
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',[
    "HLT_Ele17_CaloIdL_CaloIsoVL",
    "HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC8_Mass30",
    ])



#tagAndProbe 

process.load("UWAnalysis.Configuration.zEETagAndProbe_cff")
process.tagAndProbe = cms.Path(process.tagAndProbeSequence)

addTagAndProbePlotter(process,'ElectronSCTagAndProbePlotter',
                              'electronHLT8',
                              'convRejElectrons',
                              'selectedTagAndProbeEleSCs',
                              ['CIC','ISO'],
                              ['(electronID("cicTight")==5 || electronID("cicTight")==7 || electronID("cicTight")==13 || electronID("cicTight")==15)','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.25'],
                              ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle32CaloIdTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter'],
                              ['hltEle17CaloIdIsoEle8CaloIdIsoPixelMatchDoubleFilter','hltEle8CaloIdLCaloIsoVLPixelMatchFilter']
                                                            
)
# addTagAndProbePlotter(process,'ElectronTagAndProbePlotter',
#                               'electronID',
#                               'convRejElectrons',
#                               'selectedTagAndProbeDiElectrons',
#                               ['WWID','ISO'],
#                               ['userFloat("WWID")>0','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.1'],
#                               ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle32CaloIdTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter'],
#                               ['hltEle15CaloIdVTTrkIdTCaloIsoTTrkIsoTTrackIsolFilter','hltEle18CaloIdVTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter']
#                               
#                               
# )
# addTagAndProbePlotter(process,'ElectronTagAndProbePlotter',
#                               'electronHLT15',
#                               'convRejElectrons',
#                               'selectedTagAndProbeDiElectrons',
#                               ['WWID','ISO'],
#                               ['userFloat("WWID")>0','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.1'],
#                               ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle32CaloIdTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter'],
#                               ['hltEle15CaloIdVTTrkIdTCaloIsoTTrkIsoTTrackIsolFilter','hltEle15CaloIdVTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter']
# 
# 
# )
# 
# addTagAndProbePlotter(process,'ElectronTagAndProbePlotter',
#                               'electronHLT18',
#                               'convRejElectrons',
#                               'selectedTagAndProbeDiElectrons',
#                               ['WWID','ISO'],
#                               ['userFloat("WWID")>0','(chargedHadronIso+max(0.0,neutralHadronIso+photonIso-0.5*particleIso))/pt()<0.1'],
#                               ['hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','hltEle32CaloIdTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter'],
#                               ['hltEle18CaloIdVTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter']
# 
# )



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











