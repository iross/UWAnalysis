
import FWCore.ParameterSet.Config as cms
from CommonTools.ParticleFlow.Isolation.tools_cfi import *

from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.tools.helpers import *
from PhysicsTools.PatAlgos.tools.tauTools import *
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.PatAlgos.tools.metTools import *
from PhysicsTools.PatAlgos.tools.pfTools import *
from PhysicsTools.PatAlgos.tools.trigTools import *
from RecoMuon.MuonIsolationProducers.muIsoDepositTk_cfi import *
import RecoMuon.MuonIsolationProducers.muIsoDepositTk_cfi
from RecoMuon.MuonIsolationProducers.muIsoDepositCalByAssociatorTowers_cfi  import *
import RecoMuon.MuonIsolationProducers.muIsoDepositCalByAssociatorTowers_cfi 
from RecoEgamma.EgammaIsolationAlgos.eleIsoDepositTk_cff import *
from RecoEgamma.EgammaIsolationAlgos.eleIsoDepositEcalFromHits_cff import *
from RecoEgamma.EgammaIsolationAlgos.eleIsoDepositHcalFromTowers_cff import *
from Configuration.StandardSequences.GeometryIdeal_cff import *
import sys


def defaultReconstructionSKIM(process):
  process.load("UWAnalysis.Configuration.startUpSequence_cff")
  process.load("Configuration.StandardSequences.Geometry_cff")
  process.load("Configuration.StandardSequences.MagneticField_cff")
  process.load("Configuration.StandardSequences.Services_cff")
  process.load("Configuration.StandardSequences.Reconstruction_cff")
  process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
  process.load("DQMServices.Core.DQM_cfg")
  process.load("DQMServices.Components.DQMEnvironment_cfi")
  process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")

  #make only what you need
  process.patDefaultSequence = cms.Sequence(
    process.makePatElectrons +
    process.makePatMuons     +
    process.makePatTaus      +
    process.patCandidateSummary
  )

  #remove MC matching
  removeMCMatching(process,['All'],"",False)
  #HPS
  switchToPFTauHPS(process)
  #apply particle based isolation
  switchToElePFIsolation(process,'gsfElectrons')
  switchToMuPFIsolation(process,'muons')
#  zzStdIsoMu(process,'muons')
#  zzStdIsoEle(process,'gsfElectrons')
  electronOverloading(process,True,'patElectrons')
  addSkimForDATA(process) 
  process.recoPAT = cms.Sequence(process.ak5PFJets+process.PFTau+process.patDefaultSequence)
  
  runPFNoPileUp(process)



def defaultReconstruction(process,triggerProcess = 'HLT',triggerPaths = ['HLT_Mu9','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v2','HLT_Mu15_v1','HLT_Mu15_v2']):
  #Make PAT
  runRECO(process)
  global TriggerPaths
  TriggerPaths= triggerPaths

  #Use PF Jets
  switchJetCollection(process,cms.InputTag('ak5PFJets'),True,True,('AK5PF',['L1FastJet','L2Relative','L3Absolute','L2L3Residual']),False,cms.InputTag("ak5GenJets"),True,"ak5","","")
  #remove MC matching
  removeMCMatching(process,['All'],"",False)
  #HPS
  switchToPFTauHPS(process)
  addTauDeltaBeta(process,'hpsPFTauProducer')
  #Add PF MET
  addPfMET(process,'')
  #apply particle based isolation
  switchToElePFIsolation(process,'gsfElectrons')
  switchToMuPFIsolation(process,'muons')
#  zzStdIsoMu(process,'muons')
#  zzStdIsoEle(process,'gsfElectrons')
  #Add PAT Trigger
  switchOnTrigger( process,'patTrigger','patTriggerEvent','patDefaultSequence',triggerProcess,'') 
  muonTriggerMatch(process,triggerProcess)
  electronTriggerMatch(process,triggerProcess)
  tauTriggerMatch(process,triggerProcess)

  #Muon Overloading
  muonOverloading(process,'triggeredPatMuons')
  tauOverloading(process,'triggeredPatTaus')
  jetOverloading(process)
  electronOverloading(process,True,'triggeredPatElectrons')

  #Add the tracks
  addTrackCandidates(process)

  #addSuperClusters
  addSuperClusterCandidates(process)

  #add GOODCOLL criteria
  addSkimForDATA(process)

  #Apply default selections
  applyDefaultSelections(process)

  #Run FastJet 
  runRho(process)
  runPFNoPileUp(process)

#  addCustomJEC(process)

  process.patJetCorrFactors.useRho = True

  
def defaultReconstructionMC(process,triggerProcess = 'HLT',triggerPaths = ['HLT_Mu9'],calibrateMET = False,calibrationScheme = "BothLegs"):
  #Make PAT
  runRECO(process)


  global TriggerPaths
  TriggerPaths= triggerPaths


  #Use PF Jets
  switchJetCollection(process,cms.InputTag('ak5PFJets'),True,True,('AK5PF',['L1FastJet','L2Relative','L3Absolute']),False,cms.InputTag("ak5GenJets"),True,"ak5","","")

  #make HPS Tau ID
  switchToPFTauHPS(process)
  addTauDeltaBeta(process,'hpsPFTauProducer')

  #Add PF MET
  addPfMET(process,'')

  #apply particle based isolation
  switchToElePFIsolation(process,'gsfElectrons')
  switchToMuPFIsolation(process,'muons')
#  zzStdIsoMu(process,'muons')
#  zzStdIsoEle(process,'gsfElectrons')
  #Add PAT Trigger
  switchOnTrigger( process,'patTrigger','patTriggerEvent','patDefaultSequence',triggerProcess,'') 
  muonTriggerMatch(process,triggerProcess)
  electronTriggerMatch(process,triggerProcess)
  tauTriggerMatch(process,triggerProcess)


  #Add the IP etc of the muon
  muonOverloading(process,'triggeredPatMuons')
  tauOverloading(process,'triggeredPatTaus')
  electronOverloading(process,False,'triggeredPatElectrons')
  jetOverloading(process)

  #Add the tracks
  addTrackCandidates(process)
  #addSuperClusters
  addSuperClusterCandidates(process)

  addSkimForDATA(process)
  applyDefaultSelections(process)


  #Run FastJet subtraction
  runRho(process)
  runPFNoPileUp(process)


#  addCustomJEC(process)
  process.patJetCorrFactors.useRho = True





def applyDefaultSelections(process):
  #DONT CHANGE THOSE HERE THEY ARE NOT USED FOR YOUR SELECTIONS!!!
  #ONLY FOR SYSTEMATICS . PLEASE CHANGE THEM in YOUR CFG FILE IF REALLY NEEDED

  #require jet selection over 15 GeV
  process.selectedPatJets.cut =  cms.string("abs(eta)<5.0&&pt>10&&neutralHadronEnergyFraction<0.99&&neutralEmEnergyFraction<0.99&nConstituents>1&&((abs(eta)>2.4)||(abs(eta)<2.4&&chargedHadronEnergyFraction>0&&chargedMultiplicity>0&&chargedEmEnergyFraction<0.99))")
  #require muon selection
  process.selectedPatMuons.cut =  cms.string("pt>10&&isGlobalMuon&&(chargedHadronIso()+max(photonIso+neutralHadronIso()-userIso(0),0.0))/pt()<0.3")
  #require electron selection
  process.selectedPatElectrons.cut =  cms.string('pt>10&&userFloat("wp95")>0&&(chargedHadronIso()+photonIso()+neutralHadronIso())/pt()<0.3')
  #require tau selection
  process.selectedPatTaus.cut =cms.string('pt>15&&tauID("decayModeFinding")&&tauID("byLooseIsolation")')




def runRECO(process):
  process.load("UWAnalysis.Configuration.startUpSequence_cff")
  process.load("Configuration.StandardSequences.Geometry_cff")
  process.load("Configuration.StandardSequences.MagneticField_cff")
  process.load("Configuration.StandardSequences.Services_cff")
  process.load("Configuration.StandardSequences.Reconstruction_cff")
  process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
  process.load("DQMServices.Core.DQM_cfg")
  process.load("DQMServices.Components.DQMEnvironment_cfi")
  process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")


  process.recoPAT = cms.Path(process.PFTau+process.patElectronId+process.patDefaultSequence)

def runRho(process):
  #Run the rho correction only for neutrals
#  process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
  process.load('RecoJets.Configuration.RecoPFJets_cff')
  import RecoJets.JetProducers.kt4PFJets_cfi
  process.kt6corPFJets=RecoJets.JetProducers.kt4PFJets_cfi.kt4PFJets.clone()
  process.kt6corPFJets.rParam = cms.double(0.6)
  process.kt6corPFJets.doRhoFastjet = cms.bool(True) 
  process.kt6corPFJets.Rho_EtaMax = cms.double(2.5)
  process.kt6corPFJets.Ghost_EtaMax = cms.double(2.5)
  process.kt6PFJets.doRhoFastjet = True
  process.ak5PFJets.doAreaFastjet = True

  process.rhoSeq = cms.Sequence(process.kt6PFJets+process.ak5PFJets+process.kt6corPFJets)
  process.patJSeq = process.patDefaultSequence
  process.patDefaultSequence = cms.Sequence(process.rhoSeq+process.patJSeq)

def addCustomJEC(process):
  process.load("CondCore.DBCommon.CondDBCommon_cfi")
  process.jec = cms.ESSource("PoolDBESSource",
      DBParameters = cms.PSet(
      messageLevel = cms.untracked.int32(0)
        ),
      timetype = cms.string('runnumber'),
      toGet = cms.VPSet(
      cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec11V2_AK5PF'),
            label  = cms.untracked.string('AK5PF')
            ),
      cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec11V2_AK5Calo'),
            label  = cms.untracked.string('AK5Calo')
            )
      ),
      ## here you add as many jet types as you need (AK5PFchs, AK5Calo, AK5JPT, AK7PF, AK7Calo, KT4PF, KT4Calo)
      connect = cms.string('sqlite:Jec11V2.db')
  )
  # Add an es_prefer statement to get your new JEC constants from the sqlite file, rather than from the global tag
  process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')



def addTrigger(process,triggerProcess):
   process.patTrigger = cms.EDProducer( "PATTriggerProducer",
                                    processName    = cms.string(triggerProcess),
                                    )

   process.patDefaultSequence += process.patTrigger



def muonTriggerMatch(process,triggerProcess):

   process.triggeredPatMuons = cms.EDProducer("MuonTriggerMatcher",
                                            src = cms.InputTag("patMuons"),
                                            trigEvent = cms.InputTag("hltTriggerSummaryAOD"),
                                            filters = cms.VInputTag(
                                                cms.InputTag('hltSingleMuIsoL3IsoFiltered12','',triggerProcess),
                                                cms.InputTag('hltSingleMuIsoL3IsoFiltered15','',triggerProcess),
                                                cms.InputTag('hltSingleMuIsoL3IsoFiltered24','',triggerProcess),
                                                cms.InputTag('hltDiMuonL3PreFiltered8','',triggerProcess),
                                                cms.InputTag('hltDiMuonL3PreFiltered7','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoMu15IsoPFTau15','',triggerProcess),
                                                cms.InputTag('hltL1Mu3EG5L3Filtered17','',triggerProcess),
                                                cms.InputTag('hltL1MuOpenEG5L3Filtered8','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoMu12IsoPFTau10','',triggerProcess),
                                                cms.InputTag('hltSingleMuIsoL3IsoFiltered17','',triggerProcess),
                                                cms.InputTag('hltSingleMuL2QualIsoL3IsoFiltered17','',triggerProcess),
                                                cms.InputTag('hltSingleMuL2QualIsoL3IsoFiltered24','',triggerProcess),                                                
                                                cms.InputTag('hltSingleMu13L3Filtered13','',triggerProcess),
                                                cms.InputTag('hltSingleMuIsoL1s14L3IsoFiltered15eta2p1',"",triggerProcess)
                                            ),
                                            pdgId = cms.int32(13)
  )

   process.patDefaultSequence=cms.Sequence(process.patDefaultSequence*process.triggeredPatMuons)
   




def electronTriggerMatch(process,triggerProcess):

   process.triggeredPatElectronsL = cms.EDProducer("ElectronTriggerMatcher",
                                            src = cms.InputTag("patElectrons"),
                                            trigEvent = cms.InputTag("hltTriggerSummaryAOD"),
                                            filters = cms.VInputTag(
                                                cms.InputTag('hltEle17CaloIdLCaloIsoVLPixelMatchFilterDoubleEG125','',triggerProcess),
                                                cms.InputTag('hltEle17CaloIdIsoEle8CaloIdIsoPixelMatchDoubleFilter','',triggerProcess),
                                                cms.InputTag('hltEle17CaloIdLCaloIsoVLPixelMatchFilter','',triggerProcess),
                                                cms.InputTag('hltEle8CaloIdLCaloIsoVLPixelMatchFilter','',triggerProcess)
                                                
                                            ),
                                            pdgId = cms.int32(0)
  )
   process.triggeredPatElectrons = cms.EDProducer("ElectronTriggerMatcher",
                                            src = cms.InputTag("triggeredPatElectronsL"),
                                            trigEvent = cms.InputTag("hltTriggerSummaryAOD"),
                                            filters = cms.VInputTag(
                                                cms.InputTag('hltEle15CaloIdVTTrkIdTCaloIsoTTrkIsoTTrackIsolFilter','',triggerProcess),
                                                cms.InputTag('hltEle15CaloIdVTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter','',triggerProcess),
                                                cms.InputTag('hltEle18CaloIdVTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoEle15IsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoEle15TightIsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoEle18MediumIsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','',triggerProcess),
                                                cms.InputTag('hltEle32CaloIdTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter','',triggerProcess),
                                                cms.InputTag('hltL1NonIsoHLTNonIsoMu17Ele8PixelMatchFilter','',triggerProcess),
                                                cms.InputTag('hltL1NonIsoHLTNonIsoMu8Ele17PixelMatchFilter','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoEle18TightIsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoEle18IsoPFTau20','',triggerProcess)
                                            ),
                                            pdgId = cms.int32(11)
  )
  


   process.patDefaultSequence=cms.Sequence(process.patDefaultSequence*process.triggeredPatElectronsL*process.triggeredPatElectrons)



def tauTriggerMatch(process,triggerProcess):
   strTrig=''
   for i in TriggerPaths:
    if i==TriggerPaths[0]:
      strTrig+='path(\"'+i+'\")'
    else:  
      strTrig+='|| path(\"'+i+'\")'


   #Match With The triggers
   process.preTriggeredPatTaus = cms.EDProducer("TauTriggerMatcher",
                                            src = cms.InputTag("patTaus"),
                                            trigEvent = cms.InputTag("hltTriggerSummaryAOD"),
                                            filters = cms.VInputTag(
                                                cms.InputTag('hltFilterDoubleIsoPFTau20Trk5LeadTrack5IsolationL1HLTMatched','',triggerProcess),
                                                cms.InputTag('hltFilterDoubleIsoPFTau35Trk5LeadTrack5IsolationL1HLTMatched','',triggerProcess)
                                            ),
                                            pdgId = cms.int32(0)
  )

   process.triggeredPatTaus = cms.EDProducer("TauTriggerMatcher",
                                            src = cms.InputTag("preTriggeredPatTaus"),
                                            trigEvent = cms.InputTag("hltTriggerSummaryAOD"),
                                            filters = cms.VInputTag(
                                                cms.InputTag('hltOverlapFilterIsoMu15IsoPFTau15','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoMu15IsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoMu15MediumIsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoMu15TightIsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterMu15IsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoMu12IsoPFTau10','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoMu15IsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoEle15IsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoEle15IsoPFTau15','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoEle15TightIsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltOverlapFilterIsoEle18MediumIsoPFTau20','',triggerProcess),
                                                cms.InputTag('hltFilterDoubleIsoPFTau20Trk5LeadTrack5IsolationL1HLTMatched','',triggerProcess)
                                            ),

                                            pdgId = cms.int32(15)
  )
                                            


   process.patDefaultSequence=cms.Sequence(process.patDefaultSequence*process.preTriggeredPatTaus*process.triggeredPatTaus)




def tauOverloading(process,src):


  process.patRhoTau = cms.EDProducer("TauRhoOverloader", 
                                          src = cms.InputTag(src),
                                          srcRho = cms.InputTag("kt6corPFJets","rho")
  )
  process.patOverloadedTaus = cms.EDProducer('PATTauOverloader',
                                        src = cms.InputTag("patRhoTau")
  )                                        

  process.tauOverloading = cms.Sequence(process.patRhoTau+process.patOverloadedTaus)
  process.patDefaultSequence*=process.tauOverloading


def jetOverloading(process,src = "selectedPatJets"):



  process.patOverloadedJets = cms.EDProducer('PATJetOverloader',
                                        src = cms.InputTag(src)
  )                                        

  process.jetOverloading = cms.Sequence(process.patOverloadedJets)
  process.patDefaultSequence*=process.jetOverloading



def electronOverloading(process,isdata,src):

  process.patElectrons.addElectronID     = cms.bool( True )
  
  ##Add CIC Electron ID
  process.load("RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_DataTuning_cfi")
  process.CICID = cms.Sequence(
	process.eidVeryLoose+
	process.eidLoose+
	process.eidMedium+
	process.eidTight+
	process.eidSuperTight+
	process.eidHyperTight1+
	process.eidHyperTight2+
	process.eidHyperTight3+
	process.eidHyperTight4
	)

  process.patElectrons.electronIDSources = cms.PSet(
	cicVeryLoose = cms.InputTag("eidVeryLoose"),
	cicLoose = cms.InputTag("eidLoose"),
	cicMedium = cms.InputTag("eidMedium"),
	cicTight = cms.InputTag("eidTight"),
	cicSuperTight = cms.InputTag("eidSuperTight"),
	cicHyperTight1 = cms.InputTag("eidHyperTight1"),
	cicHyperTight2 = cms.InputTag("eidHyperTight2"),
	cicHyperTight3 = cms.InputTag("eidHyperTight3"),
	cicHyperTight4 = cms.InputTag("eidHyperTight4")
	)
  process.electronsWP80 = cms.EDProducer('PATVBTFElectronEmbedder',
                                             src             = cms.InputTag(src),
                                             sigmaEtaEta     = cms.vdouble(0.01,0.03),
                                             deltaEta        = cms.vdouble(0.004,0.007),
                                             deltaPhi        = cms.vdouble(0.06,0.03),
                                             hoE             = cms.vdouble(0.04,0.025),
                                             id              = cms.string("wp80")

  )                                             

  process.electronsWP90 = cms.EDProducer('PATVBTFElectronEmbedder',
                                             src             = cms.InputTag("electronsWP80"),
                                             sigmaEtaEta     = cms.vdouble(0.01,0.03),
                                             deltaEta        = cms.vdouble(0.007,0.009),
                                             deltaPhi        = cms.vdouble(0.8,0.7),
                                             hoE             = cms.vdouble(0.12,0.05),
                                             id              = cms.string("wp90")
  )   
  
  process.electronsWP95 = cms.EDProducer('PATVBTFElectronEmbedder',
                                             src             = cms.InputTag("electronsWP90"),
                                             sigmaEtaEta     = cms.vdouble(0.01,0.03),
                                             deltaEta        = cms.vdouble(0.007,0.01),
                                             deltaPhi        = cms.vdouble(0.8,0.7),
                                             hoE             = cms.vdouble(0.15,0.07),
                                             id              = cms.string("wp95")
  )                                             


  process.patRhoElectron = cms.EDProducer("ElectronRhoOverloader", 
                                          src = cms.InputTag("electronsWP95"),
                                          srcRho = cms.InputTag("kt6corPFJets","rho")
  )


  process.convRejElectrons = cms.EDProducer('PATWWElectronEmbedder',
                                             src             = cms.InputTag("patRhoElectron"),
                                             srcVertices     = cms.InputTag("primaryVertexFilter"),
                                             sigmaEtaEta     = cms.vdouble(0.01,0.03,0.01,0.03),
                                             deltaEta        = cms.vdouble(0.004,0.005,0.004,0.007),
                                             deltaPhi        = cms.vdouble(0.03,0.02,0.06,0.03),
                                             hoE             = cms.vdouble(0.025,0.025,0.04,0.025),
                                             convDist        = cms.vdouble(0.02,0.02,0.02,0.02),
                                             convDCot        = cms.vdouble(0.02,0.02,0.02,0.02),
                                             id              = cms.string("WWID"),
                                             fbrem           = cms.double(0.15),
                                             EOP             = cms.double(0.95),
                                             d0              = cms.double(0.045),
                                             dz              = cms.double(0.2),
                                             )        

  process.electronOverloading=cms.Sequence(process.electronsWP80+process.electronsWP90+process.electronsWP95+process.patRhoElectron+process.convRejElectrons)
  process.postElectronSequence=process.patDefaultSequence
  process.patDefaultSequence = cms.Sequence(process.CICID*process.postElectronSequence*process.electronOverloading)

def muonOverloading(process,src):
  #create the impact parameter

  process.patPFMuonMatch = cms.EDProducer("PATPFMuonEmbedder", #Saves the case where muon is matched to a PF Muon
                                          src = cms.InputTag(src),
                                          ref = cms.InputTag("pfAllMuons")
   )

  process.patZZMuonMatch = cms.EDProducer("PATZZMuonEmbedder", #Saves the case where muon is matched to a PF Muon
                                          src = cms.InputTag("patPFMuonMatch"),
                                          maxChi2=cms.double(10.),
                                          minTrackerHits=cms.int32(10),
                                          minMuonHits = cms.int32(1),
                                          minMatches  = cms.int32(2)
 
   )
  process.patVBTFMuonMatch = cms.EDProducer("PATVBTFMuonEmbedder", #Saves the case where muon is matched to a PF Muon
                                          src = cms.InputTag("patZZMuonMatch"),
                                          maxDxDy=cms.double(0.2),
                                          maxChi2=cms.double(10.),
                                          minTrackerHits=cms.int32(10),
                                          minPixelHits=cms.int32(1),
                                          minMuonHits = cms.int32(1),
                                          minMatches  = cms.int32(2),
                                          maxResol      = cms.double(0.1)
 
   )

  process.patWWMuonMatch = cms.EDProducer("PATWWMuonEmbedder", #Saves the case where muon is matched to a PF Muon
                                          src = cms.InputTag("patVBTFMuonMatch"),
                                          srcVertices = cms.InputTag("primaryVertexFilter"),
                                          maxDxDy=cms.double(0.045),####REMOVED IP CUT
                                          maxChi2=cms.double(10.),
                                          minTrackerHits=cms.int32(10),
                                          minPixelHits=cms.int32(1),
                                          minMuonHits = cms.int32(1),
                                          minMatches  = cms.int32(2),
                                          maxResol      = cms.double(0.1),
                                          dz            = cms.double(0.2)
    )

  process.patMuonsForAnalysis = cms.EDProducer("MuonRhoOverloader", 
                                          src = cms.InputTag("patWWMuonMatch"),
                                          srcRho = cms.InputTag("kt6corPFJets","rho")
  )
  
  process.patDefaultSequence = cms.Sequence(process.patDefaultSequence*process.patPFMuonMatch*process.patZZMuonMatch*process.patVBTFMuonMatch*process.patWWMuonMatch*process.patMuonsForAnalysis)
   

def runPFNoPileUp(process):
  process.load("CommonTools.ParticleFlow.ParticleSelectors.pfCandsForIsolation_cff")
  process.pfPileUpCandidates = cms.EDProducer(
    "TPPFCandidatesOnPFCandidates",
    enable =  cms.bool( True ),
    verbose = cms.untracked.bool( False ),
    name = cms.untracked.string("pileUpCandidates"),
    topCollection = cms.InputTag("pfNoPileUp"),
    bottomCollection = cms.InputTag("particleFlow"),
    )



  #enable PF no Pile Up
  process.pfPileUp.Enable = cms.bool(True)

  #Put all charged particles in charged hadron collection(electrons and muons)
  process.pfAllChargedHadrons.pdgId = cms.vint32(211,-211,321,-321,999211,2212,-2212,11,-11,13,-13)

  process.pileUpHadrons = cms.EDFilter("PdgIdPFCandidateSelector",
                                         src = cms.InputTag("pfPileUpCandidates"),
                                         pdgId = cms.vint32(211,-211,321,-321,999211,2212,-2212,11,-11,13,-13)
                                     )
  process.pfAllNeutrals = cms.EDFilter("PdgIdPFCandidateSelector",
                                       src = cms.InputTag("pfNoPileUp"),
                                       pdgId = cms.vint32(111,130,310,2112,22)
                                   )



  process.pfAllElectrons.src = cms.InputTag("pfNoPileUp")

  process.pfAllMuons = cms.EDFilter("PdgIdPFCandidateSelector",
                                         src = cms.InputTag("pfNoPileUp"),
                                         pdgId = cms.vint32(13,-13)
                                     )


  process.pfPostSequence = cms.Sequence(
    process.pfCandsForIsolationSequence+
    process.pfAllMuons+
    process.pfPileUpCandidates+
    process.pileUpHadrons+
    process.pfAllNeutrals
  )      


  process.patPreIsoSeq = process.pfPostSequence
  process.patDefaultSequence = cms.Sequence(process.patPreIsoSeq*process.patDefaultSequence)


def switchToMuPFIsolation(process,muons):

  ###Muon Isolation

  process.muPFIsoDepositAll     = isoDepositReplace(muons,cms.InputTag("pfNoPileUp"))
  process.muPFIsoDepositCharged = isoDepositReplace(muons,"pfAllChargedHadrons")
  process.muPFIsoDepositNeutral = isoDepositReplace(muons,"pfAllNeutralHadrons")
  process.muPFIsoDepositGamma = isoDepositReplace(muons,"pfAllPhotons")


  #Isodeposit from PileUp- For Vertex subtraction!!!!
  process.muPFIsoDepositPU = isoDepositReplace(muons,cms.InputTag("pileUpHadrons"))
  

  process.muPFIsoDeposits = cms.Sequence(
      process.muPFIsoDepositAll*
      process.muPFIsoDepositCharged*
      process.muPFIsoDepositPU*
      process.muPFIsoDepositNeutral*
      process.muPFIsoDepositGamma
  )

  
  #And Values
  process.muPFIsoValueAll = cms.EDProducer("CandIsolatorFromDeposits",
       deposits = cms.VPSet(
          cms.PSet(
          src = cms.InputTag("muPFIsoDepositAll"),
          deltaR = cms.double(0.4),
          weight = cms.string('1'),
          vetos = cms.vstring('0.001','Threshold(0.5)'),
          skipDefaultVeto = cms.bool(True),
          mode = cms.string('sum')
        )
      )
  )

  process.muPFIsoValueCharged = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
             src = cms.InputTag("muPFIsoDepositCharged"),
             deltaR = cms.double(0.4),
             weight = cms.string('1'),
             vetos = cms.vstring('0.0001','Threshold(0.0)'),
             skipDefaultVeto = cms.bool(True),
             mode = cms.string('sum')
         ) 
     )
 )

  process.muPFIsoValueNeutral = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
            src = cms.InputTag("muPFIsoDepositNeutral"),
            deltaR = cms.double(0.4),
            weight = cms.string('1'),
            vetos = cms.vstring('0.01','Threshold(0.5)'),
            skipDefaultVeto = cms.bool(True),
            mode = cms.string('sum')
        )
    )
  )

  process.muPFIsoValueGamma = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
             src = cms.InputTag("muPFIsoDepositGamma"),
             deltaR = cms.double(0.4),
             weight = cms.string('1'),
             vetos = cms.vstring('0.01','Threshold(0.5)'),
              skipDefaultVeto = cms.bool(True),
              mode = cms.string('sum')
         ) 
     )
  )

  process.muPFIsoValuePU = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
             src = cms.InputTag("muPFIsoDepositPU"),
             deltaR = cms.double(0.4),
             weight = cms.string('1'),
             vetos = cms.vstring('0.0001','Threshold(0.5)'),
             skipDefaultVeto = cms.bool(True),
             mode = cms.string('sum')
         ) 
     )
 )

  process.muPFIsoValuePULow = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
             src = cms.InputTag("muPFIsoDepositPU"),
             deltaR = cms.double(0.4),
             weight = cms.string('1'),
             vetos = cms.vstring('0.0001','Threshold(0.0)'),
             skipDefaultVeto = cms.bool(True),
             mode = cms.string('sum')
         ) 
     )
 )



  process.muPFIsoValues =  cms.Sequence( process.muPFIsoValueAll
                               * process.muPFIsoValueCharged
                               * process.muPFIsoValueNeutral
                               * process.muPFIsoValueGamma
                               * process.muPFIsoValuePU
                               * process.muPFIsoValuePULow
  )

  process.muisolationPrePat = cms.Sequence(
      process.muPFIsoDeposits*
      process.muPFIsoValues
  )

  process.patMuons.isoDeposits = cms.PSet(
        particle         = cms.InputTag("muPFIsoDepositAll"),
        pfChargedHadrons = cms.InputTag("muPFIsoDepositCharged"),
        pfNeutralHadrons = cms.InputTag("muPFIsoDepositNeutral"),
        pfPhotons        = cms.InputTag("muPFIsoDepositGamma")
  )

  #H->ZZ->4l analysis -- StdIso
  process.muIsoDepositTkNew=RecoMuon.MuonIsolationProducers.muIsoDepositTk_cfi.muIsoDepositTk.clone()
  process.muIsoDepositTkNew.IOPSet.inputMuonCollection = cms.InputTag(muons)

  process.muIsoDepositCalByAssociatorTowersNew=RecoMuon.MuonIsolationProducers.muIsoDepositCalByAssociatorTowers_cfi.muIsoDepositCalByAssociatorTowers.clone()
  process.muIsoDepositCalByAssociatorTowersNew.IOPSet.inputMuonCollection = cms.InputTag(muons)

  process.vetoMuons =  cms.EDFilter("MuonRefSelector",
          src = cms.InputTag("muons"),
          cut = cms.string("isGlobalMuon && pt>5")
          )
  process.vetoElectrons =  cms.EDFilter("GsfElectronRefSelector",
          src = cms.InputTag("gsfElectrons"),
          cut = cms.string("pt>5 ")
          )

  process.muIsoFromDepsTkOptimized = cms.EDProducer("CandIsolatorFromDeposits",
          deposits = cms.VPSet(cms.PSet(
              mode = cms.string('sum'),
              src = cms.InputTag("muIsoDepositTkNew"),
              weight = cms.string('1'),
              deltaR = cms.double(0.3),
              vetos = cms.vstring(
                  'vetoMuons:0.015',
                  'vetoElectrons:0.015',
                  'Threshold(1.0)'),
              skipDefaultVeto = cms.bool(True))
              )
          )

  process.muIsoFromDepsEcalOptimized = cms.EDProducer("CandIsolatorFromDeposits",
          deposits = cms.VPSet(cms.PSet(
              mode = cms.string('sum'),
              src = cms.InputTag("muIsoDepositCalByAssociatorTowers","ecal"),
              weight = cms.string('1'),
              deltaR = cms.double(0.3),
              vetos = cms.vstring('vetoMuons:0.015',
                  'vetoElectrons:0.015',
#                  'Threshold(1.0)'),
				),
              skipDefaultVeto = cms.bool(True)
              ))
          )

  process.muIsoFromDepsHcalOptimized = cms.EDProducer("CandIsolatorFromDeposits",
          deposits = cms.VPSet(cms.PSet(
              mode = cms.string('sum'),
              src = cms.InputTag("muIsoDepositCalByAssociatorTowersNew","hcal"),
              weight = cms.string('1'),
              deltaR = cms.double(0.3),
              vetos = cms.vstring('vetoMuons:0.015',
                  'vetoElectrons:0.015',
#                  'Threshold(1.0)'),
				),
              skipDefaultVeto = cms.bool(True)
              ))
          )

  process.patMuons.isolationValues = cms.PSet(
            particle         = cms.InputTag("muPFIsoValueAll"),
            pfChargedHadrons = cms.InputTag("muPFIsoValueCharged"),
            pfNeutralHadrons = cms.InputTag("muPFIsoValueNeutral"),
            pfPhotons        = cms.InputTag("muPFIsoValueGamma"),
            user = cms.VInputTag(
                         cms.InputTag("muPFIsoValuePU"),
                         cms.InputTag("muIsoFromDepsEcalOptimized"),
                         cms.InputTag("muIsoFromDepsHcalOptimized"),
                         cms.InputTag("muIsoFromDepsTkOptimized")
                         )

            )

  process.muStdIso = cms.Sequence(process.vetoElectrons+process.vetoMuons+process.muIsoDepositTkNew+process.muIsoFromDepsTkOptimized+process.muIsoDepositCalByAssociatorTowersNew+process.muIsoFromDepsEcalOptimized+process.muIsoFromDepsHcalOptimized)	

  process.patSeq = process.patDefaultSequence
  process.patDefaultSequence = cms.Sequence(process.muisolationPrePat*process.muStdIso*process.patSeq)

def addTauDeltaBeta(process,taus):

  ###Muon Isolation

  #Isodeposit from PileUp- For Vertex subtraction!!!!
  process.tauPFIsoDepositPU = isoDepositReplace(taus,cms.InputTag("pileUpHadrons"))
  
  process.tauPFIsoDeposits = cms.Sequence(
      process.tauPFIsoDepositPU
  )

  process.tauPFIsoValuePU = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
             src = cms.InputTag("tauPFIsoDepositPU"),
             deltaR = cms.double(0.5),
             weight = cms.string('1'),
             vetos = cms.vstring('0.0001','Threshold(0.5)'),
             skipDefaultVeto = cms.bool(True),
             mode = cms.string('sum')
         ) 
     )
 )

  process.tauPFIsoValues =  cms.Sequence(
    process.tauPFIsoValuePU
  )

  process.tauisolationPrePat = cms.Sequence(
      process.tauPFIsoDeposits*
      process.tauPFIsoValues
  )




  process.patTaus.isolationValues = cms.PSet(
             particle         = cms.InputTag("tauPFIsoValuePU")
#            pfChargedHadrons = cms.InputTag("muPFIsoValueCharged"),
#            pfNeutralHadrons = cms.InputTag("muPFIsoValueNeutral"),
#            pfPhotons        = cms.InputTag("muPFIsoValueGamma"),
           )

  process.patSeqq = process.patDefaultSequence
  process.patDefaultSequence = cms.Sequence(process.tauisolationPrePat*process.patSeqq)


def switchToElePFIsolation(process,electrons):
  ###Electron Isolation

  process.elePFIsoDepositAll     = isoDepositReplace(electrons,cms.InputTag("pfNoPileUp"))
  process.elePFIsoDepositCharged = isoDepositReplace(electrons,"pfAllChargedHadrons")
  process.elePFIsoDepositNeutral = isoDepositReplace(electrons,"pfAllNeutralHadrons")
  process.elePFIsoDepositGamma = isoDepositReplace(electrons,"pfAllPhotons")
  process.elePFIsoDepositPU = isoDepositReplace(electrons,cms.InputTag("pileUpHadrons"))


  process.elePFIsoDeposits = cms.Sequence(
      process.elePFIsoDepositAll*
      process.elePFIsoDepositCharged*
      process.elePFIsoDepositNeutral*
      process.elePFIsoDepositGamma*
      process.elePFIsoDepositPU
  )

  
  #And Values
  process.elePFIsoValueAll = cms.EDProducer("CandIsolatorFromDeposits",
       deposits = cms.VPSet(
          cms.PSet(
          src = cms.InputTag("elePFIsoDepositAll"),
          deltaR = cms.double(0.4),
          weight = cms.string('1'),
          vetos = cms.vstring('0.03','Threshold(1.0)'),
          skipDefaultVeto = cms.bool(True),
          mode = cms.string('sum')
        )
      )
  )

  
  process.elePFIsoValueCharged = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
             src = cms.InputTag("elePFIsoDepositCharged"),
             deltaR = cms.double(0.4),
             weight = cms.string('1'),
             vetos = cms.vstring('0.03','Threshold(0.0)'),
             skipDefaultVeto = cms.bool(True),
             mode = cms.string('sum')
         ) 
     )
 )


  process.elePFIsoValueNeutral = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
            src = cms.InputTag("elePFIsoDepositNeutral"),
            deltaR = cms.double(0.4),
            weight = cms.string('1'),
            vetos = cms.vstring('0.08','Threshold(0.5)'),
            skipDefaultVeto = cms.bool(True),
            mode = cms.string('sum')
        )
    )
  )

  process.elePFIsoValueGamma = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
             src = cms.InputTag("elePFIsoDepositGamma"),
             deltaR = cms.double(0.4),
             weight = cms.string('1'),
             vetos = cms.vstring('0.05','Threshold(0.5)'),
             skipDefaultVeto = cms.bool(True),
             mode = cms.string('sum')
         ) 
     )
  )

  process.elePFIsoValuePU = cms.EDProducer("CandIsolatorFromDeposits",
     deposits = cms.VPSet(
         cms.PSet(
             src = cms.InputTag("elePFIsoDepositPU"),
             deltaR = cms.double(0.4),
             weight = cms.string('1'),
             vetos = cms.vstring('0.0','Threshold(0.5)'),
             skipDefaultVeto = cms.bool(True),
             mode = cms.string('sum')
         ) 
     )
  )




  process.elePFIsoValues =  cms.Sequence( process.elePFIsoValueAll
                               * process.elePFIsoValueCharged
                               * process.elePFIsoValueNeutral
                               * process.elePFIsoValueGamma
                               * process.elePFIsoValuePU
  )

  process.eleisolationPrePat = cms.Sequence(
	  process.elePFIsoDeposits*
      process.elePFIsoValues
  )


#
#KLUDGE : Since PAT electron does not support custom iso deposits 
#put the pileup in the place of all candidates
#

  process.patElectrons.isoDeposits = cms.PSet(
        pfAllParticles   = cms.InputTag("elePFIsoDepositAll"),
        pfChargedHadrons = cms.InputTag("elePFIsoDepositCharged"),
        pfNeutralHadrons = cms.InputTag("elePFIsoDepositNeutral"),
        pfPhotons        = cms.InputTag("elePFIsoDepositGamma")
  )

  process.eleIsoDepositTk.src = electrons
  process.eleIsoDepositEcalFromHits.ExtractorPSet.barrelEcalHits = cms.InputTag("reducedEcalRecHitsEB","")
  process.eleIsoDepositEcalFromHits.ExtractorPSet.endcapEcalHits = cms.InputTag("reducedEcalRecHitsEE","")
  process.eleIsoDepositEcalFromHits.src = electrons
  process.eleIsoDepositHcalFromTowers.src = electrons

  process.vetoMuons =  cms.EDFilter("MuonRefSelector",
          src = cms.InputTag("muons"),
          cut = cms.string("isGlobalMuon && pt>5")
          )
  process.vetoElectrons =  cms.EDFilter("GsfElectronRefSelector",
          src = cms.InputTag("gsfElectrons"),
          cut = cms.string("pt>5 ")
          )

  process.eleIsoFromDepsTkOptimized = cms.EDProducer("CandIsolatorFromDeposits",
          deposits = cms.VPSet(cms.PSet(
              mode = cms.string('sum'),
              src = cms.InputTag("eleIsoDepositTk"),
              weight = cms.string('1'),
              deltaR = cms.double(0.3),
              vetos = cms.vstring(
                  'vetoMuons:0.015',
                  'vetoElectrons:RectangularEtaPhiVeto(-0.015,0.015,-0.5,0.5)',
                  'RectangularEtaPhiVeto(-0.015,0.015,-0.5,0.5)',
                  'Threshold(0.7)'),
              skipDefaultVeto = cms.bool(True) 
              ))
          )

  process.eleIsoFromDepsEcalFromHitsByCrystalOptimized = cms.EDProducer("CandIsolatorFromDeposits",
          deposits = cms.VPSet(cms.PSet(
              mode = cms.string('sum'),
              src = cms.InputTag("eleIsoDepositEcalFromHits"),
              weight = cms.string('1'),
              deltaR = cms.double(0.3),
              vetos = cms.vstring('NumCrystalVeto(3.0)',
                  'EcalBarrel:NumCrystalEtaPhiVeto(1.0,9999.0)',
                  'EcalEndcaps:NumCrystalEtaPhiVeto(1.5,9999.0)',
                  'EcalBarrel:AbsThresholdFromTransverse(0.08)',
                  'EcalEndcaps:AbsThreshold(0.20)',
                  'vetoMuons:0.05',
                  'vetoElectrons:NumCrystalVeto(3.0)',
                  'vetoElectrons:NumCrystalEtaPhiVeto(1.5,15.0)'),
              skipDefaultVeto = cms.bool(True)
              ))
          )

  process.eleIsoFromDepsHcalFromTowersOptimized = cms.EDProducer("CandIsolatorFromDeposits",
          deposits = cms.VPSet(cms.PSet(
              src = cms.InputTag("eleIsoDepositHcalFromTowers"),
              deltaR = cms.double(0.3),
              weight = cms.string('1'),
              vetos = cms.vstring('0.15', 'vetoMuons:0.05'),
              skipDefaultVeto = cms.bool(True),
              mode = cms.string('sum')
              ))
          ) 

###KLUDGE -> Add DB, std iso values in UserIso
  process.patElectrons.isolationValues = cms.PSet(
            pfAllParticles   = cms.InputTag("elePFIsoValuePU"),
            pfChargedHadrons = cms.InputTag("elePFIsoValueCharged"),
            pfNeutralHadrons = cms.InputTag("elePFIsoValueNeutral"),
            pfPhotons        = cms.InputTag("elePFIsoValueGamma"),
            user = cms.VInputTag(
                cms.InputTag("elePFIsoValuePU"),
                cms.InputTag("eleIsoFromDepsEcalFromHitsByCrystalOptimized"),
                cms.InputTag("eleIsoFromDepsHcalFromTowersOptimized"),
                cms.InputTag("eleIsoFromDepsTkOptimized")
                )
            )

  process.eleStdIso = cms.Sequence(process.vetoElectrons+process.vetoMuons+process.eleIsoDepositEcalFromHits+process.eleIsoDepositHcalFromTowers+process.eleIsoDepositTk+process.eleIsoFromDepsTkOptimized+process.eleIsoFromDepsEcalFromHitsByCrystalOptimized +process.eleIsoFromDepsEcalFromHitsByCrystalOptimized+process.eleIsoFromDepsHcalFromTowersOptimized )	
  process.patEleIsoSeq = process.patDefaultSequence
  process.patDefaultSequence = cms.Sequence(process.eleisolationPrePat*process.eleStdIso*process.patEleIsoSeq)

def getAllEventCounters(process,path,onSkim = False):
        stringList = []
        if onSkim:
          stringList.append('processedEvents')

        modules = listModules(path)
    
        for mod in modules:
            if(hasattr(mod,'label')):
                if mod.label().find('Counter') !=-1 :
                    stringList.append(mod.name.value())
        print 'List Of Filters'        
        print stringList
        
        return cms.untracked.vstring(stringList)

def addEventSummary(process,onSkim = False,name = 'summary',path = 'eventSelection'):
    
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )

   summary = cms.EDAnalyzer('EventSummary',
                            src =getAllEventCounters(process,getattr(process,path),onSkim)
   )

   setattr(process,name,summary)
   if onSkim:
        process.EDMtoMEConverter = cms.EDAnalyzer("EDMtoMEConverter",
                                               Name = cms.untracked.string('EDMtoMEConverter'),
                                               Verbosity = cms.untracked.int32(1), # 0 provides no output
                                               # 1 provides basic output
                                               Frequency = cms.untracked.int32(50),
                                               convertOnEndLumi = cms.untracked.bool(True),
                                               convertOnEndRun = cms.untracked.bool(True)
                                               )
        eventSummaryPath=cms.EndPath(process.EDMtoMEConverter+getattr(process,name))
        setattr(process,name+"Path",eventSummaryPath)
   else:
        eventSummaryPath=cms.EndPath(getattr(process,name))
        setattr(process,name+"Path",eventSummaryPath)
   

def addTrackCandidates(process):
  process.trackCandidates = cms.EDProducer("TrackViewCandidateProducer",
                                   src = cms.InputTag("generalTracks"),
                                   particleType = cms.string('mu+'),
                                   cut = cms.string('pt > 8')
  )

  process.gsfTrackCandidates = cms.EDProducer("GSFTrackCandidateProducer",
                                   src = cms.InputTag("electronGsfTracks"),
                                   threshold = cms.double(8.0)
  )



  process.patDefaultSequence*=process.trackCandidates
  process.patDefaultSequence*=process.gsfTrackCandidates




def addSuperClusterCandidates(process):


 process.superClusters = cms.EDProducer("SuperClusterMerger",
                                        src = cms.VInputTag(cms.InputTag("correctedHybridSuperClusters"), cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"))
                                       )

 process.superClusterCands = cms.EDProducer("ConcreteEcalCandidateProducer",
                                              src = cms.InputTag("superClusters"),
                                              particleType = cms.int32(11),
                                           )



 process.patDefaultSequence*=process.superClusters
 process.patDefaultSequence*=process.superClusterCands




def createGeneratedParticles(process,name,commands):


  refObjects = cms.EDProducer("GenParticlePruner",
    src = cms.InputTag("genParticles"),
    select = cms.vstring(
    "drop  *  " 
    )
   )
  refObjects.select.extend(commands)
  setattr(process,name,refObjects)
  process.patDefaultSequence*= getattr(process,name)


def createGeneratedTaus(process,decayMode,fiducialCuts):
  process.generatedTaus = cms.EDFilter("TauGenJetDecayModeSelector",
                                       src = cms.InputTag("tauGenJets"),
                                       select = cms.vstring(decayMode),
                                       filter = cms.bool(False)
                                       )
  process.generatedTausInAcceptance = cms.EDFilter("GenJetSelector",
                                           src = cms.InputTag("generatedTaus"),
                                           cut = cms.string(fiducialCuts),
                                           filter = cms.bool(False)
                                           )

  process.patDefaultSequence*= process.generatedTaus
  process.patDefaultSequence*= process.generatedTausInAcceptance



def addSkimForDATA(process):
  #good vertex
  process.primaryVertexFilter = cms.EDFilter("VertexSelector",
                                        src = cms.InputTag('offlinePrimaryVertices'),
                                        cut = cms.string('ndof()>4&&position().rho()<2&&abs(z())<24'),
                                        filter = cms.bool(False)
  )                                             
  process.preVertexSequence=process.patDefaultSequence
  process.patDefaultSequence=cms.Sequence(process.primaryVertexFilter*process.preVertexSequence)

def cloneAndReplaceInputTag(process,sequence,oldValue,newValue,postfix):
  #First Clone the sequence
  p = cloneProcessingSnippet(process, sequence, postfix)
  massSearchReplaceAnyInputTag(p,oldValue,newValue )
  modules = listModules(p)

  #Change the labels of the counters
  for mod in modules:
    if(hasattr(mod,'label')):
      if mod.label().find('Counter') !=-1 :
        if(hasattr(mod,'name')):
          newValue = mod.name.value()+postfix
          mod.name=cms.string(newValue)
  return p


def addMuonAnalyzer(process,src,ref,paths):
  process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )

  muonAnalysis = cms.EDAnalyzer('MuonEffAnalyzer',
                                        src = cms.InputTag(src),
                                        ref = cms.InputTag(ref),
                                        primaryVertices = cms.InputTag("primaryVertexFilter"),
                                        triggerPaths = cms.vstring(paths)
                                )
  setattr(process,'muonAnalysis'+src,muonAnalysis)
  p = cms.EndPath(getattr(process,'muonAnalysis'+src))
  setattr(process,'muonAnalysisPath'+src,p)



def addTauIDPlotter(process,name,src,ref,discriminators,ptNum = 0.0,ptDenom = 0.0):
  process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )

  muonAnalysis = cms.EDAnalyzer('TauIDPlotter',
                                src=cms.InputTag(src),
                                srcVertices=cms.InputTag("primaryVertexFilter"),
                                ref=cms.InputTag(ref),
                                id= cms.vstring(discriminators),
                                thresholdNum = cms.untracked.double(ptNum),
                                threshold = cms.untracked.double(ptDenom)
                                )                                
  
  setattr(process,'tauFakeRate'+name,muonAnalysis)
  p = cms.EndPath(getattr(process,'tauFakeRate'+name))
  setattr(process,'tauFakeRatePath'+name,p)


def addTagAndProbePlotter(process,type,name,src,ref,selections,methods,triggers,triggersProbe):

  process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
  muonAnalysis = cms.EDAnalyzer(type,
                                src=cms.InputTag(src),
                                vertices=cms.InputTag("primaryVertexFilter"),
                                ref=cms.InputTag(ref),
                                patTrigger = cms.InputTag("patTrigger"),
                                id= cms.vstring(selections),
                                methods= cms.vstring(methods),
                                triggers = cms.vstring(triggers),
                                triggersProbe = cms.vstring(triggersProbe),
  )                                
  
  setattr(process,'tagAndProbe'+name,muonAnalysis)
  p = cms.EndPath(getattr(process,'tagAndProbe'+name))
  setattr(process,'tagAndProbePath'+name,p)


def addRunRangePlotter(process,triggers):
  process.runRangeSummary = cms.EDAnalyzer('RunRangeAnalyzer',
                           patTrigger = cms.InputTag("patTrigger"),
                           triggerRanges = cms.vstring(triggers)
  )                                
  process.p = cms.EndPath(process.runRangeSummary)


def createSystematics(process,sequence,postfix,muScale,eScale,tauScale,jetScale,unclusteredScale):

  #First Clone the sequence
  p = cloneProcessingSnippet(process, sequence, postfix)
  modules = listModules(p)

  #Change the labels of the counters and the smearign modules
  for mod in modules:
    if(hasattr(mod,'label')):
      if mod.label().find('Counter') !=-1 :
        if(hasattr(mod,'name')):
          newValue = mod.name.value()+postfix
          mod.name=cms.string(newValue)
      if mod.label().find('smearedMuons') !=-1 :
          mod.energyScale = cms.double(muScale)
      if mod.label().find('smearedTaus') !=-1 :
          mod.energyScale = cms.double(tauScale)
      if mod.label().find('smearedElectrons') !=-1 :
          mod.energyScale = cms.double(eScale)
      if mod.label().find('smearedJets') !=-1 :
          mod.energyScaleDB = cms.double(jetScale)
      if mod.label().find('smearedMET') !=-1 :
          mod.unclusteredScale= cms.double(unclusteredScale)
  return cms.Path(p) 







   

