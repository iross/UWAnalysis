{


  //STANDARD
  //    std::string preselection = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&eleMuPt1>15&&eleMuPt2>15&&eleMuMissHits==0&&abs(eleMuEleDB)<0.02&&(!(abs(eleMuConvDist)<0.02&&abs(eleMuDCotTheta)<0.02))&&((eleMuEleEB&&((eleMuEleECALIso>1.&&(eleMuEleECALIso-1.+eleMuEleHTrackIso)/eleMuPt1<0.1)||(eleMuEleECALIso<1.&&(eleMuEleHTrackIso)/eleMuPt1<0.1)))||(eleMuEleEE&&((eleMuEleECALIso+eleMuEleHTrackIso)/eleMuPt1<0.1)))&&eleMuMuRelStdIso03<0.15&&eleMuMt1<50&&eleMuMt2<50&&eleMuCharge==0";



    std::string preselection = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&eleMuMissHitsWW==0&&abs(eleMuEleDB)<0.02&&eleMuCharge==0";


//MU PF Iso
//   std::string preselection = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&eleMuPt1>15&&eleMuPt2>15&&eleMuMissHits==0&&abs(eleMuEleDB)<0.02&&(!(abs(eleMuConvDist)<0.02&&abs(eleMuDCotTheta)<0.2))&&((eleMuEleEB&&((eleMuEleECALIso>1.&&(eleMuEleECALIso-1.+eleMuEleHTrackIso)/eleMuPt1<0.1)||(eleMuEleECALIso<1.&&(eleMuEleECALIso+eleMuEleHTrackIso)/eleMuPt1<0.1)))||(eleMuEleEE&&((eleMuEleECALIso+eleMuEleHTrackIso)/eleMuPt1<0.1)))&&eleMuMuRelPFIso<0.23&&eleMuMt1<50&&eleMuMt2<50&&eleMuCharge==0";

//ELE PF iso
//   std::string preselection = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&eleMuPt1>15&&eleMuPt2>15&&eleMuMissHits==0&&abs(eleMuEleDB)<0.02&&(!(abs(eleMuConvDist)<0.02&&abs(eleMuDCotTheta)<0.2))&&eleMuElePFRelIso<0.15&&eleMuMuRelPFIso<0.23&&eleMuMt1<50&&eleMuMt2<50&&eleMuCharge==0";



 TCanvas * mass =   plotter->makeStackedPlot("sv_KineMETPtMass",preselection,"36.3",30,0,300,"M(#tau^{+},#tau^{-})","GeV/c^{2}",10,60,55,0.6,0.6,false,0.1,65,"");
mass->SaveAs("mass.png");
mass->SaveAs("mass.pdf");

  TCanvas * mass2 =   plotter->makeStackedPlot("eleMuMass",preselection,"36.3",20,0,200,"visible Mass","GeV/c^{2}",10,70,65,0.6,0.6,false,0.1,75,"");
 mass->SaveAs("massV.png");
 mass->SaveAs("massV.pdf");
















}
