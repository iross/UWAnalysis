import FWCore.ParameterSet.Config as cms
import sys

metCalibration = cms.PSet(
                   applyCalibration = cms.bool(False),
                   calibrationScheme = cms.string("BothLegs"),
                   responseU1   = cms.string("1.41455-0.9118*x"),
                   responseU2   = cms.string("-0.019"),
                   resolutionU1 = cms.string("9.78414+0.08411*x-4.04839e-6**x*x"),
                   resolutionU2 = cms.string("9.67923+0.0563313*x-0.000112069*x*x"),
                   responseMCU1   = cms.string("1.17961-0.944036*x"),
                   responseMCU2   = cms.string("0.0001916"),
                   resolutionMCU1 = cms.string("9.60309+0.0548918*x+0.000158131*x*x"),
                   resolutionMCU2 = cms.string("9.49535+0.0384724*x-3.43035e-5*x*x")
)

    #THINGS YOU NEED
svFitLikelihoodMuTauKinematicsPhaseSpace = cms.PSet(
    pluginName = cms.string("svFitLikelihoodDiTauKinematicsPhaseSpace"),
    pluginType = cms.string("SVfitLikelihoodMuTauPairKinematics"),
    # Always fit
    firstFitIteration = cms.uint32(0),
    leg1 = cms.PSet(
        pluginType = cms.string("SVfitMuonLikelihoodPhaseSpace")
    ),
    leg2 = cms.PSet(
        pluginType = cms.string("SVfitTauLikelihoodPhaseSpace")
    )
)

svFitLikelihoodMuTauMEt = cms.PSet(
    pluginName = cms.string("svFitLikelihoodMEt"),
    pluginType = cms.string("SVfitLikelihoodMEtMuTau"),
    # Always fit
    firstFitIteration = cms.uint32(0),
    resolution = cms.PSet(
        parSigma = cms.string("7.54*(1 - 0.00542*x)"),
        parBias = cms.string("-0.96"),
        perpSigma = cms.string("6.85*(1 - 0.00547*x)"),
        perpBias = cms.string("0."),
    ),
    srcPFCandidates = cms.InputTag('particleFlow')
)

svFitLikelihoodMuTauPtBalance = cms.PSet(
    pluginName = cms.string("svFitLikelihoodDiTauPtBalance"),
    pluginType = cms.string("SVfitLikelihoodMuTauPairPtBalance"),
    # Always fit
    firstFitIteration = cms.uint32(0),
)


    #THINGS YOU NEED
svFitLikelihoodEleTauKinematicsPhaseSpace = cms.PSet(
    pluginName = cms.string("svFitLikelihoodDiTauKinematicsPhaseSpace"),
    pluginType = cms.string("SVfitLikelihoodElecTauPairKinematics"),
    # Always fit
    firstFitIteration = cms.uint32(0),
    leg1 = cms.PSet(
        pluginType = cms.string("SVfitElectronLikelihoodPhaseSpace")
    ),
    leg2 = cms.PSet(
        pluginType = cms.string("SVfitTauLikelihoodPhaseSpace")
    )
)

svFitLikelihoodEleTauMEt = cms.PSet(
    pluginName = cms.string("svFitLikelihoodMEt"),
    pluginType = cms.string("SVfitLikelihoodMEtElecTau"),
    # Always fit
    firstFitIteration = cms.uint32(0),
    resolution = cms.PSet(
        parSigma = cms.string("7.54*(1 - 0.00542*x)"),
        parBias = cms.string("-0.96"),
        perpSigma = cms.string("6.85*(1 - 0.00547*x)"),
        perpBias = cms.string("0."),
    ),
    srcPFCandidates = cms.InputTag('particleFlow')
)

svFitLikelihoodEleTauPtBalance = cms.PSet(
    pluginName = cms.string("svFitLikelihoodDiTauPtBalance"),
    pluginType = cms.string("SVfitLikelihoodElecTauPairPtBalance"),
    # Always fit
    firstFitIteration = cms.uint32(0),
)


    #THINGS YOU NEED
svFitLikelihoodEleMuKinematicsPhaseSpace = cms.PSet(
    pluginName = cms.string("svFitLikelihoodDiTauKinematicsPhaseSpace"),
    pluginType = cms.string("SVfitLikelihoodElecMuPairKinematics"),
    # Always fit
    firstFitIteration = cms.uint32(0),
    leg1 = cms.PSet(
        pluginType = cms.string("SVfitElectronLikelihoodPhaseSpace")
    ),
    leg2 = cms.PSet(
        pluginType = cms.string("SVfitMuonLikelihoodPhaseSpace")
    )
)

svFitLikelihoodEleMuMEt = cms.PSet(
    pluginName = cms.string("svFitLikelihoodMEt"),
    pluginType = cms.string("SVfitLikelihoodMEtElecMu"),
    # Always fit
    firstFitIteration = cms.uint32(0),
    resolution = cms.PSet(
        parSigma = cms.string("7.54*(1 - 0.00542*x)"),
        parBias = cms.string("-0.96"),
        perpSigma = cms.string("6.85*(1 - 0.00547*x)"),
        perpBias = cms.string("0."),
    ),
    srcPFCandidates = cms.InputTag('particleFlow')
)

svFitLikelihoodEleMuPtBalance = cms.PSet(
    pluginName = cms.string("svFitLikelihoodDiTauPtBalance"),
    pluginType = cms.string("SVfitLikelihoodElecMuPairPtBalance"),
    # Always fit
    firstFitIteration = cms.uint32(0),
)



    #THINGS YOU NEED
svFitLikelihoodMuMuKinematicsPhaseSpace = cms.PSet(
    pluginName = cms.string("svFitLikelihoodDiTauKinematicsPhaseSpace"),
    pluginType = cms.string("SVfitLikelihoodMuPairKinematics"),
    # Always fit
    firstFitIteration = cms.uint32(0),
    leg1 = cms.PSet(
        pluginType = cms.string("SVfitMuonLikelihoodPhaseSpace")
    ),
    leg2 = cms.PSet(
        pluginType = cms.string("SVfitMuonLikelihoodPhaseSpace")
    )
)

svFitLikelihoodMuMuMEt = cms.PSet(
    pluginName = cms.string("svFitLikelihoodMEt"),
    pluginType = cms.string("SVfitLikelihoodMEtMuMu"),
    # Always fit
    firstFitIteration = cms.uint32(0),
    resolution = cms.PSet(
        parSigma = cms.string("7.54*(1 - 0.00542*x)"),
        parBias = cms.string("-0.96"),
        perpSigma = cms.string("6.85*(1 - 0.00547*x)"),
        perpBias = cms.string("0."),
    ),
    srcPFCandidates = cms.InputTag('particleFlow')
)

svFitLikelihoodMuMuPtBalance = cms.PSet(
    pluginName = cms.string("svFitLikelihoodDiTauPtBalance"),
    pluginType = cms.string("SVfitLikelihoodMuPairPtBalance"),
    # Always fit
    firstFitIteration = cms.uint32(0),
)



def getInstanceName(obj, pyNameSpace = None, process = None):
    if process is not None:
         return obj.label()
    else:
         if pyNameSpace is not None:
               for name, ref in pyNameSpace.items():
                    if ref is obj : return name
         else:
               for pyModule in sys.modules.values():
                    for name, ref in pyModule.__dict__.items():
                        if ref is obj : return name
    return None


class CutSequenceProducer(cms._ParameterTypeBase):


    #init functions get the input collection to the cut sequence
    def __init__(self,initialCounter,pyModuleName,pyNameSpace) :
        self.input = ''
        self.pyModuleName = pyModuleName,
        self.pyNameSpace = pyNameSpace




       #Add the first Counter
        counter  = cms.EDProducer("EventCounter")
        counter.name=cms.string(initialCounter)
        counter.setLabel(initialCounter)
        pyModule = sys.modules[self.pyModuleName[0]]
        if pyModule is None:
            raise ValueError("'pyModuleName' Parameter invalid")
        setattr(pyModule,initialCounter+'Counter',counter)
        self.sequence=counter


    def addDiCandidateModule(self,moduleName,moduleType, src1,src2,met,jets,min = 1,max=9999,text = '',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles = 'genTaus'):
               dicand  = cms.EDProducer(moduleType)
               dicand.useLeadingTausOnly = cms.bool(False)
               dicand.srcLeg1 = cms.InputTag(src1)
               dicand.srcLeg2 = cms.InputTag(src2)
               dicand.srcJets = cms.InputTag(jets)
               dicand.dRmin12 = cms.double(dR)
               dicand.srcMET = cms.InputTag(met)
               dicand.srcPrimaryVertex = cms.InputTag("offlinePrimaryVertices")
               dicand.srcBeamSpot = cms.InputTag("offlineBeamSpot")
               dicand.srcGenParticles = cms.InputTag(genParticles)
               dicand.recoMode = cms.string("")
               dicand.verbosity = cms.untracked.int32(0)
               dicand.doSVreco = cms.bool(False)
               dicand.metCalibration = metCalibration
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)

               self.sequence*=dicand

               self.input=moduleName

               #Create the Filter

               filter  = cms.EDFilter("PATCandViewCountFilter")
               filter.minNumber = cms.uint32(min)
               filter.maxNumber = cms.uint32(max)
               filter.src = cms.InputTag(moduleName)
               filterName = moduleName+'Filter'
               filter.setLabel(filterName)
               #Register the filter in the namespace
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,filterName,filter)
               self.sequence*=filter

          #now the counter
               if text is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(text)
                   counterName = moduleName+'Counter'
                   counter.setLabel(counterName)
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,counterName,counter)
                   self.sequence*=counter



    def addCrossCleanerModule(self,moduleName,moduleType,min = 1,max=9999,text = '',dR = 0.1):
               dicand  = cms.EDProducer(moduleType)
               dicand.src = cms.InputTag(self.input)
               dicand.dR = cms.double(dR)
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName

               #Create the Filter

               filter  = cms.EDFilter("PATCandViewCountFilter")
               filter.minNumber = cms.uint32(min)
               filter.maxNumber = cms.uint32(max)
               filter.src = cms.InputTag(moduleName)
               filterName = moduleName+'Filter'
               filter.setLabel(filterName)
               #Register the filter in the namespace
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,filterName,filter)
               self.sequence*=filter

          #now the counter
               if text is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(text)
                   counterName = moduleName+'Counter'
                   counter.setLabel(counterName)
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,counterName,counter)
                   self.sequence*=counter

################################################################################
#####     NSV fit configuration                                            #####
################################################################################

    def addDiCandNSVFit(self,moduleName,finalState=("Mu", "Tau"),algo="fit"):
               # Do import here so python only crashes (at run time)
               # if TauAna packages aren't checked out.
               import TauAnalysis.CandidateTools.nSVfitAlgorithmDiTau_cfi as nsv
               # Define which NSVfit plugins map to different final states
               nsvFinalStates = {
                   'Mu' : {
                       'builder' : nsv.nSVfitTauToMuBuilder,
                       'phase_space' : nsv.nSVfitMuonLikelihoodPhaseSpace,
                   },
                   'Elec' : {
                       'builder' : nsv.nSVfitTauToElecBuilder,
                       'phase_space' : nsv.nSVfitElectronLikelihoodPhaseSpace,
                   },
                   'Tau' : {
                       'builder' : nsv.nSVfitTauToHadBuilder,
                       'phase_space' : nsv.nSVfitTauLikelihoodPhaseSpace,
                   },
               }

               leg1, leg2 = finalState
               dicand  = cms.EDProducer("PAT"+leg1+leg2+"NSVFitter")
               dicand.src = cms.InputTag(self.input)
               dicand.srcPrimaryVertex = cms.InputTag("offlinePrimaryVerticesWithBS")
               dicand.config = nsv.nSVfitConfig_template.clone()
               # Setup final state specific plugins
               dicand.config.event.resonances.A.daughters.leg1.likelihoodFunctions = \
                       cms.VPSet(nsvFinalStates[leg1]['phase_space'].clone())
               dicand.config.event.resonances.A.daughters.leg1.builder = \
                       nsvFinalStates[leg1]['builder'].clone()
               dicand.config.event.resonances.A.daughters.leg2.likelihoodFunctions = \
                       cms.VPSet(nsvFinalStates[leg2]['phase_space'].clone())
               dicand.config.event.resonances.A.daughters.leg2.builder = \
                       nsvFinalStates[leg2]['builder'].clone()
               if algo == "fit":
                   dicand.algorithm = nsv.nSVfitProducerByLikelihoodMaximization.algorithm.clone()
               elif algo == "int":
                   dicand.algorithm = nsv.nSVfitProducerByIntegration.algorithm.clone()
               else:
                   raise ValueError("Unknown NSVfit algo type: %s" % algo)

               dicand.resultLabel = cms.string("PsMETLogM_" + algo)

               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName

    def addQuadCandNSVFit(self,moduleName,finalState=("Mu","Mu","Mu", "Tau"),algo="fit"):
               # Do import here so python only crashes (at run time)
               # if TauAna packages aren't checked out.
               import TauAnalysis.CandidateTools.nSVfitAlgorithmDiTau_cfi as nsv
			   # Define which NSVfit plugins map to different final states
               nsvFinalStates = {
                   'Mu' : {
                       'builder' : nsv.nSVfitTauToMuBuilder,
                       'phase_space' : nsv.nSVfitMuonLikelihoodPhaseSpace,
                   },
                   'Elec' : {
                       'builder' : nsv.nSVfitTauToElecBuilder,
                       'phase_space' : nsv.nSVfitElectronLikelihoodPhaseSpace,
                   },
                   'Tau' : {
                       'builder' : nsv.nSVfitTauToHadBuilder,
                       'phase_space' : nsv.nSVfitTauLikelihoodPhaseSpace,
                   },
               }
               #backwards naming for Z2 goodness.
               leg3, leg4, leg1, leg2 = finalState
               dicand  = cms.EDProducer("PAT"+leg3+leg4+leg1+leg2+"NSVFitter")
               dicand.src = cms.InputTag(self.input)
               dicand.srcPrimaryVertex = cms.InputTag("offlinePrimaryVerticesWithBS")
               dicand.config = nsv.nSVfitConfig_template.clone()
               # Setup final state specific plugins
               dicand.config.event.resonances.A.daughters.leg1.likelihoodFunctions = \
                       cms.VPSet(nsvFinalStates[leg1]['phase_space'].clone())
               dicand.config.event.resonances.A.daughters.leg1.builder = \
                       nsvFinalStates[leg1]['builder'].clone()
               dicand.config.event.resonances.A.daughters.leg2.likelihoodFunctions = \
                       cms.VPSet(nsvFinalStates[leg2]['phase_space'].clone())
               dicand.config.event.resonances.A.daughters.leg2.builder = \
                       nsvFinalStates[leg2]['builder'].clone()
               if algo == "fit":
                   dicand.algorithm = nsv.nSVfitProducerByLikelihoodMaximization.algorithm.clone()
               elif algo == "int":
                   dicand.algorithm = nsv.nSVfitProducerByIntegration.algorithm.clone()
               else:
                   raise ValueError("Unknown NSVfit algo type: %s" % algo)

               dicand.resultLabel = cms.string("PsMETLogM_" + algo)

               pyModule = sys.modules[self.pyModuleName[0]]
               print pyModule
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName

    def addMuTauNSVFit(self,moduleName, algo="fit"):
               self.addDiCandNSVFit(moduleName,("Mu","Tau"), algo)

    def addEleTauNSVFit(self,moduleName, algo="fit"):
               self.addDiCandNSVFit(moduleName,("Elec","Tau"), algo)

    def addEleMuNSVFit(self,moduleName, algo="fit"):
               self.addDiCandNSVFit(moduleName,("Elec","Mu"), algo)

    def addMuMuNSVFit(self,moduleName, algo="fit"):
               self.addDiCandNSVFit(moduleName,("Mu","Mu"), algo)

    def addMuMuMuTauNSVFit(self,moduleName, algo="fit"):
               self.addQuadCandNSVFit(moduleName,("Mu","Mu","Mu","Tau"), algo)

################################################################################
#####     Legacy SVfit configuration                                       #####
################################################################################

    def addMuTauSVFit(self,moduleName):
               dicand  = cms.EDProducer('PATMuTauSVFitter')
               dicand.src = cms.InputTag(self.input)
               dicand.srcPrimaryVertex = cms.InputTag("offlinePrimaryVerticesWithBS")
               dicand.srcBeamSpot = cms.InputTag("offlineBeamSpot")
               dicand.svFit = cms.PSet(
                               psKine = cms.PSet(
                                   likelihoodFunctions = cms.VPSet(
                                       svFitLikelihoodMuTauKinematicsPhaseSpace
                                   ),
                                   estUncertainties = cms.PSet(
                                   numSamplings = cms.int32(-1)
                                   )
                                ),
                                psKine_MEt = cms.PSet(
                                   likelihoodFunctions = cms.VPSet(
                                       svFitLikelihoodMuTauKinematicsPhaseSpace,
                                       svFitLikelihoodMuTauMEt
                                    ),
                                    estUncertainties = cms.PSet(
                                    numSamplings = cms.int32(-1)
                                    )
                                ),
                                psKine_MEt_ptBalance = cms.PSet(
                                likelihoodFunctions = cms.VPSet(
                                           svFitLikelihoodMuTauKinematicsPhaseSpace,
                                           svFitLikelihoodMuTauMEt,
                                           svFitLikelihoodMuTauPtBalance
                                ),
                                estUncertainties = cms.PSet(
                                      numSamplings = cms.int32(-1)
                                 )
                                )
               )

               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName


    def addEleTauSVFit(self,moduleName):
               dicand  = cms.EDProducer('PATEleTauSVFitter')
               dicand.src = cms.InputTag(self.input)
               dicand.srcPrimaryVertex = cms.InputTag("offlinePrimaryVerticesWithBS")
               dicand.srcBeamSpot = cms.InputTag("offlineBeamSpot")
               dicand.svFit = cms.PSet(
                               psKine = cms.PSet(
                                   likelihoodFunctions = cms.VPSet(
                                       svFitLikelihoodEleTauKinematicsPhaseSpace
                                   ),
                                   estUncertainties = cms.PSet(
                                   numSamplings = cms.int32(-1)
                                   )
                                ),
                                psKine_MEt = cms.PSet(
                                   likelihoodFunctions = cms.VPSet(
                                       svFitLikelihoodEleTauKinematicsPhaseSpace,
                                       svFitLikelihoodEleTauMEt
                                    ),
                                    estUncertainties = cms.PSet(
                                    numSamplings = cms.int32(-1)
                                    )
                                ),
                                psKine_MEt_ptBalance = cms.PSet(
                                likelihoodFunctions = cms.VPSet(
                                           svFitLikelihoodEleTauKinematicsPhaseSpace,
                                           svFitLikelihoodEleTauMEt,
                                           svFitLikelihoodEleTauPtBalance
                                ),
                                estUncertainties = cms.PSet(
                                      numSamplings = cms.int32(-1)
                                 )
                                )
               )

               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName



    def addEleMuSVFit(self,moduleName):
               dicand  = cms.EDProducer('PATEleMuSVFitter')
               dicand.src = cms.InputTag(self.input)
               dicand.srcPrimaryVertex = cms.InputTag("offlinePrimaryVerticesWithBS")
               dicand.srcBeamSpot = cms.InputTag("offlineBeamSpot")
               dicand.svFit = cms.PSet(
                               psKine = cms.PSet(
                                   likelihoodFunctions = cms.VPSet(
                                       svFitLikelihoodEleMuKinematicsPhaseSpace
                                   ),
                                   estUncertainties = cms.PSet(
                                   numSamplings = cms.int32(-1)
                                   )
                                ),
                                psKine_MEt = cms.PSet(
                                   likelihoodFunctions = cms.VPSet(
                                       svFitLikelihoodEleMuKinematicsPhaseSpace,
                                       svFitLikelihoodEleMuMEt
                                    ),
                                    estUncertainties = cms.PSet(
                                    numSamplings = cms.int32(-1)
                                    )
                                ),
                                psKine_MEt_ptBalance = cms.PSet(
                                likelihoodFunctions = cms.VPSet(
                                           svFitLikelihoodEleMuKinematicsPhaseSpace,
                                           svFitLikelihoodEleMuMEt,
                                           svFitLikelihoodEleMuPtBalance
                                ),
                                estUncertainties = cms.PSet(
                                      numSamplings = cms.int32(-1)
                                 )
                                )
               )

               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName



    def addMuMuSVFit(self,moduleName):
               dicand  = cms.EDProducer('PATMuMuSVFitter')
               dicand.src = cms.InputTag(self.input)
               dicand.srcPrimaryVertex = cms.InputTag("offlinePrimaryVerticesWithBS")
               dicand.srcBeamSpot = cms.InputTag("offlineBeamSpot")
               dicand.svFit = cms.PSet(
                               psKine = cms.PSet(
                                   likelihoodFunctions = cms.VPSet(
                                       svFitLikelihoodMuMuKinematicsPhaseSpace
                                   ),
                                   estUncertainties = cms.PSet(
                                   numSamplings = cms.int32(-1)
                                   )
                                ),
                                psKine_MEt = cms.PSet(
                                   likelihoodFunctions = cms.VPSet(
                                       svFitLikelihoodMuMuKinematicsPhaseSpace,
                                       svFitLikelihoodMuMuMEt
                                    ),
                                    estUncertainties = cms.PSet(
                                    numSamplings = cms.int32(-1)
                                    )
                                ),
                                psKine_MEt_ptBalance = cms.PSet(
                                likelihoodFunctions = cms.VPSet(
                                           svFitLikelihoodMuMuKinematicsPhaseSpace,
                                           svFitLikelihoodMuMuMEt,
                                           svFitLikelihoodMuMuPtBalance
                                ),
                                estUncertainties = cms.PSet(
                                      numSamplings = cms.int32(-1)
                                 )
                                )
               )

               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName



    def setSRC(self,src):
               self.input=src

    def addCandidateMETModule(self,moduleName,moduleType, srcLeptons,srcMET,srcJets,min = 1,max=9999,text = ''):
               dicand  = cms.EDProducer(moduleType)
               dicand.srcLeptons = cms.InputTag(srcLeptons)
               dicand.srcMET = cms.InputTag(srcMET)
               dicand.srcJets = cms.InputTag(srcJets)
               dicand.verbosity = cms.untracked.int32(0)
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName

               #Create the Filter

               filter  = cms.EDFilter("PATCandViewCountFilter")
               filter.minNumber = cms.uint32(min)
               filter.maxNumber = cms.uint32(max)
               filter.src = cms.InputTag(moduleName)
               filterName = moduleName+'Filter'
               filter.setLabel(filterName)
               #Register the filter in the namespace
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,filterName,filter)
               self.sequence*=filter

          #now the counter
               if text is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(text)
                   counterName = moduleName+'Counter'
                   counter.setLabel(counterName)
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,counterName,counter)
                   self.sequence*=counter

    def addSorter(self,moduleName,moduleType):
               selector  = cms.EDProducer(moduleType)
               selector.src = cms.InputTag(self.input)
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,selector)

               self.sequence*=selector

               self.input=moduleName

    def addGeneric(self,moduleName,moduleType):
               selector  = cms.EDProducer(moduleType)
               selector.src = cms.InputTag(self.input)
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,selector)
               self.sequence*=selector
               self.input=moduleName


    def addSelector(self,moduleName,moduleType,cut,summaryText = None,minFilter = 1, maxFilter  = 9999):
               selector  = cms.EDFilter(moduleType)
               selector.src = cms.InputTag(self.input)
               selector.cut = cms.string(cut)
               selector.filter = cms.bool(False)
               print moduleName,cut

               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,selector)

               self.sequence*=selector

               self.input=moduleName

               #Create the Filter

               filter  = cms.EDFilter("PATCandViewCountFilter")
               filter.minNumber = cms.uint32(minFilter)
               filter.maxNumber = cms.uint32(maxFilter)
               filter.src = cms.InputTag(moduleName)
               filterName = moduleName+'Filter'
               filter.setLabel(filterName)
               #Register the filter in the namespace
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,filterName,filter)
               self.sequence*=filter

          #now the counter
               if summaryText is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(summaryText)
                   counterName = moduleName+'Counter'
                   counter.setLabel(counterName)
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,counterName,counter)
                   self.sequence*=counter


    def addSmearing(self,taus,muons,electrons,jets,mpost=''):
          smearedTaus = cms.EDProducer("SmearedTauProducer",
                                       src = cms.InputTag(taus),
                                       smearMCParticle = cms.bool(False),
                                       module_label = cms.string("CRAP"),
                                       energyScale  = cms.double(1.00),
                                       deltaEta     = cms.double(0.0),
                                       deltaPhi     = cms.double(0.0),
                                       deltaPt      = cms.double(0.0),
                                       smearConstituents = cms.bool(False),
                                       hadronEnergyScale = cms.double(1.0),
                                       gammaEnergyScale = cms.double(1.0)
                                       )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedTaus'+mpost,smearedTaus)
          self.sequence*=smearedTaus


          #add a post MET tau
          smearedTausID = cms.EDProducer("SmearedTauProducer",
                                       src = cms.InputTag('selectedPatTaus'),
                                       smearMCParticle = cms.bool(False),
                                       module_label = cms.string("CRAP"),
                                       energyScale  = cms.double(1.0),
                                       deltaEta     = cms.double(0.0),
                                       deltaPhi     = cms.double(0.0),
                                       deltaPt      = cms.double(0.0),
                                       smearConstituents = cms.bool(False),
                                       hadronEnergyScale = cms.double(1.0),
                                       gammaEnergyScale = cms.double(1.0)
                                       )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedTausID'+mpost,smearedTausID)
          self.sequence*=smearedTausID



          smearedMuons = cms.EDProducer("SmearedMuonProducer",
                                        src = cms.InputTag(muons),
                                        smearMCParticle = cms.bool(False),
                                        module_label = cms.string("CRAP"),
                                        energyScale  = cms.double(1.0),
                                        deltaEta     = cms.double(0.0),
                                        deltaPhi     = cms.double(0.0),
                                        deltaPt      = cms.double(0.0)
                                        )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedMuons'+mpost,smearedMuons)
          self.sequence*=smearedMuons

          smearedMuonsID = cms.EDProducer("SmearedMuonProducer",
                                        src = cms.InputTag('selectedPatMuons'),
                                        smearMCParticle = cms.bool(False),
                                        module_label = cms.string("CRAP"),
                                        energyScale  = cms.double(1.0),
                                        deltaEta     = cms.double(0.0),
                                        deltaPhi     = cms.double(0.0),
                                        deltaPt      = cms.double(0.0)
                                        )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedMuonsID'+mpost,smearedMuonsID)
          self.sequence*=smearedMuonsID


          smearedElectrons = cms.EDProducer("SmearedElectronProducer",
                                            src = cms.InputTag(electrons),
                                            smearMCParticle = cms.bool(False),
                                            module_label = cms.string("CRAP"),
                                            energyScale  = cms.double(1.0),
                                            deltaEta     = cms.double(0.0),
                                            deltaPhi     = cms.double(0.0),
                                            deltaPt      = cms.double(0.0)
                                            )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedElectrons'+mpost,smearedElectrons)
          self.sequence*=smearedElectrons

          smearedElectronsID = cms.EDProducer("SmearedElectronProducer",
                                            src = cms.InputTag('selectedPatElectrons'),
                                            smearMCParticle = cms.bool(False),
                                            module_label = cms.string("CRAP"),
                                            energyScale  = cms.double(1.0),
                                            deltaEta     = cms.double(0.0),
                                            deltaPhi     = cms.double(0.0),
                                            deltaPt      = cms.double(0.0)
                                            )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedElectronsID'+mpost,smearedElectronsID)
          self.sequence*=smearedElectronsID

          smearedJets = cms.EDProducer("SmearedJetProducer",
                                       src = cms.InputTag(jets),
                                       smearMCParticle = cms.bool(False),
                                       module_label = cms.string("CRAP"),
                                       energyScale  = cms.double(1.0),
                                       energyScaleDB= cms.double(0),
                                       deltaEta     = cms.double(0.0),
                                       deltaPhi     = cms.double(0.0),
                                       deltaPt      = cms.double(0.0)
                                       )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedJets'+mpost,smearedJets)
          self.sequence*=smearedJets


          smearedMET = cms.EDProducer('METRecalculator',
                                      met = cms.InputTag("patMETs"),
                                      originalObjects = cms.VInputTag(cms.InputTag('selectedPatMuons'),
                                                                      cms.InputTag('selectedPatElectrons'),
                                                                      cms.InputTag('selectedPatTaus'),
                                                                      cms.InputTag('selectedPatJets')
                                                                      ),
                                      smearedObjects = cms.VInputTag(cms.InputTag("smearedMuonsID"+mpost),
                                                                     cms.InputTag("smearedElectronsID"+mpost),
                                                                     cms.InputTag("smearedTausID"+mpost),
                                                                     cms.InputTag("smearedJets"+mpost)
                                                                 ),
                                      unclusteredScale = cms.double(1.0),
                                      threshold   = cms.double(0.)
                                      )
          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedMET'+mpost,smearedMET)
          self.sequence*=smearedMET


    def addHLT(self,path,triggerProcess,summaryText = ''):
               hltSkimmer = cms.EDFilter("HLTHighLevel",
                          TriggerResultsTag = cms.InputTag("TriggerResults","",triggerProcess),
                          HLTPaths = cms.vstring(path),           # provide list of HLT paths (or patterns) you want
                          eventSetupPathsKey = cms.string(''), # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
                          andOr = cms.bool(True),             # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
                          throw = cms.bool(True)    # throw exception on unknown path names
               )

               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,'hltSkimmer',hltSkimmer)
               self.sequence*=hltSkimmer

          #now the counter
               if summaryText is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(summaryText)
                   counter.setLabel('hltSkimmerCounter')
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,'hltSkimmerCounter',counter)
                   self.sequence*=counter


    def returnSequence(self):
        return cms.Sequence(self.sequence)
