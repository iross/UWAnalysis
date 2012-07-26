'''
File: submitJobs.py
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Generate job submission file.
'''

import json
import fnmatch
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

out.write("cat LLLL.py > DATA.py\n")
out.write("cat CONDOR.py >> DATA.py\n")
out.write("cat LLLL-MC.py > MC.py\n")
out.write("cat CONDOR.py >> MC.py\n")
out.write("mkdir -p /scratch/$USER/DAGs/{0}/\n".format(tag))

merge.write("mkdir sandbox\n")
merge.write("cd sandbox\n")

datasets = json.load(file)
for dataset in datasets:
    passes = True
    if options.samples:
        passes = False
        if fnmatch.fnmatchcase(dataset, options.samples):
            passes = True
    if passes:
        if datasets[dataset]['url'] == '':
            out.write('farmoutAnalysisJobs --skip-existing-output --output-dir=. --output-dag-file=/scratch/iross/DAGs/{tag}/{dataset} --input-dir=root://cmsxrootd.hep.wisc.edu/{path} {dataset}_{tag} $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/LLLL/{type}.py\n'.format(tag=tag,dataset=dataset,path=datasets[dataset]['path'],type=datasets[dataset]['type']))
        else:
            print datasets[dataset]['path']
            out.write('farmoutAnalysisJobs --skip-existing-output --output-dir=. --output-dag-file=/scratch/iross/DAGs/{tag}/{dataset} --input-dbs-path={path} --dbs-service-url={url} {dataset} $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/LLLL/{type}.py\n'.format(tag=tag,dataset=dataset,path=datasets[dataset]['path'],url=datasets[dataset]['url'],type=datasets[dataset]['type']))
        merge.write('find /scratch/$USER/{dataset}_{tag}-{type}/*/*.root | xargs ls -l | awk \'{{if ($5 > 1000) print $9}}\'| xargs hadd {dataset}.root\n'.format(dataset=dataset,tag=tag,type=datasets[dataset]['type']))
        merge.write('EventWeightsIterative outputFile="{dataset}.root" weight={xsection} histoName="MM/results"\n'.format(dataset=dataset,xsection=datasets[dataset]['xsection'])) 

out.write("rm DATA.py\n")
out.write("rm MC.py\n")

file.close()
out.close()
merge.close()
