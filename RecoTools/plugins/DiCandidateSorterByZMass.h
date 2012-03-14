// -*- C++ -*-
//
// Package:    PATMuonTrackVetoSelector
// Class:      PATMuonTrackVetoSelector
// 
/**\class PATMuonTrackVetoSelector PATMuonTrackVetoSelector.cc UWAnalysis/PATMuonTrackVetoSelector/src/PATMuonTrackVetoSelector.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Michail Bachtis
//         Created:  Sun Jan 31 15:04:57 CST 2010
// $Id: DiCandidateSorterByZMass.h,v 1.1 2011/06/17 15:59:57 iross Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration





template <class T>
class DiCandidateSorterByZMass : public edm::EDProducer {
   public:
  explicit DiCandidateSorterByZMass(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src"))
     {
       produces<std::vector<T> >();
     }

  ~DiCandidateSorterByZMass() {}


   private:
  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    
    std::vector<T> toBeSorted;
    Handle<std::vector<T> > cands;
    if(iEvent.getByLabel(src_,cands)) 
      toBeSorted =  *cands;
    if(toBeSorted.size()>0) {
      Sorter sorter;
      std::sort(toBeSorted.begin(),toBeSorted.end(),sorter);
    }
    std::auto_ptr<std::vector<T> > out(new std::vector<T>);
    //	double tempSum=0;
    for(unsigned int i=0;i<toBeSorted.size();++i){
//		std::cout << "First Z mass, pts: " << toBeSorted.at(i).leg1()->mass() << ", " << toBeSorted.at(i).leg1()->pt() << "(" << toBeSorted.at(i).leg1()->leg1()->pt() << "," << toBeSorted.at(i).leg1()->leg2()->pt() << "), second Z mass, pt: " << toBeSorted.at(i).leg2()->mass() << ", " << toBeSorted.at(i).leg2()->pt() << "(" <<  toBeSorted.at(i).leg2()->leg1()->pt() << "," << toBeSorted.at(i).leg2()->leg2()->pt() << ")" << std::endl;
      out->push_back(toBeSorted.at(i));
    }
	iEvent.put(out);

  } 

  //  template<class T>
  class Sorter {
  public:
    Sorter() 
    {}
    ~Sorter()
    {}
    bool operator()(T t1,T t2)
    {
//      if (t1.leg1()->mass() != t2.leg1()->mass()) {
//		  std::cout << "diff. mass" << std::endl;
		return (abs(t1.leg1()->mass()-91.2) < abs(t2.leg1()->mass()-91.2));
//	  } else { //if Z masses are the same, sort by Z2 Pt
//	  	return (t1.leg2()->pt() > t2.leg2()->pt());
//	  }
    } 
};

      // ----------member data ---------------------------
      edm::InputTag src_;



};
