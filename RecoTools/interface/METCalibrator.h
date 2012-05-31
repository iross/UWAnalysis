// Original Author:  Michail Bachtis
//         Created:  Sun Jan 31 15:04:57 CST 2010
#ifndef RecoTools_METCalibrator
#define RecoTools_METCalibrator

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "UWAnalysis/RecoTools/interface/RecoilCorrector.hh"
#include "Math/GenVector/VectorUtil.h"
#include <TFormula.h>
#include <TRandom3.h>
#include "Utilities/General/interface/FileInPath.h"

//
// class decleration



class METCalibrator  {
   public:
  METCalibrator() {}

  METCalibrator(const edm::ParameterSet& iConfig):
    calibrate_(iConfig.getParameter<bool>("applyCalibration")),
    calibrationScheme_(iConfig.getParameter<std::string>("calibrationScheme")),
    responseU1_(iConfig.getParameter<std::string>("responseU1")),
    responseU2_(iConfig.getParameter<std::string>("responseU2")),
    resolutionU1_(iConfig.getParameter<std::string>("resolutionU1")),
    resolutionU2_(iConfig.getParameter<std::string>("resolutionU2")),
    responseMCU1_(iConfig.getParameter<std::string>("responseMCU1")),
    responseMCU2_(iConfig.getParameter<std::string>("responseMCU2")),
    resolutionMCU1_(iConfig.getParameter<std::string>("resolutionMCU1")),
    resolutionMCU2_(iConfig.getParameter<std::string>("resolutionMCU2")),
    shiftScale_(iConfig.getUntrackedParameter<double>("shiftScale",0.0)),
    shiftRes_(iConfig.getUntrackedParameter<double>("shiftRes",0.0))
  {

    //create the formulas

    //check if we use Phil's Recipe

    if(calibrationScheme_.find("Phil") == 0 ) {
      //initialize Phil's corrector 

      edm::FileInPath fileDZ0("UWAnalysis/Configuration/data/recoilfit_datamm_0jet.root");
      edm::FileInPath fileDZ1("UWAnalysis/Configuration/data/recoilfit_datamm_1jet.root");
      edm::FileInPath fileDZ2("UWAnalysis/Configuration/data/recoilfit_datamm_2jet.root");
      edm::FileInPath fileZ0("UWAnalysis/Configuration/data/recoilfit_zmm42X_0jet.root");
      edm::FileInPath fileZ1("UWAnalysis/Configuration/data/recoilfit_zmm42X_1jet.root");
      edm::FileInPath fileZ2("UWAnalysis/Configuration/data/recoilfit_zmm42X_2jet.root");
      edm::FileInPath fileW0("UWAnalysis/Configuration/data/recoilfit_wjets_0jet.root");
      edm::FileInPath fileW1("UWAnalysis/Configuration/data/recoilfit_wjets_1jet.root");
      edm::FileInPath fileW2("UWAnalysis/Configuration/data/recoilfit_wjets_2jet.root");
      edm::FileInPath fileH0("UWAnalysis/Configuration/data/recoilfit_higgs_0jet.root");
      edm::FileInPath fileH1("UWAnalysis/Configuration/data/recoilfit_higgs_1jet.root");
      edm::FileInPath fileH2("UWAnalysis/Configuration/data/recoilfit_higgs_2jet.root");


      philCorrectorZ0 = new RecoilCorrector(fileZ0.fullPath());
      philCorrectorZ0->addMCFile(fileZ0.fullPath());
      philCorrectorZ0->addDataFile(fileDZ0.fullPath());

      philCorrectorZ1 = new RecoilCorrector(fileZ1.fullPath());
      philCorrectorZ1->addMCFile(fileZ1.fullPath());
      philCorrectorZ1->addDataFile(fileDZ1.fullPath());

      philCorrectorZ2 = new RecoilCorrector(fileZ2.fullPath());
      philCorrectorZ2->addMCFile(fileZ2.fullPath());
      philCorrectorZ2->addDataFile(fileDZ2.fullPath());

      //////////////////////////
      philCorrectorW0= new RecoilCorrector(fileW0.fullPath());
      philCorrectorW0->addMCFile(fileZ0.fullPath());
      philCorrectorW0->addDataFile(fileDZ0.fullPath());

      philCorrectorW1= new RecoilCorrector(fileW1.fullPath());
      philCorrectorW1->addMCFile(fileZ1.fullPath());
      philCorrectorW1->addDataFile(fileDZ1.fullPath());


      philCorrectorW2= new RecoilCorrector(fileW2.fullPath());
      philCorrectorW2->addMCFile(fileZ2.fullPath());
      philCorrectorW2->addDataFile(fileDZ2.fullPath());

      //////////////////////////
      philCorrectorH0= new RecoilCorrector(fileH0.fullPath());
      philCorrectorH0->addMCFile(fileZ0.fullPath());
      philCorrectorH0->addDataFile(fileDZ0.fullPath());


      philCorrectorH1= new RecoilCorrector(fileH1.fullPath());
      philCorrectorH1->addMCFile(fileZ1.fullPath());
      philCorrectorH1->addDataFile(fileDZ1.fullPath());


      philCorrectorH2= new RecoilCorrector(fileH2.fullPath());
      philCorrectorH2->addMCFile(fileZ2.fullPath());
      philCorrectorH2->addDataFile(fileDZ2.fullPath());

    }
    else
      {
	//initialize Mike's corrector
	responseFU1 = new TFormula("responseFU1",responseU1_.c_str());
	responseFU2 = new TFormula("responseFU2",responseU2_.c_str());
	resolutionFU1 = new TFormula("resolutionFU1",resolutionU1_.c_str());
	resolutionFU2 = new TFormula("resolutionFU2",resolutionU2_.c_str());
	
	responseMCFU1 = new TFormula("responseMCFU1",responseMCU1_.c_str());
	responseMCFU2 = new TFormula("responseMCFU2",responseMCU2_.c_str());
	resolutionMCFU1 = new TFormula("resolutionMCFU1",resolutionMCU1_.c_str());
	resolutionMCFU2 = new TFormula("resolutionMCFU2",resolutionMCU2_.c_str());
    
      }

    random = new TRandom3(101982);




  }
  
  ~METCalibrator() {}


  reco::Candidate::LorentzVector calibrate(const reco::Candidate::LorentzVector& met,
					   const reco::Candidate::LorentzVector& leg1,
					   const reco::Candidate::LorentzVector& leg2,
					   const reco::GenParticleCollection* genParticles,
					   int jets) {

    if(!calibrate_) return met;

    if(calibrationScheme_.find("Phil") ==0)
      return calibratePhil(met,leg1,leg2,genParticles,jets);
    else
      return calibrate(met,leg1,leg2,genParticles);

  }


  reco::Candidate::LorentzVector calibratePhil(const reco::Candidate::LorentzVector& metV,
					   const reco::Candidate::LorentzVector& leg1,
					   const reco::Candidate::LorentzVector& leg2,
					   const reco::GenParticleCollection* genParticles,
					   int njet) {


    double met =metV.pt(); 
    double metphi=metV.phi();
    double lGenPt;
    double lGenPhi; 
    double lepPt =(leg1+leg2).pt() ;
    double lepPhi=(leg1+leg2).phi();
    double iU1=0.0;
    double iU2=0.0;


    if(calibrationScheme_=="Phil_W") {
    lepPt =leg1.pt() ;
    lepPhi=leg1.phi();
    }


    std::pair<bool,math::XYZVector> bosonResult = getGeneratedBoson(genParticles);
    if(!bosonResult.first) {
      //      printf("Boson NOT found/cannot calibrate\n");
      return metV;
    }
    
    lGenPt = sqrt(bosonResult.second.x()*bosonResult.second.x()+bosonResult.second.y()*bosonResult.second.y());
    lGenPhi= bosonResult.second.Phi();



    if(calibrationScheme_=="Phil_Z" &&njet==0)
      philCorrectorZ0->CorrectType2(met,metphi,lGenPt,lGenPhi,lepPt,lepPhi,iU1,iU2,shiftScale_,shiftRes_,njet); 
    if(calibrationScheme_=="Phil_Z" &&njet==1)
      philCorrectorZ1->CorrectType2(met,metphi,lGenPt,lGenPhi,lepPt,lepPhi,iU1,iU2,shiftScale_,shiftRes_,njet); 
    if(calibrationScheme_=="Phil_Z" &&njet>=2)
      philCorrectorZ2->CorrectType2(met,metphi,lGenPt,lGenPhi,lepPt,lepPhi,iU1,iU2,shiftScale_,shiftRes_,2); 

    if(calibrationScheme_=="Phil_W" &&njet==0)
      philCorrectorW0->CorrectType2(met,metphi,lGenPt,lGenPhi,lepPt,lepPhi,iU1,iU2,shiftScale_,shiftRes_,njet); 
    if(calibrationScheme_=="Phil_W" &&njet==1)
      philCorrectorW1->CorrectType2(met,metphi,lGenPt,lGenPhi,lepPt,lepPhi,iU1,iU2,shiftScale_,shiftRes_,njet); 
    if(calibrationScheme_=="Phil_W" &&njet>=2)
      philCorrectorW2->CorrectType2(met,metphi,lGenPt,lGenPhi,lepPt,lepPhi,iU1,iU2,shiftScale_,shiftRes_,2); 


    if(calibrationScheme_=="Phil_H" &&njet==0)
      philCorrectorH0->CorrectType2(met,metphi,lGenPt,lGenPhi,lepPt,lepPhi,iU1,iU2,shiftScale_,shiftRes_,njet); 
    if(calibrationScheme_=="Phil_H" &&njet==1)
      philCorrectorH1->CorrectType2(met,metphi,lGenPt,lGenPhi,lepPt,lepPhi,iU1,iU2,shiftScale_,shiftRes_,njet); 
    if(calibrationScheme_=="Phil_H" &&njet>=2)
      philCorrectorH2->CorrectType2(met,metphi,lGenPt,lGenPhi,lepPt,lepPhi,iU1,iU2,shiftScale_,shiftRes_,2); 
 

    math::PtEtaPhiMLorentzVector a(met,0.0,metphi,0.0);

    reco::Candidate::LorentzVector b(a.px(),a.py(),a.pz(),a.energy());



    //    printf("MET = %f %f\n",metV.pt(),b.pt());

    return b;
    


  }

  reco::Candidate::LorentzVector calibrate(const reco::Candidate::LorentzVector& met,
					   const reco::Candidate::LorentzVector& leg1,
					   const reco::Candidate::LorentzVector& leg2,
					   const reco::GenParticleCollection* genParticles) {


    math::XYZVector residualPart(0.,0.,0.);
    math::XYZVector recoil(0.,0.,0.);
    math::XYZVector metXY(met.px(),met.py(),0.);

    if(calibrationScheme_ =="BothLegs" || calibrationScheme_ == "BothLegsTauTau") {
      residualPart = math::XYZVector(leg1.x()+leg2.x(),leg1.y()+leg2.y(),0.0);
      recoil       = -metXY - residualPart;
    }
    else if(calibrationScheme_ =="OneLeg") {
      residualPart = math::XYZVector(leg1.x(),leg1.y(),0.0);
      recoil       = -metXY - residualPart;
    }
    else {
      return met;
    }



    if(!calibrate_) return met;



    //OK now get the generated particle

    std::pair<bool,math::XYZVector> bosonResult = getGeneratedBoson(genParticles);
    if(!bosonResult.first) {
      //      printf("Boson NOT found/cannot calibrate\n");
      return met;
    }
    math::XYZVector boson = bosonResult.second;

    math::XYZVector verticalBoson(-boson.y(),boson.x(),0.0);

    //OK now get the projections

    
    double U1 = recoil.Dot(boson)/boson.r();
    double U2 = recoil.Dot(verticalBoson)/verticalBoson.r();



    //correct for the response-U2 is corrected additively since it is independent of pt
    U1*= responseFU1->Eval(boson.rho())/responseMCFU1->Eval(boson.rho());

    //get the resolutions
    float sigmaData1 = resolutionFU1->Eval(boson.rho());
    float sigmaData2 = resolutionFU2->Eval(boson.rho());
    float sigmaMC1 = resolutionMCFU1->Eval(boson.rho());
    float sigmaMC2 = resolutionMCFU2->Eval(boson.rho());

    //create the additional smearing factors needed to match the data 
    float smearingFactor1 = sqrt(fabs(sigmaData1*sigmaData1-sigmaMC1*sigmaMC1));
    float smearingFactor2 = sqrt(fabs(sigmaData2*sigmaData2-sigmaMC2*sigmaMC2));



    //apply smearing
    U1+= random->Gaus(0.0,smearingFactor1);
    U2+= random->Gaus(responseFU2->Eval(boson.rho())-responseMCFU2->Eval(boson.rho()),smearingFactor2);
    
    //recreate the recoil
    math::XYZVector calibratedRecoil = U1*boson/boson.r() + U2*verticalBoson/verticalBoson.r();
    //recreate the met

    math::XYZVector out = -calibratedRecoil - residualPart;

    reco::Candidate::LorentzVector metOut(out.x(),out.y(),0.0,out.r());


    return metOut;
  }

					   


   private:


  std::pair<bool,math::XYZVector> getGeneratedBoson(const reco::GenParticleCollection* genParticles) {
    math::XYZVector out(0.,0.,0.);
    bool found=false;
    std::vector<int> ids;
    if(calibrationScheme_  == "BothLegs" || calibrationScheme_  == "BothLegsTauTau" ||calibrationScheme_=="Phil_Z"||calibrationScheme_=="Phil_H")
      {
	ids.push_back(23);
	ids.push_back(22);
	ids.push_back(25);
	ids.push_back(35);
	ids.push_back(36);
      }       
    if(calibrationScheme_  == "OneLeg"||calibrationScheme_  == "Phil_W")
      {
	ids.push_back(24);
      }       
    
    //get the boson with the highest mass
    double maxMass=0.0;
    if(genParticles!=0&& genParticles->size()>0)
    for(reco::GenParticleCollection::const_iterator i = genParticles->begin();
	i!=genParticles->end();
	++i) 
      for(unsigned int j=0;j<ids.size();++j)
	if(abs(i->pdgId())==ids.at(j) &&i->mass()>maxMass) 
	  {
	    maxMass = i->mass();
	    out = math::XYZVector(i->px(),i->py(),0.0);
	    found=true;
	    if(calibrationScheme_ =="BothLegsTauTau") {
	      int taus=0;
	      for(unsigned int k=0;k<i->numberOfDaughters();++k)
		if(abs(i->daughter(k)->pdgId())==15)
		  taus++;
	      if(taus==0)
		found=false;
	    }
	  }

    //    printf("Found boson with mass=%f\n",maxMass);

    return std::make_pair(found,out);

  }

  bool calibrate_;
  std::string calibrationScheme_;
  std::string responseU1_;
  std::string responseU2_;
  std::string resolutionU1_;
  std::string resolutionU2_;

  std::string responseMCU1_;
  std::string responseMCU2_;
  std::string resolutionMCU1_;
  std::string resolutionMCU2_;

  TFormula* responseFU1;
  TFormula* responseFU2;
  TFormula* resolutionFU1;
  TFormula* resolutionFU2;
  TFormula* responseMCFU1;
  TFormula* responseMCFU2;
  TFormula* resolutionMCFU1;
  TFormula* resolutionMCFU2;


  TRandom *random;


  RecoilCorrector* philCorrectorZ0;
  RecoilCorrector* philCorrectorZ1;
  RecoilCorrector* philCorrectorZ2;
  //////////////////////////////////////////
  RecoilCorrector* philCorrectorW0;
  RecoilCorrector* philCorrectorW1;
  RecoilCorrector* philCorrectorW2;
  //////////////////////////////////////////
  RecoilCorrector* philCorrectorH0;
  RecoilCorrector* philCorrectorH1;
  RecoilCorrector* philCorrectorH2;



  double shiftScale_;
  double shiftRes_;
};

#endif
