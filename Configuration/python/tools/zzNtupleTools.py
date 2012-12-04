from UWAnalysis.Configuration.tools.analysisTools import TriggerPaths
import FWCore.ParameterSet.Config as cms

def zzCommon(src,pluginType,leadOnly=True):
    sharedV = cms.VPSet(
            cms.PSet(
                pluginType = cms.string("PUFiller"),
                src        = cms.InputTag("addPileupInfo"),
                tag        = cms.string("pu"),
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mass"),
                method     = cms.string("mass()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("pt"),
                method     = cms.string("pt()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("charge"),
                method     = cms.string("charge()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Mass"),
                method     = cms.string("leg1.mass()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Mass"),
                method     = cms.string("leg2.mass()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("bestZmass"),
                method     = cms.string("bestZmass()"),
                leadingOnly= cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("subBestZmass"),
                method     = cms.string("subBestZmass()"),
                leadingOnly= cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Charge"),
                method     = cms.string("leg1.charge()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Charge"),
                method     = cms.string("leg2.charge()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Pt"),
                method     = cms.string("leg1.pt()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Pt"),
                method     = cms.string("leg2.pt()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Eta"),
                method     = cms.string("leg1.eta()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Eta"),
                method     = cms.string("leg2.eta()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Phi"),
                method     = cms.string("leg1.phi()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z2Phi"),
                method     = cms.string("leg2.phi()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("met"),
                method     = cms.string("met.pt()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("fourFour"),
                method     = cms.string("fourFour()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("sixSix"),
                method     = cms.string("sixSix()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("M12"),
                method     = cms.string("invM12()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("M13"),
                method     = cms.string("invM13()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("M14"),
                method     = cms.string("invM14()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("M23"),
                method     = cms.string("invM23()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("M24"),
                method     = cms.string("invM24()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("M34"),
                method     = cms.string("invM34()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("kd"),
                method     = cms.string("kd()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("psig"),
                method     = cms.string("psig()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("pbkg"),
                method     = cms.string("pbkg()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("kdPS"),
                method     = cms.string("kdPS()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("psigPS"),
                method     = cms.string("psigPS()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("pbkg"),
                method     = cms.string("pbkg()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("kdS2M"),
                method     = cms.string("kdS2M()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("psigS2M"),
                method     = cms.string("psigS2M()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("pbkg"),
                method     = cms.string("pbkg()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag      = cms.string("rho"),
                method     = cms.string('leg1.leg1.userFloat("rho")'),
                leadingOnly= cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag      = cms.string("z1l1PhotonIso"),
                method     = cms.string('leg1.leg1PhotonIso()'),
                leadingOnly= cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag      = cms.string("z1l2PhotonIso"),
                method     = cms.string('leg1.leg2PhotonIso()'),
                leadingOnly= cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag      = cms.string("z2l1PhotonIso"),
                method     = cms.string('leg2.leg1PhotonIso()'),
                leadingOnly= cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag      = cms.string("z2l2PhotonIso"),
                method     = cms.string('leg2.leg2PhotonIso()'),
                leadingOnly= cms.untracked.bool(leadOnly)
                ),
            )
    return sharedV

def fsrCommon(src,pluginType,leadOnly=True):
    sharedV = cms.VPSet(
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("massNoFSR"),
            method     = cms.string("massNoFSR()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z1MassNoFSR"),
            method     = cms.string("leg1.noPhoP4().M()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z2MassNoFSR"),
            method     = cms.string("leg2.noPhoP4().M()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z1phoEta"),
            method     = cms.string("leg1.phoEta()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z1phoPhi"),
            method     = cms.string("leg1.phoPhi()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z1phoLepDR"),
            method     = cms.string("leg1.lepDR()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z1phoLepPt"),
            method     = cms.string("leg1.lepPt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z1phoPt"),
            method     = cms.string("leg1.phoPt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z2phoEta"),
            method     = cms.string("leg2.phoEta()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z2phoPhi"),
            method     = cms.string("leg2.phoPhi()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z2phoLepDR"),
            method     = cms.string("leg2.lepDR()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z2phoLepPt"),
            method     = cms.string("leg2.lepPt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("z2phoPt"),
            method     = cms.string("leg2.phoPt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        )
    return sharedV

def anglesCommon(src,pluginType,leadOnly=True):
    sharedV = cms.VPSet(
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("costheta1"),
            method     = cms.string("costheta1()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("costheta2"),
            method     = cms.string("costheta2()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("Phi"),
            method     = cms.string("Phi()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("costhetaStar"),
            method     = cms.string("costhetaStar()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("phiStar1"),
            method     = cms.string("phiStar1()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("phiStar2"),
            method     = cms.string("phiStar2()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("phiStar12"),
            method     = cms.string("phiStar12()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("phi1"),
            method     = cms.string("phi1()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string("phi2"),
            method     = cms.string("phi2()"),
            leadingOnly=cms.untracked.bool(leadOnly)
            ),
        )
    return sharedV

def metCommon(src,pluginType,leadOnly=True):
    sharedV = cms.VPSet(
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mt"),
                method     = cms.string("mt12MET"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mt1"),
                method     = cms.string("mt1MET"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mt1_12"),
                method     = cms.string("leg1.mt12MET"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mt1_1"),
                method     = cms.string("leg1.mt1MET"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt1_2"),
                    method     = cms.string("leg1.mt2MET"),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt2"),
                    method     = cms.string("mt2MET"),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt2_12"),
                    method     = cms.string("leg2.mt12MET"),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt2_1"),
                    method     = cms.string("leg2.mt1MET"),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("mt2_2"),
                    method     = cms.string("leg2.mt2MET"),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("dZ12"),
                    method     = cms.string('leg1.dz'),
                    leadingOnly= cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("dZ13"),
                    method     = cms.string('abs(leg1.z1-leg2.z1)'),
                    leadingOnly= cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("dZ14"),
                    method     = cms.string('abs(leg1.z1-leg2.z2)'),
                    leadingOnly= cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("z1l1Z"),
                    method     = cms.string('leg1.z1'),
                    leadingOnly= cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("z1l2Z"),
                    method     = cms.string('leg1.z2'),
                    leadingOnly= cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("z2l1Z"),
                    method     = cms.string('leg2.z1'),
                    leadingOnly= cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag      = cms.string("z2l2Z"),
                    method     = cms.string('leg2.z2'),
                    leadingOnly= cms.untracked.bool(leadOnly)
                    ),
        )
    return sharedV

def genCommon(src,pluginType,leadOnly=True):
    sharedV = cms.VPSet(
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1l1GenPt"),
                method     = cms.string('leg1.p4VisLeg1gen().pt()'),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1l2GenPt"),
                method     = cms.string('leg1.p4VisLeg2gen().pt()'),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1GenPdgId"),
                method     = cms.string('genPdg1()'),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l2GenPdgId"),
                method     = cms.string('genPdg2()'),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1l1GenPdgId"),
                method     = cms.string('leg1.genPdg1()'),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l1l2GenPdgId"),
                method     = cms.string('leg1.genPdg2()'),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("l2l1GenPdgId"),
                method     = cms.string('leg2.genPdg1()'),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l2l2GenPdgId"),
                    method     = cms.string('leg2.genPdg2()'),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l1GenMass"),
                    method     = cms.string('leg1.p4VisGen().M()'),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l2l1GenPt"),
                    method     = cms.string('leg2.p4VisLeg1gen().pt()'),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l2l2GenPt"),
                    method     = cms.string('leg2.p4VisLeg2gen().pt()'),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("l2GenMass"),
                    method     = cms.string('leg2.p4VisGen().M()'),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    ),
            cms.PSet(
                    pluginType = cms.string(pluginType),
                    src        = cms.InputTag(src),
                    tag        = cms.string("GenMass"),
                    method     = cms.string('p4VisGen().M()'),
                    leadingOnly=cms.untracked.bool(leadOnly)
                    )
            )
    return sharedV

def countCommon(src, pluginType, srcEEEE, srcEEMM, srcMMEE, srcMMMM, leadOnly=True):
    sharedV = cms.VPSet(
        cms.PSet(
            pluginType = cms.string(pluginType+"JetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20"),
            method     = cms.string('pt()>20'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
#       cms.PSet(
#           pluginType = cms.string(pluginType+"JetCountFillerOL"),
#           src        = cms.InputTag(src),
#           tag        = cms.string("jetsPt20bLooseOL"),
#           method     = cms.string('pt()>20&&bDiscriminator("")>1.7&&abs(eta)<2.4'),
#           leadingOnly=cms.untracked.bool(leadOnly)
#       ),
#       cms.PSet(
#           pluginType = cms.string(pluginType+"JetCountFillerOL"),
#           src        = cms.InputTag(src),
#           tag        = cms.string("jetsPt20bMedOL"),
#           method     = cms.string('pt()>20&&bDiscriminator("")>3.3&&abs(eta)<2.4'),
#           leadingOnly=cms.untracked.bool(leadOnly)
#       ),
        cms.PSet(
            pluginType = cms.string(pluginType+"JetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20bLoose"),
            method     = cms.string('pt()>20&&bDiscriminator("")>1.7&&abs(eta)<2.4'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType+"JetCountFiller"),
            src        = cms.InputTag(src),
            tag        = cms.string("jetsPt20bMed"),
            method     = cms.string('pt()>20&&bDiscriminator("")>3.3&&abs(eta)<2.4'),
            leadingOnly=cms.untracked.bool(leadOnly)
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
            pluginType = cms.string("CollectionSizeFiller"),
            src        = cms.InputTag('gsfElectrons'),
            tag        = cms.string("gsfElectrons"),
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

def muCommon(src,legName,legMethod,pluginType,leadOnly=True):
    isoLeg=legMethod[:-1] # for photon iso, we access with leg1.leg1Photon() because of possible recovery of photon in FSR
    sharedV = cms.VPSet(
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Pt"),
            method     = cms.string(legMethod+"pt"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Eta"),
            method     = cms.string(legMethod+"eta"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Phi"),
            method     = cms.string(legMethod+"phi"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
#       cms.PSet(
#           pluginType = cms.string(pluginType),
#           src        = cms.InputTag(src),
#           tag        = cms.string(legName+"ValidMuonHits"),
#           method     = cms.string(legMethod+"globalTrack().hitPattern().numberOfValidMuonHits()"),
#           leadingOnly=cms.untracked.bool(leadOnly)
#       ),
#       cms.PSet(
#           pluginType = cms.string(pluginType),
#           src        = cms.InputTag(src),
#          tag        = cms.string(legName+"numMatches"),
#           method     = cms.string(legMethod+"numberOfMatches()"),
#           leadingOnly=cms.untracked.bool(leadOnly)
#       ),
#       cms.PSet(
#           pluginType = cms.string(pluginType),
#           src        = cms.InputTag(src),
#           tag        = cms.string(legName+"ValidHits"),
#           method     = cms.string(legMethod+"numberOfValidHits()"),
#           leadingOnly=cms.untracked.bool(leadOnly)
#       ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"isGlobal"),
            method     = cms.string(legMethod+"isGlobalMuon()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"isTracker"),
            method     = cms.string(legMethod+"isTrackerMuon()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
#       cms.PSet(
#           pluginType = cms.string(pluginType),
#           src        = cms.InputTag(src),
#           tag        = cms.string(legName+"NormChiSq"),
#           method     = cms.string(legMethod+"normChi2()"),
#           leadingOnly=cms.untracked.bool(leadOnly)
#       ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoEcaldR03"),
            method     = cms.string(legMethod+"isolationR03().emEt"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoEcal"),
            method     = cms.string(legMethod+"userIso(1)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoHcaldR03"),
            method     = cms.string(legMethod+"isolationR03().hadEt"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoHcal"),
            method     = cms.string(legMethod+"userIso(2)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoTk"),
            method     = cms.string(legMethod+"userIso(3)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPFIsoDB"),
            method     = cms.string("("+legMethod+"chargedHadronIso+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-0.5*"+legMethod+"userIso(0),0.0))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPfIsoRho"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-"+legMethod+"userFloat('rho')*3.14*0.4*0.4,0.0))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rho"),
            method     = cms.string(legMethod+"userFloat('rho')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"SIP"),
            method     = cms.string(legMethod+"userFloat('ip3DS')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dXY"),
            method     = cms.string(legMethod+"userFloat('ipDXY')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dz"),
            method     = cms.string(legMethod+"userFloat('dz')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dB"),
            method     = cms.string(legMethod+"userIso(0)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfChargedHad"),
            method     = cms.string(legMethod+"chargedHadronIso()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfNeutralHad"),
            method     = cms.string(legMethod+"neutralHadronIso()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfPhotonIso"),
            method     = cms.string(legMethod+"photonIso()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rhoZZ"),
            method     = cms.string(legMethod+"userFloat('zzRho')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rhoZZ2012"),
            method     = cms.string(legMethod+"userFloat('zzRho2012')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EAGamma04"),
            method     = cms.string(legMethod+"userFloat('EAGamma04')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EANeuHadron04"),
            method     = cms.string(legMethod+"userFloat('EANeuHadron04')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EAGammaNeuHadron04"),
            method     = cms.string(legMethod+"userFloat('EAGammaNeuHadron04')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso2012_noFSR"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+legMethod+"photonIso()-"+legMethod+"userFloat('effArea')*"+legMethod+"userFloat('zzRho2012')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso2012"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+isoLeg+"PhotonIso()-"+legMethod+"userFloat('effArea')*"+legMethod+"userFloat('zzRho2012')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+legMethod+"photonIso()-"+legMethod+"userFloat('effArea')*"+legMethod+"userFloat('zzRho')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"idMVA"),
            method     = cms.string(legMethod+"userFloat('idmva')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"isPF"),
            method=cms.string(legMethod+"pfCandidateRef.isNonnull()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        )
    return sharedV

def tauCommon(src,legName,legMethod,pluginType,leadOnly=True):
    sharedV = cms.VPSet(
        cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string(legName+"Eta"),
                method     = cms.string(legMethod+"eta"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
        cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string(legName+"Phi"),
                method     = cms.string(legMethod+"phi"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
        cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string(legName+"Pt"),
                method     = cms.string(legMethod+"pt"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
#        cms.PSet(
#                pluginType = cms.string(pluginType),
#                src        = cms.InputTag(src),
#                tag        = cms.string(legName+"JetPt"),
#                method     = cms.string(legMethod+"pfJetRef.pt"),
#                leadingOnly=cms.untracked.bool(leadOnly)
#                ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Prongs"),
            method     = cms.string(legMethod+"signalPFChargedHadrCands.size()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Gammas"),
            method     = cms.string(legMethod+"signalPFGammaCands.size()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"Mass"),
            method     = cms.string(legMethod+"mass()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"VLooseIso"),
            method     = cms.string(legMethod+"tauID('byVLooseIsolation')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"LooseIso"),
            method     = cms.string(legMethod+"tauID('byLooseIsolation')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MediumIso"),
            method     = cms.string(legMethod+"tauID('byMediumIsolation')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName+"QIso"),
            method      = cms.string(legMethod+"isolationPFChargedHadrCandsPtSum()"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName+"NIso"),
            method      = cms.string(legMethod+"isolationPFGammaCandsEtSum()"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName+"PUIso"),
            method      = cms.string(legMethod+"particleIso()"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"LooseIsoDB"),
            method     = cms.string(legMethod+"tauID('byLooseIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MediumIsoDB"),
            method     = cms.string(legMethod+"tauID('byMediumIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"LooseIsoCombDB"),
            method     = cms.string(legMethod+"tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MediumIsoCombDB"),
            method     = cms.string(legMethod+"tauID('byMediumCombinedIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"TightIsoCombDB"),
            method     = cms.string(legMethod+"tauID('byTightCombinedIsolationDeltaBetaCorr')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EleVeto"),
            method     = cms.string(legMethod+"tauID('againstElectronLoose')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MuVeto"),
            method     = cms.string(legMethod+"tauID('againstMuonLoose')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MuVetoTight"),
            method     = cms.string(legMethod+"tauID('againstMuonTight')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        )
    return sharedV

def eleCommon(src,legName,legMethod,pluginType,leadOnly=True):
    isoLeg=legMethod[:-1] # for photon iso, we access with leg1.leg1Photon() because of possible recovery of photon in FSR
    sharedV = cms.VPSet(
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Pt"),
           method     = cms.string(legMethod+"pt"),
           leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Eta"),
           method     = cms.string(legMethod+"eta"),
           leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Phi"),
           method     = cms.string(legMethod+"phi"),
           leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"elIso03B"),
            method     = cms.string("("+legMethod+"dr03TkSumPt()+max("+legMethod+"dr03EcalRecHitSumEt()-1.0,0.0)+"+legMethod+"dr03HcalTowerSumEt())/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelIso03E"),
            method     = cms.string("("+legMethod+"dr03TkSumPt()+"+legMethod+"dr03EcalRecHitSumEt()+"+legMethod+"dr03HcalTowerSumEt())/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"DcotTheta"),
            method     = cms.string(legMethod+'convDcot'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"ConvDistance"),
            method     = cms.string(legMethod+'convDist'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"MissHits"),
            method     = cms.string(legMethod+'gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPFIso"),
            method     = cms.string('('+legMethod+"chargedHadronIso+"+legMethod+"photonIso+"+legMethod+"neutralHadronIso)/"+legMethod+'pt()'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"IP"),
            method     = cms.string(legMethod+'dB'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"WP80"),
            method     = cms.string(legMethod+'userFloat("wp80")'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"WP90"),
            method     = cms.string(legMethod+'userFloat("wp90")'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"CiCLoose"),
            method     = cms.string(legMethod+'electronID("cicLoose")'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"CiCTight"),
            method     = cms.string(legMethod+'electronID("cicTight")'),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPfIsoRho"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-"+legMethod+"userFloat('rho')*3.14*0.4*0.4,0.0))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"AbslPFIsoDB"),
            method     = cms.string("("+legMethod+"chargedHadronIso+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-0.5*"+legMethod+"userIso(0),0.0))"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"RelPFIsoDB"),
            method     = cms.string("("+legMethod+"chargedHadronIso+max("+legMethod+"photonIso()+"+legMethod+"neutralHadronIso()-0.5*"+legMethod+"userIso(0),0.0))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoEcaldR03"),
            method     = cms.string(legMethod+"dr03EcalRecHitSumEt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoEcal"),
            method     = cms.string(legMethod+"userIso(1)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoHcaldR03"),
            method     = cms.string(legMethod+"dr03HcalTowerSumEt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoHcal"),
            method     = cms.string(legMethod+"userIso(2)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"StdIsoTk"),
            method     = cms.string(legMethod+"userIso(3)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dz"),
            method     = cms.string(legMethod+"userFloat('dz')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dXY"),
            method     = cms.string(legMethod+"userFloat('ipDXY')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"SIP"),
            method     = cms.string(legMethod+"userFloat('ip3DS')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"SIP"),
            method     = cms.string(legMethod+"userFloat('ip3DS')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"dB"),
            method     = cms.string(legMethod+"userIso(0)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfChargedHad"),
            method     = cms.string(legMethod+"chargedHadronIso()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfNeutralHad"),
            method     = cms.string(legMethod+"neutralHadronIso()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfPhotonIso"),
            method     = cms.string(legMethod+"photonIso()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rhoZZ"),
            method     = cms.string(legMethod+"userFloat('zzRho')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"rhoZZ2012"),
            method     = cms.string(legMethod+"userFloat('zzRho2012')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EAGamma04"),
            method     = cms.string(legMethod+"userFloat('EAGamma04')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EANeuHadron04"),
            method     = cms.string(legMethod+"userFloat('EANeuHadron04')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"EAGammaNeuHadron04"),
            method     = cms.string(legMethod+"userFloat('EAGammaNeuHadron04')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso2012_noFSR"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+legMethod+"photonIso()-"+legMethod+"userFloat('effArea')*"+legMethod+"userFloat('zzRho2012')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso2012"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+isoLeg+"PhotonIso()-"+legMethod+"userFloat('effArea')*"+legMethod+"userFloat('zzRho2012')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"pfCombIso"),
            method     = cms.string("("+legMethod+"chargedHadronIso()+max(0.0,"+legMethod+"neutralHadronIso()+"+legMethod+"photonIso()-"+legMethod+"userFloat('effArea')*"+legMethod+"userFloat('zzRho')))/"+legMethod+"pt()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"mvaNonTrig"),
            method     = cms.string(legMethod+"electronID('mvaNonTrigV0')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"mvaNonTrigPass"),
            method     = cms.string(legMethod+"userFloat('mvaNonTrigV0Pass')"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"r9"),
            method     = cms.string(legMethod+"r9()"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"userIso0"),
            method     = cms.string(legMethod+"userIso(0)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"userIso1"),
            method     = cms.string(legMethod+"userIso(1)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType = cms.string(pluginType),
            src        = cms.InputTag(src),
            tag        = cms.string(legName+"userIso2"),
            method     = cms.string(legMethod+"userIso(2)"),
            leadingOnly=cms.untracked.bool(leadOnly)
        ),
        )
    return sharedV

def SCCommon(src,legName,legMethod,pluginType,leadOnly=True):
    sharedV = cms.VPSet(
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Pt"),
           method     = cms.string(legMethod+"pt"),
           leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Et"),
           method     = cms.string(legMethod+"et"),
           leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Eta"),
           method     = cms.string(legMethod+"eta"),
           leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
           pluginType = cms.string(pluginType),
           src        = cms.InputTag(src),
           tag        = cms.string(legName+"Phi"),
           method     = cms.string(legMethod+"phi"),
           leadingOnly=cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "isEE"),
            method      = cms.string(legMethod + "isEE"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "isEB"),
            method      = cms.string(legMethod + "isEB"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "sigmaEtaEta"),
            method      = cms.string(legMethod + "sigmaEtaEta"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "sigmaIetaIeta"),
            method      = cms.string(legMethod + "sigmaIetaIeta"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "e1x5"),
            method      = cms.string(legMethod + "e1x5"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "e2x5"),
            method      = cms.string(legMethod + "e2x5"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "e3x3"),
            method      = cms.string(legMethod + "e3x3"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "e5x5"),
            method      = cms.string(legMethod + "e5x5"),
            leadingOnly = cms.untracked.bool(leadOnly)
        ),
        cms.PSet(
            pluginType  = cms.string(pluginType),
            src         = cms.InputTag(src),
            tag         = cms.string(legName + "maxEnergyXtal"),
            method      = cms.string(legMethod + "maxEnergyXtal"),
            leadingOnly = cms.untracked.bool(leadOnly)
        )
        #cms.PSet(
        #    pluginType  = cms.string(pluginType),
        #    src         = cms.InputTag(src),
        #    tag         = cms.string(legName + "hcalDepth1OverEcal"),
        #    method      = cms.string(legMethod + "hcalDepth2OverEcal"),
        #    leadingOnly = cms.untracked.bool(leadOnly)
        #),
        #cms.PSet(
        #    pluginType  = cms.string(pluginType),
        #    src         = cms.InputTag(src),
        #    tag         = cms.string(legName + "hcalDepth1OverEcalBc"),
        #    method      = cms.string(legMethod + "hcalDepth2OverEcalBc"),
        #    leadingOnly = cms.untracked.bool(leadOnly)
        #)
        )
    return sharedV

def zCommon(src,pluginType,leadOnly=True):
    sharedV = cms.VPSet(
            cms.PSet(
                pluginType = cms.string("PUFiller"),
                src        = cms.InputTag("addPileupInfo"),
                tag        = cms.string("pu"),
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("mass"),
                method     = cms.string("mass()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("pt"),
                method     = cms.string("pt()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("charge"),
                method     = cms.string("charge()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("met"),
                method     = cms.string("met.pt()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            )
    return sharedV

def zlCommon(src,pluginType,leadOnly=True):
    sharedV = cms.VPSet(
            cms.PSet(
                pluginType = cms.string("PUFiller"),
                src        = cms.InputTag("addPileupInfo"),
                tag        = cms.string("pu"),
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Mass"),
                method     = cms.string("leg1.mass()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Pt"),
                method     = cms.string("leg1.pt()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("z1Charge"),
                method     = cms.string("leg1.charge()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            cms.PSet(
                pluginType = cms.string(pluginType),
                src        = cms.InputTag(src),
                tag        = cms.string("met"),
                method     = cms.string("met.pt()"),
                leadingOnly=cms.untracked.bool(leadOnly)
                ),
            )
    return sharedV

def addMuMuTauTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold',MC=False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('MMTTEventTree',
            leadingOnly = cms.bool(leadingOnly),
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),

        zzShared = zzCommon(src,'PATMuMuTauTauQuadFiller',leadingOnly),
#        fsrShared = fsrCommon(src, 'PATMuMuTauTauQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src, 'PATMuMuTauTauQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATMuMuTauTauQuadFiller',leadingOnly),
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
        counters = countCommon(src,'PATMuMuTauTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuTauTauQuadFiller',leadingOnly),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuTauTauQuadFiller',leadingOnly),
        #tautau quantities
        z2l1 = tauCommon(src,'z2l1','leg2.leg1.','PATMuMuTauTauQuadFiller',leadingOnly),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATMuMuTauTauQuadFiller',leadingOnly),
        #       tautauShared = tauTauCommon(src,'PATMuMuTauTauQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATMuMuTauTauQuadFiller',leadingOnly),
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
def addMuMuMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('MMMMEventTree',
        leadingOnly = cms.bool(leadingOnly),
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
            leadingOnly=cms.untracked.bool(leadingOnly)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        zzShared = zzCommon(src,'PATMuMuMuMuQuadFiller',leadingOnly),
        fsrShared = fsrCommon(src, 'PATMuMuMuMuQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src, 'PATMuMuMuMuQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATMuMuMuMuQuadFiller'),
        #genShared = genCommon(src,'PATMuMuMuMuQuadFiller'),
        counters = countCommon(src,'PATMuMuMuMuQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        #mumu1 quantities
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuMuMuQuadFiller',leadingOnly),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuMuMuQuadFiller',leadingOnly),
        z2l1 = muCommon(src,'z2l1','leg2.leg1.','PATMuMuMuMuQuadFiller',leadingOnly),
        z2l2 = muCommon(src,'z2l2','leg2.leg2.','PATMuMuMuMuQuadFiller',leadingOnly),
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
def addMuMuMuTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('MMMTEventTree',
        leadingOnly=cms.bool(leadingOnly),
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
            leadingOnly=cms.untracked.bool(leadingOnly)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        #ZZ quantities
        zzShared = zzCommon(src,'PATMuMuMuTauQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATMuMuMuTauQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATMuMuMuTauQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src,'PATMuMuMuTauQuadFiller',leadingOnly),
        counters = countCommon(src,'PATMuMuMuTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        z1l1 = muCommon(src,"z1l1","leg1.leg1.",'PATMuMuMuTauQuadFiller',leadingOnly),
        z1l2 = muCommon(src,"z1l2","leg1.leg2.",'PATMuMuMuTauQuadFiller',leadingOnly),
        z2l1 = muCommon(src,"z2l1","leg2.leg1.",'PATMuMuMuTauQuadFiller',leadingOnly),
        z2l2 = tauCommon(src,"z2l2","leg2.leg2.",'PATMuMuMuTauQuadFiller',leadingOnly),
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
def addMuMuEleTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('MMETEventTree',
        leadingOnly=cms.bool(leadingOnly),
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
            leadingOnly=cms.untracked.bool(leadingOnly)
        ),
        PVs = cms.PSet(
            pluginType = cms.string("VertexSizeFiller"),
            src        = cms.InputTag("primaryVertexFilter"),
            tag        = cms.string("vertices")
        ),
        zzShared = zzCommon(src,'PATMuMuEleTauQuadFiller',leadingOnly),
#        fsrShared = fsrCommon(src, 'PATMuMuEleTauQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src,'PATMuMuEleTauQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATMuMuEleTauQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATMuMuEleTauQuadFiller',leadingOnly),
        #ZZ quantities
        counters = countCommon(src,'PATMuMuEleTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        #mumu quantities
#       mumuShared = muMuCommon(src,'PATMuMuEleTauQuadFiller',leadingOnly),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuEleTauQuadFiller',leadingOnly),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuEleTauQuadFiller',leadingOnly),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATMuMuEleTauQuadFiller',leadingOnly),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATMuMuEleTauQuadFiller',leadingOnly),
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
def addMuMuEleMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   eventTree = cms.EDAnalyzer('MMEMEventTree',
        leadingOnly=cms.bool(leadingOnly),
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
        zzShared = zzCommon(src,'PATMuMuEleMuQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATMuMuEleMuQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src,'PATMuMuEleMuQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATMuMuEleMuQuadFiller',leadingOnly),
        counters = countCommon(src,'PATMuMuEleMuQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        #mumu quantities
#       mumuShared = muMuCommon(src,'PATMuMuEleMuQuadFiller',leadingOnly),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuEleMuQuadFiller',leadingOnly),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuEleMuQuadFiller',leadingOnly),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATMuMuEleMuQuadFiller',leadingOnly),
        z2l2 = muCommon(src,'z2l2','leg2.leg2.','PATMuMuEleMuQuadFiller',leadingOnly),
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
def addMuMuEleEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('MMEEEventTree',
        #common quantities
        leadingOnly=cms.bool(leadingOnly),
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
        zzShared = zzCommon(src,'PATMuMuEleEleQuadFiller',leadingOnly),
        fsrShared = fsrCommon(src, 'PATMuMuEleEleQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src, 'PATMuMuEleEleQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATMuMuEleEleQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATMuMuEleEleQuadFiller',leadingOnly),
        counters = countCommon(src,'PATMuMuEleEleQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        #mumu quantities
#       mumuShared = muMuCommon(src,'PATMuMuEleEleQuadFiller',leadingOnly),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuEleEleQuadFiller',leadingOnly),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuEleEleQuadFiller',leadingOnly),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATMuMuEleEleQuadFiller',leadingOnly),
        z2l2 = eleCommon(src,'z2l2','leg2.leg2.','PATMuMuEleEleQuadFiller',leadingOnly),
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
def addEleEleTauTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EETTEventTree',
        leadingOnly=cms.bool(leadingOnly),
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
        counters = countCommon(src,'PATEleEleTauTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        #ele ele quantities
        zzShared = zzCommon(src,'PATEleEleTauTauQuadFiller',leadingOnly),
#        fsrShared = fsrCommon(src, 'PATEleEleTauTauQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src,'PATEleEleTauTauQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATEleEleTauTauQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATEleEleTauTauQuadFiller',leadingOnly),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleTauTauQuadFiller',leadingOnly),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleTauTauQuadFiller',leadingOnly),
        z2l1 = tauCommon(src,'z2l1','leg2.leg1.','PATEleEleTauTauQuadFiller',leadingOnly),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATEleEleTauTauQuadFiller',leadingOnly),
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
def addEleEleEleTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EEETEventTree',
        leadingOnly=cms.bool(leadingOnly),
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
        counters = countCommon(src,'PATEleEleEleTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        zzShared = zzCommon(src,'PATEleEleEleTauQuadFiller',leadingOnly),
#        fsrShared = fsrCommon(src, 'PATEleEleEleTauQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src,'PATEleEleEleTauQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATEleEleEleTauQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATEleEleEleTauQuadFiller',leadingOnly),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleTauQuadFiller',leadingOnly),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleTauQuadFiller',leadingOnly),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATEleEleEleTauQuadFiller',leadingOnly),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATEleEleEleTauQuadFiller',leadingOnly),
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
def addEleEleMuTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EEMTEventTree',
        leadingOnly=cms.bool(leadingOnly),
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
        counters = countCommon(src,'PATEleEleMuTauQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        zzShared = zzCommon(src,'PATEleEleMuTauQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATEleEleMuTauQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src,'PATEleEleMuTauQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATEleEleMuTauQuadFiller',leadingOnly),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleMuTauQuadFiller',leadingOnly),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleMuTauQuadFiller',leadingOnly),
        z2l1 = muCommon(src,'z2l1','leg2.leg1.','PATEleEleMuTauQuadFiller',leadingOnly),
        z2l2 = tauCommon(src,'z2l2','leg2.leg2.','PATEleEleMuTauQuadFiller',leadingOnly),
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
def addEleEleEleMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EEEMEventTree',
        leadingOnly=cms.bool(leadingOnly),
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
        counters = countCommon(src,'PATEleEleEleMuQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        zzShared = zzCommon(src,'PATEleEleEleMuQuadFiller',leadingOnly),
#        fsrShared = fsrCommon(src, 'PATEleEleEleMuQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src,'PATEleEleEleMuQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATEleEleEleMuQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATEleEleEleMuQuadFiller',leadingOnly),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleMuQuadFiller',leadingOnly),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleMuQuadFiller',leadingOnly),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATEleEleEleMuQuadFiller',leadingOnly),
        z2l2 = muCommon(src,'z2l2','leg2.leg2.','PATEleEleEleMuQuadFiller',leadingOnly),
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
def addEleEleEleEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EEEEEventTree',
        leadingOnly=cms.bool(leadingOnly),
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
        counters = countCommon(src,'PATEleEleEleEleQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        zzShared = zzCommon(src,'PATEleEleEleEleQuadFiller',leadingOnly),
        fsrShared = fsrCommon(src, 'PATEleEleEleEleQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src,'PATEleEleEleEleQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATEleEleEleEleQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATEleEleEleEleQuadFiller',leadingOnly),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleEleQuadFiller',leadingOnly),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleEleQuadFiller',leadingOnly),
        z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATEleEleEleEleQuadFiller',leadingOnly),
        z2l2 = eleCommon(src,'z2l2','leg2.leg2.','PATEleEleEleEleQuadFiller',leadingOnly),
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


def addEleEleMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EEMMEventTree',
        leadingOnly=cms.bool(leadingOnly),
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
        counters = countCommon(src,'PATEleEleMuMuQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        zzShared = zzCommon(src,'PATEleEleMuMuQuadFiller',leadingOnly),
        fsrShared = fsrCommon(src, 'PATEleEleMuMuQuadFiller',leadingOnly),
        anglesShared = anglesCommon(src,'PATEleEleMuMuQuadFiller',leadingOnly),
        metShared = metCommon(src,'PATEleEleMuMuQuadFiller',leadingOnly),
        #genShared = genCommon(src,'PATEleEleMuMuQuadFiller',leadingOnly),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleMuMuQuadFiller',leadingOnly),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleMuMuQuadFiller',leadingOnly),
        z2l1 = muCommon(src,'z2l1','leg2.leg1.','PATEleEleMuMuQuadFiller',leadingOnly),
        z2l2 = muCommon(src,'z2l2','leg2.leg2.','PATEleEleMuMuQuadFiller',leadingOnly),
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
        leadingOnly= False,
        src     = 'zzCleanedCandsAboveThreshold',
        srcEEEE = 'zzCleanedCandsAboveThreshold',
        srcEEMM = 'zzCleanedCandsAboveThreshold',
        srcMMEE = 'zzCleanedCandsAboveThreshold',
        srcMMMM = 'zzCleanedCandsAboveThreshold',
        MC      = False):

    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root"))

    eventTree = cms.EDAnalyzer('EventTreeMaker',
            leadingOnly=cms.untracked.bool(leadingOnly),
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
            counters = countCommon(src,'PATEleEleEleSCQuad',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
            zzShared = zzCommon(src,'PATEleEleEleSCQuadFiller',leadingOnly),
            metShared = metCommon(src,'PATEleEleEleSCQuadFiller',leadingOnly),

            z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleSCQuadFiller',leadingOnly),
            z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleSCQuadFiller',leadingOnly),
            z2l1 = eleCommon(src,'z2l1','leg2.leg1.','PATEleEleEleSCQuadFiller',leadingOnly),
            z2l2 =  SCCommon(src,'z2l2','leg2.leg2.','PATEleEleEleSCQuadFiller',leadingOnly)
            )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name + 'Path', p)



def addMuMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('MMMEventTree',
            leadingOnly=cms.bool(leadingOnly),
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zlCommon(src,'PATMuMuMuTriFiller'),
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
        counters = countCommon(src,'PATMuMuMuTri',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuMuTriFiller',leadingOnly),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuMuTriFiller',leadingOnly),
        z2l1 = muCommon(src,'z2l1','leg2.','PATMuMuMuTriFiller',leadingOnly),
        #       tautauShared = tauTauCommon(src,'PATMuMuMuTriFiller',leadingOnly),
#       #genShared = genCommon(src,'PATMuMuMuTriFiller',leadingOnly),
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

def addMuMuEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('MMEEventTree',
            leadingOnly=cms.bool(leadingOnly),
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zlCommon(src,'PATMuMuEleTriFiller',leadingOnly),
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
        counters = countCommon(src,'PATMuMuEleTri',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        z1l1 = muCommon(src,'z1l1','leg1.leg1.','PATMuMuEleTriFiller',leadingOnly),
        z1l2 = muCommon(src,'z1l2','leg1.leg2.','PATMuMuEleTriFiller',leadingOnly),
        z2l1 = eleCommon(src,'z2l1','leg2.','PATMuMuEleTriFiller',leadingOnly),
        #       tautauShared = tauTauCommon(src,'PATMuMuEleTriFiller',leadingOnly),
#       #genShared = genCommon(src,'PATMuMuEleTriFiller',leadingOnly),
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

def addEleEleMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EEMEventTree',
            leadingOnly=cms.bool(leadingOnly),
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zlCommon(src,'PATEleEleMuTriFiller',leadingOnly),
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
        counters = countCommon(src,'PATEleEleMuTri',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleMuTriFiller',leadingOnly),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleMuTriFiller',leadingOnly),
        z2l1 = muCommon(src,'z2l1','leg2.','PATEleEleMuTriFiller',leadingOnly),
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

def addEleEleEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False,leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EEEEventTree',
            leadingOnly=cms.bool(leadingOnly),
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zlCommon(src,'PATEleEleEleTriFiller'),
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
        counters = countCommon(src,'PATEleEleEleTri',srcEEEE,srcEEMM,srcMMEE,srcMMMM,leadingOnly),
        z1l1 = eleCommon(src,'z1l1','leg1.leg1.','PATEleEleEleTriFiller',leadingOnly),
        z1l2 = eleCommon(src,'z1l2','leg1.leg2.','PATEleEleEleTriFiller',leadingOnly),
        z2l1 = eleCommon(src,'z2l1','leg2.','PATEleEleEleTriFiller',leadingOnly),
        #       tautauShared = tauTauCommon(src,'PATEleEleEleTriFiller',leadingOnly),
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

def addEleEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False, leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('EEEventTree',
            leadingOnly=cms.bool(leadingOnly),
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zCommon(src,'PATElePairFiller'),
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
        z1l1 = eleCommon(src,'l1','leg1.','PATElePairFiller',leadingOnly),
        z1l2 = eleCommon(src,'l2','leg2.','PATElePairFiller',leadingOnly),
    )
    if MC:
        eventTree.truth = cms.PSet(
            pluginType = cms.string("PATMuMuTauTauTruthFiller"),
            src        = cms.InputTag(src),
            gensrc        = cms.InputTag("genParticles"),
            tag        = cms.string("refitVertex"),            method     = cms.string('1')
        )
    setattr(process, name, eventTree)
    p = cms.Path(getattr(process,name))
    setattr(process, name+'Path', p)

def addMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold', srcEEEE='zzCleanedCandsAboveThreshold', srcEEMM='zzCleanedCandsAboveThreshold', srcMMEE='zzCleanedCandsAboveThreshold', srcMMMM='zzCleanedCandsAboveThreshold', MC = False, leadingOnly=False):
    process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
    eventTree = cms.EDAnalyzer('MMEventTree',
            leadingOnly=cms.bool(leadingOnly),
            coreCollections = cms.VInputTag(
            cms.InputTag(src)
        ),
        zzShared = zCommon(src,'PATMuPairFiller'),
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
        z1l1 = muCommon(src,'l1','leg1.','PATMuPairFiller',leadingOnly),
        z1l2 = muCommon(src,'l2','leg2.','PATMuPairFiller',leadingOnly),
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
