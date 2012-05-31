import FWCore.ParameterSet.Config as cms

from UWAnalysis.Configuration.tools.CutSequenceProducer import *

MC2011TriggerPaths=["HLT_Mu17_Mu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]
DATA2011TriggerPaths=["HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL","HLT_Mu17_Mu8","HLT_DoubleMu7","HLT_Mu13_Mu8"]
DATAMC2012TriggerPaths=["HLT_Mu17_Mu8","HLT_Mu17_TkMu8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL","HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"]

MMMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMManalysisConfigurator.addSelectorPdgID("test","PdgIdAndStatusCandViewSelector","genDaughters","genReq2",[11,13],1,9999)
MMMManalysisConfigurator.addGeneric("dilep","CandViewShallowCloneCombiner","test@- test@+","","dilep")
MMMManalysisConfigurator.addSelector("dilepClean","CandViewSelector","deltaR(daughter(0).eta,daughter(0).phi,daughter(1).eta,daughter(1).phi)>0","dilep clean")
MMMManalysisConfigurator.addGeneric("zz","CandViewShallowCloneCombiner","dilep dilep","","fourl")
MMMManalysisConfigurator.addGeneric("zzOnShell","CandViewShallowCloneCombiner","dilep dilep","daughter(0).mass>60 && daughter(0).mass<120 && daughter(1).mass>60&&daughter(1).mass<120","fourlOnShell")
MMMMselectionSequence =MMMManalysisConfigurator.returnSequence()

