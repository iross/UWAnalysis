from UWAnalysis.Configuration.tools.analysisTools import TriggerPaths
import FWCore.ParameterSet.Config as cms

def zzCommon(src,pluginType):
    sharedV = cms.VPSet(
            cms.PSet(
                pluginType = cms.string("PUFiller"),
                src        = cms.InputTag("addPileupInfo"),
                tag        = cms.string("pu")
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mass"),
                method     = cms.string("mass()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("pt"),
                method     = cms.string("pt()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("charge"),
                method     = cms.string("charge()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Mass"),
                method     = cms.string("leg1.mass()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Mass"),
                method     = cms.string("leg2.mass()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Charge"),
                method     = cms.string("leg1.charge()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Charge"),
                method     = cms.string("leg2.charge()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Pt"),
                method     = cms.string("leg1.pt()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Pt"),
                method     = cms.string("leg2.pt()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Eta"),
                method     = cms.string("leg1.eta()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Eta"),
                method     = cms.string("leg2.eta()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Phi"),
                method     = cms.string("leg1.phi()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Phi"),
                method     = cms.string("leg2.phi()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("met"),
                method     = cms.string("met.pt()"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag      = cms.string("rho"),
                method     = cms.string('leg1.leg1.userFloat("rho")'),
                leadingOnly= cms.untracked.bool(True)
                ),  
            )
    return sharedV

def metCommon(src,pluginType):
    sharedV = cms.VPSet(
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mt"),
                method     = cms.string("mt12MET"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mt1"),
                method     = cms.string("mt1MET"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mt1_12"),
                method     = cms.string("leg1.mt12MET"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mt1_1"),
                method     = cms.string("leg1.mt1MET"),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt1_2"),
                    method     = cms.string("leg1.mt2MET"),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt2"),
                    method     = cms.string("mt2MET"),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt2_12"),
                    method     = cms.string("leg2.mt12MET"),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt2_1"),
                    method     = cms.string("leg2.mt1MET"),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt2_2"),
                    method     = cms.string("leg2.mt2MET"),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("dZ12"),
                    method     = cms.string('leg1.dz'),
                    leadingOnly= cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("dZ13"),
                    method     = cms.string('abs(leg1.z1-leg2.z1)'),
                    leadingOnly= cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("dZ14"),
                    method     = cms.string('abs(leg1.z1-leg2.z2)'),
                    leadingOnly= cms.untracked.bool(True)
                    ),  
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("z1l1Z"),
                    method     = cms.string('leg1.z1'),
                    leadingOnly= cms.untracked.bool(True)
                    ),  
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("z1l2Z"),
                    method     = cms.string('leg1.z2'),
                    leadingOnly= cms.untracked.bool(True)
                    ),  
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("z2l1Z"),
                    method     = cms.string('leg2.z1'),
                    leadingOnly= cms.untracked.bool(True)
                    ),  
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("z2l2Z"),
                    method     = cms.string('leg2.z2'),
                    leadingOnly= cms.untracked.bool(True)
                    ),  
        )
    return sharedV

def genCommon(src,pluginType):
    sharedV = cms.VPSet(
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1l1GenPt"),
                method     = cms.string('leg1.p4VisLeg1gen().pt()'),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1l2GenPt"),
                method     = cms.string('leg1.p4VisLeg2gen().pt()'),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1GenPdgId"),
                method     = cms.string('genPdg1()'),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l2GenPdgId"),
                method     = cms.string('genPdg2()'),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1l1GenPdgId"),
                method     = cms.string('leg1.genPdg1()'),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1l2GenPdgId"),
                method     = cms.string('leg1.genPdg2()'),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l2l1GenPdgId"),
                method     = cms.string('leg2.genPdg1()'),
                leadingOnly=cms.untracked.bool(True)
                ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l2l2GenPdgId"),
                    method     = cms.string('leg2.genPdg2()'),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l1GenMass"),
                    method     = cms.string('leg1.p4VisGen().M()'),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l2l1GenPt"),
                    method     = cms.string('leg2.p4VisLeg1gen().pt()'),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l2l2GenPt"),
                    method     = cms.string('leg2.p4VisLeg2gen().pt()'),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l2GenMass"),
                    method     = cms.string('leg2.p4VisGen().M()'),
                    leadingOnly=cms.untracked.bool(True)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("GenMass"),
                    method     = cms.string('p4VisGen().M()'),
                    leadingOnly=cms.untracked.bool(True)
                    )
            )
    return sharedV

def countCommon(src, pluginType, srcEEEE, srcEEMM, srcMMEE, srcMMMM):
    sharedV = cms.VPSet(
        cms.PSet(
            pluginType = cms.string(pluginType+"JetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
#       cms.PSet(
#           pluginType = cms.string(pluginType+"JetCountFillerOL"),
#           src        = cms.InputTag(src),
#           tag        = cms.string("jetsPt20bLooseOL"),
#           method     = cms.string('pt()>20&&bDiscriminator("")>1.7&&abs(eta)<2.4'),
#           leadingOnly=cms.untracked.bool(True)
#       ),
#       cms.PSet(
#           pluginType = cms.string(pluginType+"JetCountFillerOL"),
#           src        = cms.InputTag(src),
#           tag        = cms.string("jetsPt20bMedOL"),
#           method     = cms.string('pt()>20&&bDiscriminator("")>3.3&&abs(eta)<2.4'),
#           leadingOnly=cms.untracked.bool(True)
#       ),
        cms.PSet(
            pluginType = cms.string(pluginType+"JetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20bLoose"),
            method     = cms.string('pt()>20&&bDiscriminator("")>1.7&&abs(eta)<2.4'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType+"JetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20bMed"),
            method     = cms.string('pt()>20&&bDiscriminator("")>3.3&&abs(eta)<2.4'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string("CollectionSizeFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("nZZCandidates"),
            ),
        cms.PSet(
            pluginType = cms.string("CollectionSizeFiller"),
            src        = cms.InputTag(srcEEEE),
            tag        = cms.string("nZZeeeeCandidates"),
            ),
        cms.PSet(
            pluginType = cms.string("CollectionSizeFiller"),
            src        = cms.InputTag(srcEEMM),
            tag        = cms.string("nZZeemmCandidates"),
            ),
        cms.PSet(
            pluginType = cms.string("CollectionSizeFiller"),
            src        = cms.InputTag(srcMMEE),
            tag        = cms.string("nZZmmeeCandidates"),
        ),
        cms.PSet(
            pluginType = cms.string("CollectionSizeFiller"),
            src        = cms.InputTag(srcMMMM),
            tag        = cms.string("nZZmmmmCandidates"),
        ),
        cms.PSet(
                pluginType = cms.string("ElectronCountFiller"),
                src        = cms.InputTag('mvaedElectrons'),
                # pass candidate collection so we can cross-clean
                # dR
                tag        = cms.string("nElectrons"),
                method     = cms.string("pt>10 && userFloat('mvaNonTrigV0Pass')>0 && (chargedHadronIso()+max(0.0,neutralHadronIso()+photonIso()-userFloat('zzRho')*userFloat('EAGammaNeuHadron04')))/pt<0.4"),
                ),
        cms.PSet(
                pluginType = cms.string("MuonCountFiller"),
                src        = cms.InputTag('cleanPatMuons'),
                # pass candidate collection so we can cross-clean
                # dR
                tag        = cms.string("nMuons"),
                method     = cms.string("pfCandidateRef().isNonnull() && (isTrackerMuon() | isGlobalMuon()) && pt>10 && (chargedHadronIso()+max(0.0,neutralHadronIso()+photonIso()-userFloat('zzRho')*userFloat('EAGammaNeuHadron04')))/pt<0.40"),
                ),
        cms.PSet(
                pluginType = cms.string("TauCountFiller"),
                src        = cms.InputTag('cleanPatTaus'),
                # pass candidate collection so we can cross-clean
                # dR
                tag        = cms.string("nTaus"),
                method     = cms.string("pt>20 && tauID('againstMuonLoose') && tauID('againstElectronLoose') && tauID('byLooseIsolationMVA')"),
                ),
        cms.PSet(
                pluginType = cms.string(pluginType+"EleExtraCountFiller"),
                src        = cms.InputTag('mvaedElectrons'),
                candSrc        = cms.InputTag(src),
                mindR = cms.double(0.3),
                tag        = cms.string("nExtraElectrons"),

                method     = cms.string("pt>10 && userFloat('mvaNonTrigV0Pass')>0 && (chargedHadronIso()+max(0.0,neutralHadronIso()+photonIso()-userFloat('zzRho')*userFloat('EAGammaNeuHadron04')))/pt<0.40"),
                ),
        cms.PSet(
                pluginType = cms.string(pluginType+"MuExtraCountFiller"),
                src        = cms.InputTag('cleanPatMuons'),
                candSrc        = cms.InputTag(src),
                mindR = cms.double(0.3),
                tag        = cms.string("nExtraMuons"),
                method     = cms.string("pfCandidateRef().isNonnull() && (isTrackerMuon() | isGlobalMuon()) && pt>10 && (chargedHadronIso()+max(0.0,neutralHadronIso()+photonIso()-userFloat('zzRho')*userFloat('EAGammaNeuHadron04')))/pt<0.40"),
                ),
        cms.PSet(
                pluginType = cms.string(pluginType+"TauExtraCountFiller"),
                src        = cms.InputTag('cleanPatTaus'),
                candSrc        = cms.InputTag(src),
                mindR = cms.double(0.3),
                tag        = cms.string("nExtraTaus"),
                method     = cms.string("pt>20 && tauID('againstMuonLoose') && tauID('againstElectronLoose') && tauID('byLooseIsolationMVA')"),
                ),
        )
    return sharedV

def muCommon(src,legName,legMethod,pluginType):
    sharedV = cms.VPSet(
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Pt"),
            method     = cms.string(legMethod+"pt"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Eta"),
            method     = cms.string(legMethod+"eta"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Phi"),
            method     = cms.string(legMethod+"phi"),
            leadingOnly=cms.untracked.bool(True)
        ),
        #temp
#       cms.PSet(
#           pluginType = cms.string(pluginType),
#           src        = cms.InputTag(src),
#           tag        = cms.string(legName+"ValidMuonHits"),
#           method     = cms.string(legMethod+"globalTrack().hitPattern().numberOfValidMuonHits()"),
#           leadingOnly=cms.untracked.bool(True)
#       ),
#       cms.PSet(
#           pluginType = cms.string(pluginType),
#           src        = cms.InputTag(src),
#           tag        = cms.string(legName+"numMatches"),
#           method     = cms.string(legMethod+"numberOfMatches()"),
#           leadingOnly=cms.untracked.bool(True)
#       ),
#       cms.PSet(
#           pluginType = cms.string(pluginType),
#           src        = cms.InputTag(src),
#           tag        = cms.string(legName+"ValidHits"),
#           method     = cms.string(legMethod+"numberOfValidHits()"),
#           leadingOnly=cms.untracked.bool(True)
#       ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"isGlobal"),
            method     = cms.string(legMethod+"isGlobalMuon()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"isTracker"),
            method     = cms.string(legMethod+"isTrackerMuon()"),
            leadingOnly=cms.untracked.bool(True)
        ),
#       cms.PSet(
#           pluginType = cms.string(pluginType),
#           src        = cms.InputTag(src),
#           tag        = cms.string(legName+"NormChiSq"),
#           method     = cms.string(legMethod+"normChi2()"),
#           leadingOnly=cms.untracked.bool(True)
#       ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoEcaldR03"),
            method     = cms.string(legMethod+"isolationR03().emEt"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoEcal"),
            method     = cms.string(legMethod+"userIso(1)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoHcaldR03"),
            method     = cms.string(legMethod+"isolationR03().hadEt"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoHcal"),
            method     = cms.string(legMethod+"userIso(2)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoTk"),
            method     = cms.string(legMethod+"userIso(3)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPFIsoDB"),
            method     = cms.string("("+legMethod+"chargedHadronIso+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-0.5*"+legMethod+"userIso(0),0.0))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPfIsoRho"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-"+legMethod+"userFloat('rho')*3.14*0.4*0.4,0.0))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rho"),
            method     = cms.string(legMethod+"userFloat('rho')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"SIP"),
            method     = cms.string(legMethod+"userFloat('ip3DS')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dXY"),
            method     = cms.string(legMethod+"userFloat('ipDXY')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dz"),
            method     = cms.string(legMethod+"userFloat('dz')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dB"),
            method     = cms.string(legMethod+"userIso(0)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfChargedHad"),
            method     = cms.string(legMethod+"chargedHadronIso()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfNeutralHad"),
            method     = cms.string(legMethod+"neutralHadronIso()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfPhotonIso"),
            method     = cms.string(legMethod+"photonIso()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rhoZZ"),
            method     = cms.string(legMethod+"userFloat('zzRho')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rhoZZ2012"),
            method     = cms.string(legMethod+"userFloat('zzRho2012')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EAGamma04"),
            method     = cms.string(legMethod+"userFloat('EAGamma04')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EANeuHadron04"),
            method     = cms.string(legMethod+"userFloat('EANeuHadron04')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EAGammaNeuHadron04"),
            method     = cms.string(legMethod+"userFloat('EAGammaNeuHadron04')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso2012"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+legMethod+"photonIso()-"+legMethod+"userFloat('EAGammaNeuHadron04')*"+legMethod+"userFloat('zzRho2012')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+legMethod+"photonIso()-"+legMethod+"userFloat('EAGammaNeuHadron04')*"+legMethod+"userFloat('zzRho')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"idMVA"),
            method     = cms.string(legMethod+"userFloat('idmva')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"isPF"),
            method=cms.string(legMethod+"pfCandidateRef.isNonnull()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"ringRad"),
            method     = cms.string(legMethod+"userFloat('isoringsradmva')"),
            leadingOnly=cms.untracked.bool(True)
        )
        )
    return sharedV

def tauCommon(src,legName,legMethod,pluginType):
    sharedV = cms.VPSet(
        cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string(legName+"Eta"),
                method     = cms.string(legMethod+"eta"),
                leadingOnly=cms.untracked.bool(True)
                ),
        cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string(legName+"Phi"),
                method     = cms.string(legMethod+"phi"),
                leadingOnly=cms.untracked.bool(True)
                ),
        cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string(legName+"Pt"),
                method     = cms.string(legMethod+"pt"),
                leadingOnly=cms.untracked.bool(True)
                ),
        cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string(legName+"JetPt"),
                method     = cms.string(legMethod+"pfJetRef.pt"),
                leadingOnly=cms.untracked.bool(True)
                ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Prongs"),
            method     = cms.string(legMethod+"signalPFChargedHadrCands.size()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Gammas"),
            method     = cms.string(legMethod+"signalPFGammaCands.size()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Mass"),
            method     = cms.string(legMethod+"mass()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"VLooseIso"),
            method     = cms.string(legMethod+"tauID('byVLooseIsolation')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"LooseIso"),
            method     = cms.string(legMethod+"tauID('byLooseIsolation')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MediumIso"),
            method     = cms.string(legMethod+"tauID('byMediumIsolation')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName+"QIso"),
            method      = cms.string(legMethod+"isolationPFChargedHadrCandsPtSum()"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName+"NIso"),
            method      = cms.string(legMethod+"isolationPFGammaCandsEtSum()"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName+"PUIso"),
            method      = cms.string(legMethod+"particleIso()"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"LooseIsoDB"),
            method     = cms.string(legMethod+"tauID('byLooseIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MediumIsoDB"),
            method     = cms.string(legMethod+"tauID('byMediumIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"LooseIsoCombDB"),
            method     = cms.string(legMethod+"tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MediumIsoCombDB"),
            method     = cms.string(legMethod+"tauID('byMediumCombinedIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"TightIsoCombDB"),
            method     = cms.string(legMethod+"tauID('byTightCombinedIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EleVeto"),
            method     = cms.string(legMethod+"tauID('againstElectronLoose')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MuVeto"),
            method     = cms.string(legMethod+"tauID('againstMuonLoose')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MuVetoTight"),
            method     = cms.string(legMethod+"tauID('againstMuonTight')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        )
    return sharedV

def eleCommon(src,legName,legMethod,pluginType):
    sharedV = cms.VPSet(
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Pt"),
           method     = cms.string(legMethod+"pt"),
           leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Eta"),
           method     = cms.string(legMethod+"eta"),
           leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Phi"),
           method     = cms.string(legMethod+"phi"),
           leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"elIso03B"),
            method     = cms.string("("+legMethod+"dr03TkSumPt()+max("+legMethod+"dr03EcalRecHitSumEt()-1.0,0.0)+"+legMethod+"dr03HcalTowerSumEt())/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelIso03E"),
            method     = cms.string("("+legMethod+"dr03TkSumPt()+"+legMethod+"dr03EcalRecHitSumEt()+"+legMethod+"dr03HcalTowerSumEt())/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"DcotTheta"),
            method     = cms.string(legMethod+'convDcot'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"ConvDistance"),
            method     = cms.string(legMethod+'convDist'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MissHits"),
            method     = cms.string(legMethod+'gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPFIso"),
            method     = cms.string('('+legMethod+"chargedHadronIso+"+legMethod+"photonIso+"+legMethod+"neutralHadronIso)/"+legMethod+'pt()'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"IP"),
            method     = cms.string(legMethod+'dB'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"WP80"),
            method     = cms.string(legMethod+'userFloat("wp80")'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"WP90"),
            method     = cms.string(legMethod+'userFloat("wp90")'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"CiCLoose"),
            method     = cms.string(legMethod+'electronID("cicLoose")'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"CiCTight"),
            method     = cms.string(legMethod+'electronID("cicTight")'),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPfIsoRho"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-"+legMethod+"userFloat('rho')*3.14*0.4*0.4,0.0))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"AbslPFIsoDB"),
            method     = cms.string("("+legMethod+"chargedHadronIso+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-0.5*"+legMethod+"userIso(0),0.0))"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPFIsoDB"),
            method     = cms.string("("+legMethod+"chargedHadronIso+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-0.5*"+legMethod+"userIso(0),0.0))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoEcaldR03"),
            method     = cms.string(legMethod+"dr03EcalRecHitSumEt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoEcal"),
            method     = cms.string(legMethod+"userIso(1)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoHcaldR03"),
            method     = cms.string(legMethod+"dr03HcalTowerSumEt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoHcal"),
            method     = cms.string(legMethod+"userIso(2)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoTk"),
            method     = cms.string(legMethod+"userIso(3)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"SIP"),
            method     = cms.string(legMethod+"userFloat('ip3DS')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dB"),
            method     = cms.string(legMethod+"userIso(0)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfChargedHad"),
            method     = cms.string(legMethod+"chargedHadronIso()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfNeutralHad"),
            method     = cms.string(legMethod+"neutralHadronIso()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfPhotonIso"),
            method     = cms.string(legMethod+"photonIso()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rhoZZ"),
            method     = cms.string(legMethod+"userFloat('zzRho')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rhoZZ2012"),
            method     = cms.string(legMethod+"userFloat('zzRho2012')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EAGamma04"),
            method     = cms.string(legMethod+"userFloat('EAGamma04')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EANeuHadron04"),
            method     = cms.string(legMethod+"userFloat('EANeuHadron04')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EAGammaNeuHadron04"),
            method     = cms.string(legMethod+"userFloat('EAGammaNeuHadron04')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso2012"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+legMethod+"photonIso()-"+legMethod+"userFloat('EAGammaNeuHadron04')*"+legMethod+"userFloat('zzRho2012')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+legMethod+"photonIso()-"+legMethod+"userFloat('EAGammaNeuHadron04')*"+legMethod+"userFloat('zzRho')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MITID"),
            method     = cms.string(legMethod+"userFloat('MITID')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MITpreID"),
            method     = cms.string(legMethod+"userFloat('MITpreID')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"mvaNonTrig"),
            method     = cms.string(legMethod+"electronID('mvaNonTrigV0')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"mvaNonTrigPass"),
            method     = cms.string(legMethod+"userFloat('mvaNonTrigV0Pass')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"isomva"),
            method     = cms.string(legMethod+"userFloat('isomva')"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"userIso0"),
            method     = cms.string(legMethod+"userIso(0)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"userIso1"),
            method     = cms.string(legMethod+"userIso(1)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"userIso2"),
            method     = cms.string(legMethod+"userIso(2)"),
            leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"isodmvaPass"),
            method     = cms.string(legMethod+"userFloat('isomvaPass')"),
            leadingOnly=cms.untracked.bool(True)
        )
        )
    return sharedV

def SCCommon(src,legName,legMethod,pluginType):
    sharedV = cms.VPSet(
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Pt"),
           method     = cms.string(legMethod+"pt"),
           leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Et"),
           method     = cms.string(legMethod+"et"),
           leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Eta"),
           method     = cms.string(legMethod+"eta"),
           leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Phi"),
           method     = cms.string(legMethod+"phi"),
           leadingOnly=cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "isEE"),
            method      = cms.string(legMethod + "isEE"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "isEB"),
            method      = cms.string(legMethod + "isEB"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "sigmaEtaEta"),
            method      = cms.string(legMethod + "sigmaEtaEta"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "sigmaIetaIeta"),
            method      = cms.string(legMethod + "sigmaIetaIeta"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "e1x5"),
            method      = cms.string(legMethod + "e1x5"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "e2x5"),
            method      = cms.string(legMethod + "e2x5"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "e3x3"),
            method      = cms.string(legMethod + "e3x3"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "e5x5"),
            method      = cms.string(legMethod + "e5x5"),
            leadingOnly = cms.untracked.bool(True)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "maxEnergyXtal"),
            method      = cms.string(legMethod + "maxEnergyXtal"),
            leadingOnly = cms.untracked.bool(True)
        )
        #cms.PSet(
        #    pluginType  = cms.string(pluginType),
        #    src         = cms.InputTag(src),
        #    tag         = cms.string(legName + "hcalDepth1OverEcal"),
        #    method      = cms.string(legMethod + "hcalDepth2OverEcal"),
        #    leadingOnly = cms.untracked.bool(True)
        #),
        #cms.PSet(
        #    pluginType  = cms.string(pluginType),
        #    src         = cms.InputTag(src),
        #    tag         = cms.string(legName + "hcalDepth1OverEcalBc"),
        #    method      = cms.string(legMethod + "hcalDepth2OverEcalBc"),
        #    leadingOnly = cms.untracked.bool(True)
        #)
        )
    return sharedV

def addMuMuTauTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold',MC=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zzCommon(src,'PATMuMuTauTauQuadFiller'),
        metShared = metCommon(src,'PATMuMuTauTauQuadFiller'),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #Candidate size quantities
        counters = countCommon(src,'PATMuMuTauTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuTauTauQuadFiller'),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuTauTauQuadFiller'),
        #tautau quantities
        z2l1 = tauCommon(src,'z2l1','leg2.leg1.','PATMuMuTauTauQuadFiller'),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATMuMuTauTauQuadFiller'),
        #       tautauShared = tauTauCommon(src,'PATMuMuTauTauQuadFiller'),
        #genShared = genCommon(src,'PATMuMuTauTauQuadFiller'),
        )
    if MC:
        eventTree.truth = cms.PSet(
                pluginType = cms.string("PATMuMuTauTauTruthFiller"),
                src        = cms.InputTag(src),
                gensrc        = cms.InputTag("genParticles"),
                tag        = cms.string("refitVertex"),
                method     = cms.string('1')
                )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)

#mumumumu tree
def addMuMuMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATMuMuMuMuQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        zzShared = zzCommon(src,'PATMuMuMuMuQuadFiller'),
        metShared = metCommon(src,'PATMuMuMuMuQuadFiller'),
        #genShared = genCommon(src,'PATMuMuMuMuQuadFiller'),
        counters = countCommon(src,'PATMuMuMuMuQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        #mumu1 quantities
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuMuMuQuadFiller'),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuMuMuQuadFiller'),
        z2l1 = muCommon(src,'z2l1','leg2.leg1.','PATMuMuMuMuQuadFiller'),
        z2l2 = muCommon(src,'z2l2','leg2.leg2.','PATMuMuMuMuQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATMuMuMuMuTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)


#mumumutau tree
def addMuMuMuTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATMuMuMuTauQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        zzShared = zzCommon(src,'PATMuMuMuTauQuadFiller'),
        metShared = metCommon(src,'PATMuMuMuTauQuadFiller'),
        #genShared = genCommon(src,'PATMuMuMuTauQuadFiller'),
        counters = countCommon(src,'PATMuMuMuTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        z1l1 = muCommon(src,"z1l1","leg1.leg1.",'PATMuMuMuTauQuadFiller'),
        z1l2 = muCommon(src,"z1l2","leg1.leg2.",'PATMuMuMuTauQuadFiller'),
        z2l1 = muCommon(src,"z2l1","leg2.leg1.",'PATMuMuMuTauQuadFiller'),
        z2l2 = tauCommon(src,"z2l2","leg2.leg2.",'PATMuMuMuTauQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATMuMuMuTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)


#mumuelectau tree
def addMuMuEleTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATMuMuEleTauQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        zzShared = zzCommon(src,'PATMuMuEleTauQuadFiller'),
        metShared = metCommon(src,'PATMuMuEleTauQuadFiller'),
        #genShared = genCommon(src,'PATMuMuEleTauQuadFiller'),
        #ZZ quantities
        counters = countCommon(src,'PATMuMuEleTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        #mumu quantities
#       mumuShared = muMuCommon(src,'PATMuMuEleTauQuadFiller'),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuEleTauQuadFiller'),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuEleTauQuadFiller'),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATMuMuEleTauQuadFiller'),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATMuMuEleTauQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATMuMuEleTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )

    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)
        
#mumuelemu tree
def addMuMuEleMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATMuMuEleMuQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        zzShared = zzCommon(src,'PATMuMuEleMuQuadFiller'),
        metShared = metCommon(src,'PATMuMuEleMuQuadFiller'),
        #genShared = genCommon(src,'PATMuMuEleMuQuadFiller'),
        counters = countCommon(src,'PATMuMuEleMuQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        #mumu quantities
#       mumuShared = muMuCommon(src,'PATMuMuEleMuQuadFiller'),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuEleMuQuadFiller'),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuEleMuQuadFiller'),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATMuMuEleMuQuadFiller'),
        z2l2 = muCommon(src,'z2l2','leg2.leg2.','PATMuMuEleMuQuadFiller'),
   )
   if MC:
       eventTree.truth = cms.PSet(
               pluginType = cms.string("PATMuMuEleMuTruthFiller"),
               src        = cms.InputTag(src),
               gensrc        = cms.InputTag("genParticles"),
               tag        = cms.string("refitVertex"),
               method     = cms.string('1')
               )
   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p) 

#mumueleele
def addMuMuEleEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATMuMuEleEleQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        zzShared = zzCommon(src,'PATMuMuEleEleQuadFiller'),
        metShared = metCommon(src,'PATMuMuEleEleQuadFiller'),
        #genShared = genCommon(src,'PATMuMuEleEleQuadFiller'),
        counters = countCommon(src,'PATMuMuEleEleQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        #mumu quantities
#       mumuShared = muMuCommon(src,'PATMuMuEleEleQuadFiller'),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuEleEleQuadFiller'),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuEleEleQuadFiller'),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATMuMuEleEleQuadFiller'),
        z2l2 = eleCommon(src,'z2l2','leg2.leg2.','PATMuMuEleEleQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATMuMuEleEleTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)


#eleeletautau
def addEleEleTauTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATEleEleTauTauQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        counters = countCommon(src,'PATEleEleTauTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        #ele ele quantities
        zzShared = zzCommon(src,'PATEleEleTauTauQuadFiller'),
        metShared = metCommon(src,'PATEleEleTauTauQuadFiller'),
        #genShared = genCommon(src,'PATEleEleTauTauQuadFiller'),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleTauTauQuadFiller'),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleTauTauQuadFiller'),
        z2l1 = tauCommon(src,'z2l1','leg2.leg1.','PATEleEleTauTauQuadFiller'),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATEleEleTauTauQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATEleEleTauTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)

#eleeleeletau
def addEleEleEleTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATEleEleEleTauQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        counters = countCommon(src,'PATEleEleEleTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        zzShared = zzCommon(src,'PATEleEleEleTauQuadFiller'),
        metShared = metCommon(src,'PATEleEleEleTauQuadFiller'),
        #genShared = genCommon(src,'PATEleEleEleTauQuadFiller'),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleTauQuadFiller'),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleTauQuadFiller'),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATEleEleEleTauQuadFiller'),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATEleEleEleTauQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATEleEleEleTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)
    
#eleelemutau
def addEleEleMuTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATEleEleMuTauQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        counters = countCommon(src,'PATEleEleMuTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        zzShared = zzCommon(src,'PATEleEleMuTauQuadFiller'),
        metShared = metCommon(src,'PATEleEleMuTauQuadFiller'),
        #genShared = genCommon(src,'PATEleEleMuTauQuadFiller'),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleMuTauQuadFiller'),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleMuTauQuadFiller'),
        z2l1 = muCommon(src,'z2l1','leg2.leg1.','PATEleEleMuTauQuadFiller'),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATEleEleMuTauQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATEleEleMuTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)
    
    
#eleeleelemu
def addEleEleEleMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATEleEleEleMuQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        counters = countCommon(src,'PATEleEleEleMuQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        zzShared = zzCommon(src,'PATEleEleEleMuQuadFiller'),
        metShared = metCommon(src,'PATEleEleEleMuQuadFiller'),
        #genShared = genCommon(src,'PATEleEleEleMuQuadFiller'),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleMuQuadFiller'),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleMuQuadFiller'),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATEleEleEleMuQuadFiller'),
        z2l2 = muCommon(src,'z2l2','leg2.leg2.','PATEleEleEleMuQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATEleEleEleMuTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)
    

#eleeleeleele
def addEleEleEleEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATEleEleEleEleQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        counters = countCommon(src,'PATEleEleEleEleQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        zzShared = zzCommon(src,'PATEleEleEleEleQuadFiller'),
        metShared = metCommon(src,'PATEleEleEleEleQuadFiller'),
        #genShared = genCommon(src,'PATEleEleEleEleQuadFiller'),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleEleQuadFiller'),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleEleQuadFiller'),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATEleEleEleEleQuadFiller'),
        z2l2 = eleCommon(src,'z2l2','leg2.leg2.','PATEleEleEleEleQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATEleEleEleEleTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)


def addEleEleMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
        #common quantities
        coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        JetsPt20 = cms.PSet(
            pluginType = cms.string("PATEleEleMuMuQuadJetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(True)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        Rho = cms.PSet(
            pluginType = cms.string("EventWeightFiller"),
            src        = cms.InputTag("kt6PFJets","rho"),
            tag        = cms.string("rho")
        ),
        #ZZ quantities
        counters = countCommon(src,'PATEleEleMuMuQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        zzShared = zzCommon(src,'PATEleEleMuMuQuadFiller'),
        metShared = metCommon(src,'PATEleEleMuMuQuadFiller'),
        #genShared = genCommon(src,'PATEleEleMuMuQuadFiller'),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleMuMuQuadFiller'),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleMuMuQuadFiller'),
        z2l1 = muCommon(src,'z2l1','leg2.leg1.','PATEleEleMuMuQuadFiller'),
        z2l2 = muCommon(src,'z2l2','leg2.leg2.','PATEleEleMuMuQuadFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATEleEleMuMuTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)


def addEleEleEleSCEventTree(process, name,
        src     = 'zzCleanedCandsAboveThreshold',
        srcEEEE = 'zzCleanedCandsAboveThreshold',
        srcEEMM = 'zzCleanedCandsAboveThreshold',
        srcMMEE = 'zzCleanedCandsAboveThreshold',
        srcMMMM = 'zzCleanedCandsAboveThreshold',
        MC      = False):

    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root"))
    
    eventTree = cms.EDAnalyzer('EventTreeMaker',
            coreCollections = cms.VInputTag( cms.InputTag(src) ),

            trigger = cms.PSet(
                pluginType  = cms.string("TriggerFiller"),
                src         = cms.InputTag("patTrigger"),
                paths       = cms.vstring(TriggerPaths)
                ),
            PVs = cms.PSet(
                pluginType  = cms.string("VertexSizeFiller"),
                src         = cms.InputTag("primaryVertexFilter"),
                tag         = cms.string("vertices")
                ),
            Rho = cms.PSet(
                pluginType  = cms.string("EventWeightFiller"),
                src         = cms.InputTag("kt6PFJets","rho"),
                tag         = cms.string("rho")
                ),
            # ZZ Quantities
            counters = countCommon(src,'PATEleEleEleSCQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
            zzShared = zzCommon(src,'PATEleEleEleSCQuadFiller'),
            metShared = metCommon(src,'PATEleEleEleSCQuadFiller'),

            z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleSCQuadFiller'),
            z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleSCQuadFiller'),
            z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATEleEleEleSCQuadFiller'),
            z2l2 =  SCCommon(src,'z2l2','leg2.leg2.','PATEleEleEleSCQuadFiller')
            )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name + 'Path', p)



def addMuMuEleSCEventTree(process, name,
        src     = 'zzCleanedCandsAboveThreshold',
        srcEEEE = 'zzCleanedCandsAboveThreshold',
        srcEEMM = 'zzCleanedCandsAboveThreshold',
        srcMMEE = 'zzCleanedCandsAboveThreshold',
        srcMMMM = 'zzCleanedCandsAboveThreshold',
        MC      = False):
    
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root"))

    eventTree = cms.EDAnalyzer('EventTreeMaker',
            coreCollections = cms.VInputTag( cms.InputTag(src) ),

            trigger = cms.PSet(
                pluginType  = cms.string("TriggerFiller"),
                src         = cms.InputTag("patTrigger"),
                paths       = cms.vstring(TriggerPaths)
                ),
            PVs = cms.PSet(
                pluginType  = cms.string("VertexSizeFiller"),
                src         = cms.InputTag("primaryVertexFilter"),
                tag         = cms.string("vertices")
                ),
            Rho = cms.PSet(
                pluginType  = cms.string("EventWeightFiller"),
                src         = cms.InputTag("kt6PFJets","rho"),
                tag         = cms.string("rho")
                ),
            # ZZ Quantities
            counters = countCommon(src,'PATMuMuEleSCQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
            zzShared = zzCommon(src,'PATMuMuEleSCQuadFiller'),
            metShared = metCommon(src,'PATMuMuEleSCQuadFiller'),

            z1l1 =  muCommon(src,'z1l1','leg1.leg1.','PATMuMuEleSCQuadFiller'),
            z1l2 =  muCommon(src,'z1l2','leg1.leg2.','PATMuMuEleSCQuadFiller'),
            z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATMuMuEleSCQuadFiller'),
            z2l2 =  SCCommon(src,'z2l2','leg2.leg2.','PATMuMuEleSCQuadFiller')
            )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process,name + 'Path',p)


def addMuMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zzCommon(src,'PATMuMuMuTriFiller'),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #Candidate size quantities
        counters = countCommon(src,'PATMuMuMuTri',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuMuTriFiller'),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuMuTriFiller'),
        z2l1 = muCommon(src,'z2l1','leg2.','PATMuMuMuTriFiller'),
        #       tautauShared = tauTauCommon(src,'PATMuMuMuTriFiller'),
#       #genShared = genCommon(src,'PATMuMuMuTriFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATMuMuTauTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)

def addMuMuEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zzCommon(src,'PATMuMuEleTriFiller'),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #Candidate size quantities
        counters = countCommon(src,'PATMuMuEleTri',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuEleTriFiller'),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuEleTriFiller'),
        z2l1 = eleCommon(src,'z2l1','leg2.','PATMuMuEleTriFiller'),
        #       tautauShared = tauTauCommon(src,'PATMuMuEleTriFiller'),
#       #genShared = genCommon(src,'PATMuMuEleTriFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATMuMuTauTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)

def addEleEleMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zzCommon(src,'PATEleEleMuTriFiller'),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #Candidate size quantities
        counters = countCommon(src,'PATEleEleMuTri',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleMuTriFiller'),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleMuTriFiller'),
        z2l1 = muCommon(src,'z2l1','leg2.','PATEleEleMuTriFiller'),
        #       tautauShared = tauTauCommon(src,'PATEleEleMuTriFiller'),
#       genShared = genCommon(src,'PATEleEleMuTriFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATMuMuTauTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)

def addEleEleEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EventTreeMaker',
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zzCommon(src,'PATEleEleEleTriFiller'),
        trigger = cms.PSet(
            pluginType = cms.string("TriggerFiller"),
            src        = cms.InputTag("patTrigger"),
            paths      = cms.vstring(TriggerPaths)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #Candidate size quantities
        counters = countCommon(src,'PATEleEleEleTri',srcEEEE,srcEEMM,srcMMEE,srcMMMM),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleTriFiller'),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleTriFiller'),
        z2l1 = eleCommon(src,'z2l1','leg2.','PATEleEleEleTriFiller'),
        #       tautauShared = tauTauCommon(src,'PATEleEleEleTriFiller'),
#       genShared = genCommon(src,'PATEleEleEleTriFiller'),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATMuMuTauTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),
            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)
