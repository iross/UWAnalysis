#!/bin/bash

#first we need to create the PDFs from the trees

CreateWorkspace outputFile='diTau.root' 



MakeKeysPDF inputFile='inputs/mutau/ZTTPOWHEG3.root'  inputTrees='muTauEventTreeNominal/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree'   cut='mumuSize==0&&HLT_Any'     pdfNames='ZTTPdf_MuTau','ZTTPdfTauUp_MuTau','ZTTPdfTauDown_MuTau'          outputFile='diTau.root'         variableNewName='mass'          variable='muTauMass'            rho=2.0            weight='__WEIGHT__'  normnames='ZTTMCNorm_MuTau'

MakeInterpolatedMorphPDF channel='MuTau' prefix='ZTTPdf' shifts='Tau'

				 
MakeKeysPDF inputFile='inputs/mutau/W.root' inputTrees='muTauEventTreeNominal/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut='mumuSize==0&&HLT_Any' \
                                 pdfNames='WPdf_MuTau','WPdfTauUp_MuTau','WPdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 variable='muTauMass' \
                                 variableNewName='mass' \
                                 weight='__WEIGHT__' \
                                 normnames='WMCNorm_MuTau' \

MakeInterpolatedMorphPDF channel='MuTau' prefix='WPdf' shifts='Tau'



MakeKeysPDF inputFile='inputs/mutau/ZMM.root' inputTrees='muTauEventTreeNominal/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut='mumuSize==0&&HLT_Any&&muTauGenPt2<=0' \
                                 pdfNames='ZJFTPdf_MuTau','ZJFTPdfTauUp_MuTau','ZJFTPdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 normnames='ZJFTMCNorm_MuTau' \
                                 variable='muTauMass' \
                                 variableNewName='mass' 

MakeInterpolatedMorphPDF channel='MuTau' prefix='ZJFTPdf' shifts='Tau'


MakeKeysPDF inputFile='inputs/mutau/TOP.root' inputTrees='muTauEventTreeNominal/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut='mumuSize==0&&HLT_Any' \
                                 pdfNames='TOPPdf_MuTau','TOPPdfTauUp_MuTau','TOPPdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 normnames='TOPMCNorm_MuTau' \
                                 variable='muTauMass' \
                                 variableNewName='mass' \
                                 weight='__WEIGHT__'

MakeInterpolatedMorphPDF channel='MuTau' prefix='TOPPdf' shifts='Tau'

MakeKeysPDF inputFile='inputs/mutau/VV.root' inputTrees='muTauEventTreeNominal/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut='mumuSize==0&&HLT_Any' \
                                 pdfNames='VVPdf_MuTau','VVPdfTauUp_MuTau','VVPdfTauDown_MuTau'\
                                 normnames='VVMCNorm_MuTau' \
                                 outputFile='diTau.root' \
                                 variable='muTauMass' \
                                 variableNewName='mass' \
                                 weight='__WEIGHT__'

MakeInterpolatedMorphPDF channel='MuTau' prefix='VVPdf' shifts='Tau'



#data driven shapes
MakeKeysPDF inputFile='inputs/mutau/DATA.root' inputTrees='muTauEventTree/eventTree' \
                                 cut='((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==0&&muTauRelPFIso<0.3&muTauisMuon==0&&muTauCharge!=0&&muTauMt1<40.' \
                                 pdfNames='QCDPdf_MuTau' \
                                 outputFile='diTau.root' \
                                 variable='muTauMass' \
                                 variableNewName='mass' 



MakeKeysPDF inputFile='inputs/mutau/DATA.root' inputTrees='muTauEventTree/eventTree' \
                                 cut='((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==1&&muTauRelPFIso<0.1&muTauisMuon==1&&muTauCharge==0&&muTauMt1<40.' \
                                 pdfNames='ZMFTPdf_MuTau' \
                                 outputFile='diTau.root' \
                                 variable='muTauMass' \
                                 variableNewName='mass' 






#create normalization from MC for things that you get shape from data 
MakeNormalization inputFile='inputs/mutau/ZMM.root'  inputTree='muTauEventTreeNominal/eventTree' cut='mumuSize==0&&HLT_Any&&muTauGenPt2>0'   outputFile='diTau.root'  weight='__WEIGHT__'  normname='ZMFTMCNorm_MuTau'
MakeNormalization inputFile='inputs/mutau/QCD.root'  inputTree='muTauEventTreeNominal/eventTree' cut='mumuSize==0&&HLT_Any&&muTauGenPt2>0'   outputFile='diTau.root'  weight='__WEIGHT__'  normname='QCDMCNorm_MuTau'



#Now create the higgs PDFs
for higgsMass in 90 100 120 130 140 160 180 200 250 300 350 400 450 500 
do
echo 'Making PDF for Higgs Mass = '$higgsMass

MakeKeysPDF inputFile='inputs/mutau/bbA'$higgsMass'.root' inputTrees='muTauEventTreeNominal/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut='mumuSize==0&&HLT_Any' \
                                 pdfNames='BBH'$higgsMass'Pdf_MuTau','BBH'$higgsMass'PdfTauUp_MuTau','BBH'$higgsMass'PdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 variable='muTauMass' \
                                 variableNewName='mass' \
                                 rho=2.0 \
                                 weight='__WEIGHT__' \
                                 normnames='BBH'$higgsMass'MCEff_MuTau' 

MakeInterpolatedMorphPDF channel='MuTau' prefix='BBH'$higgsMass'Pdf' shifts='Tau'

MakeKeysPDF inputFile='inputs/mutau/ggH'$higgsMass'.root' inputTrees='muTauEventTreeNominal/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut='mumuSize==0&&HLT_Any' \
                                 pdfNames='GGH'$higgsMass'Pdf_MuTau','GGH'$higgsMass'PdfTauUp_MuTau','GGH'$higgsMass'PdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 variable='muTauMass' \
                                 variableNewName='mass' \
                                 rho=2.0 \
                                 weight='__WEIGHT__' \
                                 normnames='GGH'$higgsMass'MCEff_MuTau' 

MakeInterpolatedMorphPDF channel='MuTau' prefix='GGH'$higgsMass'Pdf' shifts='Tau'

done


#Assume for now that b-tagging shapes are the same 
#create MC normalizations for the samples you need(Z->tautua and Higgs) 
#recall that you need one for B and one for exclusive no Bjet
MakeNormalization inputFile='inputs/mutau/ZTTPOWHEG3.root'  inputTree='muTauEventTreeNominal/eventTree' cut='mumuSize==0&&HLT_Any&&muTauJetsBTag2Pt15>0'   outputFile='diTau.root'  weight='__WEIGHT__'  normname='ZTTBMCNorm_MuTau'
MakeNormalization inputFile='inputs/mutau/ZTTPOWHEG3.root'  inputTree='muTauEventTreeNominal/eventTree' cut='mumuSize==0&&HLT_Any&&muTauJetsBTag2Pt15==0'   outputFile='diTau.root'  weight='__WEIGHT__'  normname='ZTTNOBMCNorm_MuTau'
for higgsMass in 90 100 120 130 140 160 180 200 250 300 350 400 450 500 
do
echo 'Making B-tagging normalizations for  Higgs Mass = '$higgsMass
MakeNormalization inputFile='inputs/mutau/bbA'$higgsMass'.root'  inputTree='muTauEventTreeNominal/eventTree' cut='mumuSize==0&&HLT_Any&&muTauJetsBTag2Pt15>0'   outputFile='diTau.root'  weight='__WEIGHT__'  normname='BBH'$higgsMass'BMCEff_MuTau'
MakeNormalization inputFile='inputs/mutau/bbA'$higgsMass'.root'  inputTree='muTauEventTreeNominal/eventTree' cut='mumuSize==0&&HLT_Any&&muTauJetsBTag2Pt15==0'   outputFile='diTau.root'  weight='__WEIGHT__'  normname='BBH'$higgsMass'NOBMCEff_MuTau'

MakeNormalization inputFile='inputs/mutau/ggH'$higgsMass'.root'  inputTree='muTauEventTreeNominal/eventTree' cut='mumuSize==0&&HLT_Any&&muTauJetsBTag2Pt15>0'   outputFile='diTau.root'  weight='__WEIGHT__'  normname='GGH'$higgsMass'BMCEff_MuTau'
MakeNormalization inputFile='inputs/mutau/ggH'$higgsMass'.root'  inputTree='muTauEventTreeNominal/eventTree' cut='mumuSize==0&&HLT_Any&&muTauJetsBTag2Pt15==0'   outputFile='diTau.root'  weight='__WEIGHT__'  normname='GGH'$higgsMass'NOBMCEff_MuTau'
done


#Now Make Datasets(Since the two samples are exclusive dont create the combined one 
#mu+tau inclusive
#MakeDataSet inputFile='inputs/mutau/DATA.root'  inputTree='muTauEventTreeNominal/eventTree'  cut='mumuSize==0&&HLT_Any'  name='DATA_MuTau'  outputFile='DATA_MuTau.root'  variables='muTauMass'  variableNewNames='mass'   

#mu+tau btag
MakeDataSet inputFile='inputs/mutau/DATA.root'  inputTree='muTauEventTreeNominal/eventTree'  cut='mumuSize==0&&HLT_Any&&muTauJetsBTag2Pt15>0'  name='DATA_MuTau_B'  outputFile='DATA_MuTauB.root'      variables='muTauMass'  variableNewNames='mass' min=0. max=500.  

MakeDataSet inputFile='inputs/mutau/DATA.root'  inputTree='muTauEventTreeNominal/eventTree'  cut='mumuSize==0&&HLT_Any&&muTauJetsBTag2Pt15==0'  name='DATA_MuTau_NOB'  outputFile='DATA_MuTauNOB.root'  variables='muTauMass'  variableNewNames='mass' min=0. max=500.  

#combine them to one 
MakeSimultaneousDataSet inputFiles='DATA_MuTauB.root','DATA_MuTauNOB.root' inputNames='DATA_MuTau_B','DATA_MuTau_NOB' outputFile='DATA_MuTau.root' categories='MuTau_B','MuTau_NOB' name='DATA_MuTau'




#clean up
rm tmp.root
rm DATA_MuTauB.root
rm DATA_MuTauNOB.root
