import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'FT_R_39X_V4A::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/F27D338B-D2EA-DF11-9664-00261834B561.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/F0AFAFDB-D0EA-DF11-A4EC-485B39800C2D.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/ECABC1EE-D1EA-DF11-84A4-485B39800C15.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/EAE1B0EE-D1EA-DF11-B3FF-90E6BA442F43.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/E6607991-D2EA-DF11-9A20-0019BB3FF44C.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/E25D7CCB-D3EA-DF11-8F73-E0CB4E29C507.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/DE14A27B-D2EA-DF11-A6CC-E0CB4E29C4D5.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/D0CFA004-D0EA-DF11-A74A-001A4BA81F0A.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/CCD726E3-D0EA-DF11-9971-90E6BA0D09D7.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/CA73A152-CFEA-DF11-B566-E0CB4E29C517.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/C8C78FFB-D1EA-DF11-9C07-E0CB4E29C506.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/B6CE8BCC-D3EA-DF11-A615-E0CB4E1A114C.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/B41D95C1-D3EA-DF11-B595-485B39800B83.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/B2E648DB-D0EA-DF11-A65A-E0CB4E1A1180.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/AE5EB3C2-D3EA-DF11-8865-485B39800BD7.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/AC9FAE84-D2EA-DF11-B37D-E0CB4E29C4E4.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/9ACFD0E0-D1EA-DF11-AFD6-001EC9D7F68B.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/9831A7C1-D3EA-DF11-AE65-E0CB4E1A11A1.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/96C1DDCA-D3EA-DF11-A683-90E6BA442F10.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/94450A8C-D2EA-DF11-BBB9-0030487CDAC6.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/921F4B7D-D2EA-DF11-9F41-E0CB4E5536A5.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/88AB9DF1-CFEA-DF11-9B66-E0CB4E55369E.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/84EDF126-D1EA-DF11-9730-E0CB4E4408BE.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/80ED4E8B-D2EA-DF11-90CF-90E6BA0D09EC.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/74E5ECC8-D3EA-DF11-B787-485B39800BDA.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/7031AEDC-CFEA-DF11-8548-E0CB4E29C4F2.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/52ADF58E-D2EA-DF11-A064-E0CB4E19F962.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/52ACEE1C-D4EA-DF11-B7DA-90E6BA0D09B6.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/4CC547C5-D3EA-DF11-AEFB-90E6BA442F31.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/3EE0A02A-D1EA-DF11-8202-E0CB4E29C4D7.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/30BA2ECE-D3EA-DF11-84FD-90E6BA19A232.root',
                '/store/data/Run2010B/Mu/RECO/Nov4ReReco_v1/0008/2C8B9078-D2EA-DF11-9970-E0CB4E5536BE.root',
        

        
)
)

process.load("PhysicsTools.PatAlgos.patSequences_cff")

from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT')


#mu enriched fake rate 
process.load("UWAnalysis.Configuration.tauFakeRate_muEnriched_cff")
process.muEnrichedFakeRate = cms.Path(process.muEnrichedSequence)
#w jets fake rate 
process.load("UWAnalysis.Configuration.tauFakeRate_wJets_cff")
process.wJetsFakeRate = cms.Path(process.wJetsSequence)
#z jets fake rate 
process.load("UWAnalysis.Configuration.tauFakeRate_zJets_cff")
process.zJetsFakeRate = cms.Path(process.zJetsSequence)


addTauIDPlotter(process,'MuEnriched','patTaus','muEnrichedJetsForFakeRate',['leadingTrackFinding','byLooseIsolation','againstMuon','againstElectron'])
addTauIDPlotter(process,'wJets','patTaus','wJetsForFakeRate',['leadingTrackFinding','byLooseIsolation','againstMuon','againstElectron'])
addTauIDPlotter(process,'zJets','patTaus','zJetsForFakeRate',['leadingTrackFinding','byLooseIsolation','againstMuon','againstElectron'])

