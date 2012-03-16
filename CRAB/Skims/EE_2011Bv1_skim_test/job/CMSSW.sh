#!/bin/sh

# put STDERR to STDOUT 
exec 2>&1

echo "This script was generated by crab (version 2.8.0)."
#
# HEAD
#
#
echo "Running $0 with $# positional parameters: $*"

getRandSeed() {
     den=(0 1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d e f g h i j k l m n o p q r s t u v w x y z)
    nd=${#den[*]}
    randj=${den[$RANDOM % $nd]}${den[$RANDOM % $nd]}${den[$RANDOM % $nd]}
    echo $randj
}

dumpStatus() {
    echo ">>> info for dashboard:"
    echo "***** Cat $1 *****"
    cat $1
    echo "***** End Cat jobreport *****"
    chmod a+x $RUNTIME_AREA/report.py

    $RUNTIME_AREA/report.py $(cat $1)
    rm -f $1
    echo "MonitorJobID=`echo $MonitorJobID`" > $1
    echo "MonitorID=`echo $MonitorID`" >> $1
}


### REMOVE THE WORKING_DIR IN OSG SITES ###
remove_working_dir() {
    cd $RUNTIME_AREA
    echo ">>> working dir = $WORKING_DIR"
    echo ">>> current directory (RUNTIME_AREA): $RUNTIME_AREA"
    echo ">>> Remove working directory: $WORKING_DIR"
    /bin/rm -rf $WORKING_DIR
    if [ -d $WORKING_DIR ] ;then
        echo "ERROR ==> OSG $WORKING_DIR could not be deleted on WN `hostname`"
        job_exit_code=10017
    fi
}

### DUMP ORIGINAL ENVIRONMENT BEFORE CMSSW CUSTOMIZATIOn
dumpEnv(){
echo export PATH=$PATH >> CacheEnv.sh
echo export LD_LIBRARY_PATH=$LD_LIBRARY_PATH >> CacheEnv.sh
echo export PYTHONPATH=$PYTHONPATH >> CacheEnv.sh
}



#
# EXECUTE THIS FUNCTION BEFORE EXIT 
#

func_exit() { 
    if [ $PYTHONPATH ]; then 
       if [ ! -s $RUNTIME_AREA/fillCrabFjr.py ]; then 
           echo "WARNING: it is not possible to create crab_fjr.xml to final report" 
       else 
           python $RUNTIME_AREA/fillCrabFjr.py $RUNTIME_AREA/crab_fjr_$NJob.xml --errorcode $job_exit_code $executable_exit_status 
       fi
    fi
    cd $RUNTIME_AREA  
    for file in $filesToCheck ; do
        if [ -e $file ]; then
            echo "tarring file $file in  $out_files"
        else
            echo "WARNING: output file $file not found!"
        fi
    done
    if [ $middleware == OSG ]; then
        final_list=$filesToCheck
        if [ $WORKING_DIR ]; then
            remove_working_dir
        fi
        symlinks -d .
    else
        final_list=$filesToCheck" .BrokerInfo"
    fi
    TIME_WRAP_END=`date +%s`
    let "TIME_WRAP = TIME_WRAP_END - TIME_WRAP_INI" 

    let "MIN_JOB_DURATION = 60*10" 
    let "PADDING_DURATION = MIN_JOB_DURATION - TIME_WRAP" 
    if [ $PADDING_DURATION -gt 0 ]; then 
        echo ">>> padding time: Sleeping the wrapper for $PADDING_DURATION seconds"
        sleep $PADDING_DURATION
        TIME_WRAP_END=`date +%s`
        let "TIME_WRAP = TIME_WRAP_END - TIME_WRAP_INI" 
    else 
        echo ">>> padding time: Wrapper lasting more than $MIN_JOB_DURATION seconds. No sleep required."
    fi

    if [ $PYTHONPATH ]; then 
       if [ ! -s $RUNTIME_AREA/fillCrabFjr.py ]; then 
           echo "WARNING: it is not possible to create crab_fjr.xml to final report" 
       else 
           set -- $CPU_INFOS 
           echo "CrabUserCpuTime=$1" >>  $RUNTIME_AREA/$repo 
           echo "CrabSysCpuTime=$2" >>  $RUNTIME_AREA/$repo 
           echo "CrabCpuPercentage=$3" >>  $RUNTIME_AREA/$repo 
           python $RUNTIME_AREA/fillCrabFjr.py $RUNTIME_AREA/crab_fjr_$NJob.xml --timing $TIME_WRAP $TIME_EXE $TIME_STAGEOUT \"$CPU_INFOS\" 
           echo "CrabWrapperTime=$TIME_WRAP" >> $RUNTIME_AREA/$repo 
           if [ $TIME_STAGEOUT -lt 0 ]; then 
               export TIME_STAGEOUT=NULL 
           fi
           echo "CrabStageoutTime=$TIME_STAGEOUT" >> $RUNTIME_AREA/$repo 
       fi
    fi
    echo "Disk space used:"
    echo "du -sh $RUNTIME_AREA"
    du -sh $RUNTIME_AREA 

    dumpStatus $RUNTIME_AREA/$repo 

    echo "JOB_EXIT_STATUS = $job_exit_code"
    echo "JobExitCode=$job_exit_code" >> $RUNTIME_AREA/$repo
    dumpStatus $RUNTIME_AREA/$repo
    tar zcvf ${out_files}.tgz  ${final_list}
    exit $job_exit_code
}



RUNTIME_AREA=`pwd`
export RUNTIME_AREA

echo "Today is `date`"
echo "Job submitted on host `hostname`"
uname -a
echo ">>> current directory (RUNTIME_AREA): `pwd`"
echo ">>> current directory content:"
ls -Al
echo ">>> current user: `id`"
echo ">>> voms proxy information:"
voms-proxy-info -all

repo=jobreport.txt



#Written by cms_cmssw::wsUntarSoftware
echo ">>> tar xzf $RUNTIME_AREA/default.tgz :" 
tar zxvf $RUNTIME_AREA/default.tgz
untar_status=$? 
if [ $untar_status -ne 0 ]; then 
   echo "ERROR ==> Untarring .tgz file failed"
   job_exit_code=$untar_status
   func_exit
else 
   echo "Successful untar" 
   chmod a+w -R $RUNTIME_AREA 
   chmod 600 $X509_USER_PROXY 
fi 

echo ">>> Include $RUNTIME_AREA in PYTHONPATH:"
if [ -z "$PYTHONPATH" ]; then
   export PYTHONPATH=$RUNTIME_AREA/
else
   export PYTHONPATH=$RUNTIME_AREA/:${PYTHONPATH}
echo "PYTHONPATH=$PYTHONPATH"
fi


#
# SETUP ENVIRONMENT
#

export TIME_WRAP_INI=`date +%s` 
export TIME_STAGEOUT=-2 

# glidein specific stuff
# strip arguments
echo "strip arguments"
args=("$@")
nargs=$#
shift $nargs
# job number (first parameter for job wrapper)
NJob=${args[0]}; export NJob
NResub=${args[1]}; export NResub
NRand=`getRandSeed`; export NRand
OutUniqueID=_$NRand
OutUniqueID=_$NResub$OutUniqueID
OutUniqueID=$NJob$OutUniqueID; export OutUniqueID
out_files=out_files_${NJob}; export out_files
echo $out_files
echo ">>> list of expected files on output sandbox"
echo "output files: crab_fjr_$NJob.xml CMSSW_$NJob.stdout CMSSW_$NJob.stderr"
filesToCheck="crab_fjr_$NJob.xml CMSSW_$NJob.stdout CMSSW_$NJob.stderr"
export filesToCheck
if [ $Glidein_MonitorID ]; then 
   MonitorJobID=${NJob}_${Glidein_MonitorID}
   SyncGridJobId=${Glidein_MonitorID}
else 
   MonitorJobID=${NJob}_$Glidein_MonitorID
   SyncGridJobId=$Glidein_MonitorID
fi
MonitorID=iross_EE_2011Bv1_skim_test_s74o1n
echo "MonitorJobID=$MonitorJobID" > $RUNTIME_AREA/$repo 
echo "SyncGridJobId=$SyncGridJobId" >> $RUNTIME_AREA/$repo 
echo "MonitorID=$MonitorID" >> $RUNTIME_AREA/$repo
echo ">>> GridFlavour discovery: " 
if [ $OSG_APP ]; then 
    middleware=OSG 
    if [ $OSG_JOB_CONTACT ]; then 
        SyncCE="$OSG_JOB_CONTACT"; 
        echo "SyncCE=$SyncCE" >> $RUNTIME_AREA/$repo ;
    else
        echo "not reporting SyncCE";
    fi
    echo "GridFlavour=$middleware" | tee -a $RUNTIME_AREA/$repo 
    echo "source OSG GRID setup script" 
    source $OSG_GRID/setup.sh 
elif [ $NORDUGRID_CE ]; then 
    middleware=ARC 
    echo "SyncCE=${NORDUGRID_CE}:2811/nordugrid-GE-${QUEUE:-queue}" >> $RUNTIME_AREA/$repo 
    echo "GridFlavour=$middleware" | tee -a $RUNTIME_AREA/$repo 
elif [ $VO_CMS_SW_DIR ]; then 
    middleware=LCG 
    if  [ $GLIDEIN_Gatekeeper ]; then 
        echo "SyncCE=`echo $GLIDEIN_Gatekeeper | sed -e s/:2119//`" >> $RUNTIME_AREA/$repo 
    else 
        echo "SyncCE=`glite-brokerinfo getCE`" >> $RUNTIME_AREA/$repo 
    fi 
    echo "GridFlavour=$middleware" | tee -a $RUNTIME_AREA/$repo 
else 
    echo "ERROR ==> GridFlavour not identified" 
    job_exit_code=10030 
    func_exit 
fi 
dumpStatus $RUNTIME_AREA/$repo 


export VO=cms
if [ $middleware == LCG ]; then
   if  [ $GLIDEIN_Gatekeeper ]; then
       CloseCEs=$GLIDEIN_Gatekeeper 
   else
       CloseCEs=`glite-brokerinfo getCE`
   fi
   echo "CloseCEs = $CloseCEs"
   CE=`echo $CloseCEs | sed -e "s/:.*//"`
   echo "CE = $CE"
elif [ $middleware == OSG ]; then 
    if [ $OSG_JOB_CONTACT ]; then 
        CE=`echo $OSG_JOB_CONTACT | /usr/bin/awk -F\/ '{print $1}'` 
    else 
        echo "ERROR ==> OSG mode in setting CE name from OSG_JOB_CONTACT" 
        job_exit_code=10099
        func_exit
    fi 
elif [ $middleware == ARC ]; then 
    echo "CE = $NORDUGRID_CE"
fi 

dumpEnv


#Written by cms_cmssw::wsSetupEnvironment
echo ">>> setup environment"
echo "set SCRAM ARCH to slc5_amd64_gcc434"
export SCRAM_ARCH=slc5_amd64_gcc434
echo "SCRAM_ARCH = $SCRAM_ARCH"
if [ $middleware == LCG ] || [ $middleware == CAF ] || [ $middleware == LSF ]; then 

#Written by cms_cmssw::wsSetupCMSLCGEnvironment_
    echo ">>> setup CMS LCG environment:"
    echo "set SCRAM ARCH and BUILD_ARCH to slc5_amd64_gcc434 ###"
    export SCRAM_ARCH=slc5_amd64_gcc434
    export BUILD_ARCH=slc5_amd64_gcc434
    if [ ! $VO_CMS_SW_DIR ] ;then
        echo "ERROR ==> CMS software dir not found on WN `hostname`"
        job_exit_code=10031
        func_exit
    else
        echo "Sourcing environment... "
        if [ ! -s $VO_CMS_SW_DIR/cmsset_default.sh ] ;then
            echo "ERROR ==> cmsset_default.sh file not found into dir $VO_CMS_SW_DIR"
            job_exit_code=10020
            func_exit
        fi
        echo "sourcing $VO_CMS_SW_DIR/cmsset_default.sh"
        source $VO_CMS_SW_DIR/cmsset_default.sh
        result=$?
        if [ $result -ne 0 ]; then
            echo "ERROR ==> problem sourcing $VO_CMS_SW_DIR/cmsset_default.sh"
            job_exit_code=10032
            func_exit
        fi
    fi
    
    echo "==> setup cms environment ok"
elif [ $middleware == OSG ]; then
    WORKING_DIR=`/bin/mktemp  -d $OSG_WN_TMP/cms_XXXXXXXXXXXX`
    if [ ! $? == 0 ] ;then
        echo "ERROR ==> OSG $WORKING_DIR could not be created on WN `hostname`"
        job_exit_code=10016
        func_exit
    fi
    echo ">>> Created working directory: $WORKING_DIR"

    echo "Change to working directory: $WORKING_DIR"
    cd $WORKING_DIR
    echo ">>> current directory (WORKING_DIR): $WORKING_DIR"

#Written by cms_cmssw::wsSetupCMSOSGEnvironment_
    echo ">>> setup CMS OSG environment:"
    echo "set SCRAM ARCH to slc5_amd64_gcc434"
    export SCRAM_ARCH=slc5_amd64_gcc434
    echo "SCRAM_ARCH = $SCRAM_ARCH"
    if [ -f $OSG_APP/cmssoft/cms/cmsset_default.sh ] ;then
      # Use $OSG_APP/cmssoft/cms/cmsset_default.sh to setup cms software
        source $OSG_APP/cmssoft/cms/cmsset_default.sh CMSSW_4_2_5
    else
        echo "ERROR ==> $OSG_APP/cmssoft/cms/cmsset_default.sh file not found"
        job_exit_code=10020
        func_exit
    fi

    echo "==> setup cms environment ok"
    echo "SCRAM_ARCH = $SCRAM_ARCH"
elif [ $middleware == SGE ]; then

#Written by cms_cmssw::wsSetupCMSLCGEnvironment_
    echo ">>> setup CMS LCG environment:"
    echo "set SCRAM ARCH and BUILD_ARCH to slc5_amd64_gcc434 ###"
    export SCRAM_ARCH=slc5_amd64_gcc434
    export BUILD_ARCH=slc5_amd64_gcc434
    if [ ! $VO_CMS_SW_DIR ] ;then
        echo "ERROR ==> CMS software dir not found on WN `hostname`"
        job_exit_code=10031
        func_exit
    else
        echo "Sourcing environment... "
        if [ ! -s $VO_CMS_SW_DIR/cmsset_default.sh ] ;then
            echo "ERROR ==> cmsset_default.sh file not found into dir $VO_CMS_SW_DIR"
            job_exit_code=10020
            func_exit
        fi
        echo "sourcing $VO_CMS_SW_DIR/cmsset_default.sh"
        source $VO_CMS_SW_DIR/cmsset_default.sh
        result=$?
        if [ $result -ne 0 ]; then
            echo "ERROR ==> problem sourcing $VO_CMS_SW_DIR/cmsset_default.sh"
            job_exit_code=10032
            func_exit
        fi
    fi
    
    echo "==> setup cms environment ok"
elif [ $middleware == ARC ]; then

#Written by cms_cmssw::wsSetupCMSLCGEnvironment_
    echo ">>> setup CMS LCG environment:"
    echo "set SCRAM ARCH and BUILD_ARCH to slc5_amd64_gcc434 ###"
    export SCRAM_ARCH=slc5_amd64_gcc434
    export BUILD_ARCH=slc5_amd64_gcc434
    if [ ! $VO_CMS_SW_DIR ] ;then
        echo "ERROR ==> CMS software dir not found on WN `hostname`"
        job_exit_code=10031
        func_exit
    else
        echo "Sourcing environment... "
        if [ ! -s $VO_CMS_SW_DIR/cmsset_default.sh ] ;then
            echo "ERROR ==> cmsset_default.sh file not found into dir $VO_CMS_SW_DIR"
            job_exit_code=10020
            func_exit
        fi
        echo "sourcing $VO_CMS_SW_DIR/cmsset_default.sh"
        source $VO_CMS_SW_DIR/cmsset_default.sh
        result=$?
        if [ $result -ne 0 ]; then
            echo "ERROR ==> problem sourcing $VO_CMS_SW_DIR/cmsset_default.sh"
            job_exit_code=10032
            func_exit
        fi
    fi
    
    echo "==> setup cms environment ok"
elif [ $middleware == PBS ]; then

#Written by cms_cmssw::wsSetupCMSLCGEnvironment_
    echo ">>> setup CMS LCG environment:"
    echo "set SCRAM ARCH and BUILD_ARCH to slc5_amd64_gcc434 ###"
    export SCRAM_ARCH=slc5_amd64_gcc434
    export BUILD_ARCH=slc5_amd64_gcc434
    if [ ! $VO_CMS_SW_DIR ] ;then
        echo "ERROR ==> CMS software dir not found on WN `hostname`"
        job_exit_code=10031
        func_exit
    else
        echo "Sourcing environment... "
        if [ ! -s $VO_CMS_SW_DIR/cmsset_default.sh ] ;then
            echo "ERROR ==> cmsset_default.sh file not found into dir $VO_CMS_SW_DIR"
            job_exit_code=10020
            func_exit
        fi
        echo "sourcing $VO_CMS_SW_DIR/cmsset_default.sh"
        source $VO_CMS_SW_DIR/cmsset_default.sh
        result=$?
        if [ $result -ne 0 ]; then
            echo "ERROR ==> problem sourcing $VO_CMS_SW_DIR/cmsset_default.sh"
            job_exit_code=10032
            func_exit
        fi
    fi
    
    echo "==> setup cms environment ok"
fi


echo ">>> specific cmssw setup environment:"
echo "CMSSW_VERSION =  CMSSW_4_2_5"
scram project CMSSW CMSSW_4_2_5
status=$?
if [ $status != 0 ] ; then
    echo "ERROR ==> CMSSW CMSSW_4_2_5 not found on `hostname`" 
    job_exit_code=10034
    func_exit
fi 
cd CMSSW_4_2_5
SOFTWARE_DIR=`pwd`; export SOFTWARE_DIR
echo ">>> current directory (SOFTWARE_DIR): $SOFTWARE_DIR" 
eval `scram runtime -sh | grep -v SCRAMRT_LSB_JOBNAME`
if [ $? != 0 ] ; then
    echo "ERROR ==> Problem with the command: "
    echo "eval \`scram runtime -sh | grep -v SCRAMRT_LSB_JOBNAME \` at `hostname`"
    job_exit_code=10034
    func_exit
fi 

## number of arguments (first argument always jobnumber, the second is the resubmission number)

if [ $nargs -lt 2 ]
then
    echo 'ERROR ==> Too few arguments' +$nargs+ 
    job_exit_code=50113
    func_exit
fi


DatasetPath=/DoubleElectron/Run2011B-PromptReco-v1/AOD
PrimaryDataset=DoubleElectron
DataTier=Run2011B-PromptReco-v1
ApplicationFamily=cmsRun

cp  $RUNTIME_AREA/CMSSW.py .
cp  $RUNTIME_AREA/CMSSW.py.pkl .
PreserveSeeds=; export PreserveSeeds
IncrementSeeds=; export IncrementSeeds
echo "PreserveSeeds: <$PreserveSeeds>"
echo "IncrementSeeds:<$IncrementSeeds>"
mv -f CMSSW.py pset.py
export var_filter='{"skim.root": null}'
echo $var_filter
echo "WNHostName=`hostname`" | tee -a $RUNTIME_AREA/$repo
dumpStatus $RUNTIME_AREA/$repo

#
# END OF SETUP ENVIRONMENT
#
#
# PREPARE AND RUN EXECUTABLE
#


#Written by cms_cmssw::wsBuildExe
echo ">>> moving CMSSW software directories in `pwd`" 
rm -rf lib/ module/ 
mv $RUNTIME_AREA/lib/ . 
mv $RUNTIME_AREA/module/ . 
rm -rf src/ 
mv $RUNTIME_AREA/src/ . 
echo ">>> Include $RUNTIME_AREA in PYTHONPATH:"
if [ -z "$PYTHONPATH" ]; then
   export PYTHONPATH=$RUNTIME_AREA/
else
   export PYTHONPATH=$RUNTIME_AREA/:${PYTHONPATH}
echo "PYTHONPATH=$PYTHONPATH"
fi


edmConfigHash pset.py 
PSETHASH=`edmConfigHash pset.py` 
echo "PSETHASH = $PSETHASH" 
if [ -z "$PSETHASH" ]; then 
   export PSETHASH=null
fi 

executable=cmsRun


#
# END OF PREPARE AND RUN EXECUTABLE
#

#
# COPY INPUT
#


#
# Rewrite cfg or cfgpy file
#

# Rewrite cfg for this job
echo  $RUNTIME_AREA/writeCfg.py  pset.py pset.py
python $RUNTIME_AREA/writeCfg.py  pset.py pset.py

        result=$?
        if [ $result -ne 0 ]; then
            echo "ERROR ==> problem re-writing config file"
            job_exit_code=10040
            func_exit
        fi

          
cat $RUNTIME_AREA/inputsReport.txt  

echo ">>> Executable $executable"
which $executable
res=$?
if [ $res -ne 0 ];then
  echo "ERROR ==> executable not found on WN `hostname`"
  job_exit_code=10035
  func_exit
else
  echo "ok executable found"
fi

echo "ExeStart=$executable" >>  $RUNTIME_AREA/$repo
dumpStatus $RUNTIME_AREA/$repo

echo ">>> $executable started at `date -u`"
start_exe_time=`date +%s`
CPU_INFOS=-1 
/usr/bin/time -f "%U %S %P" -o cpu_timing.txt $executable  -j $RUNTIME_AREA/crab_fjr_$NJob.xml -p pset.py
executable_exit_status=$?
CPU_INFOS=`tail -n 1 cpu_timing.txt`
stop_exe_time=`date +%s`
echo ">>> $executable ended at `date -u`"

#### dashboard add timestamp!
echo "ExeEnd=$executable" >> $RUNTIME_AREA/$repo
dumpStatus $RUNTIME_AREA/$repo

let "TIME_EXE = stop_exe_time - start_exe_time"
echo "TIME_EXE = $TIME_EXE sec"
echo "ExeTime=$TIME_EXE" >> $RUNTIME_AREA/$repo



#Written by cms_cmssw::wsParseFJR
echo ">>> Parse FrameworkJobReport crab_fjr.xml"
if [ -s $RUNTIME_AREA/crab_fjr_$NJob.xml ]; then
    if [ -s $RUNTIME_AREA/parseCrabFjr.py ]; then
        cmd_out=`python $RUNTIME_AREA/parseCrabFjr.py --input $RUNTIME_AREA/crab_fjr_$NJob.xml --dashboard $MonitorID,$MonitorJobID `
        cmd_out_1=`python $RUNTIME_AREA/parseCrabFjr.py --input $RUNTIME_AREA/crab_fjr_$NJob.xml --popularity $MonitorID,$MonitorJobID,$RUNTIME_AREA/inputsReport.txt `
        echo "Result of parsing the FrameworkJobReport crab_fjr.xml: $cmd_out_1"
        executable_exit_status=`python $RUNTIME_AREA/parseCrabFjr.py --input $RUNTIME_AREA/crab_fjr_$NJob.xml --exitcode`
        if [ $executable_exit_status -eq 50115 ];then
            echo ">>> crab_fjr.xml contents: "
            cat $RUNTIME_AREA/crab_fjr_$NJob.xml
            echo "Wrong FrameworkJobReport --> does not contain useful info. ExitStatus: $executable_exit_status"
        elif [ $executable_exit_status -eq -999 ];then
            echo "ExitStatus from FrameworkJobReport not available. not available. Using exit code of executable from command line."
        else
            echo "Extracted ExitStatus from FrameworkJobReport parsing output: $executable_exit_status"
        fi
    else
        echo "CRAB python script to parse CRAB FrameworkJobReport crab_fjr.xml is not available, using exit code of executable from command line."
    fi
    if [ $executable_exit_status -eq 0 ];then
        echo ">>> Executable succeded  $executable_exit_status"
    fi
else
    echo "CRAB FrameworkJobReport crab_fjr.xml is not available, using exit code of executable from command line."
fi

if [ $executable_exit_status -ne 0 ];then
    echo ">>> Executable failed  $executable_exit_status"
    echo "ExeExitCode=$executable_exit_status" | tee -a $RUNTIME_AREA/$repo
    echo "EXECUTABLE_EXIT_STATUS = $executable_exit_status"
    job_exit_code=$executable_exit_status
    func_exit
fi

echo "ExeExitCode=$executable_exit_status" | tee -a $RUNTIME_AREA/$repo
echo "EXECUTABLE_EXIT_STATUS = $executable_exit_status"
job_exit_code=$executable_exit_status


#
# PROCESS THE PRODUCED RESULTS
#



#Written by cms_cmssw::wsRenameOutput
echo ">>> current directory (SOFTWARE_DIR): $SOFTWARE_DIR" 
echo ">>> current directory content:"
ls -Al


# check output file
if [ -e ./skim.root ] ; then
    mv skim.root skim_$OutUniqueID.root
    ln -s `pwd`/skim_$OutUniqueID.root $RUNTIME_AREA/skim.root
else
    job_exit_code=60302
    echo "WARNING: Output file skim.root not found"
fi
file_list="$SOFTWARE_DIR/skim_$OutUniqueID.root"

echo ">>> current directory (SOFTWARE_DIR): $SOFTWARE_DIR" 
echo ">>> current directory content:"
ls -Al

cd $RUNTIME_AREA
echo ">>> current directory (RUNTIME_AREA):  $RUNTIME_AREA"


#
# COPY OUTPUT FILE TO SE
#

export SE=cmssrm.hep.wisc.edu
echo "SE = $SE"
export SE_PATH=/srm/v2/server?SFN=/hdfs/store/user/iross/.//EE_2011Bv1_skim_test/
echo "SE_PATH = $SE_PATH"
export LFNBaseName=/store/user/iross/.//EE_2011Bv1_skim_test/
echo "LFNBaseName = $LFNBaseName"
export USER=iross
echo "USER = $USER"
export endpoint=srm://cmssrm.hep.wisc.edu:8443/srm/v2/server?SFN=/hdfs/store/user/iross/.//EE_2011Bv1_skim_test/
echo "endpoint = $endpoint"
echo ">>> Copy output files from WN = `hostname` to $SE_PATH :"
export TIME_STAGEOUT_INI=`date +%s` 
copy_exit_status=0
echo "python cmscp.py  --destination $endpoint --inputFileList $file_list --middleware $middleware --se_name $SE --for_lfn $LFNBaseName    "
python cmscp.py  --destination $endpoint --inputFileList $file_list --middleware $middleware --se_name $SE --for_lfn $LFNBaseName    
if [ -f $RUNTIME_AREA/resultCopyFile ] ;then
    cat $RUNTIME_AREA/resultCopyFile
    pwd
else
    echo "ERROR ==> $RUNTIME_AREA/resultCopyFile file not found. Problem during the stageout"
    echo "RUNTIME_AREA content: " 
    ls $RUNTIME_AREA 
    job_exit_code=60318
    func_exit 
fi
if [ -f cmscpReport.sh ] ;then
    cat cmscpReport.sh
    source cmscpReport.sh
    source_result=$? 
    if [ $source_result -ne 0 ]; then
        echo "problem with the source of cmscpReport.sh file"
        StageOutExitStatus=60307
    fi
else
    echo "cmscpReport.sh file not found"
    StageOutExitStatus=60307
fi
if [ $StageOutExitStatus -ne 0 ]; then
    echo "Problem copying file to $SE $SE_PATH"
    copy_exit_status=$StageOutExitStatus 
if [ -f .SEinteraction.log ] ;then
    echo "########## contents of SE interaction"
    cat .SEinteraction.log
    echo "#####################################"
else
    echo ".SEinteraction.log file not found"
fi
    job_exit_code=$StageOutExitStatus
fi
export TIME_STAGEOUT_END=`date +%s` 
let "TIME_STAGEOUT = TIME_STAGEOUT_END - TIME_STAGEOUT_INI" 

echo ">>> current dir: `pwd`"
echo ">>> current dir content:"
ls -Al


#Written by cms_cmssw::wsModifyReport
echo ">>> Modify Job Report:" 
chmod a+x $RUNTIME_AREA/ProdCommon/FwkJobRep/ModifyJobReport.py
echo "CMSSW_VERSION = $CMSSW_VERSION"

echo "$RUNTIME_AREA/ProdCommon/FwkJobRep/ModifyJobReport.py fjr $RUNTIME_AREA/crab_fjr_$NJob.xml json $RUNTIME_AREA/resultCopyFile n_job $OutUniqueID PrimaryDataset $PrimaryDataset  ApplicationFamily $ApplicationFamily ApplicationName $executable cmssw_version $CMSSW_VERSION psethash $PSETHASH"
$RUNTIME_AREA/ProdCommon/FwkJobRep/ModifyJobReport.py fjr $RUNTIME_AREA/crab_fjr_$NJob.xml json $RUNTIME_AREA/resultCopyFile n_job $OutUniqueID PrimaryDataset $PrimaryDataset  ApplicationFamily $ApplicationFamily ApplicationName $executable cmssw_version $CMSSW_VERSION psethash $PSETHASH
modifyReport_result=$?
if [ $modifyReport_result -ne 0 ]; then
    modifyReport_result=70500
    job_exit_code=$modifyReport_result
    echo "ModifyReportResult=$modifyReport_result" | tee -a $RUNTIME_AREA/$repo
    echo "WARNING: Problem with ModifyJobReport"
else
    mv NewFrameworkJobReport.xml $RUNTIME_AREA/crab_fjr_$NJob.xml
fi

#
# END OF PROCESS THE PRODUCED RESULTS
#


func_exit
