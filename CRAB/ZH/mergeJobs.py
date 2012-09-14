'''
File: mergeJobs.py
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Generate job submission file (for merging analysis root files).
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

merge = open("mergeJobs.sh","write")

datasets = json.load(file)

def makeFileList(dataset):
    """Dump list of completed files into a .txt file. It's used for merging. And for keeping track of what's done, I guess."""
    subprocess.call("mkdir -p fileLists",shell=True)
    subprocess.call("touch fileLists/{dataset}.txt".format(dataset=dataset),shell=True)
    subprocess.call("ls /hdfs/store/user/$USER/{dataset}_{tag}-{type}_{dataset}/*/*.root | sed -e 's/\/hdfs//g' > fileLists/{dataset}.txt".format(dataset=dataset,tag=tag,type=datasets[dataset]['type']),shell=True)

for dataset in datasets:
    passes = True
    if args.samples:
        passes = False
        for pattern in args.samples:
            if fnmatch.fnmatchcase(dataset, pattern):
                passes = True
    if passes:
        makeFileList(dataset)
        merge.write('farmoutAnalysisJobs --skip-existing-output --output-dir=. --merge {dataset}_{tag} $CMSSW_BASE --input-file-list=fileLists/{dataset}.txt --input-files-per-job=300\n'.format(dataset=dataset,tag=tag))
        if datasets[dataset]['type']=="DATA":
            merge.write('jobReportSummary /scratch/$USER/{dataset}_{tag}-DATA_{dataset}/*/*.xml --json-out /scratch/$USER/{dataset}_{tag}.json\n'.format(dataset=dataset,tag=tag))
            

file.close()
merge.close()
