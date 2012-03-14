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

#include "Math/GenVector/VectorUtil.h"
#include <TFormula.h>
#include <TRandom3.h>

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
    resolutionMCU2_(iConfig.getParameter<std::string>("resolutionMCU2"))

  {

    //create the formulas
    responseFU1 = new TFormula("responseFU1",responseU1_.c_str());
    responseFU2 = new TFormula("responseFU2",responseU2_.c_str());
    resolutionFU1 = new TFormula("resolutionFU1",resolutionU1_.c_str());
    resolutionFU2 = new TFormula("resolutionFU2",resolutionU2_.c_str());

    responseMCFU1 = new TFormula("responseMCFU1",responseMCU1_.c_str());
    responseMCFU2 = new TFormula("responseMCFU2",responseMCU2_.c_str());
    resolutionMCFU1 = new TFormula("resolutionMCFU1",resolutionMCU1_.c_str());
    resolutionMCFU2 = new TFormula("resolutionMCFU2",resolutionMCU2_.c_str());
    
    random = new TRandom3(101982);
  }
  
  ~METCalibrator() {}

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
    if(!bosonResult.first) return met;

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
    if(calibrationScheme_  == "BothLegs" || calibrationScheme_  == "BothLegsTauTau")
      {
	ids.push_back(23);
	ids.push_back(25);
	ids.push_back(35);
	ids.push_back(36);
      }       
    if(calibrationScheme_  == "OneLeg")
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

};

#endif
