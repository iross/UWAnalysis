import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V13::All'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)



process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/user/bachtis/Z11-SKIM/1/SKIM-82CAEBE7-36F8-E011-97B5-E0CB4E19F969.root'
        )
)


process.load("PhysicsTools.PatAlgos.patSequences_cff")


from UWAnalysis.Configuration.tools.analysisTools import *
defaultReconstructionMC(process,'HLT',[
'HLT_Ele18_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_MediumIsoPFTau20'
])




#EventSelection
process.load("UWAnalysis.Configuration.zEleTauAnalysis_cff")

process.metCalibration.applyCalibration = cms.bool(True)
process.metCalibration.calibrationScheme = cms.string("Phil_Z")


process.eventSelection = cms.Path(process.selectionSequence)

#Systematic Shifts
process.eventSelectionTauUp    = createSystematics(process,process.selectionSequence,'TauUp',1.00,1.0,1.03,0,1.0)
process.eventSelectionTauDown  = createSystematics(process,process.selectionSequence,'TauDown',1.0,1.0,0.97,0,1.0)
process.eventSelectionMetUp    = createRecoilSystematics(process,process.selectionSequence,'MetUp',1.0,0.0)
process.eventSelectionMetDown  = createRecoilSystematics(process,process.selectionSequence,'MetDown',-1.0,0.0)
process.eventSelectionMetRUp    = createRecoilSystematics(process,process.selectionSequence,'MetRUp',0.0,1.0)
process.eventSelectionMetRDown  = createRecoilSystematics(process,process.selectionSequence,'MetRDown',0.0,-1.0)


from UWAnalysis.Configuration.tools.ntupleTools import addEleTauEventTree

addEleTauEventTree(process,'eleTauEventTree')
addEleTauEventTree(process,'eleTauEventTreeFinal','eleTausOS','osDiElectrons')
addEleTauEventTree(process,'eleTauEventTreeTauUp','eleTausSortedTauUp','osDiElectronsTauUp','eleTracksSortedTauUp','eleGSFTracksSortedTauUp')
addEleTauEventTree(process,'eleTauEventTreeTauDown','eleTausSortedTauDown','osDiElectronsTauDown','eleTracksSortedTauDown','eleGSFTracksSortedTauDown')
addEleTauEventTree(process,'eleTauEventTreeMetUp','eleTausSortedMetUp','osDiElectronsMetUp','eleTracksSortedMetUp','eleGSFTracksSortedMetUp')
addEleTauEventTree(process,'eleTauEventTreeMetDown','eleTausSortedMetDown','osDiElectronsMetDown','eleTracksSortedMetDown','eleGSFTracksSortedMetDown')
addEleTauEventTree(process,'eleTauEventTreeMetRUp','eleTausSortedMetRUp','osDiElectronsMetRUp','eleTracksSortedMetRUp','eleGSFTracksSortedMetRUp')
addEleTauEventTree(process,'eleTauEventTreeMetRDown','eleTausSortedMetRDown','osDiElectronsMetRDown','eleTracksSortedMetRDown','eleGSFTracksSortedMetRDown')



createGeneratedParticles(process,
                         'genTauCands',
                          [
                           "keep pdgId = {tau+} & mother.pdgId()= {Z0}",
                           "keep pdgId = {tau-} & mother.pdgId() = {Z0} "
                          ]
)



createGeneratedParticles(process,
                         'genDaughters',
                          [
                           "keep++ pdgId = {Z0}",
                           "keep pdgId = {tau+}",
                           "keep pdgId = {tau-}",
                           "drop pdgId = {mu+}",
                           "drop pdgId = {mu-}",
                           "keep pdgId = 11",
                           "keep pdgId = -11"
                          ]
)





addEventSummary(process,True)












