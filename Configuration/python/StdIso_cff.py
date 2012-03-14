import FWCore.ParameterSet.Config as cms

#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

######################__________________________________MMMT_____________________________________##############################

MMMTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMT',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
#nSVfitTrackService = cms.Service("NSVfitTrackService")
#Add smearing
MMMTanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets')
#Create di muon OS pairs 
MMMTanalysisConfigurator.addDiCandidateModule('MMMTdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
#Require they are OS and at least Global muons
MMMTanalysisConfigurator.addSelector('MMMTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>40 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4','MMMTDiMuonCreation',1)
#Make DiTaus
MMMTanalysisConfigurator.addDiCandidateModule('MMMTmuTau','PATMuTauPairProducer', 'smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'MMMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
#Combine and create zz candidates
MMMTanalysisConfigurator.addDiCandidateModule('MMMTzzCands','PATMuMuMuTauQuadProducer','MMMTosDiMuons','MMMTmuTau','smearedMET','smearedJets',1,9999,text='MMMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMTanalysisConfigurator.addCrossCleanerModule('MMMTzzCleanedCands','PATMuMuMuTauQuadCrossCleaner',1,9999,text='MMMTAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMTanalysisConfigurator.addSelector('MMMTzzMuID','PATMuMuMuTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMMTLeadingZMuID')
MMMTanalysisConfigurator.addSelector('MMMTzzMuIso','PATMuMuMuTauQuadSelector','((leg1.leg1.userIso(1)-leg1.leg1.userFloat("rho")*(? abs(leg1.leg1.eta())<1.479 ? 0.074 : 0.045)+leg1.leg1.userIso(2)-leg1.leg1.userFloat("rho")*(? abs(leg1.leg1.eta())<1.479 ? 0.022 : 0.030) + leg1.leg1.userIso(3))/leg1.leg1.pt()<0.30)&&((leg1.leg2.userIso(1)-leg1.leg2.userFloat("rho")*(? abs(leg1.leg2.eta())<1.479 ? 0.074 : 0.045)+leg1.leg2.userIso(2)-leg1.leg2.userFloat("rho")*(? abs(leg1.leg2.eta())<1.479 ? 0.022 : 0.030) + leg1.leg2.userIso(3))/leg1.leg2.pt()<0.30)','MMMTLeadingZMuIso')
MMMTanalysisConfigurator.addSelector('MMMTzzMuID2','PATMuMuMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','MMMTSecondZMuID')
MMMTanalysisConfigurator.addSelector('MMMTzzTauID','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','MMMTTauDecayModeFinding')
MMMTanalysisConfigurator.addSelector('MMMTzzMuIso2','PATMuMuMuTauQuadSelector','((leg2.leg1.userIso(1)-leg2.leg1.userFloat("rho")*(? abs(leg2.leg1.eta())<1.479 ? 0.074 : 0.045)+leg2.leg1.userIso(2)-leg2.leg1.userFloat("rho")*(? abs(leg2.leg1.eta())<1.479 ? 0.022 : 0.030) + leg2.leg1.userIso(3))/leg2.leg1.pt()<0.20)','MMMTSecondZMuIso')
MMMTanalysisConfigurator.addSelector('MMMTzzTauIso','PATMuMuMuTauQuadSelector','(leg2.leg2.isolationPFChargedHadrCandsPtSum())<4.0','MMMTTauLooseIsolation')
#Sort your ZZ candidates by higher Z1 Pt + Z2 Pt 
MMMTanalysisConfigurator.addSorter('MMMTzzCleanedCandsSortedByZMass','PATMuMuMuTauQuadSorterByZMass')
MMMTanalysisConfigurator.addSelector('MMMTzzdZ','PATMuMuMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMTdZ')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsAboveThreshold','PATMuMuMuTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.4 && abs(leg2.leg2.eta())<2.3','MMMTAtLeastOneZZCandOverThresholds')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsMuRej','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("againstMuonLoose")','MMMTTauMuRejection')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsEleRej','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")','MMMTTauEleRejection')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsHt','PATMuMuMuTauQuadSelector','leg2.leg2.pt()+leg2.leg1.pt()>30','MMMTHt')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsMuTauQ','PATMuMuMuTauQuadSelector','leg2.charge()==0','MMMTMuTauCharge')
MMMTanalysisConfigurator.addSelector('MMMTzzCleanedCandsMTMass','PATMuMuMuTauQuadSelector','leg2.mass()>30&&leg2.mass()<80','MMMTMTMass')
#MMMTanalysisConfigurator.addMuMuMuTauNSVFit('muMuMuTauNSVFit')
#create the sequence
MMMTselectionSequence =MMMTanalysisConfigurator.returnSequence()

# apply std.iso. with effective area treatment -- userIso1-aeff*rho+userIso2-aeff*rho+userIso3-aeff*rho

######################__________________________________MMTT_____________________________________##############################

MMTTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMTT',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMTTanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','MMTT')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiMuons','PATMuPairProducer', 'smearedMuonsMMTT','smearedMuonsMMTT','smearedMETMMTT','smearedJetsMMTT',1,genParticles='genDaughters')
MMTTanalysisConfigurator.addSelector('MMTTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>40 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4','MMTT DiMuonCreation',1)
MMTTanalysisConfigurator.addDiCandidateModule('MMTTdiTaus','PATDiTauPairProducer','smearedTausMMTT','smearedTausMMTT','smearedMETMMTT','smearedJetsMMTT',1,9999,text='MMTTAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTanalysisConfigurator.addDiCandidateModule('MMTTzzCands','PATMuMuTauTauQuadProducer','MMTTosDiMuons','MMTTdiTaus','smearedMETMMTT','smearedJetsMMTT',1,9999,text='MMTTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTanalysisConfigurator.addCrossCleanerModule('MMTTzzCleanedCands','PATMuMuTauTauQuadCrossCleaner',1,9999,text='MMTTAtLeastOneZZCleanedCandidate',dR = 0.1) 
MMTTanalysisConfigurator.addSelector('MMTTzzMuID','PATMuMuTauTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMTTLeadingZMuID')
MMTTanalysisConfigurator.addSelector('MMTTzzMuIso','PATMuMuTauTauQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','MMTTLeadingZMuIso')
MMTTanalysisConfigurator.addSelector('MMTTzzTauID','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','MMTTDecayModeFinding')
MMTTanalysisConfigurator.addSelector('MMTTzzTauIso','PATMuMuTauTauQuadSelector','(leg2.leg1.isolationPFChargedHadrCandsPtSum())<4.0&&(leg2.leg2.isolationPFChargedHadrCandsPtSum())<4.0','MMTTTauIsolation')
MMTTanalysisConfigurator.addSorter('MMTTzzCleanedCandsSortedByZMass','PATMuMuTauTauQuadSorterByZMass')
MMTTanalysisConfigurator.addSelector('MMTTzzdZ','PATMuMuTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMTTdZ')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsAboveThreshold','PATMuMuTauTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>20 &&leg2().leg2().pt()>20  && abs(leg2.leg1.eta())<2.3  && abs(leg2.leg2.eta())<2.3','MMTTAtLeastOneZZCandOverThresholds')
MMTTanalysisConfigurator.addSelector('MMTTzzTauMedIso','PATMuMuTauTauQuadSelector','(leg2.leg1.isolationPFChargedHadrCandsPtSum())<3.0&&(leg2.leg2.isolationPFChargedHadrCandsPtSum())<3.0','MMTTTauMedIsolation')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsMuRej','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("againstMuonLoose")&&leg2.leg2.tauID("againstMuonLoose")','MMTTTauMuRejection')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsEleRej','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstElectronLoose")','MMTTTauEleRejection')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsHt','PATMuMuTauTauQuadSelector','leg2.leg2.pt()+leg2.leg1.pt()>40','MMTTHt')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsTauTauQ','PATMuMuTauTauQuadSelector','leg2.charge()==0','TauTauChargeMMTT')
MMTTanalysisConfigurator.addSelector('MMTTzzCleanedCandsTTMass','PATMuMuTauTauQuadSelector','leg2.mass()>30&&leg2.mass()<80','MMTTTTMass')

MMTTselectionSequence =MMTTanalysisConfigurator.returnSequence()


######################__________________________________MMET_____________________________________##############################

MMETanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMET',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMETanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','MMET')
MMETanalysisConfigurator.addDiCandidateModule('MMETdiMuons','PATMuPairProducer', 'smearedMuonsMMET','smearedMuonsMMET','smearedMETMMET','smearedJetsMMET',1,genParticles='genDaughters')
MMETanalysisConfigurator.addSelector('MMETosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>40 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4','MMET DiMuonCreation',1)
MMETanalysisConfigurator.addDiCandidateModule('MMETelecTau','PATEleTauPairProducer','smearedElectronsMMET','smearedTausMMET','smearedMETMMET','smearedJetsMMET',1,9999,text='MMETAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addDiCandidateModule('MMETzzCands','PATMuMuEleTauQuadProducer','MMETosDiMuons','MMETelecTau','smearedMETMMET','smearedJetsMMET',1,9999,text='MMETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETanalysisConfigurator.addCrossCleanerModule('MMETzzCleanedCands2','PATMuMuEleTauQuadCrossCleaner',1,9999,text='MMETAtLeastOneZZCleanedCandidate',dR = 0.1)
MMETanalysisConfigurator.addSelector('MMETzzCleanedMuID','PATMuMuEleTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMETLeadingZMuID')
MMETanalysisConfigurator.addSelector('MMETzzCleanedMuIso','PATMuMuEleTauQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','MMETLeadingZMuIso')
MMETanalysisConfigurator.addSelector('MMETzzCleanedEleID','PATMuMuEleTauQuadSelector','(leg2.leg1.electronID("cicLoose")==1||leg2.leg1.electronID("cicLoose")==3||leg2.leg1.electronID("cicLoose")==5||leg2.leg1.electronID("cicLoose")==7||leg2.leg1.electronID("cicLoose")==9||leg2.leg1.electronID("cicLoose")==11||leg2.leg1.electronID("cicLoose")==13||leg2.leg1.electronID("cicLoose")==15)','MMETEleCiCLoose')
MMETanalysisConfigurator.addSelector('MMETzzTauID','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','MMETDecayModeFinding')
MMETanalysisConfigurator.addSelector('MMETzzCleanedEleIso','PATMuMuEleTauQuadSelector','((leg2.leg1.pt()>20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.35)||(leg2.leg1.pt()<20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))<7))','MMETLooseEleIso')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsTauIso','PATMuMuEleTauQuadSelector','(leg2.leg2.isolationPFChargedHadrCandsPtSum())<4.0','MMETTauIsolation')
MMETanalysisConfigurator.addSorter('MMETzzCleanedCandsSortedByZMass','PATMuMuEleTauQuadSorterByZMass')
MMETanalysisConfigurator.addSelector('MMETzzdZ','PATMuMuEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMETdZ')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsAboveThreshold','PATMuMuEleTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>15 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.3','MMETAtLeastOneZZCandOverThresholds')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsMuRej','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("againstMuonLoose")','MMETTauMuRejection')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsEleRej','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")','MMETTauEleRejection')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsHt','PATMuMuEleTauQuadSelector','leg2.leg2.pt()+leg2.leg1.pt()>30','MMETHt')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsETauQ','PATMuMuEleTauQuadSelector','leg2.charge()==0','MMETEleTauCharge')
MMETanalysisConfigurator.addSelector('MMETzzCleanedCandsETMass','PATMuMuEleTauQuadSelector','leg2.mass()>30&&leg2.mass()<80','MMETETMass')

MMETselectionSequence =MMETanalysisConfigurator.returnSequence()


######################__________________________________MMEM_____________________________________##############################

MMEManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEManalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','MMEM')
MMEManalysisConfigurator.addDiCandidateModule('MMEMdiMuons','PATMuPairProducer', 'smearedMuonsMMEM','smearedMuonsMMEM','smearedMETMMEM','smearedJetsMMEM',1,genParticles='genDaughters')
MMEManalysisConfigurator.addSelector('MMEMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>40 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4','MMEM DiMuonCreation',1)
MMEManalysisConfigurator.addDiCandidateModule('MMEMelecMu','PATEleMuPairProducer','smearedElectronsMMEM','smearedMuonsMMEM','smearedMETMMEM','smearedJetsMMEM',1,9999,text='MMEMAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addDiCandidateModule('MMEMzzCands','PATMuMuEleMuQuadProducer','MMEMosDiMuons','MMEMelecMu','smearedMETMMEM','smearedJetsMMEM',1,9999,text='MMEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEManalysisConfigurator.addCrossCleanerModule('MMEMzzCleanedCands','PATMuMuEleMuQuadCrossCleaner',1,9999,text='MMEMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEManalysisConfigurator.addSelector('MMEMzzCleanedMuID','PATMuMuEleMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMEMLeadingZMuID')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedMuIso','PATMuMuEleMuQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','MMEMLeadingZMuIso')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedThirdMuID','PATMuMuEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','MMEMThirdMuID')
MMEManalysisConfigurator.addSelector('MMEMzzEleId','PATMuMuEleMuQuadSelector','(leg2.leg1.electronID("cicLoose")==1||leg2.leg1.electronID("cicLoose")==3||leg2.leg1.electronID("cicLoose")==5||leg2.leg1.electronID("cicLoose")==7||leg2.leg1.electronID("cicLoose")==9||leg2.leg1.electronID("cicLoose")==11||leg2.leg1.electronID("cicLoose")==13||leg2.leg1.electronID("cicLoose")==15)','MMEMEleCiCLoose') 
MMEManalysisConfigurator.addSelector('MMEMzzCleanedThirdMuIso','PATMuMuEleMuQuadSelector','((leg2.leg2.pt()>20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.35)||(leg2.leg2.pt()<20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))<7))','MMEMThirdMuIso')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedEleIso','PATMuMuEleMuQuadSelector','((leg2.leg1.pt()>20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.35)||(leg2.leg1.pt()<20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))<7))','MMEMLooseEleIso')
MMEManalysisConfigurator.addSorter('MMEMzzCleanedCandsSortedByZMass','PATMuMuEleMuQuadSorterByZMass')
MMEManalysisConfigurator.addSelector('MMEMzzdZ','PATMuMuEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEMdZ')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedCandsAboveThreshold','PATMuMuEleMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 && leg2().leg2().pt()>10 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.4','MMEMAtLeastOneZZCandOverThresholds')
MMEManalysisConfigurator.addSelector('MMEMzzCleanedCandsEMuQ','PATMuMuEleMuQuadSelector','leg2.charge()==0','MMEMEleMuCharge')

MMEMselectionSequence =MMEManalysisConfigurator.returnSequence()


######################__________________________________MMEE_____________________________________##############################

MMEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','MMEE')
MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiMuons','PATMuPairProducer', 'smearedMuonsMMEE','smearedMuonsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')
MMEEanalysisConfigurator.addSelector('MMEEosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>40 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4','MMEE DiMuonCreation',1)
MMEEanalysisConfigurator.addDiCandidateModule('MMEEeleEle','PATElePairProducer','smearedElectronsMMEE','smearedElectronsMMEE','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneEleEle',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEanalysisConfigurator.addDiCandidateModule('MMEEzzCands','PATMuMuEleEleQuadProducer','MMEEosDiMuons','MMEEeleEle','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEanalysisConfigurator.addCrossCleanerModule('MMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='MMEEAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedMuID','PATMuMuEleEleQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMEELeadingZMuID')
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedMuIso','PATMuMuEleEleQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','MMEELeadingZMuIso')
MMEEanalysisConfigurator.addSelector('MMEEzzEleId','PATMuMuEleEleQuadSelector','((leg2.leg1.electronID("cicLoose")==1||leg2.leg1.electronID("cicLoose")==3||leg2.leg1.electronID("cicLoose")==5||leg2.leg1.electronID("cicLoose")==7||leg2.leg1.electronID("cicLoose")==9||leg2.leg1.electronID("cicLoose")==11||leg2.leg1.electronID("cicLoose")==13||leg2.leg1.electronID("cicLoose")==15)&&(leg2.leg2.electronID("cicLoose")==1||leg2.leg2.electronID("cicLoose")==3||leg2.leg2.electronID("cicLoose")==5||leg2.leg2.electronID("cicLoose")==7||leg2.leg2.electronID("cicLoose")==9||leg2.leg2.electronID("cicLoose")==11||leg2.leg1.electronID("cicLoose")==13||leg2.leg2.electronID("cicLoose")==15))','MMEEEleCiCTight') 
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedEleIso','PATMuMuEleEleQuadSelector','((leg2.leg1.pt()>20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.35)||(leg2.leg1.pt()<20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))<7))&&((leg2.leg2.pt()>20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.35)||(leg2.leg2.pt()<20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))<7))','MMEELooseEleIso')
MMEEanalysisConfigurator.addSorter('MMEEzzCleanedCandsSortedByZMass','PATMuMuEleEleQuadSorterByZMass')
MMEEanalysisConfigurator.addSelector('MMEEzzdZ','PATMuMuEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEEdZ')
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedCandsAboveThreshold','PATMuMuEleEleQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>7 &&leg2().leg2().pt()>7 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.5','MMEEAtLeastOneZZCandOverThresholds')
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedCandsEleEleQ','PATMuMuEleEleQuadSelector','leg2.charge()==0','EleEleCharge')

MMEEselectionSequence =MMEEanalysisConfigurator.returnSequence()


######################__________________________________MMMM_____________________________________##############################

MMMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMManalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','MMMM')
MMMManalysisConfigurator.addDiCandidateModule('MMMMdiMuons','PATMuPairProducer', 'smearedMuonsMMMM','smearedMuonsMMMM','smearedMETMMMM','smearedJetsMMMM',1,genParticles='genDaughters')
MMMManalysisConfigurator.addSelector('MMMMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>40 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4','MMMM DiMuonCreation',1)
MMMManalysisConfigurator.addDiCandidateModule('MMMMzzCands','PATMuMuMuMuQuadProducer','MMMMosDiMuons','MMMMdiMuons','smearedMETMMMM','smearedJetsMMMM',1,9999,text='MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMManalysisConfigurator.addCrossCleanerModule('MMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='MMMMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMManalysisConfigurator.addSelector('MMMMzzCleanedMuID','PATMuMuMuMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMMMLeadingZMuID')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedMuIso','PATMuMuMuMuQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','MMMMLeadingZMuIso')
MMMManalysisConfigurator.addSelector('MMMMzzMuIDSecondPair','PATMuMuMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','MMMMsecondPairID')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedMuIsoSecondPair','PATMuMuMuMuQuadSelector','((leg2.leg1.pt()>20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.35)||(leg2.leg1.pt()<20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))<7))&&((leg2.leg2.pt()>20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.35)||(leg2.leg2.pt()<20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))<7))','MMMMsecondPairIso')
MMMManalysisConfigurator.addSorter('MMMMzzCleanedCandsSortedByZMass','PATMuMuMuMuQuadSorterByZMass')
MMMManalysisConfigurator.addSelector('MMMMzzdZ','PATMuMuMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMMdZ')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedCandsAboveThreshold','PATMuMuMuMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>5 &&leg2().leg2().pt()>5 && abs(leg2.leg1.eta())<2.4 && abs(leg2.leg2.eta())<2.4','MMMMAtLeastOneZZCandOverThresholds')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedCandsMuMuQ','PATMuMuMuMuQuadSelector','leg2.charge()==0','MMMMSecondZCharge')

MMMMselectionSequence =MMMManalysisConfigurator.returnSequence()


######################___________________electron+electron pair as leading Z_____________________##############################

#eeLeadingID1='leg1.electronID("cicLoose")==1||leg1.electronID("cicLoose")==3||leg1.electronID("cicLoose")==5||leg1.electronID("cicLoose")==7||leg1.electronID("cicLoose")==9||leg1.electronID("cicLoose")==11||leg1.electronID("cicLoose")==13||leg1.electronID("cicLoose")==15'
#eeLeadingID2='leg2.electronID("cicLoose")==1||leg2.electronID("cicLoose")==3||leg2.electronID("cicLoose")==5||leg2.electronID("cicLoose")==7||leg2.electronID("cicLoose")==9||leg2.electronID("cicLoose")==11||leg2.electronID("cicLoose")==13||leg2.electronID("cicLoose")==15'
#eeLeadingID=eeLeadingID1+'&&'+eeLeadingID2
#eeLeading=eeLeadingID+'&&charge==0 && mass>40'

######################__________________________________EEMT_____________________________________##############################

EEMTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEMT',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEMTanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEMT')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTdiElectrons','PATElePairProducer', 'smearedElectronsEEMT','smearedElectronsEEMT','smearedMETEEMT','smearedJetsEEMT',1,genParticles='genDaughters')
EEMTanalysisConfigurator.addSelector('EEMTosDiElectrons','PATElePairSelector','(leg1.electronID("cicLoose")==1||leg1.electronID("cicLoose")==3||leg1.electronID("cicLoose")==5||leg1.electronID("cicLoose")==7||leg1.electronID("cicLoose")==9||leg1.electronID("cicLoose")==11||leg1.electronID("cicLoose")==13||leg1.electronID("cicLoose")==15)&&(leg2.electronID("cicLoose")==1||leg2.electronID("cicLoose")==3||leg2.electronID("cicLoose")==5||leg2.electronID("cicLoose")==7||leg2.electronID("cicLoose")==9||leg2.electronID("cicLoose")==11||leg2.electronID("cicLoose")==13||leg2.electronID("cicLoose")==15)&&charge==0&&mass>40','EEMTDiEleCreation',1)
EEMTanalysisConfigurator.addDiCandidateModule('EEMTmuTau','PATMuTauPairProducer', 'smearedMuonsEEMT','smearedTausEEMT','smearedMETEEMT','smearedJetsEEMT',1,9999,text = 'EEMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEMTanalysisConfigurator.addDiCandidateModule('EEMTzzCands','PATEleEleMuTauQuadProducer','EEMTosDiElectrons','EEMTmuTau','smearedMETEEMT','smearedJetsEEMT',1,9999,text='EEMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMTanalysisConfigurator.addCrossCleanerModule('EEMTzzCleanedCands','PATEleEleMuTauQuadCrossCleaner',1,9999,text='EEMTAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedeleIso','PATEleEleMuTauQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','EEMTLeadingZEleIso')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedmuID','PATEleEleMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','EEMTMuID')
EEMTanalysisConfigurator.addSelector('EEMTzzTauID','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','EEMTDecayModeFinding')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedmuIso','PATEleEleMuTauQuadSelector','((leg2.leg1.pt()>20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.35)||(leg2.leg1.pt()<20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))<7))','EEMTLooseMuIso')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsTauIso','PATEleEleMuTauQuadSelector','(leg2.leg2.isolationPFChargedHadrCandsPtSum())<4.0','EEMTTauIsolation')
EEMTanalysisConfigurator.addSorter('EEMTzzCleanedCandsSortedByZMass','PATEleEleMuTauQuadSorterByZMass')
EEMTanalysisConfigurator.addSelector('EEMTzzdZ','PATEleEleMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMTdZ')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsAboveThreshold','PATEleEleMuTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.4 && abs(leg2.leg2.eta())<2.3','EEMTAtLeastOneZZCandOverThresholds')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsMuRej','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("againstMuonLoose")','EEMTTauMuRejection')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsEleRej','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")','EEMTTauEleRejection')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsHt','PATEleEleMuTauQuadSelector','leg2.leg2.pt()+leg2.leg1.pt()>30','EEMTHt')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsMuTauQ','PATEleEleMuTauQuadSelector','leg2.charge()==0','EEMTMuTauCharge')
EEMTanalysisConfigurator.addSelector('EEMTzzCleanedCandsMTMass','PATEleEleMuTauQuadSelector','leg2.mass()>30&&leg2.mass()<80','EEMTMTMass')

EEMTselectionSequence =EEMTanalysisConfigurator.returnSequence()


######################__________________________________EEET_____________________________________##############################

EEETanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEET',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEETanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEET')
EEETanalysisConfigurator.addDiCandidateModule('EEETdiElectrons','PATElePairProducer', 'smearedElectronsEEET','smearedElectronsEEET','smearedMETEEET','smearedJetsEEET',1,genParticles='genDaughters')
EEETanalysisConfigurator.addSelector('EEETosDiElectrons','PATElePairSelector','(leg1.electronID("cicLoose")==1||leg1.electronID("cicLoose")==3||leg1.electronID("cicLoose")==5||leg1.electronID("cicLoose")==7||leg1.electronID("cicLoose")==9||leg1.electronID("cicLoose")==11||leg1.electronID("cicLoose")==13||leg1.electronID("cicLoose")==15)&&(leg2.electronID("cicLoose")==1||leg2.electronID("cicLoose")==3||leg2.electronID("cicLoose")==5||leg2.electronID("cicLoose")==7||leg2.electronID("cicLoose")==9||leg2.electronID("cicLoose")==11||leg2.electronID("cicLoose")==13||leg2.electronID("cicLoose")==15)&&charge==0&&mass>40','EEETDiEleCreation',1)
EEETanalysisConfigurator.addDiCandidateModule('EEETeleTau','PATEleTauPairProducer', 'smearedElectronsEEET','smearedTausEEET','smearedMETEEET','smearedJetsEEET',1,9999,text = 'EEETAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETanalysisConfigurator.addDiCandidateModule('EEETzzCands','PATEleEleEleTauQuadProducer','EEETosDiElectrons','EEETeleTau','smearedMETEEET','smearedJetsEEET',1,9999,text='EEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEETanalysisConfigurator.addCrossCleanerModule('EEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='EEETAtLeastOneZZCleanedCandidate',dR = 0.1)
EEETanalysisConfigurator.addSelector('EEETzzCleanedeleIso','PATEleEleEleTauQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','EEETLeadingZEleIso')
EEETanalysisConfigurator.addSelector('EEETzzCleanedThirdeleID','PATEleEleEleTauQuadSelector','(leg2.leg1.electronID("cicLoose")==1||leg2.leg1.electronID("cicLoose")==3||leg2.leg1.electronID("cicLoose")==5||leg2.leg1.electronID("cicLoose")==7||leg2.leg1.electronID("cicLoose")==9||leg2.leg1.electronID("cicLoose")==11||leg2.leg1.electronID("cicLoose")==13||leg2.leg1.electronID("cicLoose")==15)','EEETLooseThirdEleCiCLoose')
EEETanalysisConfigurator.addSelector('EEETzzTauID','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','EEETDecayModeFinding')
EEETanalysisConfigurator.addSelector('EEETzzCleanedThirdeleIso','PATEleEleEleTauQuadSelector','((leg2.leg1.pt()>20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.35)||(leg2.leg1.pt()<20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))<7))','EEETLooseThirdEleIso')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsTauIso','PATEleEleEleTauQuadSelector','(leg2.leg2.isolationPFChargedHadrCandsPtSum())<4.0','EEETTauIsolation')
EEETanalysisConfigurator.addSorter('EEETzzCleanedCandsSortedByZMass','PATEleEleEleTauQuadSorterByZMass')
EEETanalysisConfigurator.addSelector('EEETzzdZ','PATEleEleEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEETdZ')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsAboveThreshold','PATEleEleEleTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.3','EEETAtLeastOneZZCandOverThresholds')
EEETanalysisConfigurator.addSorter('EEETzzTEMPntuples','PATEleEleEleTauQuadSorterByZMass')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsMuRej','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("againstMuonLoose")','EEETTauMuRejection')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsEleRej','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")','EEETTauEleRejection')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsHt','PATEleEleEleTauQuadSelector','leg2.leg2.pt()+leg2.leg1.pt()>30','EEETHt')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsETauQ','PATEleEleEleTauQuadSelector','leg2.charge()==0','EEETEleTauCharge')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsETMass','PATEleEleEleTauQuadSelector','leg2.mass()>30&&leg2.mass()<80','EEETETMass')

EEETselectionSequence =EEETanalysisConfigurator.returnSequence()


######################__________________________________EETT_____________________________________##############################

EETTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEETT',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EETTanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EETT')
EETTanalysisConfigurator.addDiCandidateModule('EETTdiElectrons','PATElePairProducer', 'smearedElectronsEETT','smearedElectronsEETT','smearedMETEETT','smearedJetsEETT',1,genParticles='genDaughters')
EETTanalysisConfigurator.addSelector('EETTosDiElectrons','PATElePairSelector','(leg1.electronID("cicLoose")==1||leg1.electronID("cicLoose")==3||leg1.electronID("cicLoose")==5||leg1.electronID("cicLoose")==7||leg1.electronID("cicLoose")==9||leg1.electronID("cicLoose")==11||leg1.electronID("cicLoose")==13||leg1.electronID("cicLoose")==15)&&(leg2.electronID("cicLoose")==1||leg2.electronID("cicLoose")==3||leg2.electronID("cicLoose")==5||leg2.electronID("cicLoose")==7||leg2.electronID("cicLoose")==9||leg2.electronID("cicLoose")==11||leg2.electronID("cicLoose")==13||leg2.electronID("cicLoose")==15)&&charge==0&&mass>40','EETTDiEleCreation',1)
EETTanalysisConfigurator.addDiCandidateModule('EETTtauTau','PATDiTauPairProducer', 'smearedTausEETT','smearedTausEETT','smearedMETEETT','smearedJetsEEET',1,9999,text = 'EETTAtLeastOnediTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EETTanalysisConfigurator.addDiCandidateModule('EETTzzCands','PATEleEleTauTauQuadProducer','EETTosDiElectrons','EETTtauTau','smearedMETEETT','smearedJetsEEET',1,9999,text='EETTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EETTanalysisConfigurator.addCrossCleanerModule('EETTzzCleanedCands','PATEleEleTauTauQuadCrossCleaner',1,9999,text='EETTAtLeastOneZZCleanedCandidate',dR = 0.1)
EETTanalysisConfigurator.addSelector('EETTzzCleanedeleIso','PATEleEleTauTauQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','EETTLeadingZEleIso')
EETTanalysisConfigurator.addSelector('EETTzzTauID','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','EETTDecayModeFinding')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsTauIso','PATEleEleTauTauQuadSelector','(leg2.leg1.isolationPFChargedHadrCandsPtSum())<4.0&&(leg2.leg2.isolationPFChargedHadrCandsPtSum())<4.0','EETTTauIsolation')
EETTanalysisConfigurator.addSorter('EETTzzCleanedCandsSortedByZMass','PATEleEleTauTauQuadSorterByZMass')
EETTanalysisConfigurator.addSelector('EETTzzdZ','PATEleEleTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EETTdZ')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsAboveThreshold','PATEleEleTauTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>20 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.3 && abs(leg2.leg2.eta())<2.3','EETTAtLeastOneZZCandOverThresholds')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsTauMedIso','PATEleEleTauTauQuadSelector','(leg2.leg1.isolationPFChargedHadrCandsPtSum())<3.0&&(leg2.leg2.isolationPFChargedHadrCandsPtSum())<3.0','EETTTauMedIsolation')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsMuRej','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("againstMuonLoose")&&leg2.leg2.tauID("againstMuonLoose")','EETTTauMuRejection')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsEleRej','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstElectronLoose")','EETTTauEleRejection')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsHt','PATEleEleTauTauQuadSelector','leg2.leg2.pt()+leg2.leg1.pt()>40','EETTHt')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsTauTauQ','PATEleEleTauTauQuadSelector','leg2.charge()==0','TauTauChargeEETT')
EETTanalysisConfigurator.addSelector('EETTzzCleanedCandsTTMass','PATEleEleTauTauQuadSelector','leg2.mass()>30&&leg2.mass()<80','EETTTTMass')

EETTselectionSequence =EETTanalysisConfigurator.returnSequence()


######################__________________________________EEEM_____________________________________##############################

EEEManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEManalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEEM')
EEEManalysisConfigurator.addDiCandidateModule('EEEMdiElectrons','PATElePairProducer', 'smearedElectronsEEEM','smearedElectronsEEEM','smearedMETEEEM','smearedJetsEEEM',1,genParticles='genDaughters')
EEEManalysisConfigurator.addSelector('EEEMosDiElectrons','PATElePairSelector','(leg1.electronID("cicLoose")==1||leg1.electronID("cicLoose")==3||leg1.electronID("cicLoose")==5||leg1.electronID("cicLoose")==7||leg1.electronID("cicLoose")==9||leg1.electronID("cicLoose")==11||leg1.electronID("cicLoose")==13||leg1.electronID("cicLoose")==15)&&(leg2.electronID("cicLoose")==1||leg2.electronID("cicLoose")==3||leg2.electronID("cicLoose")==5||leg2.electronID("cicLoose")==7||leg2.electronID("cicLoose")==9||leg2.electronID("cicLoose")==11||leg2.electronID("cicLoose")==13||leg2.electronID("cicLoose")==15)&&charge==0&&mass>40','EEEMDiEleCreation',1)
EEEManalysisConfigurator.addDiCandidateModule('EEEMeleMu','PATEleMuPairProducer', 'smearedElectronsEEEM','smearedMuonsEEEM','smearedMETEEEM','smearedJetsEEEM',1,9999,text = 'EEEMAtLeastOneEleMu',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEEManalysisConfigurator.addDiCandidateModule('EEEMzzCands','PATEleEleEleMuQuadProducer','EEEMosDiElectrons','EEEMeleMu','smearedMETEEEM','smearedJetsEEEM',1,9999,text='EEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEManalysisConfigurator.addCrossCleanerModule('EEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='EEEMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEManalysisConfigurator.addSelector('EEEMzzCleanedeleIso','PATEleEleEleMuQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','EEEMLeadingZEleIso')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedThirdeleID','PATEleEleEleMuQuadSelector','(leg2.leg1.electronID("cicLoose")==1||leg2.leg1.electronID("cicLoose")==3||leg2.leg1.electronID("cicLoose")==5||leg2.leg1.electronID("cicLoose")==7||leg2.leg1.electronID("cicLoose")==9||leg2.leg1.electronID("cicLoose")==11||leg2.leg1.electronID("cicLoose")==13||leg2.leg1.electronID("cicLoose")==15)','EEEMLooseThirdEleCiCLoose')
EEEManalysisConfigurator.addSelector('EEEMzzMuID','PATEleEleEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','EEEMMuID')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedThirdeleIso','PATEleEleEleMuQuadSelector','((leg2.leg1.pt()>20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.35)||(leg2.leg1.pt()<20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))<7))','EEEMLooseThirdEleIso')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedmuIso','PATEleEleEleMuQuadSelector','((leg2.leg2.pt()>20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.35)||(leg2.leg2.pt()<20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))<7))','EEEMLooseMuIso')
EEEManalysisConfigurator.addSorter('EEEMzzCleanedCandsSortedByZMass','PATEleEleEleMuQuadSorterByZMass')
EEEManalysisConfigurator.addSelector('EEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEMdZ')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsAboveThreshold','PATEleEleEleMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>10 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.4','EEEMAtLeastOneZZCandOverThresholds')
EEEManalysisConfigurator.addSelector('EEEMzzCleanedCandsEleMuQ','PATEleEleEleMuQuadSelector','leg2.charge()==0','EEEMEleMuCharge')

EEEMselectionSequence =EEEManalysisConfigurator.returnSequence()


######################__________________________________EEEE_____________________________________##############################

EEEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEEanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEEE')
EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiElectrons','PATElePairProducer', 'smearedElectronsEEEE','smearedElectronsEEEE','smearedMETEEEE','smearedJetsEEEE',1,genParticles='genDaughters')
EEEEanalysisConfigurator.addSelector('EEEEosDiElectrons','PATElePairSelector','(leg1.electronID("cicLoose")==1||leg1.electronID("cicLoose")==3||leg1.electronID("cicLoose")==5||leg1.electronID("cicLoose")==7||leg1.electronID("cicLoose")==9||leg1.electronID("cicLoose")==11||leg1.electronID("cicLoose")==13||leg1.electronID("cicLoose")==15)&&(leg2.electronID("cicLoose")==1||leg2.electronID("cicLoose")==3||leg2.electronID("cicLoose")==5||leg2.electronID("cicLoose")==7||leg2.electronID("cicLoose")==9||leg2.electronID("cicLoose")==11||leg2.electronID("cicLoose")==13||leg2.electronID("cicLoose")==15)&&charge==0&&mass>40','EEEE DiEleCreation',1)
EEEEanalysisConfigurator.addDiCandidateModule('EEEEzzCands','PATEleEleEleEleQuadProducer','EEEEosDiElectrons','EEEEdiElectrons','smearedMETEEEE','smearedJetsEEEE',1,9999,text='EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEEanalysisConfigurator.addCrossCleanerModule('EEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='EEEEAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedEleIDleading','PATEleEleEleEleQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','EEEELeadingZEleIso')
EEEEanalysisConfigurator.addSelector('EEEEzzEleIDSecond','PATEleEleEleEleQuadSelector','((leg2.leg1.electronID("cicLoose")==1||leg2.leg1.electronID("cicLoose")==3||leg2.leg1.electronID("cicLoose")==5||leg2.leg1.electronID("cicLoose")==7||leg2.leg1.electronID("cicLoose")==9||leg2.leg1.electronID("cicLoose")==11||leg2.leg1.electronID("cicLoose")==13||leg2.leg1.electronID("cicLoose")==15)&&(leg2.leg2.electronID("cicLoose")==1||leg2.leg2.electronID("cicLoose")==3||leg2.leg2.electronID("cicLoose")==5||leg2.leg2.electronID("cicLoose")==7||leg2.leg2.electronID("cicLoose")==9||leg2.leg2.electronID("cicLoose")==11||leg2.leg1.electronID("cicLoose")==13||leg2.leg2.electronID("cicLoose")==15))','EEEEsecondLegEleCiCLoose')
EEEEanalysisConfigurator.addSelector('EEEEzzEleIsoSecond','PATEleEleEleEleQuadSelector','((leg2.leg1.pt()>20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.35)||(leg2.leg1.pt()<20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))<7))&&((leg2.leg2.pt()>20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.35)||(leg2.leg2.pt()<20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))<7))','EEEEsecondLegLooseEleIso')
EEEEanalysisConfigurator.addSorter('EEEEzzCleanedCandsSortedByZMass','PATEleEleEleEleQuadSorterByZMass')
EEEEanalysisConfigurator.addSelector('EEEEzzdZ','PATEleEleEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEEdZ')
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedCandsAboveThreshold','PATEleEleEleEleQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>7 &&leg2().leg2().pt()>7 && abs(leg2.leg2.eta())<2.5 && abs(leg2.leg2.eta())<2.5','EEEEAtLeastOneZZCandOverThresholds')
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedCandsEleEleQ','PATEleEleEleEleQuadSelector','leg2.charge()==0','EEEESecondZCharge')

EEEEselectionSequence =EEEEanalysisConfigurator.returnSequence()

######################__________________________________EEMM_____________________________________##############################

EEMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEMManalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEMM')
EEMManalysisConfigurator.addDiCandidateModule('EEMMdiElectrons','PATElePairProducer', 'smearedElectronsEEMM','smearedElectronsEEMM','smearedMETEEMM','smearedJetsEEMM',1,genParticles='genDaughters')
EEMManalysisConfigurator.addSelector('EEMMosDiElectrons','PATElePairSelector','(leg1.electronID("cicLoose")==1||leg1.electronID("cicLoose")==3||leg1.electronID("cicLoose")==5||leg1.electronID("cicLoose")==7||leg1.electronID("cicLoose")==9||leg1.electronID("cicLoose")==11||leg1.electronID("cicLoose")==13||leg1.electronID("cicLoose")==15)&&(leg2.electronID("cicLoose")==1||leg2.electronID("cicLoose")==3||leg2.electronID("cicLoose")==5||leg2.electronID("cicLoose")==7||leg2.electronID("cicLoose")==9||leg2.electronID("cicLoose")==11||leg2.electronID("cicLoose")==13||leg2.electronID("cicLoose")==15)&&charge==0&&mass>40','EEMM DiEleCreation',1)
EEMManalysisConfigurator.addDiCandidateModule('EEMMdiMuons','PATMuPairProducer', 'smearedMuonsEEMM','smearedMuonsEEMM','smearedMETEEMM','smearedJetsEEMM',1)
EEMManalysisConfigurator.addDiCandidateModule('EEMMzzCands','PATEleEleMuMuQuadProducer','EEMMosDiElectrons','EEMMdiMuons','smearedMETEEMM','smearedJetsEEMM',1,9999,text='EEMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMManalysisConfigurator.addCrossCleanerModule('EEMMzzCleanedCands','PATEleEleMuMuQuadCrossCleaner',1,9999,text='EEMMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMManalysisConfigurator.addSelector('EEMMzzCleanedEleIDleading','PATEleEleMuMuQuadSelector','((leg1.leg1.pt()>20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.35)||(leg1.leg1.pt()<20&&(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))<7))&&((leg1.leg2.pt()>20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.35)||(leg1.leg2.pt()<20&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))<7))','EEMMLeadingZEleIso')
#EEMManalysisConfigurator.addSelector('EEMMzzMuMuMass','PATEleEleMuMuQuadSelector','leg2.mass<60','EEMMmumuMass')
EEMManalysisConfigurator.addSelector('EEMMzzMuIDSecondPair','PATEleEleMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','EEMMsecondPairID')
EEMManalysisConfigurator.addSelector('EEMMzzCleanedMuIsoSecondPair','PATEleEleMuMuQuadSelector','((leg2.leg1.pt()>20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.35)||(leg2.leg1.pt()<20&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))<7))&&((leg2.leg2.pt()>20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.35)||(leg2.leg2.pt()<20&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))<7))','EEMMsecondPairIso')
EEMManalysisConfigurator.addSorter('EEMMzzCleanedCandsSortedByZMass','PATEleEleMuMuQuadSorterByZMass')
EEMManalysisConfigurator.addSelector('EEMMzzdZ','PATEleEleMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMMdZ')
EEMManalysisConfigurator.addSelector('EEMMzzCleanedCandsAboveThreshold','PATEleEleMuMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>5 &&leg2().leg2().pt()>5 && abs(leg2.leg2.eta())<2.5 && abs(leg2.leg2.eta())<2.5','EEMMAtLeastOneZZCandOverThresholds')
EEMManalysisConfigurator.addSelector('EEMMzzCleanedCandsMuMuQ','PATEleEleMuMuQuadSelector','leg2.charge()==0','EEMMSecondZCharge')

EEMMselectionSequence =EEMManalysisConfigurator.returnSequence()

#####################_______________________________EndOfConfigurators__________________________################################

