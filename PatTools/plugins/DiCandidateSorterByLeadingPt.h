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
// $Id: DiCandidateSorterByLeadingPt.h,v 1.1.1.1 2010/04/16 10:07:30 bachtis Exp $
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
class DiCandidateSorterByLeadingPt : public edm::EDProducer {
   public:
  explicit DiCandidateSorterByLeadingPt(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src"))
     {
       produces<std::vector<T> >();
     }

  ~DiCandidateSorterByLeadingPt() {}


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
    for(unsigned int i=0;i<toBeSorted.size();++i)
      out->push_back(toBeSorted.at(i));
    
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
      return (t1.leg1()->pt()+t1.leg2()->pt()) > (t2.leg1()->pt()+t2.leg2()->pt());
    } 
};

      // ----------member data ---------------------------
      edm::InputTag src_;



};
