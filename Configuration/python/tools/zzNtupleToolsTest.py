from UWAnalysis.Configuration.tools.analysisTools import TriggerPaths
import FWCore.ParameterSet.Config as cms
#mumutautau tree
def addMuMuTauTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
	eventTree = cms.EDAnalyzer('EventTreeMaker',
		coreCollections = cms.VInputTag(
			cms.InputTag(src)
		),
     	trigger = cms.PSet(
			pluginType = cms.string("TriggerFiller"),
			src        = cms.InputTag("patTrigger"),
			paths      = cms.vstring(TriggerPaths)
		),
		JetsPt20 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadJetCountFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("jetsPt20"),
			method     = cms.string('pt()>20'),
			leadingOnly=cms.untracked.bool(True)
		),
		MET = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("MuMuTauTauVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#mumu quantities
		mumuSIPtest = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1SIPTest"),
			method     = cms.string("leg1.leg1.userFloat('SIP3D')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Pt"),
			method     = cms.string("leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuCharge = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuMass = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1isTracker"),
			method     = cms.string("leg1.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2isTracker"),
			method     = cms.string("leg1.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Pt"),
			method     = cms.string("leg1.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Pt"),
			method     = cms.string("leg1.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Eta"),
			method     = cms.string("leg1.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Eta"),
			method     = cms.string("leg1.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Phi"),
			method     = cms.string("leg1.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Phi"),
			method     = cms.string("leg1.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidMuonHits1"),
			method     = cms.string("leg1.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidMuonHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidMuonHits"),
			method     = cms.string("leg1.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1numMatches1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1numMatches"),
			method     = cms.string("leg1.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1numMatches2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2numMatches"),
			method     = cms.string("leg1.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidHits"),
			method     = cms.string("leg1.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidHits"),
			method     = cms.string("leg1.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1NormChiSq"),
			method     = cms.string("leg1.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2NormChiSq"),
			method     = cms.string("leg1.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1StandardRelIso"),
			method     = cms.string("(leg1.leg1.isolationR03.sumPt+leg1.leg1.isolationR03.emEt+leg1.leg1.isolationR03.hadEt)/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2StandardRelIso"),
			method     = cms.string("(leg1.leg2.isolationR03.sumPt+leg1.leg2.isolationR03.emEt+leg1.leg2.isolationR03.hadEt)/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso())/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso())/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mumuPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuTauTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	mumuPFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATMuMuTauTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		mumuVBTFID1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1VBTFID"),
			method     = cms.string("leg1.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuVBTFID2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2VBTFID"),
			method     = cms.string("leg1.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		#tautau quantities
		tautaupt = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Pt"),
			method     = cms.string("leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauCharge = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMass = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
			),
		tautaueta1 = cms.PSet(
				pluginType = cms.string("PATMuMuTauTauQuadFiller"),
				src        = cms.InputTag(src),
				tag        = cms.string("z2l1Eta"),
				method     = cms.string("leg2.leg1.eta"),
				leadingOnly=cms.untracked.bool(True)
				),
		tautaueta2 = cms.PSet(
				pluginType = cms.string("PATMuMuTauTauQuadFiller"),
				src        = cms.InputTag(src),
				tag        = cms.string("z2l2Eta"),
				method     = cms.string("leg2.leg2.eta"),
				leadingOnly=cms.untracked.bool(True)
				),
		tautaupt1 = cms.PSet(
				pluginType = cms.string("PATMuMuTauTauQuadFiller"),
				src        = cms.InputTag(src),
				tag        = cms.string("z2l1Pt"),
				method     = cms.string("leg2.leg1.pt"),
				leadingOnly=cms.untracked.bool(True)
				),
		tautaupt2 = cms.PSet(
				pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Pt"),
			method     = cms.string("leg2.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaujetpt1 = cms.PSet(
				pluginType = cms.string("PATMuMuTauTauQuadFiller"),
				src        = cms.InputTag(src),
				tag        = cms.string("z2l1JetPt"),
				method     = cms.string("leg2.leg1.pfJetRef.pt"),
				leadingOnly=cms.untracked.bool(True)
				),
		tautaujetpt2 = cms.PSet(
				pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2JetPt"),
			method     = cms.string("leg2.leg2.pfJetRef.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauprongs1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Prongs"),
			method     = cms.string("leg2.leg1.signalPFChargedHadrCands.size()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauprongs2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Prongs2"),
			method     = cms.string("leg2.leg2.signalPFChargedHadrCands.size()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauGammas1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Gammas"),
			method     = cms.string('leg2.leg1.signalPFGammaCands.size()'),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauGammas2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Gammas"),
			method     = cms.string('leg2.leg2.signalPFGammaCands.size()'),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaumass1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Mass"),
			method     = cms.string("leg2.leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaumass2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Mass"),
			method     = cms.string("leg2.leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauDecayFound1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1DecayFinding"),
			method     = cms.string('leg2.leg1.tauID("decayModeFinding")'),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauDecayFound2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2DecayFinding"),
			method     = cms.string('leg2.leg2.tauID("decayModeFinding")'),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauVLooseIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1VLooseIso"),
			method     = cms.string("leg2.leg1.tauID('byVLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauVLooseIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIso"),
			method     = cms.string("leg2.leg2.tauID('byVLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1LooseIso"),
			method     = cms.string("leg2.leg1.tauID('byLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIso"),
			method     = cms.string("leg2.leg2.tauID('byLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MediumIso"),
			method     = cms.string("leg2.leg1.tauID('byMediumIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MediumIso"),
			method     = cms.string("leg2.leg2.tauID('byMediumIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    tautauAbsIsoRho1 = cms.PSet(
			  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l1AbsIsoRho"),
			  method     = cms.string('leg2.leg1.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg1.isolationPFGammaCandsEtSum()-leg2.leg1.userFloat("rho")*3.14*0.5*0.5)'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    tautauAbsIso1 = cms.PSet(
			  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l1AbsIso"),
			  method     = cms.string('leg2.leg1.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg1.isolationPFGammaCandsEtSum())'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    tautauAbsIsoRho2 = cms.PSet(
			  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIsoRho"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-leg2.leg2.userFloat("rho")*3.14*0.5*0.5)'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    tautauAbsIso2 = cms.PSet(
			  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIso"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum())'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
     	tautauAbsIsoDB1 = cms.PSet(
			  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			  src        = cms.InputTag(src),
		      tag        = cms.string("z2l1AbsIsoDeltaBeta"),
		      method     = cms.string('leg2.leg1.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg1.isolationPFGammaCandsEtSum()-0.35*leg2.leg1.particleIso())'),
		 	  leadingOnly=cms.untracked.bool(True)
	    ),
     	tautauAbsIsoDB2 = cms.PSet(
			  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			  src        = cms.InputTag(src),
		      tag        = cms.string("z2l2AbsIsoDeltaBeta"),
		      method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-0.35*leg2.leg2.particleIso())'),
		 	  leadingOnly=cms.untracked.bool(True)
	    ),
	    tautauQIso1 = cms.PSet(
	    	pluginType  = cms.string("PATMuMuTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l1QIso"),
	    	method		= cms.string('leg2.leg1.isolationPFChargedHadrCandsPtSum()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauQIso2 = cms.PSet(
	    	pluginType  = cms.string("PATMuMuTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l2QIso"),
	    	method		= cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauNIso1 = cms.PSet(
	    	pluginType  = cms.string("PATMuMuTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l1NIso"),
	    	method		= cms.string('leg2.leg1.isolationPFGammaCandsEtSum()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauNIso2 = cms.PSet(
	    	pluginType  = cms.string("PATMuMuTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l2NIso"),
	    	method		= cms.string('leg2.leg2.isolationPFGammaCandsEtSum()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauPUIso1 = cms.PSet(
	    	pluginType  = cms.string("PATMuMuTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l1PUIso"),
	    	method		= cms.string('leg2.leg1.particleIso()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauPUIso2 = cms.PSet(
	    	pluginType  = cms.string("PATMuMuTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l2PUIso"),
	    	method		= cms.string('leg2.leg2.particleIso()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
		tautauLooseIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1LooseIsoDB"),
			method     = cms.string("leg2.leg1.tauID('byLooseIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIsoDB"),
			method     = cms.string("leg2.leg2.tauID('byLooseIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MediumIsoDB"),
			method     = cms.string("leg2.leg1.tauID('byMediumIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MediumIsoDB"),
			method     = cms.string("leg2.leg2.tauID('byMediumIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIsoCombDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1LooseIsoCombDB"),
			method     = cms.string("leg2.leg1.tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIsoCombDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIsoCombDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MediumIsoCombDB"),
			method     = cms.string("leg2.leg1.tauID('byMediumCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIsoCombDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MediumIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byMediumCombinedIsolationDeltaBetaCorr')"),
		),
		tautauTightIsoCombDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1TightIsoCombDB"),
			method     = cms.string("leg2.leg1.tauID('byTightCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauTightIsoCombDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2TightIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byTightCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauEleVeto1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1EleVeto"),
			method     = cms.string("leg2.leg1.tauID('againstElectronLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauEleVeto2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2EleVeto"),
			method     = cms.string("leg2.leg2.tauID('againstElectronLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMuVeto1 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MuVeto"),
			method     = cms.string("leg2.leg1.tauID('againstMuonLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMuVeto2 = cms.PSet(
			pluginType = cms.string("PATMuMuTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MuVeto"),
			method     = cms.string("leg2.leg2.tauID('againstMuonLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuTauTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)

#mumumumu tree
def addMuMuMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("MuMuMuMuVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#mumu1 quantities
		mumu1pt = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Pt"),
			method     = cms.string("leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1Charge = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1Mass = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1isTracker1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1isTracker"),
			method     = cms.string("leg1.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1isTracker2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2isTracker"),
			method     = cms.string("leg1.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1pt1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Pt"),
			method     = cms.string("leg1.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1pt2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Pt"),
			method     = cms.string("leg1.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1eta1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Eta"),
			method     = cms.string("leg1.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1eta2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Eta"),
			method     = cms.string("leg1.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1phi1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Phi"),
			method     = cms.string("leg1.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1phi2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Phi"),
			method     = cms.string("leg1.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidMuonHits1"),
			method     = cms.string("leg1.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidMuonHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidMuonHits"),
			method     = cms.string("leg1.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1numMatches1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1numMatches"),
			method     = cms.string("leg1.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1numMatches2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2numMatches"),
			method     = cms.string("leg1.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidHits1"),
			method     = cms.string("leg1.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidHits"),
			method     = cms.string("leg1.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1NormChiSq1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1NormChiSq"),
			method     = cms.string("leg1.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1NormChiSq2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2NormChiSq"),
			method     = cms.string("leg1.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1RelStdIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1StandardRelIso"),
			method     = cms.string("(leg1.leg1.isolationR03.sumPt+leg1.leg1.isolationR03.emEt+leg1.leg1.isolationR03.hadEt)/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1RelStdIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2StandardRelIso"),
			method     = cms.string("(leg1.leg2.isolationR03.sumPt+leg1.leg2.isolationR03.emEt+leg1.leg2.isolationR03.hadEt)/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1AbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1AbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1RelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1RelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1RelPFIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso())/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1RelPFIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso())/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mumu1PFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	mumu1PFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		mumu1VBTFID1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1VBTFID"),
			method     = cms.string("leg1.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1VBTFID2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2VBTFID"),
			method     = cms.string("leg1.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		#mumu2 quantities
		mumu2pt = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Pt"),
			method     = cms.string("leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2Charge = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2Mass = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2isTracker1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1isTracker"),
			method     = cms.string("leg2.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2isTracker2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2isTracker"),
			method     = cms.string("leg2.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2pt1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Pt"),
			method     = cms.string("leg2.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2pt2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Pt"),
			method     = cms.string("leg2.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2eta1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Eta"),
			method     = cms.string("leg2.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2eta2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Eta"),
			method     = cms.string("leg2.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2phi1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Phi"),
			method     = cms.string("leg2.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2phi2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Phi"),
			method     = cms.string("leg2.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2ValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidMuonHits1"),
			method     = cms.string("leg2.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2ValidMuonHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ValidMuonHits"),
			method     = cms.string("leg2.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2numMatches1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1numMatches"),
			method     = cms.string("leg2.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2numMatches2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2numMatches"),
			method     = cms.string("leg2.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2ValidHits1 = cms.PSet(

			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidHits"),
			method     = cms.string("leg2.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2ValidHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ValidHits"),
			method     = cms.string("leg2.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2NormChiSq1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1NormChiSq"),
			method     = cms.string("leg2.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2NormChiSq2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2NormChiSq"),
			method     = cms.string("leg2.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2RelStdIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1StandardRelIso"),
			method     = cms.string("(leg2.leg1.isolationR03.sumPt+leg2.leg1.isolationR03.emEt+leg2.leg1.isolationR03.hadEt)/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2RelStdIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2StandardRelIso"),
			method     = cms.string("(leg2.leg2.isolationR03.sumPt+leg2.leg2.isolationR03.emEt+leg2.leg2.isolationR03.hadEt)/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2AbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2AbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2AbsPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2RelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2RelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2RelPFIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso())/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2RelPFIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIso"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso())/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mumu2PFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	mumu2PFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l2RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-leg2.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		mumu2VBTFID1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("zz2l1VBTFID"),
			method     = cms.string("leg2.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2VBTFID2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("zz2l2VBTFID"),
			method     = cms.string("leg2.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuMuMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)


#mumumutau tree
def addMuMuMuTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("MuMuMuTauVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#mumu quantities
		mumupt = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Pt"),
			method     = cms.string("leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuCharge = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuMass = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1isTracker"),
			method     = cms.string("leg1.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2isTracker"),
			method     = cms.string("leg1.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Pt"),
			method     = cms.string("leg1.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Pt"),
			method     = cms.string("leg1.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Eta"),
			method     = cms.string("leg1.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Eta"),
			method     = cms.string("leg1.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Phi"),
			method     = cms.string("leg1.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Phi"),
			method     = cms.string("leg1.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidMuonHits1"),
			method     = cms.string("leg1.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidMuonHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidMuonHits"),
			method     = cms.string("leg1.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumunumMatches1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1numMatches"),
			method     = cms.string("leg1.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumunumMatches2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2numMatches"),
			method     = cms.string("leg1.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidHits"),
			method     = cms.string("leg1.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidHits"),
			method     = cms.string("leg1.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1NormChiSq"),
			method     = cms.string("leg1.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2NormChiSq"),
			method     = cms.string("leg1.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1StandardRelIso"),
			method     = cms.string("(leg1.leg1.isolationR03.sumPt+leg1.leg1.isolationR03.emEt+leg1.leg1.isolationR03.hadEt)/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2StandardRelIso"),
			method     = cms.string("(leg1.leg2.isolationR03.sumPt+leg1.leg2.isolationR03.emEt+leg1.leg2.isolationR03.hadEt)/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso())/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso())/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mumuPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	mumuPFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		mumuVBTFID1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1VBTFID"),
			method     = cms.string("leg1.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuVBTFID2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2VBTFID"),
			method     = cms.string("leg1.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		#mutau quantities
#		muTauSVFit = cms.PSet(
#				pluginType = cms.string("PATMMMTSVFitFiller"),
#				src        = cms.InputTag(src),
#				tag        = cms.string("sv_")
#				),
		mutaupt = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Pt"),
			method     = cms.string("leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauCharge = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauMass = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaupt1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Pt"),
			method     = cms.string("leg2.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaupt2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Pt"),
			method     = cms.string("leg2.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaujetpt2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2JetPt"),
			method     = cms.string("leg2.leg2.pfJetRef.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaueta1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Eta"),
			method     = cms.string("leg2.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaueta2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Eta"),
			method     = cms.string("leg2.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauphi1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Phi"),
			method     = cms.string("leg2.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauphi2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Phi"),
			method     = cms.string("leg2.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
	#mu-specific
		mutauisTracker= cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1isTracker"),
			method     = cms.string("leg2.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauValidMuonHits = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidMuonHits1"),
			method     = cms.string("leg2.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaunumMatches = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1numMatches"),
			method     = cms.string("leg2.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauValidHits = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidHits"),
			method     = cms.string("leg2.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauNormChiSq = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1NormChiSq"),
			method     = cms.string("leg2.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauRelStdIso = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1StandardRelIso"),
			method     = cms.string("(leg2.leg1.isolationR03.sumPt+leg2.leg1.isolationR03.emEt+leg2.leg1.isolationR03.hadEt)/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauAbsPFIsoDB = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauRelPFIsoDB = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauRelPFIso = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso())/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mutauPFRelIsoRho = cms.PSet(
		  	pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		mutauVBTFID = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1VBTFID"),
			method     = cms.string("leg2.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		#tau-specific
		mutauprongs = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Prongs"),
			method     = cms.string("leg2.leg2.signalPFChargedHadrCands.size()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauGammas = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Gammas"),
			method     = cms.string('leg2.leg2.signalPFGammaCands.size()'),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaumass = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Mass"),
			method     = cms.string("leg2.leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauDecayFound = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2DecayFinding"),
			method     = cms.string('leg2.leg2.tauID("decayModeFinding")'),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauVLooseIso = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIso"),
			method     = cms.string("leg2.leg2.tauID('byVLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauLooseIso = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIso"),
			method     = cms.string("leg2.leg2.tauID('byLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		
	    mutauAbsIsoRho = cms.PSet(
			  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIsoRho"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-leg2.leg2.userFloat("rho")*3.14*0.5*0.5)'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    mutauAbsIso = cms.PSet(
			  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIso"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum())'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
     	mutauAbsIsoDB2 = cms.PSet(
			  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			  src        = cms.InputTag(src),
		      tag        = cms.string("z2l2AbsIsoDeltaBeta"),
		      method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-0.35*leg2.leg2.particleIso())'),
		 	  leadingOnly=cms.untracked.bool(True)
	    ),
		mutauLooseIsoCombDB = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauVLooseIsoCombDB = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byVLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauEleVeto = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2EleVeto"),
			method     = cms.string("leg2.leg2.tauID('againstElectronLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauMuVeto = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MuVeto"),
			method     = cms.string("leg2.leg2.tauID('againstMuonLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauMuVetoTight = cms.PSet(
			pluginType = cms.string("PATMuMuMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MuVetoTight"),
			method     = cms.string("leg2.leg2.tauID('againstMuonTight')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuMuTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)


#mumuelectau tree
def addMuMuEleTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("MuMuEleTauVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		SIP3Dtest1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("sip3deletest"),
			method     = cms.string("leg2.leg1.userFloat('SIP3D')"),
			leadingOnly=cms.untracked.bool(True)
		),
		SIP3Dtest2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("sip3dmutest"),
			method     = cms.string("leg1.leg1.userFloat('SIP3D')"),
			leadingOnly=cms.untracked.bool(True)
		),
		Mass = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#mumu quantities
		mumupt = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Pt"),
			method     = cms.string("leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuCharge = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuMass = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1isTracker"),
			method     = cms.string("leg1.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2isTracker"),
			method     = cms.string("leg1.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Pt"),
			method     = cms.string("leg1.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Pt"),
			method     = cms.string("leg1.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Eta"),
			method     = cms.string("leg1.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Eta"),
			method     = cms.string("leg1.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Phi"),
			method     = cms.string("leg1.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Phi"),
			method     = cms.string("leg1.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidMuonHits1"),
			method     = cms.string("leg1.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidMuonHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidMuonHits"),
			method     = cms.string("leg1.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumunumMatches1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1numMatches"),
			method     = cms.string("leg1.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumunumMatches2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2numMatches"),
			method     = cms.string("leg1.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidHits"),
			method     = cms.string("leg1.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidHits"),
			method     = cms.string("leg1.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1NormChiSq"),
			method     = cms.string("leg1.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2NormChiSq"),
			method     = cms.string("leg1.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1StandardRelIso"),
			method     = cms.string("(leg1.leg1.isolationR03.sumPt+leg1.leg1.isolationR03.emEt+leg1.leg1.isolationR03.hadEt)/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2StandardRelIso"),
			method     = cms.string("(leg1.leg2.isolationR03.sumPt+leg1.leg2.isolationR03.emEt+leg1.leg2.isolationR03.hadEt)/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		deltaB = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("DB"),
			method     = cms.string("leg1.leg2.userIso(0)"),
			leadingOnly=cms.untracked.bool(True)
		),
		rho = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("rho"),
			method     = cms.string("leg1.leg2.userFloat('rho')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso())/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso())/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mumuPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	mumuPFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		mumuVBTFID1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1VBTFID"),
			method     = cms.string("leg1.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuVBTFID2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2VBTFID"),
			method     = cms.string("leg1.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		#ele tau quantities
		eletaupt = cms.PSet(
		   pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2Pt"),
		   method     = cms.string("leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletauCharge = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauMass = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletaupt1 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Pt"),
		   method     = cms.string("leg2.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletaupt2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Pt"),
		   method     = cms.string("leg2.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletaujetpt2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2JetPt"),
		   method     = cms.string("leg2.leg2.pfJetRef.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletaueta1 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Eta"),
		   method     = cms.string("leg2.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletaueta2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Eta"),
		   method     = cms.string("leg2.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletauphi1 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Phi"),
		   method     = cms.string("leg2.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletauphi2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Phi"),
		   method     = cms.string("leg2.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleTauRelIso03B = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03B"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+max(leg2.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleTauRelIso03E = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03E"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+leg2.leg1.dr03EcalRecHitSumEt()+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleTauDCotTheta = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1DcotTheta"),
			method     = cms.string('leg2.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauConvDist = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ConvDistance"),
			method     = cms.string('leg2.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauMissHits = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MissHits"),
			method     = cms.string('leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauPFRelIso = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string('(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso+leg2.leg1.neutralHadronIso)/leg2.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eleTauPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eleTauAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
     	eletauAbsIsoDB2 = cms.PSet(
			  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			  src        = cms.InputTag(src),
		      tag        = cms.string("z2l2AbsIsoDeltaBeta"),
		      method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-0.35*leg2.leg2.particleIso())'),
		 	  leadingOnly=cms.untracked.bool(True)
	    ),
		eletauLooseIsoCombDB = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauVLooseIsoCombDB = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byVLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauEleIP = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1IP"),
			method     = cms.string('leg2.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauWP80 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP80"),
			method     = cms.string('leg2.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauWP90 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP90"),
			method     = cms.string('leg2.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauCiCLoose = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCLoose"),
			method     = cms.string('leg2.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauCiCMedium = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCMedium"),
			method     = cms.string('leg2.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauCiCTight = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCTight"),
			method     = cms.string('leg2.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauCiCSuperTight = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCSuperTight"),
			method     = cms.string('leg2.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleTauCiCHyperTight1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCHyperTight1"),
			method     = cms.string('leg2.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		#tau-specific
		eletauprongs = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Prongs"),
			method     = cms.string("leg2.leg2.signalPFChargedHadrCands.size()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauGammas = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Gammas"),
			method     = cms.string('leg2.leg2.signalPFGammaCands.size()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletaumass = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Mass"),
			method     = cms.string("leg2.leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauDecayFound = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2DecayFinding"),
			method     = cms.string('leg2.leg2.tauID("decayModeFinding")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauVLooseIso = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIso"),
			method     = cms.string("leg2.leg2.tauID('byVLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauLooseIso = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIso"),
			method     = cms.string("leg2.leg2.tauID('byLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    eletauAbsIsoRho = cms.PSet(
			  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIsoRho"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-leg2.leg2.userFloat("rho")*3.14*0.5*0.5)'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    eletauAbsIso = cms.PSet(
			  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIso"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum())'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
		eletauEleVeto = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2EleVeto"),
			method     = cms.string("leg2.leg2.tauID('againstElectronLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauEleVetoMedium = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2EleVetoMedium"),
			method     = cms.string("leg2.leg2.tauID('againstElectronMedium')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauMuVeto = cms.PSet(
			pluginType = cms.string("PATMuMuEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MuVeto"),
			method     = cms.string("leg2.leg2.tauID('againstMuonLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuEleTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)

	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)
		
#mumuelemu tree
def addMuMuEleMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("MuMuEleMuVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#mumu quantities
		eleMuEta = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Eta"),
			method     = cms.string("leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuPhi = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Phi"),
			method     = cms.string("leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuEta = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Eta"),
			method     = cms.string("leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuPhi = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Phi"),
			method     = cms.string("leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Pt"),
			method     = cms.string("leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuCharge = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuMass = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1isTracker"),
			method     = cms.string("leg1.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2isTracker"),
			method     = cms.string("leg1.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Pt"),
			method     = cms.string("leg1.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Pt"),
			method     = cms.string("leg1.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Eta"),
			method     = cms.string("leg1.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Eta"),
			method     = cms.string("leg1.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Phi"),
			method     = cms.string("leg1.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Phi"),
			method     = cms.string("leg1.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidMuonHits"),
			method     = cms.string("leg1.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidMuonHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidMuonHits"),
			method     = cms.string("leg1.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumunumMatches1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1numMatches"),
			method     = cms.string("leg1.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumunumMatches2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2numMatches"),
			method     = cms.string("leg1.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidHits1"),
			method     = cms.string("leg1.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidHits"),
			method     = cms.string("leg1.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1NormChiSq"),
			method     = cms.string("leg1.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2NormChiSq"),
			method     = cms.string("leg1.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1StandardRelIso"),
			method     = cms.string("(leg1.leg1.isolationR03.sumPt+leg1.leg1.isolationR03.emEt+leg1.leg1.isolationR03.hadEt)/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2StandardRelIso"),
			method     = cms.string("(leg1.leg2.isolationR03.sumPt+leg1.leg2.isolationR03.emEt+leg1.leg2.isolationR03.hadEt)/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso())/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso())/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mumuPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	mumuPFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		mumuVBTFID1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1VBTFID"),
			method     = cms.string("leg1.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuVBTFID2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2VBTFID"),
			method     = cms.string("leg1.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		#ele mu quantities
		elemupt = cms.PSet(
		   pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2Pt"),
		   method     = cms.string("leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemuCharge = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuMass = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemupt1 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Pt"),
		   method     = cms.string("leg2.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemupt2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Pt"),
		   method     = cms.string("leg2.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemueta1 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Eta"),
		   method     = cms.string("leg2.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemueta2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Eta"),
		   method     = cms.string("leg2.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemuphi1 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Phi"),
		   method     = cms.string("leg2.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemuphi2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Phi"),
		   method     = cms.string("leg2.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		elemuRelIso03B = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03B"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+max(leg2.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		elemuRelIso03E = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03E"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+leg2.leg1.dr03EcalRecHitSumEt()+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		elemuDCotTheta = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1DcotTheta"),
			method     = cms.string('leg2.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuConvDist = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ConvDistance"),
			method     = cms.string('leg2.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuMissHits = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MissHits"),
			method     = cms.string('leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuPFRelIso = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string('(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso+leg2.leg1.neutralHadronIso)/leg2.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuEleIP = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1IP"),
			method     = cms.string('leg2.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuWP80 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP80"),
			method     = cms.string('leg2.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuWP90 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP90"),
			method     = cms.string('leg2.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCLoose = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCLoose"),
			method     = cms.string('leg2.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCMedium = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCMedium"),
			method     = cms.string('leg2.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCTight = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCTight"),
			method     = cms.string('leg2.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCSuperTight = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCSuperTight"),
			method     = cms.string('leg2.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCHyperTight1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCHyperTight1"),
			method     = cms.string('leg2.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		#mu-specific
		elemuisTracker= cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2isTracker"),
			method     = cms.string("leg2.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuValidMuonHits = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ValidMuonHits"),
			method     = cms.string("leg2.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemunumMatches = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2numMatches"),
			method     = cms.string("leg2.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuValidHits = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ValidHits"),
			method     = cms.string("leg2.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuNormChiSq = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2NormChiSq"),
			method     = cms.string("leg2.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuRelStdIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2StandardRelIso2"),
			method     = cms.string("(leg2.leg2.isolationR03.sumPt+leg2.leg2.isolationR03.emEt+leg2.leg2.isolationR03.hadEt)/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2AbsPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuRelPFIso = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIso2"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso())/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	elemuPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	elemuPFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l2RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-leg2.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  
		elemuVBTFID = cms.PSet(
			pluginType = cms.string("PATMuMuEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VBTFID"),
			method     = cms.string("leg2.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuEleMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
   )
   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)	

#mumueleele
def addMuMuEleEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("MuMuEleEleVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#mumu quantities
		mumupt = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Pt"),
			method     = cms.string("leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuCharge = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuMass = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1isTracker"),
			method     = cms.string("leg1.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2isTracker"),
			method     = cms.string("leg1.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Pt"),
			method     = cms.string("leg1.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Pt"),
			method     = cms.string("leg1.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Eta"),
			method     = cms.string("leg1.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Eta"),
			method     = cms.string("leg1.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Phi"),
			method     = cms.string("leg1.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Phi"),
			method     = cms.string("leg1.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidMuonHits1"),
			method     = cms.string("leg1.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidMuonHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidMuonHits"),
			method     = cms.string("leg1.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1numMatches1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1numMatches"),
			method     = cms.string("leg1.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1numMatches2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2numMatches"),
			method     = cms.string("leg1.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidHits"),
			method     = cms.string("leg1.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidHits"),
			method     = cms.string("leg1.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1NormChiSq"),
			method     = cms.string("leg1.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2NormChiSq"),
			method     = cms.string("leg1.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1StandardRelIso"),
			method     = cms.string("(leg1.leg1.isolationR03.sumPt+leg1.leg1.isolationR03.emEt+leg1.leg1.isolationR03.hadEt)/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2StandardRelIso"),
			method     = cms.string("(leg1.leg2.isolationR03.sumPt+leg1.leg2.isolationR03.emEt+leg1.leg2.isolationR03.hadEt)/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso())/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso())/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mumuPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	mumuPFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		mumuVBTFID1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1VBTFID"),
			method     = cms.string("leg1.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuVBTFID2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2VBTFID"),
			method     = cms.string("leg1.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		#ele ele quantities
		eleelept = cms.PSet(
		   pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2Pt"),
		   method     = cms.string("leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleCharge = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMass = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelept1 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Pt"),
		   method     = cms.string("leg2.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelept2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Pt"),
		   method     = cms.string("leg2.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta1 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Eta"),
		   method     = cms.string("leg2.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Eta"),
		   method     = cms.string("leg2.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi1 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Phi"),
		   method     = cms.string("leg2.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi2 = cms.PSet(
		   pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Phi"),
		   method     = cms.string("leg2.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleeleRelIso03B1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03B"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+max(leg2.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03E"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+leg2.leg1.dr03EcalRecHitSumEt()+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1DcotTheta"),
			method     = cms.string('leg2.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ConvDistance"),
			method     = cms.string('leg2.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MissHits"),
			method     = cms.string('leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string('(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso+leg2.leg1.neutralHadronIso)/leg2.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1IP"),
			method     = cms.string('leg2.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP801 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP80"),
			method     = cms.string('leg2.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP901 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP90"),
			method     = cms.string('leg2.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCLoose"),
			method     = cms.string('leg2.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCMedium"),
			method     = cms.string('leg2.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCTight"),
			method     = cms.string('leg2.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCSuperTight"),
			method     = cms.string('leg2.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCHyperTight1"),
			method     = cms.string('leg2.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03B2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelIso03B"),
			method     = cms.string("(leg2.leg2.dr03TkSumPt()+max(leg2.leg2.dr03EcalRecHitSumEt()-1.0,0.0)+leg2.leg2.dr03HcalTowerSumEt())/leg2.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelIso03E"),
			method     = cms.string("(leg2.leg2.dr03TkSumPt()+leg2.leg2.dr03EcalRecHitSumEt()+leg2.leg2.dr03HcalTowerSumEt())/leg2.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2DcotTheta"),
			method     = cms.string('leg2.leg2.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ConvDistance"),
			method     = cms.string('leg2.leg2.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MissHits"),
			method     = cms.string('leg2.leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIso"),
			method     = cms.string('(leg2.leg2.chargedHadronIso+leg2.leg2.photonIso+leg2.leg2.neutralHadronIso)/leg2.leg2.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eleelePFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	eleelePFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l2RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-leg2.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eleeleAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2AbsPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2IP"),
			method     = cms.string('leg2.leg2.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP802 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2WP80"),
			method     = cms.string('leg2.leg2.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP902 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2WP90"),
			method     = cms.string('leg2.leg2.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCLoose"),
			method     = cms.string('leg2.leg2.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCMedium"),
			method     = cms.string('leg2.leg2.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCTight"),
			method     = cms.string('leg2.leg2.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight2 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCSuperTight"),
			method     = cms.string('leg2.leg2.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight12 = cms.PSet(
			pluginType = cms.string("PATMuMuEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCHyperTight1"),
			method     = cms.string('leg2.leg2.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATMuMuEleEleQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)


#eleeletautau
def addEleEleTauTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("EleEleTauTauVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#ele ele quantities
		eleelept = cms.PSet(
		   pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1Pt"),
		   method     = cms.string("leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleCharge = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMass = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelept1 = cms.PSet(
		   pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Pt"),
		   method     = cms.string("leg1.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelept2 = cms.PSet(
		   pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Pt"),
		   method     = cms.string("leg1.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta1 = cms.PSet(
		   pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Eta"),
		   method     = cms.string("leg1.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta2 = cms.PSet(
		   pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Eta"),
		   method     = cms.string("leg1.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi1 = cms.PSet(
		   pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Phi"),
		   method     = cms.string("leg1.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi2 = cms.PSet(
		   pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Phi"),
		   method     = cms.string("leg1.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleeleRelIso03B1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1elIso03B"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+max(leg1.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03E"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+leg1.leg1.dr03EcalRecHitSumEt()+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1DcotTheta"),
			method     = cms.string('leg1.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ConvDistance"),
			method     = cms.string('leg1.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1MissHits"),
			method     = cms.string('leg1.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string('(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso+leg1.leg1.neutralHadronIso)/leg1.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1IP"),
			method     = cms.string('leg1.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP801 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP80"),
			method     = cms.string('leg1.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP901 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP90"),
			method     = cms.string('leg1.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCLoose"),
			method     = cms.string('leg1.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCMedium"),
			method     = cms.string('leg1.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCTight"),
			method     = cms.string('leg1.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCSuperTight"),
			method     = cms.string('leg1.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCHyperTight1"),
			method     = cms.string('leg1.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03B2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03B"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+max(leg1.leg2.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03E"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+leg1.leg2.dr03EcalRecHitSumEt()+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2DcotTheta"),
			method     = cms.string('leg1.leg2.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ConvDistance"),
			method     = cms.string('leg1.leg2.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2MissHits"),
			method     = cms.string('leg1.leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string('(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso+leg1.leg2.neutralHadronIso)/leg1.leg2.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eleelePFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	eleelePFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eleeleAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbslPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2IP"),
			method     = cms.string('leg1.leg2.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP802 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP80"),
			method     = cms.string('leg1.leg2.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP902 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP90"),
			method     = cms.string('leg1.leg2.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCLoose"),
			method     = cms.string('leg1.leg2.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCMedium"),
			method     = cms.string('leg1.leg2.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCTight"),
			method     = cms.string('leg1.leg2.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCSuperTight"),
			method     = cms.string('leg1.leg2.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight12 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCHyperTight1"),
			method     = cms.string('leg1.leg2.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		#tautau quantities
		tautaupt = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Pt"),
			method     = cms.string("leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauCharge = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMass = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaupt1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Pt"),
			method     = cms.string("leg2.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaupt2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Pt"),
			method     = cms.string("leg2.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaujetpt1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1JetPt"),
			method     = cms.string("leg2.leg1.pfJetRef.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaujetpt2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2JetPt"),
			method     = cms.string("leg2.leg2.pfJetRef.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaueta1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Eta"),
			method     = cms.string("leg2.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaueta2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Eta"),
			method     = cms.string("leg2.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauphi1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Phi"),
			method     = cms.string("leg2.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauphi2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Phi"),
			method     = cms.string("leg2.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauprongs1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Prongs"),
			method     = cms.string("leg2.leg1.signalPFChargedHadrCands.size()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauprongs2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Prongs"),
			method     = cms.string("leg2.leg2.signalPFChargedHadrCands.size()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauGammas1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Gammas"),
			method     = cms.string('leg2.leg1.signalPFGammaCands.size()'),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauGammas2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Gammas"),
			method     = cms.string('leg2.leg2.signalPFGammaCands.size()'),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaumass1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Mass"),
			method     = cms.string("leg2.leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautaumass2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Mass"),
			method     = cms.string("leg2.leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauDecayFound1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1DecayFinding"),
			method     = cms.string('leg2.leg1.tauID("decayModeFinding")'),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauDecayFound2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2DecayFinding"),
			method     = cms.string('leg2.leg2.tauID("decayModeFinding")'),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauVLooseIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1VLooseIso"),
			method     = cms.string("leg2.leg1.tauID('byVLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauVLooseIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIso"),
			method     = cms.string("leg2.leg2.tauID('byVLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1LooseIso"),
			method     = cms.string("leg2.leg1.tauID('byLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIso"),
			method     = cms.string("leg2.leg2.tauID('byLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MediumIso"),
			method     = cms.string("leg2.leg1.tauID('byMediumIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MediumIso"),
			method     = cms.string("leg2.leg2.tauID('byMediumIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    tautauAbsIsoRho1 = cms.PSet(
			  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l1AbsIsoRho"),
			  method     = cms.string('leg2.leg1.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg1.isolationPFGammaCandsEtSum()-leg2.leg1.userFloat("rho")*3.14*0.5*0.5)'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    tautauAbsIso1 = cms.PSet(
			  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l1AbsIso"),
			  method     = cms.string('leg2.leg1.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg1.isolationPFGammaCandsEtSum())'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    tautauAbsIsoRho2 = cms.PSet(
			  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIsoRho"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-leg2.leg2.userFloat("rho")*3.14*0.5*0.5)'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    tautauAbsIso2 = cms.PSet(
			  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIso"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum())'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
     	tautauAbsIsoDB1 = cms.PSet(
			  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			  src        = cms.InputTag(src),
		      tag        = cms.string("z2l1AbsIsoDeltaBeta"),
		      method     = cms.string('leg2.leg1.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg1.isolationPFGammaCandsEtSum()-0.35*leg2.leg1.particleIso())'),
		 	  leadingOnly=cms.untracked.bool(True)
	    ),
     	tautauAbsIsoDB2 = cms.PSet(
			  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			  src        = cms.InputTag(src),
		      tag        = cms.string("z2l2AbsIsoDeltaBeta"),
		      method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-0.35*leg2.leg2.particleIso())'),
		 	  leadingOnly=cms.untracked.bool(True)
	    ),
	    tautauQIso1 = cms.PSet(
	    	pluginType  = cms.string("PATEleEleTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l1QIso"),
	    	method		= cms.string('leg2.leg1.isolationPFChargedHadrCandsPtSum()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauQIso2 = cms.PSet(
	    	pluginType  = cms.string("PATEleEleTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l2QIso"),
	    	method		= cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauNIso1 = cms.PSet(
	    	pluginType  = cms.string("PATEleEleTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l1NIso"),
	    	method		= cms.string('leg2.leg1.isolationPFGammaCandsEtSum()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauNIso2 = cms.PSet(
	    	pluginType  = cms.string("PATEleEleTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l2NIso"),
	    	method		= cms.string('leg2.leg2.isolationPFGammaCandsEtSum()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauPUIso1 = cms.PSet(
	    	pluginType  = cms.string("PATEleEleTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l1PUIso"),
	    	method		= cms.string('leg2.leg1.particleIso()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
	    tautauPUIso2 = cms.PSet(
	    	pluginType  = cms.string("PATEleEleTauTauQuadFiller"),
	    	src		    = cms.InputTag(src),
	    	tag			= cms.string("z2l2PUIso"),
	    	method		= cms.string('leg2.leg2.particleIso()'),
	    	leadingOnly	= cms.untracked.bool(True)
	    ),
		tautauLooseIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1LooseIsoDB"),
			method     = cms.string("leg2.leg1.tauID('byLooseIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIsoDB"),
			method     = cms.string("leg2.leg2.tauID('byLooseIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MediumIsoDB"),
			method     = cms.string("leg2.leg1.tauID('byMediumIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MediumIsoDB"),
			method     = cms.string("leg2.leg2.tauID('byMediumIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIsoCombDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1LooseIsoCombDB"),
			method     = cms.string("leg2.leg1.tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauLooseIsoCombDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIsoCombDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MediumIsoCombDB"),
			method     = cms.string("leg2.leg1.tauID('byMediumCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMediumIsoCombDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MediumIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byMediumCombinedIsolationDeltaBetaCorr')"),
		),
		tautauTightIsoCombDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1TightIsoCombDB"),
			method     = cms.string("leg2.leg1.tauID('byTightCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauTightIsoCombDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2TightIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byTightCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauEleVeto1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1EleVeto"),
			method     = cms.string("leg2.leg1.tauID('againstElectronLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauEleVeto2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2EleVeto"),
			method     = cms.string("leg2.leg2.tauID('againstElectronLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMuVeto1 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MuVeto"),
			method     = cms.string("leg2.leg1.tauID('againstMuonLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		tautauMuVeto2 = cms.PSet(
			pluginType = cms.string("PATEleEleTauTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MuVeto"),
			method     = cms.string("leg2.leg2.tauID('againstMuonLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleTauTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)

#eleeleeletau
def addEleEleEleTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("EleEleEleTauVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#ele ele quantities
		eleelept = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1Pt"),
		   method     = cms.string("leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleCharge = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMass = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelept1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Pt"),
		   method     = cms.string("leg1.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelept2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Pt"),
		   method     = cms.string("leg1.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Eta"),
		   method     = cms.string("leg1.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Eta"),
		   method     = cms.string("leg1.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Phi"),
		   method     = cms.string("leg1.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Phi2"),
		   method     = cms.string("leg1.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleeleRelIso03B1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03B"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+max(leg1.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03E"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+leg1.leg1.dr03EcalRecHitSumEt()+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1DcotTheta"),
			method     = cms.string('leg1.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ConvDistance"),
			method     = cms.string('leg1.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1MissHits"),
			method     = cms.string('leg1.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string('(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso+leg1.leg1.neutralHadronIso)/leg1.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1IP"),
			method     = cms.string('leg1.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP801 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP80"),
			method     = cms.string('leg1.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP901 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP90"),
			method     = cms.string('leg1.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCLoose"),
			method     = cms.string('leg1.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCMedium"),
			method     = cms.string('leg1.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCTight"),
			method     = cms.string('leg1.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCSuperTight"),
			method     = cms.string('leg1.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCHyperTight1"),
			method     = cms.string('leg1.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03B2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03B"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+max(leg1.leg2.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03E"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+leg1.leg2.dr03EcalRecHitSumEt()+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2DcotTheta"),
			method     = cms.string('leg1.leg2.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ConvDistance"),
			method     = cms.string('leg1.leg2.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2MissHits"),
			method     = cms.string('leg1.leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string('(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso+leg1.leg2.neutralHadronIso)/leg1.leg2.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eleelePFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	eleelePFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eleeleAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2IP"),
			method     = cms.string('leg1.leg2.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP802 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP802"),
			method     = cms.string('leg1.leg2.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP902 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP90"),
			method     = cms.string('leg1.leg2.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCLoose"),
			method     = cms.string('leg1.leg2.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCMedium"),
			method     = cms.string('leg1.leg2.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCTight"),
			method     = cms.string('leg1.leg2.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCSuperTight"),
			method     = cms.string('leg1.leg2.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight12 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCHyperTight1"),
			method     = cms.string('leg1.leg2.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		#ele tau quantities
		eletaupt = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2Pt"),
		   method     = cms.string("leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletauCharge = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauMass = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletaupt1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Pt"),
		   method     = cms.string("leg2.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletaupt2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Pt"),
		   method     = cms.string("leg2.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletaujetpt2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2JetPt"),
		   method     = cms.string("leg2.leg2.pfJetRef.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletaueta1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Eta"),
		   method     = cms.string("leg2.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletaueta2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Eta"),
		   method     = cms.string("leg2.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletauphi1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Phi"),
		   method     = cms.string("leg2.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eletauphi2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Phi"),
		   method     = cms.string("leg2.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eletauRelIso03B = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03B"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+max(leg2.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eletauRelIso03E = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03E"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+leg2.leg1.dr03EcalRecHitSumEt()+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eletauDCotTheta = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1DcotTheta"),
			method     = cms.string('leg2.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauConvDist = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ConvDistance"),
			method     = cms.string('leg2.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauMissHits = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MissHits"),
			method     = cms.string('leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauPFRelIso = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string('(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso+leg2.leg1.neutralHadronIso)/leg2.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eletauPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eletauAbsPFIsoDB = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauRelPFIsoDB = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauEleIP = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1IP"),
			method     = cms.string('leg2.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauWP80 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP80"),
			method     = cms.string('leg2.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauWP90 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP90"),
			method     = cms.string('leg2.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauCiCLoose = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCLoose"),
			method     = cms.string('leg2.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauCiCMedium = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCMedium"),
			method     = cms.string('leg2.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauCiCTight = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCTight"),
			method     = cms.string('leg2.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauCiCSuperTight = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCSuperTight"),
			method     = cms.string('leg2.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauCiCHyperTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCHyperTight1"),
			method     = cms.string('leg2.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		#tau-specific
		eletauprongs = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Prongs"),
			method     = cms.string("leg2.leg2.signalPFChargedHadrCands.size()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauGammas = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Gammas"),
			method     = cms.string('leg2.leg2.signalPFGammaCands.size()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletaumass = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2TauMass"),
			method     = cms.string("leg2.leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauDecayFound = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2DecayFinding"),
			method     = cms.string('leg2.leg2.tauID("decayModeFinding")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauVLooseIso = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIso"),
			method     = cms.string("leg2.leg2.tauID('byVLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauLooseIso = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIso"),
			method     = cms.string("leg2.leg2.tauID('byLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    eletauAbsIsoRho = cms.PSet(
			  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIsoRho"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-leg2.leg2.userFloat("rho")*3.14*0.5*0.5)'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    eletauAbsIso = cms.PSet(
			  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIso"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum())'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
     	eletauAbsIsoDB2 = cms.PSet(
			  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			  src        = cms.InputTag(src),
		      tag        = cms.string("z2l2AbsIsoDeltaBeta"),
		      method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-0.35*leg2.leg2.particleIso())'),
		 	  leadingOnly=cms.untracked.bool(True)
	    ),
		eletauLooseIsoCombDB = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauVLooseIsoCombDB = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byVLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauEleVeto = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2EleVeto"),
			method     = cms.string("leg2.leg2.tauID('againstElectronLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauEleVetoMedium = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2EleVetoMedium"),
			method     = cms.string("leg2.leg2.tauID('againstElectronMedium')"),
			leadingOnly=cms.untracked.bool(True)
		),
		eletauMuVeto = cms.PSet(
			pluginType = cms.string("PATEleEleEleTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MuVeto"),
			method     = cms.string("leg2.leg2.tauID('againstMuonLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleEleTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)
	
#eleelemutau
def addEleEleMuTauEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("EleEleMuTauVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#ele ele quantities
		eleelept = cms.PSet(
		   pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1Pt"),
		   method     = cms.string("leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleCharge = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMass = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelept1 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Pt"),
		   method     = cms.string("leg1.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelept2 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Pt"),
		   method     = cms.string("leg1.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta1 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Eta"),
		   method     = cms.string("leg1.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta2 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Eta"),
		   method     = cms.string("leg1.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi1 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Phi"),
		   method     = cms.string("leg1.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi2 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Phi"),
		   method     = cms.string("leg1.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleeleRelIso03B1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03B"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+max(leg1.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03E"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+leg1.leg1.dr03EcalRecHitSumEt()+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1DcotTheta"),
			method     = cms.string('leg1.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ConvDistance"),
			method     = cms.string('leg1.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1MissHits"),
			method     = cms.string('leg1.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string('(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso+leg1.leg1.neutralHadronIso)/leg1.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1IP"),
			method     = cms.string('leg1.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP801 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP80"),
			method     = cms.string('leg1.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP901 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP90"),
			method     = cms.string('leg1.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCLoose"),
			method     = cms.string('leg1.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCMedium"),
			method     = cms.string('leg1.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCTight"),
			method     = cms.string('leg1.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCSuperTight"),
			method     = cms.string('leg1.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCHyperTight1"),
			method     = cms.string('leg1.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03B2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03B"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+max(leg1.leg2.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03E"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+leg1.leg2.dr03EcalRecHitSumEt()+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2DcotTheta"),
			method     = cms.string('leg1.leg2.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ConvDistance"),
			method     = cms.string('leg1.leg2.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2MissHits"),
			method     = cms.string('leg1.leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string('(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso+leg1.leg2.neutralHadronIso)/leg1.leg2.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eleelePFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	eleelePFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eleeleAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2IP"),
			method     = cms.string('leg1.leg2.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP802 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP80"),
			method     = cms.string('leg1.leg2.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP902 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP90"),
			method     = cms.string('leg1.leg2.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCLoose"),
			method     = cms.string('leg1.leg2.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCMedium"),
			method     = cms.string('leg1.leg2.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCTight"),
			method     = cms.string('leg1.leg2.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCSuperTight"),
			method     = cms.string('leg1.leg2.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight12 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCHyperTight1"),
			method     = cms.string('leg1.leg2.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		#mutau quantities
		mutaupt = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Pt"),
			method     = cms.string("leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauCharge = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauMass = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaupt1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Pt"),
			method     = cms.string("leg2.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaujetpt2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2JetPt"),
			method     = cms.string("leg2.leg2.pfJetRef.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaupt2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Pt"),
			method     = cms.string("leg2.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaueta1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Eta"),
			method     = cms.string("leg2.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaueta2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Eta"),
			method     = cms.string("leg2.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauphi1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Phi"),
			method     = cms.string("leg2.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauphi2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Phi"),
			method     = cms.string("leg2.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		#mu-specific
		mutauisGlobal = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1isGlobal"),
			method     = cms.string("leg2.leg1.isGlobalMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauisTracker= cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1isTracker"),
			method     = cms.string("leg2.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauValidMuonHits = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidMuonHits1"),
			method     = cms.string("leg2.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaunumMatches = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1numMatches"),
			method     = cms.string("leg2.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauValidHits = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidHits"),
			method     = cms.string("leg2.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauNormChiSq = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1NormChiSq"),
			method     = cms.string("leg2.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauRelStdIso = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1StandardRelIso"),
			method     = cms.string("(leg2.leg1.isolationR03.sumPt+leg2.leg1.isolationR03.emEt+leg2.leg1.isolationR03.hadEt)/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauAbsPFIsoDB = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauRelPFIsoDB = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauRelPFIso = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso())/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mutauPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
     	mutauAbsIsoDB2 = cms.PSet(
			  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			  src        = cms.InputTag(src),
		      tag        = cms.string("z2l2AbsIsoDeltaBeta"),
		      method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-0.35*leg2.leg2.particleIso())'),
		 	  leadingOnly=cms.untracked.bool(True)
	    ),
		mutauVBTFID = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1VBTFID"),
			method     = cms.string("leg2.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		#tau-specific
		mutauprongs = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Prongs"),
			method     = cms.string("leg2.leg2.signalPFChargedHadrCands.size()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauGammas = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Gammas"),
			method     = cms.string('leg2.leg2.signalPFGammaCands.size()'),
			leadingOnly=cms.untracked.bool(True)
		),
		mutaumass = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Mass"),
			method     = cms.string("leg2.leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauDecayFound = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2DecayFinding"),
			method     = cms.string('leg2.leg2.tauID("decayModeFinding")'),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauVLooseIso = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIso"),
			method     = cms.string("leg2.leg2.tauID('byVLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauLooseIso = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIso"),
			method     = cms.string("leg2.leg2.tauID('byLooseIsolation')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    mutauAbsIsoRho = cms.PSet(
			  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIsoRho"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum()-leg2.leg2.userFloat("rho")*3.14*0.5*0.5)'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
	    mutauAbsIso = cms.PSet(
			  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			  src        = cms.InputTag(src),
			  tag        = cms.string("z2l2AbsIso"),
			  method     = cms.string('leg2.leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.leg2.isolationPFGammaCandsEtSum())'),
			  leadingOnly=cms.untracked.bool(True)
	    ),
		mutauLooseIsoCombDB = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2LooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauVLooseIsoCombDB = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VLooseIsoCombDB"),
			method     = cms.string("leg2.leg2.tauID('byVLooseCombinedIsolationDeltaBetaCorr')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauEleVeto = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2EleVeto"),
			method     = cms.string("leg2.leg2.tauID('againstElectronLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauMuVeto = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MuVeto"),
			method     = cms.string("leg2.leg2.tauID('againstMuonLoose')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mutauMuVetoTight = cms.PSet(
			pluginType = cms.string("PATEleEleMuTauQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MuVetoTight"),
			method     = cms.string("leg2.leg2.tauID('againstMuonTight')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleMuTauQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)
	
	
#eleeleelemu
def addEleEleEleMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("EleEleEleMuVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#ele ele quantities
		eleelept = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1Pt"),
		   method     = cms.string("leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleCharge = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMass = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelept1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Pt"),
		   method     = cms.string("leg1.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelept2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Pt"),
		   method     = cms.string("leg1.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Eta"),
		   method     = cms.string("leg1.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Eta"),
		   method     = cms.string("leg1.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Phi"),
		   method     = cms.string("leg1.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Phi"),
		   method     = cms.string("leg1.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleeleRelIso03B1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03B"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+max(leg1.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03E"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+leg1.leg1.dr03EcalRecHitSumEt()+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1DcotTheta"),
			method     = cms.string('leg1.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ConvDistance"),
			method     = cms.string('leg1.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1MissHits"),
			method     = cms.string('leg1.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string('(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso+leg1.leg1.neutralHadronIso)/leg1.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1IP"),
			method     = cms.string('leg1.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP801 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP80"),
			method     = cms.string('leg1.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP901 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP90"),
			method     = cms.string('leg1.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCLoose"),
			method     = cms.string('leg1.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCMedium"),
			method     = cms.string('leg1.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCTight"),
			method     = cms.string('leg1.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCSuperTight"),
			method     = cms.string('leg1.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCHyperTight1"),
			method     = cms.string('leg1.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03B2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03B"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+max(leg1.leg2.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03E"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+leg1.leg2.dr03EcalRecHitSumEt()+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2DcotTheta"),
			method     = cms.string('leg1.leg2.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ConvDistance"),
			method     = cms.string('leg1.leg2.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2MissHits"),
			method     = cms.string('leg1.leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string('(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso+leg1.leg2.neutralHadronIso)/leg1.leg2.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eleelePFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	eleelePFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eleeleAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2IP"),
			method     = cms.string('leg1.leg2.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP802 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP80"),
			method     = cms.string('leg1.leg2.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP902 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP90"),
			method     = cms.string('leg1.leg2.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCLoose"),
			method     = cms.string('leg1.leg2.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCMedium"),
			method     = cms.string('leg1.leg2.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCTight"),
			method     = cms.string('leg1.leg2.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCSuperTight"),
			method     = cms.string('leg1.leg2.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight12 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCHyperTight1"),
			method     = cms.string('leg1.leg2.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		#ele mu quantities
		elemupt = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2Pt"),
		   method     = cms.string("leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemuCharge = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuMass = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemupt1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Pt"),
		   method     = cms.string("leg2.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemupt2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Pt"),
		   method     = cms.string("leg2.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemueta1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Eta"),
		   method     = cms.string("leg2.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemueta2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Eta"),
		   method     = cms.string("leg2.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemuphi1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Phi"),
		   method     = cms.string("leg2.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		elemuphi2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Phi2"),
		   method     = cms.string("leg2.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		elemuRelIso03B = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03B"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+max(leg2.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		elemuRelIso03E = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03E"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+leg2.leg1.dr03EcalRecHitSumEt()+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		elemuDCotTheta = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1DcotTheta"),
			method     = cms.string('leg2.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuConvDist = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ConvDistance"),
			method     = cms.string('leg2.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuMissHits = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MissHits"),
			method     = cms.string('leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuPFRelIso = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string('(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso+leg2.leg1.neutralHadronIso)/leg2.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuEleIP = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1IP"),
			method     = cms.string('leg2.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuWP80 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP80"),
			method     = cms.string('leg2.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuWP90 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP90"),
			method     = cms.string('leg2.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCLoose1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCLoose"),
			method     = cms.string('leg2.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCMedium1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCMedium"),
			method     = cms.string('leg2.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCTight"),
			method     = cms.string('leg2.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCSuperTight"),
			method     = cms.string('leg2.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuCiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCHyperTight1"),
			method     = cms.string('leg2.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		#mu-specific
		elemuisTracker = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2isTracker"),
			method     = cms.string("leg2.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuGlobal = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Global2"),
			method     = cms.string("leg2.leg2.isGlobalMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuValidMuonHits = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ValidMuonHits"),
			method     = cms.string("leg2.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemunumMatches = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2numMatches"),
			method     = cms.string("leg2.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuValidHits = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ValidHits1"),
			method     = cms.string("leg2.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuNormChiSq = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2NormChiSq"),
			method     = cms.string("leg2.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuRelStdIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2StandardRelIso2"),
			method     = cms.string("(leg2.leg2.isolationR03.sumPt+leg2.leg2.isolationR03.emEt+leg2.leg2.isolationR03.hadEt)/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuAbsPFIsoDB = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2AbsPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	elemuPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	elemuPFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l2RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-leg2.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		elemuAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2AbsPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		elemuVBTFID = cms.PSet(
			pluginType = cms.string("PATEleEleEleMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VBTFID"),
			method     = cms.string("leg2.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleEleMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)
	

#eleeleeleele
def addEleEleEleEleEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("EleEleEleEleVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#ele ele quantities
		eleele1pt = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1Pt"),
		   method     = cms.string("leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele1Charge = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1Mass = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1pt1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Pt"),
		   method     = cms.string("leg1.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele1pt2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Pt"),
		   method     = cms.string("leg1.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele1eta1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Eta"),
		   method     = cms.string("leg1.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele1eta2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Eta"),
		   method     = cms.string("leg1.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele1phi1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Phi"),
		   method     = cms.string("leg1.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele1phi2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Phi"),
		   method     = cms.string("leg1.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleele1RelIso03B1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03B"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+max(leg1.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleele1RelIso03E1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03E"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+leg1.leg1.dr03EcalRecHitSumEt()+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleele1DCotTheta1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1DcotTheta"),
			method     = cms.string('leg1.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1ConvDist1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ConvDistance"),
			method     = cms.string('leg1.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1MissHits1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1MissHits"),
			method     = cms.string('leg1.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1PFRelIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string('(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso+leg1.leg1.neutralHadronIso)/leg1.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1EleIP1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1IP"),
			method     = cms.string('leg1.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1WP801 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP80"),
			method     = cms.string('leg1.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1WP901 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP90"),
			method     = cms.string('leg1.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCLoose1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCLoose"),
			method     = cms.string('leg1.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCMedium1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCMedium"),
			method     = cms.string('leg1.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCTight"),
			method     = cms.string('leg1.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCSuperTight"),
			method     = cms.string('leg1.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCHyperTight1"),
			method     = cms.string('leg1.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1RelIso03B2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03B"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+max(leg1.leg2.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleele1RelIso03E2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03E"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+leg1.leg2.dr03EcalRecHitSumEt()+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleele1DCotTheta2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2DcotTheta"),
			method     = cms.string('leg1.leg2.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1ConvDist2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ConvDistance"),
			method     = cms.string('leg1.leg2.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1MissHits2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2MissHits"),
			method     = cms.string('leg1.leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1PFRelIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string('(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso+leg1.leg2.neutralHadronIso)/leg1.leg2.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eleele1PFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	eleele1PFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eleele1AbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1AbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1RelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1RelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1EleIP2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2IP"),
			method     = cms.string('leg1.leg2.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1WP802 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP80"),
			method     = cms.string('leg1.leg2.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1WP902 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP90"),
			method     = cms.string('leg1.leg2.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCLoose2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCLoose"),
			method     = cms.string('leg1.leg2.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCMedium2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCMedium"),
			method     = cms.string('leg1.leg2.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCTight"),
			method     = cms.string('leg1.leg2.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCSuperTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCSuperTight"),
			method     = cms.string('leg1.leg2.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele1CiCHyperTight12 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCHyperTight1"),
			method     = cms.string('leg1.leg2.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		#ele ele quantities
		eleele2pt = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2Pt"),
		   method     = cms.string("leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele2Charge = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2Mass = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2pt1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Pt"),
		   method     = cms.string("leg2.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele2pt2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Pt"),
		   method     = cms.string("leg2.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele2eta1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Eta"),
		   method     = cms.string("leg2.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele2eta2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Eta"),
		   method     = cms.string("leg2.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele2phi1 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l1Phi"),
		   method     = cms.string("leg2.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleele2phi2 = cms.PSet(
		   pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z2l2Phi"),
		   method     = cms.string("leg2.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleele2RelIso03B1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03B"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+max(leg2.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleele2RelIso03E1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelIso03E"),
			method     = cms.string("(leg2.leg1.dr03TkSumPt()+leg2.leg1.dr03EcalRecHitSumEt()+leg2.leg1.dr03HcalTowerSumEt())/leg2.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleele2DCotTheta1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1DcotTheta"),
			method     = cms.string('leg2.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2ConvDist1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ConvDistance"),
			method     = cms.string('leg2.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2MissHits1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1MissHits"),
			method     = cms.string('leg2.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2PFRelIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string('(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso+leg2.leg1.neutralHadronIso)/leg2.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2EleIP1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1IP"),
			method     = cms.string('leg2.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2WP801 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP80"),
			method     = cms.string('leg2.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2WP901 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1WP90"),
			method     = cms.string('leg2.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCLoose1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCLoose"),
			method     = cms.string('leg2.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCMedium1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCMedium"),
			method     = cms.string('leg2.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCTight"),
			method     = cms.string('leg2.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCSuperTight"),
			method     = cms.string('leg2.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1CiCHyperTight1"),
			method     = cms.string('leg2.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2RelIso03B2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelIso03B"),
			method     = cms.string("(leg2.leg2.dr03TkSumPt()+max(leg2.leg2.dr03EcalRecHitSumEt()-1.0,0.0)+leg2.leg2.dr03HcalTowerSumEt())/leg2.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleele2RelIso03E2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelIso03E"),
			method     = cms.string("(leg2.leg2.dr03TkSumPt()+leg2.leg2.dr03EcalRecHitSumEt()+leg2.leg2.dr03HcalTowerSumEt())/leg2.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleele2DCotTheta2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2DcotTheta"),
			method     = cms.string('leg2.leg2.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2ConvDist2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ConvDistance"),
			method     = cms.string('leg2.leg2.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2MissHits2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2MissHits"),
			method     = cms.string('leg2.leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2PFRelIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIso"),
			method     = cms.string('(leg2.leg2.chargedHadronIso+leg2.leg2.photonIso+leg2.leg2.neutralHadronIso)/leg2.leg2.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eleele2PFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	eleele2PFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l2RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-leg2.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eleele2AbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2AbsPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2AbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2RelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2RelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2EleIP2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2IP"),
			method     = cms.string('leg2.leg2.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2WP802 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2WP80"),
			method     = cms.string('leg2.leg2.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2WP902 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2WP90"),
			method     = cms.string('leg2.leg2.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCLoose2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCLoose"),
			method     = cms.string('leg2.leg2.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCMedium2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCMedium"),
			method     = cms.string('leg2.leg2.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCTight"),
			method     = cms.string('leg2.leg2.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCSuperTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCSuperTight"),
			method     = cms.string('leg2.leg2.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleele2CiCHyperTight12 = cms.PSet(
			pluginType = cms.string("PATEleEleEleEleQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2CiCHyperTight1"),
			method     = cms.string('leg2.leg2.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleEleEleQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)


def addEleEleMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysisTest.root") )
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
		MET = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		refitVertex = cms.PSet(
			pluginType = cms.string("EleEleMuMuVertexFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("refitVertex"),
			vertexTag  = cms.InputTag("offlinePrimaryVertices")
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
		Mass = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("charge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Size = cms.PSet(
			pluginType = cms.string("CollectionSizeFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("nZZCandidates"),
		),
		#mumu quantities
		mumupt = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Pt"),
			method     = cms.string("leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuCharge = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuMass = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),

		mumupt1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Pt"),
			method     = cms.string("leg2.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumupt2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Pt"),
			method     = cms.string("leg2.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Eta"),
			method     = cms.string("leg2.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumueta2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Eta"),
			method     = cms.string("leg2.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Phi"),
			method     = cms.string("leg2.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuphi2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2Phi"),
			method     = cms.string("leg2.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2ValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidMuonHits1"),
			method     = cms.string("leg2.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2ValidMuonHits2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ValidMuonHits"),
			method     = cms.string("leg2.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2numMatches1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1numMatches"),
			method     = cms.string("leg2.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2numMatches2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2numMatches"),
			method     = cms.string("leg2.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidHits"),
			method     = cms.string("leg2.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuValidHits2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2ValidHits"),
			method     = cms.string("leg2.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1NormChiSq"),
			method     = cms.string("leg2.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuNormChiSq2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2NormChiSq"),
			method     = cms.string("leg2.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1StandardRelIso"),
			method     = cms.string("(leg2.leg1.isolationR03.sumPt+leg2.leg1.isolationR03.emEt+leg2.leg1.isolationR03.hadEt)/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelStdIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2StandardRelIso"),
			method     = cms.string("(leg2.leg2.isolationR03.sumPt+leg2.leg2.isolationR03.emEt+leg2.leg2.isolationR03.hadEt)/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2AbsPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIsoDB"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIso"),
			method     = cms.string("(leg2.leg1.chargedHadronIso+leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso())/leg2.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuRelPFIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2RelPFIso"),
			method     = cms.string("(leg2.leg2.chargedHadronIso+leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso())/leg2.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mumuPFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-leg2.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	mumuPFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l2RelPfIsoRho"),
		  	method     = cms.string('(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-leg2.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		mumuisTracker1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1isTracker"),
			method     = cms.string("leg2.leg1.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuisTracker2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2isTracker"),
			method     = cms.string("leg2.leg2.isTrackerMuon()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuVBTFID1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1VBTFID"),
			method     = cms.string("leg2.leg1.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumuVBTFID2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2VBTFID"),
			method     = cms.string("leg2.leg2.userFloat('isVBTFMuon')"),
			leadingOnly=cms.untracked.bool(True)
		),
		#ele ele quantities
		eleelept = cms.PSet(
		   pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1Pt"),
		   method     = cms.string("leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleCharge = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMass = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelept1 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Pt"),
		   method     = cms.string("leg1.leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelept2 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Pt"),
		   method     = cms.string("leg1.leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta1 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Eta"),
		   method     = cms.string("leg1.leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta2 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Eta"),
		   method     = cms.string("leg1.leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi1 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l1Phi"),
		   method     = cms.string("leg1.leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi2 = cms.PSet(
		   pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("z1l2Phi"),
		   method     = cms.string("leg1.leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleeleRelIso03B1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03B"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+max(leg1.leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelIso03E"),
			method     = cms.string("(leg1.leg1.dr03TkSumPt()+leg1.leg1.dr03EcalRecHitSumEt()+leg1.leg1.dr03HcalTowerSumEt())/leg1.leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1DcotTheta"),
			method     = cms.string('leg1.leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ConvDistance"),
			method     = cms.string('leg1.leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1MissHits"),
			method     = cms.string('leg1.leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string('(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso+leg1.leg1.neutralHadronIso)/leg1.leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1IP"),
			method     = cms.string('leg1.leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP801 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP80"),
			method     = cms.string('leg1.leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP901 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1WP90"),
			method     = cms.string('leg1.leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCLoose"),
			method     = cms.string('leg1.leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCMedium"),
			method     = cms.string('leg1.leg1.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCTight"),
			method     = cms.string('leg1.leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCSuperTight"),
			method     = cms.string('leg1.leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1CiCHyperTight1"),
			method     = cms.string('leg1.leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleAbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleAbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03B2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03B"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+max(leg1.leg2.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelIso03E"),
			method     = cms.string("(leg1.leg2.dr03TkSumPt()+leg1.leg2.dr03EcalRecHitSumEt()+leg1.leg2.dr03HcalTowerSumEt())/leg1.leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2DcotTheta"),
			method     = cms.string('leg1.leg2.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ConvDistance"),
			method     = cms.string('leg1.leg2.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2MissHits"),
			method     = cms.string('leg1.leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIso"),
			method     = cms.string('(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso+leg1.leg2.neutralHadronIso)/leg1.leg2.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
	  	eleelePFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l1RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	  	eleelePFRelIsoRho2 = cms.PSet(
		  	pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z1l2RelPfIsoRho"),
		  	method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
		eleeleEleIP2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2IP"),
			method     = cms.string('leg1.leg2.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP802 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP80"),
			method     = cms.string('leg1.leg2.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP902 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2WP90"),
			method     = cms.string('leg1.leg2.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCLoose"),
			method     = cms.string('leg1.leg2.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCMedium2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCMedium"),
			method     = cms.string('leg1.leg2.electronID("cicMedium")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCTight"),
			method     = cms.string('leg1.leg2.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight2 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCSuperTight"),
			method     = cms.string('leg1.leg2.electronID("cicSuperTight")'),
		),
		eleeleCiCHyperTight12 = cms.PSet(
			pluginType = cms.string("PATEleEleMuMuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2CiCHyperTight"),
			method     = cms.string('leg1.leg2.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
	    l1l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l1GenPt"),
		  method     = cms.string('leg1.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l1l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1l2GenPt"),
		  method     = cms.string('leg1.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l1GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l1GenMass"),
		  method     = cms.string('leg1.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	    l2l1GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l1GenPt"),
		  method     = cms.string('leg2.p4VisLeg1gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	    l2l2GenPt = cms.PSet(
		  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2l2GenPt"),
		  method     = cms.string('leg2.p4VisLeg2gen().pt()'),
		  leadingOnly=cms.untracked.bool(True)
	    ),
	  	l2GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("l2GenMass"),
		  method     = cms.string('leg2.p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	GenMass = cms.PSet(
		  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
		  src        = cms.InputTag(src),
		  tag        = cms.string("GenMass"),
		  method     = cms.string('p4VisGen().M()'),
		  leadingOnly=cms.untracked.bool(True)
	  	),
	  	dZ12 = cms.PSet(
	  	  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ12"),
	  	  method     = cms.string('leg1.dz'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ13 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ13"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z1)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),
	  	dZ14 =  cms.PSet(
	  	  pluginType = cms.string("PATEleEleMuMuQuadFiller"),
	  	  src        = cms.InputTag(src),
	  	  tag		 = cms.string("dZ14"),
	  	  method     = cms.string('abs(leg1.z1-leg2.z2)'),
	  	  leadingOnly= cms.untracked.bool(True)
	  	),	  	
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)



