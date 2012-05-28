import FWCore.ParameterSet.Config as cms


#globalMuon
globalMuons = cms.EDFilter("PATMuonSelector",
                           src = cms.InputTag('analysisMuons'),
                           cut = cms.string('isGlobalMuon()'),
                           filter = cms.bool(False)
)

#muons over pt
muonsPtCut = cms.EDFilter("PATMuonSelector",
                          src = cms.InputTag('globalMuons'),
                          cut = cms.string('pt > 15.'),
                          filter = cms.bool(False)
)

isolatedMuons = cms.EDFilter("PATMuonSelector",
                          src = cms.InputTag('muonsPtCut'),
                          cut = cms.string('chargedHadronIso+photonIso<3'),
                          filter = cms.bool(False)
)


#create a collection of tracks
allTracks = cms.EDProducer("TrackViewCandidateProducer",
    src = cms.InputTag("generalTracks"),
    particleType = cms.string('mu+'),
    cut = cms.string('pt > 15&& abs(eta)<2.1&&charge>0')
)



#Make the invariant mass of the muon and the track and select the Z candidate
diMuons = cms.EDProducer("CandViewCombiner",
                         decay = cms.string("isolatedMuons@+ allTracks@-"),
                         cut = cms.string("86.0 < mass < 98.0"),
                         name = cms.string('zToMuMu'),
                         roles = cms.vstring('tag', 'probe')
                         
)

#Extract the probed tracks
probes = cms.EDProducer('TagAndProbe',
                        src = cms.InputTag('diMuons')
)                        



analysis = cms.EDAnalyzer('MuonEffAnalyzer',
                                       src = cms.InputTag('analysisMuons'),
                                       ref = cms.InputTag('probes'),
                                       vertices = cms.InputTag('offlinePrimaryVertices'),
                                       FileName = cms.string("tagAndProbe.root"),
                                       TriggerPath = cms.string("HLT_Mu9"),
                                       MatchDR = cms.untracked.double(0.3)
)                                       


tagAndProbe = cms.Sequence(globalMuons*
                              muonsPtCut*
                              isolatedMuons*
                              allTracks*
                              diMuons*
                              probes*
                              analysis)



           



                         
    


    


