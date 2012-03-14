{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/SimplePlotter.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  SimplePlotter *plotter = new SimplePlotter();

  plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/QCD.root","QCD","__WEIGHT__",0,kViolet-5,kViolet+3);
  plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/EWK.root"," t#bar{t}/ewk","__WEIGHT__",0,kRed+2,kRed+4);
  plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/W.root","W+jets","__WEIGHT__",0,kOrange+7,kOrange+3);
   plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/ZTTPOWHEG4.root","Z #rightarrow #tau #tau","__WEIGHT__",0,kOrange-2,kBlack);

   //90
   //   plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/ggH90.root","#Phi(90) #rightarrow #tau #tau","90.2/110000",-1,5,1001);
   //   plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA90.root","","87.7/110000",-1,5,1001);
   //   plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH130.root","","1.53/110000",-1,5);
   //   plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA130.root","","0.04/106400",-1,5);

   //100
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH100.root","#Phi(100) #rightarrow #tau #tau","54.5/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA100.root","","64.1/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH130.root","","1.77/110000",-1,5);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA130.root","","0.09/106400",-1,5);
   

 //   // // //120-40
       // plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/ggH120.root","#Phi(120) #rightarrow #tau #tau","21.5*__WEIGHT__",-1,kGreen+2,kGreen+2,1001);
       // plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/bbA120.root","","31.6*__WEIGHT__",-1,kGreen+2,kGreen+2,1001); 
       // plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/ggH130.root","","2.66*__WEIGHT__",-1,kGreen+2,kGreen+2);
       // plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/bbA130.root","","0.93*__WEIGHT__",-1,kGreen+2,kGreen+2);

   // //130
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH130.root","#Phi(130) #rightarrow #tau #tau","16.4/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA130.root","","27.8/110000",-1,5,1001);

   // //140
     // plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/ggH140.root","#Phi(130) #rightarrow #tau #tau","10.17/110000",-1,5,1001);
     // plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/bbA140.root","","19.8/110000",-1,5,1001);
     // plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/ggH130.root","","1.39/110000",-1,5);
     // plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/bbA130.root","","1.39/106400",-1,5);


   // //160
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH160.root","#Phi(160) #rightarrow #tau #tau","5.13/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA160.root","","12.96/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH130.root","","1.24/110000",-1,5);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA130.root","","0.23/106400",-1,5);

   // //180
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH180.root","#Phi(180) #rightarrow #tau #tau","2.73/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA180.root","","8.44/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH130.root","","1.19/110000",-1,5);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA130.root","","0.10/106400",-1,5);

   // //200
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH200.root","#Phi(200) #rightarrow #tau #tau","1.53/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA200.root","","5.65/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH130.root","","1.12/110000",-1,5);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA130.root","","0.06/106400",-1,5);


   // //250
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH250.root","#Phi(250) #rightarrow #tau #tau","0.43/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA250.root","","2.28/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH130.root","","0.98/110000",-1,5);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA130.root","","0.03/106400",-1,5);

   // //300
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH300.root","#Phi(300) #rightarrow #tau #tau","0.14/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA300.root","","1.01/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH130.root","","0.90/110000",-1,5);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA130.root","","0.02/106400",-1,5);

   // //350
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH350.root","#Phi(350) #rightarrow #tau #tau","0.05/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA350.root","","0.46/110000",-1,5,1001);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/ggH130.root","","0.85/110000",-1,5);
    // plotter->addFile("muTauEventTree/eventTreeNominal","sandbox/ztt-latest/bbA130.root","","0.01/106400",-1,5);

   plotter->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/DATA.root","DATA","1",1,kBlack,0);

   ////PLOTTERS FOR BACKGROUND ENRICHED REGIONS!


  SimplePlotter *plotterZENR = new SimplePlotter();

  plotterZENR->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/NO_Z.root"," Others","__WEIGHT__",0,kViolet-5,kViolet+2);
  plotterZENR->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/ZMM.root","Z+jets","1.08*__WEIGHT__",0,kOrange+7,kOrange+3);
  plotterZENR->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/DATA.root","DATA","1",1,kBlack,0);

  SimplePlotter *plotterWENR = new SimplePlotter();

  plotterWENR->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/NO_W.root"," Others","__WEIGHT__",0,kViolet-5,kViolet+2);
  plotterWENR->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/WMN.root","W+jets","__WEIGHT__",0,kOrange+7,kOrange+3);
  plotterWENR->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/DATA.root","DATA","1",1,kBlack,0);


  SimplePlotter *plotterTOPENR = new SimplePlotter();

  plotterTOPENR->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/NO_TOP.root"," Others","__WEIGHT__",0,24,24);
  plotterTOPENR->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/TOP.root","t#bar{t}","__WEIGHT__",0,30,30);
  plotterTOPENR->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/DATA.root","DATA","1",1,kBlack,0);


  SimplePlotter *plotterMC = new SimplePlotter();

  plotterMC->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/ZTTPOWHEG3.root"," POWHEG-Z2","__WEIGHT__",0,kRed,kRed);
  plotterMC->addFile("muTauEventTree/eventTree","sandbox/ztt-latest/ZTT.root","PYTHIA-D6T","__WEIGHT__",0,kBlack,0);

















}
