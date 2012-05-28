import FWCore.ParameterSet.Config as cms

#TriggerPaths=["HLT_DoubleMu3","HLT_DoubleMu7","HLT_Mu13_Mu8","HLT_Mu17_Mu8","HLT_Ele10_LW_LR1","HLT_Ele15_SW_LR1","HLT_Ele15_SW_CaloEleID_L1R","HLT_Ele17_SW_TightEleID_L1R","HLT_Ele17_SW_TighterEleIdIsol_L1R","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]

TriggerPaths=["HLT_Mu13_Mu8","HLT_Mu17_Mu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]

#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

MMMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

#MMMManalysisConfigurator.addSelectorPdgID("test","PdgIdAndStatusCandViewSelector","genDaughters","genReq2",[11,13],1,9999)
#MMMManalysisConfigurator.addGeneric("trilep","CandViewShallowCloneCombiner","test@- test@+ test@+","","")
#MMMManalysisConfigurator.addGeneric("zz","CandViewShallowCloneCombiner","trilep@+ test@-","","testGeneric")
#1. Skim
##todo
#2. Trigger
MMMManalysisConfigurator.addHLTTest("MMMMHLT",TriggerPaths,"HLT_req")
MMMManalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMMM')
#Leptons cross-cleaning
#todo
#Good leptons selected
#todo...

MMMManalysisConfigurator.addDiCandidateModule('MMMMdiMuons','PATMuPairProducer', 'smearedMuonsMMMM','smearedMuonsMMMM','smearedMETMMMM','smearedJetsMMMM',1,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMMManalysisConfigurator.addSelector('MMMMosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4','one Z1',1)
MMMManalysisConfigurator.addSelector('MMMMosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','one Z1 with iso',1)

MMMManalysisConfigurator.addDiCandidateModule('MMMMdiElectrons','PATElePairProducer', 'smearedElectronsMMMM','smearedElectronsMMMM','smearedMETMMMM','smearedJetsMMMM',0,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMMManalysisConfigurator.addSelector('MMMMosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0&&leg2.userFloat("mvaNonTrigV0Pass")>0&&leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg1.pt()>7&&leg2.pt()>7&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5','',0)
MMMManalysisConfigurator.addSelector('MMMMosDiElectronsSIP','PATElePairSelector','abs(leg1.userFloat("ip3DS"))<4&&abs(leg2.userFloat("ip3DS"))<4','',0)
MMMManalysisConfigurator.addSelector('MMMMosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','',0)

MMMManalysisConfigurator.addBestSelector("MMMMbestTest","PATMuMuMuMuBestSelector","MMMMosDiMuonsIso","MMMMosDiElectronsIso","Best Zmm")

#3b. Apply 40<mZ1<120) 
MMMManalysisConfigurator.addSelector('MMMMosDiMuonsMassReq','PATMuPairSelector','mass>40&&mass<120','40 lt mZ1 lt 120 mmmm',1)
#4a. At least 4 good leptons (Muons: pf, pt>5, |eta|<2.4; electrons: gsf, pt>7, |eta|<2.5, missing hits<=1, BDTeID ("non triggered")
#4b. At least one another pair (SF/OS) 
MMMManalysisConfigurator.addDiCandidateModule('MMMMzzCands','PATMuMuMuMuQuadProducer','MMMMosDiMuonsIso','MMMMosDiMuonsIso','smearedMETMMMM','smearedJetsMMMM',1,9999,text='MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
MMMManalysisConfigurator.addCrossCleanerModule('MMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='cross cleaned',dR = 0.01)
#4c. Pair #2 built (SF/OS, highest pT leptons) 
MMMManalysisConfigurator.addSelector('MMMMzzCleanedMuIso','PATMuMuMuMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25 && (leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.25 ','two good Zs should lose none',1)
MMMManalysisConfigurator.addSorter('MMMMzzCleanedCandsSortedByZMass','PATMuMuMuMuQuadSorterByZMass')
#4d. Apply mll cuts (4<mZ2<120) 
MMMManalysisConfigurator.addSelector('MMMMzzCleanedZ2Mass','PATMuMuMuMuQuadSelector','leg2.mass()>4&&leg2.mass()<120','z2 mass 4 to 120')
#5. Ensure there are two offline leptons with PT>20,10
MMMManalysisConfigurator.addSelector('MMMMzzPt','PATMuMuMuMuQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req',1) 
#6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
#MMMManalysisConfigurator.addSelector('MMMMzzQCDsupp','PATMuMuMuMuQuadSelector','(leg1.leg1.p4()+leg1.leg2.p4()).M()>4','pt req',1) 
MMMManalysisConfigurator.addInvMassModule('MMMMzzInvMass','PATMuMuMuMuQuadInvMassSelector',1,9999,text='m4l gt 4 for all',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
MMMManalysisConfigurator.addSelector('MMMMZ4lSpace','PATMuMuMuMuQuadSelector','mass>70','Z to 4l phasespace',1)
#8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
MMMManalysisConfigurator.addSelector('MMMMHSpace','PATMuMuMuMuQuadSelector','mass>100','Higgs phasespace',1)
MMMManalysisConfigurator.addSorter('MMMMFinalSel','PATMuMuMuMuQuadSorterByZMass')
MMMMselectionSequence =MMMManalysisConfigurator.returnSequence()

###--------- EEEE ----------###

EEEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
#EEEEanalysisConfigurator.addSelectorPdgID("test","PdgIdAndStatusCandViewSelector","genDaughters","genReq2",[11,13],1,9999)
#EEEEanalysisConfigurator.addGeneric("trilep","CandViewShallowCloneCombiner","test@- test@+ test@+","","")
#EEEEanalysisConfigurator.addGeneric("zz","CandViewShallowCloneCombiner","trilep@+ test@-","","testGeneric")
#1. Skim
##todo
#2. Trigger
EEEEanalysisConfigurator.addHLTTest("EEEEHLT",TriggerPaths,"EEEE HLT_req")
EEEEanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','EEEE')
#Leptons cross-cleaning
##todo
##Good leptons selected
##todo...
#
EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiElectrons','PATElePairProducer', 'smearedElectronsEEEE','smearedElectronsEEEE','smearedMETEEEE','smearedJetsEEEE',1,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
EEEEanalysisConfigurator.addSelector('EEEEosDiElectrons','PATElePairSelector','charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0&&leg2.userFloat("mvaNonTrigV0Pass")>0&&leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg1.pt()>7&&leg2.pt()>7&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5','',1)
EEEEanalysisConfigurator.addSelector('EEEEosDiElectronsSIP','PATElePairSelector','abs(leg1.userFloat("ip3DS"))<4&&abs(leg2.userFloat("ip3DS"))<4','',1)
EEEEanalysisConfigurator.addSelector('EEEEosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','one Z1 with iso eeee',1)
#EEEEanalysisConfigurator.addSelector('EEEEosDiElectronsIso','PATElePairSelector','leg1.userFloat("isomvaPass")>0.0&&leg2.userFloat("isomvaPass")>0.0','one Z1 with iso eeee',1)

EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiMuons','PATMuPairProducer', 'smearedMuonsEEEE','smearedMuonsEEEE','smearedMETEEEE','smearedJetsEEEE',0,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
EEEEanalysisConfigurator.addSelector('EEEEosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4','',0)
EEEEanalysisConfigurator.addSelector('EEEEosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','',0)

EEEEanalysisConfigurator.addBestSelector("EEEEbestTest","PATEleEleEleEleBestSelector","EEEEosDiElectronsIso","EEEEosDiMuonsIso","Good Zee")

##3b. Apply 40<mZ1<120) 
EEEEanalysisConfigurator.addSelector('EEEEosDiEleMassReq','PATElePairSelector','mass>40&&mass<120','40 lt mZ1 lt 120 eeee',1)
##4a. At least 4 good leptons (Muons: pf, pt>5, |eta|<2.4; electrons: gsf, pt>7, |eta|<2.5, missing hits<=1, BDTeID ("non triggered")
##4b. At least one another pair (SF/OS) 
EEEEanalysisConfigurator.addDiCandidateModule('EEEEzzCands','PATEleEleEleEleQuadProducer','EEEEosDiElectronsIso','EEEEosDiElectronsIso','smearedMETEEEE','smearedJetsEEEE',1,9999,text='EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
EEEEanalysisConfigurator.addCrossCleanerModule('EEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='cross cleaned eeee',dR = 0.01)
#EEEEanalysisConfigurator.addSelector('EEEEzzCleanedEleID','PATEleEleEleEleQuadSelector','leg2.leg1.pfCandidateRef().isNonnull()&&leg2.leg2.pfCandidateRef().isNonnull()&&(leg2.leg1.isGlobalMuon()||leg2.leg1.isTrackerMuon())&&(leg2.leg2.isGlobalMuon()||leg2.leg2.isTrackerMuon())','should lose none')
##4c. Pair #2 built (SF/OS, highest pT leptons) 
#EEEEanalysisConfigurator.addSelector('EEEEzzCleanedEleIso','PATEleEleEleEleQuadSelector','(leg2.leg1.chargedHadronIso()+max(0.0,leg2.leg1.neutralHadronIso()+leg2.leg1.photonIso()-leg2.leg1.userFloat("zzRho")*leg2.leg1.userFloat("EAGammaNeuHadron04")))/leg2.leg1.pt<0.25 && (leg2.leg2.chargedHadronIso()+max(0.0,leg2.leg2.neutralHadronIso()+leg2.leg2.photonIso()-leg2.leg2.userFloat("zzRho")*leg2.leg2.userFloat("EAGammaNeuHadron04")))/leg2.leg2.pt<0.25 ','two good Zs eeee',1)
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedEleIso','PATEleEleEleEleQuadSelector','leg2.leg1.userFloat("isomvaPass")>0.0&&leg2.leg2.userFloat("isomvaPass")>0.0','two good Zs eeee',1)
EEEEanalysisConfigurator.addSorter('EEEEzzCleanedCandsSortedByZMass','PATEleEleEleEleQuadSorterByZMass')
##4d. Apply mll cuts (4<mZ2<120) 
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedZ2Mass','PATEleEleEleEleQuadSelector','leg2.mass()>4&&leg2.mass()<120','EEEESecondZCharge')
##5. Ensure there are two offline leptons with PT>20,10
EEEEanalysisConfigurator.addSelector('EEEEzzPt','PATEleEleEleEleQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req eeee',1) 
##6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
EEEEanalysisConfigurator.addInvMassModule('EEEEzzInvMass','PATEleEleEleEleQuadInvMassSelector',1,9999,text='m2l gt 4 for all eeee',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
EEEEanalysisConfigurator.addSelector('EEEEZ4lSpace','PATEleEleEleEleQuadSelector','mass>70','Z to 4l phasespace eeee',1)
##8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
EEEEanalysisConfigurator.addSelector('EEEEHSpace','PATEleEleEleEleQuadSelector','mass>100','Higgs phasespace eeee',1)
EEEEanalysisConfigurator.addSorter('EEEEFinalSel','PATEleEleEleEleQuadSorterByZMass')
EEEEselectionSequence =EEEEanalysisConfigurator.returnSequence()


###--------- MMEE ----------###

MMEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
#MMEEanalysisConfigurator.addSelectorPdgID("test","PdgIdAndStatusCandViewSelector","genDaughters","genReq2",[11,13],1,9999)
#MMEEanalysisConfigurator.addGeneric("trilep","CandViewShallowCloneCombiner","test@- test@+ test@+","","")
#MMEEanalysisConfigurator.addGeneric("zz","CandViewShallowCloneCombiner","trilep@+ test@-","","testGeneric")
#1. Skim
##todo
#2. Trigger
MMEEanalysisConfigurator.addHLTTest("MMEEHLT",TriggerPaths,"MMEE HLT_req")
MMEEanalysisConfigurator.addSmearing('cleanPatTaus','cleanPatMuons','cleanPatElectrons','selectedPatJets','MMEE')
#Leptons cross-cleaning
##todo
##Good leptons selected
##todo...
#
MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiMuons','PATMuPairProducer', 'smearedMuonsMMEE','smearedMuonsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')
#3a. Pair #1 built, (SF/OS, closest to Z0) 
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsnoPF','PATMuPairSelector','mass()>4&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4','one Z1 MMEE no pf',1)
MMEEanalysisConfigurator.addSelector('MMEEosDiMuons','PATMuPairSelector','leg1.pfCandidateRef().isNonnull()&&leg2.pfCandidateRef().isNonnull()&&charge==0&&(leg1.isGlobalMuon()||leg1.isTrackerMuon())&&(leg2.isGlobalMuon()||leg2.isTrackerMuon()) && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4 && leg1.pt()>5 && leg2.pt()>5 && abs(leg1.userFloat("ip3DS"))<4 && abs(leg2.userFloat("ip3DS"))<4','one Z1 MMEE',1)
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsIso','PATMuPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','one Z1 with iso MMEE',1)

#temp minFilter=0, then require (M_mm is better than M_ee)
MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiElectrons','PATElePairProducer', 'smearedElectronsMMEE','smearedElectronsMMEE','smearedMETMMEE','smearedJetsMMEE',0,genParticles='genDaughters')
MMEEanalysisConfigurator.addSelector('MMEEosDiElectrons','PATElePairSelector','mass()>4&&charge==0&&leg1.userFloat("mvaNonTrigV0Pass")>0&&leg2.userFloat("mvaNonTrigV0Pass")>0&&leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg1.pt()>7&&leg2.pt()>7&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&abs(leg1.userFloat("ip3DS"))<4&&abs(leg2.userFloat("ip3DS"))<4','',0)
MMEEanalysisConfigurator.addSelector('MMEEosDiElectronsIso','PATElePairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.neutralHadronIso()+leg1.photonIso()-leg1.userFloat("zzRho")*leg1.userFloat("EAGammaNeuHadron04")))/leg1.pt<0.25 && (leg2.chargedHadronIso()+max(0.0,leg2.neutralHadronIso()+leg2.photonIso()-leg2.userFloat("zzRho")*leg2.userFloat("EAGammaNeuHadron04")))/leg2.pt<0.25 ','a Z with iso ee should cut none',0)
#MMEEanalysisConfigurator.addSelector('MMEEosDiElectronsIso','PATElePairSelector','leg1.userFloat("isomvaPass")>0.0&&leg2.userFloat("isomvaPass")','a Z with iso ee mmee',1)

MMEEanalysisConfigurator.addDiCandidateModule('MMEEzzCands','PATMuMuEleEleQuadProducer','MMEEosDiMuonsIso','MMEEosDiElectronsIso','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.01,recoMode ="",genParticles='genDaughters')
#3b. Apply 40<mZ1<120) 
MMEEanalysisConfigurator.addSelector('MMEEosDiMuonsMassReq','PATMuMuEleEleQuadSelector','(leg1.mass>40&&leg1.mass<120)||(leg2.mass>40&&leg2.mass<120)','40 lt mZ1 lt 120 mmee',1)
#4a. At least 4 good leptons (Muons: pf, pt>5, |eta|<2.4; electrons: gsf, pt>7, |eta|<2.5, missing hits<=1, BDTeID ("non triggered")
##4b. At least one another pair (SF/OS) 
MMEEanalysisConfigurator.addCrossCleanerModule('MMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='cross cleaned mmee',dR = 0.01)
#MMEEanalysisConfigurator.addSelector('MMEEzzCleanedEleID','PATMuMuEleEleQuadSelector','leg2.leg1.pfCandidateRef().isNonnull()&&leg2.leg2.pfCandidateRef().isNonnull()&&(leg2.leg1.isGlobalMuon()||leg2.leg1.isTrackerMuon())&&(leg2.leg2.isGlobalMuon()||leg2.leg2.isTrackerMuon())','should lose none')
##4c. Pair #2 built (SF/OS, highest pT leptons) 
MMEEanalysisConfigurator.addSorter('MMEEzzCleanedCandsSortedByZMass','PATMuMuEleEleQuadSorterByZMass')
##4d. Apply mll cuts (4<mZ2<120) 
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedZ2Mass','PATMuMuEleEleQuadSelector','(leg1.mass()>40&&leg1.mass()<120&&leg2.mass()>4&&leg2.mass()<120)||(leg1.mass()>4&&leg1.mass()<120&&leg2.mass()>40&&leg2.mass()<120)','MMEESecondZCharge')
##5. Ensure there are two offline leptons with PT>20,10
MMEEanalysisConfigurator.addSelector('MMEEzzPt','PATMuMuEleEleQuadSelector','(leg1.leg1.pt()>20&&(leg1.leg2.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg1.leg2.pt()>20&&(leg1.leg1.pt()>10||leg2.leg1.pt()>10||leg2.leg2.pt()>10))||(leg2.leg1.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg2.pt()>10))||(leg2.leg2.pt()>20&&(leg1.leg1.pt()>10||leg1.leg2.pt()>10||leg2.leg1.pt()>10))','pt req mmee',1) 
##6. QCD suppression (mll>4 GeV cut on all 6 pairs irrespectively of flavour and sign)
MMEEanalysisConfigurator.addInvMassModule('MMEEzzInvMass','PATMuMuEleEleQuadInvMassSelector',1,9999,text='m2l gt 4 for all mmee',Mll = 4)
#7. Z->4l phase space (m4l > 70 GeV)
MMEEanalysisConfigurator.addSelector('MMEEZ4lSpace','PATMuMuEleEleQuadSelector','mass>70','Z to 4l phasespace mmee',1)
##8. H->ZZ->4l Phase Space (m(4l) > 100 GeV)
MMEEanalysisConfigurator.addSelector('MMEEHSpace','PATMuMuEleEleQuadSelector','mass>100','Higgs phasespace mmee',1)
MMEEanalysisConfigurator.addSorter('MMEEFinalSel','PATMuMuEleEleQuadSorterByZMass')
MMEEselectionSequence =MMEEanalysisConfigurator.returnSequence()
######################_______________________________EndOfConfigurators__________________________################################
