// -*- C++ -*-
//
// Package:    ZLeptonTauPhaseSpaceAnalyzer
// Class:      ZLeptonTauPhaseSpaceAnalyzer
// 
/**\class ZLLPhaseSpaceAnalyzer ZLLPhaseSpaceAnalyzer.cc UWAnalysis/ZLLPhaseSpaceAnalyzer/src/ZLLPhaseSpaceAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Michail Bachtis
//         Created:  Fri Feb 26 18:44:19 CST 2010
// $Id: ZLLPhaseSpaceAnalyzer.cc,v 1.1.1.1 2010/04/16 10:07:11 bachtis Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TTree.h"
#include "TFile.h"

//#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration
//

class ZLLPhaseSpaceAnalyzer : public edm::EDAnalyzer {
   public:
      explicit ZLLPhaseSpaceAnalyzer(const edm::ParameterSet&);
      ~ZLLPhaseSpaceAnalyzer();


   private:

      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
  int motherBosonID_;
  int leptonID_;
  std::string fName_;
  
 
  TFile *f;
  TTree *t;


  //---------ntuple data----------------------------------
  float leptonPt1;
  float leptonEta1;
  float leptonPt2;
  float leptonEta2;
  float visMass;


  class Sorter{
  public:
    Sorter(){}
    ~Sorter(){}
    bool operator()(math::XYZTLorentzVector p1,math::XYZTLorentzVector p2)
    {
      return p1.pt() > p2.pt();
    } 

  };

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ZLLPhaseSpaceAnalyzer::ZLLPhaseSpaceAnalyzer(const edm::ParameterSet& iConfig):
  motherBosonID_(iConfig.getParameter<int>("motherBosonID")),
  leptonID_(iConfig.getParameter<int>("leptonID")),
  fName_(iConfig.getParameter<std::string>("FileName"))  
{
   //now do what ever initialization is needed
  f = new TFile(fName_.c_str(),"RECREATE");
  t = new TTree("tree","Tree");

  t->Branch("leptonPt1",&leptonPt1,"leptonPt1/F");
  t->Branch("leptonEta1",&leptonEta1,"leptonEta1/F");
  t->Branch("leptonPt2",&leptonPt2,"leptonPt2/F");
  t->Branch("leptonEta2",&leptonEta2,"leptonEta2/F");
  t->Branch("visMass",&visMass,"visMass/F");
}


ZLLPhaseSpaceAnalyzer::~ZLLPhaseSpaceAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
ZLLPhaseSpaceAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;

   edm::Handle<GenParticleCollection> genParticles;
   iEvent.getByLabel("genParticles", genParticles);

   GenParticleCollection::const_iterator p = genParticles->begin();
  
   for (;p != genParticles->end(); ++p ) {
 
     if(abs((*p).pdgId())== motherBosonID_&& abs(p->status()) == 3 )
       {
	 printf("Found boson\n");
	 std::vector<math::XYZTLorentzVector> leptons;

	 math::XYZTLorentzVector Boson((*p).px(),(*p).py(),(*p).pz(),(*p).energy());
	 for (GenParticle::const_iterator BosonIt=(*p).begin(); BosonIt != (*p).end(); BosonIt++){
	   if (abs((*BosonIt).pdgId()) == leptonID_ && ((*BosonIt).status()==3)) //if it is a Tau and decayed
	     {
	       leptons.push_back(BosonIt->p4());
	     }
	 }


	 if(leptons.size()==2)
	   {
	     Sorter sorter;
	     std::sort(leptons.begin(),leptons.end(),sorter);

	     leptonPt1 = leptons.at(0).pt();
	     leptonEta1 = leptons.at(0).eta();
	     leptonPt2 = leptons.at(1).pt();
	     leptonEta2 = leptons.at(1).eta();
	     visMass = (leptons.at(0)+leptons.at(1)).M();
	     t->Fill();
	     	       
	   }




       }
   }





}

void 
ZLLPhaseSpaceAnalyzer::endJob() 
{
  f->Write();
  f->Close();

}





//define this as a plug-in
DEFINE_FWK_MODULE(ZLLPhaseSpaceAnalyzer);
