#!/bin/bash

#first we need to create the PDFs from the trees




CreateWorkspace outputFile='inputs.root' 


MakeKeysPDF inputFile='inputs/ZLL.root'  inputTrees=$1   cut=$2'&&'$3     pdfNames='SignalPassPdf'          outputFile='inputs.root'         variableNewName='mass'          variable='mass'            rho=1.0        weight='__WEIGHT__'  min=60 max=120. maxentries=10000.

MakeKeysPDF inputFile='inputs/ZLL.root'  inputTrees=$1   cut=$2'&&!('$3')'     pdfNames='SignalFailPdf'          outputFile='inputs.root'         variableNewName='mass'          variable='mass'            rho=1.0        weight='__WEIGHT__'  min=60 max=120. maxentries=10000.

#Real Data -PASS
MakeDataSet inputFile='inputs/DATA.root'  inputTree=$4  cut=$2'&&'$3  name='DATA_REAL_Pass'  outputFile='inputs.root'    variables='mass'  variableNewNames='mass' min=60. max=120.  

#Real Data -FAIL
MakeDataSet inputFile='inputs/DATA.root'  inputTree=$4  cut=$2'&&!('$3')'  name='DATA_REAL_Fail'  outputFile='inputs.root'    variables='mass'  variableNewNames='mass' min=60. max=120.  

MakeSimultaneousDataSet categories='pass','fail' outputfile='inputs.root' inputnames='DATA_REAL_Pass','DATA_REAL_Fail' name='DATA_REAL'




#clean up
rm tmp.root
