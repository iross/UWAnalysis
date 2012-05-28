#ifndef PHYSICS_DRAWER
#define PHYSICS_DRAWER

#include "NtuplePlotter.h"
#include <vector>
#include <string>
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1F.h"
#include "THStack.h"
#include <vector>
class PhysicsDrawer
{
 public:
  PhysicsDrawer();
  ~PhysicsDrawer();

  void addPlotter(NtuplePlotter* w ,std::string preCut,std::string label,Color_t color ,int signal,std::string opt = "MC");

  
   TCanvas* draw(const std::string& expression,
		 const std::string& cut,
		 int bins,
		 double min,
		 double max,
		 char* xlabel = "",
		 char *ylabel = "");

   TCanvas* drawStacked(const std::string& expression,
			const std::string& cut,
			const std::string& lumi,
			int bins,
			double min,
			double max,
			char* xlabel = "",
			char *ylabel = "");


   void setAlias(std::string ref,std::string alias);

 private:
   std::vector<NtuplePlotter*> wrappers;
   std::vector<std::string> labels;
   std::vector<std::string> opts;
   std::vector<std::string> preCuts;
   std::vector<Color_t> colors;
   std::vector<int> types;
};

#endif
