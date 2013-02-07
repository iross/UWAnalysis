Generate `datasets.json` From PatTuple List
-------------------------------------------

Tapas has made scripts available to find information about available patTuples and their
locations in hdfs. To use them, you must first `cmsenv` in the `FinalStateAnalysis` area. 
Then run

    source /afs/hep.wisc.edu/home/tapas/work/phedex-subs/setFinalStateAnalysisPythonPath 
    python /afs/hep.wisc.edu/home/tapas/work/phedex-subs/getPatTupleInfo.py -h

which will print help information on the `getPatTupleInfo.py` tool. Suppose you wanted
the latest 8 TeV samples. You would run

    python /afs/hep.wisc.edu/home/tapas/work/phedex-subs/getPatTupleInfo.py -e 8 -l > pattuples.txt

which would list all 8 TeV patTuples and store the output in `pattuples.txt`. In order to
submit jobs to Condor, the file `datasets.json` is required. If necessary, the tool
`extractDatasets.py` can be used to generate this file. The usage is

    python extractDatasets.py --patTupleList pattuples.txt --datasetList datasetlist.txt --outputJson datasets.json

The file `datasetlist.txt` should be formatted as in this example:

    #[name] [type] [provide xsec if MC] [DAS dataset name]
    
    # DATA samples
    DoubleElectron2012A         DATA    /DoubleElectron/Run2012A-13Jul2012-v1/AOD
    DoubleElectron2012Arecover  DATA    /DoubleElectron/Run2012A-recover-06Aug2012-v1/AOD
    DoubleElectron2012B         DATA    /DoubleElectron/Run2012B-13Jul2012-v1/AOD
    DoubleElectron2012Cv1       DATA    /DoubleElectron/Run2012C-PromptReco-v1/AOD
    DoubleElectron2012Cv2       DATA    /DoubleElectron/Run2012C-PromptReco-v2/AOD
    
    # MC samples -- be sure to provide cross-section
    ggH115                      MC      0.01232     /GluGluToHToZZTo4L_M-115_8TeV-powheg-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
