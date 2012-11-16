#ifndef UWAnalysis_PatTools_QuadCandInvMassSelector_h
#define UWAnalysis_PatTools_QuadCandInvMassSelector_h



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
class QuadCandInvMassSelector : public edm::EDProducer 
{
    typedef edm::Ptr<T1> T1Ptr;
    typedef edm::Ptr<T2> T2Ptr;

    typedef std::vector<CompositePtrCandidateT1T2MEt<T1,T2> > CompositePtrCandidateCollection;

    public:

    explicit QuadCandInvMassSelector(const edm::ParameterSet& cfg)
    {

        src_ = cfg.getParameter<edm::InputTag>("src");
        minMll_ = cfg.getParameter<double>("minMll");

        produces<CompositePtrCandidateCollection>("");
    }

    ~QuadCandInvMassSelector() {}

    void produce(edm::Event& evt, const edm::EventSetup& es)
    {

        typedef edm::View<CompositePtrCandidateT1T2MEt<T1,T2> > TView;
        edm::Handle<TView> collection;
        pf::fetchCollection(collection, src_, evt);

        std::auto_ptr<CompositePtrCandidateCollection> compositePtrCandidateCollection(new CompositePtrCandidateCollection());

        for(unsigned int i=0;i<collection->size();++i) {
            CompositePtrCandidateT1T2MEt<T1,T2> cand = collection->at(i);

            int charge11 = cand.leg1()->leg1()->charge();
            int charge12 = cand.leg1()->leg2()->charge();
            int charge21 = cand.leg2()->leg1()->charge();
            int charge22 = cand.leg2()->leg2()->charge();

            bool check11=false;
            bool check12=false;

            /**
            std::cout << "Charges: " << charge11 << ", " << charge12 << ", " << charge21 << ", " << charge22 << std::endl;
            std::cout << "M1112: " << ((cand.leg1()->leg1()->p4())+(cand.leg1()->leg2()->p4())).M() << std::endl;
            std::cout << "M1121: " << ((cand.leg1()->leg1()->p4())+(cand.leg2()->leg1()->p4())).M() << std::endl;
            std::cout << "M1122: " << ((cand.leg1()->leg1()->p4())+(cand.leg2()->leg2()->p4())).M() << std::endl;
            std::cout << "M1221: " << ((cand.leg1()->leg2()->p4())+(cand.leg2()->leg1()->p4())).M() << std::endl;
            std::cout << "M1222: " << ((cand.leg1()->leg2()->p4())+(cand.leg2()->leg2()->p4())).M() << std::endl;
            std::cout << "M2122: " << ((cand.leg2()->leg1()->p4())+(cand.leg2()->leg2()->p4())).M() << std::endl;
            **/

            if (((cand.leg1()->leg1()->p4())+(cand.leg1()->leg2()->p4())).M() > minMll_){
                if (((cand.leg2()->leg1()->p4())+(cand.leg2()->leg2()->p4())).M() > minMll_){

                    //check OS combinations between legs
                    if (charge11!=charge21){
                        if (((cand.leg1()->leg1()->p4())+(cand.leg2()->leg1()->p4())).M() > minMll_) check11=true;
                    } else if (charge11!=charge22){
                        if (((cand.leg1()->leg1()->p4())+(cand.leg2()->leg2()->p4())).M() > minMll_) check11=true;
                    }

                    if (charge12!=charge21){
                        if (((cand.leg1()->leg2()->p4())+(cand.leg2()->leg1()->p4())).M() > minMll_) check12=true;
                    } else if (charge12!=charge22){
                        if (((cand.leg1()->leg2()->p4())+(cand.leg2()->leg2()->p4())).M() > minMll_) check12=true;
                    }
                    if (check11 && check12) {
                        compositePtrCandidateCollection->push_back(cand);
                    }
                }
            }
        }

        evt.put(compositePtrCandidateCollection);
    }

    private:

    edm::InputTag src_;
    double minMll_;

};

#endif

