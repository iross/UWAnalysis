// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


#include <TFile.h>
#include <TTree.h>


//
// class decleration
//
template<typename T>
class SimpleTreeMaker : public edm::EDAnalyzer {
   public:
       explicit SimpleTreeMaker(const edm::ParameterSet& iConfig):
	 src_(iConfig.getParameter<edm::InputTag>("src")),
	 vars_(iConfig.getParameter<std::vector<edm::ParameterSet> >("vars")),
	 //	 fileName_(iConfig.getParameter<std::string>("fileName")),
	 //	 filters_(iConfig.getUntrackedParameter<std::vector<std::string> >("Filters")),
	 useLeading_(iConfig.getUntrackedParameter<bool>("AddLeadingCandsOnly",false))
	 {
	   //	   f = new TFile(fileName_.c_str(),"recreate");
	   edm::Service<TFileService> fs;
	   t = fs->make<TTree>( "tree"  , "");
	   //	   t = new TTree("tree",""); 

	   values = new float[200];

	   for(unsigned int i=0;i<vars_.size();++i) {

	     values[i]          = 0;
	     std::string tag    = vars_[i].getParameter<std::string>("tag");
	     std::string method = vars_[i].getParameter<std::string>("method"); 
	     methods.push_back( method );
	     vars.push_back(new StringObjectFunction<T>(method));
	     t->Branch(tag.c_str(),&values[i],(tag+"/F").c_str());
	   }

	   //Add event and RUN BRANCHING	 
	   t->Branch("EVENT",&EVENT,"EVENT/i");
	   t->Branch("RUN",&RUN,"RUN/i");
	   t->Branch("LUMI",&LUMI,"LUMI/i");
	 }

       ~SimpleTreeMaker()
	 { }
       
   private:


       virtual void endJob()
	 {
/* 	   f->cd(); */
/* 	   printf("saving weight info\n");  */
/* 	   DQMStore* store = &*edm::Service<DQMStore>(); */
/* 	   if(filters_.size()>0) { */
/* 	     TH1F *tmp = new TH1F("EventSummary","EventSummary",filters_.size(),0,filters_.size()); */
	     
/* 	     for(unsigned int i=0;i<filters_.size();++i) { */
/* 	       MonitorElement *tmpM = store->get(filters_[i]); */
/* 	       tmp->SetBinContent(i+1,tmpM->getFloatValue()); */
/* 	       tmp->GetXaxis()->SetBinLabel(i+1,filters_[i].c_str()); */
/* 	     } */

/* 	     tmp->Write(); */
/* 	   } */
/* 	   f->Write(); */
/* 	   f->Close(); */
/* 	   printf("Clearing memory\n"); */
	   
/* 	   for(unsigned int i=0;i<vars.size();++i) { */
/* 	     StringObjectFunction<T>* tmp = vars[i]; */
/* 	     vars[i]=0; */
/* 	     delete tmp; */
/* 	   } */
	   
	     
	  
	 }




       virtual void analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup)
	{
	  std::auto_ptr<std::vector<T> > out(new std::vector<T>);
	  edm::Handle<std::vector<T> > obj;

	  EVENT  = iEvent.id().event();
	  RUN    = iEvent.id().run();
	  LUMI   = 0;//iEvent.id().luminosityBlock();

	  if(iEvent.getByLabel(src_,obj))  {
	    unsigned int objToProcess=0;
	    if(useLeading_)
	      {
		if(obj->size()>0)
		  objToProcess=1;
	      }
	    else
	      {
		objToProcess=obj->size();
	      }

	    for(unsigned int i=0;i<objToProcess;++i){
	      T object = obj->at(i);

	      //fill the tree
	      for(unsigned int j=0;j<vars.size();++j) {
		values[j]=0;
		values[j] = (*vars[j])(object);
	      }
	      t->Fill();
	    }
	  }

	}

      // ----------member data ---------------------------
      edm::InputTag src_;
      std::vector<edm::ParameterSet> vars_;
      std::vector<StringObjectFunction<T>* > vars;
      //      std::string fileName_;
      //      TFile *f;
      TTree *t;
      float *values;
      std::vector<std::string> methods;
      //      std::vector<std::string> filters_;
      bool useLeading_;

      //add run event data
      unsigned int EVENT;
      unsigned int RUN;
      unsigned int LUMI;
 

};


