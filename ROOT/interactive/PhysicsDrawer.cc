#include "PhysicsDrawer.h"
#include <math.h>
PhysicsDrawer::PhysicsDrawer()
{}

PhysicsDrawer::~PhysicsDrawer()
{}

void 
PhysicsDrawer::addPlotter(NtuplePlotter* w,
			std::string preCut,
			std::string label,
			Color_t color,
			  int signal,
			  std::string opt)
{
  wrappers.push_back(w);
  preCuts.push_back(preCut);
  labels.push_back(label);
  colors.push_back(color);
  types.push_back(signal);
  opts.push_back(opt);
}


TCanvas* 
PhysicsDrawer::draw(const std::string& expression,
		    const std::string& cut,
		    int bins,
		    double min,
		    double max,
		    char* xlabel,
		    char *ylabel)

{


  TCanvas *canv = new TCanvas(expression.c_str(),expression.c_str());
  canv->cd();
  std::vector<TH1F*> histos;
  
  double maxB=0;


  for(unsigned int i=0;i<wrappers.size();++i)
    {
      std::string c;
      if(cut.size()==0)
	c=preCuts[i];
      else
	c=preCuts[i]+"*("+cut+")";
      
      std::string opt = opts[i];
      if(i!=0)
	opt=opt+",SAME";

      TH1F *tmpHist = wrappers[i]->draw(expression,c,1,bins,min,max,opt,colors[i],xlabel,ylabel,"CMS Preliminary");
      double max_tmp = tmpHist->GetMaximum();
      if(max_tmp>maxB) maxB = max_tmp;
      printf("%s : %f\n",labels[i].c_str(),tmpHist->Integral());
      histos.push_back(tmpHist);
    }

  
  TLegend *l = new TLegend(0.6,0.6,0.9,0.9);
  l->SetFillColor(kWhite);
  for(unsigned int j=0;j<histos.size();++j)
    {
      std::string opt;
      if(j==0)
	opt="HIST";

      else
	opt="HIST,SAME";
      histos[j]->GetYaxis()->SetRangeUser(0,maxB);
      histos[j]->SetLineWidth(2);
      histos[j]->SetLineColor(colors[j]);
      histos[j]->SetFillStyle(0);
      histos[j]->Draw(opt.c_str());
      l->AddEntry(histos[j],labels[j].c_str(),"lp");
    }
  l->Draw();


 
  return canv;
}


// TCanvas* 
// PhysicsDrawer::drawStacked(const std::string& expression,
// 			   const std::string& cut,
// 			   int bins,
// 			   double min,
// 			   double max,
// 			   char* xlabel,
// 			   char *ylabel)

// {
//   TCanvas *canv = new TCanvas(("stacked"+expression).c_str(),expression.c_str());

//   canv->cd();
//   std::vector<TH1F*> histos;
//   for(unsigned int i=0;i<wrappers.size();++i)
//     {
//       std::string c;
//       if(cut.size()==0)
// 	c=preCuts[i];
//       else
// 	c=preCuts[i]+"*("+cut+")";
      
	
// 	  histos.push_back(wrappers[i]->draw(expression,c,1,bins,min,max,"HIST",colors[i],xlabel,ylabel,"CMS Preliminary"));
//     }

//   TLegend *l = new TLegend(0.6,0.6,0.9,0.9);
//   l->SetFillColor(kWhite);

//   //  TH1F* refHisto = histos[0];
//   for(unsigned int i=0;i<histos.size()-1;++i)
//     for(unsigned int j=i+1;j<histos.size();++j)
//     {
//       histos[i]->Add(histos[j]);
//     }


//   for(unsigned int j=0;j<histos.size();++j)
//     {

//       histos[j]->SetLineWidth(2);
//       histos[j]->SetFillStyle(3001);
//       histos[j]->SetFillColor(colors[j]);
//       histos[j]->SetLineColor(kBlack);
      
//       histos[j]->Draw("HIST,SAME");
//       l->AddEntry(histos[j],labels[j].c_str(),"lp");
//     }
//   l->Draw();
 
//   return canv;
// }


TCanvas* 
PhysicsDrawer::drawStacked(const std::string& expression,
			   const std::string& cut,
			   const std::string& lumi,
			   int bins,
			   double min,
			   double max,
			   char* xlabel,
			   char *ylabel)


{
  TCanvas *canv = new TCanvas(("stacked"+expression).c_str(),expression.c_str());
  THStack *hs = new THStack("hs","CMS Preliminary");
  
  canv->cd();

  std::vector<TH1F*> histos;
  for(unsigned int i=0;i<wrappers.size();++i)
    {
      std::string c;
      if(opts[i]=="MC")
	{
	  if(cut.size()==0)
	    c="("+lumi+")*"+preCuts[i];
	  else
	   c="("+lumi+")*"+preCuts[i]+"*("+cut+")";
	  histos.push_back(wrappers[i]->draw(expression,c,1,bins,min,max,"HIST",colors[i],xlabel,ylabel,"CMS Preliminary"));

	}
      else if(opts[i]=="DATA")
	{
	  c=cut;
	  histos.push_back(wrappers[i]->draw(expression,c,1,bins,min,max,"HIST",colors[i],xlabel,ylabel,"CMS Preliminary"));
	  
	}
    }

  TLegend *l = new TLegend(0.6,0.6,0.9,0.9);
  l->SetFillColor(kWhite);

  double signal=0.0;
  double bkg=0.0;



  for(unsigned int j=0;j<histos.size();++j)
    if(opts[j]=="MC")
    {
      if(types[j]==1)
	signal+=histos[j]->Integral();
      else
	bkg+=histos[j]->Integral();

      histos[j]->SetLineWidth(2);
      //      histos[j]->SetFillStyle(3001);
      histos[j]->SetFillColor(colors[j]);
      histos[j]->SetLineColor(kBlack);
      
      l->AddEntry(histos[j],labels[j].c_str(),"fp");
    }


  for(unsigned int i=0;i<histos.size();++i)
    if(opts[i]=="MC")
    {
          hs->Add(histos[i]);
    }

  float maxY = hs->GetMaximum();


  for(unsigned int i=0;i<histos.size();++i)
    if(opts[i]=="DATA")
      {
 	histos[i]->SetMarkerStyle(20);
 	if(histos[i]->GetMaximum()>maxY)
 	  maxY=histos[i]->GetMaximum();
 	l->AddEntry(histos[i],labels[i].c_str(),"p");
      }

  THStack *hsFinal = new THStack("hsFinal","CMS Preliminary");

  //Make second stack!
  //first update the histogram maximum
  for(unsigned int j=0;j<histos.size();++j) {
    histos[j]->GetYaxis()->SetRangeUser(0.,maxY);
    if(opts[j]=="MC")
      {
	hsFinal->Add(histos[j]);
      }

  }


  for(unsigned int j=0;j<histos.size();++j) {
    histos[j]->GetYaxis()->SetRangeUser(0.,maxY);
    if(opts[j]=="DATA")
      {
	histos[j]->Draw("e1");

      }

  }


      hsFinal->Draw("A,HIST,SAME");

//   for(unsigned int j=0;j<histos.size();++j) {
//     if(opts[j]=="DATA")
//       {
	
//       }

//   }
  
  

  canv->Update();
 

  

  l->Draw();

  printf ("S = %f B=%f\n",signal,bkg);
  printf("S/B = %f\n",signal/bkg);
  printf("S/SQRT(B) = %f\n",signal/sqrt(bkg));
  printf("S/SQRT(S+B) = %f\n",signal/sqrt(signal+bkg));

 
  return canv;
}


void 
PhysicsDrawer::setAlias(std::string ref,std::string alias)
{
  for(unsigned int i=0;i<wrappers.size();++i)
    {
      wrappers[i]->setAlias(ref,alias);
    }


}
