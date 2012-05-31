#!/usr/bin/env python
from math import *
import os
from optparse import OptionParser
import ROOT

parser = OptionParser(usage="usage: %prog [options]  \nrun with --help to get list of options")
parser.add_option("-o", "--out",      dest="out",      default="TestGrid",  type="string", help="output file prefix")
parser.add_option("-m", "--mass",      dest="mass",      default=120,  type="int", help="mass")
parser.add_option("-O", "--options",  dest="options",  default="--freq  --testStat LHC ",  type="string", help="options to use for combine")
(options, args) = parser.parse_args()
    

print "Creating executable script ",options.out+".sh"


script = open(options.out+"_analyze.sh", "w")
script.write("#!/bin/bash \n")
script.write("rm higgsCombine* \n")
script.write("cp {cwd}/workspace.{workspace}.root . \n".format(cwd=os.getcwd(),workspace=options.out))
script.write("cp {cwd}/CLS_{workspace}.root . \n".format(cwd=os.getcwd(),workspace=options.out))
script.write("$CMSSW_BASE/bin/$SCRAM_ARCH/combine  workspace.{workspace}.root  -M HybridNew  {options} --grid=CLS_{workspace}.root -m {mass} \n ".format(workspace=options.out,options=options.options,mass=options.mass))
script.write("$CMSSW_BASE/bin/$SCRAM_ARCH/combine  workspace.{workspace}.root  -M HybridNew  {options} --grid=CLS_{workspace}.root --expectedFromGrid=0.5 -m {mass} \n ".format(workspace=options.out,options=options.options,mass=options.mass))
script.write("$CMSSW_BASE/bin/$SCRAM_ARCH/combine  workspace.{workspace}.root  -M HybridNew  {options} --grid=CLS_{workspace}.root --expectedFromGrid=0.16 -m {mass}\n ".format(workspace=options.out,options=options.options,mass=options.mass))
script.write("$CMSSW_BASE/bin/$SCRAM_ARCH/combine  workspace.{workspace}.root  -M HybridNew  {options} --grid=CLS_{workspace}.root --expectedFromGrid=0.84 -m {mass}\n ".format(workspace=options.out,options=options.options,mass=options.mass))
script.write("$CMSSW_BASE/bin/$SCRAM_ARCH/combine  workspace.{workspace}.root  -M HybridNew  {options} --grid=CLS_{workspace}.root --expectedFromGrid=0.0275 -m {mass}\n ".format(workspace=options.out,options=options.options,mass=options.mass))
script.write("$CMSSW_BASE/bin/$SCRAM_ARCH/combine  workspace.{workspace}.root  -M HybridNew  {options} --grid=CLS_{workspace}.root --expectedFromGrid=0.975 -m {mass}\n ".format(workspace=options.out,options=options.options,mass=options.mass))

script.write("hadd out.root higgsCombine*.root\n")
script.write("mv out.root $OUTPUT\n")
script.write("\n");
script.close()
os.system("chmod +x {prefix}_analyze.sh".format(prefix=options.out))
os.system("mv {prefix}_analyze.sh submit/".format(prefix=options.out))
os.system("farmoutAnalysisJobs  --express-queue   --input-dir=$PWD  --match-input-files={workspace}.txt --fwklite  --output-dir=. CLSResults_{workspace} $CMSSW_BASE $PWD/submit/{workspace}_analyze.sh".format(workspace=options.out))
