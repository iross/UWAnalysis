{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/SimplePlotter.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  SimplePlotter *plotter = new SimplePlotter();
  plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/TOP.root","t #bar{t}","__WEIGHT__*(charge==0)",0,kRed,1);
  plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/VV.root","Diboson","__WEIGHT__*(charge==0)",0,kGreen-3,1);
  plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/W.root","W","__WEIGHT__*(charge==0&&genTaus<2)",0,kYellow,1);
  plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/DATA.root","QCD","1.85*(charge!=0)/2200.",0,kViolet-5,kViolet+3);
  plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/ZJETS.root","Z #rightarrow #tau #tau","__WEIGHT__*(charge==0)",0,10,kBlack);


    // plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/ggH120.root","#Phi(120,15) #rightarrow #tau #tau","4.91*__WEIGHT__",-1,kBlue,1); 
    // plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/ggH130.root","","1.87*__WEIGHT__",-1,kBlue,1);
  //     plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/bbA120.root","","8.48*__WEIGHT__",-1,kBlue,1,1001); 
    // plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/bbA130.root","","0.53*__WEIGHT__",-1,kBlue,1);

        plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/sm115.root","SM H(115) #rightarrow #tau #tau","1.38*__WEIGHT__*(charge==0)",-1,kBlue,kBlue);
        plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/vbf115.root","","0.107*__WEIGHT__*(charge==0)",-1,kBlue,kBlue);


 plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/DATA.root","DATA","(charge==0)",1,kBlack,0);



}
