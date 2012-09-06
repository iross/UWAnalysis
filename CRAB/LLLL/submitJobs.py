'''
File: submitJobs.py
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Generate job submission file.
'''

import json
import fnmatch
import subprocess
from RecoLuminosity.LumiDB import argparse

parser=argparse.ArgumentParser(description="%prog -- dump some analysis-level plots and yields")
parser.add_argument("--tag",dest="tag",type=str,default="")
parser.add_argument("--json",dest="json",type=str,default="datasets.json")
parser.add_argument("--samples",dest="samples",nargs="+",type=str,default="")
args=parser.parse_args()

file = open(args.json)
tag = args.tag

out = open("submitJobs.sh","write")

def getLumis(input_file):
    """Return lumisToProcess string"""

    lumis="process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange("
    infile=open("dataJSONs/"+input_file)
    entry=json.load(infile)
    for run in sorted(entry):
        for lumirange in entry[run]:
            lumis += "'%s:%s-%s:%s'," % (run, lumirange[0], run, lumirange[1])
    lumis=lumis[:-1] #remove that last comma
    lumis+=")\n"
    return lumis

out.write("cat LLLL-MC.py > MC.py\n")
out.write("cat CONDOR.py >> MC.py\n")
out.write("mkdir -p /scratch/$USER/DAGs/{0}/\n".format(tag))

datasets = json.load(file)

for dataset in datasets:
    passes = True
    runFile='MC.py'
    if args.samples:
        passes = False
        for pattern in args.samples:
            if fnmatch.fnmatchcase(dataset, pattern):
                passes = True

    if passes:
        if datasets[dataset]['type']=="DATA":
            print dataset
            subprocess.call("cat LLLL.py > DATA_{dataset}.py".format(dataset=dataset),shell=True)
            subprocess.call("cat CONDOR.py >> DATA_{dataset}.py".format(dataset=dataset),shell=True)
            lumis=getLumis(datasets[dataset]['json'])
            f=open("DATA_{dataset}.py".format(dataset=dataset),"a+b")
            f.write(lumis)
            f.close()
            runFile="DATA_{dataset}.py".format(dataset=dataset)

        if datasets[dataset]['url'] == '':
            out.write('farmoutAnalysisJobs --skip-existing-output --output-dag-file=/scratch/iross/DAGs/{tag}/{dataset} --input-dir=root://cmsxrootd.hep.wisc.edu/{path} {dataset}_{tag} $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/LLLL/'.format(tag=tag,dataset=dataset,path=datasets[dataset]['path'])+runFile+'\n')
        else:
            out.write('farmoutAnalysisJobs --skip-existing-output --output-dag-file=/scratch/iross/DAGs/{tag}/{dataset} --input-dbs-path={path} --dbs-service-url={url} {dataset} $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/LLLL/'.format(tag=tag,dataset=dataset,path=datasets[dataset]['path'],url=datasets[dataset]['url'])+runFile+'.py\n')

out.write("rm DATA*.py\n")
out.write("rm MC.py\n")

file.close()
out.close()
