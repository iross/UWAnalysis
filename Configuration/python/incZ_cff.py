import FWCore.ParameterSet.Config as cms

#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *



llLeadingIso1='(leg1.pt()>20&&(leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))/leg1.pt()<0.25)'
llLeadingIso2='(leg2.pt()>10&&(leg2.chargedHadronIso()+max(leg2.photonIso()+leg2.neutralHadronIso()-0.5*leg2.userIso(0),0.0))/leg2.pt()<0.25)'
llLeadingIso=llLeadingIso1+'&&'+llLeadingIso2
mumuLeadingID='leg1.isGlobalMuon()&&leg2.isGlobalMuon()&&leg1.isTrackerMuon()&&leg2.isTrackerMuon()'
mumuLeading=mumuLeadingID+'&& mass>60 && mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4'
eeLeading='charge==0 && leg1.electronID("cicTight")&1==1 && leg2.electronID("cicTight")&1==1 && mass>60 && mass<120 && abs(leg1.eta())<2.5 && abs(leg2.eta())<2.5'

EEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEE',
                                                                                 pyModuleName = __name__,
                                                                                 pyNameSpace  = locals())

EEanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EE')
EEanalysisConfigurator.addDiCandidateModule('EEdiElectrons','PATElePairProducer', 'smearedElectronsEE','smearedElectronsEE','smearedMETEE','smearedJetsEE',1,genParticles='genDaughters')
EEanalysisConfigurator.addSorter('zEleEleCandidatesSorted','PATElePairSorter')
EEanalysisConfigurator.addSelector('EEosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&mass>40 && leg1.userFloat("SIP3D")<4 && leg2.userFloat("SIP3D")<4','EEDiEleCreation',1)
EEanalysisConfigurator.addSelector('EEeleIso','PATElePairSelector',llLeadingIso,'EELeadingZEleIso')
EEanalysisConfigurator.addSelector('EEaboveThresh','PATElePairSelector','leg1.pt()>20 && leg2.pt()>10','EEAtLeastOneZZCandOverThresholds')

zEleEleSelectionSequence =EEanalysisConfigurator.returnSequence()

MManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMM',
                                                                                                                              pyModuleName = __name__,
                                                                                                                              pyNameSpace  = locals())
#Add smearing
MManalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets')
#Create di muon OS pairs
MManalysisConfigurator.addDiCandidateModule('MMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MManalysisConfigurator.addSorter('zMuMuCandidatesSorted','PATMuPairSorter')
MManalysisConfigurator.addSelector('MMzzMuID','PATMuPairSelector','leg1.isGlobalMuon()&&leg2.isGlobalMuon()&&leg1.isTrackerMuon()&&leg2.isTrackerMuon()','MMLeadingZMuID')
MManalysisConfigurator.addSelector('MMzzMuIso','PATMuPairSelector','((leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))/leg1.pt()<0.25) && ((leg2.chargedHadronIso()+max(leg2.photonIso()+leg2.neutralHadronIso()-0.5*leg2.userIso(0),0.0))/leg2.pt()<0.25)','MMLeadingZMuIso')
MManalysisConfigurator.addSelector('MMaboveThresh','PATMuPairSelector','leg1.pt()>20 && leg2.pt()>10 && leg1.userFloat("SIP3D")<4 && leg2.userFloat("SIP3D")<4','MMAtLeastOneZZCandOverThresholds')

#create the sequence
zMuMuSelectionSequence =MManalysisConfigurator.returnSequence()
