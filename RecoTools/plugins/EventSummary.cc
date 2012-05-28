#include "UWAnalysis/RecoTools/plugins/EventSummary.h"

EventSummary::EventSummary(const edm::ParameterSet& iConfig):
  histos_(iConfig.getUntrackedParameter<std::vector<std::string> >("src"))
{
}


EventSummary::~EventSummary()
{

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
EventSummary::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
}


// ------------ method called once each job just before starting event loop  ------------
void 
EventSummary::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EventSummary::endJob() {

  store = &*edm::Service<DQMStore>();
  std::vector<std::string> filters;
  if(histos_.size()==0)
   filters = store->getMEs();
  else
    filters = histos_;

  //Preclean filters
  std::vector<std::string> cleanFilters;

      for(unsigned int i=0;i<filters.size();++i)
	if(filters[i].size()>0)
	{
	  MonitorElement *tmp = store->get(filters[i]);
	  if(tmp)
	    cleanFilters.push_back(filters[i]);
	  else
	    printf("Not Found Filter %s\n",filters[i].c_str());
	}

  if(cleanFilters.size()>0)
    {
      TH1F * results = fs->make<TH1F>( "results"  , "Filter Results", filters.size(),  0.,filters.size());
      results->Sumw2();
      for(unsigned int i=0;i<cleanFilters.size();++i)
	if(cleanFilters[i].size()>0)
	{
	  MonitorElement *tmp = store->get(cleanFilters[i]);
	  if(tmp->kind()==MonitorElement::DQM_KIND_REAL)
	    {
	      results->SetBinContent(i+1,tmp->getFloatValue());
	      results->GetXaxis()->SetBinLabel(i+1,cleanFilters[i].c_str());
	    }
	}

    }
}


#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(EventSummary);
