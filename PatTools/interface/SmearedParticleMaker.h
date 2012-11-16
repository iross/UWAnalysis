#ifndef TauAnalysis_SmearedParticleMaker
#define TauAnalysis_SmearedParticleMaker

/* Smeared Particle Maker 
Module that changes the energy scale PT, ETA 
for a general PAT Particle 
Author : Michail Bachtis 
University of Wisconsin
*/
// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Random/RandGauss.h"
#include <TFile.h>
#include <TH1F.h>

#include <TRandom.h>
#include <TRandom3.h>

/*Helper classes to return the generated Lorentz Vector in case of leptons and jets*/

template <typename T>
class GenParticleRetriever {
 public:
  GenParticleRetriever() {}
  ~GenParticleRetriever() {}
  GenParticleRetriever(const T& particle) {
    if(particle.genParticle()!=0)
      p4_ = particle.genParticle()->p4();
    else
      p4_ = particle.p4();
  }

  math::XYZTLorentzVector genP4() { return p4_; }
  
 private:
  math::XYZTLorentzVector p4_;
};

template <typename T>
class GenJetRetriever {
 public:
  GenJetRetriever() {}
  ~GenJetRetriever() {}
  GenJetRetriever(const T& particle) {
    if(particle.genJet()!=0)
      p4_ = particle.genJet()->p4();
    else
      p4_ = particle.p4();
  }
  math::XYZTLorentzVector genP4() { return p4_; }
 private:
  math::XYZTLorentzVector p4_;
};


/*end helper classes*/


template <typename T,typename G>
class SmearedParticleMaker  {
   public:
  explicit SmearedParticleMaker(const edm::ParameterSet& iConfig):
    //    fileName_(iConfig.getParameter<edm::FileInPath>("fileName")),  
    smearMCParticle_(iConfig.getParameter<bool>("smearMCParticle")),  
    energyScale_(iConfig.getParameter<double>("energyScale")),
    deltaEta_(iConfig.getParameter<double>("deltaEta")),
    deltaPhi_(iConfig.getParameter<double>("deltaPhi")),
    deltaPtB_(iConfig.getParameter<double>("deltaPtB")),
    deltaPtE_(iConfig.getParameter<double>("deltaPtE")),
    moduleLabel_(iConfig.getParameter<std::string>("@module_label"))
    {
      random = new TRandom3(356784);

    }

  ~SmearedParticleMaker() {

  }
    
     void smear(T& object)
       {


	 math::XYZTLorentzVector vToSmear;
	 
	 //Decide which LV to smear
	 if(smearMCParticle_){
	   //check if it matched to a gen jet or a gen particle
	   G mcRetriever(object);
	   vToSmear = mcRetriever.genP4(); //If it is not matched it will return the reco p4
	 }
	 else {
	   vToSmear = object.p4();
	 }
      
	 //apply energy scale!
	 object.setP4(energyScale_*vToSmear);
	 
	 //apply pt and eta and phi DISPLACEMENTS

	 if(deltaPtB_>0) {
	   if(fabs(object.eta())<1.442) {
	     math::PtEtaPhiMLorentzVector vec(object.pt()*(1+random->Gaus(0.0,deltaPtB_)),object.eta()+deltaEta_,object.phi()+deltaPhi_,object.mass());
	     math::XYZTLorentzVector cartVec(vec.px(),vec.py(),vec.pz(),vec.energy());
	     object.setP4(cartVec);
	   }
	   else
	     {
	       math::PtEtaPhiMLorentzVector vec(object.pt()*(1+random->Gaus(0.0,deltaPtE_)),object.eta()+deltaEta_,object.phi()+deltaPhi_,object.mass());
	       math::XYZTLorentzVector cartVec(vec.px(),vec.py(),vec.pz(),vec.energy());
	       object.setP4(cartVec);
	       
	     }


	 }
	 else
	   {

	   if(fabs(object.eta())<1.442) {
	     math::PtEtaPhiMLorentzVector vec(object.pt()/(1+random->Gaus(0.0,deltaPtB_)),object.eta()+deltaEta_,object.phi()+deltaPhi_,object.mass());
	     math::XYZTLorentzVector cartVec(vec.px(),vec.py(),vec.pz(),vec.energy());
	     object.setP4(cartVec);
	   }
	   else
	     {
	       math::PtEtaPhiMLorentzVector vec(object.pt()/(1+random->Gaus(0.0,deltaPtE_)),object.eta()+deltaEta_,object.phi()+deltaPhi_,object.mass());
	       math::XYZTLorentzVector cartVec(vec.px(),vec.py(),vec.pz(),vec.energy());
	       object.setP4(cartVec);
	       
	     }



	   }

       }


 protected:     

    


      // ----------member data ---------------------------
      bool smearMCParticle_;        //Smear MC particle instead of reconstructed particle
      //Flat smearing
      double energyScale_;          //energy Scale 
      double deltaEta_;             //delta Eta
      double deltaPhi_;              //delta phi
      double deltaPtB_;              //delta Pt
      double deltaPtE_;              //delta Pt
      std::string moduleLabel_;
      
      TRandom *random;

};


#endif
