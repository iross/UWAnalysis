import FWCore.ParameterSet.Config as cms

generatedMuons = cms.EDFilter("TauGenJetDecayModeSelector",
                              src = cms.InputTag("tauGenJets"),
                              select = cms.vstring('muon'),
                              filter = cms.bool(True)
)
generatedMuonsInAcceptance = cms.EDFilter("GenJetSelector",
                                          src = cms.InputTag("generatedMuons"),
                                          cut = cms.string('pt > 5.&&abs(eta)<2.4'),
                                          filter = cms.bool(True)
)

skimGenerator = cms.Sequence(
    generatedMuons*
    generatedMuonsInAcceptance

)    



muonPerformanceSignal = cms.EDAnalyzer('MuonEffAnalyzer',
                                       src = cms.InputTag('analysisMuons'),
                                       primaryVertices = cms.InputTag("offlinePrimaryVertices"),
                                       ref = cms.InputTag('generatedMuonsInAcceptance'),
                                       FileName = cms.string("signal_out.root"),
                                       TriggerPath = cms.string("HLT_Mu9")
)                                       

muonPerformance = cms.EDAnalyzer('MuonEffAnalyzer',
                                       src = cms.InputTag('analysisMuons'),
                                       primaryVertices = cms.InputTag("offlinePrimaryVertices"),
                                       ref = cms.InputTag('muons'),
                                       FileName = cms.string("qcd_out.root"),
                                       TriggerPath = cms.string("HLT_Mu9"),
                                       MatchDR = cms.untracked.double(0.5)
)                                       


muonPerfSignal = cms.Sequence(muonPerformanceSignal)

muonPerfBkg = cms.Sequence(muonPerformance)

