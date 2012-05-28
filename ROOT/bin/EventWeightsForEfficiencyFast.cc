#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include <math.h> 
#include "TMath.h" 
#include <limits>




double efficiency(double m, double m0, double sigma, double alpha, double n, double norm)
 { 
   const double sqrtPiOver2 = 1.2533141373;
   const double sqrt2 = 1.4142135624;

   double sig = fabs((double) sigma);
   
   double t = (m - m0)/sig ;
   
   if (alpha < 0)
     t = -t;

   double absAlpha = fabs(alpha / sig);
   double a = TMath::Power(n/absAlpha,n)*exp(-0.5*absAlpha*absAlpha);
   double b = absAlpha - n/absAlpha;

   //   if (a>=std::numeric_limits<double>::max()) return -1. ;

   double ApproxErf ;
   double arg = absAlpha / sqrt2 ;
   if (arg > 5.) ApproxErf = 1 ;
   else if (arg < -5.) ApproxErf = -1 ;
   else ApproxErf = TMath::Erf(arg) ;

   double leftArea = (1 + ApproxErf) * sqrtPiOver2 ;
   double rightArea = ( a * 1/TMath::Power(absAlpha - b,n-1)) / (n - 1);
   double area = leftArea + rightArea;

   if ( t <= absAlpha ){
     arg = t / sqrt2 ;
     if (arg > 5.) ApproxErf = 1 ;
     else if (arg < -5.) ApproxErf = -1 ;
     else ApproxErf = TMath::Erf(arg) ;
     return norm * (1 + ApproxErf) * sqrtPiOver2 / area ;
   }
   else{
     return norm * (leftArea +  a * (1/TMath::Power(t-b,n-1) - 1/TMath::Power(absAlpha - b,n-1)) / (1 - n)) / area ;
   }
  
 }


void readdir(TDirectory *dir,optutl::CommandLineParser parser); 


float weightEMu(float pt1,float pt2) {
  float m0 =14.4751; float sigma = 0.120967; float alpha = 0.0226; float n = 4.3709; float norm=0.874294;


  m0=2.90901; sigma=22.4641;alpha=74.3622;n=3.72143;norm=0.976318;
  float dataMUID = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=1.74118; sigma=22.5399;alpha=52.1416;n=6.59594;norm=0.980176;
  float mcMUID = efficiency(pt2,m0,sigma,alpha,n,norm);
  

  m0=2.67899; sigma=21.9374;alpha=35.4;n=155.359;norm=0.977301;
  float eleid = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=-3.1459; sigma=27.0568;alpha=81.9479;n=2.21511;norm=0.974106;
  float mceleid = efficiency(pt1,m0,sigma,alpha,n,norm);



  return dataMUID*0.997841*eleid/(mcMUID*mceleid);
 

}


float weightMuTau(float pt1,float pt2,float eta1) {

  float m0 =15.06; float sigma = 0.55278; float alpha = 1.34236; float n = 1.003; float norm = 3.36767;
  float muBdata2 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0 =15.03175; sigma = 0.866114; alpha = 1.25009; n = 1.63711; norm = 0.844906;
  float muEdata2 = efficiency(pt1,m0,sigma,alpha,n,norm);

  float muBmc = 0.91677;
  float muBdata1 = 0.901186;

  float muEmc = 0.835749;
  float muEdata1 = 0.862932;


  m0 =16.7854;sigma = -0.69382;alpha = 4.57285;n = 94.1275;norm=0.883126;
  float data1 = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=14.6677; sigma=0.408165;alpha=0.551949;n=1.4477;norm=0.961277;
  float data2 = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=19.1898; sigma=-1.35938;alpha=2.82724;n=1.02721;norm=1.50862;
  float data3 = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=14.5311; sigma=-0.0151916;alpha=0.0022261;n=1.6761;norm=0.891203;
  float mcTau = efficiency(pt2,m0,sigma,alpha,n,norm);


  float weighttau=(0.03655*data1+0.4282*data2+0.5352*data3);


//   m0=0.131943; sigma=3.44931;alpha=0.568297;n=109.249;norm=1.05591;
//   float dataIsoB = efficiency(pt1,m0,sigma,alpha,n,norm);
// 
//   m0=1.6991; sigma=7.71496;alpha=2.73853;n=121.61;norm=1.06467;
//   float mcIsoB = efficiency(pt1,m0,sigma,alpha,n,norm);
//  
//   m0=-0.352197; sigma=4.47776;alpha=1.00561;n=113.944;norm=1.04108;
//   float dataIsoE = efficiency(pt1,m0,sigma,alpha,n,norm);
// 
//   m0=7.23378; sigma=1.70884;alpha=1.3651;n=1.05211;norm=4.33366;
//   float mcIsoE = efficiency(pt1,m0,sigma,alpha,n,norm);

  float dataIdB = 0.958046;
  float mcIdB = 0.968006;
  
  float dataIdE = 0.937338;
  float mcIdE = 0.960542;
  if(pt1 > 17 && pt1 < 20){
	  if(fabs(eta1)<1.4)
		return weighttau*0.678*dataIdB*(0.478*muBdata1+0.522*muBdata2)/(mcTau*0.705*mcIdB*muBmc);
	  else
		return weighttau*0.699*dataIdE*(0.478*muEdata1+0.522*muEdata2)/(mcTau*0.734*mcIdE*muEmc);
  }
  else if(pt1 > 20 && pt1 < 25){
  	  if(fabs(eta1)<1.4)
		return weighttau*0.768*dataIdB*(0.478*muBdata1+0.522*muBdata2)/(mcTau*0.786*mcIdB*muBmc);
	  else
		return weighttau*0.783*dataIdE*(0.478*muEdata1+0.522*muEdata2)/(mcTau*0.810*mcIdE*muEmc);  	  
  }
  else{
      if(fabs(eta1)<1.4)
		return weighttau*dataIdB*(0.478*muBdata1+0.522*muBdata2)/(mcTau*mcIdB*muBmc);
	  else
		return weighttau*dataIdE*(0.478*muEdata1+0.522*muEdata2)/(mcTau*mcIdE*muEmc);  	  
  }
}


float weightMuTauEmbedded(float pt1,float pt2,float eta1) {
  float m0 =15.06; float sigma = 0.55278; float alpha = 1.34236; float n = 1.003; float norm = 3.36767;
  float muBdata2 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0 =15.03175; sigma = 0.866114; alpha = 1.25009; n = 1.63711; norm = 0.844906;
  float muEdata2 = efficiency(pt1,m0,sigma,alpha,n,norm);

  float muBmc = 0.91677;
  float muBdata1 = 0.901186;

  float muEmc = 0.835749;
  float muEdata1 = 0.862932;


  m0 =16.7854;sigma = -0.69382;alpha = 4.57285;n = 94.1275;norm=0.883126;
  float data1 = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=14.6677; sigma=0.408165;alpha=0.551949;n=1.4477;norm=0.961277;
  float data2 = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=19.1898; sigma=-1.35938;alpha=2.82724;n=1.02721;norm=1.50862;
  float data3 = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=14.5311; sigma=-0.0151916;alpha=0.0022261;n=1.6761;norm=0.891203;
  float mcTau = efficiency(pt2,m0,sigma,alpha,n,norm);


  float weighttau=(0.03655*data1+0.4282*data2+0.5352*data3);


//   m0=0.131943; sigma=3.44931;alpha=0.568297;n=109.249;norm=1.05591;
//   float dataIsoB = efficiency(pt1,m0,sigma,alpha,n,norm);
// 
//   m0=1.6991; sigma=7.71496;alpha=2.73853;n=121.61;norm=1.06467;
//   float mcIsoB = efficiency(pt1,m0,sigma,alpha,n,norm);
//  
//   m0=-0.352197; sigma=4.47776;alpha=1.00561;n=113.944;norm=1.04108;
//   float dataIsoE = efficiency(pt1,m0,sigma,alpha,n,norm);
// 
//   m0=7.23378; sigma=1.70884;alpha=1.3651;n=1.05211;norm=4.33366;
//   float mcIsoE = efficiency(pt1,m0,sigma,alpha,n,norm);

  float dataIdB = 0.958046;
  float mcIdB = 0.968006;
  
  float dataIdE = 0.937338;
  float mcIdE = 0.960542;






  if(pt1 > 17 && pt1 < 20){
	  if(fabs(eta1)<1.4)
		return weighttau*0.678*dataIdB*(0.478*muBdata1+0.522*muBdata2)/(0.705*mcIdB);
	  else
		return weighttau*0.699*dataIdE*(0.478*muEdata1+0.522*muEdata2)/(0.734*mcIdE);
  }
  else if(pt1 > 20 && pt1 < 25){
  	  if(fabs(eta1)<1.4)
		return weighttau*0.768*dataIdB*(0.478*muBdata1+0.522*muBdata2)/(0.786*mcIdB);
	  else
		return weighttau*0.783*dataIdE*(0.478*muEdata1+0.522*muEdata2)/(0.810*mcIdE);  	  
  }
  else{
      if(fabs(eta1)<1.4)
		return weighttau*dataIdB*(0.478*muBdata1+0.522*muBdata2)/(mcIdB);
	  else
		return weighttau*dataIdE*(0.478*muEdata1+0.522*muEdata2)/(mcIdE);  	  
  }


}



float weightETauEmbedded(float pt1,float pt2,float eta1) {

  float m0 =14.8772; float sigma = 0.311255; float alpha = 0.221021; float n = 1.87734; float norm=0.986665;
  float dataeleEB15 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=15.6629; sigma=0.759192;alpha=0.47756;n=2.02154;norm=0.998816;
  float dataeleEE15 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=15.1804; sigma=2.43126;alpha=3.85048;n=1.72284;norm=0.998507;
  float mceleEB = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=16.993; sigma=0.0693958;alpha=0.00695096;n=1.9566;norm=1.00632;
  float mceleEE = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=18.3193; sigma=0.443703;alpha=0.385554;n=1.86523;norm=0.986514;
  float dataeleEB18 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=19.6586; sigma=-0.682633;alpha=0.279486;n=2.66423;norm=0.973455;
  float dataeleEE18 = efficiency(pt1,m0,sigma,alpha,n,norm);


  m0=20.554; sigma=0.683776;alpha=0.855573;n=1.45917;norm=1.03957;
  float dataeleEB20 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=23.6386; sigma=-1.60775;alpha=1.72093;n=1.4131;norm=1.13962;
  float dataeleEE20 = efficiency(pt1,m0,sigma,alpha,n,norm);


  m0=19.6319; sigma=-0.986354;alpha=1.94272;n=1.02398;norm=1.91094;
  float datatauLoose = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=19.3535; sigma=0.369967;alpha=0.158178;n=3.31129;norm=0.76279;
  float datatauMedium = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=19.7197; sigma=0.844386;alpha=1.16726;n=1.00747;norm=9.35089;
  float datatauTight = efficiency(pt2,m0,sigma,alpha,n,norm);


  m0=19.451; sigma=-0.0554166;alpha=0.0518694;n=1.24892;norm=0.950397;
  float mctau = efficiency(pt2,m0,sigma,alpha,n,norm);


//   m0=2.67899; sigma=21.9374;alpha=35.4;n=155.359;norm=0.977301;
//   float eleid = efficiency(pt2,m0,sigma,alpha,n,norm);
// 
//   m0=-3.1459; sigma=27.0568;alpha=81.9479;n=2.21511;norm=0.974106;
//   float mceleid = efficiency(pt2,m0,sigma,alpha,n,norm);



  if(fabs(eta1)<1.442)
    return (0.2425*dataeleEB15*datatauLoose+0.1720*dataeleEB15*datatauTight+0.3830*dataeleEB18*datatauMedium+0.2025*dataeleEB20*datatauMedium);
  else
    return (0.2425*dataeleEE15*datatauLoose+0.1720*dataeleEE15*datatauTight+0.3830*dataeleEE18*datatauMedium+0.2025*dataeleEE20*datatauMedium);



}




float weightETau(float pt1,float pt2,float eta1) {

  float m0 =14.8772; float sigma = 0.311255; float alpha = 0.221021; float n = 1.87734; float norm=0.986665;
  float dataeleEB15 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=15.6629; sigma=0.759192;alpha=0.47756;n=2.02154;norm=0.998816;
  float dataeleEE15 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=15.1804; sigma=2.43126;alpha=3.85048;n=1.72284;norm=0.998507;
  float mceleEB = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=16.993; sigma=0.0693958;alpha=0.00695096;n=1.9566;norm=1.00632;
  float mceleEE = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=18.3193; sigma=0.443703;alpha=0.385554;n=1.86523;norm=0.986514;
  float dataeleEB18 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=19.6586; sigma=-0.682633;alpha=0.279486;n=2.66423;norm=0.973455;
  float dataeleEE18 = efficiency(pt1,m0,sigma,alpha,n,norm);


  m0=20.554; sigma=0.683776;alpha=0.855573;n=1.45917;norm=1.03957;
  float dataeleEB20 = efficiency(pt1,m0,sigma,alpha,n,norm);

  m0=23.6386; sigma=-1.60775;alpha=1.72093;n=1.4131;norm=1.13962;
  float dataeleEE20 = efficiency(pt1,m0,sigma,alpha,n,norm);


  m0=19.6319; sigma=-0.986354;alpha=1.94272;n=1.02398;norm=1.91094;
  float datatauLoose = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=19.3535; sigma=0.369967;alpha=0.158178;n=3.31129;norm=0.76279;
  float datatauMedium = efficiency(pt2,m0,sigma,alpha,n,norm);

  m0=19.7197; sigma=0.844386;alpha=1.16726;n=1.00747;norm=9.35089;
  float datatauTight = efficiency(pt2,m0,sigma,alpha,n,norm);


  m0=19.451; sigma=-0.0554166;alpha=0.0518694;n=1.24892;norm=0.950397;
  float mctau = efficiency(pt2,m0,sigma,alpha,n,norm);


//   m0=2.67899; sigma=21.9374;alpha=35.4;n=155.359;norm=0.977301;
//   float eleid = efficiency(pt2,m0,sigma,alpha,n,norm);
// 
//   m0=-3.1459; sigma=27.0568;alpha=81.9479;n=2.21511;norm=0.974106;
//   float mceleid = efficiency(pt2,m0,sigma,alpha,n,norm);



  if(fabs(eta1)<1.442)
    return (0.2425*dataeleEB15*datatauLoose+0.1720*dataeleEB15*datatauTight+0.3830*dataeleEB18*datatauMedium+0.2025*dataeleEB20*datatauMedium)/(mctau*mceleEB);
  else
    return (0.2425*dataeleEE15*datatauLoose+0.1720*dataeleEE15*datatauTight+0.3830*dataeleEE18*datatauMedium+0.2025*dataeleEE20*datatauMedium)/(mctau*mceleEE);



}



int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__HLT__");
   parser.addOption("finalState",optutl::CommandLineParser::kString,"Final state","mutau");
   parser.parseArguments (argc, argv);
   
   TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");
   readdir(f,parser);
   f->Close();

} 


void readdir(TDirectory *dir,optutl::CommandLineParser parser) 
{
  TDirectory *dirsav = gDirectory;
  TIter next(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())) {
    printf("Found key=%s \n",key->GetName());
    TObject *obj = key->ReadObj();

    if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
      dir->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      readdir(subdir,parser);
      dirsav->cd();
    }
    else if(obj->IsA()->InheritsFrom(TTree::Class())) {
      TTree *t = (TTree*)obj;
      float weight = 1.0;
      TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());

      float pt1;
      float eta1;
      float pt2;
      float eta2;


      t->SetBranchAddress("pt1",&pt1);
      t->SetBranchAddress("eta1",&eta1);
      t->SetBranchAddress("pt2",&pt2);
      t->SetBranchAddress("eta2",&eta2);
      
      std::string finalState = parser.stringValue("finalState");

      printf("Found tree -> weighting\n");
      for(Int_t i=0;i<t->GetEntries();++i)
	{
	  t->GetEntry(i);
	  weight=0;
	  if(finalState=="muTau")
	    weight=weightMuTau(pt1,pt2,eta1);
	  else if (finalState=="eleTau")
	    weight=weightETau(pt1,pt2,eta1);
	  else if (finalState=="eleMu")
	    weight=weightEMu(pt1,pt2);
	  else if (finalState=="muTauEmbedded")
	    weight=weightMuTauEmbedded(pt1,pt2,eta1);
	  else if (finalState=="eleTauEmbedded")
	    weight=weightETauEmbedded(pt1,pt2,eta1);

	  newBranch->Fill();
	}

      t->Write("",TObject::kOverwrite);
    }
  }
}
