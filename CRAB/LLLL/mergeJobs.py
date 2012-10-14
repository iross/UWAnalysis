'''
File: submitJobs.py
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Generate job submission file.
'''

import json
import fnmatch
import subprocess
from optparse import OptionParser

parser=OptionParser(description="%prog -- dump some analysis-level plots and yields",usage="%prog --extra='extra cuts to apply'")
parser.add_option("--tag",dest="tag",type="string",default="")
parser.add_option("--json",dest="json",type="string",default="datasets.json")
parser.add_option("--samples",dest="samples",type="string",default="")
(options,args)=parser.parse_args()

file = open(options.json)
tag = options.tag

out = open("submitJobs.sh","write")
merge = open("mergeJobs.sh","write")

merge.write("mkdir sandbox\n")
merge.write("cd sandbox\n")

datasets = json.load(file)

def makeFileList(dataset):
    """Dump list of completed files into a .txt file. It's used for merging. And for keeping track of what's done, I guess."""
    subprocess.call("mkdir -p fileLists",shell=True)
    subprocess.call("touch fileLists/{dataset}.txt".format(dataset=dataset),shell=True)
    subprocess.call("ls /hdfs/store/user/$USER/{dataset}_{tag}-{type}/*.root | sed -e 's/\/hdfs//g' > fileLists/{dataset}.txt".format(dataset=dataset,tag=tag,type=datasets[dataset]['type']),shell=True)

for dataset in datasets:
    passes = True
    if options.samples:
        passes = False
        if fnmatch.fnmatchcase(dataset, options.samples):
            passes = True
    if passes:
        makeFileList(dataset)
        merge.write('farmoutAnalysisJobs --skip-existing-output --output-dir=. --merge {dataset}_{tag} $CMSSW_BASE --input-file-list=../fileLists/{dataset}.txt --input-files-per-job=300\n'.format(dataset=dataset,tag=tag))

file.close()
merge.close()
