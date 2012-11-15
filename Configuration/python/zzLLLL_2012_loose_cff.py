import FWCore.ParameterSet.Config as cms

from UWAnalysis.Configuration.tools.CutSequenceProducer import *

MC2011TriggerPaths=["HLT_Mu17_Mu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]
DATA2011TriggerPaths=["HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL","HLT_Mu17_Mu8","HLT_DoubleMu7","HLT_Mu13_Mu8"]
DATAMC2012TriggerPaths=["HLT_Mu17_Mu8","HLT_Mu17_TkMu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Ele15_Ele8_Ele5_CaloIdL_TrkIdVL"]


#MM
ZMM = CutSequenceProducer(initialCounter  = 'initialEventsZMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
ZMM.addDiCandidateModule('ZMMInit','PATMuPairProducer', 'goodPatMuons','goodPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
ZMM.addSelector('ZMMSel','PATMuPairSelector','mass>40&&charge==0&&leg1.pfCandidateRef().isNonnull()&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&abs(leg1.eta())<2.4 && leg1.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.pfCandidateRef().isNonnull()&&(leg2.isGlobalMuon()||leg2.isTrackerMuon())&&abs(leg2.eta())<2.4 && leg2.pt()>5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 mmm',1)
ZMM.addSelector('ZMMIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40','MMMLeadingZMuIso')
ZMM.addSorter('ZMMFinal',"PATMuPairSorter")
ZMMSeq = ZMM.returnSequence()

#EE
ZEE = CutSequenceProducer(initialCounter  = 'initialEventsZEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
ZEE.addDiCandidateModule('ZEEInit','PATElePairProducer', 'mvaedElectrons','mvaedElectrons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
ZEE.addSelector('ZEESel','PATElePairSelector','mass>40&&charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 eem',1)
ZEE.addSelector('ZEEIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40','EEMLeadingZMuIso')
ZEE.addSorter('ZEEFinal',"PATElePairSorter")
ZEESeq = ZEE.returnSequence()

#MMM tri
MMMtri = CutSequenceProducer(initialCounter  = 'initialEventsMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMMtri.addHLTFilter("MMMHLT",DATAMC2012TriggerPaths,"MMM HLT_req")
MMMtri.addDiCandidateModule('triMMMdiMuons','PATMuPairProducer', 'goodPatMuons','goodPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
MMMtri.addSelector('triMMMosDiMuons','PATMuPairSelector','mass>40&&charge==0&&leg1.pfCandidateRef().isNonnull()&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&abs(leg1.eta())<2.4 && leg1.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.pfCandidateRef().isNonnull()&&(leg2.isGlobalMuon()||leg2.isTrackerMuon())&&abs(leg2.eta())<2.4 && leg2.pt()>5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 MMM',1)
MMMtri.addDiCandidateModule('triMMMzzCands','PATMuMuMuTriProducer','triMMMosDiMuons','goodPatMuons','systematicsMET','selectedPatJets',1,9999,text='MMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMMtri.addCrossCleanerModule('triMMMzzCleanedCands','PATMuMuMuTriCrossCleaner',1,9999,text='MMMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMtri.addSelector('triMMMzzMuIso','PATMuMuMuTriSelector','(leg1.leg1.chargedHadronIso()+max(0.0,leg1.leg1.neutralHadronIso()+leg1.leg1.photonIso()-leg1.leg1.userFloat("zzRho2012")*leg1.leg1.userFloat("effArea")))/leg1.leg1.pt<0.40 && (leg1.leg2.chargedHadronIso()+max(0.0,leg1.leg2.neutralHadronIso()+leg1.leg2.photonIso()-leg1.leg2.userFloat("zzRho2012")*leg1.leg2.userFloat("effArea")))/leg1.leg2.pt<0.40 ','MMMLeadingZMuIso')
MMMtri.addSelector('triMMMthirdMuID','PATMuMuMuTriSelector','leg2.pt()>5 && abs(leg2.eta())<2.4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0 && (leg2.isGlobalMuon() || leg2.isTrackerMuon())','MMMthirdMuID')
MMMSeq = MMMtri.returnSequence()

#MME tri
MMEtri = CutSequenceProducer(initialCounter  = 'initialEventsMME',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMEtri.addHLTFilter("MMEHLT",DATAMC2012TriggerPaths,"MME HLT_req")
MMEtri.addDiCandidateModule('triMMEosDiMuons','PATMuPairProducer', 'goodPatMuons','goodPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
MMEtri.addSelector('MMEosDiMuons','PATMuPairSelector','mass>40&&charge==0&&leg1.pfCandidateRef().isNonnull()&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&abs(leg1.eta())<2.4 && leg1.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && leg2.pfCandidateRef().isNonnull()&&(leg2.isGlobalMuon()||leg2.isTrackerMuon())&&abs(leg2.eta())<2.4 && leg2.pt()>5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 MME',1)
MMEtri.addDiCandidateModule('triMMEzzCands','PATMuMuEleTriProducer','triMMEosDiMuons','mvaedElectrons','systematicsMET','selectedPatJets',1,9999,text='MMEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMEtri.addCrossCleanerModule('triMMEzzCleanedCands','PATMuMuEleTriCrossCleaner',1,9999,text='MMEAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEtri.addSelector('triMMEzzMuIso','PATMuMuEleTriSelector','(leg1.leg1.chargedHadronIso()+max(0.0,leg1.leg1.neutralHadronIso()+leg1.leg1.photonIso()-leg1.leg1.userFloat("zzRho2012")*leg1.leg1.userFloat("effArea")))/leg1.leg1.pt<0.40 && (leg1.leg2.chargedHadronIso()+max(0.0,leg1.leg2.neutralHadronIso()+leg1.leg2.photonIso()-leg1.leg2.userFloat("zzRho2012")*leg1.leg2.userFloat("effArea")))/leg1.leg2.pt<0.40  ','MMELeadingZMuIso')
MMEtri.addSelector('triMMEthirdEleID','PATMuMuEleTriSelector','leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0 && leg2.gsfTrack.trackerExpectedHitsInner.numberOfHits()<2','MMEthirdMuID')
MMESeq = MMEtri.returnSequence()

#EEM tri
EEMtri = CutSequenceProducer(initialCounter  = 'initialEventsEEM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEMtri.addHLTFilter("EEMHLT",DATAMC2012TriggerPaths,"EEM HLT_req")
EEMtri.addDiCandidateModule('triEEMosDiMuons','PATElePairProducer', 'mvaedElectrons','mvaedElectrons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
EEMtri.addSelector('EEMosDiMuons','PATElePairSelector','mass>40&&charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 EEM',1)
EEMtri.addDiCandidateModule('triEEMzzCands','PATEleEleMuTriProducer','triEEMosDiMuons','goodPatMuons','systematicsMET','selectedPatJets',1,9999,text='EEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
EEMtri.addCrossCleanerModule('triEEMzzCleanedCands','PATEleEleMuTriCrossCleaner',1,9999,text='EEMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMtri.addSelector('triEEMzzMuIso','PATEleEleMuTriSelector','(leg1.leg1.chargedHadronIso()+max(0.0,leg1.leg1.neutralHadronIso()+leg1.leg1.photonIso()-leg1.leg1.userFloat("zzRho2012")*leg1.leg1.userFloat("effArea")))/leg1.leg1.pt<0.40 && (leg1.leg2.chargedHadronIso()+max(0.0,leg1.leg2.neutralHadronIso()+leg1.leg2.photonIso()-leg1.leg2.userFloat("zzRho2012")*leg1.leg2.userFloat("effArea")))/leg1.leg2.pt<0.40','EEMLeadingZMuIso')
EEMtri.addSelector('triEEMthirdMuID','PATEleEleMuTriSelector','leg2.pt()>5 && abs(leg2.eta())<2.4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0 && (leg2.isGlobalMuon() || leg2.isTrackerMuon())','EEMthirdMuID')
EEMSeq = EEMtri.returnSequence()

#EEM tri
EEEtri = CutSequenceProducer(initialCounter  = 'initialEventsEEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEtri.addHLTFilter("EEEHLT",DATAMC2012TriggerPaths,"EEE HLT_req")
EEEtri.addDiCandidateModule('triEEEosDiMuons','PATElePairProducer', 'mvaedElectrons','mvaedElectrons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
EEEtri.addSelector('EEEosDiMuons','PATElePairSelector','mass>40&&charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 EEE',1)
EEEtri.addDiCandidateModule('triEEEzzCands','PATEleEleEleTriProducer','triEEEosDiMuons','mvaedElectrons','systematicsMET','selectedPatJets',1,9999,text='EEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
EEEtri.addCrossCleanerModule('triEEEzzCleanedCands','PATEleEleEleTriCrossCleaner',1,9999,text='EEEAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEtri.addSelector('triEEEzzMuIso','PATEleEleEleTriSelector','(leg1.leg1.chargedHadronIso()+max(0.0,leg1.leg1.neutralHadronIso()+leg1.leg1.photonIso()-leg1.leg1.userFloat("zzRho2012")*leg1.leg1.userFloat("effArea")))/leg1.leg1.pt<0.40 && (leg1.leg2.chargedHadronIso()+max(0.0,leg1.leg2.neutralHadronIso()+leg1.leg2.photonIso()-leg1.leg2.userFloat("zzRho2012")*leg1.leg2.userFloat("effArea")))/leg1.leg2.pt<0.40','EEELeadingZMuIso')
EEEtri.addSelector('triEEEthirdEleID','PATEleEleEleTriSelector','leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0 && leg2.gsfTrack.trackerExpectedHitsInner.numberOfHits()<2','EEEthirdMuID')
EEESeq = EEEtri.returnSequence()

MMMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMManalysisConfigurator.addHLTFilter("MMMMHLT",DATAMC2012TriggerPaths,"HLT_req")
MMMManalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','MMMM')

MMMManalysisConfigurator.addDiCandidateModule('MMMMdiMuonsNoCut','PATMuPairProducer', 'smearedMuonsMMMM','smearedMuonsMMMM','smearedMETMMMM','smearedJetsMMMM',1,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0)
MMMManalysisConfigurator.addSelector('MMMMdiMuons','PATMuPairSelector','abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5','',1)
MMMManalysisConfigurator.addFSRRecovery('MMMMfsredMM','MuMuZFSRRecovery','MMMMdiMuons','boostedFsrPhotons','smearedElectronsMMMM','goodPatMuons')
MMMManalysisConfigurator.addSelector('MMMMosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMMM',1)
#should this be before ID criteria?


#leg[12]PhotonIso() has FSR cand photons removed
MMMManalysisConfigurator.addSelector('MMMMosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40 ','one Z1 with iso',1)

MMMManalysisConfigurator.addDiCandidateModule('MMMMdiElectrons','PATElePairProducer', 'smearedElectronsMMMM','smearedElectronsMMMM','smearedMETMMMM','smearedJetsMMMM',0,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0)
MMMManalysisConfigurator.addSelector('MMMMosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0&&leg2.userFloat("mvaNonTrigV0Pass")>0&&leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg1.pt()>7&&leg2.pt()>7&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5','',0)
MMMManalysisConfigurator.addSelector('MMMMosDiElectronsSIP','PATElePairSelector','abs(leg1.userFloat("ip3DS"))<4&&abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','',0)
MMMManalysisConfigurator.addSelector('MMMMosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40 ','',0)
MMMManalysisConfigurator.addBestSelector("MMMMbest","PATMuMuMuMuBestSelector","MMMMosDiMuonsIso","MMMMosDiElectronsIso","Best Zmm")

#3b. Apply 40<mZ1<120)
MMMManalysisConfigurator.addSelector('MMMMosDiMuonsMassReq','PATMuPairSelector','mass>40&&mass<120','40 lt mZ1 lt 120 mmmm',1)
#4b. At least one another pair (SF/OS)
#MMMManalysisConfigurator.addDiCandidateModule('MMMMzzCands','PATMuMuMuMuQuadProducer','MMMMbest','MMMMosDiMuonsIso','smearedMETMMMM','smearedJetsMMMM',1,9999,text='MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMMManalysisConfigurator.addDiCandidateModule('MMMMzzCands','PATMuMuMuMuQuadProducer','MMMMosDiMuonsIso','MMMMfsredMM','smearedMETMMMM','smearedJetsMMMM',1,9999,text='MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMMManalysisConfigurator.addQuadEmbedder('MMMMEmbedder','PATMuMuMuMuQuadEmbedder')
MMMManalysisConfigurator.addCrossCleanerModule('MMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='cross cleaned',dR = 0.02)
MMMMselectionSequence =MMMManalysisConfigurator.returnSequence()

###--------- EEEE ----------###

EEEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEEEanalysisConfigurator.addHLTFilter("EEEEHLT",DATAMC2012TriggerPaths,"EEEE HLT_req")
EEEEanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','EEEE')

EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiElectronsNoCuts','PATElePairProducer', 'smearedElectronsEEEE','smearedElectronsEEEE','smearedMETEEEE','smearedJetsEEEE',1,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0)
EEEEanalysisConfigurator.addSelector('EEEEdiElectrons','PATElePairSelector','leg1.pt()>7 && abs(leg1.eta())<2.5 && leg2.pt()>7 && abs(leg2.eta())<2.5','',1)
EEEEanalysisConfigurator.addFSRRecovery('EEEEfsredEE','EleEleZFSRRecovery','EEEEdiElectrons','boostedFsrPhotons','smearedElectronsEEEE','goodPatMuons','fsrrrrrr',passThrough=False)
EEEEanalysisConfigurator.addSelector('EEEEosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','aaaaaa',1)


EEEEanalysisConfigurator.addSelector('EEEEosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40 ','one Z1 with iso eeee',1)

EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiMuons','PATMuPairProducer', 'smearedMuonsEEEE','smearedMuonsEEEE','smearedMETEEEE','smearedJetsEEEE',0,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0)
EEEEanalysisConfigurator.addSelector('EEEEosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','',0)
EEEEanalysisConfigurator.addSelector('EEEEosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40 ','',0)

EEEEanalysisConfigurator.addBestSelector("EEEEbest","PATEleEleEleEleBestSelector","EEEEosDiElectronsIso","EEEEosDiMuonsIso","Good Zee")

##3b. Apply 40<mZ1<120)
EEEEanalysisConfigurator.addSelector('EEEEosDiEleMassReq','PATElePairSelector','mass>40&&mass<120','40 lt mZ1 lt 120 eeee',1)
##4b. At least one another pair (SF/OS)
#EEEEanalysisConfigurator.addDiCandidateModule('EEEEzzCands','PATEleEleEleEleQuadProducer','EEEEbest','EEEEosDiElectronsIso','smearedMETEEEE','smearedJetsEEEE',1,9999,text='EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
EEEEanalysisConfigurator.addDiCandidateModule('EEEEzzCands','PATEleEleEleEleQuadProducer','EEEEosDiElectronsIso','EEEEfsredEE','smearedMETEEEE','smearedJetsEEEE',1,9999,text='EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
EEEEanalysisConfigurator.addQuadEmbedder('EEEEQuadEmbedder','PATEleEleEleEleQuadEmbedder')
EEEEanalysisConfigurator.addCrossCleanerModule('EEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='cross cleaned eeee',dR = 0.02)
EEEEselectionSequence =EEEEanalysisConfigurator.returnSequence()


###--------- MMEE (OR of eemm and mmee) ----------###

MMEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEanalysisConfigurator.addHLTFilter("MMEEHLT",DATAMC2012TriggerPaths,"MMEE HLT_req")
MMEEanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','MMEE')

MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiMuonsNoCuts','PATMuPairProducer', 'smearedMuonsMMEE','smearedMuonsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')

#3a. Pair #1 built, (SF/OS, closest to Z0)
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsnoPF','PATMuPairSelector','charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEE no pf',1)
MMEEanalysisConfigurator.addSelector('MMEEosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEE',1)
MMEEanalysisConfigurator.addFSRRecovery('MMEEfsredMM','MuMuZFSRRecovery','MMEEosDiMuons','boostedFsrPhotons','smearedElectronsMMEE','goodPatMuons')
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40 ','one Z1 with iso MMEE',1)

MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiElectrons','PATElePairProducer', 'smearedElectronsMMEE','smearedElectronsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')
MMEEanalysisConfigurator.addSelector('MMEEosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','',1)
MMEEanalysisConfigurator.addFSRRecovery('MMEEfsredEE','EleEleZFSRRecovery','MMEEosDiElectrons','boostedFsrPhotons','smearedElectronsMMEE','goodPatMuons')
MMEEanalysisConfigurator.addSelector('MMEEosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40 ','MMEE Zee with iso',1)

MMEEanalysisConfigurator.addDiCandidateModule('MMEEzzCands','PATMuMuEleEleQuadProducer','MMEEosDiMuonsIso','MMEEosDiElectronsIso','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMEEanalysisConfigurator.addQuadEmbedder('MMEEQuadEmbedder','PATMuMuEleEleQuadEmbedder')
MMEEanalysisConfigurator.addCrossCleanerModule('MMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='cross cleaned mmee',dR = 0.01)
#3b. Apply 40<mZ1<120)
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsMassReq','PATMuMuEleEleQuadSelector','(leg1.mass>40&&leg1.mass<120)||(leg2.mass>40&&leg2.mass<120)','40 lt mZ1 lt 120 mmee',1)
##4b. At least one another pair (SF/OS)
MMEEanalysisConfigurator.addSorter('MMEESorted','PATMuMuEleEleQuadSorterByZMass')
##4d. Apply mll cuts (4<mZ2<120)
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedZ2Mass','PATMuMuEleEleQuadSelector','(leg1.mass()>40&&leg1.mass()<120&&leg2.mass()>4&&leg2.mass()<120)||(leg1.mass()>4&&leg1.mass()<120&&leg2.mass()>40&&leg2.mass()<120)','MMEESecondZCharge')
##5. Ensure there are two offline leptons with PT>20,10
MMEEanalysisConfigurator.addSelector('MMEEzzPt','PATMuMuEleEleQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req mmee',1)
##6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
MMEEanalysisConfigurator.addInvMassModule('MMEEzzInvMass','PATMuMuEleEleQuadInvMassSelector',1,9999,text='m2l gt 4 for all mmee',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
MMEEanalysisConfigurator.addSelector('MMEEZ4lSpace','PATMuMuEleEleQuadSelector','mass>70','Z to 4l phasespace mmee',1)
##8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
MMEEanalysisConfigurator.addSelector('MMEEHSpace','PATMuMuEleEleQuadSelector','mass>100&&((leg1.mass()>40&&leg1.mass()<120&&leg2.mass()>12)||(leg2.mass()>40&&leg2.mass()<120&&leg1.mass()>12))','Higgs phasespace mmee',1)
MMEEanalysisConfigurator.addSorter('MMEEFinalSel','PATMuMuEleEleQuadSorterByZMass')
MMEEselectionSequence =MMEEanalysisConfigurator.returnSequence()


###--------- EEMM ----------###

EEMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEMManalysisConfigurator.addHLTFilter("EEMMHLT",DATAMC2012TriggerPaths,"EEMM HLT_req")
EEMManalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','EEMM')

EEMManalysisConfigurator.addDiCandidateModule('EEMMdiElectrons','PATElePairProducer', 'smearedElectronsEEMM','smearedElectronsEEMM','smearedMETEEMM','smearedJetsEEMM',0,genParticles='genDaughters')

#3a. Pair #1 built, (SF/OS, closest to Z0)
#todo
EEMManalysisConfigurator.addSelector('EEMMosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 EEMM no pf',1)
EEMManalysisConfigurator.addFSRRecovery('EEMMfsredEE','EleEleZFSRRecovery','EEMMosDiElectrons','boostedFsrPhotons','smearedElectronsEEMM','goodPatMuons')
EEMManalysisConfigurator.addSelector('EEMMosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40 ','one Z1 with iso EEMM',1)

EEMManalysisConfigurator.addDiCandidateModule('EEMMdiMuonsNoCuts','PATMuPairProducer', 'smearedMuonsEEMM','smearedMuonsEEMM','smearedMETEEMM','smearedJetsEEMM',1,genParticles='genDaughters')
EEMManalysisConfigurator.addSelector('EEMMdiMuons','PATMuPairSelector','abs(leg1.eta())<2.4 && leg1.pt()>5&&abs(leg2.eta())<2.4 && leg2.pt()>5','',1)
EEMManalysisConfigurator.addFSRRecovery('EEMMdiMuonsFSR','MuMuZFSRRecovery','EEMMdiMuons','boostedFsrPhotons','smearedElectronsEEMM','goodPatMuons')
EEMManalysisConfigurator.addDiCandidateModule('EEMMzzCands','PATEleEleMuMuQuadProducer','EEMMosDiElectronsIso','EEMMdiMuonsFSR','smearedMETEEMM','smearedJetsEEMM',1,9999,text='EEMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
EEMManalysisConfigurator.addQuadEmbedder('EEMMQuadEmbedder','PATEleEleMuMuQuadEmbedder')
EEMManalysisConfigurator.addCrossCleanerModule('EEMMzzCleanedCands','PATEleEleMuMuQuadCrossCleaner',1,9999,text='cross cleaned eemm',dR = 0.01)
EEMMselectionSequence =EEMManalysisConfigurator.returnSequence()

###--------- MMEE only ----------###

MMEEonlyanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEEonly',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEonlyanalysisConfigurator.addHLTFilter("MMEEonlyHLT",DATAMC2012TriggerPaths,"MMEEonly HLT_req")
MMEEonlyanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','MMEEonly')

MMEEonlyanalysisConfigurator.addDiCandidateModule('MMEEonlydiMuons','PATMuPairProducer', 'smearedMuonsMMEE','smearedMuonsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')

#3a. Pair #1 built, (SF/OS, closest to Z0)
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyosDiMuonsnoPF','PATMuPairSelector','charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEEonly no pf',1)
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEE only',1)
MMEEonlyanalysisConfigurator.addFSRRecovery('MMEEonlyfsredMM','MuMuZFSRRecovery','MMEEonlyosDiMuons','boostedFsrPhotons','smearedElectronsMMEE','goodPatMuons')
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.40 ','one Z1 with iso MMEE only',1)

MMEEonlyanalysisConfigurator.addDiCandidateModule('MMEEonlydiElectrons','PATElePairProducer', 'smearedElectronsMMEE','smearedElectronsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')
MMEEonlyanalysisConfigurator.addFSRRecovery('MMEEonlydiElectronsFSR','EleEleZFSRRecovery','MMEEonlydiElectrons','boostedFsrPhotons','smearedElectronsMMEE','goodPatMuons')
MMEEonlyanalysisConfigurator.addDiCandidateModule('MMEEonlyzzCands','PATMuMuEleEleQuadProducer','MMEEonlyosDiMuonsIso','MMEEonlydiElectronsFSR','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEonlyAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMEEonlyanalysisConfigurator.addQuadEmbedder('MMEEOnlyQuadEmbedder','PATMuMuEleEleQuadEmbedder')
MMEEonlyanalysisConfigurator.addCrossCleanerModule('MMEEonlyzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='cross cleaned mmee',dR = 0.01)
MMEEonlyselectionSequence =MMEEonlyanalysisConfigurator.returnSequence()

######################__________________________________MMMT_____________________________________##############################

MMMTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
MMMTanalysisConfigurator.addHLTFilter("MMMTHLT",DATAMC2012TriggerPaths,"HLT_req_MMMT")

MMMTanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','MMMT')
MMMTanalysisConfigurator.addDiCandidateModule('MMMTdiMuons','PATMuPairProducer', 'smearedMuonsMMMT','smearedMuonsMMMT','smearedMETMMMT','smearedJetsMMMT',1,genParticles='genDaughters')
MMMTanalysisConfigurator.addSelector('MMMTosDiMuons','PATMuPairSelector','charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMMTDiMuonCreation',1)
MMMTanalysisConfigurator.addSelector('MMMTosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.25 ','MMMTDiMuonIso',1)
MMMTanalysisConfigurator.addDiCandidateModule('MMMTmuTau','PATMuTauPairProducer', 'smearedMuonsMMMT','smearedTausMMMT','smearedMETMMMT','smearedJetsMMMT',1,9999,text = 'MMMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
MMMTanalysisConfigurator.addDiCandidateModule('MMMTzzCands','PATMuMuMuTauQuadProducer','MMMTosDiMuons','MMMTmuTau','smearedMETMMMT','smearedJetsMMMT',1,9999,text='MMMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMMTanalysisConfigurator.addCrossCleanerModule('MMMTzzCleanedCands','PATMuMuMuTauQuadCrossCleaner',1,9999,text='MMMTAtLeastOneZZCleanedCandidate',dR = 0.1)
#create the sequence
MMMTselectionSequence =MMMTanalysisConfigurator.returnSequence()

######################__________________________________MMTT_____________________________________##############################


MMTTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMTT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
MMTTanalysisConfigurator.addHLTFilter("MMTTHLT",DATAMC2012TriggerPaths,"HLT_reqMMTT")

MMTTanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','MMTT')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiMuons','PATMuPairProducer', 'smearedMuonsMMTT','smearedMuonsMMTT','smearedMETMMTT','smearedJetsMMTT',1,genParticles='genDaughters')
MMTTanalysisConfigurator.addSelector('MMTTosDiMuons','PATMuPairSelector','mass>40 && charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMTTDiMuonCreation',1)
MMTTanalysisConfigurator.addSelector('MMTTosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.25 ','MMTTDiMuonIso',1)
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiTaus','PATDiTauPairProducer','smearedTausMMTT','smearedTausMMTT','smearedMETMMTT','smearedJetsMMTT',1,9999,text='MMTTAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTzzCands','PATMuMuTauTauQuadProducer','MMTTosDiMuons','MMTTdiTaus','smearedMETMMTT','smearedJetsMMTT',1,9999,text='MMTTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMTTanalysisConfigurator.addCrossCleanerModule('MMTTzzCleanedCands','PATMuMuTauTauQuadCrossCleaner',1,9999,text='MMTTAtLeastOneZZCleanedCandidate',dR = 0.1)
MMTTselectionSequence =MMTTanalysisConfigurator.returnSequence()


######################__________________________________MMET_____________________________________##############################

MMETanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMET',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

MMETanalysisConfigurator.addHLTFilter("MMETHLT",DATAMC2012TriggerPaths,"HLT_reqMMET")
MMETanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','MMET')
MMETanalysisConfigurator.addDiCandidateModule('MMETdiMuons','PATMuPairProducer', 'smearedMuonsMMET','smearedMuonsMMET','smearedMETMMET','smearedJetsMMET',1,genParticles='genDaughters')
MMETanalysisConfigurator.addSelector('MMETosDiMuons','PATMuPairSelector','mass>40 && charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMETDiMuonCreation',1)
MMETanalysisConfigurator.addSelector('MMETosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.25 ','MMETDiMuonIso',1)
MMETanalysisConfigurator.addDiCandidateModule('MMETelecTau','PATEleTauPairProducer','smearedElectronsMMET','smearedTausMMET','smearedMETMMET','smearedJetsMMET',1,9999,text='MMETAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addDiCandidateModule('MMETzzCands','PATMuMuEleTauQuadProducer','MMETosDiMuons','MMETelecTau','smearedMETMMET','smearedJetsMMET',1,9999,text='MMETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addCrossCleanerModule('MMETzzCleanedCands','PATMuMuEleTauQuadCrossCleaner',1,9999,text='MMETAtLeastOneZZCleanedCandidate',dR = 0.1)
MMETselectionSequence =MMETanalysisConfigurator.returnSequence()


######################__________________________________MMEM_____________________________________##############################

MMEManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEM',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

MMEManalysisConfigurator.addHLTFilter("MMEMHLT",DATAMC2012TriggerPaths,"HLT_reqMMEM")
MMEManalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','MMEM')
MMEManalysisConfigurator.addDiCandidateModule('MMEMdiMuons','PATMuPairProducer', 'smearedMuonsMMEM','smearedMuonsMMEM','smearedMETMMEM','smearedJetsMMEM',1,genParticles='genDaughters')
MMEManalysisConfigurator.addSelector('MMEMosDiMuons','PATMuPairSelector','mass>40 && charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMEMDiMuonCreation',1)
MMEManalysisConfigurator.addSelector('MMEMosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.25 ','MMEMDiMuonIso',1)
MMEManalysisConfigurator.addDiCandidateModule('MMEMelecMu','PATEleMuPairProducer','smearedElectronsMMEM','smearedMuonsMMEM','smearedMETMMEM','smearedJetsMMEM',1,9999,text='MMEMAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addDiCandidateModule('MMEMzzCands','PATMuMuEleMuQuadProducer','MMEMosDiMuons','MMEMelecMu','smearedMETMMEM','smearedJetsMMEM',1,9999,text='MMEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addCrossCleanerModule('MMEMzzCleanedCands','PATMuMuEleMuQuadCrossCleaner',1,9999,text='MMEMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEMselectionSequence =MMEManalysisConfigurator.returnSequence()

######################__________________________________EEMT_____________________________________##############################

EEMTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEMT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

EEMTanalysisConfigurator.addHLTFilter("EEMTHLT",DATAMC2012TriggerPaths,"HLT_reqEEMT")
EEMTanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','EEMT')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTdiElectrons','PATElePairProducer', 'smearedElectronsEEMT','smearedElectronsEEMT','smearedMETEEMT','smearedJetsEEMT',1,genParticles='genDaughters')

EEMTanalysisConfigurator.addSelector('EEMTosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EEMTDiEleCreation',1)
EEMTanalysisConfigurator.addSelector('EEMTosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.25 ','EEMTDiEleIso',1)

EEMTanalysisConfigurator.addDiCandidateModule('EEMTmuTau','PATMuTauPairProducer', 'smearedMuonsEEMT','smearedTausEEMT','smearedMETEEMT','smearedJetsEEMT',1,9999,text = 'EEMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTzzCands','PATEleEleMuTauQuadProducer','EEMTosDiElectrons','EEMTmuTau','smearedMETEEMT','smearedJetsEEMT',1,9999,text='EEMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEMTanalysisConfigurator.addCrossCleanerModule('EEMTzzCleanedCands','PATEleEleMuTauQuadCrossCleaner',1,9999,text='EEMTAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMTselectionSequence =EEMTanalysisConfigurator.returnSequence()


######################__________________________________EEET_____________________________________##############################

EEETanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEET',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

EEETanalysisConfigurator.addHLTFilter("EEETHLT",DATAMC2012TriggerPaths,"HLT_reqEEET")
EEETanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','EEET')
EEETanalysisConfigurator.addDiCandidateModule('EEETdiElectrons','PATElePairProducer', 'smearedElectronsEEET','smearedElectronsEEET','smearedMETEEET','smearedJetsEEET',1,genParticles='genDaughters')
EEETanalysisConfigurator.addSelector('EEETosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EEETDiEleCreation',1)
EEETanalysisConfigurator.addSelector('EEETosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.25 ','EEETDiEleIso',1)
EEETanalysisConfigurator.addDiCandidateModule('EEETeleTau','PATEleTauPairProducer', 'smearedElectronsEEET','smearedTausEEET','smearedMETEEET','smearedJetsEEET',1,9999,text = 'EEETAtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETanalysisConfigurator.addDiCandidateModule('EEETzzCands','PATEleEleEleTauQuadProducer','EEETosDiElectrons','EEETeleTau','smearedMETEEET','smearedJetsEEET',1,9999,text='EEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEETanalysisConfigurator.addCrossCleanerModule('EEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='EEETAtLeastOneZZCleanedCandidate',dR = 0.1)
EEETselectionSequence =EEETanalysisConfigurator.returnSequence()


######################__________________________________EETT_____________________________________##############################

EETTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEETT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

EETTanalysisConfigurator.addHLTFilter("EETTHLT",DATAMC2012TriggerPaths,"HLT_reqEETT")
EETTanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','EETT')
EETTanalysisConfigurator.addDiCandidateModule('EETTdiElectrons','PATElePairProducer', 'smearedElectronsEETT','smearedElectronsEETT','smearedMETEETT','smearedJetsEETT',1,genParticles='genDaughters')
EETTanalysisConfigurator.addSelector('EETTosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EETTDiEleCreation',1)

EETTanalysisConfigurator.addSelector('EETTosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.25 ','EETTDiEleIso',1)
EETTanalysisConfigurator.addDiCandidateModule('EETTtauTau','PATDiTauPairProducer', 'smearedTausEETT','smearedTausEETT','smearedMETEETT','smearedJetsEETT',1,9999,text = 'EETTAtLeastOnediTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EETTanalysisConfigurator.addDiCandidateModule('EETTzzCands','PATEleEleTauTauQuadProducer','EETTosDiElectrons','EETTtauTau','smearedMETEETT','smearedJetsEETT',1,9999,text='EETTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EETTanalysisConfigurator.addCrossCleanerModule('EETTzzCleanedCands','PATEleEleTauTauQuadCrossCleaner',1,9999,text='EETTAtLeastOneZZCleanedCandidate',dR = 0.1)
EETTselectionSequence =EETTanalysisConfigurator.returnSequence()

######################__________________________________EEEM_____________________________________##############################

EEEManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEM',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
EEEManalysisConfigurator.addHLTFilter("EEEMHLT",DATAMC2012TriggerPaths,"HLT_reqEEEM")
EEEManalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','EEEM')
EEEManalysisConfigurator.addDiCandidateModule('EEEMdiElectrons','PATElePairProducer', 'smearedElectronsEEEM','smearedElectronsEEEM','smearedMETEEEM','smearedJetsEEEM',1,genParticles='genDaughters')
EEEManalysisConfigurator.addSelector('EEEMosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EEEMDiEleCreation',1)
EEEManalysisConfigurator.addSelector('EEEMosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.25 ','EEEMDiEleIso',1)

EEEManalysisConfigurator.addDiCandidateModule('EEEMeleMu','PATEleMuPairProducer', 'smearedElectronsEEEM','smearedMuonsEEEM','smearedMETEEEM','smearedJetsEEEM',1,9999,text = 'EEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEEManalysisConfigurator.addDiCandidateModule('EEEMzzCands','PATEleEleEleMuQuadProducer','EEEMosDiElectrons','EEEMeleMu','smearedMETEEEM','smearedJetsEEEM',1,9999,text='EEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEEManalysisConfigurator.addCrossCleanerModule('EEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='EEEMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEMselectionSequence =EEEManalysisConfigurator.returnSequence()

######################__________________________________EEES_____________________________________##############################

EEESanalysisConfigurator = CutSequenceProducer(
        initialCounter  = 'initialEventsEEES',
        pyModuleName = __name__,
        pyNameSpace  = locals()
        )
#EEEManalysisConfigurator.addHLTFilter("EEEMHLT",DATAMC2012TriggerPaths,"HLT_reqEEEM")
EEESanalysisConfigurator.addSmearing('cleanPatTaus','goodPatMuons','mvaedElectrons','selectedPatJets','EEES')
EEESanalysisConfigurator.addDiCandidateModule('EEESdiElectrons','PATElePairProducer', 'smearedElectronsEEES','smearedElectronsEEES','smearedMETEEES','smearedJetsEEES',1,genParticles='genDaughters')
EEESanalysisConfigurator.addSelector('EEESosDiElectrons','PATElePairSelector','charge == 0 && mass > 40 && leg1.userFloat("mvaNonTrigV0Pass") > 0 && leg2.userFloat("mvaNonTrigV0Pass") > 0 && abs(leg1.eta()) < 2.4 && abs(leg2.eta()) < 2.4','EEESDiEleCreation',1)
#EEESanalysisConfigurator.addSelector('EEEMosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("effArea")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("effArea")))/leg2.pt<0.25 ','EEEMDiEleIso',1)

EEESanalysisConfigurator.addDiCandidateModule('EEESeleSC','PATEleSCPairProducer','smearedElectronsEEES','selectedPatPhotons','smearedMETEEES','smearedJetsEEES',1,9999,text = 'EEESAtLeastOneMuTau',leadingObjectsOnly = False, dR = 0.5, recoMode ="", genParticles='genDaughters')

EEESanalysisConfigurator.addDiCandidateModule('EEESzzCands','PATEleEleEleSCQuadProducer','EEESosDiElectrons','EEESeleSC','smearedMETEEES','smearedJetsEEES',1,9999,text='EEESAtLeastOneZZ',leadingObjectsOnly = False, dR = 0.005, recoMode="", genParticles='genDaughters')
EEESanalysisConfigurator.addCrossCleanerModule('EEESzzCleanedCands','PATEleEleEleSCQuadCrossCleaner',1,9999,text='EEESAtLeastOneZZCleanedCandidate',dR = 0.1)

EEESanalysisConfigurator.addSelector('EEESzzEleIso','PATEleEleEleSCQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("effArea")))/leg2.leg1.pt<0.25','EEESEleIso')

EEESanalysisConfigurator.addSorter('EEESzzCleanedCandsSortedByZMass','PATEleEleEleSCQuadSorterByZMass')

#EEEManalysisConfigurator.addDiCandidateModule('EEEMeleMu','PATEleMuPairProducer', 'smearedElectronsEEEM','smearedMuonsEEEM','smearedMETEEEM','smearedJetsEEEM',1,9999,text = 'EEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
#EEEManalysisConfigurator.addDiCandidateModule('EEEMzzCands','PATEleEleEleMuQuadProducer','EEEMosDiElectrons','EEEMeleMu','smearedMETEEEM','smearedJetsEEEM',1,9999,text='EEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
#EEEManalysisConfigurator.addCrossCleanerModule('EEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='EEEMAtLeastOneZZCleanedCandidate',dR = 0.1)


#EEEManalysisConfigurator.addSelector('EEEMzzCleanedThirdMuID','PATEleEleEleMuQuadSelector','leg2.leg2.userInt("tightID")>0.5 && abs(leg2.leg2.eta())<2.5','EEEMThirdMuID')
#EEEManalysisConfigurator.addSelector('EEEMzzEleId','PATEleEleEleMuQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','EEEMEleCiCLoose')
#EEEManalysisConfigurator.addSelector('EEEMzzEleIso','PATEleEleEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("effArea")))/leg2.leg1.pt<0.25','EEEMEleIso')
#EEEManalysisConfigurator.addSelector('EEEMzzMuIso2','PATEleEleEleMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho2012")*leg2.leg2.userFloat("effArea")))/leg2.leg2.pt<0.25','EEEMMuIso')
#EEEManalysisConfigurator.addSorter('EEEMzzCleanedCandsSortedByZMass','PATEleEleEleMuQuadSorterByZMass')
#EEEManalysisConfigurator.addSelector('EEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EEEMdZ')
#EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsAboveThreshold','PATEleEleEleMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 && leg2().leg2().pt()>10 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.4','EEEMAtLeastOneZZCandOverThresholds')
#EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsEMuQ','PATEleEleEleMuQuadSelector','leg2.charge()==0','EEEMEleMuCharge')
#EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsMMMass','PATEleEleEleMuQuadSelector','leg1.mass()>60&&leg1.mass()<120','EEEMMMMass')
#EEEManalysisConfigurator.addSorter('EEEMFinalSel','PATEleEleEleMuQuadSorterByZMass')
#EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsETMass','PATEleEleEleMuQuadSelector','leg2.mass()<90','EEEMEMMass')

EEESselectionSequence = EEESanalysisConfigurator.returnSequence()

######################_______________________________EndOfConfigurators__________________________################################
