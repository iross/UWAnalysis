import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatAlgos.tools.helpers import *
import sys


#evSummaryBase = cms.EDProducer('EventSummary',
#                               src = cms.untracked.vstring('','')
#)                               


class EventSummaryMaker(cms._ParameterTypeBase):
    #init functions get the input collection to the cut sequence
    def __init__(self,path):
        self.path = path
        self.stringList = []
        
    def getCounters(self,process):
        modules = listModules(self.path)
       
        for mod in modules:
            if(hasattr(mod,'label')):
               if mod.label().find('Counter') !=-1 :
                    self.stringList.append(mod.name.value())
        print 'List Of Filters'        
        print self.stringList        
        return cms.untracked.vstring(self.stringList)
    

        
