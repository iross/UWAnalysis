import re
import json
from optparse import OptionParser

parser = OptionParser()

parser.add_option("--datasetList", dest="inFile")
parser.add_option("--patTupleList", dest="patTuples")
parser.add_option("--outputJson", dest="outFile")

(options, args) = parser.parse_args()

inFile  = open(options.inFile,'r')
patFile = open(options.patTuples,'r')
outFile = open(options.outFile,'w')



def findPath(inString, sampleName):
    RE = re.compile("\s*Storage Dir: (.+)\n\s*Datadef key: .+\n\s*Dataset name: "+sampleName)
    results = RE.findall(inString)

    out = []
    for i in results:
        out.append(i)

    return out


datasets = {}

dataRE = re.compile("^(\w+)\s+DATA\s+(.+)$")
mcRE   = re.compile("^(\w+)\s+MC\s+(\d+\.\d+)\s+(.+)$")

patString = patFile.read()

for line in inFile:

    dataMatch = dataRE.match(line)
    mcMatch   = mcRE.match(line)

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

    else:
        continue

    samplePaths = findPath(patString, sampleName)

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

outFile.write(json.dumps(datasets,indent=4))

outFile.close()
inFile.close()
patFile.close()
