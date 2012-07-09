import FWCore.ParameterSet.Config as cms

from UWAnalysis.Configuration.tools.CutSequenceProducer import *

MC2011TriggerPaths=["HLT_Mu17_Mu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]
DATA2011TriggerPaths=["HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL","HLT_Mu17_Mu8","HLT_DoubleMu7","HLT_Mu13_Mu8"]
DATAMC2012TriggerPaths=["HLT_Mu17_Mu8","HLT_Mu17_TkMu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]

#MMM tri
MMMtri = CutSequenceProducer(initialCounter  = 'initialEventsMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMMtri.addHLTFilter("MMMHLT",DATAMC2012TriggerPaths,"MMM HLT_req")
MMMtri.addDiCandidateModule('triMMMdiMuons','PATMuPairProducer', 'cleanPatMuons','cleanPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
MMMtri.addSelector('triMMMosDiMuons','PATMuPairSelector','mass>40&&charge==0&&leg1.pfCandidateRef().isNonnull()&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&abs(leg1.eta())<2.4 && leg1.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.pfCandidateRef().isNonnull()&&(leg2.isGlobalMuon()||leg2.isTrackerMuon())&&abs(leg2.eta())<2.4 && leg2.pt()>5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 MMM',1)

#temp -- try out the FSR module
#MMMtri.addFSRRecovery('fsredMM','MuMuZFSRRecovery','triMMMosDiMuons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons')

MMMtri.addDiCandidateModule('triMMMzzCands','PATMuMuMuTriProducer','triMMMosDiMuons','cleanPatMuons','systematicsMET','selectedPatJets',1,9999,text='MMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMMtri.addCrossCleanerModule('triMMMzzCleanedCands','PATMuMuMuTriCrossCleaner',1,9999,text='MMMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMtri.addSelector('triMMMzzMuIso','PATMuMuMuTriSelector','(leg1.leg1.chargedHadronIso()+max(0.0,leg1.leg1.neutralHadronIso()+leg1.leg1.photonIso()-leg1.leg1.userFloat("zzRho2012")*leg1.leg1.userFloat("EAGammaNeuHadron04")))/leg1.leg1.pt<0.40 && (leg1.leg2.chargedHadronIso()+max(0.0,leg1.leg2.neutralHadronIso()+leg1.leg2.photonIso()-leg1.leg2.userFloat("zzRho2012")*leg1.leg2.userFloat("EAGammaNeuHadron04")))/leg1.leg2.pt<0.40 ','MMMLeadingZMuIso')
MMMtri.addSelector('triMMMthirdMuID','PATMuMuMuTriSelector','leg2.pt()>5 && abs(leg2.eta())<2.4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0 && (leg2.isGlobalMuon() || leg2.isTrackerMuon())','MMMthirdMuID')
MMMSeq = MMMtri.returnSequence()

#MME tri
MMEtri = CutSequenceProducer(initialCounter  = 'initialEventsMME',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMEtri.addHLTFilter("MMEHLT",DATAMC2012TriggerPaths,"MME HLT_req")
MMEtri.addDiCandidateModule('triMMEosDiMuons','PATMuPairProducer', 'cleanPatMuons','cleanPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
MMEtri.addSelector('MMEosDiMuons','PATMuPairSelector','mass>40&&charge==0&&leg1.pfCandidateRef().isNonnull()&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&abs(leg1.eta())<2.4 && leg1.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && leg2.pfCandidateRef().isNonnull()&&(leg2.isGlobalMuon()||leg2.isTrackerMuon())&&abs(leg2.eta())<2.4 && leg2.pt()>5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 MME',1)
MMEtri.addDiCandidateModule('triMMEzzCands','PATMuMuEleTriProducer','triMMEosDiMuons','mvaedElectrons','systematicsMET','selectedPatJets',1,9999,text='MMEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMEtri.addCrossCleanerModule('triMMEzzCleanedCands','PATMuMuEleTriCrossCleaner',1,9999,text='MMEAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEtri.addSelector('triMMEzzMuIso','PATMuMuEleTriSelector','(leg1.leg1.chargedHadronIso()+max(0.0,leg1.leg1.neutralHadronIso()+leg1.leg1.photonIso()-leg1.leg1.userFloat("zzRho2012")*leg1.leg1.userFloat("EAGammaNeuHadron04")))/leg1.leg1.pt<0.40 && (leg1.leg2.chargedHadronIso()+max(0.0,leg1.leg2.neutralHadronIso()+leg1.leg2.photonIso()-leg1.leg2.userFloat("zzRho2012")*leg1.leg2.userFloat("EAGammaNeuHadron04")))/leg1.leg2.pt<0.40  ','MMELeadingZMuIso')
MMEtri.addSelector('triMMEthirdEleID','PATMuMuEleTriSelector','leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0 && leg2.gsfTrack.trackerExpectedHitsInner.numberOfHits()<2','MMEthirdMuID')
MMESeq = MMEtri.returnSequence()

#EEM tri
EEMtri = CutSequenceProducer(initialCounter  = 'initialEventsEEM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEMtri.addHLTFilter("EEMHLT",DATAMC2012TriggerPaths,"EEM HLT_req")
EEMtri.addDiCandidateModule('triEEMosDiMuons','PATElePairProducer', 'mvaedElectrons','mvaedElectrons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
EEMtri.addSelector('EEMosDiMuons','PATElePairSelector','mass>40&&charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 EEM',1)

#temp -- try out the FSR module
#EEMtri.addFSRRecovery('tempFSREEM','EleEleZFSRRecovery','EEMosDiMuons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons')

EEMtri.addDiCandidateModule('triEEMzzCands','PATEleEleMuTriProducer','triEEMosDiMuons','cleanPatMuons','systematicsMET','selectedPatJets',1,9999,text='EEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
EEMtri.addCrossCleanerModule('triEEMzzCleanedCands','PATEleEleMuTriCrossCleaner',1,9999,text='EEMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMtri.addSelector('triEEMzzMuIso','PATEleEleMuTriSelector','(leg1.leg1.chargedHadronIso()+max(0.0,leg1.leg1.neutralHadronIso()+leg1.leg1.photonIso()-leg1.leg1.userFloat("zzRho2012")*leg1.leg1.userFloat("EAGammaNeuHadron04")))/leg1.leg1.pt<0.40 && (leg1.leg2.chargedHadronIso()+max(0.0,leg1.leg2.neutralHadronIso()+leg1.leg2.photonIso()-leg1.leg2.userFloat("zzRho2012")*leg1.leg2.userFloat("EAGammaNeuHadron04")))/leg1.leg2.pt<0.40','EEMLeadingZMuIso')
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
EEEtri.addSelector('triEEEzzMuIso','PATEleEleEleTriSelector','(leg1.leg1.chargedHadronIso()+max(0.0,leg1.leg1.neutralHadronIso()+leg1.leg1.photonIso()-leg1.leg1.userFloat("zzRho2012")*leg1.leg1.userFloat("EAGammaNeuHadron04")))/leg1.leg1.pt<0.40 && (leg1.leg2.chargedHadronIso()+max(0.0,leg1.leg2.neutralHadronIso()+leg1.leg2.photonIso()-leg1.leg2.userFloat("zzRho2012")*leg1.leg2.userFloat("EAGammaNeuHadron04")))/leg1.leg2.pt<0.40','EEELeadingZMuIso')
EEEtri.addSelector('triEEEthirdEleID','PATEleEleEleTriSelector','leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0 && leg2.gsfTrack.trackerExpectedHitsInner.numberOfHits()<2','EEEthirdMuID')
EEESeq = EEEtri.returnSequence()

MMMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMManalysisConfigurator.addHLTFilter("MMMMHLT",DATAMC2012TriggerPaths,"HLT_req")
MMMManalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMMM')

MMMManalysisConfigurator.addDiCandidateModule('MMMMdiMuons','PATMuPairProducer', 'smearedMuonsMMMM','smearedMuonsMMMM','smearedMETMMMM','smearedJetsMMMM',1,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMMManalysisConfigurator.addSelector('MMMMosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMMM',1)

MMMManalysisConfigurator.addFSRRecovery('MMMMfsredMM','MuMuZFSRRecovery','MMMMosDiMuons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons')

#leg[12]PhotonIso() has FSR cand photons removed
MMMManalysisConfigurator.addSelector('MMMMosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','one Z1 with iso',1)

MMMManalysisConfigurator.addDiCandidateModule('MMMMdiElectrons','PATElePairProducer', 'smearedElectronsMMMM','smearedElectronsMMMM','smearedMETMMMM','smearedJetsMMMM',0,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMMManalysisConfigurator.addSelector('MMMMosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0&&leg2.userFloat("mvaNonTrigV0Pass")>0&&leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg1.pt()>7&&leg2.pt()>7&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5','',0)
MMMManalysisConfigurator.addSelector('MMMMosDiElectronsSIP','PATElePairSelector','abs(leg1.userFloat("ip3DS"))<4&&abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','',0)
MMMManalysisConfigurator.addSelector('MMMMosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','',0)

MMMManalysisConfigurator.addBestSelector("MMMMbest","PATMuMuMuMuBestSelector","MMMMosDiMuonsIso","MMMMosDiElectronsIso","Best Zmm")

#3b. Apply 40<mZ1<120) 
MMMManalysisConfigurator.addSelector('MMMMosDiMuonsMassReq','PATMuPairSelector','mass>40&&mass<120','40 lt mZ1 lt 120 mmmm',1)
#4b. At least one another pair (SF/OS) 
MMMManalysisConfigurator.addDiCandidateModule('MMMMzzCands','PATMuMuMuMuQuadProducer','MMMMbest','MMMMosDiMuonsIso','smearedMETMMMM','smearedJetsMMMM',1,9999,text='MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMMManalysisConfigurator.addCrossCleanerModule('MMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='cross cleaned',dR = 0.01)
MMMManalysisConfigurator.addSorter('MMMMSorted','PATMuMuMuMuQuadSorterByZMass')
#4c. Pair #2 built (SF/OS, highest pT leptons) 
#4d. Apply mll cuts (4<mZ2<120) 
MMMManalysisConfigurator.addSelector('MMMMzzCleanedZ2Mass','PATMuMuMuMuQuadSelector','leg2.mass()>4&&leg2.mass()<120','z2 mass 4 to 120')
#5. Ensure there are two offline leptons with PT>20,10
MMMManalysisConfigurator.addSelector('MMMMzzPt','PATMuMuMuMuQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req',1) 
#6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
MMMManalysisConfigurator.addInvMassModule('MMMMzzInvMass','PATMuMuMuMuQuadInvMassSelector',1,9999,text='m4l gt 4 for all',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
MMMManalysisConfigurator.addSelector('MMMMZ4lSpace','PATMuMuMuMuQuadSelector','mass>70','Z to 4l phasespace',1)
#8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
MMMManalysisConfigurator.addSelector('MMMMHSpace','PATMuMuMuMuQuadSelector','mass>100&&leg2.mass()>12','Higgs phasespace',1)
MMMManalysisConfigurator.addSorter('MMMMFinalSel','PATMuMuMuMuQuadSorterByZMass')
MMMMselectionSequence =MMMManalysisConfigurator.returnSequence()

###--------- EEEE ----------###

EEEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEEEanalysisConfigurator.addHLTFilter("EEEEHLT",DATAMC2012TriggerPaths,"EEEE HLT_req")
EEEEanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEEE')

EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiElectrons','PATElePairProducer', 'smearedElectronsEEEE','smearedElectronsEEEE','smearedMETEEEE','smearedJetsEEEE',1,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
EEEEanalysisConfigurator.addSelector('EEEEosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','',1)

EEEEanalysisConfigurator.addFSRRecovery('EEEEfsredEE','EleEleZFSRRecovery','EEEEosDiElectrons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons','fsrrrrrr')

EEEEanalysisConfigurator.addSelector('EEEEosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','one Z1 with iso eeee',1)
#build dimuons for 'best' check
EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiMuons','PATMuPairProducer', 'smearedMuonsEEEE','smearedMuonsEEEE','smearedMETEEEE','smearedJetsEEEE',0,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
EEEEanalysisConfigurator.addSelector('EEEEosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','',0)
EEEEanalysisConfigurator.addSelector('EEEEosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','',0)

EEEEanalysisConfigurator.addBestSelector("EEEEbest","PATEleEleEleEleBestSelector","EEEEosDiElectronsIso","EEEEosDiMuonsIso","Good Zee")

##3b. Apply 40<mZ1<120) 
EEEEanalysisConfigurator.addSelector('EEEEosDiEleMassReq','PATElePairSelector','mass>40&&mass<120','40 lt mZ1 lt 120 eeee',1)
##4b. At least one another pair (SF/OS) 
EEEEanalysisConfigurator.addDiCandidateModule('EEEEzzCands','PATEleEleEleEleQuadProducer','EEEEbest','EEEEosDiElectronsIso','smearedMETEEEE','smearedJetsEEEE',1,9999,text='EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
EEEEanalysisConfigurator.addCrossCleanerModule('EEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='cross cleaned eeee',dR = 0.01)
EEEEanalysisConfigurator.addSorter('EEEESorted','PATEleEleEleEleQuadSorterByZMass')
##4c. Pair #2 built (SF/OS, highest pT leptons) 
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedEleIso','PATEleEleEleEleQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1PhotonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.40 && (leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2PhotonIso()-leg2.leg2.userFloat("zzRho2012")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.40 ','two good Zs eeee',1)
##4d. Apply mll cuts (4<mZ2<120) 
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedZ2Mass','PATEleEleEleEleQuadSelector','leg2.mass()>4&&leg2.mass()<120','EEEE second z 4 to 120')
##5. Ensure there are two offline leptons with PT>20,10
EEEEanalysisConfigurator.addSelector('EEEEzzPt','PATEleEleEleEleQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req eeee',1) 
##6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
EEEEanalysisConfigurator.addInvMassModule('EEEEzzInvMass','PATEleEleEleEleQuadInvMassSelector',1,9999,text='m2l gt 4 for all eeee',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
EEEEanalysisConfigurator.addSelector('EEEEZ4lSpace','PATEleEleEleEleQuadSelector','mass>70','Z to 4l phasespace eeee',1)
##8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
EEEEanalysisConfigurator.addSelector('EEEEHSpace','PATEleEleEleEleQuadSelector','mass>100&&leg2.mass()>12','Higgs phasespace eeee',1)
EEEEanalysisConfigurator.addSorter('EEEEFinalSel','PATEleEleEleEleQuadSorterByZMass')
EEEEselectionSequence =EEEEanalysisConfigurator.returnSequence()


###--------- MMEE (OR of eemm and mmee) ----------###

MMEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEanalysisConfigurator.addHLTFilter("MMEEHLT",DATAMC2012TriggerPaths,"MMEE HLT_req")
MMEEanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMEE')

MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiMuons','PATMuPairProducer', 'smearedMuonsMMEE','smearedMuonsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')

#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsnoPF','PATMuPairSelector','charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEE no pf',1)
MMEEanalysisConfigurator.addSelector('MMEEosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEE',1)
MMEEanalysisConfigurator.addFSRRecovery('MMEEfsredMM','MuMuZFSRRecovery','MMEEosDiMuons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons')
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','one Z1 with iso MMEE',1)

MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiElectrons','PATElePairProducer', 'smearedElectronsMMEE','smearedElectronsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')
MMEEanalysisConfigurator.addSelector('MMEEosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','',1)
MMEEanalysisConfigurator.addFSRRecovery('MMEEfsredEE','EleEleZFSRRecovery','MMEEosDiElectrons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons')
MMEEanalysisConfigurator.addSelector('MMEEosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','MMEE Zee with iso',1)

MMEEanalysisConfigurator.addDiCandidateModule('MMEEzzCands','PATMuMuEleEleQuadProducer','MMEEosDiMuonsIso','MMEEosDiElectronsIso','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
#3b. Apply 40<mZ1<120) 
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsMassReq','PATMuMuEleEleQuadSelector','(leg1.mass>40&&leg1.mass<120)||(leg2.mass>40&&leg2.mass<120)','40 lt mZ1 lt 120 mmee',1)
##4b. At least one another pair (SF/OS) 
MMEEanalysisConfigurator.addCrossCleanerModule('MMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='cross cleaned mmee',dR = 0.01)
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
EEMManalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEMM')

EEMManalysisConfigurator.addDiCandidateModule('EEMMdiMuons','PATElePairProducer', 'smearedElectronsEEMM','smearedElectronsEEMM','smearedMETEEMM','smearedJetsEEMM',1,genParticles='genDaughters')

#3a. Pair #1 built, (SF/OS, closest to Z0) 
#todo
EEMManalysisConfigurator.addSelector('EEMMosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','one Z1 EEMM no pf',1)
EEMManalysisConfigurator.addFSRRecovery('EEMMfsredEE','EleEleZFSRRecovery','EEMMosDiElectrons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons')
EEMManalysisConfigurator.addSelector('EEMMosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','one Z1 with iso EEMM',1)

EEMManalysisConfigurator.addDiCandidateModule('EEMMdiElectrons','PATMuPairProducer', 'smearedMuonsEEMM','smearedMuonsEEMM','smearedMETEEMM','smearedJetsEEMM',1,genParticles='genDaughters')
EEMManalysisConfigurator.addSelector('EEMMosDiMuons','PATMuPairSelector','charge==0&&leg1.pfCandidateRef().isNonnull()&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&abs(leg1.eta())<2.4 && leg1.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.pfCandidateRef().isNonnull()&&(leg2.isGlobalMuon()||leg2.isTrackerMuon())&&abs(leg2.eta())<2.4 && leg2.pt()>5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','',1)
EEMManalysisConfigurator.addFSRRecovery('EEMMfsredMM','MuMuZFSRRecovery','EEMMosDiMuons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons')
EEMManalysisConfigurator.addSelector('EEMMosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','a Z with iso ee should cut none',1)

#Don't require best--want the overlap numbers
#EEMManalysisConfigurator.addBestSelector("EEMMonlybest","PATEleEleEleEleBestSelector","EEMMosDiElectronsIso","EEMMosDiMuonsIso","Best Zmm MMEE")

EEMManalysisConfigurator.addDiCandidateModule('EEMMzzCands','PATEleEleMuMuQuadProducer','EEMMosDiElectronsIso','EEMMosDiMuonsIso','smearedMETEEMM','smearedJetsEEMM',1,9999,text='EEMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
#3b. Apply 40<mZ1<120) 
EEMManalysisConfigurator.addSelector('EEMMosDiElectronsMassReq','PATEleEleMuMuQuadSelector','(leg1.mass>40&&leg1.mass<120)','40 lt mZ1 lt 120 eemm',1)
##4b. At least one another pair (SF/OS) 
EEMManalysisConfigurator.addCrossCleanerModule('EEMMzzCleanedCands','PATEleEleMuMuQuadCrossCleaner',1,9999,text='cross cleaned eemm',dR = 0.01)
EEMManalysisConfigurator.addSorter('EEMMSorted','PATEleEleMuMuQuadSorterByZMass')
##4d. Apply mll cuts (4<mZ2<120) 
EEMManalysisConfigurator.addSelector('EEMMzzCleanedZ2Mass','PATEleEleMuMuQuadSelector','leg2.mass()>4&&leg2.mass<120','EEMMSecondZCharge')
##5. Ensure there are two offline leptons with PT>20,10
EEMManalysisConfigurator.addSelector('EEMMzzPt','PATEleEleMuMuQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req eemm',1) 
##6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
EEMManalysisConfigurator.addInvMassModule('EEMMzzInvMass','PATEleEleMuMuQuadInvMassSelector',1,9999,text='m2l gt 4 for all eemm',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
EEMManalysisConfigurator.addSelector('EEMMZ4lSpace','PATEleEleMuMuQuadSelector','mass>70','Z to 4l phasespace eemm',1)
##8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
EEMManalysisConfigurator.addSelector('EEMMHSpace','PATEleEleMuMuQuadSelector','mass>100&&leg2.mass>12&&leg2.mass<120','Higgs phasespace eemm',1)
EEMManalysisConfigurator.addSorter('EEMMFinalSel','PATEleEleMuMuQuadSorterByZMass')
EEMMselectionSequence =EEMManalysisConfigurator.returnSequence()

###--------- MMEE only ----------###

MMEEonlyanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEEonly',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEonlyanalysisConfigurator.addHLTFilter("MMEEonlyHLT",DATAMC2012TriggerPaths,"MMEEonly HLT_req")
MMEEonlyanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMEEonly')

MMEEonlyanalysisConfigurator.addDiCandidateModule('MMEEonlydiMuons','PATMuPairProducer', 'smearedMuonsMMEE','smearedMuonsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')

#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyosDiMuonsnoPF','PATMuPairSelector','charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEEonly no pf',1)
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEE only',1)
MMEEonlyanalysisConfigurator.addFSRRecovery('MMEEonlyfsredMM','MuMuZFSRRecovery','MMEEonlyosDiMuons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons')
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','one Z1 with iso MMEE only',1)

MMEEonlyanalysisConfigurator.addDiCandidateModule('MMEEonlydiElectrons','PATElePairProducer', 'smearedElectronsMMEE','smearedElectronsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0 && leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg1.pt()>7 && abs(leg1.eta())<2.5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0&&leg2.userFloat("mvaNonTrigV0Pass")>0 && leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2 && leg2.pt()>7 && abs(leg2.eta())<2.5 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0  ','',1)
MMEEonlyanalysisConfigurator.addFSRRecovery('MMEEonlyfsredEE','EleEleZFSRRecovery','MMEEonlyosDiElectrons','boostedFsrPhotons','mvaedElectrons','cleanPatMuons')
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1PhotonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2PhotonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','a Z with iso ee should cut none mmee only',1)

#Don't require best--want the overlap numbers
#MMEEonlyanalysisConfigurator.addBestSelector("MMEEonlybest","PATMuMuMuMuBestSelector","MMEEonlyosDiMuonsIso","MMEEonlyosDiElectronsIso","Best Zmm MMEE")

MMEEonlyanalysisConfigurator.addDiCandidateModule('MMEEonlyzzCands','PATMuMuEleEleQuadProducer','MMEEonlyosDiMuonsIso','MMEEonlyosDiElectronsIso','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEonlyAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
#3b. Apply 40<mZ1<120) 
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyosDiMuonsMassReq','PATMuMuEleEleQuadSelector','(leg1.mass>40&&leg1.mass<120)','40 lt mZ1 lt 120 mmee only',1)
##4b. At least one another pair (SF/OS) 
MMEEonlyanalysisConfigurator.addCrossCleanerModule('MMEEonlyzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='cross cleaned mmee',dR = 0.01)
MMEEonlyanalysisConfigurator.addSorter('MMEEonlySorted','PATMuMuEleEleQuadSorterByZMass')
##4d. Apply mll cuts (4<mZ2<120) 
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyzzCleanedZ2Mass','PATMuMuEleEleQuadSelector','leg2.mass()>4&&leg2.mass()<120','MMEEonlySecondZCharge')
##5. Ensure there are two offline leptons with PT>20,10
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyzzPt','PATMuMuEleEleQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req mmee only',1) 
##6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
MMEEonlyanalysisConfigurator.addInvMassModule('MMEEonlyzzInvMass','PATMuMuEleEleQuadInvMassSelector',1,9999,text='m2l gt 4 for all mmee only',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyZ4lSpace','PATMuMuEleEleQuadSelector','mass>70','Z to 4l phasespace mmee only',1)
##8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
MMEEonlyanalysisConfigurator.addSelector('MMEEonlyHSpace','PATMuMuEleEleQuadSelector','mass>100&&leg2.mass()>12','Higgs phasespace mmee only',1)
MMEEonlyanalysisConfigurator.addSorter('MMEEonlyFinalSel','PATMuMuEleEleQuadSorterByZMass')
MMEEonlyselectionSequence =MMEEonlyanalysisConfigurator.returnSequence()

# hey, don't forget 2l2tau

######################__________________________________MMMT_____________________________________##############################

MMMTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
MMMTanalysisConfigurator.addHLTFilter("MMMTHLT",DATAMC2012TriggerPaths,"HLT_req_MMMT")

MMMTanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMMT')
MMMTanalysisConfigurator.addDiCandidateModule('MMMTdiMuons','PATMuPairProducer', 'smearedMuonsMMMT','smearedMuonsMMMT','smearedMETMMMT','smearedJetsMMMT',1,genParticles='genDaughters')
MMMTanalysisConfigurator.addSelector('MMMTosDiMuons','PATMuPairSelector','charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMMTDiMuonCreation',1)
MMMTanalysisConfigurator.addSelector('MMMTosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','MMMTDiMuonIso',1)
MMMTanalysisConfigurator.addDiCandidateModule('MMMTmuTau','PATMuTauPairProducer', 'smearedMuonsMMMT','smearedTausMMMT','smearedMETMMMT','smearedJetsMMMT',1,9999,text = 'MMMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
MMMTanalysisConfigurator.addDiCandidateModule('MMMTzzCands','PATMuMuMuTauQuadProducer','MMMTosDiMuons','MMMTmuTau','smearedMETMMMT','smearedJetsMMMT',1,9999,text='MMMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMMTanalysisConfigurator.addCrossCleanerModule('MMMTzzCleanedCands','PATMuMuMuTauQuadCrossCleaner',1,9999,text='MMMTAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMTanalysisConfigurator.addSelector('MMMTzzMuID2','PATMuMuMuTauQuadSelector','leg2.leg1.userInt("tightID")>0 && abs (leg2.leg1.eta())<2.5','MMMTSecondZMuID')

MMMTanalysisConfigurator.addSelector('MMMTzzTauID','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','MMMTTauDecayModeFinding')
MMMTanalysisConfigurator.addSelector('MMMTzzTauDiscr','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonTight")','MMMTTauLeptonDiscrimantor')

MMMTanalysisConfigurator.addSelector('MMMTzzMuIso2','PATMuMuMuTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','MMMTSecondZMuIso')

MMMTanalysisConfigurator.addSelector('MMMTzzTauIso','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("byMediumIsolationMVA")','MMMTTauMedIsolationMVA')
MMMTanalysisConfigurator.addSorter('MMMTzzCleanedCandsSortedByZMass','PATMuMuMuTauQuadSorterByZMass')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsAboveThreshold','PATMuMuMuTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.4 && abs(leg2.leg2.eta())<2.3','MMMTAtLeastOneZZCandOverThresholds')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsMuTauQ','PATMuMuMuTauQuadSelector','leg2.charge()==0','MMMTMuTauCharge')

MMMTanalysisConfigurator.addSelector('MMMTzzdZ','PATMuMuMuTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','MMMTdZ')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsMMMass','PATMuMuMuTauQuadSelector','leg1.mass()>60&&leg1.mass()<120','MMMTMMMass')
MMMTanalysisConfigurator.addSorter('MMMTFinalSel','PATMuMuMuTauQuadSorterByZMass')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsMTMass','PATMuMuMuTauQuadSelector','leg2.mass()>30&&leg2.mass()<90','MMMTMTMass')
#create the sequence
MMMTselectionSequence =MMMTanalysisConfigurator.returnSequence()

######################__________________________________MMTT_____________________________________##############################


MMTTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMTT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
MMTTanalysisConfigurator.addHLTFilter("MMTTHLT",DATAMC2012TriggerPaths,"HLT_reqMMTT")

MMTTanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMTT')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiMuons','PATMuPairProducer', 'smearedMuonsMMTT','smearedMuonsMMTT','smearedMETMMTT','smearedJetsMMTT',1,genParticles='genDaughters')
MMTTanalysisConfigurator.addSelector('MMTTosDiMuons','PATMuPairSelector','mass>40 && charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMTTDiMuonCreation',1)
MMTTanalysisConfigurator.addSelector('MMTTosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','MMTTDiMuonIso',1)
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiTaus','PATDiTauPairProducer','smearedTausMMTT','smearedTausMMTT','smearedMETMMTT','smearedJetsMMTT',1,9999,text='MMTTAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTzzCands','PATMuMuTauTauQuadProducer','MMTTosDiMuons','MMTTdiTaus','smearedMETMMTT','smearedJetsMMTT',1,9999,text='MMTTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMTTanalysisConfigurator.addCrossCleanerModule('MMTTzzCleanedCands','PATMuMuTauTauQuadCrossCleaner',1,9999,text='MMTTAtLeastOneZZCleanedCandidate',dR = 0.1) 

MMTTanalysisConfigurator.addSelector('MMTTzzTauID','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','MMTTDecayModeFinding')
MMTTanalysisConfigurator.addSelector('MMTTzzTauDiscr','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("againstElectronMedium")&&leg2.leg1.tauID("againstMuonMedium")&&leg2.leg2.tauID("againstElectronMedium")&&leg2.leg2.tauID("againstMuonMedium")','MMTTTauLeptonDiscrimantor')
MMTTanalysisConfigurator.addSelector('MMTTzzTauIso','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("byTightIsolationMVA")&&leg2.leg2.tauID("byTightIsolationMVA")','MMTTTauIsolation')
MMTTanalysisConfigurator.addSorter('MMTTzzCleanedCandsSortedByZMass','PATMuMuTauTauQuadSorterByZMass')
MMTTanalysisConfigurator.addSelector('MMTTzzdZ','PATMuMuTauTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','MMTTdZ')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsAboveThreshold','PATMuMuTauTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>20 &&leg2().leg2().pt()>20  && abs(leg2.leg1.eta())<2.3  && abs(leg2.leg2.eta())<2.3','MMTTAtLeastOneZZCandOverThresholds')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsTauTauQ','PATMuMuTauTauQuadSelector','leg2.charge()==0','TauTauChargeMMTT')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsMMMass','PATMuMuTauTauQuadSelector','leg1.mass()>60&&leg1.mass()<120','MMTTMMMass')
MMTTanalysisConfigurator.addSorter('MMTTFinalSel','PATMuMuTauTauQuadSorterByZMass')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsTTMass','PATMuMuTauTauQuadSelector','leg2.mass()>30&&leg2.mass()<90','MMTTTTMass')
MMTTselectionSequence =MMTTanalysisConfigurator.returnSequence()


######################__________________________________MMET_____________________________________##############################

MMETanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMET',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

MMETanalysisConfigurator.addHLTFilter("MMETHLT",DATAMC2012TriggerPaths,"HLT_reqMMET")
MMETanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMET')
MMETanalysisConfigurator.addDiCandidateModule('MMETdiMuons','PATMuPairProducer', 'smearedMuonsMMET','smearedMuonsMMET','smearedMETMMET','smearedJetsMMET',1,genParticles='genDaughters')
MMETanalysisConfigurator.addSelector('MMETosDiMuons','PATMuPairSelector','mass>40 && charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMETDiMuonCreation',1)
MMETanalysisConfigurator.addSelector('MMETosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','MMETDiMuonIso',1)
MMETanalysisConfigurator.addDiCandidateModule('MMETelecTau','PATEleTauPairProducer','smearedElectronsMMET','smearedTausMMET','smearedMETMMET','smearedJetsMMET',1,9999,text='MMETAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addDiCandidateModule('MMETzzCands','PATMuMuEleTauQuadProducer','MMETosDiMuons','MMETelecTau','smearedMETMMET','smearedJetsMMET',1,9999,text='MMETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addCrossCleanerModule('MMETzzCleanedCands2','PATMuMuEleTauQuadCrossCleaner',1,9999,text='MMETAtLeastOneZZCleanedCandidate',dR = 0.1)
MMETanalysisConfigurator.addSelector('MMETzzCleanedEleID','PATMuMuEleTauQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','MMETEleID')
MMETanalysisConfigurator.addSelector('MMETzzCleanedEleIso','PATMuMuEleTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.10','MMETEleIso')
MMETanalysisConfigurator.addSelector('MMETzzTauID','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','MMETDecayModeFinding')
MMETanalysisConfigurator.addSelector('MMETzzTauIso','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("byMediumIsolationMVA")','MMETTauLooseIsolation')
MMETanalysisConfigurator.addSorter('MMETzzCleanedCandsSortedByZMass','PATMuMuEleTauQuadSorterByZMass')
MMETanalysisConfigurator.addSelector('MMETzzdZ','PATMuMuEleTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','MMETdZ')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsAboveThreshold','PATMuMuEleTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.3','MMETAtLeastOneZZCandOverThresholds')
MMETanalysisConfigurator.addSelector('MMETzzTauDiscr','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("againstElectronMVA")&&leg2.leg2.tauID("againstElectronMedium")&&leg2.leg2.tauID("againstMuonLoose")','MMETTauLeptonDiscrimantor')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsETauQ','PATMuMuEleTauQuadSelector','leg2.charge()==0','MMETEleTauCharge')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsMMMass','PATMuMuEleTauQuadSelector','leg1.mass()>60&&leg1.mass()<120','MMETMMMass')
MMETanalysisConfigurator.addSorter('MMETFinalSel','PATMuMuEleTauQuadSorterByZMass')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsETMass','PATMuMuEleTauQuadSelector','leg2.mass()>30&&leg2.mass()<90','MMETETMass')
MMETselectionSequence =MMETanalysisConfigurator.returnSequence()


######################__________________________________MMEM_____________________________________##############################

MMEManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEM',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

MMEManalysisConfigurator.addHLTFilter("MMEMHLT",DATAMC2012TriggerPaths,"HLT_reqMMEM")
MMEManalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMEM')
MMEManalysisConfigurator.addDiCandidateModule('MMEMdiMuons','PATMuPairProducer', 'smearedMuonsMMEM','smearedMuonsMMEM','smearedMETMMEM','smearedJetsMMEM',1,genParticles='genDaughters')
MMEManalysisConfigurator.addSelector('MMEMosDiMuons','PATMuPairSelector','mass>40 && charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMEMDiMuonCreation',1)
MMEManalysisConfigurator.addSelector('MMEMosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','MMEMDiMuonIso',1)
MMEManalysisConfigurator.addDiCandidateModule('MMEMelecMu','PATEleMuPairProducer','smearedElectronsMMEM','smearedMuonsMMEM','smearedMETMMEM','smearedJetsMMEM',1,9999,text='MMEMAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addDiCandidateModule('MMEMzzCands','PATMuMuEleMuQuadProducer','MMEMosDiMuons','MMEMelecMu','smearedMETMMEM','smearedJetsMMEM',1,9999,text='MMEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addCrossCleanerModule('MMEMzzCleanedCands','PATMuMuEleMuQuadCrossCleaner',1,9999,text='MMEMAtLeastOneZZCleanedCandidate',dR = 0.1)

MMEManalysisConfigurator.addSelector('MMEMzzCleanedThirdMuID','PATMuMuEleMuQuadSelector','leg2.leg2.userInt("tightID")>0.5 && abs(leg2.leg2.eta())<2.5','MMEMThirdMuID')
MMEManalysisConfigurator.addSelector('MMEMzzEleId','PATMuMuEleMuQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','MMEMEleCiCLoose') 
MMEManalysisConfigurator.addSelector('MMEMzzEleIso','PATMuMuEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','MMEMEleIso')
MMEManalysisConfigurator.addSelector('MMEMzzMuIso2','PATMuMuEleMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho2012")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.25','MMEMMuIso')
MMEManalysisConfigurator.addSorter('MMEMzzCleanedCandsSortedByZMass','PATMuMuEleMuQuadSorterByZMass')
MMEManalysisConfigurator.addSelector('MMEMzzdZ','PATMuMuEleMuQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','MMEMdZ')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedCandsAboveThreshold','PATMuMuEleMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 && leg2().leg2().pt()>10 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.4','MMEMAtLeastOneZZCandOverThresholds')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedCandsEMuQ','PATMuMuEleMuQuadSelector','leg2.charge()==0','MMEMEleMuCharge')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedCandsMMMass','PATMuMuEleMuQuadSelector','leg1.mass()>60&&leg1.mass()<120','MMEMMMMass')
MMEManalysisConfigurator.addSorter('MMEMFinalSel','PATMuMuEleMuQuadSorterByZMass')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedCandsETMass','PATMuMuEleMuQuadSelector','leg2.mass()<90','MMEMEMMass')
MMEMselectionSequence =MMEManalysisConfigurator.returnSequence()

######################__________________________________EEMT_____________________________________##############################

EEMTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEMT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

EEMTanalysisConfigurator.addHLTFilter("EEMTHLT",DATAMC2012TriggerPaths,"HLT_reqEEMT")
EEMTanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEMT')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTdiElectrons','PATElePairProducer', 'smearedElectronsEEMT','smearedElectronsEEMT','smearedMETEEMT','smearedJetsEEMT',1,genParticles='genDaughters')

EEMTanalysisConfigurator.addSelector('EEMTosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EEMTDiEleCreation',1)
EEMTanalysisConfigurator.addSelector('EEMTosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','EEMTDiEleIso',1)

EEMTanalysisConfigurator.addDiCandidateModule('EEMTmuTau','PATMuTauPairProducer', 'smearedMuonsEEMT','smearedTausEEMT','smearedMETEEMT','smearedJetsEEMT',1,9999,text = 'EEMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTzzCands','PATEleEleMuTauQuadProducer','EEMTosDiElectrons','EEMTmuTau','smearedMETEEMT','smearedJetsEEMT',1,9999,text='EEMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEMTanalysisConfigurator.addCrossCleanerModule('EEMTzzCleanedCands','PATEleEleMuTauQuadCrossCleaner',1,9999,text='EEMTAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMTanalysisConfigurator.addSelector('EEMTzzMuID2','PATEleEleMuTauQuadSelector','leg2.leg1.userInt("tightID")>0 && abs (leg2.leg1.eta())<2.5','EEMTSecondZMuID')
EEMTanalysisConfigurator.addSelector('EEMTzzTauID','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','EEMTTauDecayModeFinding')
EEMTanalysisConfigurator.addSelector('EEMTzzTauDiscr','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonTight")','EEMTTauLeptonDiscrimantor')
EEMTanalysisConfigurator.addSelector('EEMTzzMuIso2','PATEleEleMuTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','EEMTSecondZMuIso')
EEMTanalysisConfigurator.addSelector('EEMTzzTauIso','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("byMediumIsolationMVA")','EEMTTauMedIsolationMVA')
EEMTanalysisConfigurator.addSorter('EEMTzzCleanedCandsSortedByZMass','PATEleEleMuTauQuadSorterByZMass')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsAboveThreshold','PATEleEleMuTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.4 && abs(leg2.leg2.eta())<2.3','EEMTAtLeastOneZZCandOverThresholds')
EEMTanalysisConfigurator.addSelector('EEMTzzdZ','PATEleEleMuTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EEMTdZ')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsMuTauQ','PATEleEleMuTauQuadSelector','leg2.charge()==0','EEMTMuTauCharge')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsEEMass','PATEleEleMuTauQuadSelector','leg1.mass()>60&&leg1.mass()<120','EEMTEEMass')
EEMTanalysisConfigurator.addSorter('EEMTFinalSel','PATEleEleMuTauQuadSorterByZMass')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsMTMass','PATEleEleMuTauQuadSelector','leg2.mass()>30&&leg2.mass()<90','EEMTMTMass')
EEMTselectionSequence =EEMTanalysisConfigurator.returnSequence()


######################__________________________________EEET_____________________________________##############################

EEETanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEET',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

EEETanalysisConfigurator.addHLTFilter("EEETHLT",DATAMC2012TriggerPaths,"HLT_reqEEET")
EEETanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEET')
EEETanalysisConfigurator.addDiCandidateModule('EEETdiElectrons','PATElePairProducer', 'smearedElectronsEEET','smearedElectronsEEET','smearedMETEEET','smearedJetsEEET',1,genParticles='genDaughters')
EEETanalysisConfigurator.addSelector('EEETosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EEETDiEleCreation',1)
EEETanalysisConfigurator.addSelector('EEETosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','EEETDiEleIso',1)
EEETanalysisConfigurator.addDiCandidateModule('EEETeleTau','PATEleTauPairProducer', 'smearedElectronsEEET','smearedTausEEET','smearedMETEEET','smearedJetsEEET',1,9999,text = 'EEETAtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETanalysisConfigurator.addDiCandidateModule('EEETzzCands','PATEleEleEleTauQuadProducer','EEETosDiElectrons','EEETeleTau','smearedMETEEET','smearedJetsEEET',1,9999,text='EEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEETanalysisConfigurator.addCrossCleanerModule('EEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='EEETAtLeastOneZZCleanedCandidate',dR = 0.1)
EEETanalysisConfigurator.addSelector('EEETzzCleanedEleID','PATEleEleEleTauQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','EEETEleID')
EEETanalysisConfigurator.addSelector('EEETzzCleanedEleIso','PATEleEleEleTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.10','EEETEleIso')
EEETanalysisConfigurator.addSelector('EEETzzTauID','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','EEETDecayModeFinding')
EEETanalysisConfigurator.addSelector('EEETzzTauIso','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("byMediumIsolationMVA")','EEETTauLooseIsolation')
EEETanalysisConfigurator.addSorter('EEETzzCleanedCandsSortedByZMass','PATEleEleEleTauQuadSorterByZMass')
EEETanalysisConfigurator.addSelector('EEETzzdZ','PATEleEleEleTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EEETdZ')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsAboveThreshold','PATEleEleEleTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.3','EEETAtLeastOneZZCandOverThresholds')
EEETanalysisConfigurator.addSelector('EEETzzTauDiscr','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("againstElectronMVA")&&leg2.leg2.tauID("againstElectronMedium")&&leg2.leg2.tauID("againstMuonLoose")','EEETTauLeptonDiscrimantor')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsETauQ','PATEleEleEleTauQuadSelector','leg2.charge()==0','EEETEleTauCharge')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsMMMass','PATEleEleEleTauQuadSelector','leg1.mass()>60&&leg1.mass()<120','EEETMMMass')
EEETanalysisConfigurator.addSorter('EEETFinalSel','PATEleEleEleTauQuadSorterByZMass')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsETMass','PATEleEleEleTauQuadSelector','leg2.mass()>30&&leg2.mass()<90','EEETETMass')
EEETselectionSequence =EEETanalysisConfigurator.returnSequence()


######################__________________________________EETT_____________________________________##############################

EETTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEETT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())

EETTanalysisConfigurator.addHLTFilter("EETTHLT",DATAMC2012TriggerPaths,"HLT_reqEETT")
EETTanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EETT')
EETTanalysisConfigurator.addDiCandidateModule('EETTdiElectrons','PATElePairProducer', 'smearedElectronsEETT','smearedElectronsEETT','smearedMETEETT','smearedJetsEETT',1,genParticles='genDaughters')
EETTanalysisConfigurator.addSelector('EETTosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EETTDiEleCreation',1)

EETTanalysisConfigurator.addSelector('EETTosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','EETTDiEleIso',1)
EETTanalysisConfigurator.addDiCandidateModule('EETTtauTau','PATDiTauPairProducer', 'smearedTausEETT','smearedTausEETT','smearedMETEETT','smearedJetsEETT',1,9999,text = 'EETTAtLeastOnediTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EETTanalysisConfigurator.addDiCandidateModule('EETTzzCands','PATEleEleTauTauQuadProducer','EETTosDiElectrons','EETTtauTau','smearedMETEETT','smearedJetsEETT',1,9999,text='EETTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EETTanalysisConfigurator.addCrossCleanerModule('EETTzzCleanedCands','PATEleEleTauTauQuadCrossCleaner',1,9999,text='EETTAtLeastOneZZCleanedCandidate',dR = 0.1)


EETTanalysisConfigurator.addSelector('EETTzzTauID','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','EETTDecayModeFinding')
EETTanalysisConfigurator.addSelector('EETTzzTauDiscr','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("againstElectronMedium")&&leg2.leg1.tauID("againstMuonMedium")&&leg2.leg2.tauID("againstElectronMedium")&&leg2.leg2.tauID("againstMuonMedium")','EETTTauLeptonDiscrimantor')
EETTanalysisConfigurator.addSelector('EETTzzTauIso','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("byTightIsolationMVA")&&leg2.leg2.tauID("byTightIsolationMVA")','EETTTauIsolation')
EETTanalysisConfigurator.addSorter('EETTzzCleanedCandsSortedByZMass','PATEleEleTauTauQuadSorterByZMass')
EETTanalysisConfigurator.addSelector('EETTzzdZ','PATEleEleTauTauQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EETTdZ')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsAboveThreshold','PATEleEleTauTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>20 &&leg2().leg2().pt()>20  && abs(leg2.leg1.eta())<2.3  && abs(leg2.leg2.eta())<2.3','EETTAtLeastOneZZCandOverThresholds')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsTauTauQ','PATEleEleTauTauQuadSelector','leg2.charge()==0','TauTauChargeEETT')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsMMMass','PATEleEleTauTauQuadSelector','leg1.mass()>60&&leg1.mass()<120','EETTMMMass')
EETTanalysisConfigurator.addSorter('EETTFinalSel','PATEleEleTauTauQuadSorterByZMass')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsTTMass','PATEleEleTauTauQuadSelector','leg2.mass()>30&&leg2.mass()<90','EETTTTMass')
EETTselectionSequence =EETTanalysisConfigurator.returnSequence()

######################__________________________________EEEM_____________________________________##############################

EEEManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEM',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
EEEManalysisConfigurator.addHLTFilter("EEEMHLT",DATAMC2012TriggerPaths,"HLT_reqEEEM")
EEEManalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEEM')
EEEManalysisConfigurator.addDiCandidateModule('EEEMdiElectrons','PATElePairProducer', 'smearedElectronsEEEM','smearedElectronsEEEM','smearedMETEEEM','smearedJetsEEEM',1,genParticles='genDaughters')
EEEManalysisConfigurator.addSelector('EEEMosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EEEMDiEleCreation',1)
EEEManalysisConfigurator.addSelector('EEEMosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','EEEMDiEleIso',1)

EEEManalysisConfigurator.addDiCandidateModule('EEEMeleMu','PATEleMuPairProducer', 'smearedElectronsEEEM','smearedMuonsEEEM','smearedMETEEEM','smearedJetsEEEM',1,9999,text = 'EEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEEManalysisConfigurator.addDiCandidateModule('EEEMzzCands','PATEleEleEleMuQuadProducer','EEEMosDiElectrons','EEEMeleMu','smearedMETEEEM','smearedJetsEEEM',1,9999,text='EEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEEManalysisConfigurator.addCrossCleanerModule('EEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='EEEMAtLeastOneZZCleanedCandidate',dR = 0.1)


EEEManalysisConfigurator.addSelector('EEEMzzCleanedThirdMuID','PATEleEleEleMuQuadSelector','leg2.leg2.userInt("tightID")>0.5 && abs(leg2.leg2.eta())<2.5','EEEMThirdMuID')
EEEManalysisConfigurator.addSelector('EEEMzzEleId','PATEleEleEleMuQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','EEEMEleCiCLoose') 
EEEManalysisConfigurator.addSelector('EEEMzzEleIso','PATEleEleEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','EEEMEleIso')
EEEManalysisConfigurator.addSelector('EEEMzzMuIso2','PATEleEleEleMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho2012")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.25','EEEMMuIso')
EEEManalysisConfigurator.addSorter('EEEMzzCleanedCandsSortedByZMass','PATEleEleEleMuQuadSorterByZMass')
EEEManalysisConfigurator.addSelector('EEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EEEMdZ')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsAboveThreshold','PATEleEleEleMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 && leg2().leg2().pt()>10 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.4','EEEMAtLeastOneZZCandOverThresholds')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsEMuQ','PATEleEleEleMuQuadSelector','leg2.charge()==0','EEEMEleMuCharge')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsMMMass','PATEleEleEleMuQuadSelector','leg1.mass()>60&&leg1.mass()<120','EEEMMMMass')
EEEManalysisConfigurator.addSorter('EEEMFinalSel','PATEleEleEleMuQuadSorterByZMass')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsETMass','PATEleEleEleMuQuadSelector','leg2.mass()<90','EEEMEMMass')
EEEMselectionSequence =EEEManalysisConfigurator.returnSequence()





######################__________________________________EEES_____________________________________##############################

EEESanalysisConfigurator = CutSequenceProducer(
        initialCounter  = 'initialEventsEEES',
        pyModuleName = __name__,
        pyNameSpace  = locals()
        )
#EEEManalysisConfigurator.addHLTFilter("EEEMHLT",DATAMC2012TriggerPaths,"HLT_reqEEEM")
EEESanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEES')
EEESanalysisConfigurator.addDiCandidateModule('EEESdiElectrons','PATElePairProducer', 'smearedElectronsEEES','smearedElectronsEEES','smearedMETEEES','smearedJetsEEES',1,genParticles='genDaughters')
EEESanalysisConfigurator.addSelector('EEESosDiElectrons','PATElePairSelector','charge == 0 && mass > 40 && leg1.userFloat("mvaNonTrigV0Pass") > 0 && leg2.userFloat("mvaNonTrigV0Pass") > 0 && abs(leg1.eta()) < 2.4 && abs(leg2.eta()) < 2.4','EEESDiEleCreation',1)
#EEESanalysisConfigurator.addSelector('EEEMosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho2012")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho2012")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','EEEMDiEleIso',1)

EEESanalysisConfigurator.addDiCandidateModule('EEESeleSC','PATEleSCPairProducer','smearedElectronsEEES','selectedPatPhotons','smearedMETEEES','smearedJetsEEES',1,9999,text = 'EEESAtLeastOneMuTau',leadingObjectsOnly = False, dR = 0.5, recoMode ="", genParticles='genDaughters')

EEESanalysisConfigurator.addDiCandidateModule('EEESzzCands','PATEleEleEleSCQuadProducer','EEESosDiElectrons','EEESeleSC','smearedMETEEES','smearedJetsEEES',1,9999,text='EEESAtLeastOneZZ',leadingObjectsOnly = False, dR = 0.005, recoMode="", genParticles='genDaughters')
EEESanalysisConfigurator.addCrossCleanerModule('EEESzzCleanedCands','PATEleEleEleSCQuadCrossCleaner',1,9999,text='EEESAtLeastOneZZCleanedCandidate',dR = 0.1)

EEESanalysisConfigurator.addSelector('EEESzzEleIso','PATEleEleEleSCQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','EEESEleIso')

EEESanalysisConfigurator.addSorter('EEESzzCleanedCandsSortedByZMass','PATEleEleEleSCQuadSorterByZMass')

#EEEManalysisConfigurator.addDiCandidateModule('EEEMeleMu','PATEleMuPairProducer', 'smearedElectronsEEEM','smearedMuonsEEEM','smearedMETEEEM','smearedJetsEEEM',1,9999,text = 'EEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
#EEEManalysisConfigurator.addDiCandidateModule('EEEMzzCands','PATEleEleEleMuQuadProducer','EEEMosDiElectrons','EEEMeleMu','smearedMETEEEM','smearedJetsEEEM',1,9999,text='EEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
#EEEManalysisConfigurator.addCrossCleanerModule('EEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='EEEMAtLeastOneZZCleanedCandidate',dR = 0.1)


#EEEManalysisConfigurator.addSelector('EEEMzzCleanedThirdMuID','PATEleEleEleMuQuadSelector','leg2.leg2.userInt("tightID")>0.5 && abs(leg2.leg2.eta())<2.5','EEEMThirdMuID')
#EEEManalysisConfigurator.addSelector('EEEMzzEleId','PATEleEleEleMuQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','EEEMEleCiCLoose') 
#EEEManalysisConfigurator.addSelector('EEEMzzEleIso','PATEleEleEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho2012")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','EEEMEleIso')
#EEEManalysisConfigurator.addSelector('EEEMzzMuIso2','PATEleEleEleMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho2012")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.25','EEEMMuIso')
#EEEManalysisConfigurator.addSorter('EEEMzzCleanedCandsSortedByZMass','PATEleEleEleMuQuadSorterByZMass')
#EEEManalysisConfigurator.addSelector('EEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EEEMdZ')
#EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsAboveThreshold','PATEleEleEleMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 && leg2().leg2().pt()>10 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.4','EEEMAtLeastOneZZCandOverThresholds')
#EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsEMuQ','PATEleEleEleMuQuadSelector','leg2.charge()==0','EEEMEleMuCharge')
#EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsMMMass','PATEleEleEleMuQuadSelector','leg1.mass()>60&&leg1.mass()<120','EEEMMMMass')
#EEEManalysisConfigurator.addSorter('EEEMFinalSel','PATEleEleEleMuQuadSorterByZMass')
#EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsETMass','PATEleEleEleMuQuadSelector','leg2.mass()<90','EEEMEMMass')

EEESselectionSequence = EEESanalysisConfigurator.returnSequence()



######################_______________________________EndOfConfigurators__________________________################################
