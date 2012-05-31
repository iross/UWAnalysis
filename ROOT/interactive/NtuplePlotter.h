#ifndef NTUPLE_PLOTTER
#define NTUPLE_PLOTTER

#include <string>
#include <vector>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
#include <TPad.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TCanvas.h>
class NtuplePlotter
{
 public:
  NtuplePlotter();
  ~NtuplePlotter();

  NtuplePlotter(std::string tree);

  TTree* getTree() {return tree;} 
  TFile* getFile() {return file;} 


  void registerFile(std::string file);

    TH1F* draw(std::string expression,std::string cut = "",double scale = 1.,std::string opt = "HIST",Color_t col = kRed,char* xlabel = "",char *ylabel = "",char *title = "CMS Preliminary");

    TH1F* draw(std::string expression,std::string cut,double scale,int bins,double min,double max,std::string opt,Color_t col = kRed,char* xlabel = "",char *ylabel = "",char *title = "CMS Preliminary");

    TH2F* draw2D(std::string expression,std::string cut,double scale,int binsX,double minX,double maxX,int binsY,double minY,double maxY,std::string opt,Color_t col = kRed,char* xlabel = "",char *ylabel = "",char *title = "CMS Preliminary");


  void compare(NtuplePlotter& file2,std::string expression,std::string cut1,std::string cut2,int bins,double min,double max,double scale,char* xlabel = "",char *ylabel = "",char *title ="",const char* e1 ="" ,const char* e2 ="");
   
  TGraphAsymmErrors* drawEfficiency(std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,int bins,double min,double max,Color_t col,char* xtitle  = "",char* ytitle = "",char* title = "CMS Preliminary");

  TCanvas* drawEfficiencySeries(std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,int bins,double min,double max,std::string cutDescriptions,char* xtitle  = "",char* ytitle = "",char* title = "CMS Preliminary");


  TH1F* drawEfficiencyH(std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,int bins,double min,double max,Color_t col,char* xtitle  = "",char* ytitle = "",char* title = "CMS Preliminary");


  TH1F* drawSignificance (NtuplePlotter& file2,std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,std::string sigType,int bins,double min,double max,Color_t col,char* xtitle,char* ytitle,char* title);

  //    TGraphAsymmErrors* drawEfficiency(std::string numVar,std::string denomVar,std::string numCuts,std::string denomCuts,Color_t col,char* xtitle,char* ytitle,char* title);

  double cutAcceptance(const char* cut_num,const char* cut_denom);

  TH1F* drawThresholdPlot(std::string var,std::string cuts,double min,double max,double step,char* xtitle = "CMS Preliminary",char* ytitle  = "",char* title = "CMS Preliminary");

  TGraphErrors*  rocCurve(NtuplePlotter& file2,TString var,TString direction, TString numCuts,TString denomCuts,double min,double max,double step,Color_t col1,Color_t col2 = kYellow,int style = 1,TString xlabel = "",TString ylabel = "",TString name = "roc");

  TGraphErrors*  sigCurve(NtuplePlotter& file2,std::string var,char direction, std::string numCuts,std::string denomCuts,double numWeight,double denomWeight,double min,double max,double step,Color_t col,char* xlabel = "norm. cut Value ",char *ylabel = "Significance",char *title = "CMS Preliminary" );

  void setAlias(std::string collection, std::string process, std::string alias);

  void setAlias(std::string ref,std::string alias);


  void addLabel(TCanvas * c,TString label,float x , float y,float size = 0.04);

  
 private:
  TChain *tree;
  TFile *file;


  

  void tokenize(const std::string& str,
		std::vector<std::string>& tokens,
		const std::string& delimiters = " ")
{
  // Skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
  
  while (std::string::npos != pos || std::string::npos != lastPos)
    {
      // Found a token, add it to the vector.
      tokens.push_back(str.substr(0, pos));
      // Skip delimiters.  Note the "not_of"
      lastPos = str.find_first_not_of(delimiters, pos);
      // Find next "non-delimiter"
      pos = str.find_first_of(delimiters, lastPos);
    }
}

  void partialTokenize(const std::string& str,
		       std::vector<std::string>& tokens,
		       const std::string& delimiters = " ")
{
  // Skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
  
  while (std::string::npos != pos || std::string::npos != lastPos)
    {
      // Found a token, add it to the vector.
      tokens.push_back(str.substr(lastPos, pos - lastPos));
      // Skip delimiters.  Note the "not_of"
      lastPos = str.find_first_not_of(delimiters, pos);
      // Find next "non-delimiter"
      pos = str.find_first_of(delimiters, lastPos);
    }
}


};

#endif
