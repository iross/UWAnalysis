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

out.write("cat LLLL.py > DATA.py\n")
out.write("cat CONDOR.py >> DATA.py\n")
out.write("cat LLLL-MC.py > MC.py\n")
out.write("cat CONDOR.py >> MC.py\n")
out.write("mkdir -p /scratch/$USER/DAGs/{0}/\n".format(tag))

datasets = json.load(file)

for dataset in datasets:
    passes = True
    if args.samples:
        passes = False
        for pattern in args.samples:
            if fnmatch.fnmatchcase(dataset, pattern):
                passes = True

    if passes:
        if datasets[dataset]['url'] == '':
            out.write('farmoutAnalysisJobs --output-dag-file=/scratch/$USER/DAGs/{tag}/{dataset} --input-dir=root://cmsxrootd.hep.wisc.edu/{path} {dataset}_{tag} $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/LLLL/{type}.py\n'.format(tag=tag,dataset=dataset,path=datasets[dataset]['path'],type=datasets[dataset]['type']))
        else:
            out.write('farmoutAnalysisJobs --output-dag-file=/scratch/$USER/DAGs/{tag}/{dataset} --input-dbs-path={path} --dbs-service-url={url} {dataset} $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/LLLL/{type}.py\n'.format(tag=tag,dataset=dataset,path=datasets[dataset]['path'],url=datasets[dataset]['url'],type=datasets[dataset]['type']))

out.write("rm DATA.py\n")
out.write("rm MC.py\n")

file.close()
out.close()
