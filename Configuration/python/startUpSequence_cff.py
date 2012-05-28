import FWCore.ParameterSet.Config as cms


from DQMServices.Core.DQM_cfg import *
from DQMServices.Components.DQMEnvironment_cfi import *
from DQMServices.Components.MEtoEDMConverter_cfi import *
from DQMServices.Components.EDMtoMEConverter_cfi import *


saveHistos = cms.Sequence(MEtoEDMConverter)
loadHistos = cms.Sequence(EDMtoMEConverter)


initialCounter = cms.EDProducer('EventCounter',
                         name = cms.string("initialEvents")
)

startupSequence = cms.Sequence(initialCounter)


startupSequenceFromSkim = cms.Sequence(loadHistos)

