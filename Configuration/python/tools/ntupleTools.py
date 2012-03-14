import FWCore.ParameterSet.Config as cms

from UWAnalysis.Configuration.tools.analysisTools import TriggerPaths



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



#
#Ntuple for tau ID studies
#

def addTauTree(process,name,src='patOverloadedTaus'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   tauTree = cms.EDAnalyzer('PATTauTree',
                            src = cms.InputTag(src),
                            vars = cms.VPSet(
                              cms.PSet(
                                 tag        = cms.string("pt"),
                                  method     = cms.string("pt"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("eta"),
                                  method     = cms.string("eta"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("energy"),
                                  method     = cms.string("energy"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("charge"),
                                  method     = cms.string("charge"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("prongs"),
                                  method     = cms.string("signalPFChargedHadrCands.size()"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("photons"),
                                  method     = cms.string("signalPFGammaCands.size()"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("mass"),
                                  method     = cms.string("mass"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("decayMode"),
                                 method     = cms.string("pfSpecific().decayMode_"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("cone"),
                                 method     = cms.string("pfSpecific().cone_"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("angle"),
                                 method     = cms.string("pfSpecific().angle_"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("DMFound"),
                                 method     = cms.string("tauID('leadingTrackFinding')"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("VLoose"),
                                 method     = cms.string("tauID('byVLooseIsolation')"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("Loose"),
                                 method     = cms.string("tauID('byLooseIsolation')"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("Medium"),
                                 method     = cms.string("tauID('byMediumIsolation')"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("Tight"),
                                 method     = cms.string("tauID('byTightIsolation')"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("mcPt"),
                                 method     = cms.string("userFloat('genJetPt')"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("mcEta"),
                                 method     = cms.string("userFloat('genJetEta')"),
                              ),
                              cms.PSet(
                                 tag        = cms.string("mcDecayMode"),
                                 method     = cms.string("userInt('mcDecayMode')"),
                              )
)

   )

   setattr(process, name, tauTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)

def addMuMuJJEventTree(process,name,src = 'zMuMuJJCleanedCands'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              coreCollections = cms.VInputTag(
                                   cms.InputTag(src)
                              ),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src        = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                              ),
                              ##ZZ quantities
                              Mass = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mass"),
                                  method     = cms.string("mass()"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              Charge = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
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
                                PVs = cms.PSet(
                                    pluginType = cms.string("VertexSizeFiller"),
                                    src        = cms.InputTag("primaryVertexFilter"),
                                    tag        = cms.string("vertices")
                              ),
                            MET = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("met"),
                                  method     = cms.string("met.pt()"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              mu1DXY = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("z1l1DXY"),
                                  method     = cms.string('leg1.leg1.dB()'),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              mu2DXY = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("z1l2DXY"),
                                  method     = cms.string('leg1.leg2.dB()'),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              mumupt = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("z1pt"),
                                  method     = cms.string("leg1.pt"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              mumuCharge = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("z1charge"),
                                  method     = cms.string("leg1.charge()"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              mumuMass = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("z1mass"),
                                  method     = cms.string("leg1.mass()"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              mumuPt1 = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("z1l1pt"),
                                  method     = cms.string("leg1.leg1.pt"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPt2 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l2pt"),
                                    method     = cms.string("leg1.leg2.pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuEta1 = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("z1l1eta"),
                                  method     = cms.string("leg1.leg1.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuEta2 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l2eta"),
                                    method     = cms.string("leg1.leg2.eta"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuDPhi = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("z1dphi"),
                                  method     = cms.string("leg1.dPhi12()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuDR = cms.PSet(
                                  pluginType = cms.string("PATMuMuJJQuadFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("z1dR"),
                                  method     = cms.string("leg1.dR12()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPhi2 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l2phi"),
                                    method     = cms.string("leg1.leg2.phi"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuValidHits1 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l1ValidHits"),
                                    method     = cms.string("leg1.leg1.numberOfValidHits()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuValidHits2 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l2ValidHits"),
                                    method     = cms.string("leg1.leg2.numberOfValidHits()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuNormChiSq1 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l1NormChiSq"),
                                    method     = cms.string("leg1.leg1.normChi2()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
		              mumuNormChiSq2 = cms.PSet(
			            pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l2NormChiSq"),
                                    method     = cms.string("leg1.leg2.normChi2()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuRelStdIso1 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l1StandardRelIso"),
                                    method     = cms.string("(leg1.leg1.isolationR03.sumPt+leg1.leg1.isolationR03.emEt+leg1.leg1.isolationR03.hadEt)/leg1.leg1.pt()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuRelStdIso2 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l2StandardRelIso"),
                                    method     = cms.string("(leg1.leg2.isolationR03.sumPt+leg1.leg2.isolationR03.emEt+leg1.leg2.isolationR03.hadEt)/leg1.leg2.pt()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuRelPFIsoDB1 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l1RelPFIsoDB"),
                                    method     = cms.string("(leg1.leg1.chargedHadronIso+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuRelPFIsoDB2 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l2RelPFIsoDB"),
                                    method     = cms.string("(leg1.leg2.chargedHadronIso+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuRelPFIso1 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l1RelPFIso"),
                                    method     = cms.string("(leg1.leg1.chargedHadronIso+leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso())/leg1.leg1.pt()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuRelPFIso2 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l2RelPFIso"),
                                    method     = cms.string("(leg1.leg2.chargedHadronIso+leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso())/leg1.leg2.pt()"),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuPFRelIsoRho1 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l1RelPfIsoRho"),
                                    method     = cms.string('(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-leg1.leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg1.pt()'),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                              mumuPFRelIsoRho2 = cms.PSet(
                                    pluginType = cms.string("PATMuMuJJQuadFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("z1l2RelPfIsoRho"),
                                    method     = cms.string('(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-leg1.leg2.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.leg2.pt()'),
                                    leadingOnly=cms.untracked.bool(True)
                                    ),
                genZbb = cms.PSet(
                        pluginType = cms.string("CollectionSizeFiller"),
                        src        = cms.InputTag("genZbbCands"),
                        tag        = cms.string("genBs"),
                ),
                genZdd = cms.PSet(
                        pluginType = cms.string("CollectionSizeFiller"),
                        src        = cms.InputTag("genZddCands"),
                        tag        = cms.string("genDs"),
                ),
                genZuu = cms.PSet(
                        pluginType = cms.string("CollectionSizeFiller"),
                        src        = cms.InputTag("genZuuCands"),
                        tag        = cms.string("genUs"),
                ),
                genZss = cms.PSet(
                        pluginType = cms.string("CollectionSizeFiller"),
                        src        = cms.InputTag("genZssCands"),
                        tag        = cms.string("genSs"),
                ),
                genZcc = cms.PSet(
                        pluginType = cms.string("CollectionSizeFiller"),
                        src        = cms.InputTag("genZccCands"),
                        tag        = cms.string("genCs"),
                ),
		jjpt = cms.PSet(
			pluginType = cms.string("PATMuMuJJQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2pt"),
			method     = cms.string("leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		jjCharge = cms.PSet(
			pluginType = cms.string("PATMuMuJJQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2charge"),
			method     = cms.string("leg2.charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		jjMass = cms.PSet(
			pluginType = cms.string("PATMuMuJJQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2mass"),
			method     = cms.string("leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
                jjDPhi = cms.PSet(
                        pluginType = cms.string("PATMuMuJJQuadFiller"),
                        src        = cms.InputTag(src),
                        tag        = cms.string("z2dphi"),
                        method     = cms.string("leg2.dPhi12()"),
                        leadingOnly=cms.untracked.bool(True)
                ),
                jjDR = cms.PSet(
                        pluginType = cms.string("PATMuMuJJQuadFiller"),
                        src        = cms.InputTag(src),
                        tag        = cms.string("z2dR"),
                        method     = cms.string("leg2.dR12()"),
                        leadingOnly=cms.untracked.bool(True)
                ),
		jjpt1 = cms.PSet(
			pluginType = cms.string("PATMuMuJJQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1pt"),
			method     = cms.string("leg2.leg1.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
		jjpt2 = cms.PSet(
			pluginType = cms.string("PATMuMuJJQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2pt"),
			method     = cms.string("leg2.leg2.pt"),
			leadingOnly=cms.untracked.bool(True)
		),
               jjEta1 = cms.PSet(
                       pluginType = cms.string("PATMuMuJJQuadFiller"),
                       src        = cms.InputTag(src),
                       tag        = cms.string("z2l1eta"),
                       method     = cms.string("leg2.leg1.eta"),
                       leadingOnly=cms.untracked.bool(True)
                       ),
               jjEta2 = cms.PSet(
                      pluginType = cms.string("PATMuMuJJQuadFiller"),
                      src        = cms.InputTag(src),
                      tag        = cms.string("z2l2eta"),
                      method     = cms.string("leg2.leg2.eta"),
                      leadingOnly=cms.untracked.bool(True)
                      ),
               jjPhi1 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l1phi"),
                     method     = cms.string("leg2.leg1.phi"),
                     leadingOnly=cms.untracked.bool(True)
                     ),
               jjPhi2 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l2phi"),
                     method     = cms.string("leg2.leg2.phi"),
                     leadingOnly=cms.untracked.bool(True)
                     ),
               jjBTag1 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l1BTag"),
                     method     = cms.string('leg2.leg1.bDiscriminator("")'),
                     leadingOnly=cms.untracked.bool(True)
                     ),
               jjBTag2 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l2BTag"),
                     method     = cms.string('leg2.leg2.bDiscriminator("")'),
                     leadingOnly=cms.untracked.bool(True)
                     ),
               jjJetFlavour1 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l1JetFlavour"),
                     method     = cms.string('leg2.leg1.partonFlavour()'),
                     ),
               jjJetShape1 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l1JetShape"),
                     method     = cms.string('leg2.leg1.userFloat("ptRMS")'),
                     ),
               jjJetChMultiplicity1 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l1JetNCharged"),
                     method     = cms.string('leg2.leg1.chargedMultiplicity()'),
                     ),
              jjFlavour2 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l2JetFlavour"),
                     method     = cms.string('leg2.leg2.partonFlavour()'),
                     ),
               jjJetShape2 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l2JetShape"),
                     method     = cms.string('leg2.leg2.userFloat("ptRMS")'),
                     ),
               jjJetChMultiplicity2 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("z2l2JetNCharged"),
                     method     = cms.string('leg2.leg2.chargedMultiplicity()'),
                     ),
               m1j1 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("m1j1DR"),
                     method     = cms.string('sqrt((leg1.leg1.eta-leg2.leg1.eta())*(leg1.leg1.eta-leg2.leg1.eta())+(leg1.leg1.phi-leg2.leg1.phi())*(leg1.leg1.phi-leg2.leg1.phi()))'),
                     ),
               m1j2 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("m1j2DR"),
                     method     = cms.string('sqrt((leg1.leg1.eta-leg2.leg2.eta())*(leg1.leg1.eta-leg2.leg2.eta())+(leg1.leg1.phi-leg2.leg2.phi())*(leg1.leg1.phi-leg2.leg2.phi()))'),
                     ),
               m2j1 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("m2j1DR"),
                     method     = cms.string('sqrt((leg1.leg2.eta-leg2.leg1.eta())*(leg1.leg2.eta-leg2.leg1.eta())+(leg1.leg2.phi-leg2.leg1.phi())*(leg1.leg2.phi-leg2.leg1.phi()))'),
                     ),
               m2j2 = cms.PSet(
                     pluginType = cms.string("PATMuMuJJQuadFiller"),
                     src        = cms.InputTag(src),
                     tag        = cms.string("m2j2DR"),
                     method     = cms.string('sqrt((leg1.leg2.eta-leg2.leg2.eta())*(leg1.leg2.eta-leg2.leg2.eta())+(leg1.leg2.phi-leg2.leg2.phi())*(leg1.leg2.phi-leg2.leg2.phi()))'),
                     ),
		jjmass1 = cms.PSet(
			pluginType = cms.string("PATMuMuJJQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l1mass"),
			method     = cms.string("leg2.leg1.mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		jjmass2 = cms.PSet(
			pluginType = cms.string("PATMuMuJJQuadFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("z2l2mass"),
			method     = cms.string("leg2.leg2.mass()"),
			leadingOnly=cms.untracked.bool(True)
		)
	)
   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)


#Ntuple for Mu+Tau+MET  final states
#Covers Z/H -> tau tau
#Covers bbA -> tau tau
# ZH -> nu nu tau tau  
#VBF will be added



def addMuTauEventTree(process,name,src = 'diTausTauMuonVeto', srcLL = 'diMuonsSorted'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              coreCollections = cms.VInputTag(
                                   cms.InputTag(src)
                              ),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src        = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                                  ),

                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("addPileupInfo"),
                                  tag        = cms.string("pu"),
                                  ),
                                  
                              pt1 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pt1"),
                                  method     = cms.string("leg1.pt"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              pt2 = cms.PSet(
                                    pluginType = cms.string("PATMuTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt2"),
                                    method     = cms.string("leg2.pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              charge1 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge1"),
                                  method     = cms.string("leg1.charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              charge2 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge2"),
                                  method     = cms.string("leg2.charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              pt = cms.PSet(
                                    pluginType = cms.string("PATMuTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt"),
                                    method     = cms.string("pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              eta = cms.PSet(
                                    pluginType = cms.string("PATMuTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta"),
                                    method     = cms.string("eta"),
                                    leadingOnly=cms.untracked.bool(True)

                              ),
                              muTauEta1 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("eta1"),
                                  method     = cms.string("leg1.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauEta2 = cms.PSet(
                                    pluginType = cms.string("PATMuTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta2"),
                                    method     = cms.string("leg2.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauPhi1 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("phi1"),
                                  method     = cms.string("leg1.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauPhi2 = cms.PSet(
                                    pluginType = cms.string("PATMuTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("phi2"),
                                    method     = cms.string("leg2.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauDZ = cms.PSet(
                                    pluginType = cms.string("PATMuTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("dz"),
                                    method     = cms.string("dz"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauRho = cms.PSet(
                                  pluginType = cms.string("EventWeightFiller"),
                                  src        = cms.InputTag("kt6PFJets","rho"),
                                  tag        = cms.string("Rho")
                              ),

                              muTauDCA = cms.PSet(
                                    pluginType = cms.string("PATMuTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("dca"),
                                    method     = cms.string("dca"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauDist = cms.PSet(
                                    pluginType = cms.string("PATMuTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("xPointDist"),
                                    method     = cms.string("crossingPointDistance"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              projMET = cms.PSet(
                                    pluginType = cms.string("PATMuTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("projMET"),
                                    method     = cms.string("projMET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauCharge = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge"),
                                  method     = cms.string("charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauMass = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mass"),
                                  method     = cms.string("mass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauMT1 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt1"),
                                  method     = cms.string("mt1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauMT = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt"),
                                  method     = cms.string("mt12MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauMT2 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt2"),
                                  method     = cms.string("mt2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauMET = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("met"),
                                  method     = cms.string("calibratedMET.pt()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
#                              muTauGenMET = cms.PSet(
#                                  pluginType = cms.string("PATGenMETFiller"),
#                                  src        = cms.InputTag("genMetTrue"),
##                                  tag        = cms.string("genMET"),
#                                  method     = cms.string("pt()"),
#                                  leadingOnly=cms.untracked.bool(True)
#                              ),
                              muTauDPhi = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi"),
                                  method     = cms.string("dPhi12"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauDR = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dR"),
                                  method     = cms.string("dR12"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              muTauDPhi1MET = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi1MET"),
                                  method     = cms.string("dPhi1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauDPhi2MET = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi2MET"),
                                  method     = cms.string("dPhi2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauHT = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ht"),
                                  method     = cms.string("ht"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJJ = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mJJ"),
                                  method     = cms.string("mJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJJPt = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ptJJ"),
                                  method     = cms.string("ptJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              muTauVBFDEta = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfDEta"),
                                  method     = cms.string("vbfDEta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauVBFPt1 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt1"),
                                  method     = cms.string("vbfPt1"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauVBFPt2 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt2"),
                                  method     = cms.string("vbfPt2"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauVBFEta1 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta1"),
                                  method     = cms.string("vbfEta1"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauVBFEta2 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta2"),
                                  method     = cms.string("vbfEta2"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauVBFMass = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfMass"),
                                  method     = cms.string("vbfMass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuVBFJets20 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap20"),
                                  method     = cms.string("vbfNJetsGap20"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muMuVBFJets30 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap30"),
                                  method     = cms.string("vbfNJetsGap30"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muTauRelStdIso03 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lStdRelIso"),
                                  method     = cms.string('(leg1.isolationR03.sumPt+leg1.isolationR03.emEt+leg1.isolationR03.hadEt)/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauRelPFIsoDB = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lPfRelIsoDeltaBeta"),
                                  method     = cms.string('(leg1.chargedHadronIso+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauRelPFIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lPfRelIso"),
                                  method     = cms.string('(leg1.chargedHadronIso+leg1.photonIso()+leg1.neutralHadronIso())/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauDecayMode = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauDecayMode"),
                                  method     = cms.string('leg2.decayMode()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauMuTriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lTrigger"),
                                  method     = cms.string('leg1.userFloat("hltOverlapFilterIsoMu12IsoPFTau10")+leg1.userFloat("hltOverlapFilterIsoMu15IsoPFTau15")+leg1.userFloat("hltOverlapFilterIsoMu15IsoPFTau20")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauSVFit = cms.PSet(
                                    pluginType = cms.string("PATMuTauSVFitFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("sv_")
                              ),
                              muTauTauTriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauTrigger"),
                                  method     = cms.string('leg2.userFloat("hltOverlapFilterIsoMu12IsoPFTau10")+leg2.userFloat("hltOverlapFilterIsoMu15IsoPFTau15")+leg2.userFloat("hltOverlapFilterIsoMu15IsoPFTau20")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauTau1TriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("IsoMu12LTau10"),
                                  method     = cms.string('leg2.userFloat("hltOverlapFilterIsoMu12IsoPFTau10")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauTau2TriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("IsoMu15LTau15"),
                                  method     = cms.string('leg2.userFloat("hltOverlapFilterIsoMu15IsoPFTau15")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauTau3TriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("IsoMu15LTau20"),
                                  method     = cms.string('leg2.userFloat("hltOverlapFilterIsoMu15IsoPFTau20")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauTau6TriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("Mu15LTau20"),
                                  method     = cms.string('leg2.userFloat("hltOverlapFilterMu15IsoPFTau20")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauTau4TriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("IsoMu15MTau20"),
                                  method     = cms.string('leg2.userFloat("hltOverlapFilterIsoMu15MediumIsoPFTau20")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauTau5TriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("IsoMu15TTau20"),
                                  method     = cms.string('leg2.userFloat("hltOverlapFilterIsoMu15TightIsoPFTau20")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),  
                              muTauPzeta = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZeta"),
                                  method     = cms.string('pZeta-1.5*pZetaVis'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauPZ = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZ"),
                                  method     = cms.string('pZeta'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauPZV = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZV"),
                                  method     = cms.string('pZetaVis'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauHadMass = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauMass"),
                                  method     = cms.string('leg2.mass()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauDecayFound = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauDecayFound"),
                                  method     = cms.string('leg2.tauID("decayModeFinding")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauVLooseIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauVLooseIso"),
                                  method     = cms.string('leg2.tauID("byVLooseIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauLooseIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauLooseIso"),
                                  method     = cms.string('leg2.tauID("byLooseIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauMediumIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauMediumIso"),
                                  method     = cms.string('leg2.tauID("byMediumIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauTightIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),

                                  tag        = cms.string("tauTightIso"),
                                  method     = cms.string('leg2.tauID("byTightIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauLooseDBPtIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauLooseIsoDBPt"),
                                  method     = cms.string('leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauVLooseDBPtIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauVLooseIsoDBPt"),
                                  method     = cms.string('leg2.tauID("byVLooseCombinedIsolationDeltaBetaCorr")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauMediumDBPtIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauMediumIsoDBPt"),
                                  method     = cms.string('leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauTightDBPtIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauTightIsoDBPt"),
                                  method     = cms.string('leg2.tauID("byTightCombinedIsolationDeltaBetaCorr")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauAbsIsoRho = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauAbsIsoRho"),
                                  method     = cms.string('leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.isolationPFGammaCandsEtSum()-leg2.userFloat("rho")*3.14*0.5*0.5)'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauAbsIso = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauAbsIso"),
                                  method     = cms.string('leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.isolationPFGammaCandsEtSum())'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauH = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauH"),
                                  method     = cms.string('leg2.leadPFChargedHadrCand().hcalEnergy()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauE = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauE"),
                                  method     = cms.string('leg2.leadPFChargedHadrCand().ecalEnergy()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauP = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauP"),
                                  method     = cms.string('leg2.leadPFChargedHadrCand().p()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag2Pt20 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag2Pt20M = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag2Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag3Pt20 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag3Pt20M = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag3Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag2Pt30 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag2Pt30M = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag2Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag3Pt30 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag3Pt30M = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsBTag3Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsPt30 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt30"),
                                  method     = cms.string('pt()>30'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsPt30Tag = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsPt30TagMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30Matched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsPt30TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30NotMatched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsPt20 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt20"),
                                  method     = cms.string('pt()>20'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsPt20Tag = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsPt20TagMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20Matched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJetsPt20TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20NotMatched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauGenPt1 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt1"),
                                  method     = cms.string('p4VisLeg1gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauGenPt2 = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt2"),
                                  method     = cms.string('p4VisLeg2gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauGenVisMass = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genVisMass"),
                                  method     = cms.string('p4VisGen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauGenMass = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genFullMass"),
                                  method     = cms.string('p4gen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauFirstJetPt = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetPt"),
                                  method     = cms.string('pt()'),
                              ),
                              muTauFirstJetEta = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetEta"),
                                  method     = cms.string('eta()'),
                              ),

                              muTauFirstJetFlavour = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetFlavour"),
                                  method     = cms.string('partonFlavour()'),
                              ),
                              muTauFirstJetShape = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetShape"),
                                  method     = cms.string('userFloat("ptRMS")'),
                              ),
                              muTauFirstJetChMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNCharged"),
                                  method     = cms.string('chargedMultiplicity()'),
                              ),
                              muTauFirstJetNeutMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATMuTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNNeutral"),
                                  method     = cms.string('photonMultiplicity()+neutralHadronMultiplicity()'),
                              ),
                              PVs = cms.PSet(
                                    pluginType = cms.string("VertexSizeFiller"),
                                    src        = cms.InputTag("primaryVertexFilter"),
                                    tag        = cms.string("vertices")
                              ),
                              mumuSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(srcLL),
                                    tag        = cms.string("diLeptons"),
                              ),
                              genTaus = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag("genTauCands"),
                                    tag        = cms.string("genTaus"),
                              ),
                              higgsPt = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("higgsPt"),
                                  method     = cms.string('pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              muTauSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("nCands"),
                              ),
                              muTauEmbedWeight = cms.PSet(
                                    pluginType = cms.string("EventWeightFiller"),
                                    src        = cms.InputTag("generator","weight"),
                                    tag        = cms.string("embeddedWeight"),
                              ),
                              muTauEmbedPt = cms.PSet(
                                    pluginType = cms.string("PATGenParticleFiller"),
                                    src        = cms.InputTag("genDaughters"),
                                    tag        = cms.string("embeddedPt"),
                                    method     = cms.string("pt"),
                                    leadingOnly=cms.untracked.bool(False)

                              ),
                              muTauEmbedEta = cms.PSet(
                                    pluginType = cms.string("PATGenParticleFiller"),
                                    src        = cms.InputTag("genDaughters"),
                                    tag        = cms.string("embeddedEta"),
                                    method     = cms.string("eta"),
                                    leadingOnly=cms.untracked.bool(False)
                              )

   )

   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)





def addMuJetEventTree(process,name,src = 'muJetsTauPtEta', srcLL = 'diMuonsSorted'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              coreCollections = cms.VInputTag(
                                   cms.InputTag(src)
                              ),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src        = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                                  ),

                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("addPileupInfo"),
                                  tag        = cms.string("pu"),
                                  ),
                                  
                              pt1 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pt1"),
                                  method     = cms.string("leg1.pt"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              pt2 = cms.PSet(
                                    pluginType = cms.string("PATMuJetPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt2"),
                                    method     = cms.string("leg2.pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              charge1 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge1"),
                                  method     = cms.string("leg1.charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              charge2 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge2"),
                                  method     = cms.string("leg2.charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              pt = cms.PSet(
                                    pluginType = cms.string("PATMuJetPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt"),
                                    method     = cms.string("pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              eta = cms.PSet(
                                    pluginType = cms.string("PATMuJetPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta"),
                                    method     = cms.string("eta"),
                                    leadingOnly=cms.untracked.bool(True)

                              ),
                              muTauJJ = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mJJ"),
                                  method     = cms.string("mJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muTauJJPt = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ptJJ"),
                                  method     = cms.string("ptJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              muJetEta1 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("eta1"),
                                  method     = cms.string("leg1.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetEta2 = cms.PSet(
                                    pluginType = cms.string("PATMuJetPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta2"),
                                    method     = cms.string("leg2.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetPhi1 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("phi1"),
                                  method     = cms.string("leg1.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetPhi2 = cms.PSet(
                                    pluginType = cms.string("PATMuJetPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("phi2"),
                                    method     = cms.string("leg2.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetCharge = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge"),
                                  method     = cms.string("charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetMass = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mass"),
                                  method     = cms.string("mass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetMT1 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt1"),
                                  method     = cms.string("mt1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetMT = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt"),
                                  method     = cms.string("mt12MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetMT2 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt2"),
                                  method     = cms.string("mt2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetMET = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("met"),
                                  method     = cms.string("calibratedMET.pt()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetGenMET = cms.PSet(
                                  pluginType = cms.string("PATGenMETFiller"),
                                  src        = cms.InputTag("genMetTrue"),
                                  tag        = cms.string("genMET"),
                                  method     = cms.string("pt()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetDPhi = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi"),
                                  method     = cms.string("dPhi12"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetDR = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dR"),
                                  method     = cms.string("dR12"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              muJetDPhi1MET = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi1MET"),
                                  method     = cms.string("dPhi1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetDPhi2MET = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi2MET"),
                                  method     = cms.string("dPhi2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetHT = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ht"),
                                  method     = cms.string("ht"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetVBFDEta = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfDEta"),
                                  method     = cms.string("vbfDEta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetVBFPt1 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt1"),
                                  method     = cms.string("vbfPt1"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetVBFPt2 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt2"),
                                  method     = cms.string("vbfPt2"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetVBFEta1 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta1"),
                                  method     = cms.string("vbfEta1"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetVBFEta2 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta2"),
                                  method     = cms.string("vbfEta2"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetVBFMass = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfMass"),
                                  method     = cms.string("vbfMass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuVBFJets20 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap20"),
                                  method     = cms.string("vbfNJetsGap20"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muMuVBFJets30 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap30"),
                                  method     = cms.string("vbfNJetsGap30"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),

                              muJetRelStdIso03 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lStdRelIso"),
                                  method     = cms.string('(leg1.isolationR03.sumPt+leg1.isolationR03.emEt+leg1.isolationR03.hadEt)/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetRelPFIsoDB = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lPfRelIsoDeltaBeta"),
                                  method     = cms.string('(leg1.chargedHadronIso+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetRelPFIsoRho = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lPfRelIsoRho"),
                                  method     = cms.string('(leg1.chargedHadronIso+max(leg1.photonIso()+leg1.neutralHadronIso()-leg1.userFloat("rho")*3.14*0.4*0.4,0.0))/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetRelPFIso = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lPfRelIso"),
                                  method     = cms.string('(leg1.chargedHadronIso+leg1.photonIso()+leg1.neutralHadronIso())/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetPzeta = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZeta"),
                                  method     = cms.string('pZeta-1.5*pZetaVis'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetPZ = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZ"),
                                  method     = cms.string('pZeta'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetPZV = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZV"),
                                  method     = cms.string('pZetaVis'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetHadMass = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauMass"),
                                  method     = cms.string('leg2.mass()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag2Pt20 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag2Pt20M = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag2Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag3Pt20 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag3Pt20M = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag3Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag2Pt30 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag2Pt30M = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag2Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag3Pt30 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag3Pt30M = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsBTag3Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsPt30 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt30"),
                                  method     = cms.string('pt()>30'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsPt30Tag = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsPt30TagMatch = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30Matched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsPt30TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30NotMatched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsPt20 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt20"),
                                  method     = cms.string('pt()>20'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsPt20Tag = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsPt20TagMatch = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20Matched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetJetsPt20TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20NotMatched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetGenPt1 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt1"),
                                  method     = cms.string('p4VisLeg1gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetGenPt2 = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt2"),
                                  method     = cms.string('p4VisLeg2gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetGenVisMass = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genVisMass"),
                                  method     = cms.string('p4VisGen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetGenMass = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genFullMass"),
                                  method     = cms.string('p4gen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muJetFirstJetPt = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetPt"),
                                  method     = cms.string('pt()'),
                              ),
                              muJetFirstJetFlavour = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetFlavour"),
                                  method     = cms.string('partonFlavour()'),
                              ),
                              muJetFirstJetShape = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetShape"),
                                  method     = cms.string('userFloat("ptRMS")'),
                              ),
                              muJetFirstJetChMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNCharged"),
                                  method     = cms.string('chargedMultiplicity()'),
                              ),
                              muJetFirstJetNeutMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATMuJetPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNNeutral"),
                                  method     = cms.string('photonMultiplicity()+neutralHadronMultiplicity()'),
                              ),
                              PVs = cms.PSet(
                                    pluginType = cms.string("VertexSizeFiller"),
                                    src        = cms.InputTag("primaryVertexFilter"),
                                    tag        = cms.string("vertices")
                              ),
                              mumuSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(srcLL),
                                    tag        = cms.string("diLeptons"),
                              ),
                              genTaus = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag("genTauCands"),
                                    tag        = cms.string("genTaus"),
                              ),

                              muJetSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("nCands"),
                              )
   )

   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)



def addTauTauEventTree(process,name,src = 'diTausTauMuonVeto', srcMM = 'osDiMuons',srcEE = 'osDiElectrons'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              coreCollections = cms.VInputTag(
                                   cms.InputTag(src)
                              ),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src        = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                                  ),
                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("addPileupInfo"),
                                  tag        = cms.string("pu"),
                                  ),
                                  
                              pt1 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pt1"),
                                  method     = cms.string("leg1.pt"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              pt2 = cms.PSet(
                                    pluginType = cms.string("PATDiTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt2"),
                                    method     = cms.string("leg2.pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              charge1 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge1"),
                                  method     = cms.string("leg1.charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              charge2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge2"),
                                  method     = cms.string("leg2.charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              pt = cms.PSet(
                                    pluginType = cms.string("PATDiTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt"),
                                    method     = cms.string("pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              eta = cms.PSet(
                                    pluginType = cms.string("PATDiTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta"),
                                    method     = cms.string("eta"),
                                    leadingOnly=cms.untracked.bool(True)

                              ),
                              ditauEta1 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("eta1"),
                                  method     = cms.string("leg1.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauEta2 = cms.PSet(
                                    pluginType = cms.string("PATDiTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta2"),
                                    method     = cms.string("leg2.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauPhi1 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("phi1"),
                                  method     = cms.string("leg1.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauPhi2 = cms.PSet(
                                    pluginType = cms.string("PATDiTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("phi2"),
                                    method     = cms.string("leg2.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauDZ = cms.PSet(
                                    pluginType = cms.string("PATDiTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("dz"),
                                    method     = cms.string("dz"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauDCA = cms.PSet(
                                    pluginType = cms.string("PATDiTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("dca"),
                                    method     = cms.string("dca"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauDist = cms.PSet(
                                    pluginType = cms.string("PATDiTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("xPointDist"),
                                    method     = cms.string("crossingPointDistance"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              projMET = cms.PSet(
                                    pluginType = cms.string("PATDiTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("projMET"),
                                    method     = cms.string("projMET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauCharge = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge"),
                                  method     = cms.string("charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauMass = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mass"),
                                  method     = cms.string("mass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauMT1 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt1"),
                                  method     = cms.string("mt1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauMT = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt"),
                                  method     = cms.string("mt12MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauMT2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt2"),
                                  method     = cms.string("mt2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauMET = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("met"),
                                  method     = cms.string("calibratedMET.pt()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauGenMET = cms.PSet(
                                  pluginType = cms.string("PATGenMETFiller"),
                                  src        = cms.InputTag("genMetTrue"),
                                  tag        = cms.string("genMET"),
                                  method     = cms.string("pt()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauDPhi = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi"),
                                  method     = cms.string("dPhi12"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauDPhi1MET = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi1MET"),
                                  method     = cms.string("dPhi1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauDPhi2MET = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi2MET"),
                                  method     = cms.string("dPhi2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauHT = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ht"),
                                  method     = cms.string("ht"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauVBFDEta = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfDEta"),
                                  method     = cms.string("vbfDEta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauVBFMass = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfMass"),
                                  method     = cms.string("vbfMass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauDecayMode1 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t1DecayMode"),
                                  method     = cms.string('leg1.decayMode()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauDecayMode2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t2DecayMode"),
                                  method     = cms.string('leg2.decayMode()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauTauTriggerMatch1 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t1Trigger"),
                                  method     = cms.string('leg1.userFloat("hltFilterDoubleIsoPFTau20Trk5LeadTrack5IsolationL1HLTMatched")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauTauTriggerMatch2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t2Trigger"),
                                  method     = cms.string('leg2.userFloat("hltFilterDoubleIsoPFTau20Trk5LeadTrack5IsolationL1HLTMatched")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauPzeta = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZeta"),
                                  method     = cms.string('pZeta-1.5*pZetaVis'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauPZ = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZ"),
                                  method     = cms.string('pZeta'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauPZV = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZV"),
                                  method     = cms.string('pZetaVis'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauHadMass = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t1Mass"),
                                  method     = cms.string('leg1.mass()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauHadMass2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t2Mass"),
                                  method     = cms.string('leg2.mass()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauVLooseIso = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t1VLooseIso"),
                                  method     = cms.string('leg1.tauID("byVLooseIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauLooseIso = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t1LooseIso"),
                                  method     = cms.string('leg1.tauID("byLooseIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauMediumIso = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t1MediumIso"),
                                  method     = cms.string('leg1.tauID("byMediumIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauTightIso = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),

                                  tag        = cms.string("t1TightIso"),
                                  method     = cms.string('leg1.tauID("byTightIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauAbsIsoRho = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t1AbsIsoRho"),
                                  method     = cms.string('leg1.isolationPFChargedHadrCandsPtSum()+max(0.0,leg1.isolationPFGammaCandsEtSum()-leg1.userFloat("rho")*3.14*0.5*0.5)'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauAbsIso = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t1AbsIso"),
                                  method     = cms.string('leg1.isolationPFChargedHadrCandsPtSum()+max(0.0,leg1.isolationPFGammaCandsEtSum())'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauAbsIsoDB = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t1AbsIsoDeltaBeta"),
                                  method     = cms.string('leg1.isolationPFChargedHadrCandsPtSum()+max(0.0,leg1.isolationPFGammaCandsEtSum()-0.35*leg1.particleIso())'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              ditauVLooseIso2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t2VLooseIso"),
                                  method     = cms.string('leg2.tauID("byVLooseIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauLooseIso2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t2LooseIso"),
                                  method     = cms.string('leg2.tauID("byLooseIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauMediumIso2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t2MediumIso"),
                                  method     = cms.string('leg2.tauID("byMediumIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauTightIso2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),

                                  tag        = cms.string("t2TightIso"),
                                  method     = cms.string('leg2.tauID("byTightIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauAbsIsoRho2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t2AbsIsoRho"),
                                  method     = cms.string('leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.isolationPFGammaCandsEtSum()-leg2.userFloat("rho")*3.14*0.5*0.5)'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauAbsIso2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t2AbsIso"),
                                  method     = cms.string('leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.isolationPFGammaCandsEtSum())'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauAbsIsoDB2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("t2AbsIsoDeltaBeta"),
                                  method     = cms.string('leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.isolationPFGammaCandsEtSum()-0.35*leg2.particleIso())'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag2Pt20 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag2Pt20M = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag2Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag3Pt20 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag3Pt20M = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag3Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag2Pt30 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag2Pt30M = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag2Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag3Pt30 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag3Pt30M = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsBTag3Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsPt30 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt30"),
                                  method     = cms.string('pt()>30'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsPt30Tag = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsPt30TagMatch = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30Matched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsPt30TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30NotMatched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsPt20 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt20"),
                                  method     = cms.string('pt()>20'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsPt20Tag = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsPt20TagMatch = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20Matched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauJetsPt20TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20NotMatched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauGenPt1 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt1"),
                                  method     = cms.string('p4VisLeg1gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauGenPt2 = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt2"),
                                  method     = cms.string('p4VisLeg2gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauGenVisMass = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genVisMass"),
                                  method     = cms.string('p4VisGen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauGenMass = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genFullMass"),
                                  method     = cms.string('p4gen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              ditauFirstJetPt = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetPt"),
                                  method     = cms.string('pt()'),
                              ),
                              ditauFirstJetFlavour = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetFlavour"),
                                  method     = cms.string('partonFlavour()'),
                              ),
                              ditauFirstJetShape = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetShape"),
                                  method     = cms.string('userFloat("ptRMS")'),
                              ),
                              ditauFirstJetChMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNCharged"),
                                  method     = cms.string('chargedMultiplicity()'),
                              ),
                              ditauFirstJetNeutMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATDiTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNNeutral"),
                                  method     = cms.string('photonMultiplicity()+neutralHadronMultiplicity()'),
                              ),
                              PVs = cms.PSet(
                                    pluginType = cms.string("VertexSizeFiller"),
                                    src        = cms.InputTag("primaryVertexFilter"),
                                    tag        = cms.string("vertices")
                              ),
                              genTaus = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag("genTauCands"),
                                    tag        = cms.string("genTaus"),
                              ),

                              ditauSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("nCands"),
                              ),
                              dimuSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(srcMM),
                                    tag        = cms.string("diLetons1"),
                              ),
                              dieleSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(srcEE),
                                    tag        = cms.string("diLeptons2"),
                              )

   )

   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)









#
#Tree for Mu+Mu + MET final state
#
def addMuMuEventTree(process,name,src = 'zMuMuCandidatesID'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              coreCollections = cms.VInputTag(
                                   cms.InputTag(src)
                              ),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src        = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                              ),
                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("addPileupInfo"),
                                  tag        = cms.string("pu"),
                                  ),

                              mumuPt1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pt1"),
                                  method     = cms.string("leg1.pt"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPt2 = cms.PSet(
                                    pluginType = cms.string("PATMuPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt2"),
                                    method     = cms.string("leg2.pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuJJ = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mJJ"),
                                  method     = cms.string("mJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuJJPt = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ptJJ"),
                                  method     = cms.string("ptJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              mumuPt = cms.PSet(
                                    pluginType = cms.string("PATMuPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt"),
                                    method     = cms.string("pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuSVFit = cms.PSet(
                                    pluginType = cms.string("PATMuSVFitFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("sv_")
                              ),
                              mumuEta1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("eta1"),
                                  method     = cms.string("leg1.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuEta2 = cms.PSet(
                                    pluginType = cms.string("PATMuPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta2"),
                                    method     = cms.string("leg2.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPhi1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("phi1"),
                                  method     = cms.string("leg1.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPhi2 = cms.PSet(
                                    pluginType = cms.string("PATMuPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("phi2"),
                                    method     = cms.string("leg2.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuCharge = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge"),
                                  method     = cms.string("charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuTriggerMatch1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1Trigger"),
                                  method     = cms.string('leg1.triggerObjectMatchesByPath("*",1).size()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuTriggerMatch2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2Trigger"),
                                  method     = cms.string('leg2.triggerObjectMatchesByPath("*",1).size()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuMass = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mass"),
                                  method     = cms.string("mass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuMT1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt1"),
                                  method     = cms.string("mt1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuMT = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt"),
                                  method     = cms.string("mt12MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuMT2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt2"),
                                  method     = cms.string("mt2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuMET = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("met"),
                                  method     = cms.string("met.pt()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuDPhi = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi"),
                                  method     = cms.string("dPhi12"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuDPhi1MET = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi1MET"),
                                  method     = cms.string("dPhi1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuDPhi2MET = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi2MET"),
                                  method     = cms.string("dPhi2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuHT = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ht"),
                                  method     = cms.string("ht"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuRelStdIso2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1StdRelIso"),
                                  method     = cms.string('(leg1.isolationR03.sumPt+leg1.isolationR03.emEt+leg1.isolationR03.hadEt)/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuRelStdIso1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2StdRelIso"),
                                  method     = cms.string('(leg2.isolationR03.sumPt+leg2.isolationR03.emEt+leg2.isolationR03.hadEt)/leg2.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuChargeIso1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1ChargeIso"),
                                  method     = cms.string('leg1.chargedHadronIso'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuNeutralIso1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1NeutralIso"),
                                  method     = cms.string('(leg1.photonIso+leg1.neutralHadronIso())'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPUIso1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1PUIso"),
                                  method     = cms.string('leg1.userIso(0)'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPUIsoLow1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1PUIsoLow"),
                                  method     = cms.string('leg1.userIso(1)'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              mumuChargeIso2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2ChargeIso"),
                                  method     = cms.string('leg2.chargedHadronIso'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuNeutralIso2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2NeutralIso"),
                                  method     = cms.string('(leg2.photonIso+leg2.neutralHadronIso())'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPUIso2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2PUIso"),
                                  method     = cms.string('leg2.userIso(0)'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPUIsoLow2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2PUIsoLow"),
                                  method     = cms.string('leg2.userIso(1)'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuPzeta = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZeta"),
                                  method     = cms.string('pZeta-1.5*pZetaVis'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuJetsBTag2Pt20 = cms.PSet(
                                  pluginType = cms.string("PATMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuJetsBTag3Pt20 = cms.PSet(
                                  pluginType = cms.string("PATMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuJetsBTag2Pt30 = cms.PSet(
                                  pluginType = cms.string("PATMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuJetsBTag3Pt30 = cms.PSet(
                                  pluginType = cms.string("PATMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuJetsPt20 = cms.PSet(
                                  pluginType = cms.string("PATMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt20"),
                                  method     = cms.string('pt()>20'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuJetsPt30 = cms.PSet(
                                  pluginType = cms.string("PATMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt30"),
                                  method     = cms.string('pt()>30'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuJetsPt30Tag = cms.PSet(
                                  pluginType = cms.string("PATMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuJetsPt20Tag = cms.PSet(
                                  pluginType = cms.string("PATMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuDZ = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dz"),
                                  method     = cms.string("dz"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuDCA = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dca"),
                                  method     = cms.string("dca"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuDist = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("xPointDist"),
                                  method     = cms.string("dca"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuGenPt1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt1"),
                                  method     = cms.string('p4VisLeg1gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuGenPt2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt2"),
                                  method     = cms.string('p4VisLeg2gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuGenVisMass = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genVisMass"),
                                  method     = cms.string('p4VisGen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuGenMass = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genMass"),
                                  method     = cms.string('p4gen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              PVs = cms.PSet(
                                    pluginType = cms.string("VertexSizeFiller"),
                                    src        = cms.InputTag("primaryVertexFilter"),
                                    tag        = cms.string("vertices")
                              ),
                              muMuRho = cms.PSet(
                                  pluginType = cms.string("EventWeightFiller"),
                                  src        = cms.InputTag("kt6PFJets","rho"),
                                  tag        = cms.string("Rho")
                              ),
                              muMuVBFDEta = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfDEta"),
                                  method     = cms.string("vbfDEta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuVBFMass = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfMass"),
                                  method     = cms.string("vbfMass"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muMuVBFJets20 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap20"),
                                  method     = cms.string("vbfNJetsGap20"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muMuVBFJets30 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap30"),
                                  method     = cms.string("vbfNJetsGap30"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muMuVBFPt1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt1"),
                                  method     = cms.string("vbfPt1"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muMuVBFPt2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt2"),
                                  method     = cms.string("vbfPt2"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muMuVBFEta1 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta1"),
                                  method     = cms.string("vbfEta1"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muMuVBFEta2 = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta2"),
                                  method     = cms.string("vbfEta2"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              muMuRecoilPx = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("recoilPx"),
                                  method     = cms.string("recoil.x()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuRecoilPy = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("recoilPy"),
                                  method     = cms.string("recoil.y()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuPX = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("px"),
                                  method     = cms.string("px"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              muMuFirstJetPt = cms.PSet(
                                  pluginType = cms.string("PATMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetPt"),
                                  method     = cms.string('pt()'),
                              ),
                              muMuFirstJetEta = cms.PSet(
                                  pluginType = cms.string("PATMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetEta"),
                                  method     = cms.string('eta()'),
                              ),
                              muMuFirstJetFlavour = cms.PSet(
                                  pluginType = cms.string("PATMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetFlavour"),
                                  method     = cms.string('partonFlavour()'),
                              ),
                              muMuFirstJetShape = cms.PSet(
                                  pluginType = cms.string("PATMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetShape"),
                                  method     = cms.string('userFloat("ptRMS")'),
                              ),
                              muMuFirstJetChMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNCharged"),
                                  method     = cms.string('chargedMultiplicity()'),
                              ),
                              muMuFirstJetNeutMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNNeutral"),
                                  method     = cms.string('photonMultiplicity()+neutralHadronMultiplicity()'),
                              ),
                              muMuPY = cms.PSet(
                                  pluginType = cms.string("PATMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("py"),
                                  method     = cms.string("py"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("mumuSize"),
                              )
   )

   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)

##Tree for e+mu +MET final state
def addEleMuEventTree(process,name,src='eleMuonsSorted'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              coreCollections = cms.VInputTag(
                                   cms.InputTag(src)
                              ),
                              genTaus = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag("genTauCands"),
                                    tag        = cms.string("genTaus"),
                              ),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src        = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                              ),
                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("addPileupInfo"),
                                  tag        = cms.string("pu"),
                              ),
                              eleMuJJ = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mJJ"),
                                  method     = cms.string("mJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJJPt = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ptJJ"),
                                  method     = cms.string("ptJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleMuPt1 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pt1"),
                                  method     = cms.string("leg1.pt"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuPt2 = cms.PSet(
                                    pluginType = cms.string("PATEleMuPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt2"),
                                    method     = cms.string("leg2.pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuPt = cms.PSet(
                                    pluginType = cms.string("PATEleMuPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt"),
                                    method     = cms.string("pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuDXY = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2DXY"),
                                  method     = cms.string('leg2.dB()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuEleDXY = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1DXY"),
                                  method     = cms.string('leg1.dB()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuWW = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1WWID"),
                                  method     = cms.string('leg1.userFloat("WWID")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuWWMVA = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1WWMVA"),
                                  method     = cms.string('leg1.userFloat("WWMVAID")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuEta = cms.PSet(
                                    pluginType = cms.string("PATEleMuPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta"),
                                    method     = cms.string("eta"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuSVFit = cms.PSet(
                                    pluginType = cms.string("PATEleMuSVFitFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("sv_")
                              ),
                              eleMuEta1 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("eta1"),
                                  method     = cms.string("leg1.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuEta2 = cms.PSet(
                                    pluginType = cms.string("PATEleMuPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta2"),
                                    method     = cms.string("leg2.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuPhi1 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("phi1"),
                                  method     = cms.string("leg1.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuPhi2 = cms.PSet(
                                    pluginType = cms.string("PATEleMuPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("phi2"),
                                    method     = cms.string("leg2.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuMuTriggerMatch1= cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1TriggerMu17E8"),
                                  method     = cms.string('leg1.userFloat("hltL1NonIsoHLTNonIsoMu17Ele8PixelMatchFilter")+leg1.userFloat("hltMu17Ele8CaloIdTPixelMatchFilter")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuMuTriggerMatch2= cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2TriggerMu17E8"),
                                  method     = cms.string('leg2.userFloat("hltL1Mu3EG5L3Filtered17")+leg2.userFloat("hltL1Mu7EG5L3MuFiltered17")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuMuTriggerMatch3= cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1TriggerE17Mu8"),
                                  method     = cms.string('leg1.userFloat("hltL1NonIsoHLTNonIsoMu8Ele17PixelMatchFilter")+leg1.userFloat("hltMu8Ele17CaloIdTCaloIsoVLPixelMatchFilter")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuMuTriggerMatch4= cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2TriggerE17Mu8"),
                                  method     = cms.string('leg2.userFloat("hltL1MuOpenEG12L3Filtered8")+leg2.userFloat("hltL1Mu3EG5L3Filtered8")+leg2.userFloat("hltL1MuOpenEG5L3Filtered8")+leg2.userFloat("hltL1MuOpenEG8L3Filtered8")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMudca = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dca"),
                                  method     = cms.string("dca"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuXDist = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("xPointDist"),
                                  method     = cms.string("crossingPointDistance"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleMuCharge = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge"),
                                  method     = cms.string("charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuMass = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mass"),
                                  method     = cms.string("mass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuMT1 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt1"),
                                  method     = cms.string("mt1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuMT = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt"),
                                  method     = cms.string("mt12MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuMT2 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt2"),
                                  method     = cms.string("mt2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuMET = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("met"),
                                  method     = cms.string("met.pt()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuPMET = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("projMET"),
                                  method     = cms.string("projMET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuDPhi = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi"),
                                  method     = cms.string("dPhi12"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuDPhi1MET = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi1MET"),
                                  method     = cms.string("dPhi1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuDPhi2MET = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dPhi2MET"),
                                  method     = cms.string("dPhi2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuHT = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ht"),
                                  method     = cms.string("ht"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuRelStdIso03 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2StdRelIso"),
                                  method     = cms.string('(leg2.isolationR03.sumPt+leg2.isolationR03.emEt+leg2.isolationR03.hadEt)/leg2.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuRelPFIso = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2RelPFIso"),
                                  method     = cms.string('(leg2.chargedHadronIso+leg2.photonIso+leg2.neutralHadronIso)/leg2.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuRelPFIsoDB = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2RelPfIsoDeltaBeta"),
                                  method     = cms.string('(leg2.chargedHadronIso+max(leg2.photonIso+leg2.neutralHadronIso-0.5*leg2.userIso(0),0.0))/leg2.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuAbsPFIsoDB = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l2AbsPfIsoDeltaBeta"),
                                  method     = cms.string('(leg2.chargedHadronIso+max(leg2.photonIso+leg2.neutralHadronIso-0.5*leg2.userIso(0),0.0))'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleMuPzeta = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZeta"),
                                  method     = cms.string('pZeta-1.85*pZetaVis'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag2Pt30 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag2Pt30M = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag2Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag3Pt30 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag3Pt30M = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag3Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleMuJetsBTag2Pt20 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag2Pt20M = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag2Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag3Pt20 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag3Pt20M = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsBTag3Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsPt20 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt20"),
                                  method     = cms.string('pt()>20'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsPt20Tag = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsPt20TagMatch = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20Matched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsPt20TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20NotMatched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsPt30 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt30"),
                                  method     = cms.string('pt()>30'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsPt30Tag = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsPt30TagMatch = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30Matched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuJetsPt30TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30NotMatched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuElePFRelIsoDB = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1RelPfIsoDeltaBetaStd"),
                                  method     = cms.string('(leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuElePFRelIsoDBNew = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1RelPfIsoDeltaBeta"),
                                  method     = cms.string('leg1.isEB()*(leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))/leg1.pt()+leg1.isEE()*(leg1.chargedHadronIso()+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuElePFAbsIsoDBNew = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1AbsIsoDeltaBeta"),
                                  method     = cms.string('leg1.isEB()*(leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))+leg1.isEE()*(leg1.chargedHadronIso()+max(leg1.userIso(1)+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleMuElePFRelIso = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1RelPfIso"),
                                  method     = cms.string('(leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso(),0.0))/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuVBFDEta = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfDEta"),
                                  method     = cms.string("vbfDEta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuVBFMass = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfMass"),
                                  method     = cms.string("vbfMass"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              eleMuVBFPt1 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt1"),
                                  method     = cms.string("vbfPt1"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuVBFPt2 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt2"),
                                  method     = cms.string("vbfPt2"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuVBFEta1 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta1"),
                                  method     = cms.string("vbfEta1"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuVBFEta2 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta2"),
                                  method     = cms.string("vbfEta2"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleMuVBFJets20 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap20"),
                                  method     = cms.string("vbfNJetsGap20"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              eleMuVBFJets30 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap30"),
                                  method     = cms.string("vbfNJetsGap30"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              eleMuGenPt1 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt1"),
                                  method     = cms.string('p4VisLeg1gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),



                              eleMuGenPt2 = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt2"),
                                  method     = cms.string('p4VisLeg2gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuGenVisMass = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("visMass"),
                                  method     = cms.string('p4VisGen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleMuGenMass = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genMass"),
                                  method     = cms.string('p4gen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleMuFirstJetPt = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetPt"),
                                  method     = cms.string('pt()'),
                              ),
                              eleMuFirstJetEta = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetEta"),
                                  method     = cms.string('eta()'),
                              ),

                              eleMuFirstJetFlavour = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetFlavour"),
                                  method     = cms.string('partonFlavour()'),
                              ),
                              eleMuFirstJetShape = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetShape"),
                                  method     = cms.string('userFloat("ptRMS")'),
                              ),
                              eleMuFirstJetChMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNCharged"),
                                  method     = cms.string('chargedMultiplicity()'),
                              ),
                              eleMuFirstJetNeutMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATEleMuPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNNeutral"),
                                  method     = cms.string('photonMultiplicity()+neutralHadronMultiplicity()'),
                              ),
                              eleMuEmbedWeight = cms.PSet(
                                    pluginType = cms.string("EventWeightFiller"),
                                    src        = cms.InputTag("generator","weight"),
                                    tag        = cms.string("embeddedWeight"),
                              ),
                              PVs = cms.PSet(
                                    pluginType = cms.string("VertexSizeFiller"),
                                    src        = cms.InputTag("primaryVertexFilter"),
                                    tag        = cms.string("vertices")

                              ),


                              eleMuSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eleMuSize"),

                              ),
                              higgsPt = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("higgsPt"),
                                  method     = cms.string('pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              mumuSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag('diMuonsSorted'),
                                    tag        = cms.string("diLeptons1"),
                              ),
                              eeSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag('osDiElectrons'),
                                    tag        = cms.string("diLeptons2"),
                              ),
                              eleMuEmbedPt = cms.PSet(
                                    pluginType = cms.string("PATGenParticleFiller"),
                                    src        = cms.InputTag("genDaughters"),
                                    tag        = cms.string("embeddedPt"),
                                    method     = cms.string("pt"),
                                    leadingOnly=cms.untracked.bool(False)

                              ),
                              eleMuEmbedEta = cms.PSet(
                                    pluginType = cms.string("PATGenParticleFiller"),
                                    src        = cms.InputTag("genDaughters"),
                                    tag        = cms.string("embeddedEta"),
                                    method     = cms.string("eta"),
                                    leadingOnly=cms.untracked.bool(False)
                              )



   )



   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)

#Tree for e+tau + MET final state
def addEleTauEventTree(process,name,src='eleTausSorted',srcLL='osDiElectrons',srcLT='eleTracksSorted',srcLG='eleGSFTracksSorted'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              coreCollections = cms.VInputTag(
                                   cms.InputTag(src)
                              ),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src        = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(
                                      TriggerPaths
                                  )
                              ),
                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("addPileupInfo"),
                                  tag        = cms.string("pu"),
                              ),
                              eleTauRho = cms.PSet(
                                  pluginType = cms.string("EventWeightFiller"),
                                  src        = cms.InputTag("kt6PFJets","rho"),
                                  tag        = cms.string("Rho")
                              ),
                             genTaus = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag("genTauCands"),
                                    tag        = cms.string("genTaus"),
                              ),
                              eleTauPt1 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pt1"),
                                  method     = cms.string("leg1.pt"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauPdg1 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pdg1"),
                                  method     = cms.string("genPdg1()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauPdg2 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pdg2"),
                                  method     = cms.string("genPdg2()"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleTauPt2 = cms.PSet(
                                    pluginType = cms.string("PATEleTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt2"),
                                    method     = cms.string("leg2.pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauPt = cms.PSet(
                                    pluginType = cms.string("PATEleTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("pt"),
                                    method     = cms.string("pt"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauEta1 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("eta1"),
                                  method     = cms.string("leg1.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauWW = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("WWID"),
                                  method     = cms.string('leg1.userFloat("WWID")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauWWMVA = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("WWMVA"),
                                  method     = cms.string('leg1.userFloat("WWMVAID")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauEleTriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lTrigger"),
                                  method     = cms.string('leg1.userFloat("hltOverlapFilterIsoEle15IsoPFTau20")+leg1.userFloat("hltOverlapFilterIsoEle15IsoPFTau15")+leg1.userFloat("hltOverlapFilterIsoEle15TightIsoPFTau20")+leg1.userFloat("hltOverlapFilterIsoEle18MediumIsoPFTau20")+leg1.userFloat("hltOverlapFilterIsoEle20MediumIsoPFTau20")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTautauTriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauTrigger"),
                                  method     = cms.string('leg2.userFloat("hltOverlapFilterIsoEle15IsoPFTau20")+leg2.userFloat("hltOverlapFilterIsoEle15IsoPFTau15")+leg2.userFloat("hltOverlapFilterIsoEle15TightIsoPFTau20")+leg2.userFloat("hltOverlapFilterIsoEle18MediumIsoPFTau20")+leg2.userFloat("hltOverlapFilterIsoEle20MediumIsoPFTau20")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTautau2TriggerMatch = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("Ele15Tau20"),
                                  method     = cms.string('leg2.userFloat("hltOverlapFilterIsoEle15IsoPFTau20")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauEta2 = cms.PSet(
                                    pluginType = cms.string("PATEleTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta2"),
                                    method     = cms.string("leg2.eta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauEleDXY = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("l1DB"),
                                  method     = cms.string('leg1.dB()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauPhi1 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("phi1"),
                                  method     = cms.string("leg1.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauPhi2 = cms.PSet(
                                    pluginType = cms.string("PATEleTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("phi2"),
                                    method     = cms.string("leg2.phi"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauDZ = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dz"),
                                  method     = cms.string("dz"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauDCA = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("dca"),
                                  method     = cms.string("dca"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauDist = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("xPointDist"),
                                  method     = cms.string("dca"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauEta = cms.PSet(
                                    pluginType = cms.string("PATEleTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eta"),
                                    method     = cms.string("eta"),
                                    leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauSVFit = cms.PSet(
                                    pluginType = cms.string("PATEleTauSVFitFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("sv_")
                              ),
                              eleTauRelIso03B = cms.PSet(
                                    pluginType = cms.string("PATEleTauPairFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("lStandardRelIso"),
                                    method     = cms.string("leg1.isEB()*((leg1.dr03TkSumPt()+max(leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.dr03HcalTowerSumEt())/leg1.pt())+leg1.isEE()*((leg1.dr03TkSumPt()+leg1.dr03EcalRecHitSumEt()+leg1.dr03HcalTowerSumEt())/leg1.pt())"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),


                              eleTauCharge = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("charge"),
                                  method     = cms.string("charge"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauMass = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mass"),
                                  method     = cms.string("mass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauMT1 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mt1"),
                                  method     = cms.string("mt1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauMT2 = cms.PSet(
                                  pluginType =cms.string("PATEleTauPairFiller"),
                                  src = cms.InputTag(src),
                                  tag =cms.string("mt2"),
                                  method =cms.string("mt2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauMET = cms.PSet(
                                  pluginType= cms.string("PATEleTauPairFiller"),
                                  src = cms.InputTag(src),
                                  tag =cms.string("met"),
                                  method =cms.string("met.pt()"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              eleTauDPhi = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src = cms.InputTag(src),
                                  tag =cms.string("dPhi"),
                                  method =cms.string("dPhi12"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              eleTauDPhi1MET = cms.PSet(
                                  pluginType =cms.string("PATEleTauPairFiller"),
                                  src = cms.InputTag(src),
                                  tag =cms.string("dPhi1MET"),
                                  method =cms.string("dPhi1MET"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              eleTauDPhi2MET = cms.PSet(
                                  pluginType =cms.string("PATEleTauPairFiller"),
                                  src = cms.InputTag(src),
                                  tag = cms.string("dPhi2MET"),
                                  method = cms.string("dPhi2MET"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              eleTauHT = cms.PSet(
                                  pluginType =cms.string("PATEleTauPairFiller"),
                                  src = cms.InputTag(src),
                                  tag = cms.string("ht"),
                                  method =cms.string("ht"),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              eleTauPFRelIso = cms.PSet(
                                  pluginType =cms.string("PATEleTauPairFiller"),
                                  src = cms.InputTag(src),
                                  tag = cms.string("lPfRelIso"),
                                  method =cms.string('(leg1.chargedHadronIso+leg1.photonIso+leg1.neutralHadronIso)/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              eleTauPFRelIsoDBOld = cms.PSet(
                                  pluginType =cms.string("PATEleTauPairFiller"),
                                  src = cms.InputTag(src),
                                  tag =cms.string("lPfRelIsoDeltaBetaStd"),
                                  method = cms.string('(leg1.chargedHadronIso+max(leg1.photonIso+leg1.neutralHadronIso-0.5*leg1.userIso(0),0.0))/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              eleTauPFRelIsoDB = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src = cms.InputTag(src),
                                  tag =cms.string("lPfRelIsoDeltaBeta"),
                                  method =cms.string('leg1.isEB()*(leg1.chargedHadronIso+max(leg1.photonIso+leg1.neutralHadronIso-0.5*leg1.userIso(0),0.0))/leg1.pt()+leg1.isEE()*(leg1.chargedHadronIso+max(leg1.userIso(1)+leg1.neutralHadronIso-0.5*leg1.userIso(0),0.0))/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                                  ),
                              eleTauDefPFRelIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lDefPfRelIso"),
                                  method     = cms.string('(leg1.pfIsolationVariables().chargedHadronIso+leg1.pfIsolationVariables().photonIso+leg1.pfIsolationVariables().neutralHadronIso)/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauDefPFRelIsoDB = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("lDefPfRelIsoDB"),
                                  method     = cms.string('(leg1.pfIsolationVariables().chargedHadronIso+max(leg1.pfIsolationVariables().photonIso+leg1.pfIsolationVariables().neutralHadronIso-0.5*leg1.particleIso(),0.0))/leg1.pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleTauProngs = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauProngs"),
                                  method     = cms.string('leg2.signalPFChargedHadrCands.size()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauElectronDecision = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauElectronVeto"),
                                  method     = cms.string('leg2.tauID("againstElectronTight")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauElectronMVAPass = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauElectronMVAPass"),
                                  method     = cms.string('leg2.tauID("againstElectronMVA")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauPzeta = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("pZeta"),
                                  method     = cms.string('pZeta-1.5*pZetaVis'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauProjMET = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("projMET"),
                                  method     = cms.string('projMET'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauHadMass = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauMass"),
                                  method     = cms.string('leg2.mass()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauDecayMode = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauMode"),
                                  method     = cms.string('leg2.decayMode()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauE = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauE"),
                                  method     = cms.string('leg2.leadPFCand().ecalEnergy()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauH = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauH"),
                                  method     = cms.string('leg2.leadPFCand().hcalEnergy()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauLC = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauLCharge"),
                                  method     = cms.string('leg2.leadPFCand().charge()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauP = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauKFP"),
                                  method     = cms.string('leg2.userFloat("leadingKFP")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauGP = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauGSFP"),
                                  method     = cms.string('leg2.userFloat("leadingGSFP")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),



                              eleTauGSFPixel = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauGSFHits"),
                                  method     = cms.string('leg2.userFloat("pixelHits")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauCrackVeto = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauCrackVeto"),
                                  method     = cms.string('leg2.userFloat("crackVeto")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleTauPT = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauPT"),
                                  method     = cms.string('leg2.leadPFCand().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauMVA = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauMVA"),
                                  method     = cms.string('leg2.userFloat("leadingMVA")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleTauCE = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauCE"),
                                  method     = cms.string('leg2.leadPFChargedHadrCand().ecalEnergy()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauCH = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauCH"),
                                  method     = cms.string('leg2.leadPFChargedHadrCand().hcalEnergy()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauCP = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauCP"),
                                  method     = cms.string('leg2.userFloat("leadingChargedKFP")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauCGP = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauCGP"),
                                  method     = cms.string('leg2.userFloat("leadingChargedGSFP")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleTauCPT = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauCPT"),
                                  method     = cms.string('leg2.leadPFChargedHadrCand().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauCEta = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauCEta"),
                                  method     = cms.string('leg2.leadPFChargedHadrCand().positionAtECALEntrance().eta()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauBREM = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauBrem"),
                                  method     = cms.string('leg2.userFloat("bremEnergy")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleTauCMVA = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauCMVA"),
                                  method     = cms.string('leg2.leadPFChargedHadrCand().mva_e_pi()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauGammas = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauGammas"),
                                  method     = cms.string('leg2.signalPFGammaCands.size()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauAbsIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauAbsIso"),
                                  method     = cms.string('leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.isolationPFGammaCandsEtSum())'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauAbsIsoDB = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauAbsIsoDeltaBeta"),
                                  method     = cms.string('leg2.isolationPFChargedHadrCandsPtSum()+max(0.0,leg2.isolationPFGammaCandsEtSum()-0.35*leg2.particleIso())'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauVLooseIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauVLooseIso"),
                                  method     = cms.string('leg2.tauID("byVLooseIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauLooseIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauLooseIso"),
                                  method     = cms.string('leg2.tauID("byLooseIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauMediumIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauMediumIso"),
                                  method     = cms.string('leg2.tauID("byMediumIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauTightIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauTightIso"),
                                  method     = cms.string('leg2.tauID("byTightIsolation")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauLooseDBPtIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauLooseIsoDBPt"),
                                  method     = cms.string('leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauVLooseDBPtIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauVLooseIsoDBPt"),
                                  method     = cms.string('leg2.tauID("byVLooseCombinedIsolationDeltaBetaCorr")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauMediumDBPtIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauMediumIsoDBPt"),
                                  method     = cms.string('leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauTightDBPtIso = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("tauTightIsoDBPt"),
                                  method     = cms.string('leg2.tauID("byTightCombinedIsolationDeltaBetaCorr")'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag2Pt30 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag2Pt30M = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag2Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag3Pt30 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag3Pt30M = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag3Pt30NM = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt30NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag2Pt20 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag2Pt20M = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag2Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag2Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=2&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag3Pt20 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag3Pt20M = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20Matched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsBTag3Pt20NM = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsBTag3Pt20NotMatched"),
                                  method     = cms.string('bDiscriminator("")>=3.3&&pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJets30 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt30"),
                                  method     = cms.string('pt()>30'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJets30Tag = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJets30TagMatch = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30Matched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJets30TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt30NotMatched"),
                                  method     = cms.string('pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJJ = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("mJJ"),
                                  method     = cms.string("mJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJJPt = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("ptJJ"),
                                  method     = cms.string("ptJJ"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleTauJets20 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt20"),
                                  method     = cms.string('pt()>20'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJets20Tag = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJets20TagMatch = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20Matched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJets20TagNoMatch = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nTaggableJetsPt20NotMatched"),
                                  method     = cms.string('pt()>20&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauVBFDEta = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfDEta"),
                                  method     = cms.string("vbfDEta"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauVBFMass = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfMass"),
                                  method     = cms.string("vbfMass"),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauVBFPt1 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt1"),
                                  method     = cms.string("vbfPt1"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              eleTauVBFPt2 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfPt2"),
                                  method     = cms.string("vbfPt2"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              eleTauVBFEta1 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta1"),
                                  method     = cms.string("vbfEta1"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              eleTauVBFEta2 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfEta2"),
                                  method     = cms.string("vbfEta2"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),

                              eleTauVBFJets20 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap20"),
                                  method     = cms.string("vbfNJetsGap20"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),
                              eleTauVBFJets30 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("vbfNJetsGap30"),
                                  method     = cms.string("vbfNJetsGap30"),
                                  leadingOnly=cms.untracked.bool(True)
                               ),


                              eleTauJetsPt30 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt30"),
                                  method     = cms.string('pt()>30'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauJetsPt20 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairJetCountFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("nJetsPt20"),
                                  method     = cms.string('pt()>20'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleTauGenPt1 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt1"),
                                  method     = cms.string('p4VisLeg1gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauGenPt2 = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genPt2"),
                                  method     = cms.string('p4VisLeg2gen().pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauGenVisMass = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genVisMass"),
                                  method     = cms.string('p4VisGen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauGenMass = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("genMass"),
                                  method     = cms.string('p4gen().M()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),

                              eleTauFirstJetPt = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetPt"),
                                  method     = cms.string('pt()'),
                              ),
                              eleTauFirstJetEta = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetEta"),
                                  method     = cms.string('eta()'),
                              ),
                              eleTauFirstJetFlavour = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetFlavour"),
                                  method     = cms.string('partonFlavour()'),
                              ),
                              eleTauFirstJetShape = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetShape"),
                                  method     = cms.string('userFloat("ptRMS")'),
                              ),
                              eleTauFirstJetChMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNCharged"),
                                  method     = cms.string('chargedMultiplicity()'),
                              ),
                              eleTauFirstJetNeutMultiplicity = cms.PSet(
                                  pluginType = cms.string("PATEleTauPairHighestPtJetVarFiller"),
                                  src        = cms.InputTag(src),
                                  tag        = cms.string("highestJetNNeutral"),
                                  method     = cms.string('photonMultiplicity()+neutralHadronMultiplicity()'),
                              ),
                              PVs = cms.PSet(
                                    pluginType = cms.string("VertexSizeFiller"),
                                    src        = cms.InputTag("primaryVertexFilter"),
                                    tag        = cms.string("vertices")
                              ),
                              eleeleSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(srcLL),
                                    tag        = cms.string("diLeptons"),

                              ),
                              eleTauEmbedWeight = cms.PSet(
                                    pluginType = cms.string("EventWeightFiller"),
                                    src        = cms.InputTag("generator","weight"),
                                    tag        = cms.string("embeddedWeight"),
                              ),
                              higgsPt = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("higgsPt"),
                                  method     = cms.string('pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauSize = cms.PSet(
                                    pluginType = cms.string("CollectionSizeFiller"),
                                    src        = cms.InputTag(src),
                                    tag        = cms.string("eleTauSize"),

                              ),
                              eleTauEmbedPt = cms.PSet(
                                    pluginType = cms.string("PATGenParticleFiller"),
                                    src        = cms.InputTag("genDaughters"),
                                    tag        = cms.string("embeddedPt"),
                                    method     = cms.string("pt"),
                                    leadingOnly=cms.untracked.bool(False)

                              ),
                              eleTauEmbedEta = cms.PSet(
                                    pluginType = cms.string("PATGenParticleFiller"),
                                    src        = cms.InputTag("genDaughters"),
                                    tag        = cms.string("embeddedEta"),
                                    method     = cms.string("eta"),
                                    leadingOnly=cms.untracked.bool(False)
                              )


   )



   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)

#eleele
def addEleEleEventTree(process,name,src = 'zEleEleCandidatesOS'):
	process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )
	eventTree = cms.EDAnalyzer('EventTreeMaker',
		#common quantities
		coreCollections = cms.VInputTag(
			cms.InputTag(src)
		),
		trigger = cms.PSet( 
			pluginType = cms.string("TriggerFiller"),
			src        = cms.InputTag("patTrigger"),
			paths      = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL",
									"HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v1")
		),
		MET = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("met"),
			method     = cms.string("met.pt()"),
			leadingOnly=cms.untracked.bool(True)
		),
		PVs = cms.PSet(
			pluginType = cms.string("VertexSizeFiller"),
			src        = cms.InputTag("primaryVertexFilter"),
			tag        = cms.string("vertices")
		),
		#ele ele quantities
		eleelept = cms.PSet(
		   pluginType = cms.string("PATElePairFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("eleelePt"),
		   method     = cms.string("pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleCharge = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleCharge"),
			method     = cms.string("charge()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMass = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleMass"),
			method     = cms.string("mass()"),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelept1 = cms.PSet(
		   pluginType = cms.string("PATElePairFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("eleelePt1"),
		   method     = cms.string("leg1.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelept2 = cms.PSet(
		   pluginType = cms.string("PATElePairFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("eleelePt2"),
		   method     = cms.string("leg2.pt"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta1 = cms.PSet(
		   pluginType = cms.string("PATElePairFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("eleeleEta1"),
		   method     = cms.string("leg1.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleeleeta2 = cms.PSet(
		   pluginType = cms.string("PATElePairFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("eleeleEta2"),
		   method     = cms.string("leg2.eta"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi1 = cms.PSet(
		   pluginType = cms.string("PATElePairFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("eleelePhi1"),
		   method     = cms.string("leg1.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		eleelephi2 = cms.PSet(
		   pluginType = cms.string("PATElePairFiller"),
		   src        = cms.InputTag(src),
		   tag        = cms.string("eleelePhi2"),
		   method     = cms.string("leg2.phi"),
		   leadingOnly=cms.untracked.bool(True)
		),
		#ele specific quantities
		eleeleRelIso03B1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleRelIso03B1"),
			method     = cms.string("(leg1.dr03TkSumPt()+max(leg1.dr03EcalRecHitSumEt()-1.0,0.0)+leg1.dr03HcalTowerSumEt())/leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleRelIso03E1"),
			method     = cms.string("(leg1.dr03TkSumPt()+leg1.dr03EcalRecHitSumEt()+leg1.dr03HcalTowerSumEt())/leg1.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleDcotTheta1"),
			method     = cms.string('leg1.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleConvDistance1"),
			method     = cms.string('leg1.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleMissHits1"),
			method     = cms.string('leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleRelPFIso1"),
			method     = cms.string('(leg1.chargedHadronIso+leg1.photonIso+leg1.neutralHadronIso)/leg1.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleIP1"),
			method     = cms.string('leg1.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP801 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleWP801"),
			method     = cms.string('leg1.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP901 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleWP901"),
			method     = cms.string('leg1.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleCiCLoose1"),
			method     = cms.string('leg1.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleCiCTight1"),
			method     = cms.string('leg1.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight1 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleCiCSuperTight1"),
			method     = cms.string('leg1.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight11 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleCiCHyperTight11"),
			method     = cms.string('leg1.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03B2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleRelIso03B2"),
			method     = cms.string("(leg2.dr03TkSumPt()+max(leg2.dr03EcalRecHitSumEt()-1.0,0.0)+leg2.dr03HcalTowerSumEt())/leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleRelIso03E2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleRelIso03E2"),
			method     = cms.string("(leg2.dr03TkSumPt()+leg2.dr03EcalRecHitSumEt()+leg2.dr03HcalTowerSumEt())/leg2.pt()"),
		    leadingOnly=cms.untracked.bool(True)
		),
		eleeleDCotTheta2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleDcotTheta2"),
			method     = cms.string('leg2.convDcot'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleConvDist2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleConvDistance2"),
			method     = cms.string('leg2.convDist'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleMissHits2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleMissHits2"),
			method     = cms.string('leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleelePFRelIso2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleRelPFIso2"),
			method     = cms.string('(leg2.chargedHadronIso+leg2.photonIso+leg2.neutralHadronIso)/leg2.pt()'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleEleIP2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleIP2"),
			method     = cms.string('leg2.dB'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP802 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleWP802"),
			method     = cms.string('leg2.userFloat("wp80")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleWP902 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleWP902"),
			method     = cms.string('leg2.userFloat("wp90")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCLoose2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleCiCLoose2"),
			method     = cms.string('leg2.electronID("cicLoose")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCTight2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleCiCTight2"),
			method     = cms.string('leg2.electronID("cicTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCSuperTight2 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleCiCSuperTight2"),
			method     = cms.string('leg2.electronID("cicSuperTight")'),
			leadingOnly=cms.untracked.bool(True)
		),
		eleeleCiCHyperTight12 = cms.PSet(
			pluginType = cms.string("PATElePairFiller"),
			src        = cms.InputTag(src),
			tag        = cms.string("eleeleCiCHyperTight12"),
			method     = cms.string('leg2.electronID("cicHyperTight1")'),
			leadingOnly=cms.untracked.bool(True)
		),
	)
	setattr(process, name, eventTree)
	p = cms.Path(getattr(process,name))
	setattr(process, name+'Path', p)

