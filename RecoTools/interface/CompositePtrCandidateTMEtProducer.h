#ifndef UWAnalysis_RecoTools_CompositePtrCandidateTMEtProducer_h
#define UWAnalysis_RecoTools_CompositePtrCandidateTMEtProducer_h

/** \class CompositePtrCandidateTMEtProducer
 *
 * Produce combinations of visible tau decay products and missing transverse momentum 
 * (representing the undetected momentum carried away 
 *  the neutrino produced in a W --> tau nu decay and the neutrinos produced in the tau decay)
 * 
 * \authors Christian Veelken
 *
 * \version $Revision: 1.4 $
 *
 * $Id: CompositePtrCandidateTMEtProducer.h,v 1.4 2010/11/20 00:13:32 bachtis Exp $
 *
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "UWAnalysis/RecoTools/interface/FetchCollection.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEtFwd.h"
#include "UWAnalysis/RecoTools/interface/CompositePtrCandidateTMEtAlgorithm.h"

#include <string>

template<typename T>
class CompositePtrCandidateTMEtProducer : public edm::EDProducer 
{
  typedef edm::Ptr<T> TPtr;
  typedef edm::Ptr<reco::Candidate> METPtr;
  typedef edm::Ptr<pat::Jet> JetPtr;
  typedef std::vector<edm::Ptr<pat::Jet> > JetPtrVector;


  typedef std::vector<CompositePtrCandidateTMEt<T> > CompositePtrCandidateCollection;
  
 public:

  explicit CompositePtrCandidateTMEtProducer(const edm::ParameterSet& cfg)
    : algorithm_()
  {
    srcVisDecayProducts_ = cfg.getParameter<edm::InputTag>("srcLeptons");
    srcJets_ = cfg.getParameter<edm::InputTag>("srcJets");
    srcMET_ = cfg.getParameter<edm::InputTag>("srcMET");
    verbosity_ = cfg.getUntrackedParameter<int>("verbosity", 0);

    produces<CompositePtrCandidateCollection>("");
  }

  ~CompositePtrCandidateTMEtProducer() {}

  void produce(edm::Event& evt, const edm::EventSetup& es)
  {
    typedef edm::View<T> TView;
    edm::Handle<TView> visDecayProductsCollection;
    bool gotVisProducts = evt.getByLabel(srcVisDecayProducts_,visDecayProductsCollection);

  
    METPtr metPtr;
    edm::Handle<edm::View<reco::Candidate> > metCollection;
    bool gotMET = evt.getByLabel(srcMET_,metCollection);

    edm::Handle<edm::View<pat::Jet> > jetCollection;
    evt.getByLabel(srcJets_,jetCollection);

    JetPtrVector pfJets;
    for(unsigned int i=0;i<jetCollection->size();++i)
      pfJets.push_back(jetCollection->ptrAt(i));
      
    if(gotVisProducts&&gotMET) {

      //--- check that there is exactly one MET object in the event
      //    (missing transverse momentum is an **event level** quantity)
      if ( metCollection->size() >0 ) {
	metPtr = metCollection->ptrAt(0);
      } else {
	edm::LogError ("produce") << " Found " << metCollection->size() << " MET objects in collection = " << srcMET_ << ","
				  << " --> CompositePtrCandidateTMEt collection will NOT be produced !!";
	std::auto_ptr<CompositePtrCandidateCollection> emptyCompositePtrCandidateCollection(new CompositePtrCandidateCollection());
	evt.put(emptyCompositePtrCandidateCollection);
	return;
      }
      
      std::auto_ptr<CompositePtrCandidateCollection> compositePtrCandidateCollection(new CompositePtrCandidateCollection());
      for ( unsigned idxVisDecayProducts = 0, numVisDecayProducts = visDecayProductsCollection->size(); 
	    idxVisDecayProducts < numVisDecayProducts; ++idxVisDecayProducts ) {
	TPtr visDecayProductsPtr = visDecayProductsCollection->ptrAt(idxVisDecayProducts);
	
	CompositePtrCandidateTMEt<T> compositePtrCandidate = 
	  algorithm_.buildCompositePtrCandidate(visDecayProductsPtr, metPtr,pfJets,*visDecayProductsCollection);
	

      



	compositePtrCandidateCollection->push_back(compositePtrCandidate);
      }
      
      //--- add the collection of reconstructed CompositePtrCandidateTMEts to the event
      evt.put(compositePtrCandidateCollection);
    }
    else
      {
	std::auto_ptr<CompositePtrCandidateCollection> emptyCompositePtrCandidateCollection(new CompositePtrCandidateCollection());
	evt.put(emptyCompositePtrCandidateCollection);
      }
  }

  

 private:

  CompositePtrCandidateTMEtAlgorithm<T> algorithm_;
  
  edm::InputTag srcVisDecayProducts_;
  edm::InputTag srcMET_;
  edm::InputTag srcJets_;
  int verbosity_;
};

#endif

