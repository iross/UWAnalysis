import FWCore.ParameterSet.Config as cms
from RecoLuminosity.LumiDB import argparse
import FWCore.ParameterSet.VarParsing as VarParsing
import sys

options = VarParsing.VarParsing ('analysis')

options.register ('leadingOnly',
                  1, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "Only save leading candidate (default: 1)")
options.register ('leptonDump',
                  0, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "Dump information for all leptons (default: 0)")
options.register ('run2l2t',
                  0, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "Run 2l2tau final states (default: 0)")
options.register ('isMC',
                  0, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "Running on MC? (default: 0)")
options.register ('reportEvery',
                  1, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "Report every n events (default: 1)")
options.register ('effAreaTarget',
                  "2012Data", # default value. Available targets: Fal11MC, Summer11MC, 2011Data, 2012Data
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "Effective area target (default: 2012Data)")

options.maxEvents = 2000

options.parseArguments()

leadingOnly = bool(options.leadingOnly) #need to pass a bool to ntuple tools

#todo: add MC flag, release checking, EA targets, triggers, ...

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

if options.isMC:
    print "\nUsing MC settings!\n"
    process.GlobalTag.globaltag = 'START53_V10::All'
else:
    process.GlobalTag.globaltag = 'GR_R_52_V8::All'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(options.maxEvents)
        )

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = options.reportEvery
process.MessageLogger.categories.append('CalibrationChooser')
process.MessageLogger.cerr.CalibrationChooser = cms.untracked.PSet(
            limit=cms.untracked.int32(10)
            )

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            options.inputFiles
            ),
        inputCommands=cms.untracked.vstring(
            'keep *',
            'drop *_finalState*_*_*',
            'drop *_patFinalStateEvent*_*_*'
            )
        )

#process.source.secondaryFileNames = cms.untracked.vstring(
#        "file:/hdfs/store/data/Run2012C/DoubleMu/AOD/PromptReco-v2/000/201/278/487F6493-1EEE-E111-A398-001D09F297EF.root"
#        "file:/hdfs/store/data/Run2012B/DoubleElectron/AOD/13Jul2012-v1/00000/AAB0C291-89D4-E111-8D74-0026189438A0.root"
#        "file:/hdfs/store/data/Run2012B/DoubleElectron/AOD/13Jul2012-v1/00000/387EB788-6FD4-E111-9DBA-002618943944.root"
#        )

from UWAnalysis.Configuration.tools.analysisTools import *
defaultAnalysisPath(process,'HLT',
        [
            "HLT_Mu17_Mu8",
            "HLT_Mu17_TkMu8",
            "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL",
            "HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL",
            "HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"
            ],
        EAtarget=options.effAreaTarget
        )

#EventSelection
if leadingOnly is True:
    process.load("UWAnalysis.Configuration.zzLLLL_2012_cff")
else:
    print "\nSaving all candidates\n"
    process.load("UWAnalysis.Configuration.zzLLLL_2012_loose_cff")

process.eventSelectionMMEE = cms.Path(process.MMEEselectionSequence)
process.eventSelectionMMEEonly = cms.Path(process.MMEEonlyselectionSequence)
process.eventSelectionMMMM = cms.Path(process.MMMMselectionSequence)
process.eventSelectionEEEE = cms.Path(process.EEEEselectionSequence)
process.eventSelectionEEMM = cms.Path(process.EEMMselectionSequence)
process.eventSelectionMMM = cms.Path(process.MMMSeq)
process.eventSelectionMME = cms.Path(process.MMESeq)
process.eventSelectionEEM = cms.Path(process.EEMSeq)
process.eventSelectionEEE = cms.Path(process.EEESeq)
process.eventSelectionMM = cms.Path(process.ZMMSeq)
process.eventSelectionEE = cms.Path(process.ZEESeq)
#process.eventSelectionEEES = cms.Path(process.EEESselectionSequence)

from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleEventTreeFinal','MMEEZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
addMuMuEleEleEventTree(process,'muMuEleEleEventTree','MMEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuMuEventTree
addMuMuMuMuEventTree(process,'muMuMuMuEventTree','MMMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
addMuMuMuMuEventTree(process,'muMuMuMuEventTreeFinal','MMMMZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEleEventTree
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTreeFinal','MMEEonlyZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
addMuMuEleEleEventTree(process,'muMuEleEleonlyEventTree','MMEEonlyzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEleEventTree
addEleEleEleEleEventTree(process,'eleEleEleEleEventTree','EEEEzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
addEleEleEleEleEventTree(process,'eleEleEleEleEventTreeFinal','EEEEZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuMuEventTree
addEleEleMuMuEventTree(process,'eleEleMuMuEventTree','EEMMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
addEleEleMuMuEventTree(process,'eleEleMuMuEventTreeFinal','EEMMZ4lSpace','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)


from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuEventTree
addMuMuMuEventTree(process,'muMuMuEventTree','triMMMthirdMuID',leadingOnly=leadingOnly)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleEventTree
addMuMuEleEventTree(process,'muMuEleEventTree','triMMEthirdEleID',leadingOnly=leadingOnly)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuEventTree
addEleEleMuEventTree(process,'eleEleMuEventTree','triEEMthirdMuID',leadingOnly=leadingOnly)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleEventTree
addEleEleEleEventTree(process,'eleEleEleEventTree','triEEEthirdEleID',leadingOnly=leadingOnly)
from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEventTree
addEleEleEventTree(process,'eleEleEventTree','ZEEFinal',leadingOnly=leadingOnly)
from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEventTree
addMuMuEventTree(process,'muMuEventTree','ZMMFinal',leadingOnly=leadingOnly)

#Add event counter
addEventSummary(process,leadingOnly,'MMEE','eventSelectionMMEE')
addEventSummary(process,leadingOnly,'EEEE','eventSelectionEEEE')
addEventSummary(process,leadingOnly,'EEMM','eventSelectionEEMM')
addEventSummary(process,leadingOnly,'MMMM','eventSelectionMMMM')
addEventSummary(process,leadingOnly,'MM','eventSelectionEE')
addEventSummary(process,leadingOnly,'EE','eventSelectionMM')

if options.leptonDump:
#    from UWAnalysis.Configuration.tools.zzNtupleTools import addMuTree
#    addMuTree(process,'muons','corrMuons',leadingOnly=False)
    from UWAnalysis.Configuration.tools.zzNtupleTools import addEleTree
    addEleTree(process,'finalElectrons','mvaedElectrons',leadingOnly=False)
    addEleTree(process,'correctedElectrons','corrElectrons',leadingOnly=False)
    addEleTree(process,'cleanElectrons','cleanPatElectrons',leadingOnly=False)

if options.run2l2t:
    process.eventSelectionMMTT = cms.Path(process.MMTTselectionSequence)
    process.eventSelectionMMMT = cms.Path(process.MMMTselectionSequence)
    process.eventSelectionMMET = cms.Path(process.MMETselectionSequence)
    process.eventSelectionMMEM = cms.Path(process.MMEMselectionSequence)
    process.eventSelectionEEMT = cms.Path(process.EEMTselectionSequence)
    process.eventSelectionEEET = cms.Path(process.EEETselectionSequence)
    process.eventSelectionEETT = cms.Path(process.EETTselectionSequence)
    process.eventSelectionEEEM = cms.Path(process.EEEMselectionSequence)

    from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuTauTauEventTree
    addMuMuTauTauEventTree(process,'muMuTauTauEventTree','MMTTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    addMuMuTauTauEventTree(process,'muMuTauTauEventTreeFinal','MMTTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuMuTauEventTree
    addMuMuMuTauEventTree(process,'muMuMuTauEventTree','MMMTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    addMuMuMuTauEventTree(process,'muMuMuTauEventTreeFinal','MMMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleTauEventTree
    addMuMuEleTauEventTree(process,'muMuEleTauEventTree','MMETzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    addMuMuEleTauEventTree(process,'muMuEleTauEventTreeFinal','MMETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    from UWAnalysis.Configuration.tools.zzNtupleTools import addMuMuEleMuEventTree
    addMuMuEleMuEventTree(process,'muMuEleMuEventTree','MMEMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    addMuMuEleMuEventTree(process,'muMuEleMuEventTreeFinal','MMEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleTauTauEventTree
    addEleEleTauTauEventTree(process,'eleEleTauTauEventTree','EETTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    addEleEleTauTauEventTree(process,'eleEleTauTauEventTreeFinal','EETTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleTauEventTree
    addEleEleEleTauEventTree(process,'eleEleEleTauEventTree','EEETzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    addEleEleEleTauEventTree(process,'eleEleEleTauEventTreeFinal','EEETFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleMuTauEventTree
    addEleEleMuTauEventTree(process,'eleEleMuTauEventTree','EEMTzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    addEleEleMuTauEventTree(process,'eleEleMuTauEventTreeFinal','EEMTFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    from UWAnalysis.Configuration.tools.zzNtupleTools import addEleEleEleMuEventTree
    addEleEleEleMuEventTree(process,'eleEleEleMuEventTree','EEEMzzCleanedCands','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)
    addEleEleEleMuEventTree(process,'eleEleEleMuEventTreeFinal','EEEMFinalSel','EEEEFinalSel','EEMMFinalSel','MMEEFinalSel','MMEEFinalSel',MC=False,leadingOnly=leadingOnly)

    addEventSummary(process,leadingOnly,'MMMT','eventSelectionMMMT')
    addEventSummary(process,leadingOnly,'MMTT','eventSelectionMMTT')
    addEventSummary(process,leadingOnly,'MMET','eventSelectionMMET')
    addEventSummary(process,leadingOnly,'MMEM','eventSelectionMMEM')
    addEventSummary(process,leadingOnly,'EEMT','eventSelectionEEMT')
    addEventSummary(process,leadingOnly,'EEET','eventSelectionEEET')
    addEventSummary(process,leadingOnly,'EETT','eventSelectionEETT')
    addEventSummary(process,leadingOnly,'EEEM','eventSelectionEEEM')
