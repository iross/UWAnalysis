import FWCore.ParameterSet.Config as cms



###MU ENRICHED QCD#####################################################################################################
from UWAnalysis.Configuration.tools.CutSequenceProducer import *


muEnrichedConfigurator = CutSequenceProducer(initialCounter  = 'initialMuEnrichedEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())


muEnrichedConfigurator.addDiCandidateModule('diMuonsMuEnrichedFR','PATMuPairProducer', 'patMuonsForAnalysis','patMuonsForAnalysis','patMETs','selectedPatJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
muEnrichedConfigurator.addSelector('osDiMuonsMuEnrichedFR','PATMuPairSelector','charge==0&&leg1.isGlobalMuon&&leg2.isGlobalMuon&&((leg1.chargedHadronIso+leg1.photonIso+leg1.neutralHadronIso)/leg1.pt()<0.26)&&((leg2.chargedHadronIso+leg2.photonIso+leg2.neutralHadronIso)/leg2.pt()<0.3)','',0,0)
#Make Muons+MET
muEnrichedConfigurator.addCandidateMETModule('muEnrichedCands','PATMuonNuPairProducer','patMuonsForAnalysis','patMETs','selectedPatJets',0,9999,'')
muEnrichedConfigurator.addSelector('muEnrichedSelectedCands','PATMuonNuPairSelector','lepton.pt()>15&&abs(lepton.eta())<2.1&&((lepton.chargedHadronIso+lepton.photonIso+lepton.neutralHadronIso)/lepton.pt()>0.5)&&(lepton.triggerObjectMatchesByPath("HLT_Mu9").size>0||(lepton.triggerObjectMatchesByPath("HLT_Mu11").size>0)||(lepton.triggerObjectMatchesByPath("HLT_Mu15_v1").size>0))&&mt<40.','',0,100)
muEnrichedConfigurator.addGeneric('muEnrichedJetsForFakeRate','MuonNuPairJetFetcher')

muEnrichedSequence = muEnrichedConfigurator.returnSequence()





