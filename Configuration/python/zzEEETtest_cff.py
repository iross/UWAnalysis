import FWCore.ParameterSet.Config as cms

#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

######################__________________________________EEET_____________________________________##############################

EEETanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEET',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEETanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEET')
EEETanalysisConfigurator.addDiCandidateModule('EEETdiElectrons','PATElePairProducer', 'smearedElectronsEEET','smearedElectronsEEET','smearedMETEEET','smearedJetsEEET',1,genParticles='genDaughters')
EEETanalysisConfigurator.addSelector('EEETosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>40&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5','EEETDiEleCreation',1)
EEETanalysisConfigurator.addDiCandidateModule('EEETeleTau','PATEleTauPairProducer', 'smearedElectronsEEET','smearedTausEEET','smearedMETEEET','smearedJetsEEET',1,9999,text = 'EEETAtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETanalysisConfigurator.addDiCandidateModule('EEETzzCands','PATEleEleEleTauQuadProducer','EEETosDiElectrons','EEETeleTau','smearedMETEEET','smearedJetsEEET',1,9999,text='EEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEETanalysisConfigurator.addCrossCleanerModule('EEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='EEETAtLeastOneZZCleanedCandidate',dR = 0.1)
EEETanalysisConfigurator.addSelector('EEETzzEleIso','PATEleEleEleTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','EEETLeadingZEleIso')
EEETanalysisConfigurator.addSelector('EEETzzCleanedThirdeleID','PATEleEleEleTauQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','EEETTightThirdEleCiCTight')
EEETanalysisConfigurator.addSelector('EEETzzTauID','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','EEETDecayModeFinding')
EEETanalysisConfigurator.addSelector('EEETzzEleIso2','PATEleEleEleTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.10','EEETSecondZEleIso')
EEETanalysisConfigurator.addSelector('EEETzzTauIso','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")','EEETTauLooseIsolation')
EEETanalysisConfigurator.addSorter('EEETzzCleanedCandsSortedByZMass','PATEleEleEleTauQuadSorterByZMass')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsAboveThreshold','PATEleEleEleTauQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>20 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.3','EEETAtLeastOneZZCandOverThresholds')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsLepRej','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("againstMuonLoose")&&leg2.leg2.tauID("againstElectronLoose")','EEETTauLepRejection')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsETauQ','PATEleEleEleTauQuadSelector','leg2.charge()==0','EEETEleTauCharge')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsEEMass','PATEleEleEleTauQuadSelector','leg1.mass()>60&&leg1.mass()<120','EEETEEMass')
EEETanalysisConfigurator.addSorter('EEETFinalSel','PATEleEleEleTauQuadSorterByZMass')
EEETanalysisConfigurator.addSelector('EEETzzCleanedCandsETMass','PATEleEleEleTauQuadSelector','leg2.mass()>30&&leg2.mass()<80','EEETETMass')
EEETselectionSequence =EEETanalysisConfigurator.returnSequence()

#####################_______________________________EndOfConfigurators__________________________################################

