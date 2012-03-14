import FWCore.ParameterSet.Config as cms

#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

######################________________________mu+mu pair as leading______________________________##############################

mumuLeadingCut='charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4'
#(chargedHadronIso+max(photonIso+neutralHadronIso-0.5*userIso(0),0.0)
llLeadingIso1='(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25'
llLeadingIso2='(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25'
llSecondIso1='(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25'
llSecondIso2='(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25'
llLeadingIso=llLeadingIso1+"&&"+llLeadingIso2
llSecondIso=llSecondIso1+"&&"+llSecondIso2
mumuLeadingID='leg1.leg1.isGlobalMuon()&&leg1.leg2.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()'
mumuSecondID='leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()'
######################__________________________________MMEE_____________________________________##############################

MMEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','MMEE')
MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiMuons','PATMuPairProducer', 'smearedMuonsMMEE','smearedMuonsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')
MMEEanalysisConfigurator.addSelector('MMEEosDiMuons','PATMuPairSelector',mumuLeadingCut,'MMEE DiMuonCreation',1)
MMEEanalysisConfigurator.addDiCandidateModule('MMEEeleEle','PATElePairProducer','smearedElectronsMMEE','smearedElectronsMMEE','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneEleEle',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEanalysisConfigurator.addDiCandidateModule('MMEEzzCands','PATMuMuEleEleQuadProducer','MMEEosDiMuons','MMEEeleEle','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEanalysisConfigurator.addCrossCleanerModule('MMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='MMEEAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedMuID','PATMuMuEleEleQuadSelector',mumuLeadingID,'MMEELeadingZMuID')
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedMuIso','PATMuMuEleEleQuadSelector',llLeadingIso,'MMEELeadingZMuIso')
MMEEanalysisConfigurator.addSelector('MMEEzzEleId','PATMuMuEleEleQuadSelector','(leg2.leg1.electronID("cicTight")&1==1)&&(leg2.leg2.electronID("cicTight")&1==1)','MMEEEleCiCTight') 
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedEleIso','PATMuMuEleEleQuadSelector',llSecondIso,'MMEELooseEleIso')
MMEEanalysisConfigurator.addSorter('MMEEzzCleanedCandsSortedByZMass','PATMuMuEleEleQuadSorterByZMass')
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedCandsAboveThreshold','PATMuMuEleEleQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>7 &&leg2().leg2().pt()>7 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.5','MMEEAtLeastOneZZCandOverThresholds')
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedCandsEleEleQ','PATMuMuEleEleQuadSelector','leg2.charge()==0','EleEleCharge')

MMEEselectionSequence =MMEEanalysisConfigurator.returnSequence()


######################__________________________________MMMM_____________________________________##############################

MMMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMManalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','MMMM')
MMMManalysisConfigurator.addDiCandidateModule('MMMMdiMuons','PATMuPairProducer', 'smearedMuonsMMMM','smearedMuonsMMMM','smearedMETMMMM','smearedJetsMMMM',1,genParticles='genDaughters')
MMMManalysisConfigurator.addSelector('MMMMosDiMuons','PATMuPairSelector',mumuLeadingCut,'MMMM DiMuonCreation',1)
MMMManalysisConfigurator.addDiCandidateModule('MMMMzzCands','PATMuMuMuMuQuadProducer','MMMMosDiMuons','MMMMdiMuons','smearedMETMMMM','smearedJetsMMMM',1,9999,text='MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMManalysisConfigurator.addCrossCleanerModule('MMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='MMMMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMManalysisConfigurator.addSelector('MMMMzzCleanedMuID','PATMuMuMuMuQuadSelector',mumuLeadingID,'MMMMLeadingZMuID')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedMuIso','PATMuMuMuMuQuadSelector',llLeadingIso,'MMMMLeadingZMuIso')
MMMManalysisConfigurator.addSelector('MMMMzzMuIDSecondPair','PATMuMuMuMuQuadSelector',mumuSecondID,'MMMMsecondPairID')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedMuIsoSecondPair','PATMuMuMuMuQuadSelector',llSecondIso,'MMMMsecondPairIso')
MMMManalysisConfigurator.addSorter('MMMMzzCleanedCandsSortedByZMass','PATMuMuMuMuQuadSorterByZMass')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedCandsAboveThreshold','PATMuMuMuMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>5 &&leg2().leg2().pt()>5 && abs(leg2.leg1.eta())<2.4 && abs(leg2.leg2.eta())<2.4','MMMMAtLeastOneZZCandOverThresholds')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedCandsMuMuQ','PATMuMuMuMuQuadSelector','leg2.charge()==0','MMMMSecondZCharge')

MMMMselectionSequence =MMMManalysisConfigurator.returnSequence()


######################___________________electron+electron pair as leading Z_____________________##############################

eeLeading='charge==0 && leg1.electronID("cicTight")&1==1 && leg2.electronID("cicTight")&1==1 && mass>60'

######################__________________________________EEEE_____________________________________##############################

EEEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEEanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEEE')
EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiElectrons','PATElePairProducer', 'smearedElectronsEEEE','smearedElectronsEEEE','smearedMETEEEE','smearedJetsEEEE',1,genParticles='genDaughters')
EEEEanalysisConfigurator.addSelector('EEEEosDiElectrons','PATElePairSelector',eeLeading,'EEEE DiEleCreation',1)
EEEEanalysisConfigurator.addDiCandidateModule('EEEEzzCands','PATEleEleEleEleQuadProducer','EEEEosDiElectrons','EEEEdiElectrons','smearedMETEEEE','smearedJetsEEEE',1,9999,text='EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEEanalysisConfigurator.addCrossCleanerModule('EEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='EEEEAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedEleIDleading','PATEleEleEleEleQuadSelector',llLeadingIso,'EEEELeadingZEleIso')
EEEEanalysisConfigurator.addSelector('EEEEzzEleIDthird','PATEleEleEleEleQuadSelector','leg2.leg1.electronID("cicTight")&1==1','EEEEsecondLegEleCiCTight')
EEEEanalysisConfigurator.addSelector('EEEEzzEleIDfourth','PATEleEleEleEleQuadSelector','leg2.leg2.electronID("cicLoose")&1==1','EEEEsecondLegEleCiCLoose')
EEEEanalysisConfigurator.addSelector('EEEEzzEleIsoSecond','PATEleEleEleEleQuadSelector',llSecondIso,'EEEEsecondLegLooseEleIso')
EEEEanalysisConfigurator.addSorter('EEEEzzCleanedCandsSortedByZMass','PATEleEleEleEleQuadSorterByZMass')
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedCandsAboveThreshold','PATEleEleEleEleQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>7 &&leg2().leg2().pt()>7 && abs(leg2.leg2.eta())<2.5 && abs(leg2.leg2.eta())<2.5','EEEEAtLeastOneZZCandOverThresholds')
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedCandsEleEleQ','PATEleEleEleEleQuadSelector','leg2.charge()==0','EEEESecondZCharge')

EEEEselectionSequence =EEEEanalysisConfigurator.returnSequence()

######################__________________________________EEMM_____________________________________##############################

EEMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEMManalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEMM')
EEMManalysisConfigurator.addDiCandidateModule('EEMMdiElectrons','PATElePairProducer', 'smearedElectronsEEMM','smearedElectronsEEMM','smearedMETEEMM','smearedJetsEEMM',1,genParticles='genDaughters')
EEMManalysisConfigurator.addSelector('EEMMosDiElectrons','PATElePairSelector',eeLeading,'EEMM DiEleCreation',1)
EEMManalysisConfigurator.addDiCandidateModule('EEMMdiMuons','PATMuPairProducer', 'smearedMuonsEEMM','smearedMuonsEEMM','smearedMETEEMM','smearedJetsEEMM',1)
EEMManalysisConfigurator.addDiCandidateModule('EEMMzzCands','PATEleEleMuMuQuadProducer','EEMMosDiElectrons','EEMMdiMuons','smearedMETEEMM','smearedJetsEEMM',1,9999,text='EEMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMManalysisConfigurator.addCrossCleanerModule('EEMMzzCleanedCands','PATEleEleMuMuQuadCrossCleaner',1,9999,text='EEMMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMManalysisConfigurator.addSelector('EEMMzzCleanedEleIDleading','PATEleEleMuMuQuadSelector',llLeadingIso,'EEMMLeadingZEleIso')
#EEMManalysisConfigurator.addSelector('EEMMzzMuMuMass','PATEleEleMuMuQuadSelector','leg2.mass<60','EEMMmumuMass')
EEMManalysisConfigurator.addSelector('EEMMzzMuIDSecondPair','PATEleEleMuMuQuadSelector',mumuSecondID,'EEMMsecondPairID')
EEMManalysisConfigurator.addSelector('EEMMzzCleanedMuIsoSecondPair','PATEleEleMuMuQuadSelector',llSecondIso,'EEMMsecondPairIso')
EEMManalysisConfigurator.addSorter('EEMMzzCleanedCandsSortedByZMass','PATEleEleMuMuQuadSorterByZMass')
EEMManalysisConfigurator.addSelector('EEMMzzCleanedCandsAboveThreshold','PATEleEleMuMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>5 &&leg2().leg2().pt()>5 && abs(leg2.leg2.eta())<2.5 && abs(leg2.leg2.eta())<2.5','EEMMAtLeastOneZZCandOverThresholds')
EEMManalysisConfigurator.addSelector('EEMMzzCleanedCandsMuMuQ','PATEleEleMuMuQuadSelector','leg2.charge()==0','EEMMSecondZCharge')

EEMMselectionSequence =EEMManalysisConfigurator.returnSequence()

#####################_______________________________EndOfConfigurators__________________________################################

