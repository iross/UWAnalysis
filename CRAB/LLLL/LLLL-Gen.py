import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START52_V9::All'

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            #'file:/hdfs/store/user/dbelknap/GluGluToHToZZTo4L_M-125_8TeV-powheg-pythia6/GGH_HZZ4L_M-125_2012-06-20-PatTuple-MC-b497351/4cb1f8ea0bfd28794ef77b00678681f4/output_101_2_67C.root'
            #'file:/hdfs/store/mc/Summer12/ZZTo4L_TuneZ2star_8TeV_pythia6_tauola/AODSIM/PU_S7_START52_V9-v1/0000/FEF7BE48-8A94-E111-A2EA-00266CF9B5D0.root'
            #'file:/hdfs/store/mc/Summer12/GluGluToZZTo4L_8TeV-gg2zz-pythia6/AODSIM/PU_S7_START52_V9-v1/0000/EE103AAA-32B6-E111-892D-008CFA0014EC.root'
            #'file:/hdfs/store/user/iross/GluGluToZZTo2L2L_TuneZ2star_8TeV-gg2zz-pythia6/ggZZ2L2L_2012-07-24-PatTuple-ZZ-samples-4b2f7ef/2203ba93066ddf9759dd540a3ad9da22/output_27_1_T9B.root'
            #'file:/hdfs/store/mc/Summer12/GluGluToZZTo2L2L_TuneZ2star_8TeV-gg2zz-pythia6/AODSIM/PU_S7_START52_V9-v1/0000/D0768C9C-9CB5-E111-9F43-001D0967D2E7.root'
            #'file:/hdfs/store/mc/Fall11/GluGluToZZTo4L_7TeV-gg2zz-pythia6/AODSIM/PU_S6_START42_V14B-v1/0000/A4153103-CBF0-E011-B3C9-001B21670928.root'
            'file:/hdfs/store/mc/Summer12/GluGluToHToZZTo4L_M-125_8TeV-powheg-pythia6/AODSIM/PU_S7_START52_V9-v1/0000/F2181B64-BB95-E111-B3E7-00261894382D.root'
            #'file:/hdfs/store/user/iross/ZZTo4mu_8TeV-powheg-pythia6/ZZ4M_powheg_2012-05-29-8TeV-PatTuple-v2-67c1f94/c8fc7c2ff4112a438286838f75d59cdb/output_137_1_gDw.root'
            #'file:/hdfs/store/user/iross/DoubleMu/data_DoubleMu_Run2012B_PromptReco_v1_a_2012-05-29-8TeV-PatTuple-67c1f94/a7f10efca7dd683ad59c7e946715fa59/output_49_0_TNg.root',
            #		'file:/scratch/iross/zz4l_sync_summer12_EEveto.root',
            #			'file:/scratch/iross/zz4l_sync_fall11_take2.root'
            #            'file:/scratch/iross/zz4l_sync_2.root'
            #		'file:eemm_ZZ4Lfall_50evts.root'
            ),
        inputCommands=cms.untracked.vstring(
            'keep *',
            'drop *_finalState*_*_*',
            'drop *_patFinalStateEvent*_*_*'
            )
        )


# Store all Gen Level particles. For H -> ZZ or ZZ only.
process.genlevel = cms.EDAnalyzer("GenLevelFiller", gensrc = cms.InputTag("genParticles"), isGGZZ = cms.bool(False))
process.genParticles = cms.Path( process.genlevel )

process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
