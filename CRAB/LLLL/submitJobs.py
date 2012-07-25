'''
File: submitJobs.py
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Generate job submission file.
'''

import json
from optparse import OptionParser

parser=OptionParser(description="%prog -- dump some analysis-level plots and yields",usage="%prog --extra='extra cuts to apply'")
parser.add_option("--tag",dest="tag",type="string",default="MC")
parser.add_option("--json",dest="json",type="string",default="datasets.json")
(options,args)=parser.parse_args()

file = open(options.json)
tag = options.tag

out = open("submitJobs.sh","write")

out.write("cat LLLL.py > DATA.py\n")
out.write("cat CONDOR.py >> DATA.py\n")
out.write("cat LLLL-MC.py > MC.py\n")
out.write("cat CONDOR.py >> MC.py\n")
out.write("mkdir -p /scratch/$USER/DAGs/{0}/\n".format(tag))

datasets = json.load(file)
for dataset in datasets:
    if datasets[dataset]['url'] == '':
        out.write('farmoutAnalysisJobs --skip-existing-output --output-dir=. --output-dag-file=/scratch/iross/DAGs/{tag}/{dataset} --input-dir=root://cmsxrootd.hep.wisc.edu/{path} {dataset}_{tag} $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/LLLL/{type}.py\n'.format(tag=tag,dataset=dataset,path=datasets[dataset]['path'],type=datasets[dataset]['type']))
    else:
        print datasets[dataset]['path']
        out.write('farmoutAnalysisJobs --skip-existing-output --output-dir=. --output-dag-file=/scratch/iross/DAGs/{tag}/{dataset} --input-dbs-path={path} --dbs-service-url={url} {dataset} $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/LLLL/{type}.py\n'.format(tag=tag,dataset=dataset,path=datasets[dataset]['path'],url=datasets[dataset]['url'],type=datasets[dataset]['type']))

out.write("rm DATA.py\n")
out.write("rm MC.py\n")

file.close()
out.close()
