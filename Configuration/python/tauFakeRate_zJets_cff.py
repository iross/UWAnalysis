import FWCore.ParameterSet.Config as cms



###MU ENRICHED QCD#####################################################################################################
from UWAnalysis.Configuration.tools.CutSequenceProducer import *


zJetsConfigurator = CutSequenceProducer(initialCounter  = 'initialZJetsEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())


zJetsConfigurator.addDiCandidateModule('diMuonszJetsFR','PATMuPairProducer', 'patMuonsForAnalysis','patMuonsForAnalysis','patMETs','selectedPatJets',1,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
zJetsConfigurator.addSelector('osDiMuonsZJetsFR','PATMuPairSelector','charge==0&&leg1.isGlobalMuon&&leg2.isGlobalMuon&&((leg1.chargedHadronIso+leg1.photonIso+leg1.neutralHadronIso)/leg1.pt()<0.2)&&((leg2.chargedHadronIso+leg2.photonIso+leg2.neutralHadronIso)/leg2.pt()<0.2)&&mass>35&&mass<120','',0,100)
zJetsConfigurator.addGeneric('zJetsForFakeRate','MuonPairJetFetcher')
zJetsSequence = zJetsConfigurator.returnSequence()





