import FWCore.ParameterSet.Config as cms

#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

analysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
#Add smearing
analysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets')
#Create di muon OS pairs 
analysisConfigurator.addDiCandidateModule('diMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1)
#Require they are OS and at least Global muons
analysisConfigurator.addSelector('osDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon&&leg2.isGlobalMuon&& mass>60','DiMuonCreation',1)
#Make DiTaus
analysisConfigurator.addDiCandidateModule('diTaus','PATDiTauPairProducer','smearedTaus','smearedTaus','smearedMET','smearedJets',1,9999,text='AtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
#Combine and create zz candidates
analysisConfigurator.addDiCandidateModule('zzCands','PATMuMuTauTauQuadProducer','osDiMuons','diTaus','smearedMET','smearedJets',1,9999,text='AtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
#cross clean the legs of the ZZ (i.e the two Zs by product ID and DeltaR
analysisConfigurator.addCrossCleanerModule('zzCleanedCands','PATMuMuTauTauQuadCrossCleaner',1,9999,text='AtLeastOneZZCleanedCandidate',dR = 0.1)
analysisConfigurator.addSelector('zzCleanedMuID','PATMuMuTauTauQuadSelector','leg1.leg1.userFloat("isWWMuon")&&leg1.leg2.userFloat("isWWMuon")','WWMuonID')
analysisConfigurator.addSelector('zzCleanedMuIso','PATMuMuTauTauQuadSelector','(leg1.leg1.isolationR03.sumPt+leg1.leg1.isolationR03.emEt+leg1.leg1.isolationR03.hadEt)/leg1.leg1.pt()<0.2&&(leg1.leg2.isolationR03.sumPt+leg1.leg2.isolationR03.emEt+leg1.leg2.isolationR03.hadEt)/leg1.leg2.pt()<0.2','LooseMuIso')
#Sort your ZZ candidates by higher Z1 Pt + Z2 Pt 
analysisConfigurator.addSorter('zzCleanedCandsSorted','PATMuMuTauTauQuadSorter')

#JustIllustrate a selector (i.e require that pt of all legs is above a threshold
analysisConfigurator.addSelector('zzCleanedCandsAboveThreshold','PATMuMuTauTauQuadSelector','leg1().leg1().pt()>10 && leg1().leg2().pt()>10 && leg2().leg1().pt()>10 &&leg2().leg2().pt()>10','AtLeastOneZZCandOverThresholds')
#Apply loose tau ID
analysisConfigurator.addSelector('zzCleanedCandsTauID','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','DecayModeFinding')
analysisConfigurator.addSelector('zzCleanedCandsTauIso','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("byVLooseIsolation")&&leg2.leg2.tauID("byVLooseIsolation")','TauIsolation')
analysisConfigurator.addSelector('zzCleanedCandsMuRej','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("againstMuonLoose")&&leg2.leg2.tauID("againstMuonLoose")','TauMuRejection')
analysisConfigurator.addSelector('zzCleanedCandsEleRej','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstElectronLoose")','TauEleRejection')
analysisConfigurator.addSelector('zzCleanedCandsTauTauQ','PATMuMuTauTauQuadSelector','leg2.charge()==0','TauTauCharge')

#create the sequence
selectionSequence =analysisConfigurator.returnSequence()




