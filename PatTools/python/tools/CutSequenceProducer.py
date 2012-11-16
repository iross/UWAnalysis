import FWCore.ParameterSet.Config as cms
import sys

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
    def __init__(self,firstSource,pyModuleName,pyNameSpace) :
        self.input = firstSource
        self.sequence = None
        self.pyModuleName = pyModuleName,
        self.pyNameSpace = pyNameSpace 
        self.inputLabel='src'

    def changeInput(self,src):
        self.input=src

    def changeInputLabel(self,sourceLabel):
        self.inputLabel=sourceLabel

    #Creates a selection/filter/counter sequence 
    def addCut(self,module,summaryText = None,minFilter = 1, maxFilter  = 9999):


        #try to find the name of the module
        moduleName=getInstanceName(module,self.pyNameSpace)

        if(moduleName != None):
            
           #Set the correct source
           setattr(module,self.inputLabel,cms.InputTag(self.input))
           #Add module to the sequence
           if self.sequence == None:
               self.sequence=module
           else:
               self.sequence*=module

           self.input=moduleName    
           #Create the Filter
           if minFilter>0 or maxFilter<9998:
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
               counter  = cms.EDFilter("EventCounter")
               counter.name=cms.string(summaryText)
               counterName = moduleName+'Counter'
               counter.setLabel(counterName)
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                   raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,counterName,counter)
               self.sequence*=counter

    def returnSequence(self):
        return cms.Sequence(self.sequence)
    
