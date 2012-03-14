// -*- C++ -*-
//
// Package:    EventSummary
// Class:      EventSummary
// 
/**\class EventSummary EventSummary.cc CIA/EventSummary/src/EventSummary.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Michail Bachtis
//         Created:  Wed Oct 21 10:12:28 CDT 2009
// $Id: EventSummary.h,v 1.1 2010/05/14 20:27:16 bachtis Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//
// class decleration
//

class EventSummary : public edm::EDAnalyzer {
   public:
      explicit EventSummary(const edm::ParameterSet&);
      ~EventSummary();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
  
  DQMStore *store;
  edm::Service<TFileService> fs;
  std::vector<std::string> histos_;
};


