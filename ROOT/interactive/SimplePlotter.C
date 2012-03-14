#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TProfile.h"
#include <vector>
#include <math.h>
#include <stdio.h>


class SimplePlotter {
public:
  SimplePlotter() {}
  ~SimplePlotter() {}
  


  void addFile(TString tree,TString name,TString label,TString preselection,int type,Color_t color,Color_t lcolor,int style = 1001)
  {
    TChain *chain = new TChain(tree);
    chain->Add(name);
    trees_.push_back(chain);
    labels_.push_back(label);
    types_.push_back(type);
    colors_.push_back(color);
    lcolors_.push_back(lcolor);
    styles_.push_back(style);
    preselection_.push_back(preselection);

  } 



  TCanvas* makeProfile(TString var,TString selection,int binsx, float minX, float maxX,float minY,float maxY,TString labelX,TString labelY,TString addLabel,double xLabel,double yLabel,double yLabel2,TString postFix = "")
  {
    TProfile *profile = new TProfile("profile","",binsx,minX,maxX,minY,maxY);
    profile->Sumw2();
    for(unsigned int i=0;i<trees_.size();++i)
      {
	if(types_[i]){//MC
	  trees_[i]->Draw(var +">>profile",preselection_[i]+"*("+selection+")","goff");
	  profile->SetMarkerStyle(20);
	}
      }
    profile->GetXaxis()->SetTitle(labelX);
    profile->GetYaxis()->SetTitle(labelY);
    profile->GetYaxis()->SetRangeUser(minY,maxY);
    
    TCanvas *c= new TCanvas(var+postFix,var+postFix,600,600);
    c->cd();
    profile->Draw();

    TLatex *l1 = new TLatex(xLabel,yLabel,"CMS Preliminary 2010");
    l1->SetTextSize(0.045);
    l1->Draw();
    TLatex *l2 = new TLatex(xLabel,yLabel2,addLabel);
    l2->SetTextSize(0.035);
    l2->Draw();
    return c;
  }


  TCanvas* make2D(TString var,TString selection,int binsx, float minX, float maxX,int binsy,float minY,float maxY,TString labelX,TString labelY,TString addLabel,double xLabel,double yLabel,double yLabel2,TString postFix = "")
  {
    TH2F *profile = new TH2F("profile","",binsx,minX,maxX,binsy,minY,maxY);
    profile->Sumw2();
    for(unsigned int i=0;i<trees_.size();++i)
      {
	if(types_[i]){//MC
	  trees_[i]->Draw(var +">>profile",preselection_[i]+"*("+selection+")","goff");
	  profile->SetMarkerStyle(20);
	}
      }

    profile->GetXaxis()->SetTitle(labelX);
    profile->GetYaxis()->SetTitle(labelY);
    profile->GetYaxis()->SetRangeUser(minY,maxY);
    
    TCanvas *c= new TCanvas(var+postFix,var+postFix,600,600);
    c->cd();
    profile->Draw("COLZ");

    TLatex *l1 = new TLatex(xLabel,yLabel,"CMS Preliminary 2010");
    l1->SetTextSize(0.045);
    l1->Draw();
    TLatex *l2 = new TLatex(xLabel,yLabel2,addLabel);
    l2->SetTextSize(0.035);
    l2->Draw();
    return c;
  }


  TCanvas* makeStackedPlot(TString var,TString selection,TString lumi, int bins, float min, float max,TString labelX,TString units,double xLabel,double yLabel,double yLabel2,double xLegend,double yLegend,bool log,double ymin,double ymax,TString postFix = "",bool ofl = false )
  {
    THStack *hs = new THStack("hs","CMS Preliminary 2010");
    TLegend *l = new TLegend(xLegend,yLegend,xLegend+0.3,yLegend+0.3);
    
    float S=0.;
    float B=0.;
    float DATA=0.0;

     std::vector<TH1F*> histos;
    for(unsigned int i=0;i<trees_.size();++i)
      {
	TH1F * hh = new TH1F("hh","",bins,min,max);
	hh->Sumw2();
	if(types_[i]<=0){//MC
	  trees_[i]->Draw(var +">>hh",lumi+"*"+preselection_[i]+"*("+selection+")","goff");
	  hh->SetLineWidth(2);
	  hh->SetFillColor(colors_[i]);
	  hh->SetFillStyle(styles_[i]);

	  hh->SetLineColor(lcolors_[i]);
	  hh->SetName("hh"+var);
	  if(types_[i]==-1) 
	    S+=hh->Integral();
	  else if(types_[i]==0)
	    B+=hh->Integral();

	  histos.push_back(hh);

	}
	else {
	  trees_[i]->Draw(var +">>hh",preselection_[i]+"*("+selection+")","goff");
	  hh->SetMarkerStyle(20);
	  hh->SetLineWidth(2);
	  histos.push_back(hh);
	  DATA+=hh->Integral();
	}
      }
    for(unsigned int i=0;i<histos.size();++i) {
      if(ofl)
	{
	  histos[i]->SetBinContent(bins,histos[i]->GetBinContent(bins)+
				   histos[i]->GetBinContent(bins+1));
	  histos[i]->SetBinContent(bins+1,0.0);
	}


      if(types_[i]<=0)
	hs->Add(histos[i]);

      //make the legend here 
      if(labels_[types_.size()-1-i]!="") {
	if(types_[types_.size()-1-i]<=0)
	  l->AddEntry(histos[labels_.size()-1-i],labels_[labels_.size()-1-i],"f");	else
	  l->AddEntry(histos[labels_.size()-1-i],labels_[labels_.size()-1-i],"p");
      }						
    } 							
   
    l->SetFillColor(kWhite);
    l->SetBorderSize(0);

    
    TCanvas *c;
    if(log)
      c = new TCanvas(var+"LOG"+postFix,var+"LOG"+postFix,600,600);
    else
      c = new TCanvas(var+postFix,var+postFix,600,600);

    c->cd();
    if(log)
      c->SetLogy();

    for(unsigned int i=0;i<trees_.size();++i)
      if(types_[i]>0)//DATA
      {
	if(units=="")
	  histos[i]->GetXaxis()->SetTitle(labelX);
	else
	  histos[i]->GetXaxis()->SetTitle(labelX+"["+units+"]");
	  
	TString s("Events / ");
	char binW[200];
	sprintf(binW,"%1.1f",histos[i]->GetBinWidth(1));
	
	s+=binW;
	s+=" "+units;
	histos[i]->GetYaxis()->SetTitle(s);
	histos[i]->Draw("e1");
	histos[i]->GetYaxis()->SetRangeUser(ymin,ymax);
      }
    

    printf("C\n");  
    hs->Draw("A,HIST,SAME");

    TLatex *l1 = new TLatex(xLabel,yLabel,"CMS  2010");
    l1->SetTextSize(0.04);
    l1->Draw();
    TLatex *l2 = new TLatex(xLabel,yLabel2,"L_{int} = "+lumi+" pb^{-1}, #sqrt{s} = 7 TeV");
    l2->SetTextSize(0.04);
    l2->Draw();


    for(unsigned int i=0;i<trees_.size();++i)
      if(types_[i]>0)//DATA
      {
	histos[i]->Draw("e1,SAME");
      }
    l->Draw();


    printf("S = %f \n",S);
    printf("B = %f \n",B);
    printf("MC = %f \n",S+B);
    printf("DATA = %f \n",DATA);
    printf("Purity = S/(S+B) = %f\n",S/(S+B));
    printf("Significance1 = S/SQRT(S+B) = %f\n",S/sqrt(S+B));
    printf("Significance2 = S/SQRT(B) = %f\n",S/sqrt(B));
    c->RedrawAxis();
    return c;
  }

  TCanvas* makeStackedNormalizedPlot(TString var,TString selection,TString lumi, int bins, float min, float max,TString labelX,TString units,double xLabel,double yLabel,double yLabel2,double xLegend,double yLegend,bool log,double ymin,double ymax,TString postFix = "",bool ofl = false )
  {
    THStack *hs = new THStack("hs","CMS Preliminary 2010");
    TLegend *l = new TLegend(xLegend,yLegend,xLegend+0.3,yLegend+0.3);
    
    float S=0.;
    float B=0.;
    float DATA=0.0;

     std::vector<TH1F*> histos;
    for(unsigned int i=0;i<trees_.size();++i)
      {
	TH1F * hh = new TH1F("hh","",bins,min,max);
	hh->Sumw2();
	if(types_[i]<=0){//MC
	  trees_[i]->Draw(var +">>hh",lumi+"*"+preselection_[i]+"*("+selection+")","goff");
	  hh->SetLineWidth(2);
	  hh->SetFillColor(colors_[i]);
	  hh->SetFillStyle(styles_[i]);

	  hh->SetLineColor(lcolors_[i]);
	  hh->SetName("hh"+var);
	  if(types_[i]==-1) 
	    S+=hh->Integral();
	  else if(types_[i]==0)
	    B+=hh->Integral();
	  histos.push_back(hh);
	}
	else {
	  trees_[i]->Draw(var +">>hh",preselection_[i]+"*("+selection+")","goff");
	  hh->SetMarkerStyle(20);
	  hh->SetLineWidth(2);
	  histos.push_back(hh);
	  DATA+=hh->Integral();
	}
      }
    for(unsigned int i=0;i<histos.size();++i) {
      if(ofl)
	{
	  histos[i]->SetBinContent(bins,histos[i]->GetBinContent(bins)+
				   histos[i]->GetBinContent(bins+1));
	  histos[i]->SetBinContent(bins+1,0.0);
	}
      
      


      if(types_[i]<=0) {
	histos[i]->Scale(1./(S+B));
	hs->Add(histos[i]);
      }
      //make the legend here 
      if(labels_[types_.size()-1-i]!="") {
	if(types_[types_.size()-1-i]<=0)
	  l->AddEntry(histos[labels_.size()-1-i],labels_[labels_.size()-1-i],"f");	else
	  l->AddEntry(histos[labels_.size()-1-i],labels_[labels_.size()-1-i],"p");
      }						
    } 							
   
    l->SetFillColor(kWhite);
    l->SetBorderSize(0);

    
    TCanvas *c;
    if(log)
      c = new TCanvas(var+"LOG"+postFix,var+"LOG"+postFix,600,600);
    else
      c = new TCanvas(var+postFix,var+postFix,600,600);

    c->cd();
    if(log)
      c->SetLogy();

    for(unsigned int i=0;i<trees_.size();++i)
      if(types_[i]>0)//DATA
      {
	if(units=="")
	  histos[i]->GetXaxis()->SetTitle(labelX);
	else
	  histos[i]->GetXaxis()->SetTitle(labelX+"["+units+"]");
	  
	TString s("a u. ");
	histos[i]->GetYaxis()->SetTitle(s);
	histos[i]->DrawNormalized("e1");
	histos[i]->GetYaxis()->SetRangeUser(ymin,ymax);
      }
    

    printf("C\n");  
    hs->Draw("A,HIST,SAME");

    TLatex *l1 = new TLatex(xLabel,yLabel,"CMS  2010");
    l1->SetTextSize(0.04);
    l1->Draw();
    TLatex *l2 = new TLatex(xLabel,yLabel2,"L_{int} = "+lumi+" pb^{-1}, #sqrt{s} = 7 TeV");
    l2->SetTextSize(0.04);
    l2->Draw();


    for(unsigned int i=0;i<trees_.size();++i)
      if(types_[i]>0)//DATA
      {
	histos[i]->DrawNormalized("e1,SAME");
      }
    l->Draw();


    printf("S = %f \n",S);
    printf("B = %f \n",B);
    printf("MC = %f \n",S+B);
    printf("DATA = %f \n",DATA);
    printf("Purity = S/(S+B) = %f\n",S/(S+B));
    printf("Significance1 = S/SQRT(S+B) = %f\n",S/sqrt(S+B));
    printf("Significance2 = S/SQRT(B) = %f\n",S/sqrt(B));
    c->RedrawAxis();
    return c;
  }










  TCanvas* makeComparison(TString var,TString selection,TString lumi, int bins, float min, float max,TString labelX,TString units,double xLabel,double yLabel,double yLabel2,double xLegend,double yLegend,bool log,double ymin,double ymax,TString postFix = "" )
  {
    THStack *hs = new THStack("hs","CMS Preliminary 2010");
    TLegend *l = new TLegend(xLegend,yLegend,xLegend+0.3,yLegend+0.3);
    
    float S=0.;
    float B=0.;
    float DATA=0.0;

     std::vector<TH1F*> histos;
    for(unsigned int i=0;i<trees_.size();++i)
      {
	TH1F * hh = new TH1F("hh","",bins,min,max);
	hh->Sumw2();
	if(types_[i]<=0){//MC
	  trees_[i]->Draw(var +">>hh",lumi+"*"+preselection_[i]+"*("+selection+")","goff");
	  hh->Scale((float)1./trees_[i]->GetEntries());
	  hh->SetLineWidth(2);
	  hh->SetLineColor(colors_[i]);
	  hh->SetName("hh"+var);
	  if(types_[i]==-1)
	    S+=hh->Integral();
	  else if(types_[i]==0)
	    B+=hh->Integral();
	  if(labels_[i]!="")
	    l->AddEntry(hh,labels_[i],"f");

	  if(lumi=='1')
	    hh->Scale(1./hh->Integral());

	  
	  histos.push_back(hh);
	}
	else {
	  trees_[i]->Draw(var +">>hh",preselection_[i]+"*("+selection+")","goff");
	  hh->SetMarkerStyle(20);
	  l->AddEntry(hh,labels_[i],"p");
	  if(lumi=='1')
	    hh->Scale(1./hh->Integral());
	  histos.push_back(hh);
	  DATA+=hh->Integral();
	}
      }
    for(unsigned int i=0;i<histos.size();++i)
	hs->Add(histos[i]);
   
    l->SetFillColor(kWhite);
    l->SetBorderSize(0);

    
    TCanvas * c = new TCanvas(var+postFix,var+postFix,600,600);

    c->cd();
    hs->Draw("HIST,NOSTACK");

    TLatex *l1 = new TLatex(xLabel,yLabel,"CMS Preliminary 2010");
    l1->SetTextSize(0.04);
    l1->Draw();
    TLatex *l2 = new TLatex(xLabel,yLabel2,"L_{int} = "+lumi+" pb^{-1}, #sqrt{s} = 7 TeV");
    l2->SetTextSize(0.04);
    l2->Draw();

    l->Draw();



    c->RedrawAxis();
    return c;
  }






  TCanvas* makeStackedPlotAndSave(TString var,TString selection,TString lumi, int bins, float min, float max,TString labelX,TString units,double xLabel,double yLabel,double yLabel2,double xLegend,double yLegend,bool log,double ymin,double ymax,TString postFix = "" )
  {
    THStack *hs = new THStack("hs","CMS Preliminary 2010");
    TLegend *l = new TLegend(xLegend,yLegend,xLegend+0.3,yLegend+0.3);
    TFile *f = new TFile("histograms.root","RECREATE");
    f->cd();

    float S=0.;
    float B=0.;
    float DATA=0.0;

     std::vector<TH1F*> histos;
    for(unsigned int i=0;i<trees_.size();++i)
      {
	TH1F * hh = new TH1F("hh","",bins,min,max);
	hh->Sumw2();
	if(types_[i]<=0){//MC
	  trees_[i]->Draw(var +">>hh",lumi+"*"+preselection_[i]+"*("+selection+")","goff");
	  hh->SetLineWidth(2);
	  hh->SetFillColor(colors_[i]);
	  hh->SetFillStyle(styles_[i]);

	  hh->SetLineColor(kBlack);
	  hh->SetName("hh"+var);
	  if(types_[i]==-1) 
	    S+=hh->Integral();
	  else if(types_[i]==0)
	    B+=hh->Integral();
	  l->AddEntry(hh,labels_[i],"f");
	  histos.push_back(hh);

	  hh->SetName(labels_[i]);
	  hh->Write();
	  
	}
	else {
	  trees_[i]->Draw(var +">>hh",preselection_[i]+"*("+selection+")","goff");
	  hh->SetMarkerStyle(20);
	  l->AddEntry(hh,labels_[i],"p");
	  histos.push_back(hh);
	  DATA+=hh->Integral();

	  hh->SetName(labels_[i]);
	  hh->Write();
	}
      }
    for(unsigned int i=0;i<histos.size();++i)
      if(types_[i]<=0)
	hs->Add(histos[i]);
   
    l->SetFillColor(kWhite);
    l->SetBorderSize(0);

    
    TCanvas *c;
    if(log)
      c = new TCanvas(var+"LOG"+postFix,var+"LOG"+postFix,600,600);
    else
      c = new TCanvas(var+postFix,var+postFix,600,600);

    c->cd();
    if(log)
      c->SetLogy();

    for(unsigned int i=0;i<trees_.size();++i)
      if(types_[i]>0)//DATA
      {
	if(units=="")
	  histos[i]->GetXaxis()->SetTitle(labelX);
	else
	  histos[i]->GetXaxis()->SetTitle(labelX+"["+units+"]");
	  
	TString s("Events / ");
	char binW[200];
	sprintf(binW,"%1.1f",histos[i]->GetBinWidth(1));
	
	s+=binW;
	s+=" "+units;
	histos[i]->GetYaxis()->SetTitle(s);
	histos[i]->Draw("e1");
	histos[i]->GetYaxis()->SetRangeUser(ymin,ymax);
      }
    

    printf("C\n");  
    hs->Draw("A,HIST,SAME");

    TLatex *l1 = new TLatex(xLabel,yLabel,"CMS Preliminary 2010");
    l1->SetTextSize(0.04);
    l1->Draw();
    TLatex *l2 = new TLatex(xLabel,yLabel2,"L_{int} = "+lumi+" pb^{-1}, #sqrt{s} = 7 TeV");
    l2->SetTextSize(0.04);
    l2->Draw();


    for(unsigned int i=0;i<trees_.size();++i)
      if(types_[i]>0)//DATA
      {
	histos[i]->Draw("e1,SAME");
      }
    l->Draw();


    printf("S = %f \n",S);
    printf("B = %f \n",B);
    printf("MC = %f \n",S+B);
    printf("DATA = %f \n",DATA);
    printf("Purity = S/(S+B) = %f\n",S/(S+B));
    printf("Significance1 = S/SQRT(S+B) = %f\n",S/sqrt(S+B));
    printf("Significance2 = S/SQRT(B) = %f\n",S/sqrt(B));
   

    f->Close();

    return c;
  }




  TCanvas* makeStackedPlotR(TString var,TString selection,TString lumi, int bins, float min, float max,TString labelX,TString units,double xLabel,double yLabel,double yLabel2,double xLegend,double yLegend,bool log,double ymin,double ymax,TString postFix = "" )
  {
    THStack *hs = new THStack("hs","CMS Preliminary 2010");
    TLegend *l = new TLegend(xLegend,yLegend,xLegend+0.3,yLegend+0.3);
    
    float S=0.;
    float B=0.;
    float DATA=0.0;

     std::vector<TH1F*> histos;
    for(unsigned int i=0;i<trees_.size();++i)
      {
	TH1F * hh = new TH1F("hh","",bins,min,max);
	hh->Sumw2();
	if(types_[i]<=0){//MC
	  trees_[i]->Draw(var +">>hh",lumi+"*"+preselection_[i]+"*("+selection+")","goff");
	  hh->SetLineWidth(2);
	  hh->SetFillColor(colors_[i]);
	  hh->SetFillStyle(styles_[i]);
	  hh->SetLineColor(kBlack);
	  hh->SetName("hh"+var);
	  if(types_[i]==-1)
	    S+=hh->Integral();
	  else if(types_[i]==0)
	    B+=hh->Integral();
	  l->AddEntry(hh,labels_[i],"f");
	  histos.push_back(hh);

	}
	else {
	  trees_[i]->Draw(var +">>hh",preselection_[i]+"*("+selection+")","goff");
	  hh->SetMarkerStyle(20);
	  l->AddEntry(hh,labels_[i],"p");
	  histos.push_back(hh);
	  DATA+=hh->Integral();
	}
      }
    for(unsigned int i=0;i<histos.size();++i)
      if(types_[i]<=0)
	hs->Add(histos[i]);
   
    l->SetFillColor(kWhite);
    l->SetBorderSize(0);

    
    TCanvas *c  = new TCanvas(var+"LOG"+postFix,var+"LOG"+postFix,600,900);
;
 c->cd();
    TPad * plotPad = new TPad("pad1","",0.0,0.3,1.0,1.0);
    TPad * ratioPad = new TPad("pad2","",0.0,0.0,1.0,0.3);

    plotPad->Draw();
    ratioPad->Draw();
    plotPad->cd();

    if(log)
      c->cd(1)->SetLogy();

    for(unsigned int i=0;i<trees_.size();++i)
      if(types_[i]>0)//DATA
      {
	if(units=="")
	  histos[i]->GetXaxis()->SetTitle(labelX);
	else
	  histos[i]->GetXaxis()->SetTitle(labelX+"["+units+"]");
	  
	TString s("Events / ");
	char binW[200];
	sprintf(binW,"%1.1f",histos[i]->GetBinWidth(1));
	
	s+=binW;
	s+=" "+units;
	histos[i]->GetYaxis()->SetTitle(s);
	histos[i]->Draw("e1");
	histos[i]->GetYaxis()->SetRangeUser(ymin,ymax);
      }
    

    printf("C\n");  
    hs->Draw("A,HIST,SAME");

    TLatex *l1 = new TLatex(xLabel,yLabel,"CMS Preliminary 2010");
    l1->SetTextSize(0.04);
    l1->Draw();
    TLatex *l2 = new TLatex(xLabel,yLabel2,"L_{int} = "+lumi+" pb^{-1}, #sqrt{s} = 7 TeV");
    l2->SetTextSize(0.04);
    l2->Draw();


    for(unsigned int i=0;i<trees_.size();++i)
      if(types_[i]>0)//DATA
      {
	histos[i]->Draw("e1,SAME");
      }
    l->Draw();

    ratioPad->cd();

    TH1F * mcAll = new TH1F("mcAll","",bins,min,max);
    TH1F * dataAll = new TH1F("dataAll","",bins,min,max);


    for(unsigned int i=0;i<histos.size();++i)
      if(types_[i]<=0)//MC
	mcAll->Add(histos[i]);
      else
	dataAll->Add(histos[i]);

    
    
    dataAll->Divide(dataAll,mcAll);
    dataAll->SetMarkerStyle(20);
    dataAll->Fit("pol0","SAME");
    

//     if(units=="")
//       mcAll->GetXaxis()->SetTitle(labelX);
//     else
//       mcAll->GetXaxis()->SetTitle(labelX+"["+units+"]");


    dataAll->GetYaxis()->SetTitle("DATA/MC");
    dataAll->GetYaxis()->SetTitleOffset(0.55);
    dataAll->GetYaxis()->SetTitleSize(0.12);
    dataAll->GetYaxis()->SetLabelSize(0.12);
    dataAll->GetXaxis()->SetLabelSize(0.12);
    dataAll->GetYaxis()->SetNdivisions(5);
    dataAll->GetYaxis()->SetRangeUser(0.,2.);

    dataAll->Draw("P");


    printf("S = %f \n",S);
    printf("B = %f \n",B);
    printf("Purity = S/(S+B) = %f\n",S/(S+B));
    printf("Significance1 = S/SQRT(S+B) = %f\n",S/sqrt(S+B));
    printf("Significance2 = S/SQRT(B) = %f\n",S/sqrt(B));
    c->RedrawAxis();

    return c;
  }







private:
  std::vector<TChain*> trees_;
  std::vector<TString> labels_;
  std::vector<TString> preselection_;
  std::vector<int> types_;
  std::vector<int> styles_;
  std::vector<Color_t> colors_;
  std::vector<Color_t> lcolors_;
};
