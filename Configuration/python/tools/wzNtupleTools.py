from UWAnalysis.Configuration.tools.analysisTools import TriggerPaths
import FWCore.ParameterSet.Config as cms
#mumutautau tree
#mumumumu tree
def addMuMuMuEventTree(process,name,src = 'zzCleanedCandsAboveThreshold'):
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
			pluginType = cms.string("PATMuMuMuNuQuadJetCountFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("jetsPt20"),
			method     = cms.string('pt()>20'),
			leadingOnly=cms.untracked.bool(True)
		),
		MET = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
#		refitVertex = cms.PSet(
#			pluginType = cms.string("MuMuMuNuVertexFiller"),
#			src        = cms.InputTag(src),
#			tag        = cms.string("refitVertex"),
#			vertexTag  = cms.InputTag("offlinePrimaryVertices")
#		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ZZ quantities
		Mass = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		Charge = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
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
		mt = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mt"),
			method     = cms.string("mt12MET"),
			leadingOnly=cms.untracked.bool(True)
		),
		mt1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mt1"),
			method     = cms.string("mt1MET"),
			leadingOnly=cms.untracked.bool(True)
		),
		mt1_12 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mt1_12"),
			method     = cms.string("leg1.mt12MET"),
			leadingOnly=cms.untracked.bool(True)
		),
		mt1_1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mt1_1"),
			method     = cms.string("leg1.mt1MET"),
			leadingOnly=cms.untracked.bool(True)
		),
		mt1_2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mt1_2"),
			method     = cms.string("leg1.mt2MET"),
			leadingOnly=cms.untracked.bool(True)
		),
		mt2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("mt2"),
			method     = cms.string("mt2MET"),
			leadingOnly=cms.untracked.bool(True)
		),
		#mumu1 quantities
		mumu1pt = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Pt"),
			method     = cms.string("leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1Charge = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Charge"),
			method     = cms.string("leg1.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1Mass = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1Mass"),
			method     = cms.string("leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1pt1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Pt"),
			method     = cms.string("leg1.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1pt2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Pt"),
			method     = cms.string("leg1.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1eta1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Eta"),
			method     = cms.string("leg1.leg1.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1eta2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Eta"),
			method     = cms.string("leg1.leg2.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1phi1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1Phi"),
			method     = cms.string("leg1.leg1.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1phi2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2Phi"),
			method     = cms.string("leg1.leg2.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidMuonHits1"),
			method     = cms.string("leg1.leg1.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidMuonHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidMuonHits"),
			method     = cms.string("leg1.leg2.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1numMatches1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1numMatches"),
			method     = cms.string("leg1.leg1.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1numMatches2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2numMatches"),
			method     = cms.string("leg1.leg2.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1ValidHits"),
			method     = cms.string("leg1.leg1.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1ValidHits2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2ValidHits"),
			method     = cms.string("leg1.leg2.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1NormChiSq1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1NormChiSq"),
			method     = cms.string("leg1.leg1.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1NormChiSq2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2NormChiSq"),
			method     = cms.string("leg1.leg2.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1AbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1AbsPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1AbsPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2AbsPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1RelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIsoDB"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1RelPFIsoDB2 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l2RelPFIsoDB"),
			method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu1RelPFIso1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z1l1RelPFIso"),
			method     = cms.string("(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso())/leg1.leg1.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		#mumu2 quantities
		mumu2pt = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Pt"),
			method     = cms.string("leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2Charge = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2Mass = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2Mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2pt1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Pt"),
			method     = cms.string("leg2.lepton.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2eta1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Eta"),
			method     = cms.string("leg2.lepton.eta"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2phi1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1Phi"),
			method     = cms.string("leg2.lepton.phi"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2ValidMuonHits1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidMuonHits1"),
			method     = cms.string("leg2.lepton.globalTrack().hitPattern().numberOfValidMuonHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2numMatches1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1numMatches"),
			method     = cms.string("leg2.lepton.numberOfMatches()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2ValidHits1 = cms.PSet(

			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1ValidHits"),
			method     = cms.string("leg2.lepton.numberOfValidHits()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2NormChiSq1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1NormChiSq"),
			method     = cms.string("leg2.lepton.normChi2()"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2AbsPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1AbsPFIsoDB"),
			method     = cms.string("(leg2.lepton.chargedHadronIso+max(leg2.lepton.photonIso()+leg2.lepton.neutralHadronIso()-0.5*leg2.lepton.userIso(0),0.0))"),
			leadingOnly=cms.untracked.bool(True)
		),
		mumu2RelPFIsoDB1 = cms.PSet(
			pluginType = cms.string("PATMuMuMuNuQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1RelPFIsoDB"),
			method     = cms.string("(leg2.lepton.chargedHadronIso+max(leg2.lepton.photonIso()+leg2.lepton.neutralHadronIso()-0.5*leg2.lepton.userIso(0),0.0))/leg2.lepton.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
	  	mumu2PFRelIsoRho1 = cms.PSet(
		  	pluginType = cms.string("PATMuMuMuNuQuadFiller"),
		  	src        = cms.InputTag(src),
		  	tag        = cms.string("z2l1RelPfIsoRho"),
		  	method     = cms.string('(leg2.lepton.chargedHadronIso()+max(leg2.lepton.photonIso()+leg2.lepton.neutralHadronIso()-leg2.lepton.userFloat("rho")*3.14*0.4*0.4,0.0))/leg2.lepton.pt()'),
		  	leadingOnly=cms.untracked.bool(True)
	  	),
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)
