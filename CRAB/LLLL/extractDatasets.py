'''
@file extractDatasets.py
@author D. Austin Belknap

Can generate the datasets.json file needed to submit Condor jobs
given the output of Tapas's patTuple database tool and a file
containing the list of samples you want included. See the README.
'''

import re
import json
from optparse import OptionParser

parser = OptionParser()

parser.add_option("-d","--datasetList",  dest="inFile",    help="The list of datasets you want included in the output JSON.")
parser.add_option("-p","--patTupleList", dest="patTuples", help="The list of patTuples from Tapas's database tool.")
parser.add_option("-o","--outputJson",   dest="outFile",   help="The output JSON file.")

(options, args) = parser.parse_args()

inFile  = open(options.inFile,'r')
patFile = open(options.patTuples,'r')
outFile = open(options.outFile,'w')


'''
Find the patTuple path(s) associated with a data/mc sample.
@param inString The entire output of Tapas's patTuple database tool as a string
@param sampleName The name of the sample from DAS
@return A list of the patTuple paths
'''
def findPath(inString, sampleName):
    RE = re.compile("\s*Storage Dir: (.+)\n\s*Datadef key: .+\n\s*Dataset name: "+sampleName)
    results = RE.findall(inString)

    out = []
    for i in results:
        out.append(i)

    return out


datasets = {}

# Regular expressions for parsing the sample list
dataRE  = re.compile("^(\w+)\s+DATA\s+(.+)$")
mcRE    = re.compile("^(\w+)\s+MC\s+(\d+\.\d+)\s+(.+)$")

# check for comments and if xSec was forgotten for MC
mcREerr = re.compile("^\w+\s+MC\s+.+$")
comment = re.compile("^\s*\#")

patString = patFile.read()

notFound = []

for line in inFile:

    dataMatch = dataRE.match(line)
    mcMatch   = mcRE.match(line)
    mcErr     = mcREerr.match(line) 
    isComment = comment.match(line)

    # ignore comment lines
    if (isComment):
        continue

    if (dataMatch):
        name       = dataMatch.group(1)
        sampleType = "DATA"
        xsection   = 0.0
        sampleName = dataMatch.group(2)

    elif (mcMatch):
        name       = mcMatch.group(1)
        sampleType = "MC"
        xsection   = float(mcMatch.group(2))
        sampleName = mcMatch.group(3)

    # check if the xSec was forgotten with the MC datasets
    elif (mcErr):
        print "Provide cross-section for MC sample"
        print "\t" + line

    else:
        continue

    # extract the patTuple paths
    samplePaths = findPath(patString, sampleName)

    if len(samplePaths) == 0:
        notFound.append(sampleName)

    # Store the information into a python map
    if len(samplePaths) == 1:
        datasets[name] = {"type" : sampleType,
                          "path" : samplePaths[0],
                          "url"  : "",
                          "xsection" : xsection,
                          "note_" : ""
                          }

    # if the dataset is broken into more than one patTuple
    elif len(samplePaths) > 1:
        iterator = 1
        for i in samplePaths:
            tag = "p" + str(iterator)
            iterator += 1

            datasets[name+tag] = {"type" : sampleType,
                                  "path" : i,
                                  "url" : "",
                                  "xsection" : xsection,
                                  "note_" : ""
                                  }

if len(notFound) > 0:
    print "PAT-Tuples not found:"
    for i in notFound:
        print i

# Run the map through the JSON parser, and write to file
outFile.write(json.dumps(datasets,indent=4))

outFile.close()
inFile.close()
patFile.close()
