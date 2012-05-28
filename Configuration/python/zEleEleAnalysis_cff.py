import FWCore.ParameterSet.Config as cms



#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

zEleEleAnalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialZEleEleEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
zEleEleAnalysisConfigurator.addDiCandidateModule('zEleEleCandidates','PATElePairProducer', 'convRejElectrons','convRejElectrons','patMETs','selectedPatJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
zEleEleAnalysisConfigurator.addSorter('zEleEleCandidatesSorted','PATElePairSorter')
zEleEleAnalysisConfigurator.addSelector('zEleEleCandidatesID','PATElePairSelector','leg1.userFloat("WWID")>0&&leg2.userFloat("WWID")>0 &&leg1.pt()>15&&leg2.pt()>15','ZEleEleID')
# zEleEleAnalysisConfigurator.addEleEleSVFit('zEleEleCandidatesSVFit')
zEleEleAnalysisConfigurator.addSelector('zEleEleCandidatesIsol1','PATElePairSelector','leg1.dr03TkSumPt()/leg1.pt()<0.25','ZEleEleLeg1Iso')
zEleEleAnalysisConfigurator.addSelector('zEleEleCandidatesIsol2','PATElePairSelector','leg1.dr03TkSumPt()/leg2.pt()<0.25','ZEleEleLeg2Iso')
zEleEleAnalysisConfigurator.addSelector('zEleEleCandidatesOS','PATElePairSelector','charge==0','ZEleEleOS',0,100)
#create the sequence
zEleEleSelectionSequence=zEleEleAnalysisConfigurator.returnSequence()




