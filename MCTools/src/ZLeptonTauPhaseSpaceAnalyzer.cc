// -*- C++ -*-
//
// Package:    ZLeptonTauPhaseSpaceAnalyzer
// Class:      ZLeptonTauPhaseSpaceAnalyzer
// 
/**\class ZLeptonTauPhaseSpaceAnalyzer ZLeptonTauPhaseSpaceAnalyzer.cc UWAnalysis/ZLeptonTauPhaseSpaceAnalyzer/src/ZLeptonTauPhaseSpaceAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Michail Bachtis
//         Created:  Fri Feb 26 18:44:19 CST 2010
// $Id: ZLeptonTauPhaseSpaceAnalyzer.cc,v 1.4 2011/01/28 17:35:58 bachtis Exp $
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

class ZLeptonTauPhaseSpaceAnalyzer : public edm::EDAnalyzer {
   public:
      explicit ZLeptonTauPhaseSpaceAnalyzer(const edm::ParameterSet&);
      ~ZLeptonTauPhaseSpaceAnalyzer();


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
  float leptonPt;
  float leptonEta;

  float tauPt;
  float tauEta;

  float diNuPt;
  float diNuMass;

  float diNuAngle;
  float diNuDr;

  float diNuLeptonAngle;
  float diNuLeptonDr;

  float diNuPt1;
  float diNuPt2;


  float tauNuPt;
  float tauNuAngle;
  float tauNuDr;

  float visMass;

  float *bPt;
  float *bEta;
  int bN;

  float mt;

  int br;  

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
ZLeptonTauPhaseSpaceAnalyzer::ZLeptonTauPhaseSpaceAnalyzer(const edm::ParameterSet& iConfig):
  motherBosonID_(iConfig.getParameter<int>("motherBosonID")),
  leptonID_(iConfig.getParameter<int>("leptonID")),
  fName_(iConfig.getParameter<std::string>("FileName"))  
{
   //now do what ever initialization is needed
  f = new TFile(fName_.c_str(),"RECREATE");
  t = new TTree("tree","Tree");

  bPt = new float[100];
  bEta = new float[100];
  bN=0;


  t->Branch("bN",&bN,"bN/I");
  t->Branch("bPt",bPt,"bPt[bN]/F");
  t->Branch("bEta",bEta,"bEta[bN]/F");


  t->Branch("leptonPt",&leptonPt,"leptonPt/F");
  t->Branch("leptonEta",&leptonEta,"leptonEta/F");

  t->Branch("tauPt",&tauPt,"tauPt/F");
  t->Branch("tauEta",&tauEta,"tauEta/F");

  t->Branch("diNuPt",&diNuPt,"diNuPt/F");
  t->Branch("diNuMass",&diNuMass,"diNuMass/F");
  t->Branch("diNuAngle",&diNuAngle,"diNuAngle/F");
  t->Branch("diNuDr",&diNuDr,"diNuDr/F");


  t->Branch("diNuLeptonAngle",&diNuLeptonAngle,"diNuLeptonAngle/F");
  t->Branch("diNuLeptonDr",&diNuLeptonDr,"diNuLeptonDr/F");


  t->Branch("diNuPt1",&diNuPt1,"diNuPt1/F");
  t->Branch("diNuPt2",&diNuPt2,"diNuPt2/F");

  t->Branch("tauNuPt",&tauNuPt,"tauNuPt/F");
  t->Branch("tauNuAngle",&tauNuAngle,"tauNuAngle/F");
  t->Branch("tauNuDr",&tauNuDr,"tauNuDr/F");

  t->Branch("visMass",&visMass,"visMass/F");
  t->Branch("mt",&mt,"mt/F");

  t->Branch("INBR",&br,"INBR/I");


}


ZLeptonTauPhaseSpaceAnalyzer::~ZLeptonTauPhaseSpaceAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
ZLeptonTauPhaseSpaceAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;

   edm::Handle<GenParticleCollection> genParticles;
   iEvent.getByLabel("genParticles", genParticles);

   br=0;

   GenParticleCollection::const_iterator p = genParticles->begin();
   bN=0;

   for (;p != genParticles->end(); ++p ) {

     if(abs((*p).pdgId())== 5&& abs(p->status()) == 3 ) {
       bPt[bN] =p->pt();
       bEta[bN]=p->eta();
       bN++;
     }

 
     if(abs((*p).pdgId())== motherBosonID_&& abs(p->status()) == 3 )
       {
	 printf("Found boson\n");
	 std::vector<math::XYZTLorentzVector> hadronicTaus;
	 std::vector<math::XYZTLorentzVector> leptonicTaus;
	 std::vector<math::XYZTLorentzVector> hadronicNus;
	 std::vector<math::XYZTLorentzVector> leptonicNus;

	 math::XYZTLorentzVector Boson((*p).px(),(*p).py(),(*p).pz(),(*p).energy());
	 for (GenParticle::const_iterator BosonIt=(*p).begin(); BosonIt != (*p).end(); BosonIt++){
	   if (abs((*BosonIt).pdgId()) == 15 && ((*BosonIt).status()==3)) //if it is a Tau and decayed
	     {
	       printf("Found tau\n");
	       for (GenParticle::const_iterator TauIt = (*BosonIt).begin(); TauIt != (*BosonIt).end(); TauIt++) {
		 if (abs((*TauIt).pdgId()) == 15 && ((*TauIt).status()==2)) //if it is a Tau and decayed
		   {   
		     math::XYZTLorentzVector visibleTau;
		     std::vector<math::XYZTLorentzVector >nus;

		     int leptonNumbers=0;
		     int leptonID=0;
		     for (GenParticle::const_iterator particle = (*TauIt).begin(); particle != (*TauIt).end(); particle++) {
		       int pdg = abs(particle->pdgId());

		       if(pdg==12 || pdg==14 || pdg==16) {
			 nus.push_back(particle->p4());			 
			 //			 printf("Found neutrino\n");
		       }
		       else {
			 visibleTau+=particle->p4();
			 if(pdg==11||pdg==13) {
			   leptonNumbers++;
			   leptonID=pdg;
			 }
		       }
		     }

		     if(leptonNumbers==1&&leptonID_==leptonID) {
		       leptonicTaus.push_back(visibleTau);
		       for(unsigned int i=0;i<nus.size();++i)
			 leptonicNus.push_back(nus[i]);
		     }
		     if(leptonNumbers==0) {
		       hadronicTaus.push_back(visibleTau);
		       for(unsigned int i=0;i<nus.size();++i)
			 hadronicNus.push_back(nus[i]);
		     }

		   }
	       }

	     }
	 }

	 if(hadronicTaus.size()==1 &&leptonicTaus.size()==1)
	   
	   {
	     br=1;
	     //////////////
	     leptonPt=leptonicTaus.at(0).pt();
	     leptonEta=leptonicTaus.at(0).eta();
	     
	     tauPt=hadronicTaus.at(0).pt();
	     tauEta=hadronicTaus.at(0).eta();
	     
	     math::XYZTLorentzVector diNu = leptonicNus.at(0)+leptonicNus.at(1);
	     diNuPt=diNu.pt();
	     diNuMass=diNu.M();
	     
	     diNuAngle=fabs(ROOT::Math::VectorUtil::Angle(leptonicNus.at(0),leptonicNus.at(1)));
	     diNuDr=fabs(ROOT::Math::VectorUtil::DeltaR(leptonicNus.at(0),leptonicNus.at(1)));
	     
	     diNuLeptonAngle=fabs(ROOT::Math::VectorUtil::Angle(diNu,leptonicTaus.at(0)));
	     diNuLeptonDr=fabs(ROOT::Math::VectorUtil::DeltaR(diNu,leptonicTaus.at(0)));;
	     
	     diNuPt1=leptonicNus.at(0).pt();
	     diNuPt2=leptonicNus.at(1).pt();
	     
	     visMass=(leptonicTaus.at(0)+hadronicTaus.at(0)).M();

	     math::XYZTLorentzVector fullHadTau = hadronicTaus.at(0)+hadronicNus.at(0);
	     math::XYZTLorentzVector fullLepTau = leptonicTaus.at(0)+diNu;

	     double ET1 = sqrt(1.77*1.77 +fullHadTau.pt()*fullHadTau.pt());
	     double ET2 = sqrt(1.77*1.77 +fullLepTau.pt()*fullLepTau.pt());



	     mt=sqrt(2*(1.77*1.77)+2*(ET1*ET2-+fullHadTau.pt()*fullLepTau.pt()*cos(ROOT::Math::VectorUtil::DeltaPhi(fullHadTau,fullLepTau))));
	     
	     tauNuPt=hadronicNus.at(0).pt();
	     tauNuAngle=fabs(ROOT::Math::VectorUtil::Angle(hadronicTaus.at(0),hadronicNus.at(0)));
	     tauNuDr=fabs(ROOT::Math::VectorUtil::DeltaR(hadronicTaus.at(0),hadronicNus.at(0)));
	     
	     ///////////////
	   }

       }
   }

     t->Fill();


}

void 
ZLeptonTauPhaseSpaceAnalyzer::endJob() 
{
  f->Write();
  f->Close();

}





//define this as a plug-in
DEFINE_FWK_MODULE(ZLeptonTauPhaseSpaceAnalyzer);
