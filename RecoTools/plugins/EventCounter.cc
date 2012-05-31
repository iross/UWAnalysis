#include "UWAnalysis/RecoTools/plugins/EventCounter.h"

EventCounter::EventCounter(const edm::ParameterSet& iConfig):
  name_(iConfig.getParameter<std::string>("name"))
{
     DQMStore* store = &*edm::Service<DQMStore>();
     evCount = store->bookFloat(name_.c_str());
     if(evCount)
       {
	 evCount->Fill(0);
       }

}


EventCounter::~EventCounter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
EventCounter::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   if(evCount)
     {
       evCount->Fill(evCount->getFloatValue()+1.0);
     }
}

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
DEFINE_FWK_MODULE(EventCounter);
