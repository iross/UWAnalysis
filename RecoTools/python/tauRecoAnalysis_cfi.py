import FWCore.ParameterSet.Config as cms

from  PhysicsTools.JetMCAlgos.TauGenJets_cfi import *

HPSDiscriminators = cms.VInputTag(
    cms.InputTag("hpsPFTauDiscriminationByDecayModeFinding"),
    cms.InputTag("hpsPFTauDiscriminationByVLooseIsolation"),
    cms.InputTag("hpsPFTauDiscriminationByLooseIsolation"),
    cms.InputTag("hpsPFTauDiscriminationByMediumIsolation"),
    cms.InputTag("hpsPFTauDiscriminationByTightIsolation"),
    cms.InputTag("hpsPFTauDiscriminationAgainstMuon"),
    cms.InputTag("hpsPFTauDiscriminationAgainstElectron")
)                     
                     


generatedTaus = cms.EDFilter("TauGenJetDecayModeSelector",
    src = cms.InputTag("tauGenJets"),
    select = cms.vstring('oneProng0Pi0', 'oneProng1Pi0', 'oneProng2Pi0', 'oneProngOther','threeProng0Pi0', 'threeProng1Pi0', 'threeProngOther', 'rare'),
    filter = cms.bool(False)
)
generatedMuons = cms.EDFilter("TauGenJetDecayModeSelector",
   src = cms.InputTag("tauGenJets"),
   select = cms.vstring('muon'),
   filter = cms.bool(False)
)
generatedElectrons = cms.EDFilter("TauGenJetDecayModeSelector",
    src = cms.InputTag("tauGenJets"),
    select = cms.vstring('electron'),
    filter = cms.bool(False)
)

generatedMuonsInAcceptance = cms.EDFilter("GenJetSelector",
    src = cms.InputTag("generatedMuons"),
    cut = cms.string('pt > 5.&&abs(eta)<2.4'),
    filter = cms.bool(False)
)
generatedTausInAcceptance = cms.EDFilter("GenJetSelector",
    src = cms.InputTag("generatedTaus"),
    cut = cms.string('pt > 5.&&abs(eta)<2.4'),
    filter = cms.bool(False)
)
generatedElectronsInAcceptance = cms.EDFilter("GenJetSelector",
    src = cms.InputTag("generatedElectrons"),
    cut = cms.string('pt > 5.&&abs(eta)<2.4'),
    filter = cms.bool(False)
)

tauAnalysis =cms.EDAnalyzer('TauEffAnalyzer',
    src     = cms.InputTag("hpsPFTauProducer"),
    ref     = cms.InputTag("generatedTausInAcceptance"),
    stripCandidatesPdgIds        = cms.vint32(22,11),
    stripEtaAssociationDistance  = cms.double(0.05),
    stripPhiAssociationDistance  = cms.double(0.2),
    stripPtThreshold             = cms.double(1.0),
    Discriminators = HPSDiscriminators,
    FileName = cms.string("TauEfficiency.root")
)

tauAnalysisMu =cms.EDAnalyzer('TauEffAnalyzer',
    src     = cms.InputTag("hpsPFTauProducer"),
    ref     = cms.InputTag("generatedMuonsInAcceptance"),
    stripCandidatesPdgIds        = cms.vint32(22,11),
    stripEtaAssociationDistance  = cms.double(0.05),
    stripPhiAssociationDistance  = cms.double(0.2),
    stripPtThreshold             = cms.double(1.0),
    Discriminators = HPSDiscriminators,
    FileName = cms.string("TauEfficiencyMu.root")
)

tauAnalysisEle =cms.EDAnalyzer('TauEffAnalyzer',
    src     = cms.InputTag("hpsPFTauProducer"),
    ref     = cms.InputTag("generatedElectronsInAcceptance"),
    stripCandidatesPdgIds        = cms.vint32(22,11),
    stripEtaAssociationDistance  = cms.double(0.05),
    stripPhiAssociationDistance  = cms.double(0.2),
    stripPtThreshold             = cms.double(1.0),
    Discriminators = HPSDiscriminators,
    FileName = cms.string("TauEfficiencyEle.root")
)


generatedJetsInAcceptance = cms.EDFilter("GenJetSelector",
    src = cms.InputTag("antikt5GenJets"),
    cut = cms.string('pt > 5.&&abs(eta)<2.4'),
    filter = cms.bool(False)
)

tauAnalysisQCD =cms.EDAnalyzer('TauEffAnalyzer',
      src     = cms.InputTag("hpsPFTauProducer"),
      ref     = cms.InputTag("generatedJetsInAcceptance"),
      stripCandidatesPdgIds        = cms.vint32(22,11),
      stripEtaAssociationDistance  = cms.double(0.05),
      stripPhiAssociationDistance  = cms.double(0.2),
      stripPtThreshold             = cms.double(1.0),
      Discriminators = HPSDiscriminators,
      FileName = cms.string("TauEfficiencyQCD.root")
)



standardTauAnalysis =cms.EDAnalyzer('TauEffAnalyzer',
     src     = cms.InputTag("shrinkingConePFTauProducer"),
     ref     = cms.InputTag("generatedTausInAcceptance"),
     stripCandidatesPdgIds        = cms.vint32(22,11),
     stripEtaAssociationDistance  = cms.double(0.05),
     stripPhiAssociationDistance  = cms.double(0.2),
     stripPtThreshold             = cms.double(1.0),
     Discriminators = cms.VInputTag(
    cms.InputTag("shrinkingConePFTauDiscriminationByTaNCfrOnePercent"),
    cms.InputTag("shrinkingConePFTauDiscriminationByTaNCfrQuarterPercent")
),
    FileName = cms.string("TauEfficiency-STD.root")

)
standardTauAnalysisQCD =cms.EDAnalyzer('TauEffAnalyzer',
 src     = cms.InputTag("shrinkingConePFTauProducer"),
 ref     = cms.InputTag("generatedJetsInAcceptance"),
 stripCandidatesPdgIds        = cms.vint32(22,11),
 stripEtaAssociationDistance  = cms.double(0.05),
 stripPhiAssociationDistance  = cms.double(0.2),
 stripPtThreshold             = cms.double(1.0),
 Discriminators = cms.VInputTag(
   cms.InputTag("shrinkingConePFTauDiscriminationByTaNCfrOnePercent"),
   cms.InputTag("shrinkingConePFTauDiscriminationByTaNCfrTenthPercent")
 ),
  FileName = cms.string("TauEfficiency-STD-QCD.root")
)




TauEfficiency = cms.Sequence(     tauGenJets*
                                  generatedTaus*
                            
#                                  generatedMuons*
#                                  generatedElectrons*
                                  generatedTausInAcceptance*
#                                  generatedMuonsInAcceptance*
#                                  generatedElectronsInAcceptance*
                                  tauAnalysis
#                                  tauAnalysisMu*
#                                  tauAnalysisEle*
#                                  standardTauAnalysis
)

TauFakeRate            = cms.Sequence(generatedJetsInAcceptance+
                                      tauAnalysisQCD+
                                      standardTauAnalysisQCD)

TauFakeRateDATA            = cms.Sequence(tauAnalysisQCD)
#                                          standardTauAnalysisQCD)



