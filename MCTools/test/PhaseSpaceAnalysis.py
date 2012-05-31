import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START38_V12::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)




process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/mc/Fall10/DYToTauTau_M-20_CT10_TuneZ2_7TeV-powheg-pythia-tauola/AODSIM/E7TeV_ProbDist_2010Data_BX156_START38_V12-v1/0002/9C3D0635-DBEC-DF11-B7E7-001A928116F4.root',
        
),
duplicateCheckMode = cms.untracked.string("noDuplicateCheck")

)


process.mcAnalysis = cms.EDAnalyzer('ZLeptonTauPhaseSpaceAnalyzer',
                            motherBosonID = cms.int32(23),
                            leptonID = cms.int32(13),
                            FileName = cms.string('ZmuTau.root')
)                            
process.mcAnalysis2 = cms.EDAnalyzer('ZLeptonTauPhaseSpaceAnalyzer',
                            motherBosonID = cms.int32(23),
                            leptonID = cms.int32(13),
                            FileName = cms.string('ZeTau.root')
)                            


process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")





process.printTree = cms.EDAnalyzer("ParticleTreeDrawer",
                                   src = cms.InputTag("genParticles"),
                                   printP4 = cms.untracked.bool(False),
                                   printPtEtaPhi = cms.untracked.bool(False),
                                   printVertex = cms.untracked.bool(False),
                                   printStatus = cms.untracked.bool(True),
                                   printIndex = cms.untracked.bool(False),
                                   status = cms.untracked.vint32(1,2,3)
                                 )
    


process.p = cms.Path(process.mcAnalysis+process.mcAnalysis2+process.printTree)
