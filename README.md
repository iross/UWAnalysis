UWAnalysis, ZZ version
======================

Quickstart recipe
-----------------
    scram pro -n zz533 CMSSW CMSSW_5_3_3_patch1
    cd zz533/src                                                                                                                                                                                                    
    cmsenv
    git clone git@github.com:iross/UWAnalysis
    cd UWAnalysis
    sh recipe.sh
    scram b -j 4

Quick Explanation
-----------------
Each analysis is driven by a python file in UWAnalysis/Configuration/python. This file uses the CutSequenceProducer python class in tools sub directory to create a series of cuts. The user can plug an ntuple plotter in any step of the selection (i.e preselection for background estimates or final selection for shapes). The file tools/analysisTools.py has the core configuration which is common for the analysi. After that the UWAnalysis/CRAB directory has the different final states. There is a file for MC and a file for data. If you look in the py file you will see that it loads the sequence defined in analysisTools. There are also other potential switches to add systematics (shift and clone selection sequence) or add ntuples for each systematics or at preselection selection level. The user can easilly change those. For CRAB submission on the data there is a dedicated script to create a CRAB area and it is explained below.

The ntuplization is absolutely done with python and is controlled by the file UWAnalysis/Configuration/python/tools/zzNtupleTools.py.

Development is being done on the way the ntuples are structured. As of 2012-09-14, the default mode on the master branch is to save one candidate combination per event. In the event that multiple candidates pass the selection, the chosen one is defined as the one at the head of the grand list of candidates (different methods of sorting can be applied).

Submitting Jobs
---------------
CRAB job submission and retrieval scripts are produced via the CRAB/Z[ZH]/submitJobs.py and CRAB/Z[ZH]/mergeJobs.py scripts. The datasets.json file is used to define the datasets of interest (and some of their properties). todo: explain JSON

To create the jobs:

    python submitJobs.py --tag=[identifying tag]
    
By default, this will create job submissions for ALL datasets in datasets.json. To run over a subset, pass a search term (or terms) via the --samples option:

    python submitJobs.py --tag=data2012_testRun --samples "Double*2012*" "MuE*2012*"
    
Then submit the jobs by running the freshly created shell script:

    sh submitJobs.sh

When jobs are complete, running similar mergeJobs commands will create farmout jobs to merge subsets of the data, which must then be added together by hand to create the final ntuple.
   
    python mergeJobs.py --tag=data2012_testRun --samples "Double*2012*" "MuE*2012*"
    sh mergeJobs.sh
    #once these jobs are done, you'll need to go to /scratch/$USER/ and hadd the merged output files


PatTuples
----------------
Default running mode is on the common UW pattuples. Samples are being produced centrally.

For information on creating/using the pattuples, see relevant sections of http://final-state-analysis.readthedocs.org/en/latest/index.html or ask one of us..

Previous Documentation
----------------------
https://twiki.cern.ch/twiki/bin/view/Main/UWDiTau
