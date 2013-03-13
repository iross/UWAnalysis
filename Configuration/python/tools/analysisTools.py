import FWCore.ParameterSet.Config as cms
from CommonTools.ParticleFlow.Isolation.tools_cfi import *

from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.tools.helpers import *
from PhysicsTools.PatAlgos.tools.tauTools import *
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.PatAlgos.tools.metTools import *
from PhysicsTools.PatAlgos.tools.pfTools import *
from PhysicsTools.PatAlgos.tools.trigTools import *
import sys

def defaultAnalysisPath(process,triggerProcess = 'HLT',triggerPaths = ['HLT_Mu9','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v2','HLT_Mu15_v1','HLT_Mu15_v2'],EAtarget='dummy',calTarget='dummy',rochCor='dummy',isMC=False,isSync=False):
    process.load("UWAnalysis.Configuration.startUpSequence_cff")
    #process.load("Configuration.Geometry.GeometryIdeal_cff")
    process.load("Configuration.StandardSequences.Geometry_cff")
    process.load("Configuration.StandardSequences.MagneticField_cff")
    process.load("Configuration.StandardSequences.Services_cff")
    #process.load("Configuration.StandardSequences.Reconstruction_cff")
    process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
    process.load("DQMServices.Core.DQM_cfg")
    process.load("DQMServices.Components.DQMEnvironment_cfi")
    process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")

    #remove MC matching
    #removeMCMatching(process,['All'],"",False)

    global TriggerPaths
    TriggerPaths= triggerPaths

    process.analysisSequence = cms.Sequence()
    process.primaryVertexFilter = cms.EDFilter("VertexSelector",
          src = cms.InputTag('offlinePrimaryVertices'),
          cut = cms.string('!isFake && ndof() > 4 && position().rho() <= 2 && abs(z()) <= 24'),
          filter = cms.bool(True)
          )

    process.analysisSequence*=process.primaryVertexFilter

    #Add PAT Trigger
    #  switchOnTrigger( process,'patTrigger','patTriggerEvent','patDefaultSequence',triggerProcess,'')
    #  muonTriggerMatch(process,triggerProcess)
    #  electronTriggerMatch(process,triggerProcess)
    #  tauTriggerMatch(process,triggerProcess)

    process.looseMu = cms.EDProducer("PATMuonCleanerBySegments",
            src = cms.InputTag("cleanPatMuons"),
            preselection = cms.string("track.isNonnull"),
            passthrough = cms.string("isGlobalMuon && numberOfMatches >= 2"),
            fractionOfSharedSegments = cms.double(0.499)
            )

    #todo--correction types must be based from runtime config

    process.corrMuons = cms.EDProducer("PATMuonCalibrationChooser",
            src = cms.InputTag("looseMu"),
            rochcorType = cms.string(rochCor) # Rochester Correction types: RochCor2011A, RochCor2011B, RochCor2012
            )
    process.recorrMuons = cms.EDProducer("PATMuonRochesterEmbedder",
            #src = cms.InputTag("corrMuons"),
            src = cms.InputTag("looseMu"),
            isMC = cms.bool(isMC),
            isSync = cms.bool(isSync), #use fake smearing for synchronization purposes
            )

    process.goodPatMuons = cms.EDProducer("PATMuonEffectiveAreaEmbedder",
            src = cms.InputTag("recorrMuons"),
            target = cms.string(EAtarget),
            )

    # available calibration targets:
    # 2012 Data : 2012Jul13ReReco, Summer12_DR53X_HCP2012,
    #             Prompt, ReReco, ICHEP2012
    # 2012 MC   : Summer12, Summer12_DR53X_HCP2012
    #
    # 2011 Data : Jan16ReReco
    # 2011 MC   : Summer11, Fall11

    process.corrElectrons = cms.EDProducer("PATElectronCalibrationChooser",
            src = cms.InputTag("cleanPatElectrons"),
            corrType = cms.string("SmearedRegression"), # Calibration types: SmearedRegression, RegressionOnly, SmearedNoRegression
            calTarget = cms.string(calTarget)
            )

    process.eaElectrons = cms.EDProducer("PATElectronEffectiveAreaEmbedder",
            src = cms.InputTag("corrElectrons"),
            target = cms.string(EAtarget),
            )

    process.mvaedElectrons=cms.EDProducer("PATMVAIDEmbedder",
          src=cms.InputTag("eaElectrons"),
          id=cms.string("mvaNonTrigV0"),
          #recalculate MVA if you're applying the ECAL corrections here...
          recalculateMVA=cms.bool(False)
          )

    #remove electrons within 0.3 of a muon
    process.llttElectrons = cms.EDProducer("PATElectronCleaner",
          src = cms.InputTag("eaElectrons"), #was mvaedElectrons temp IAR 31.Jan.2013
          preselection = cms.string(""),
          checkOverlaps = cms.PSet(
              muons = cms.PSet(
                  src=cms.InputTag("cleanPatMuons"),
                  algorithm=cms.string("byDeltaR"),
                  preselection=cms.string("pfCandidateRef().isNonnull() && (isTrackerMuon() | isGlobalMuon()) && pt>10 && (chargedHadronIso()+max(0.0,neutralHadronIso()+photonIso()-userFloat('zzRho')*userFloat('EAGammaNeuHadron04')))/pt<0.40"),
                  deltaR=cms.double(0.3),
                  checkRecoComponents = cms.bool(False),
                  pairCut=cms.string(""),
                  requireNoOverlaps=cms.bool(True)
                  )
              ),
          finalCut = cms.string("")
          )

    #remove taus within 0.3 of a electron
    process.llttTaus = cms.EDProducer("PATTauCleaner",
          src = cms.InputTag("cleanPatTaus"),
          preselection = cms.string(""),
          checkOverlaps = cms.PSet(
              muons = cms.PSet(
                  src=cms.InputTag("mvaedElectrons"),
                  algorithm=cms.string("byDeltaR"),
                  preselection=cms.string("pt>10 && userFloat('mvaNonTrigV0Pass')>0 && (chargedHadronIso()+max(0.0,neutralHadronIso()+photonIso()-userFloat('zzRho')*userFloat('EAGammaNeuHadron04')))/pt<0.40"),
                  deltaR=cms.double(0.3),
                  checkRecoComponents = cms.bool(False),
                  pairCut=cms.string(""),
                  requireNoOverlaps=cms.bool(True)
                  )
              ),
          finalCut = cms.string("")
          )

    process.analysisSequence*=process.looseMu*process.corrMuons*process.recorrMuons*process.goodPatMuons+process.corrElectrons*process.eaElectrons*process.mvaedElectrons+process.llttElectrons+process.llttTaus

    process.runAnalysisSequence = cms.Path(process.analysisSequence)


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
    removeMCMatching(process, ['All'], outputModules = [])

    process.recoPAT = cms.Sequence(process.ak5PFJets+process.PFTau+process.patDefaultSequence)

    #HPS
    switchToPFTauHPS(process)

    #applyparticle based isolation
    switchToElePFIsolation(process,'gsfElectrons')
    switchToMuPFIsolation(process,'muons')
    runPFNoPileUp(process)

def defaultReconstruction(process,triggerProcess = 'HLT',triggerPaths = ['HLT_Mu9','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v2','HLT_Mu15_v1','HLT_Mu15_v2']):
    #Make PAT
    runRECO(process)


    #Make the TriggerPaths Global variable to be accesed by the ntuples
    global TriggerPaths
    TriggerPaths= triggerPaths

    #Add PF MET
    addPfMET(process,'')


    #Use PF Jets with b-tagging and corrections

    switchJetCollection(process,cms.InputTag('ak5PFJets'),True,True,('AK5PF',['L1FastJet','L2Relative','L3Absolute','L2L3Residual']),False,cms.InputTag("ak5GenJets"),True,"ak5","","")

    #remove MC matching
    removeMCMatching(process,['All'],"",False)

    #HPS
    switchToPFTauHPS(process)

    #apply particle based isolation
    switchToElePFIsolation(process,'gsfElectrons')
    switchToMuPFIsolation(process,'muons')

    #Add PAT Trigger
    switchOnTrigger( process,'patTrigger','patTriggerEvent','patDefaultSequence',triggerProcess,'')
    muonTriggerMatch(process,triggerProcess)
    electronTriggerMatch(process,triggerProcess)
    tauTriggerMatch(process,triggerProcess)

    #Particle  Overloading
    muonOverloading(process,'triggeredPatMuons')
    tauOverloading(process,'triggeredPatTaus')
    jetOverloading(process)
    electronOverloading(process,True,'triggeredPatElectrons')

    #Add the tracks
    addTrackCandidates(process)

    #addSuperClusters
    addSuperClusterCandidates(process)

    #add Good vertex criteria
    addSkimForDATA(process)

    #Apply default selections
    applyDefaultSelections(process)

    #Run FastJet
    runPFNoPileUp(process)


def defaultReconstructionMC(process,triggerProcess = 'HLT',triggerPaths = ['HLT_Mu9'],calibrateMET = False,calibrationScheme = "BothLegs"):
    #Make PAT
    runRECO(process)

    global TriggerPaths
    TriggerPaths= triggerPaths

    #Use PF Jets
    switchJetCollection(process,cms.InputTag('ak5PFJets'),True,True,('AK5PF',['L1FastJet','L2Relative','L3Absolute']),False,cms.InputTag("ak5GenJets"),True,"ak5","","")

    #make HPS Tau ID
    switchToPFTauHPS(process)

    #Add PF MET
    addPfMET(process,'')

    #apply particle based isolation
    switchToElePFIsolation(process,'gsfElectrons')
    switchToMuPFIsolation(process,'muons')

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

    runPFNoPileUp(process)




def applyDefaultSelections(process):
    #DONT CHANGE THOSE HERE:: THEY ARE NOT USED FOR YOUR SELECTIONS!!!
    #ONLY FOR SYSTEMATICS . PLEASE CHANGE THEM in YOUR CFG FILE IF REALLY NEEDED

    #require jet selection over 15 GeV
    process.selectedPatJets.cut =  cms.string("abs(eta)<4.5&&pt>10&&neutralHadronEnergyFraction<0.99&&neutralEmEnergyFraction<0.99&nConstituents>1&&((abs(eta)>2.4)||(abs(eta)<2.4&&chargedHadronEnergyFraction>0&&chargedMultiplicity>0&&chargedEmEnergyFraction<0.99))")
    #require muon selection
    process.selectedPatMuons.cut =  cms.string("pt>10&&isGlobalMuon&&(chargedHadronIso()+max(photonIso+neutralHadronIso()-0.5*userIso(0),0.0))/pt()<0.3")
    #require electron selection
    process.selectedPatElectrons.cut =  cms.string('pt>10&&userFloat("wp95")>0&&(chargedHadronIso()+max(photonIso()+neutralHadronIso()-0.5*particleIso(),0.0))/pt()<0.3')
    #require tau selection
    process.selectedPatTaus.cut =cms.string('pt>15&&tauID("decayModeFinding")&&tauID("byLooseCombinedIsolationDeltaBetaCorr")>0')




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
    process.load('RecoJets.Configuration.RecoPFJets_cff')
    process.ak5PFJets.doAreaFastjet = True
    process.recoPAT = cms.Path(process.ak5PFJets+process.PFTau+process.patElectronId+process.patDefaultSequence)




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
                cms.InputTag('hltL1Mu7EG5L3MuFiltered17','',triggerProcess),
                cms.InputTag('hltL1MuOpenEG12L3Filtered8','',triggerProcess),
                cms.InputTag('hltL1MuOpenEG5L3Filtered8','',triggerProcess),
                cms.InputTag('hltL1MuOpenEG8L3Filtered8','',triggerProcess),
                cms.InputTag('hltL1Mu3EG5L3Filtered8','',triggerProcess),
                cms.InputTag('hltOverlapFilterIsoMu12IsoPFTau10','',triggerProcess),
                cms.InputTag('hltSingleMuIsoL3IsoFiltered17','',triggerProcess),
                cms.InputTag('hltSingleMuL2QualIsoL3IsoFiltered17','',triggerProcess),
                cms.InputTag('hltSingleMuL2QualIsoL3IsoFiltered24','',triggerProcess),
                cms.InputTag('hltSingleMu13L3Filtered13','',triggerProcess),
                cms.InputTag('hltSingleMuIsoL1s14L3IsoFiltered15eta2p1',"",triggerProcess),
                cms.InputTag('hltL3IsoL1sMu14Eta2p1L1f0L2f14QL2IsoL3f24L3IsoFiltered','',triggerProcess),
                cms.InputTag('hltDiMuonL3p5PreFiltered8','',triggerProcess),
                cms.InputTag('hltSingleMu13L3Filtered17','',triggerProcess)
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
                cms.InputTag('hltEle8CaloIdLCaloIsoVLPixelMatchFilter','',triggerProcess),
                cms.InputTag('hltL1NonIsoHLTNonIsoMu17Ele8PixelMatchFilter','',triggerProcess),
                cms.InputTag('hltMu8Ele17CaloIdTCaloIsoVLPixelMatchFilter','',triggerProcess),
                cms.InputTag('hltL1NonIsoHLTNonIsoMu8Ele17PixelMatchFilter','',triggerProcess),
                cms.InputTag('hltMu17Ele8CaloIdTPixelMatchFilter','',triggerProcess)
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
                cms.InputTag('hltOverlapFilterIsoEle15IsoPFTau15','',triggerProcess),
                cms.InputTag('hltOverlapFilterIsoEle15TightIsoPFTau20','',triggerProcess),
                cms.InputTag('hltOverlapFilterIsoEle18MediumIsoPFTau20','',triggerProcess),
                cms.InputTag('hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTSC8TrackIsolFilter','',triggerProcess),
                cms.InputTag('hltEle17CaloIdVTCaloIsoVTTrkIdTTrkIsoVTEle8TrackIsolFilter','',triggerProcess),
                cms.InputTag('hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolFilter','',triggerProcess),
                cms.InputTag('hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolDoubleFilter','',triggerProcess),
                cms.InputTag('hltEle20CaloIdVTCaloIsoTTrkIdTTrkIsoTTrackIsoFilterL1SingleEG18orL1SingleEG20','',triggerProcess),
                cms.InputTag('hltEle32CaloIdTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter','',triggerProcess),
                cms.InputTag('hltEle32CaloIdVTCaloIsoTTrkIdTTrkIsoTTrackIsoFilter','',triggerProcess),
                cms.InputTag('hltOverlapFilterIsoEle18TightIsoPFTau20','',triggerProcess),
                cms.InputTag('hltOverlapFilterIsoEle18IsoPFTau20','',triggerProcess),
                cms.InputTag('hltOverlapFilterIsoEle20MediumIsoPFTau20','',triggerProcess)
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
               cms.InputTag('hltOverlapFilterIsoEle20MediumIsoPFTau20','',triggerProcess),
               cms.InputTag('hltFilterDoubleIsoPFTau20Trk5LeadTrack5IsolationL1HLTMatched','',triggerProcess),
               cms.InputTag('hltPFTauMediumIso20TrackMediumIso','',triggerProcess),
               cms.InputTag('hltPFTau15TrackLooseIso','',triggerProcess),
               cms.InputTag('hltPFTau20TrackLooseIso','',triggerProcess),
               cms.InputTag('hltPFTauTightIso20TrackTightIso','',triggerProcess)
               ),

           pdgId = cms.int32(15)
           )

    process.patDefaultSequence=cms.Sequence(process.patDefaultSequence*process.preTriggeredPatTaus*process.triggeredPatTaus)




def tauOverloading(process,src):


    process.patRhoTau = cms.EDProducer("TauRhoOverloader",
            src = cms.InputTag(src),
            srcRho = cms.InputTag("kt6PFJets","rho")
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
            srcRho = cms.InputTag("kt6PFJets","rho")
            )


    process.mvaElectrons = cms.EDProducer('PATWWMVAElectronEmbedder',
            src             = cms.InputTag("patRhoElectron"),
            srcVertices     = cms.InputTag("primaryVertexFilter"),
            ebHits          = cms.InputTag("reducedEcalRecHitsEB"),
            eeHits          = cms.InputTag("reducedEcalRecHitsEE"),
            id              = cms.string("WWMVAID"),
            d0              = cms.double(0.045),
            dz              = cms.double(0.2),
            )
    process.convRejElectrons = cms.EDProducer('PATWWElectronEmbedder',
            src             = cms.InputTag("mvaElectrons"),
            srcVertices     = cms.InputTag("primaryVertexFilter"),
            sigmaEtaEta     = cms.vdouble(0.01,0.03,0.01,0.03),
            deltaEta        = cms.vdouble(0.004,0.005,0.004,0.007),
            deltaPhi        = cms.vdouble(0.03,0.02,0.06,0.03),
            hoE             = cms.vdouble(0.025,0.025,0.04,0.025),
            id              = cms.string("WWID"),
            fbrem           = cms.double(0.15),
            EOP             = cms.double(0.95),
            d0              = cms.double(0.045),
            dz              = cms.double(0.2),
            )


    process.electronOverloading=cms.Sequence(process.electronsWP80+process.electronsWP90+process.electronsWP95+process.patRhoElectron+process.mvaElectrons+process.convRejElectrons)
    process.postElectronSequence=process.patDefaultSequence
    process.patDefaultSequence = cms.Sequence(process.CICID*process.postElectronSequence*process.electronOverloading)

def muonOverloading(process,src):
    process.patPFMuonMatch = cms.EDProducer("PATPFMuonEmbedder", #Saves the case where muon is matched to a PF Muon
            src = cms.InputTag(src),
            ref = cms.InputTag("pfAllMuons")
            )

    process.patZZMuonMatch = cms.EDProducer("PATZZMuonEmbedder", #Saves the case where muon is matched to a PF Muon
            src = cms.InputTag("patPFMuonMatch"),
            maxChi2=cms.double(10.),
            minTrackerHits=cms.int32(10),
            minMuonHits = cms.int32(0),
            minMatches  = cms.int32(1)

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
            minTrackerHits=cms.int32(11),
            minPixelHits=cms.int32(1),
            minMuonHits = cms.int32(1),
            minMatches  = cms.int32(2),
            maxResol      = cms.double(0.1),
            dz            = cms.double(0.2)
            )

    process.patMuonsForAnalysis = cms.EDProducer("MuonRhoOverloader",
            src = cms.InputTag("patWWMuonMatch"),
            srcRho = cms.InputTag("kt6PFJets","rho")
            )

    process.patDefaultSequence = cms.Sequence(process.patDefaultSequence*process.patPFMuonMatch*process.patZZMuonMatch*process.patVBTFMuonMatch*process.patWWMuonMatch*process.patMuonsForAnalysis)


def runPFNoPileUp(process):
    process.load("CommonTools.ParticleFlow.pfParticleSelection_cff")
    process.pfPileUpCandidates = cms.EDProducer(
            "TPPFCandidatesOnPFCandidates",
            enable =  cms.bool( True ),
            verbose = cms.untracked.bool( False ),
            name = cms.untracked.string("pileUpCandidates"),
            topCollection = cms.InputTag("pfNoPileUpIso"),
            bottomCollection = cms.InputTag("particleFlow"),
            )

    #enable PF no Pile Up
    process.pfPileUp.Enable = cms.bool(True)

    #Apply the bug fix in 42X
    process.pfPileUp.checkClosestZVertex = cms.bool(True)

    #Put all charged particles in charged hadron collection(electrons and muons)
    process.pfAllChargedHadrons.pdgId = cms.vint32(211,-211,321,-321,999211,2212,-2212,11,-11,13,-13)

    process.pileUpHadrons = cms.EDFilter("PdgIdPFCandidateSelector",
            src = cms.InputTag("pfPileUpCandidates"),
            pdgId = cms.vint32(211,-211,321,-321,999211,2212,-2212,11,-11,13,-13)
            )
    process.pfAllNeutrals = cms.EDFilter("PdgIdPFCandidateSelector",
            src = cms.InputTag("pfNoPileUpIso"),
            pdgId = cms.vint32(111,130,310,2112,22)
            )

    process.pfAllElectrons.src = cms.InputTag("pfNoPileUpIso")

    process.pfAllMuons = cms.EDFilter("PdgIdPFCandidateSelector",
            src = cms.InputTag("pfNoPileUpIso"),
            pdgId = cms.vint32(13,-13)
            )

    process.pfPostSequence = cms.Sequence(
            process.pfParticleSelectionSequence+
            process.pfAllMuons+
            process.pfPileUpCandidates+
            process.pileUpHadrons
            )

    process.patPreIsoSeq = process.pfPostSequence
    process.patDefaultSequence = cms.Sequence(process.patPreIsoSeq*process.patDefaultSequence)


def switchToMuPFIsolation(process,muons):

    ###Muon Isolation

    process.muPFIsoDepositAll     = isoDepositReplace(muons,cms.InputTag("pfNoPileUpIso"))
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
                    vetos = cms.vstring('0.0000','Threshold(0.5)'),
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

    process.patMuons.isolationValues = cms.PSet(
            particle         = cms.InputTag("muPFIsoValueAll"),
            pfChargedHadrons = cms.InputTag("muPFIsoValueCharged"),
            pfNeutralHadrons = cms.InputTag("muPFIsoValueNeutral"),
            pfPhotons        = cms.InputTag("muPFIsoValueGamma"),
            user = cms.VInputTag(
                cms.InputTag("muPFIsoValuePU")
                )

            )

    process.patSeq = process.patDefaultSequence
    process.patDefaultSequence = cms.Sequence(process.muisolationPrePat*process.patSeq)



def switchToElePFIsolation(process,electrons):
    ###Electron Isolation

    process.elePFIsoDepositAll     = isoDepositReplace(electrons,cms.InputTag("pfNoPileUpIso"))
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
                    vetos = cms.vstring('0.015','Threshold(1.0)'),
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
                    vetos = cms.vstring('0.015','Threshold(0.0)'),
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
                    vetos = cms.vstring('0.00','Threshold(0.5)'),
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
                    vetos = cms.vstring('0.00','Threshold(0.5)'),
                    skipDefaultVeto = cms.bool(True),
                    mode = cms.string('sum')
                    )
                )
            )

    process.elePFIsoValueGammaVeto = cms.EDProducer("CandIsolatorFromDeposits",
            deposits = cms.VPSet(
                cms.PSet(
                    src = cms.InputTag("elePFIsoDepositGamma"),
                    deltaR = cms.double(0.4),
                    weight = cms.string('1'),
                    vetos = cms.vstring('0.08','Threshold(0.5)'),
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
            * process.elePFIsoValueGammaVeto
            * process.elePFIsoValuePU
            )

    process.eleisolationPrePat = cms.Sequence(
            process.elePFIsoDeposits*
            process.elePFIsoValues
            )

    process.patElectrons.isoDeposits = cms.PSet(
            pfAllParticles   = cms.InputTag("elePFIsoDepositAll"),
            pfChargedHadrons = cms.InputTag("elePFIsoDepositCharged"),
            pfNeutralHadrons = cms.InputTag("elePFIsoDepositNeutral"),
            pfPhotons        = cms.InputTag("elePFIsoDepositGamma")
            )

    ###KLUDGE -> Add DB in UserIso
    process.patElectrons.isolationValues = cms.PSet(
            pfAllParticles   = cms.InputTag("elePFIsoValueAll"),
            pfChargedHadrons = cms.InputTag("elePFIsoValueCharged"),
            pfNeutralHadrons = cms.InputTag("elePFIsoValueNeutral"),
            pfPhotons        = cms.InputTag("elePFIsoValueGamma"),
            user = cms.VInputTag(
                cms.InputTag("elePFIsoValuePU"),
                cms.InputTag("elePFIsoValueGammaVeto")
                )
            )

    #52x requires PFId and NoPFId values definied. Quick and dirty workaround IAR 06.Jul.2012
    process.patElectrons.isolationValuesNoPFId = process.patElectrons.isolationValues.clone()

    process.patEleIsoSeq = process.patDefaultSequence
    process.patDefaultSequence = cms.Sequence(process.eleisolationPrePat*process.patEleIsoSeq)




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




def createGeneratedParticlesPATtuple(process,name,commands):
    refObjects = cms.EDProducer("GenParticlePruner",
            src = cms.InputTag("genParticles"),
            select = cms.vstring(
                "drop  *  "
                )
            )
    refObjects.select.extend(commands)
    setattr(process,name,refObjects)
    process.analysisSequence*= getattr(process,name)




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
                    newValue = mod.name.value() + postfix
                    mod.name=cms.string(newValue)
    return p




def createSystematics(process,sequence,postfix,muScale,eScale,tauScale,jetScale,unclusteredScale,electronresb = 0.0, electronrese = 0.0):

    #First Clone the sequence
    p = cloneProcessingSnippet(process, sequence, postfix)
    modules = listModules(p)

    #Change the labels of the counters and the smearign modules
    for mod in modules:
        if(hasattr(mod,'label')):
            if mod.label().find('Counter') != -1 :
                if(hasattr(mod,'name')):
                    newValue = mod.name.value()+postfix
                    mod.name=cms.string(newValue)
            if mod.label().find('smearedMuons') != -1 :
                mod.energyScale = cms.double(muScale)
            if mod.label().find('smearedTaus') != -1 :
                mod.energyScale = cms.double(tauScale)
            if mod.label().find('smearedElectrons') != -1 :
                mod.energyScale = cms.double(eScale)
                mod.deltaPtB = cms.double(electronresb)
                mod.deltaPtE = cms.double(electronrese)
            if mod.label().find('smearedJets') != -1 :
                mod.energyScaleDB = cms.int32(jetScale)
            if mod.label().find('smearedMET') != -1 :
                mod.unclusteredScale= cms.double(unclusteredScale)
    return cms.Path(p)




def createRecoilSystematics(process,sequence,postfix,metScale,metResolution):

    #First Clone the sequence
    p = cloneProcessingSnippet(process, sequence, postfix)
    modules = listModules(p)

    #Change the labels of the counters and the smearign modules
    for mod in modules:
        if(hasattr(mod,'label')):
            if mod.label().find('Counter') != -1 :
                if(hasattr(mod,'name')):
                    newValue = mod.name.value()+postfix
                    mod.name=cms.string(newValue)

        if(hasattr(mod,'metCalibration')):
            mod.metCalibration.shiftScale = cms.untracked.double(metScale)
            mod.metCalibration.shiftRes   = cms.untracked.double(metResolution)

    return cms.Path(p)
