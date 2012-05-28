# GEN LEVEL SKIMMING #
import FWCore.ParameterSet.Config as cms
#
#genParticlesFromZs = cms.EDFilter("GenParticlePruner",
#                                      src = cms.InputTag("genParticles"),
#                                    select = cms.vstring(
#                                        "drop * ", # this is the default
#                                        "keep+ pdgId = {Z0}",
#                                        "drop pdgId = {Z0}"
#                                    )
#)


#genTausFromZs = cms.EDFilter("GenParticlePruner",
#                                 src = cms.InputTag("genParticlesFromZs"),
#                                 select = cms.vstring(
#                                      "drop * ", # this is the default
#                                      "keep pdgId = {tau-}",
#                                      "keep pdgId = {tau+}"
#                                 )
#)

generatedMuons = cms.EDFilter("TauGenJetDecayModeSelector",
                              src = cms.InputTag("tauGenJets"),
                              select = cms.vstring('muon'),
                              filter = cms.bool(True)
)


generatedTaus = cms.EDFilter("TauGenJetDecayModeSelector",
                             src = cms.InputTag("tauGenJets"),
                             select = cms.vstring('oneProng0Pi0', 'oneProng1Pi0', 'oneProng2Pi0', 'oneProngOther',
                                                  'threeProng0Pi0', 'threeProng1Pi0', 'threeProngOther', 'rare'),
                             filter = cms.bool(True)
)

generatedTausAndElectrons = cms.EDFilter("TauGenJetDecayModeSelector",
                             src = cms.InputTag("tauGenJets"),
                             select = cms.vstring('oneProng0Pi0', 'oneProng1Pi0', 'oneProng2Pi0', 'oneProngOther',
                                                  'threeProng0Pi0', 'threeProng1Pi0', 'threeProngOther', 'rare','electron'),
                             filter = cms.bool(True)
)



branchingRatioCounter = cms.EDFilter('EventCounter',
                           name = cms.string("MCMuTauEvents")
                           )


generatedMuonsInAcceptance = cms.EDFilter("GenJetSelector",
                                          src = cms.InputTag("generatedMuons"),
                                          cut = cms.string('pt > 15.&&abs(eta)<2.1'),
                                          filter = cms.bool(True)
)
generatedTausInAcceptance = cms.EDFilter("GenJetSelector",
                                          src = cms.InputTag("generatedTaus"),
                                          cut = cms.string('pt > 15.&&abs(eta)<2.4'),
                                          filter = cms.bool(True)
)

phaseSpaceCounter = cms.EDFilter('EventCounter',
                           name = cms.string("MCSkimmedEvents")
)



skimGenerator = cms.Sequence(
    generatedMuons*
    generatedTaus*
    branchingRatioCounter
#    generatedMuonsInAcceptance*
#    generatedTausInAcceptance*
#    phaseSpaceCounter
)

skimGeneratorWithElectron = cms.Sequence(
    generatedMuons*
    generatedTausAndElectrons*
    branchingRatioCounter
#    generatedMuonsInAcceptance*
#    generatedTausInAcceptance*
#    phaseSpaceCounter
)
    



