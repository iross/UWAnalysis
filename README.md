UWAnalysis, ZZ version
======================

Quickstart recipe
-----------------
    scram pro -n zz533 CMSSW CMSSW_5_3_3_patch1
    cd zz533/src                                                                                                                                                                                                    
    cmsenv
    git clone git@github.com:iross/UWAnalysis
    cd UWAnalysis
    git checkout 53x
    sh recipe.sh
    scram b -j 4

Making patTuples
----------------
Default running mode is on the common UW pattuples. Samples are being produced centrally.

For information on creating/using the pattuples, see relevant sections of http://final-state-analysis.readthedocs.org/en/latest/index.html

Changing things
---------------
Offline
-------
