import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START38_V12::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)




process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    $inputFileNames
),
duplicateCheckMode = cms.untracked.string("noDuplicateCheck")

)


process.mcAnalysis = cms.EDAnalyzer('ZLeptonTauPhaseSpaceAnalyzer',
                            motherBosonID = cms.int32(23),
                            leptonID = cms.int32(13),
                            FileName = cms.string('$outputFileName')
)                            
process.mcAnalysis2 = cms.EDAnalyzer('ZLeptonTauPhaseSpaceAnalyzer',
                            motherBosonID = cms.int32(23),
                            leptonID = cms.int32(13),
                            FileName = cms.string('e-$outputFileName')
)                            

process.p = cms.Path(process.mcAnalysis+process.mcAnalysis2)
