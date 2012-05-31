{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/SimplePlotter.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  SimplePlotter *plotter = new SimplePlotter();

     plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/VV.root"," Diboson","__WEIGHT__*(charge==0)",0,kRed+2,kRed+4);
     plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/TOP.root"," TTbar","__WEIGHT__*(charge==0)",0,kRed+1,kRed+8);
     plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/W.root","W+jets","__WEIGHT__*((charge==0)-(charge!=0))",0,kRed-2,kRed+4);
     //      plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/DATA.root","QCD","(HLT_Any&&charge!=0)/2095.",0,kViolet-5,kViolet+3);
      plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/ZJETS.root","Z+jets","__WEIGHT__*(genTaus==0)*((charge==0)-(charge!=0))",0,kOrange+7,1);
     plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/ZJETS.root","Z#rightarrow #tau #tau","__WEIGHT__*(genTaus==2&&charge==0)",0,10,1);


  // plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/DATA.root","SS Data","(charge!=0)/223.",0,kViolet-5,kViolet+3);
  // plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/TOP.root","ttbar","0.899*__WEIGHT__*(charge==0)",0,kRed,kRed);
  // plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/VV.root","diboson","0.899*__WEIGHT__*(charge==0)",0,kYellow,kYellow);
  // plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/W.root","W+jets","0.899*__WEIGHT__*(charge==0)",0,kMagenta+7,kMagenta);
  // plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/ZEE.root",
     //" Z+jets","0.899*__WEIGHT__*(genPt2>0)",0,kRed+2,kRed+4);
  // plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/ZTT.root","Z #rightarrow #tau #tau","0.899*__WEIGHT__*(charge==0)",0,kOrange-2,kBlack);


   //90
   //   plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/ggH90.root","#Phi(90) #rightarrow #tau #tau","90.2/110000",-1,5,1001);
   //   plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA90.root","","87.7/110000",-1,5,1001);
   //   plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","","1.53/110000",-1,5);
   //   plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","0.04/106400",-1,5);

   //100
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH100.root","#Phi(100) #rightarrow #tau #tau","54.5/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA100.root","","64.1/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","","1.77/110000",-1,5);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","0.09/106400",-1,5);
   

   // // // //120-40
       //  plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/ggH120.root","#Phi(120) #rightarrow #tau #tau","39.73*__WEIGHT__",-1,kGreen+2,kGreen+2,1001); 
       // plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/bbA120.root","","64.93*__WEIGHT__",-1,kGreen+2,kGreen+2,1001); 
       // plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/ggH130.root","","2.91*__WEIGHT__",-1,kGreen+2,kGreen+2);
       // plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/bbA130.root","","1.04*__WEIGHT__",-1,kGreen+2,kGreen+2);


   // // // //120
               // plotterOS->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/ggH120.root","#Phi(120,15) #rightarrow #tau #tau","0.9935*0.906*4.91*(charge==0)*__WEIGHT__",-1,kBlue,1,1001); 
               // plotterOS->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/bbA120.root","","0.9935*0.906*8.48*__WEIGHT__*(charge==0)",-1,kBlue,1,1001); 
               // plotterOS->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/ggH130.root","","0.9935*0.906*1.87*__WEIGHT__*(charge==0)",-1,kBlue,1);
               // plotterOS->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/bbA130.root","","0.9935*0.906*0.53*__WEIGHT__*(charge==0)",-1,kBlue,1);



   // //130
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","#Phi(130) #rightarrow #tau #tau","16.4/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","27.8/110000",-1,5,1001);

   // //140
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH140.root","#Phi(130) #rightarrow #tau #tau","10.17/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA140.root","","19.8/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","","1.39/110000",-1,5);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","1.39/106400",-1,5);


   // //160
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH160.root","#Phi(160) #rightarrow #tau #tau","5.13/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA160.root","","12.96/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","","1.24/110000",-1,5);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","0.23/106400",-1,5);

   // //180
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH180.root","#Phi(180) #rightarrow #tau #tau","2.73/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA180.root","","8.44/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","","1.19/110000",-1,5);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","0.10/106400",-1,5);

   // //200
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH200.root","#Phi(200) #rightarrow #tau #tau","1.53/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA200.root","","5.65/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","","1.12/110000",-1,5);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","0.06/106400",-1,5);


   // //250
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH250.root","#Phi(250) #rightarrow #tau #tau","0.43/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA250.root","","2.28/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","","0.98/110000",-1,5);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","0.03/106400",-1,5);

   // //300
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH300.root","#Phi(300) #rightarrow #tau #tau","0.14/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA300.root","","1.01/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","","0.90/110000",-1,5);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","0.02/106400",-1,5);

   // //350
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH350.root","#Phi(350) #rightarrow #tau #tau","0.05/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA350.root","","0.46/110000",-1,5,1001);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/ggH130.root","","0.85/110000",-1,5);
    // plotter->addFile("eleTauEventTree/eventTreeNominal","sandbox/zet-latest/bbA130.root","","0.01/106400",-1,5);

  // plotterOS->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/DATA.root","DATA","(RUN<=163890)",1,kBlack,1);

  plotter->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/DATA.root","DATA","(charge==0)",1,kBlack,1);


  SimplePlotter *plotterH = new SimplePlotter();
  plotterH->addFile("eleTauEventTree/eventTree","sandbox/et-may26/DATA11.root","41X","1",-1,kBlue,1);
  plotterH->addFile("eleTauEventTree/eventTree","sandbox/zet-latest/D1.root","42X","1",-1,kRed,1);

  














}
