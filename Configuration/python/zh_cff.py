import FWCore.ParameterSet.Config as cms

from UWAnalysis.Configuration.tools.CutSequenceProducer import *

MC2011TriggerPaths=["HLT_Mu17_Mu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]
DATA2011TriggerPaths=["HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL","HLT_Mu17_Mu8","HLT_DoubleMu7","HLT_Mu13_Mu8"]
DATAMC2012TriggerPaths=["HLT_Mu17_Mu8","HLT_Mu17_TkMu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]

#todo: switch all definitions to ZH. Ugh.

#MM
ZMM = CutSequenceProducer(initialCounter  = 'initialEventsZMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
ZMM.addDiCandidateModule('ZMMInit','PATMuPairProducer', 'goodPatMuons','goodPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
ZMM.addSelector('ZMMSel','PATMuPairSelector','mass>40&&charge==0&&leg1.pfCandidateRef().isNonnull()&&leg1.isGlobalMuon()||leg1.isTrackerMuon()&&abs(leg1.eta())<2.4&&leg2.pfCandidateRef().isNonnull()&&leg2.isGlobalMuon()||leg2.isTrackerMuon()&&abs(leg2.eta())<2.4  ','one Z1 mmm',1)
ZMM.addSelector('ZMMIso','PATMuPairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','MMMLeadingZMuIso')
ZMM.addSorter('ZMMFinal',"PATMuPairSorter")
ZMMSeq = ZMM.returnSequence()

#EE
ZEE = CutSequenceProducer(initialCounter  = 'initialEventsZEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
ZEE.addDiCandidateModule('ZEEInit','PATElePairProducer', 'mvaedElectrons','mvaedElectrons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
ZEE.addSelector('ZEESel','PATElePairSelector','mass>40&&charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2','one Z1 eem',1)
ZEE.addSelector('ZEEIso','PATElePairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','EEMLeadingZMuIso')
ZEE.addSorter('ZEEFinal',"PATElePairSorter")
ZEESeq = ZEE.returnSequence()

######################__________________________________MMMT_____________________________________##############################

MMMTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
MMMTanalysisConfigurator.addHLTFilter("MMMTHLT",DATAMC2012TriggerPaths,"HLT_req_MMMT")

MMMTanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','cleanPatElectrons','selectedPatJets','MMMT')
MMMTanalysisConfigurator.addDiCandidateModule('MMMTdiMuons','PATMuPairProducer', 'smearedMuonsMMMT','smearedMuonsMMMT','smearedMETMMMT','smearedJetsMMMT',1,genParticles='genDaughters')
MMMTanalysisConfigurator.addSelector('MMMTosDiMuons','PATMuPairSelector','charge==0&&leg1.pfCandidateRef().isNonnull()&&leg1.isGlobalMuon()||leg1.isTrackerMuon()&&abs(leg1.eta())<2.4&&leg2.pfCandidateRef().isNonnull()&&leg2.isGlobalMuon()||leg2.isTrackerMuon()&&abs(leg2.eta())<2.4  ','MMMTDiMuonCreation',1)
MMMTanalysisConfigurator.addSelector('MMMTosDiMuonsIso','PATMuPairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','MMMTDiMuonIso',1)
MMMTanalysisConfigurator.addDiCandidateModule('MMMTmuTau','PATMuTauPairProducer', 'smearedMuonsMMMT','smearedTausMMMT','smearedMETMMMT','smearedJetsMMMT',1,9999,text = 'MMMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
MMMTanalysisConfigurator.addDiCandidateModule('MMMTzzCands','PATMuMuMuTauQuadProducer','MMMTosDiMuons','MMMTmuTau','smearedMETMMMT','smearedJetsMMMT',1,9999,text='MMMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMMTanalysisConfigurator.addCrossCleanerModule('MMMTzzCleanedCands','PATMuMuMuTauQuadCrossCleaner',1,9999,text='MMMTAtLeastOneZZCleanedCandidate',dR = 0.1)
#just loose PF?
MMMTanalysisConfigurator.addSelector('MMMTzzMuID2','PATMuMuMuTauQuadSelector','leg2.leg1.pfCandidateRef().isNonnull()&&abs(leg2.leg1.eta())<2.4 ','MMMTSecondZMuID')
MMMTanalysisConfigurator.addSelector('MMMTzzMuIso2','PATMuMuMuTauQuadSelector','(leg2.leg1.userIso(0)+max(leg2.leg1.userIso(1)+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(2),0.0))/leg2.leg1.pt()<0.15','MMMTSecondZMuIso')

MMMTanalysisConfigurator.addSelector('MMMTzzTauID','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")&&abs(leg2.leg2.eta())<2.3','MMMTTauDecayModeFinding')
MMMTanalysisConfigurator.addSelector('MMMTzzTauDiscr','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonTight")','MMMTTauLeptonDiscrimantor')
MMMTanalysisConfigurator.addSelector('MMMTzzTauIso','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")','MMMTTauMedIsolationMVA')

MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsMuTauQ','PATMuMuMuTauQuadSelector','leg2.charge()==0','MMMTMuTauCharge')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsAboveThreshold','PATMuMuMuTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20','MMMTAtLeastOneZZCandOverThresholds')

#vertex compatibility?
#MMMTanalysisConfigurator.addSelector('MMMTzzdZ','PATMuMuMuTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','MMMTdZ')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsMMMass','PATMuMuMuTauQuadSelector','leg1.mass()>71&&leg1.mass()<111','MMMTMMMass')
MMMTanalysisConfigurator.addQuadEmbedder('MMMTEmbedder','PATMuMuMuTauQuadEmbedder')
MMMTanalysisConfigurator.addSorter('MMMTFinalSel','PATMuMuMuTauQuadSorterByZMass')
#create the sequence
MMMTselectionSequence =MMMTanalysisConfigurator.returnSequence()

######################__________________________________MMTT_____________________________________##############################

MMTTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMTT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
MMTTanalysisConfigurator.addHLTFilter("MMTTHLT",DATAMC2012TriggerPaths,"HLT_reqMMTT")

MMTTanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','cleanPatElectrons','selectedPatJets','MMTT')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiMuons','PATMuPairProducer', 'smearedMuonsMMTT','smearedMuonsMMTT','smearedMETMMTT','smearedJetsMMTT',1,genParticles='genDaughters')
MMTTanalysisConfigurator.addSelector('MMTTosDiMuons','PATMuPairSelector','charge==0&&leg1.pfCandidateRef().isNonnull()&&leg1.isGlobalMuon()||leg1.isTrackerMuon()&&abs(leg1.eta())<2.4&&leg2.pfCandidateRef().isNonnull()&&leg2.isGlobalMuon()||leg2.isTrackerMuon()&&abs(leg2.eta())<2.4  ','MMTTDiMuonCreation',1)
MMTTanalysisConfigurator.addSelector('MMTTosDiMuonsIso','PATMuPairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','MMTTDiMuonIso',1)
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiTaus','PATDiTauPairProducer','smearedTausMMTT','smearedTausMMTT','smearedMETMMTT','smearedJetsMMTT',1,9999,text='MMTTAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTzzCands','PATMuMuTauTauQuadProducer','MMTTosDiMuons','MMTTdiTaus','smearedMETMMTT','smearedJetsMMTT',1,9999,text='MMTTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMTTanalysisConfigurator.addCrossCleanerModule('MMTTzzCleanedCands','PATMuMuTauTauQuadCrossCleaner',1,9999,text='MMTTAtLeastOneZZCleanedCandidate',dR = 0.1) 

MMTTanalysisConfigurator.addSelector('MMTTzzTauID','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")&&abs(leg2.leg1.eta())<2.3&&abs(leg2.leg2.eta())<2.3','MMTTDecayModeFinding')
MMTTanalysisConfigurator.addSelector('MMTTzzTauDiscr','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("againstElectronMedium")&&leg2.leg1.tauID("againstMuonMedium")&&leg2.leg2.tauID("againstElectronMedium")&&leg2.leg2.tauID("againstMuonMedium")','MMTTTauLeptonDiscrimantor')
MMTTanalysisConfigurator.addSelector('MMTTzzTauIso','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("byTightIsolationMVA")&&leg2.leg2.tauID("byTightCombinedIsolationDeltaBetaCorr")','MMTTTauIsolation')
MMTTanalysisConfigurator.addSorter('MMTTzzCleanedCandsSortedByZMass','PATMuMuTauTauQuadSorterByZMass')
#vertex compatibility req
#MMTTanalysisConfigurator.addSelector('MMTTzzdZ','PATMuMuTauTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','MMTTdZ')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsAboveThreshold','PATMuMuTauTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>20 &&leg2().leg2().pt()>20','MMTTAtLeastOneZZCandOverThresholds')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsTauTauQ','PATMuMuTauTauQuadSelector','leg2.charge()==0','TauTauChargeMMTT')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsMMMass','PATMuMuTauTauQuadSelector','leg1.mass()>71&&leg1.mass()<111','MMTTMMMass')
MMTTanalysisConfigurator.addQuadEmbedder('MMTTEmbedder','PATMuMuTauTauQuadEmbedder')
MMTTanalysisConfigurator.addSorter('MMTTFinalSel','PATMuMuTauTauQuadSorterByZMass')
MMTTselectionSequence =MMTTanalysisConfigurator.returnSequence()


######################__________________________________MMET_____________________________________##############################

MMETanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMET',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

MMETanalysisConfigurator.addHLTFilter("MMETHLT",DATAMC2012TriggerPaths,"HLT_reqMMET")
MMETanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','cleanPatElectrons','selectedPatJets','MMET')
MMETanalysisConfigurator.addDiCandidateModule('MMETdiMuons','PATMuPairProducer', 'smearedMuonsMMET','smearedMuonsMMET','smearedMETMMET','smearedJetsMMET',1,genParticles='genDaughters')
MMETanalysisConfigurator.addSelector('MMETosDiMuons','PATMuPairSelector','charge==0&&leg1.pfCandidateRef().isNonnull()&&leg1.isGlobalMuon()||leg1.isTrackerMuon()&&abs(leg1.eta())<2.4&&leg2.pfCandidateRef().isNonnull()&&leg2.isGlobalMuon()||leg2.isTrackerMuon()&&abs(leg2.eta())<2.4 ','MMETDiMuonCreation',1)
MMETanalysisConfigurator.addSelector('MMETosDiMuonsIso','PATMuPairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','MMETDiMuonIso',1)
MMETanalysisConfigurator.addDiCandidateModule('MMETelecTau','PATEleTauPairProducer','smearedElectronsMMET','smearedTausMMET','smearedMETMMET','smearedJetsMMET',1,9999,text='MMETAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addDiCandidateModule('MMETzzCands','PATMuMuEleTauQuadProducer','MMETosDiMuons','MMETelecTau','smearedMETMMET','smearedJetsMMET',1,9999,text='MMETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addCrossCleanerModule('MMETzzCleanedCands2','PATMuMuEleTauQuadCrossCleaner',1,9999,text='MMETAtLeastOneZZCleanedCandidate',dR = 0.1)
MMETanalysisConfigurator.addSelector('MMETzzCleanedEleID','PATMuMuEleTauQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<1&&abs(leg2.leg1.eta())<2.5','MMETEleID')
MMETanalysisConfigurator.addSelector('MMETzzCleanedEleIso','PATMuMuEleTauQuadSelector','(leg2.leg1.userIso(0)+max(leg2.leg1.userIso(1)+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(2),0.0))/leg2.leg1.pt()<0.10','MMETEleIso')

MMETanalysisConfigurator.addSelector('MMETzzTauID','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")&&abs(leg2.leg2.eta())<2.3','MMETDecayModeFinding')
MMETanalysisConfigurator.addSelector('MMETzzTauDiscr','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("againstElectronMVA")&&leg2.leg2.tauID("againstMuonLoose")','MMETTauLeptonDiscrimantor')
MMETanalysisConfigurator.addSelector('MMETzzTauIso','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")','MMETTauLooseIsolation')

MMETanalysisConfigurator.addSorter('MMETzzCleanedCandsSortedByZMass','PATMuMuEleTauQuadSorterByZMass')
#MMETanalysisConfigurator.addSelector('MMETzzdZ','PATMuMuEleTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','MMETdZ')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsAboveThreshold','PATMuMuEleTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20','MMETAtLeastOneZZCandOverThresholds')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsETauQ','PATMuMuEleTauQuadSelector','leg2.charge()==0','MMETEleTauCharge')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsMMMass','PATMuMuEleTauQuadSelector','leg1.mass()>71&&leg1.mass()<111','MMETMMMass')
MMETanalysisConfigurator.addQuadEmbedder('MMETEmbedder','PATMuMuEleTauQuadEmbedder')
MMETanalysisConfigurator.addSorter('MMETFinalSel','PATMuMuEleTauQuadSorterByZMass')
MMETselectionSequence =MMETanalysisConfigurator.returnSequence()


######################__________________________________MMEM_____________________________________##############################

MMEManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEM',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

MMEManalysisConfigurator.addHLTFilter("MMEMHLT",DATAMC2012TriggerPaths,"HLT_reqMMEM")
MMEManalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','cleanPatElectrons','selectedPatJets','MMEM')
MMEManalysisConfigurator.addDiCandidateModule('MMEMdiMuons','PATMuPairProducer', 'smearedMuonsMMEM','smearedMuonsMMEM','smearedMETMMEM','smearedJetsMMEM',1,genParticles='genDaughters')
MMEManalysisConfigurator.addSelector('MMEMosDiMuons','PATMuPairSelector','charge==0&&leg1.pfCandidateRef().isNonnull()&&leg1.isGlobalMuon()||leg1.isTrackerMuon()&&abs(leg1.eta())<2.4&&leg2.pfCandidateRef().isNonnull()&&leg2.isGlobalMuon()||leg2.isTrackerMuon()&&abs(leg2.eta())<2.4  ','MMEMDiMuonCreation',1)
MMEManalysisConfigurator.addSelector('MMEMosDiMuonsIso','PATMuPairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','MMEMDiMuonIso',1)
MMEManalysisConfigurator.addDiCandidateModule('MMEMelecMu','PATEleMuPairProducer','smearedElectronsMMEM','smearedMuonsMMEM','smearedMETMMEM','smearedJetsMMEM',1,9999,text='MMEMAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addDiCandidateModule('MMEMzzCands','PATMuMuEleMuQuadProducer','MMEMosDiMuons','MMEMelecMu','smearedMETMMEM','smearedJetsMMEM',1,9999,text='MMEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addCrossCleanerModule('MMEMzzCleanedCands','PATMuMuEleMuQuadCrossCleaner',1,9999,text='MMEMAtLeastOneZZCleanedCandidate',dR = 0.1)

MMEManalysisConfigurator.addSelector('MMEMzzCleanedThirdMuID','PATMuMuEleMuQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&abs(leg2.leg1.eta())<2.5','MMEMThirdMuID')
MMEManalysisConfigurator.addSelector('MMEMzzEleIso','PATMuMuEleMuQuadSelector','(leg2.leg1.userIso(0)+max(leg2.leg1.userIso(1)+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(2),0.0))/leg2.leg1.pt()<0.25','MMEMEleIso')
MMEManalysisConfigurator.addSelector('MMEMzzMuID2','PATMuMuEleMuQuadSelector','leg2.leg2.pfCandidateRef().isNonnull()&&abs(leg2.leg2.eta())<2.4 ','MMEMMuIso')
MMEManalysisConfigurator.addSelector('MMEMzzMuIso2','PATMuMuEleMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho2012")*leg2.leg2.userFloat("effArea")))/leg2.leg2.pt<0.25','MMEMMuIso')
MMEManalysisConfigurator.addSorter('MMEMzzCleanedCandsSortedByZMass','PATMuMuEleMuQuadSorterByZMass')
#MMEManalysisConfigurator.addSelector('MMEMzzdZ','PATMuMuEleMuQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','MMEMdZ')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedCandsAboveThreshold','PATMuMuEleMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 && leg2().leg2().pt()>10','MMEMAtLeastOneZZCandOverThresholds')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedCandsEMuQ','PATMuMuEleMuQuadSelector','leg2.charge()==0','MMEMEleMuCharge')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedCandsMMMass','PATMuMuEleMuQuadSelector','leg1.mass()>71&&leg1.mass()<111','MMEMMMMass')
MMEManalysisConfigurator.addQuadEmbedder('MMEMEmbedder','PATMuMuEleMuQuadEmbedder')
MMEManalysisConfigurator.addSorter('MMEMFinalSel','PATMuMuEleMuQuadSorterByZMass')
MMEMselectionSequence =MMEManalysisConfigurator.returnSequence()

######################__________________________________EEMT_____________________________________##############################

EEMTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEMT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

EEMTanalysisConfigurator.addHLTFilter("EEMTHLT",DATAMC2012TriggerPaths,"HLT_reqEEMT")
EEMTanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','cleanPatElectrons','selectedPatJets','EEMT')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTdiElectrons','PATElePairProducer', 'smearedElectronsEEMT','smearedElectronsEEMT','smearedMETEEMT','smearedJetsEEMT',1,genParticles='genDaughters')

EEMTanalysisConfigurator.addSelector('EEMTosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&abs(leg1.eta())<2.5&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&abs(leg2.eta())<2.5','EEMTDiEleCreation',1)
EEMTanalysisConfigurator.addSelector('EEMTosDiElectronsIso','PATElePairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','EEMTDiEleIso',1)
EEMTanalysisConfigurator.addDiCandidateModule('EEMTmuTau','PATMuTauPairProducer', 'smearedMuonsEEMT','smearedTausEEMT','smearedMETEEMT','smearedJetsEEMT',1,9999,text = 'EEMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTzzCands','PATEleEleMuTauQuadProducer','EEMTosDiElectrons','EEMTmuTau','smearedMETEEMT','smearedJetsEEMT',1,9999,text='EEMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEMTanalysisConfigurator.addCrossCleanerModule('EEMTzzCleanedCands','PATEleEleMuTauQuadCrossCleaner',1,9999,text='EEMTAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMTanalysisConfigurator.addSelector('EEMTzzMuID2','PATEleEleMuTauQuadSelector','leg2.leg1.pfCandidateRef().isNonnull()&&abs(leg2.leg1.eta())<2.4 ','EEMTSecondZMuID')
EEMTanalysisConfigurator.addSelector('EEMTzzMuIso2','PATEleEleMuTauQuadSelector','(leg2.leg1.userIso(0)+max(leg2.leg1.userIso(1)+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(2),0.0))/leg2.leg1.pt()<0.15','EEMTSecondZMuIso')

EEMTanalysisConfigurator.addSelector('EEMTzzTauID','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")&&abs(leg2.leg2.eta())<2.3','EEMTTauDecayModeFinding')
EEMTanalysisConfigurator.addSelector('EEMTzzTauDiscr','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonTight")','EEMTTauLeptonDiscrimantor')
EEMTanalysisConfigurator.addSelector('EEMTzzTauIso','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")','EEMTTauMedIsolationMVA')

EEMTanalysisConfigurator.addSorter('EEMTzzCleanedCandsSortedByZMass','PATEleEleMuTauQuadSorterByZMass')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsAboveThreshold','PATEleEleMuTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20','EEMTAtLeastOneZZCandOverThresholds')
#EEMTanalysisConfigurator.addSelector('EEMTzzdZ','PATEleEleMuTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EEMTdZ')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsMuTauQ','PATEleEleMuTauQuadSelector','leg2.charge()==0','EEMTMuTauCharge')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsEEMass','PATEleEleMuTauQuadSelector','leg1.mass()>71&&leg1.mass()<111','EEMTEEMass')
EEMTanalysisConfigurator.addQuadEmbedder('EEMTEmbedder','PATEleEleMuTauQuadEmbedder')
EEMTanalysisConfigurator.addSorter('EEMTFinalSel','PATEleEleMuTauQuadSorterByZMass')
EEMTselectionSequence =EEMTanalysisConfigurator.returnSequence()





######################__________________________________EEET_____________________________________##############################

EEETanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEET',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

EEETanalysisConfigurator.addHLTFilter("EEETHLT",DATAMC2012TriggerPaths,"HLT_reqEEET")
EEETanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','cleanPatElectrons','selectedPatJets','EEET')
EEETanalysisConfigurator.addDiCandidateModule('EEETdiElectrons','PATElePairProducer', 'smearedElectronsEEET','smearedElectronsEEET','smearedMETEEET','smearedJetsEEET',1,genParticles='genDaughters')
EEETanalysisConfigurator.addSelector('EEETosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&abs(leg1.eta())<2.5&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&abs(leg2.eta())<2.5','EEETDiEleCreation',1)
EEETanalysisConfigurator.addSelector('EEETosDiMuonsIso','PATElePairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','EEETDiEleIso',1)
EEETanalysisConfigurator.addDiCandidateModule('EEETeleTau','PATEleTauPairProducer', 'smearedElectronsEEET','smearedTausEEET','smearedMETEEET','smearedJetsEEET',1,9999,text = 'EEETAtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETanalysisConfigurator.addDiCandidateModule('EEETzzCands','PATEleEleEleTauQuadProducer','EEETosDiElectrons','EEETeleTau','smearedMETEEET','smearedJetsEEET',1,9999,text='EEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEETanalysisConfigurator.addCrossCleanerModule('EEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='EEETAtLeastOneZZCleanedCandidate',dR = 0.1)

EEETanalysisConfigurator.addSelector('EEETzzCleanedEleID','PATEleEleEleTauQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<1&&abs(leg2.leg1.eta())<2.5','EEETEleID')
EEETanalysisConfigurator.addSelector('EEETzzCleanedEleIso','PATEleEleEleTauQuadSelector','(leg2.leg1.userIso(0)+max(leg2.leg1.userIso(1)+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(2),0.0))/leg2.leg1.pt()<0.10','EEETEleIso')

EEETanalysisConfigurator.addSelector('EEETzzTauID','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")&&abs(leg2.leg2.eta())<2.3','EEETDecayModeFinding')
EEETanalysisConfigurator.addSelector('EEETzzTauDiscr','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("againstElectronMVA")&&leg2.leg2.tauID("againstMuonLoose")','EEETTauLeptonDiscrimantor')
EEETanalysisConfigurator.addSelector('EEETzzTauIso','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")','EEETTauLooseIsolation')
EEETanalysisConfigurator.addSorter('EEETzzCleanedCandsSortedByZMass','PATEleEleEleTauQuadSorterByZMass')
#EEETanalysisConfigurator.addSelector('EEETzzdZ','PATEleEleEleTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EEETdZ')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsAboveThreshold','PATEleEleEleTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20','EEETAtLeastOneZZCandOverThresholds')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsETauQ','PATEleEleEleTauQuadSelector','leg2.charge()==0','EEETEleTauCharge')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsMMMass','PATEleEleEleTauQuadSelector','leg1.mass()>71&&leg1.mass()<111','EEETMMMass')
EEETanalysisConfigurator.addQuadEmbedder('EEETEmbedder','PATEleEleEleTauQuadEmbedder')
EEETanalysisConfigurator.addSorter('EEETFinalSel','PATEleEleEleTauQuadSorterByZMass')
EEETselectionSequence =EEETanalysisConfigurator.returnSequence()


######################__________________________________EETT_____________________________________##############################

EETTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEETT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

EETTanalysisConfigurator.addHLTFilter("EETTHLT",DATAMC2012TriggerPaths,"HLT_reqEETT")
EETTanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','cleanPatElectrons','selectedPatJets','EETT')
EETTanalysisConfigurator.addDiCandidateModule('EETTdiElectrons','PATElePairProducer', 'smearedElectronsEETT','smearedElectronsEETT','smearedMETEETT','smearedJetsEETT',1,genParticles='genDaughters')
EETTanalysisConfigurator.addSelector('EETTosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&abs(leg1.eta())<2.5&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&abs(leg2.eta())<2.5','EETTDiEleCreation',1)
EETTanalysisConfigurator.addSelector('EETTosDiMuonsIso','PATElePairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','EETTDiEleIso',1)
EETTanalysisConfigurator.addDiCandidateModule('EETTtauTau','PATDiTauPairProducer', 'smearedTausEETT','smearedTausEETT','smearedMETEETT','smearedJetsEETT',1,9999,text = 'EETTAtLeastOnediTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EETTanalysisConfigurator.addDiCandidateModule('EETTzzCands','PATEleEleTauTauQuadProducer','EETTosDiElectrons','EETTtauTau','smearedMETEETT','smearedJetsEETT',1,9999,text='EETTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EETTanalysisConfigurator.addCrossCleanerModule('EETTzzCleanedCands','PATEleEleTauTauQuadCrossCleaner',1,9999,text='EETTAtLeastOneZZCleanedCandidate',dR = 0.1)


EETTanalysisConfigurator.addSelector('EETTzzTauID','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")&&abs(leg2.leg1.eta())<2.3&&abs(leg2.leg2.eta())<2.3','EETTDecayModeFinding')
EETTanalysisConfigurator.addSelector('EETTzzTauDiscr','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("againstElectronMedium")&&leg2.leg1.tauID("againstMuonMedium")&&leg2.leg2.tauID("againstElectronMedium")&&leg2.leg2.tauID("againstMuonMedium")','EETTTauLeptonDiscrimantor')
EETTanalysisConfigurator.addSelector('EETTzzTauIso','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("byTightCombinedIsolationDeltaBetaCorr")&&leg2.leg2.tauID("byTightCombinedIsolationDeltaBetaCorr")','EETTTauIsolation')
EETTanalysisConfigurator.addSorter('EETTzzCleanedCandsSortedByZMass','PATEleEleTauTauQuadSorterByZMass')
#EETTanalysisConfigurator.addSelector('EETTzzdZ','PATEleEleTauTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EETTdZ')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsAboveThreshold','PATEleEleTauTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>20 &&leg2().leg2().pt()>20','EETTAtLeastOneZZCandOverThresholds')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsTauTauQ','PATEleEleTauTauQuadSelector','leg2.charge()==0','TauTauChargeEETT')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsMMMass','PATEleEleTauTauQuadSelector','leg1.mass()>71&&leg1.mass()<111','EETTMMMass')
EETTanalysisConfigurator.addQuadEmbedder('EETTEmbedder','PATEleEleTauTauQuadEmbedder')
EETTanalysisConfigurator.addSorter('EETTFinalSel','PATEleEleTauTauQuadSorterByZMass')
EETTselectionSequence =EETTanalysisConfigurator.returnSequence()

######################__________________________________EEEM_____________________________________##############################

EEEManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEM',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
EEEManalysisConfigurator.addHLTFilter("EEEMHLT",DATAMC2012TriggerPaths,"HLT_reqEEEM")
EEEManalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','cleanPatElectrons','selectedPatJets','EEEM')
EEEManalysisConfigurator.addDiCandidateModule('EEEMdiElectrons','PATElePairProducer', 'smearedElectronsEEEM','smearedElectronsEEEM','smearedMETEEEM','smearedJetsEEEM',1,genParticles='genDaughters')
EEEManalysisConfigurator.addSelector('EEEMosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&abs(leg1.eta())<2.5&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&abs(leg2.eta())<2.5','EEEMDiEleCreation',1)
EEEManalysisConfigurator.addSelector('EEEMosDiMuonsIso','PATElePairSelector','(leg1.userIso(0)+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(2),0.0))/leg1.pt()<0.25&&(leg2.userIso(0)+max(leg2.userIso(1)+leg2.neutralHadronIso()-0.5*leg2.userIso(2),0.0))/leg2.pt()<0.25','EEEMDiEleIso',1)
EEEManalysisConfigurator.addDiCandidateModule('EEEMeleMu','PATEleMuPairProducer', 'smearedElectronsEEEM','smearedMuonsEEEM','smearedMETEEEM','smearedJetsEEEM',1,9999,text = 'EEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEEManalysisConfigurator.addDiCandidateModule('EEEMzzCands','PATEleEleEleMuQuadProducer','EEEMosDiElectrons','EEEMeleMu','smearedMETEEEM','smearedJetsEEEM',1,9999,text='EEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEEManalysisConfigurator.addCrossCleanerModule('EEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='EEEMAtLeastOneZZCleanedCandidate',dR = 0.1)

EEEManalysisConfigurator.addSelector('EEEMzzEleId','PATEleEleEleMuQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<1&&abs(leg2.leg1.eta())<2.5','EEEMEleCiCLoose') 
EEEManalysisConfigurator.addSelector('EEEMzzEleIso','PATEleEleEleMuQuadSelector','(leg2.leg1.userIso(0)+max(leg2.leg1.userIso(1)+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(2),0.0))/leg2.leg1.pt()<0.25','EEEMEleIso')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedThirdMuID','PATEleEleEleMuQuadSelector','leg2.leg2.pfCandidateRef().isNonnull()&&abs(leg2.leg2.eta())<2.4 ','EEEMThirdMuID')
EEEManalysisConfigurator.addSelector('EEEMzzMuIso2','PATEleEleEleMuQuadSelector','(leg2.leg2.userIso(0)+max(leg2.leg2.userIso(1)+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(2),0.0))/leg2.leg2.pt()<0.25','EEEMMuIso')
EEEManalysisConfigurator.addSorter('EEEMzzCleanedCandsSortedByZMass','PATEleEleEleMuQuadSorterByZMass')
#EEEManalysisConfigurator.addSelector('EEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EEEMdZ')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsAboveThreshold','PATEleEleEleMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 && leg2().leg2().pt()>10','EEEMAtLeastOneZZCandOverThresholds')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsEMuQ','PATEleEleEleMuQuadSelector','leg2.charge()==0','EEEMEleMuCharge')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsMMMass','PATEleEleEleMuQuadSelector','leg1.mass()>71&&leg1.mass()<111','EEEMMMMass')
EEEManalysisConfigurator.addQuadEmbedder('EEEMEmbedder','PATEleEleEleMuQuadEmbedder')
EEEManalysisConfigurator.addSorter('EEEMFinalSel','PATEleEleEleMuQuadSorterByZMass')
EEEMselectionSequence =EEEManalysisConfigurator.returnSequence()

#####################_______________________________EndOfConfigurators__________________________################################
