import FWCore.ParameterSet.Config as cms

from UWAnalysis.Configuration.tools.CutSequenceProducer import *

MC2011TriggerPaths=["HLT_Mu17_Mu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]
DATA2011TriggerPaths=["HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL","HLT_Mu17_Mu8","HLT_DoubleMu7","HLT_Mu13_Mu8"]
DATAMC2012TriggerPaths=["HLT_Mu17_Mu8","HLT_Mu17_TkMu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]

MMMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMManalysisConfigurator.addHLTFilter("MMMMHLT",DATAMC2012TriggerPaths,"HLT_req")
MMMManalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMMM')

MMMManalysisConfigurator.addDiCandidateModule('MMMMdiMuons','PATMuPairProducer', 'smearedMuonsMMMM','smearedMuonsMMMM','smearedMETMMMM','smearedJetsMMMM',1,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMMManalysisConfigurator.addSelector('MMMMosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1',1)
MMMManalysisConfigurator.addSelector('MMMMosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','one Z1 with iso',1)

MMMManalysisConfigurator.addDiCandidateModule('MMMMdiElectrons','PATElePairProducer', 'smearedElectronsMMMM','smearedElectronsMMMM','smearedMETMMMM','smearedJetsMMMM',0,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMMManalysisConfigurator.addSelector('MMMMosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0&&leg2.userFloat("mvaNonTrigV0Pass")>0&&leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg1.pt()>7&&leg2.pt()>7&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5','',0)
MMMManalysisConfigurator.addSelector('MMMMosDiElectronsSIP','PATElePairSelector','abs(leg1.userFloat("ip3DS"))<4&&abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','',0)
MMMManalysisConfigurator.addSelector('MMMMosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','',0)

MMMManalysisConfigurator.addBestSelector("MMMMbest","PATMuMuMuMuBestSelector","MMMMosDiMuonsIso","MMMMosDiElectronsIso","Best Zmm")

#3b. Apply 40<mZ1<120) 
MMMManalysisConfigurator.addSelector('MMMMosDiMuonsMassReq','PATMuPairSelector','mass>40&&mass<120','40 lt mZ1 lt 120 mmmm',1)
#4b. At least one another pair (SF/OS) 
MMMManalysisConfigurator.addDiCandidateModule('MMMMzzCands','PATMuMuMuMuQuadProducer','MMMMosDiMuonsIso','MMMMosDiMuonsIso','smearedMETMMMM','smearedJetsMMMM',1,9999,text='MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMMManalysisConfigurator.addCrossCleanerModule('MMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='cross cleaned',dR = 0.01)
#4c. Pair #2 built (SF/OS, highest pT leptons) 
MMMManalysisConfigurator.addSelector('MMMMzzCleanedMuIso','PATMuMuMuMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.40 && (leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.40 ','two good Zs should lose none',1)
#4d. Apply mll cuts (4<mZ2<120) 
MMMManalysisConfigurator.addSelector('MMMMzzCleanedZ2Mass','PATMuMuMuMuQuadSelector','leg2.mass()>4&&leg2.mass()<120','z2 mass 4 to 120')
#5. Ensure there are two offline leptons with PT>20,10
MMMManalysisConfigurator.addSelector('MMMMzzPt','PATMuMuMuMuQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req',1) 
#6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
MMMManalysisConfigurator.addInvMassModule('MMMMzzInvMass','PATMuMuMuMuQuadInvMassSelector',1,9999,text='m4l gt 4 for all',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
MMMManalysisConfigurator.addSelector('MMMMZ4lSpace','PATMuMuMuMuQuadSelector','mass>70','Z to 4l phasespace',1)
#8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
MMMManalysisConfigurator.addSorter('MMMMFinalSel','PATMuMuMuMuQuadSorterByZMass')
MMMManalysisConfigurator.addSelector('MMMMHSpace','PATMuMuMuMuQuadSelector','mass>100&&leg2.mass()>12','Higgs phasespace',1)
MMMMselectionSequence =MMMManalysisConfigurator.returnSequence()

###--------- EEEE ----------###

EEEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEEEanalysisConfigurator.addHLTFilter("EEEEHLT",DATAMC2012TriggerPaths,"EEEE HLT_req")
EEEEanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEEE')

EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiElectrons','PATElePairProducer', 'smearedElectronsEEEE','smearedElectronsEEEE','smearedMETEEEE','smearedJetsEEEE',1,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
EEEEanalysisConfigurator.addSelector('EEEEosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0&&leg2.userFloat("mvaNonTrigV0Pass")>0&&leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg1.pt()>7&&leg2.pt()>7&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5','',1)
EEEEanalysisConfigurator.addSelector('EEEEosDiElectronsSIP','PATElePairSelector','abs(leg1.userFloat("ip3DS"))<4&&abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && leg2.userFloat("dz")<1.0','',1)
EEEEanalysisConfigurator.addSelector('EEEEosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','one Z1 with iso eeee',1)

#build dimuons for 'best' check
EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiMuons','PATMuPairProducer', 'smearedMuonsEEEE','smearedMuonsEEEE','smearedMETEEEE','smearedJetsEEEE',0,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
EEEEanalysisConfigurator.addSelector('EEEEosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','',0)
EEEEanalysisConfigurator.addSelector('EEEEosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','',0)

EEEEanalysisConfigurator.addBestSelector("EEEEbest","PATEleEleEleEleBestSelector","EEEEosDiElectronsIso","EEEEosDiMuonsIso","Good Zee")

##3b. Apply 40<mZ1<120) 
EEEEanalysisConfigurator.addSelector('EEEEosDiEleMassReq','PATElePairSelector','mass>40&&mass<120','40 lt mZ1 lt 120 eeee',1)
##4b. At least one another pair (SF/OS) 
EEEEanalysisConfigurator.addDiCandidateModule('EEEEzzCands','PATEleEleEleEleQuadProducer','EEEEosDiElectronsIso','EEEEosDiElectronsIso','smearedMETEEEE','smearedJetsEEEE',1,9999,text='EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
EEEEanalysisConfigurator.addCrossCleanerModule('EEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='cross cleaned eeee',dR = 0.01)
##4c. Pair #2 built (SF/OS, highest pT leptons) 
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedEleIso','PATEleEleEleEleQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.40 && (leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.40 ','two good Zs eeee',1)
##4d. Apply mll cuts (4<mZ2<120) 
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedZ2Mass','PATEleEleEleEleQuadSelector','leg2.mass()>4&&leg2.mass()<120','EEEE second z 4 to 120')
##5. Ensure there are two offline leptons with PT>20,10
EEEEanalysisConfigurator.addSelector('EEEEzzPt','PATEleEleEleEleQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req eeee',1) 
##6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
EEEEanalysisConfigurator.addInvMassModule('EEEEzzInvMass','PATEleEleEleEleQuadInvMassSelector',1,9999,text='m2l gt 4 for all eeee',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
EEEEanalysisConfigurator.addSelector('EEEEZ4lSpace','PATEleEleEleEleQuadSelector','mass>70','Z to 4l phasespace eeee',1)
##8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
EEEEanalysisConfigurator.addSorter('EEEEFinalSel','PATEleEleEleEleQuadSorterByZMass')
EEEEanalysisConfigurator.addSelector('EEEEHSpace','PATEleEleEleEleQuadSelector','mass>100&&leg2.mass()>12','Higgs phasespace eeee',1)
EEEEselectionSequence =EEEEanalysisConfigurator.returnSequence()


###--------- MMEE ----------###

MMEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEanalysisConfigurator.addHLTFilter("MMEEHLT",DATAMC2012TriggerPaths,"MMEE HLT_req")
MMEEanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMEE')

MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiMuons','PATMuPairProducer', 'smearedMuonsMMEE','smearedMuonsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')

#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsnoPF','PATMuPairSelector','mass()>4&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEE no pf',1)
MMEEanalysisConfigurator.addSelector('MMEEosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','one Z1 MMEE',1)
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','one Z1 with iso MMEE',1)

MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiElectrons','PATElePairProducer', 'smearedElectronsMMEE','smearedElectronsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')
MMEEanalysisConfigurator.addSelector('MMEEosDiElectrons','PATElePairSelector','mass()>4&&charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0&&leg2.userFloat("mvaNonTrigV0Pass")>0&&leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg1.pt()>7&&leg2.pt()>7&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&abs(leg1.userFloat("ip3DS"))<4&&abs(leg2.userFloat("ip3DS"))<4 && abs(leg1.userFloat("ipDXY"))<0.5 && abs(leg1.userFloat("dz"))<1.0 && abs(leg2.userFloat("ipDXY"))<0.5 && abs(leg2.userFloat("dz"))<1.0','',1)
MMEEanalysisConfigurator.addSelector('MMEEosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.40 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.40 ','a Z with iso ee should cut none',1)

MMEEanalysisConfigurator.addDiCandidateModule('MMEEzzCands','PATMuMuEleEleQuadProducer','MMEEosDiMuonsIso','MMEEosDiElectronsIso','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
#3b. Apply 40<mZ1<120) 
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsMassReq','PATMuMuEleEleQuadSelector','(leg1.mass>40&&leg1.mass<120)||(leg2.mass>40&&leg2.mass<120)','40 lt mZ1 lt 120 mmee',1)
##4b. At least one another pair (SF/OS) 
MMEEanalysisConfigurator.addCrossCleanerModule('MMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='cross cleaned mmee',dR = 0.01)
##4d. Apply mll cuts (4<mZ2<120) 
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedZ2Mass','PATMuMuEleEleQuadSelector','(leg1.mass()>40&&leg1.mass()<120&&leg2.mass()>4&&leg2.mass()<120)||(leg1.mass()>4&&leg1.mass()<120&&leg2.mass()>40&&leg2.mass()<120)','MMEESecondZCharge')
##5. Ensure there are two offline leptons with PT>20,10
MMEEanalysisConfigurator.addSelector('MMEEzzPt','PATMuMuEleEleQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req mmee',1) 
##6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
MMEEanalysisConfigurator.addInvMassModule('MMEEzzInvMass','PATMuMuEleEleQuadInvMassSelector',1,9999,text='m2l gt 4 for all mmee',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
MMEEanalysisConfigurator.addSelector('MMEEZ4lSpace','PATMuMuEleEleQuadSelector','mass>70','Z to 4l phasespace mmee',1)
##8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
MMEEanalysisConfigurator.addSorter('MMEEFinalSel','PATMuMuEleEleQuadSorterByZMass')
MMEEanalysisConfigurator.addSelector('MMEEHSpace','PATMuMuEleEleQuadSelector','mass>100&&((leg1.mass()>40&&leg1.mass()<120&&leg2.mass()>12)||(leg2.mass()>40&&leg2.mass()<120&&leg1.mass()>12))','Higgs phasespace mmee',1)
MMEEselectionSequence =MMEEanalysisConfigurator.returnSequence()

# hey, don't forget 2l2tau

######################__________________________________MMMT_____________________________________##############################

MMMTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMT',
                                          pyModuleName = __name__,
                                                                            pyNameSpace  = locals())
MMMTanalysisConfigurator.addHLTFilter("MMMTHLT",DATAMC2012TriggerPaths,"HLT_req_MMMT")

#MMMTanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMMT')
MMMTanalysisConfigurator.addDiCandidateModule('MMMTdiMuons','PATMuPairProducer', 'cleanPatMuons','cleanPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
MMMTanalysisConfigurator.addSelector('MMMTosDiMuons','PATMuPairSelector','charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMMTDiMuonCreation',1)
MMMTanalysisConfigurator.addSelector('MMMTosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','MMMTDiMuonIso',1)
MMMTanalysisConfigurator.addDiCandidateModule('MMMTmuTau','PATMuTauPairProducer', 'cleanPatMuons','llttTaus','systematicsMET','selectedPatJets',1,9999,text = 'MMMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
MMMTanalysisConfigurator.addDiCandidateModule('MMMTzzCands','PATMuMuMuTauQuadProducer','MMMTosDiMuons','MMMTmuTau','systematicsMET','selectedPatJets',1,9999,text='MMMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMMTanalysisConfigurator.addCrossCleanerModule('MMMTzzCleanedCands','PATMuMuMuTauQuadCrossCleaner',1,9999,text='MMMTAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMTanalysisConfigurator.addSelector('MMMTzzMuID2','PATMuMuMuTauQuadSelector','leg2.leg1.userInt("tightID")>0 && abs (leg2.leg1.eta())<2.5','MMMTSecondZMuID')

MMMTanalysisConfigurator.addSelector('MMMTzzTauID','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','MMMTTauDecayModeFinding')
MMMTanalysisConfigurator.addSelector('MMMTzzTauDiscr','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonTight")','MMMTTauLeptonDiscrimantor')

MMMTanalysisConfigurator.addSelector('MMMTzzMuIso2','PATMuMuMuTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','MMMTSecondZMuIso')

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

#MMTTanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMTT')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiMuons','PATMuPairProducer', 'cleanPatMuons','cleanPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
MMTTanalysisConfigurator.addSelector('MMTTosDiMuons','PATMuPairSelector','mass>40 && charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMTTDiMuonCreation',1)
MMTTanalysisConfigurator.addSelector('MMTTosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','MMTTDiMuonIso',1)
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiTaus','PATDiTauPairProducer','llttTaus','llttTaus','systematicsMET','selectedPatJets',1,9999,text='MMTTAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTzzCands','PATMuMuTauTauQuadProducer','MMTTosDiMuons','MMTTdiTaus','systematicsMET','selectedPatJets',1,9999,text='MMTTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
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
#MMETanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMET')
MMETanalysisConfigurator.addDiCandidateModule('MMETdiMuons','PATMuPairProducer', 'cleanPatMuons','cleanPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
MMETanalysisConfigurator.addSelector('MMETosDiMuons','PATMuPairSelector','mass>40 && charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMETDiMuonCreation',1)
MMETanalysisConfigurator.addSelector('MMETosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','MMETDiMuonIso',1)
MMETanalysisConfigurator.addDiCandidateModule('MMETelecTau','PATEleTauPairProducer','llttElectrons','llttTaus','systematicsMET','selectedPatJets',1,9999,text='MMETAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addDiCandidateModule('MMETzzCands','PATMuMuEleTauQuadProducer','MMETosDiMuons','MMETelecTau','systematicsMET','selectedPatJets',1,9999,text='MMETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addCrossCleanerModule('MMETzzCleanedCands2','PATMuMuEleTauQuadCrossCleaner',1,9999,text='MMETAtLeastOneZZCleanedCandidate',dR = 0.1)
MMETanalysisConfigurator.addSelector('MMETzzCleanedEleID','PATMuMuEleTauQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','MMETEleID')
MMETanalysisConfigurator.addSelector('MMETzzCleanedEleIso','PATMuMuEleTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.10','MMETEleIso')
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
#MMEManalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMEM')
MMEManalysisConfigurator.addDiCandidateModule('MMEMdiMuons','PATMuPairProducer', 'cleanPatMuons','cleanPatMuons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
MMEManalysisConfigurator.addSelector('MMEMosDiMuons','PATMuPairSelector','mass>40 && charge==0 && leg1.userInt("tightID")>0.5 && abs(leg1.eta()) < 2.5 && leg2.userInt("tightID")>0.5 && abs(leg2.eta())<2.5','MMEMDiMuonCreation',1)
MMEManalysisConfigurator.addSelector('MMEMosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','MMEMDiMuonIso',1)
MMEManalysisConfigurator.addDiCandidateModule('MMEMelecMu','PATEleMuPairProducer','llttElectrons','cleanPatMuons','systematicsMET','selectedPatJets',1,9999,text='MMEMAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addDiCandidateModule('MMEMzzCands','PATMuMuEleMuQuadProducer','MMEMosDiMuons','MMEMelecMu','systematicsMET','selectedPatJets',1,9999,text='MMEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addCrossCleanerModule('MMEMzzCleanedCands','PATMuMuEleMuQuadCrossCleaner',1,9999,text='MMEMAtLeastOneZZCleanedCandidate',dR = 0.1)

MMEManalysisConfigurator.addSelector('MMEMzzCleanedThirdMuID','PATMuMuEleMuQuadSelector','leg2.leg2.userInt("tightID")>0.5 && abs(leg2.leg2.eta())<2.5','MMEMThirdMuID')
MMEManalysisConfigurator.addSelector('MMEMzzEleId','PATMuMuEleMuQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','MMEMEleCiCLoose') 
MMEManalysisConfigurator.addSelector('MMEMzzEleIso','PATMuMuEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','MMEMEleIso')
MMEManalysisConfigurator.addSelector('MMEMzzMuIso2','PATMuMuEleMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.25','MMEMMuIso')
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
#EEMTanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEMT')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTdiElectrons','PATElePairProducer', 'llttElectrons','llttElectrons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')

EEMTanalysisConfigurator.addSelector('EEMTosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EEMTDiEleCreation',1)
EEMTanalysisConfigurator.addSelector('EEMTosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','EEMTDiEleIso',1)

EEMTanalysisConfigurator.addDiCandidateModule('EEMTmuTau','PATMuTauPairProducer', 'cleanPatMuons','llttTaus','systematicsMET','selectedPatJets',1,9999,text = 'EEMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTzzCands','PATEleEleMuTauQuadProducer','EEMTosDiElectrons','EEMTmuTau','systematicsMET','selectedPatJets',1,9999,text='EEMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEMTanalysisConfigurator.addCrossCleanerModule('EEMTzzCleanedCands','PATEleEleMuTauQuadCrossCleaner',1,9999,text='EEMTAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMTanalysisConfigurator.addSelector('EEMTzzMuID2','PATEleEleMuTauQuadSelector','leg2.leg1.userInt("tightID")>0 && abs (leg2.leg1.eta())<2.5','EEMTSecondZMuID')
EEMTanalysisConfigurator.addSelector('EEMTzzTauID','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','EEMTTauDecayModeFinding')
EEMTanalysisConfigurator.addSelector('EEMTzzTauDiscr','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonTight")','EEMTTauLeptonDiscrimantor')
EEMTanalysisConfigurator.addSelector('EEMTzzMuIso2','PATEleEleMuTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','EEMTSecondZMuIso')
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
#EEETanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEET')
EEETanalysisConfigurator.addDiCandidateModule('EEETdiElectrons','PATElePairProducer', 'llttElectrons','llttElectrons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
EEETanalysisConfigurator.addSelector('EEETosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EEETDiEleCreation',1)
EEETanalysisConfigurator.addSelector('EEETosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','EEETDiEleIso',1)
EEETanalysisConfigurator.addDiCandidateModule('EEETeleTau','PATEleTauPairProducer', 'llttElectrons','llttTaus','systematicsMET','selectedPatJets',1,9999,text = 'EEETAtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETanalysisConfigurator.addDiCandidateModule('EEETzzCands','PATEleEleEleTauQuadProducer','EEETosDiElectrons','EEETeleTau','systematicsMET','selectedPatJets',1,9999,text='EEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEETanalysisConfigurator.addCrossCleanerModule('EEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='EEETAtLeastOneZZCleanedCandidate',dR = 0.1)
EEETanalysisConfigurator.addSelector('EEETzzCleanedEleID','PATEleEleEleTauQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','EEETEleID')
EEETanalysisConfigurator.addSelector('EEETzzCleanedEleIso','PATEleEleEleTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.10','EEETEleIso')
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
#EETTanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EETT')
EETTanalysisConfigurator.addDiCandidateModule('EETTdiElectrons','PATElePairProducer', 'llttElectrons','llttElectrons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
EETTanalysisConfigurator.addSelector('EETTosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EETTDiEleCreation',1)
EETTanalysisConfigurator.addSelector('EETTosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','EETTDiEleIso',1)
EETTanalysisConfigurator.addDiCandidateModule('EETTtauTau','PATDiTauPairProducer', 'llttTaus','llttTaus','systematicsMET','selectedPatJets',1,9999,text = 'EETTAtLeastOnediTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EETTanalysisConfigurator.addDiCandidateModule('EETTzzCands','PATEleEleTauTauQuadProducer','EETTosDiElectrons','EETTtauTau','systematicsMET','selectedPatJets',1,9999,text='EETTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
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
#EEEManalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEEM')
EEEManalysisConfigurator.addDiCandidateModule('EEEMdiElectrons','PATElePairProducer', 'llttElectrons','llttElectrons','systematicsMET','selectedPatJets',1,genParticles='genDaughters')
EEEManalysisConfigurator.addSelector('EEEMosDiElectrons','PATElePairSelector','charge==0 && mass>40 && leg1.userFloat("mvaNonTrigV0Pass")>0 && leg2.userFloat("mvaNonTrigV0Pass")>0 && abs(leg1.eta())<2.4 && abs(leg2.eta()) < 2.4','EEEMDiEleCreation',1)
EEEManalysisConfigurator.addSelector('EEEMosDiMuonsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','EEEMDiEleIso',1)

EEEManalysisConfigurator.addDiCandidateModule('EEEMeleMu','PATEleMuPairProducer', 'llttElectrons','cleanPatMuons','systematicsMET','selectedPatJets',1,9999,text = 'EEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEEManalysisConfigurator.addDiCandidateModule('EEEMzzCands','PATEleEleEleMuQuadProducer','EEEMosDiElectrons','EEEMeleMu','systematicsMET','selectedPatJets',1,9999,text='EEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.005,recoMode ="",genParticles='genDaughters')
EEEManalysisConfigurator.addCrossCleanerModule('EEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='EEEMAtLeastOneZZCleanedCandidate',dR = 0.1)


EEEManalysisConfigurator.addSelector('EEEMzzCleanedThirdMuID','PATEleEleEleMuQuadSelector','leg2.leg2.userInt("tightID")>0.5 && abs(leg2.leg2.eta())<2.5','EEEMThirdMuID')
EEEManalysisConfigurator.addSelector('EEEMzzEleId','PATEleEleEleMuQuadSelector','leg2.leg1.userFloat("mvaNonTrigV0Pass")>0','EEEMEleCiCLoose') 
EEEManalysisConfigurator.addSelector('EEEMzzEleIso','PATEleEleEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25','EEEMEleIso')
EEEManalysisConfigurator.addSelector('EEEMzzMuIso2','PATEleEleEleMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.25','EEEMMuIso')
EEEManalysisConfigurator.addSorter('EEEMzzCleanedCandsSortedByZMass','PATEleEleEleMuQuadSorterByZMass')
EEEManalysisConfigurator.addSelector('EEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.leg1.userFloat("dz")-leg1.leg2.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg1.userFloat("dz"))<0.1&&abs(leg1.leg1.userFloat("dz")-leg2.leg2.userFloat("dz"))<0.1','EEEMdZ')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsAboveThreshold','PATEleEleEleMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 && leg2().leg2().pt()>10 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.4','EEEMAtLeastOneZZCandOverThresholds')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsEMuQ','PATEleEleEleMuQuadSelector','leg2.charge()==0','EEEMEleMuCharge')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsMMMass','PATEleEleEleMuQuadSelector','leg1.mass()>60&&leg1.mass()<120','EEEMMMMass')
EEEManalysisConfigurator.addSorter('EEEMFinalSel','PATEleEleEleMuQuadSorterByZMass')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsETMass','PATEleEleEleMuQuadSelector','leg2.mass()<90','EEEMEMMass')
EEEMselectionSequence =EEEManalysisConfigurator.returnSequence()

######################_______________________________EndOfConfigurators__________________________################################
