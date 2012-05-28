#include <TList.h>
#include <TString.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TLegend.h>

#include <RooAbsData.h>
#include <Math/MinimizerOptions.h>
#include <RooAbsReal.h>
#include <RooAbsPdf.h>
#include <RooAddPdf.h>
#include <RooArgSet.h>
#include <RooCurve.h>
#include <RooCategory.h>
#include <RooDataHist.h>
#include <RooDataSet.h>
#include <RooExtendPdf.h>
#include <RooFitResult.h>
#include <RooHist.h>
#include <RooHistPdf.h>
#include <RooMinuit.h>
#include <RooBinning.h>
#include <RooPlot.h>
#include <RooProdPdf.h>
#include <RooRealVar.h>
#include <RooFormulaVar.h>
#include <RooArgList.h>

#include <RooSimultaneous.h>
#include <RooWorkspace.h>
#include <RooStats/RooStatsUtils.h>

class plotter {
 public:
  plotter() {}
  ~plotter() {}
  plotter(RooWorkspace *w,std::string channel,std::string model,std::string par, std::string cat,std::string pdf = "",std::string data = ""):
    w_(w),
    par_(w->var(par.c_str())),
    cat_(w->cat(cat.c_str())),
    legend_(new TLegend(0.7,0.6,0.9,0.9))
    {


      if(data.size()==0) 
	data_ = w->data(("DATA_"+channel).c_str());
      else
	data_ = w->data(data.c_str());

      //set tdr Style
      tdrStyle();

      //check the  PDF 
      if(pdf.size()==0) {
	if(channel.size()>0) {
	  modelPdf_ = (w->pdf(("model_"+channel+"_"+model).c_str()));
	}
	else {
	  modelPdf_ = (w->pdf(("model_"+model).c_str()));
	}
      }
      else
	{
	  modelPdf_ = (w->pdf(pdf.c_str()));
	}


      if (modelPdf_ == 0) {
	std::cerr << "ERROR: missing pdf " << "model_"+channel+"_"+model << std::endl;
      }

      legend_->SetBorderSize(0);
      legend_->SetFillColor(kWhite);

      

    }


    void setCosmetics(std::string title,std::string unit) {
      par_->SetTitle(title.c_str());
      par_->setUnit(unit.c_str());

    }
    
    void addComponent(std::string name,std::string component,int fillColor,int lineColor) {
      components_.push_back(TString::Format("%s",component.c_str()));
      componentLabels_.push_back(name);
      fillColors_.push_back(fillColor);
      lineColors_.push_back(lineColor);
    }

    RooPlot* producePlot(std::string slice,int bins, float min, float max)
      {
	using namespace RooFit;
	//create binning
	RooBinning binning(bins,min,max);

	//	RooPlot *frame = par_->frame(min,max);
	RooPlot *frame = par_->frame();

	if(data_) {
	if(cat_) 
	  data_->plotOn(frame,Binning(binning),Cut(TString::Format("%s==%s::%s",cat_->GetName(),cat_->GetName(),slice.c_str())));
	else 
	  data_->plotOn(frame);
 	  RooCurve * curve = (RooCurve *) frame->getObject(frame->numItems() - 1);
 	  if(curve) 
 	    legend_->AddEntry(curve,"DATA","p"); 
	}
	
	//now create th stack
	for(int N=components_.size()-1;N>=0 ;N=N-1) {
	  //create component stack
	  TString compStack;
	  for(int i=0;i<=N;++i)
	    if(i!=N)
	      compStack+=components_[i]+",";
	    else
	      compStack+=components_[i];
	  //plot It!
	  if (cat_&&data_) {
	    modelPdf_->plotOn(frame, RooFit::Components(compStack), RooFit::LineColor(lineColors_[N]),RooFit::FillColor(fillColors_[N]),RooFit::FillStyle(1001), RooFit::LineWidth(2), RooFit::Slice(*cat_, slice.c_str()),RooFit::DrawOption("F"),RooFit::ProjWData(*data_));

	    modelPdf_->plotOn(frame, RooFit::Components(compStack), RooFit::LineColor(lineColors_[N]),RooFit::FillColor(fillColors_[N]),RooFit::FillStyle(1001), RooFit::LineWidth(2),RooFit::Slice(*cat_, slice.c_str()),RooFit::ProjWData(*data_));

	  }
	  else if (data_) {
	    modelPdf_->plotOn(frame, RooFit::Components(compStack), RooFit::LineColor(lineColors_[N]),RooFit::FillColor(fillColors_[N]),RooFit::FillStyle(1001), RooFit::LineWidth(2),RooFit::DrawOption("F"),RooFit::ProjWData(*data_));
	    modelPdf_->plotOn(frame, RooFit::Components(compStack), RooFit::LineColor(lineColors_[N]),RooFit::FillColor(fillColors_[N]),RooFit::FillStyle(1001), RooFit::LineWidth(2),RooFit::ProjWData(*data_));

	  }
	  else  {
	    modelPdf_->plotOn(frame, RooFit::Components(compStack), RooFit::LineColor(lineColors_[N]),RooFit::FillColor(fillColors_[N]),RooFit::FillStyle(1001), RooFit::LineWidth(2),RooFit::DrawOption("FL"));
	    modelPdf_->plotOn(frame, RooFit::Components(compStack), RooFit::LineColor(lineColors_[N]),RooFit::FillColor(fillColors_[N]),RooFit::FillStyle(1001), RooFit::LineWidth(2));
	  }
	  RooCurve * curve = (RooCurve *) frame->getObject(frame->numItems() - 1);
	  if(curve)
	    legend_->AddEntry(curve,componentLabels_[N].c_str(),"lf");
	}

	//If data exists just plot the data 
	if(data_&&cat_) data_->plotOn(frame,Binning(binning),Cut(TString::Format("%s==%s::%s",cat_->GetName(),cat_->GetName(),slice.c_str())));
	else if(data_)
	  data_->plotOn(frame);
	frame->addObject(legend_);


	
	return frame;
      }


 private:
  RooWorkspace *w_;
  RooAbsPdf* modelPdf_;
  RooRealVar *par_;
  RooCategory *cat_;
  RooAbsData *data_;
  TLegend *legend_;

  //plotting stuff
  std::vector<TString> components_;
  std::vector<std::string> componentLabels_;
  std::vector<int> fillColors_;
  std::vector<int> lineColors_;



  //TDR STYLE
  void tdrStyle() {
    gStyle->SetPadTopMargin(0.05);
    gStyle->SetPadBottomMargin(0.13);
    gStyle->SetPadLeftMargin(0.16);
    gStyle->SetPadRightMargin(0.04);
    gStyle->SetPalette(1);
    gStyle->SetHistMinimumZero(1);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetCanvasColor(kWhite);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadColor(kWhite);
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameBorderSize(1);
    gStyle->SetFrameFillColor(0);
    gStyle->SetStatColor(kWhite);
    gStyle->SetTitleColor(1);
    gStyle->SetTitleFillColor(10);

    gStyle->SetOptTitle(0);

    gStyle->SetStatFont(42);
    gStyle->SetStatFontSize(0.04);///---> gStyle->SetStatFontSize(0.025);
    gStyle->SetTitleColor(1, "XYZ");
    gStyle->SetTitleFont(42, "XYZ");
    gStyle->SetTitleSize(0.06, "XYZ");
    // gStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
    // gStyle->SetTitleYSize(Float_t size = 0.02);
    gStyle->SetTitleXOffset(0.9);
    gStyle->SetTitleYOffset(1.25);
    // gStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

    // For the axis labels:

    gStyle->SetLabelColor(1, "XYZ");
    gStyle->SetLabelFont(42, "XYZ");
    gStyle->SetLabelOffset(0.007, "XYZ");
    gStyle->SetLabelSize(0.05, "XYZ");

    // For the axis:
    gStyle->SetAxisColor(1, "XYZ");
    gStyle->SetStripDecimals(kTRUE);
    gStyle->SetTickLength(0.03, "XYZ");
    gStyle->SetNdivisions(510, "XYZ");
    gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    gStyle->SetPadTickY(1);

}


};
