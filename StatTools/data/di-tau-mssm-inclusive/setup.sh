#!/bin/bash

PDFEXEC=MakeKeysPDF
DSEXEC=MakeDataSet
SDSEXEC=MakeSimultaneousDataSet
BINNING="min=0.0 max=600."
DBINNING="min=0.0 max=600."

if [ "$1" = "binned" ]; then 
PDFEXEC=MakeTHKeysPDF
DSEXEC=MakeDataHist
SDSEXEC=MakeSimultaneousDataHist
BINNING="min=0.0 max=600."
DBINNING="min=0.0 max=600."

fi 

if [ "$1" = "histogram" ]; then 
PDFEXEC=MakeHistPDF
DSEXEC=MakeDataSet
SDSEXEC=MakeSimultaneousDataSet
#BINNING="binning=0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,180,200,250,300,400,500,1000 bins=23 min=0.0 max=500."
BINNING="bins=30 min=0.0 max=600."
DBINNING="min=0.0 max=600."
fi 



CreateWorkspace outputFile='diTau.root' 


muTauCut='HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&abs(dz)<0.2'
muTauCutZJFT='HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&abs(dz)<0.2&&genPt2==0'
muTauCutZMFT='HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&abs(dz)<0.2&&genPt2>0'
muTauCutQCD='(HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.3&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&charge!=0&&abs(dz)<0.2)'



eleTauCut='HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&tauElectronVeto&&abs(eta1)<2.1'
eleTauCutZJFT='HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&tauElectronVeto&&abs(eta1)<2.1&&genPt2==0'
eleTauCutZEFT='HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&tauElectronVeto&&abs(eta1)<2.1&&genPt2>0'
eleTauCutQCD='HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.3&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&charge!=0&&tauElectronVeto&&abs(eta1)<2.1'

eleMuCut='HLT_Any&&vertices>0&&l1RelPfIsoDeltaBeta<0.25&&l2RelPFIsoDeltaBeta<0.2&&pZeta>-20&&charge==0&&pt1>15&&pt2>10&&abs(l1DB)<0.02&&abs(l2DXY)<0.02&&diLeptons1==0&&diLeptons2==0&&dz<0.2'
eleMuCutQCD='HLT_Any&&vertices>0&&l1RelPfIsoDeltaBeta<0.25&&l2RelPFIsoDeltaBeta<0.2&&pZeta>-20&&charge!=0&&pt1>15&&pt2>10&&abs(l1DB)<0.02&&abs(l2DXY)<0.02&&diLeptons1==0&&diLeptons2==0&&dz<0.2'


variable='mass'
newVariable='mass'



########################################################E+MU###################################################################


#Z to tau tau 
$PDFEXEC inputFile='../inputs/emu/ZTT.root'  inputTrees='eleMuEventTree/eventTree','eleMuEventTreeEleUp/eventTree','eleMuEventTreeEleDown/eventTree'   cut=$eleMuCut     pdfNames='ZTTPdf_EMu','ZTTPdfEleUp_EMu','ZTTPdfEleDown_EMu'          outputFile='diTau.root'         variableNewName=$newVariable          variable=$variable                        weight='__WEIGHT__' $BINNING

MakeInterpolatedMorphPDF channel='EMu' prefix='ZTTPdf' shifts='Ele' 
		
#VJETS
$PDFEXEC inputFile='../inputs/emu/VJETS.root' inputTrees='eleMuEventTree/eventTree','eleMuEventTreeEleUp/eventTree','eleMuEventTreeEleDown/eventTree'    cut=$eleMuCut    pdfNames='VJETSPdf_EMu','VJETSPdfEleUp_EMu','VJETSPdfEleDown_EMu'   outputFile='diTau.root'    variable=$variable    variableNewName=$newVariable    weight='__WEIGHT__'  $BINNING

MakeInterpolatedMorphPDF channel='EMu' prefix='VJETSPdf' shifts='Ele' 


#TTbar
$PDFEXEC inputFile='../inputs/emu/TOP.root' inputTrees='eleMuEventTree/eventTree','eleMuEventTreeEleUp/eventTree','eleMuEventTreeEleDown/eventTree' \
                                 cut=$eleMuCut \
                                 pdfNames='TOPPdf_EMu','TOPPdfEleUp_EMu','TOPPdfEleDown_EMu' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__' $BINNING

MakeInterpolatedMorphPDF channel='EMu' prefix='TOPPdf' shifts='Ele'


#Diboson
$PDFEXEC inputFile='../inputs/emu/VV.root' inputTrees='eleMuEventTree/eventTree','eleMuEventTreeEleUp/eventTree','eleMuEventTreeEleDown/eventTree' \
                                 cut=$eleMuCut \
                                 pdfNames='VVPdf_EMu','VVPdfEleUp_EMu','VVPdfEleDown_EMu'\
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__' $BINNING

MakeInterpolatedMorphPDF channel='EMu' prefix='VVPdf' shifts='Ele'


#data driven shape for QCD
$PDFEXEC inputFile='../inputs/emu/DATA.root' inputTrees='eleMuEventTree/eventTree' \
                                 cut=$eleMuCutQCD \
                                 pdfNames='QCDPdf_EMu' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable $BINNING 

#create normalization from MC for things that you get shape from data 
MakeNormalization inputFile='../inputs/emu/ZTT.root'  inputTree='eleMuEventTree/eventTree' cut=$eleMuCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='ZTTMCNorm_EMu'
MakeNormalization inputFile='../inputs/emu/TOP.root'  inputTree='eleMuEventTree/eventTree' cut=$eleMuCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='TOPMCNorm_EMu'
MakeNormalization inputFile='../inputs/emu/VV.root'  inputTree='eleMuEventTree/eventTree' cut=$eleMuCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='VVMCNorm_EMu'
MakeNormalization inputFile='../inputs/emu/VJETS.root'  inputTree='eleMuEventTree/eventTree' cut=$eleMuCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='VJETSMCNorm_EMu'

#Now create the MSSM Higgs PDFs
for higgsMass in 90 100 120 130 140 160 180 200 250 300 350 400 450 500 
do
echo 'Making PDF for Higgs Mass = '$higgsMass

$PDFEXEC inputFile='../inputs/emu/bbA'$higgsMass'.root' inputTrees='eleMuEventTree/eventTree','eleMuEventTreeEleUp/eventTree','eleMuEventTreeEleDown/eventTree' \
                                 cut=$eleMuCut \
                                 pdfNames='BBH'$higgsMass'Pdf_EMu','BBH'$higgsMass'PdfEleUp_EMu','BBH'$higgsMass'PdfEleDown_EMu' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__' $BINNING


MakeNormalization inputFile='../inputs/emu/bbA'$higgsMass'.root'  inputTree='eleMuEventTree/eventTree' cut=$eleMuCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='BBH'$higgsMass'MCEff_EMu' 
MakeInterpolatedMorphPDF channel='EMu' prefix='BBH'$higgsMass'Pdf' shifts='Ele'

$PDFEXEC inputFile='../inputs/emu/ggH'$higgsMass'.root' inputTrees='eleMuEventTree/eventTree','eleMuEventTreeEleUp/eventTree','eleMuEventTreeEleDown/eventTree' \
                                 cut=$eleMuCut \
                                 pdfNames='GGH'$higgsMass'Pdf_EMu','GGH'$higgsMass'PdfEleUp_EMu','GGH'$higgsMass'PdfEleDown_EMu' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__' $BINNING

MakeNormalization inputFile='../inputs/emu/ggH'$higgsMass'.root'  inputTree='eleMuEventTree/eventTree' cut=$eleMuCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='GGH'$higgsMass'MCEff_EMu' 
MakeInterpolatedMorphPDF channel='EMu' prefix='GGH'$higgsMass'Pdf' shifts='Ele'

done


#Now create the MSM Higgs PDFs
for higgsMass in 100 105 110 115 120 130
do
echo 'Making PDF for Higgs Mass = '$higgsMass

$PDFEXEC inputFile='../inputs/emu/sm'$higgsMass'.root' inputTrees='eleMuEventTree/eventTree','eleMuEventTreeEleUp/eventTree','eleMuEventTreeEleDown/eventTree' \
                                 cut=$eleMuCut \
                                 pdfNames='SM'$higgsMass'Pdf_EMu','SM'$higgsMass'PdfEleUp_EMu','SM'$higgsMass'PdfEleDown_EMu' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__' $BINNING

MakeNormalization inputFile='../inputs/emu/sm'$higgsMass'.root'  inputTree='eleMuEventTree/eventTree' cut=$eleMuCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='SM'$higgsMass'MCEff_EMu' 
MakeInterpolatedMorphPDF channel='EMu' prefix='SM'$higgsMass'Pdf' shifts='Ele'
done



########################################################MU+TAU###################################################################



#Z to tau tau 
$PDFEXEC inputFile='../inputs/mutau/ZTT.root'  inputTrees='muTauEventTree/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree'   cut=$muTauCut     pdfNames='ZTTPdf_MuTau','ZTTPdfTauUp_MuTau','ZTTPdfTauDown_MuTau'          outputFile='diTau.root'         variableNewName=$newVariable          variable=$variable                        weight='__WEIGHT__' $BINNING
MakeInterpolatedMorphPDF channel='MuTau' prefix='ZTTPdf' shifts='Tau' 
		
#W+jets 
$PDFEXEC inputFile='../inputs/mutau/W.root' inputTrees='muTauEventTree/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree'    cut=$muTauCut    pdfNames='WPdf_MuTau','WPdfTauUp_MuTau','WPdfTauDown_MuTau'   outputFile='diTau.root'    variable=$variable    variableNewName=$newVariable    weight='__WEIGHT__' $BINNING 
MakeInterpolatedMorphPDF channel='MuTau' prefix='WPdf' shifts='Tau' 




#Z +jets (jet fakes tau)
$PDFEXEC inputFile='../inputs/mutau/ZMM.root' inputTrees='muTauEventTree/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut=$muTauCutZJFT \
                                 pdfNames='ZJFTPdf_MuTau','ZJFTPdfTauUp_MuTau','ZJFTPdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable  $BINNING

MakeInterpolatedMorphPDF channel='MuTau' prefix='ZJFTPdf' shifts='Tau'


#Z+jets (muon fakes tau)
$PDFEXEC inputFile='../inputs/mutau/ZMM.root' inputTrees='muTauEventTree/eventTree' \
                                 cut=$muTauCutZMFT \
                                 pdfNames='ZMFTPdf_MuTau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable  $BINNING
#TTbar
$PDFEXEC inputFile='../inputs/mutau/TOP.root' inputTrees='muTauEventTree/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut=$muTauCut \
                                 pdfNames='TOPPdf_MuTau','TOPPdfTauUp_MuTau','TOPPdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__'      $BINNING
MakeInterpolatedMorphPDF channel='MuTau' prefix='TOPPdf' shifts='Tau'


#Diboson
$PDFEXEC inputFile='../inputs/mutau/VV.root' inputTrees='muTauEventTree/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut=$muTauCut \
                                 pdfNames='VVPdf_MuTau','VVPdfTauUp_MuTau','VVPdfTauDown_MuTau'\
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__'   $BINNING

MakeInterpolatedMorphPDF channel='MuTau' prefix='VVPdf' shifts='Tau'



#data driven shape for QCD
$PDFEXEC inputFile='../inputs/mutau/DATA.root' inputTrees='muTauEventTree/eventTree' \
                                 cut=$muTauCutQCD \
                                 pdfNames='QCDPdf_MuTau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable  $BINNING

#create normalization from MC for things that you get shape from data 
MakeNormalization inputFile='../inputs/mutau/ZTT.root'  inputTree='muTauEventTree/eventTree' cut=$muTauCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='ZTTMCNorm_MuTau'


#Now create the MSSM Higgs PDFs
for higgsMass in 90 100 120 130 140 160 180 200 250 300 350 400 450 500 
do
echo 'Making PDF for Higgs Mass = '$higgsMass

$PDFEXEC inputFile='../inputs/mutau/bbA'$higgsMass'.root' inputTrees='muTauEventTree/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut=$muTauCut \
                                 pdfNames='BBH'$higgsMass'Pdf_MuTau','BBH'$higgsMass'PdfTauUp_MuTau','BBH'$higgsMass'PdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__'        $BINNING

MakeNormalization inputFile='../inputs/mutau/bbA'$higgsMass'.root'  inputTree='muTauEventTree/eventTree' cut=$muTauCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='BBH'$higgsMass'MCEff_MuTau' 
MakeInterpolatedMorphPDF channel='MuTau' prefix='BBH'$higgsMass'Pdf' shifts='Tau'

$PDFEXEC inputFile='../inputs/mutau/ggH'$higgsMass'.root' inputTrees='muTauEventTree/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut=$muTauCut \
                                 pdfNames='GGH'$higgsMass'Pdf_MuTau','GGH'$higgsMass'PdfTauUp_MuTau','GGH'$higgsMass'PdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__'      $BINNING

MakeNormalization inputFile='../inputs/mutau/ggH'$higgsMass'.root'  inputTree='muTauEventTree/eventTree' cut=$muTauCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='GGH'$higgsMass'MCEff_MuTau' 
MakeInterpolatedMorphPDF channel='MuTau' prefix='GGH'$higgsMass'Pdf' shifts='Tau'

done


#Now create the MSM Higgs PDFs
for higgsMass in 100 105 110 115 120 130
do
echo 'Making PDF for Higgs Mass = '$higgsMass

$PDFEXEC inputFile='../inputs/mutau/sm'$higgsMass'.root' inputTrees='muTauEventTree/eventTree','muTauEventTreeTauUp/eventTree','muTauEventTreeTauDown/eventTree' \
                                 cut=$muTauCut \
                                 pdfNames='SM'$higgsMass'Pdf_MuTau','SM'$higgsMass'PdfTauUp_MuTau','SM'$higgsMass'PdfTauDown_MuTau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__' $BINNING
MakeNormalization inputFile='../inputs/mutau/sm'$higgsMass'.root'  inputTree='muTauEventTree/eventTree' cut=$muTauCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='SM'$higgsMass'MCEff_MuTau' 
MakeInterpolatedMorphPDF channel='MuTau' prefix='SM'$higgsMass'Pdf' shifts='Tau'
done





########################################################E+TAU###################################################################

#Z to tau tau 
$PDFEXEC inputFile='../inputs/etau/ZTT.root'  inputTrees='eleTauEventTree/eventTree','eleTauEventTreeTauUp/eventTree','eleTauEventTreeTauDown/eventTree','eleTauEventTreeEleUp/eventTree','eleTauEventTreeEleDown/eventTree'   cut=$eleTauCut     pdfNames='ZTTPdf_ETau','ZTTPdfTauUp_ETau','ZTTPdfTauDown_ETau','ZTTPdfEleUp_ETau','ZTTPdfEleDown_ETau'          outputFile='diTau.root'         variableNewName=$newVariable          variable=$variable                        weight='__WEIGHT__' $BINNING

MakeInterpolatedMorphPDF channel='ETau' prefix='ZTTPdf' shifts='Tau','Ele'
		
#W+jets 
$PDFEXEC inputFile='../inputs/etau/W.root' inputTrees='eleTauEventTree/eventTree','eleTauEventTreeTauUp/eventTree','eleTauEventTreeTauDown/eventTree','eleTauEventTreeEleUp/eventTree','eleTauEventTreeEleDown/eventTree'    cut=$eleTauCut    pdfNames='WPdf_ETau','WPdfTauUp_ETau','WPdfTauDown_ETau','WPdfEleUp_ETau','WPdfEleDown_ETau'   outputFile='diTau.root'    variable=$variable    variableNewName=$newVariable    weight='__WEIGHT__'  $BINNING

MakeInterpolatedMorphPDF channel='ETau' prefix='WPdf' shifts='Tau','Ele'


#Z +jets (jet fakes tau)
$PDFEXEC inputFile='../inputs/etau/ZEE.root' inputTrees='eleTauEventTree/eventTree','eleTauEventTreeTauUp/eventTree','eleTauEventTreeTauDown/eventTree','eleTauEventTreeEleUp/eventTree','eleTauEventTreeEleDown/eventTree' \
                                 cut=$eleTauCutZJFT \
                                 pdfNames='ZJFTPdf_ETau','ZJFTPdfTauUp_ETau','ZJFTPdfTauDown_ETau','ZJFTPdfEleUp_ETau','ZJFTPdfEleDown_ETau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable                                 $BINNING

MakeInterpolatedMorphPDF channel='ETau' prefix='ZJFTPdf' shifts='Tau','Ele'


#Z+jets (muon fakes tau)
$PDFEXEC inputFile='../inputs/etau/ZEE.root' inputTrees='eleTauEventTree/eventTree','eleTauEventTreeTauUp/eventTree','eleTauEventTreeTauDown/eventTree','eleTauEventTreeEleUp/eventTree','eleTauEventTreeEleDown/eventTree' \
                                 cut=$eleTauCutZEFT \
                                 pdfNames='ZEFTPdf_ETau','ZEFTPdfTauUp_ETau','ZEFTPdfTauDown_ETau','ZEFTPdfEleUp_ETau','ZEFTPdfEleDown_ETau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable         $BINNING
MakeInterpolatedMorphPDF channel='ETau' prefix='ZEFTPdf' shifts='Tau','Ele'

#TTbar
$PDFEXEC inputFile='../inputs/etau/TOP.root' inputTrees='eleTauEventTree/eventTree','eleTauEventTreeTauUp/eventTree','eleTauEventTreeTauDown/eventTree','eleTauEventTreeEleUp/eventTree','eleTauEventTreeEleDown/eventTree' \
                                 cut=$eleTauCut \
                                 pdfNames='TOPPdf_ETau','TOPPdfTauUp_ETau','TOPPdfTauDown_ETau','TOPPdfEleUp_ETau','TOPPdfEleDown_ETau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__'      $BINNING
MakeInterpolatedMorphPDF channel='ETau' prefix='TOPPdf' shifts='Tau','Ele'

#Diboson
$PDFEXEC inputFile='../inputs/etau/VV.root' inputTrees='eleTauEventTree/eventTree','eleTauEventTreeTauUp/eventTree','eleTauEventTreeTauDown/eventTree','eleTauEventTreeEleUp/eventTree','eleTauEventTreeEleDown/eventTree' \
                                 cut=$eleTauCut \
                                 pdfNames='VVPdf_ETau','VVPdfTauUp_ETau','VVPdfTauDown_ETau','VVPdfEleUp_ETau','VVPdfEleDown_ETau'\
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__'   $BINNING 
MakeInterpolatedMorphPDF channel='ETau' prefix='VVPdf' shifts='Tau','Ele'



#data driven shape for QCD
$PDFEXEC inputFile='../inputs/etau/DATA.root' inputTrees='eleTauEventTree/eventTree' \
                                 cut=$eleTauCutQCD \
                                 pdfNames='QCDPdf_ETau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable    $BINNING 

#create normalization from MC for things that you get shape from data 
MakeNormalization inputFile='../inputs/etau/ZTT.root'  inputTree='eleTauEventTree/eventTree' cut=$eleTauCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='ZTTMCNorm_ETau'


#Now create the MSSM Higgs PDFs
for higgsMass in 90 100 120 130 140 160 180 200 250 300 350 400 450 500 
do
echo 'Making PDF for Higgs Mass = '$higgsMass

$PDFEXEC inputFile='../inputs/etau/bbA'$higgsMass'.root' inputTrees='eleTauEventTree/eventTree','eleTauEventTreeTauUp/eventTree','eleTauEventTreeTauDown/eventTree','eleTauEventTreeEleUp/eventTree','eleTauEventTreeEleDown/eventTree' \
                                 cut=$eleTauCut \
                                 pdfNames='BBH'$higgsMass'Pdf_ETau','BBH'$higgsMass'PdfTauUp_ETau','BBH'$higgsMass'PdfTauDown_ETau','BBH'$higgsMass'PdfEleUp_ETau','BBH'$higgsMass'PdfEleDown_ETau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__' $BINNING

MakeNormalization inputFile='../inputs/etau/bbA'$higgsMass'.root'  inputTree='eleTauEventTree/eventTree' cut=$eleTauCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='BBH'$higgsMass'MCEff_ETau' 
MakeInterpolatedMorphPDF channel='ETau' prefix='BBH'$higgsMass'Pdf' shifts='Tau','Ele'

$PDFEXEC inputFile='../inputs/etau/ggH'$higgsMass'.root' inputTrees='eleTauEventTree/eventTree','eleTauEventTreeTauUp/eventTree','eleTauEventTreeTauDown/eventTree','eleTauEventTreeEleUp/eventTree','eleTauEventTreeEleDown/eventTree' \
                                 cut=$eleTauCut \
                                 pdfNames='GGH'$higgsMass'Pdf_ETau','GGH'$higgsMass'PdfTauUp_ETau','GGH'$higgsMass'PdfTauDown_ETau','GGH'$higgsMass'PdfEleUp_ETau','GGH'$higgsMass'PdfEleDown_ETau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__' $BINNING

MakeNormalization inputFile='../inputs/etau/ggH'$higgsMass'.root'  inputTree='eleTauEventTree/eventTree' cut=$eleTauCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='GGH'$higgsMass'MCEff_ETau' 
MakeInterpolatedMorphPDF channel='ETau' prefix='GGH'$higgsMass'Pdf' shifts='Tau','Ele'

done


#Now create the MSM Higgs PDFs
for higgsMass in 100 105 110 115 120 130
do
echo 'Making PDF for Higgs Mass = '$higgsMass

$PDFEXEC inputFile='../inputs/etau/sm'$higgsMass'.root' inputTrees='eleTauEventTree/eventTree','eleTauEventTreeTauUp/eventTree','eleTauEventTreeTauDown/eventTree','eleTauEventTreeEleUp/eventTree','eleTauEventTreeEleDown/eventTree' \
                                 cut=$eleTauCut \
                                 pdfNames='SM'$higgsMass'Pdf_ETau','SM'$higgsMass'PdfTauUp_ETau','SM'$higgsMass'PdfTauDown_ETau','SM'$higgsMass'PdfEleUp_ETau','SM'$higgsMass'PdfEleDown_ETau' \
                                 outputFile='diTau.root' \
                                 variable=$variable \
                                 variableNewName=$newVariable \
                                 weight='__WEIGHT__' $BINNING

MakeNormalization inputFile='../inputs/etau/sm'$higgsMass'.root'  inputTree='eleTauEventTree/eventTree' cut=$eleTauCut   outputFile='diTau.root'  weight='__WEIGHT__'  normname='SM'$higgsMass'MCEff_ETau' 
MakeInterpolatedMorphPDF channel='ETau' prefix='SM'$higgsMass'Pdf' shifts='Tau','Ele'
done






MakeDataSet inputFile='../inputs/mutau/DATA.root'  inputTree='muTauEventTree/eventTree'  cut=$muTauCut  name='DATA_MuTau'  outputFile='diTau.root'      variables='mass'  variableNewNames='mass'  $DBINNING 

MakeDataSet inputFile='../inputs/emu/DATA.root'  inputTree='eleMuEventTree/eventTree'  cut=$eleMuCut  name='DATA_EMu'  outputFile='diTau.root'      variables='mass'  variableNewNames='mass'   $DBINNING

MakeDataSet inputFile='../inputs/etau/DATA.root'  inputTree='eleTauEventTree/eventTree'  cut=$eleTauCut  name='DATA_ETau'  outputFile='diTau.root'      variables='mass'  variableNewNames='mass'  $DBINNING

MakeSimultaneousDataSet  name='data_obs' outputfile='diTau.root' categories='MuTau','ETau','EMu' inputnames='DATA_MuTau','DATA_ETau','DATA_EMu'








#clean up
rm tmp.root

