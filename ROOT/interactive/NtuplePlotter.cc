#include "NtuplePlotter.h"
#include <TFile.h>
#include <TROOT.h>
#include <math.h>
NtuplePlotter::NtuplePlotter()
{

}

NtuplePlotter::~NtuplePlotter()
{

}

NtuplePlotter::NtuplePlotter(std::string t)
{
  tree = new TChain(t.c_str());
}


void
NtuplePlotter::registerFile(std::string file)
{
  tree->Add(file.c_str());
}



void 
NtuplePlotter::setAlias(std::string collection,std::string process, std::string alias)
{
  tree->SetAlias((collection+"_"+process+".obj").c_str(),alias.c_str());

}

void 
NtuplePlotter::setAlias(std::string collection, std::string alias)
{
  tree->SetAlias((collection).c_str(),alias.c_str());
}



TH1F* 
NtuplePlotter::draw(std::string expression,std::string cut,double scale,int bins,double min,double max,std::string opt,Color_t col,char* xlabel,char *ylabel,char *title)
{
  TH1F *h = new TH1F("hh","a",bins,min,max);

  tree->Draw((expression+" >>hh").c_str(),cut.c_str(),"goff");
  h->Sumw2();

  h->GetXaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetNdivisions(509);
  h->GetYaxis()->SetNdivisions(509);
  h->GetYaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleOffset(1.25);
  h->SetMarkerColor(col);
  h->SetMarkerStyle(20);
  h->GetXaxis()->SetTitle(xlabel);
  h->GetYaxis()->SetTitle(ylabel);
  h->SetTitle(title);
      if(h->Integral()>0)
	if(scale==0) h->Scale(1/h->Integral());
	else
	  h->Scale(scale);
  h->Draw(opt.c_str());
  return h;
}



TH1F* 
NtuplePlotter::draw(std::string expression,std::string cut,double scale,std::string opt,Color_t col,char* xlabel,char *ylabel,char *title)
{
  tree->Draw(expression.c_str(),cut.c_str(),"goff");
  TH1F* h = (TH1F*)gPad->GetPrimitive("htemp");

  h->Sumw2();

  h->GetXaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetNdivisions(509);
  h->GetYaxis()->SetNdivisions(509);
  h->GetYaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleOffset(1.25);
  h->SetMarkerColor(col);
  h->SetMarkerStyle(20);
  h->SetFillColor(col);
  h->GetXaxis()->SetTitle(xlabel);
  h->GetYaxis()->SetTitle(ylabel);
  h->SetTitle(title);
      if(h->Integral()>0)
	if(scale==0) h->Scale(1/h->Integral());
	else
	  h->Scale(scale);
  h->Draw(opt.c_str());
  return h;
}


TH2F* 
NtuplePlotter::draw2D(std::string expression,std::string cut,double scale,int binsX,double minX,double maxX,int binsY,double minY,double maxY,std::string opt,Color_t col,char* xlabel,char *ylabel,char *title)
{
  TH2F *h = new TH2F("h","h",binsX,minX,maxX,binsY,minY,maxY);

  tree->Draw((expression+" >>h").c_str(),cut.c_str(),"goff");
  h->GetXaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetNdivisions(509);
  h->GetYaxis()->SetNdivisions(509);
  h->GetYaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleOffset(1.25);
  h->SetMarkerColor(col);
  h->SetMarkerStyle(1);
  h->SetMarkerColor(col);
  h->GetXaxis()->SetTitle(xlabel);
  h->GetYaxis()->SetTitle(ylabel);
  h->SetTitle(title);
      if(h->Integral()>0)
	if(scale==0) h->Scale(1/h->Integral());
	else
	  h->Scale(scale);
  h->Draw(opt.c_str());
  return h;
}






void
NtuplePlotter::compare(NtuplePlotter& file2,std::string expression,std::string cut1,std::string cut2,int bins,double min,double max,double scale,char* xlabel,char *ylabel,char *title,const char* e1,const char* e2)
{

  if(cut2=="*")
    cut2=cut1;

  TH1F *hh = new TH1F("hh","hh",bins,min,max);
  TH1F *h = new TH1F("h","h",bins,min,max);

  tree->Draw((expression+">>h").c_str(),cut1.c_str(),"goff");
  file2.getTree()->Draw((expression+">>hh").c_str(),cut2.c_str(),"goff");

  h->Sumw2();
  hh->Sumw2();

  h->GetXaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetNdivisions(509);
  h->GetYaxis()->SetNdivisions(509);
  h->GetYaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleOffset(1.25);

  h->SetMarkerColor(kBlack);
  h->SetMarkerStyle(20);
  h->SetFillStyle(0);
  h->SetLineWidth(2);

  h->SetMarkerSize(0.7);
  h->SetLineColor(kBlue);
  h->SetFillColor(kBlue);
  h->SetFillStyle(3001);

  h->GetXaxis()->SetTitle(xlabel);
  h->GetYaxis()->SetTitle(ylabel);
  h->SetTitle(title);
  if(h->Integral()>0)
    if(scale==0) h->Scale(1/h->Integral());
    else
      h->Scale(scale);
  hh->SetMarkerColor(kBlack);
  hh->SetMarkerStyle(20);
  hh->SetMarkerSize(0.8);
  
  if(hh->Integral()>0)
    if(scale==0) hh->Scale(1/hh->Integral());
    else
      hh->Scale(scale);
  
  h->Draw("HIST");
  hh->Draw("e1,SAME");
  
  if(e1!="")
    {
      TLegend *l = new TLegend(0.6,0.7,0.9,0.9);
      l->AddEntry(h,e1,"f");
      l->AddEntry(hh,e2,"p");
      l->Draw();
    }
  
}


TH1F* 
NtuplePlotter::drawSignificance (NtuplePlotter& file2,std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,std::string sigType,int bins,double min,double max,Color_t col,char* xtitle,char* ytitle,char* title)
{
  
  
  TH1F *h = new TH1F("h","h",bins,min,max);
  TH1F *hh = new TH1F("hh","hh",bins,min,max);
  
  tree->Draw((numVar+">>h").c_str(),numCuts.c_str(),"goff");
  file2.getTree()->Draw((denomVar+">>hh").c_str(),denomCuts.c_str(),"goff");
  
  h->Sumw2();
  hh->Sumw2();
  
  TH1F* g1 = new TH1F("sig","Significance",bins,min,max); 
  
  for(unsigned int i=1;i<=g1->GetNbinsX();++i)
    {
      double S = h->GetBinContent(i);
      double B = hh->GetBinContent(i);
      if(S>0&&B>0)
	{
	  if(sigType =="discovery")
	    g1->SetBinContent(i,S/sqrt(B));
	  else if(sigType =="measurement")
	    g1->SetBinContent(i,S/sqrt(S+B));
	}
    }
  
  
  h->Delete();
  hh->Delete();
  
  g1->GetXaxis()->SetLabelSize(0.06);
  g1->GetXaxis()->SetNdivisions(509);
  g1->GetYaxis()->SetNdivisions(509);
  g1->GetYaxis()->SetLabelSize(0.06);
  g1->GetXaxis()->SetTitleSize(0.06);
  g1->GetYaxis()->SetTitleSize(0.06);
  g1->GetYaxis()->SetTitleOffset(1.25);
  g1->SetMarkerColor(col);
  g1->SetMarkerStyle(20);
  g1->GetXaxis()->SetTitle(xtitle);
  g1->GetYaxis()->SetTitle(ytitle);
  g1->SetTitle(title);
  g1->Draw("");

  return g1;


}



TH1F* 
NtuplePlotter::drawEfficiencyH(std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,int bins,double min,double max,Color_t col,char* xtitle,char* ytitle,char* title)
{


  TH1F *h = new TH1F("h","h",bins,min,max);
  TH1F *hh = new TH1F("hh","hh",bins,min,max);

  tree->Draw((numVar+">>h").c_str(),numCuts.c_str(),"goff");
  tree->Draw((denomVar+">>hh").c_str(),denomCuts.c_str(),"goff");
  h->Sumw2();
  hh->Sumw2();


  h->SetName("eff");
  h->Divide(h,hh,1.,1.,"B");


  h->GetXaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetNdivisions(509);
  h->GetYaxis()->SetNdivisions(509);
  h->GetYaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleOffset(1.25);
  h->SetMarkerColor(col);
  h->SetMarkerStyle(20);
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  h->SetTitle(title);
  h->Draw("");

  return h;
}

TGraphAsymmErrors* 
NtuplePlotter::drawEfficiency(std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,int bins,double min,double max,Color_t col,char* xtitle,char* ytitle,char* title)
{


  TH1F *h = new TH1F("h","h",bins,min,max);
  TH1F *hh = new TH1F("hh","hh",bins,min,max);
  h->Sumw2();
  hh->Sumw2();

  tree->Draw((numVar+">>h").c_str(),numCuts.c_str(),"goff");
  tree->Draw((denomVar+">>hh").c_str(),denomCuts.c_str(),"goff");

  TGraphAsymmErrors* g1 = new TGraphAsymmErrors;
  g1->SetName("eff");
  g1->Divide(h,hh);

  h->Delete();
  hh->Delete();

  g1->GetXaxis()->SetLabelSize(0.06);
  g1->GetXaxis()->SetNdivisions(509);
  g1->GetYaxis()->SetNdivisions(509);
  g1->GetYaxis()->SetLabelSize(0.06);
  g1->GetXaxis()->SetTitleSize(0.06);
  g1->GetYaxis()->SetTitleSize(0.06);
  g1->GetYaxis()->SetTitleOffset(1.25);
  g1->SetMarkerColor(col);
  g1->SetMarkerStyle(20);
  g1->GetXaxis()->SetTitle(xtitle);
  g1->GetYaxis()->SetTitle(ytitle);
  g1->SetTitle(title);
  g1->Draw("AP");

  return g1;
}


/*
TGraphAsymmErrors* NtuplePlotter::drawEfficiency(std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,Color_t col,char* xtitle,char* ytitle,char* title)
{
  tree->Draw(numVar.c_str(),numCuts.c_str());
  TH1F* h = (TH1F*)(gPad->GetPrimitive("htemp"));
  h->Sumw2();

  TH1F *hh = new TH1F("hh","hh",h->GetNbinsX(),h->GetXaxis()->GetXmin(),h->GetXaxis()->GetXmax());
  tree->Draw((denomVar+">>hh").c_str(),denomCuts.c_str());
  hh->Sumw2();

  TGraphAsymmErrors* g1 = new TGraphAsymmErrors;
  g1->SetName("e1");
  g1->BayesDivide(h,hh);

  h->Delete();
  hh->Delete();


  g1->GetXaxis()->SetLabelSize(0.06);
  g1->GetXaxis()->SetNdivisions(509);
  g1->GetYaxis()->SetNdivisions(509);
  g1->GetYaxis()->SetLabelSize(0.06);
  g1->GetXaxis()->SetTitleSize(0.06);
  g1->GetYaxis()->SetTitleSize(0.06);
  g1->GetYaxis()->SetTitleOffset(1.25);
  g1->SetMarkerColor(col);
  g1->SetMarkerStyle(20);
  g1->GetXaxis()->SetTitle(xtitle);
  g1->GetYaxis()->SetTitle(ytitle);
  g1->SetTitle(title);
  g1->Draw("AP");

  return g1;
}
*/


double
NtuplePlotter::cutAcceptance(const char* cut_num,const char* cut_denom)
{
   
  if(tree->GetEntries(cut_denom)>0)
    printf("Cut Effect  =%f \n",((double)tree->GetEntries(cut_num))/((double)tree->GetEntries(cut_denom)));
  else
    printf("Denominator = 0\n");
  
  double efficiency = ((double)tree->GetEntries(cut_num))/((double)tree->GetEntries(cut_denom));
  double error = sqrt(efficiency*(1-efficiency)/((double)tree->GetEntries(cut_denom)));

  printf(" Result = %f +- %f\n",efficiency,error);

  return efficiency;
}



TH1F* 
NtuplePlotter::drawThresholdPlot(std::string var,std::string cuts,double min,double max,double step,char* xtitle,char* ytitle,char* title)
{

  TH1F *g1 = new TH1F("h","h",(int)((max-min)/step),min,max);

  int n=0;
  for(double th=min;th<max;th+=step)
    {

      char v[500];
      sprintf(v,"%s>%f&&%s",var.c_str(),th,cuts.c_str());
      if(tree->GetEntries(cuts.c_str())>0) {
	double efficiency=cutAcceptance(v,cuts.c_str());
	double error = sqrt(efficiency*(1-efficiency)/((double)tree->GetEntries(cuts.c_str())));
	g1->SetBinContent(n,efficiency);
	g1->SetBinError(n,error);
	
	n++;
      }
    }

  g1->GetXaxis()->SetLabelSize(0.06);
  g1->GetXaxis()->SetNdivisions(509);
  g1->GetYaxis()->SetNdivisions(509);
  g1->GetYaxis()->SetLabelSize(0.06);
  g1->GetXaxis()->SetTitleSize(0.06);
  g1->GetYaxis()->SetTitleSize(0.06);
  g1->GetYaxis()->SetTitleOffset(1.25);
  g1->SetMarkerColor(kRed);
  g1->SetMarkerStyle(20);
  g1->GetYaxis()->SetTitle("Acceptance");
  g1->GetXaxis()->SetTitle(xtitle);
  g1->GetYaxis()->SetTitle(ytitle);
  g1->SetTitle(title);
  g1->Draw("");

  return g1;
}



TGraphErrors*  
NtuplePlotter::rocCurve(NtuplePlotter& file2,TString var,TString direction,TString numCuts,TString denomCuts,double min,double max,double step,Color_t col,Color_t fillColor,int style,TString xlabel,TString ylabel,TString name)
{

  TGraphErrors *g=  new TGraphErrors();

  double num=0.0;
  double denom=0.0;
  double x = 0.;
  double y=0.;

  double ex = 0.;
  double ey=0.;

  int point = 0;

  for(double c = min; c<max;c+=step)
    {
      TString cutSignal     ="("+ numCuts+")*("+var+direction+TString::Format("%f",c)+")";
      TString cutBackground ="("+ denomCuts+")*("+var+direction+TString::Format("%f",c)+")";

      TH1F * htmp1 = new TH1F("htmp1","s_n",2,0,2);
      htmp1->Sumw2();
      tree->Draw(var+"=="+var+">>htmp1",cutSignal,"goff");
      num = htmp1->Integral();
      delete htmp1;

      TH1F * htmp2 = new TH1F("htmp2","s_n",2,0,2);
      htmp2->Sumw2();

      tree->Draw(var+"=="+var+">>htmp2",numCuts,"goff");
      denom = htmp2->Integral();
      delete htmp2;
      if(denom >0)
	{
	  y = num/denom;
	  ey = sqrt(y*(1-y)/denom);
	  //let's go for y
	  TH1F * htmp3 = new TH1F("htmp3","s_n",2,0,2);
	  htmp3->Sumw2();
	  file2.getTree()->Draw(var+"=="+var+">>htmp3",cutBackground,"goff");
	  num = htmp3->Integral();  
	  delete htmp3;

	  TH1F * htmp4 = new TH1F("htmp4","s_n",2,0,2);
	  htmp4->Sumw2();
	  file2.getTree()->Draw(var+"=="+var+">>htmp4",denomCuts,"goff");
	  denom = htmp4->Integral();
	  delete htmp4;

	  if(denom>0)
	    {  
	      x = num / denom;
	      ex= sqrt(x*(1-x)/denom);
	      g->SetPoint(point,x,y);
	      g->SetPointError(point,ex,ey);
	      point++;
	      }
	}
      
    }


  g->SetMarkerColor(col);
  g->SetLineColor(col);
  g->SetFillColor(fillColor);
  g->SetLineStyle(style);
  g->SetLineWidth(2);
  g->SetMarkerStyle(20);
  g->GetXaxis()->SetTitle(xlabel);
  g->GetYaxis()->SetTitle(ylabel);

  g->SetName(name);
  g->Draw("AP");
  return g;

}



TGraphErrors*  
NtuplePlotter::sigCurve(NtuplePlotter& file2,std::string var,char direction, std::string numCuts,std::string denomCuts,double numWeight,double denomWeight,double min,double max,double step,Color_t col,char* xlabel,char *ylabel,char *title)
{

  TGraphErrors *g=  new TGraphErrors();


  double num=0.0;
  double denom=0.0;
  double x = 0.;
  double y=0.;

  double ex = 0.;
  double ey=0.;

  int point = 0;

  for(double c = min; c<max;c+=step)
    {
      char v[300];
      char v2[300];
  	
      //create cut
      sprintf(v,"%s%c%f&&%s",var.c_str(),direction,c,numCuts.c_str());
      sprintf(v2,"%s%c%f&&%s",var.c_str(),direction,c,denomCuts.c_str());
      num = numWeight*tree->GetEntries(v)/tree->GetEntries();
      denom=denomWeight*file2.getTree()->GetEntries(v2)/file2.getTree()->GetEntries();
      if(denom >0)
	{
	  y = num /sqrt(num+denom);
	  x = (c-min)/(max-min);
	  g->SetPoint(point,x,y);
	  g->SetPointError(point,ex,ey);
	  point++;
	}
      
    }


  g->GetXaxis()->SetLabelSize(0.06);
  g->GetXaxis()->SetNdivisions(509);
  g->GetYaxis()->SetNdivisions(509);
  g->GetYaxis()->SetLabelSize(0.06);
  g->GetXaxis()->SetTitleSize(0.06);
  g->GetYaxis()->SetTitleSize(0.06);
  g->GetYaxis()->SetTitleOffset(1.25);
  g->SetMarkerColor(col);
  g->SetLineColor(col);
  g->SetLineWidth(2);
  g->SetMarkerStyle(20);
  g->GetXaxis()->SetTitle(xlabel);
  g->GetYaxis()->SetTitle(ylabel);
  g->SetTitle(title);
 

  char nam[100];
  sprintf(nam,"Significance(%s)",var.c_str());
  g->SetName(nam);
  
  
  g->Draw("AP");
  return g;

}



void NtuplePlotter::addLabel(TCanvas *c,TString label,float x , float y,float size)
{
  c->cd();
  TLatex *a = new TLatex(x,y,label);
  a->SetTextSize(size);
  a->Draw();

}



TCanvas* 
NtuplePlotter::drawEfficiencySeries(std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,int bins,double min,double max,std::string cutDescriptions,char* xtitle,char* ytitle,char* title)
{
  std::vector<std::string> cuts;
  std::vector<std::string> cutDes;
  tokenize(numCuts,cuts,"*");
  partialTokenize(cutDescriptions,cutDes,"*");
  
  TCanvas *c = new TCanvas("StepByStep","Step By Step",400,400);
  TLegend *l = new TLegend(0.6,0.6,0.8,0.8);

  std::vector<TGraphAsymmErrors*> graphs;
  c->cd();
  for(unsigned int i=0;i<cuts.size();++i)
    {
      printf("Cut=%s\n",cuts[i].c_str());

      TGraphAsymmErrors *g =drawEfficiency(numVar,denomVar,cuts[i],denomCuts,bins,min,max,i+2,xtitle, ytitle,title);
      graphs.push_back(g);


    }
  graphs[0]->Draw("AP");
  l->AddEntry(graphs[0],cutDes[0].c_str(),"p");

  for(unsigned int i=1;i<cuts.size();++i)
    {
      if(cutDes.size()>i-1)
	l->AddEntry(graphs[i],cutDes[i].c_str(),"p");
      else
	l->AddEntry(graphs[i],"UNKNOWN","p");

      graphs[i]->Draw("Psame");
    }
  l->Draw();

  return c;
}
