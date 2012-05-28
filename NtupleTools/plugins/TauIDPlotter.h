//HadronicTauEfficiencyAnalyzer
//Module that  measures performance of final  
//selected Tau candidates


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <TH1F.h>
#include <TProfile.h>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


//
// class decleration
//


class TauIDPlotter : public edm::EDAnalyzer {
   public:
      explicit TauIDPlotter(const edm::ParameterSet&);
      ~TauIDPlotter();

   private:
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob();
      
      edm::InputTag src_;
      edm::InputTag srcVertices_;
      edm::InputTag ref_;
      std::vector<std::string> discriminators_;
      double ptThres_;
      double ptNum_;
      double matchDR_;
      int bins_;
      double min_;
      double max_;

      std::vector<TH1F*> histos;
      std::vector<TH1F*> histosEta;
      std::vector<TH1F*> histosL;
      std::vector<TH1F*> histosV;
      std::vector<TProfile*> histosR;

      TH1F* rawSummary;
      TH1F* rawSummaryL;
      TH1F* rawSummaryEvent;

      edm::Service<TFileService> fs;


};
