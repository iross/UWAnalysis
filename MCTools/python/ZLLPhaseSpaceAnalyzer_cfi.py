import FWCore.ParameterSet.Config as cms

mcAnalysis = cms.EDAnalyzer('ZLLPhaseSpaceAnalyzer',
                            motherBosonID = cms.int32(23),
                            leptonID = cms.int32(13),
                            FileName = cms.string('mcOutput.root')
)                            

