#ifndef UWAnalysis_PatTools_BestSelector_h
#define UWAnalysis_PatTools_BestSelector_h



#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "UWAnalysis/PatTools/interface/FetchCollection.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"

#include "UWAnalysis/PatTools/interface/CompositePtrCandidateT1T2MEtAlgorithm.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <string>

template<typename T1, typename T2>
class BestSelector : public edm::EDProducer 
{
	typedef edm::Ptr<T1> T1Ptr;
	typedef edm::Ptr<T2> T2Ptr;

	typedef std::vector<T1> CompositePtrCandidateCollection;
	public:

	explicit BestSelector(const edm::ParameterSet& cfg)
	{

		src_ = cfg.getParameter<edm::InputTag>("src");
		src2_ = cfg.getParameter<edm::InputTag>("src2");

		produces<CompositePtrCandidateCollection>("");
	}

	~BestSelector() {}

	void produce(edm::Event& evt, const edm::EventSetup& es)
	{
		std::auto_ptr<CompositePtrCandidateCollection> compositePtrCandidateCollection(new CompositePtrCandidateCollection());

		typedef edm::View<T1> T1View;
        std::vector<T1> temp;
		edm::Handle<T1View> collection;
		pf::fetchCollection(collection, src_, evt);

		typedef edm::View<T2> T2View;
		edm::Handle<T2View> collection2;
		pf::fetchCollection(collection2, src2_, evt);
		double z0=91.1876;
        int bestIndex=0;
		for(unsigned int i=0;i<collection->size();++i) {
			bool keep=true;
			for(unsigned int j=0;j<collection2->size();++j) {
				if (abs(collection->at(i).mass()-z0) > abs(collection2->at(j).mass()-z0)){
					keep=false;
				}
			}
			if (keep==true){
				temp.push_back(collection->at(i));
			}
            for (unsigned int i = 0;  i < temp.size(); i++) {
				if (abs(temp.at(i).mass()-z0) < abs(temp.at(bestIndex).mass()-z0)){
                    bestIndex=i;
                }
            }
		}
        if (temp.size()>0){
            compositePtrCandidateCollection->push_back(temp.at(bestIndex));
        }
		evt.put(compositePtrCandidateCollection);
	}

	private:

	edm::InputTag src_;
	edm::InputTag src2_;

};

#endif

