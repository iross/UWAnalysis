#ifndef UWAnalysis_RecoTools_PATCandNSVFitter_h
#define UWAnalysis_RecoTools_PATCandNSVFitter_h

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

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"

#include "TauAnalysis/CandidateTools/interface/NSVfitAlgorithmBase.h"
#include "AnalysisDataFormats/TauAnalysis/interface/NSVfitResonanceHypothesisSummary.h"

#include "UWAnalysis/RecoTools/interface/candidateAuxFunctions.h"
#include "UWAnalysis/RecoTools/interface/generalAuxFunctions.h"

template<typename T1, typename T2>
class PATCandidatePairNSVFitter : public edm::EDProducer
{
  typedef edm::Ptr<T1> T1Ptr;
  typedef edm::Ptr<T2> T2Ptr;
  typedef std::vector<edm::Ptr<pat::Jet> > JetPtrVector;
  typedef std::vector<CompositePtrCandidateT1T2MEt<T1,T2> > CompositePtrCandidateCollection;

 public:

  explicit PATCandidatePairNSVFitter(const edm::ParameterSet& cfg)
  {
    src_     = cfg.getParameter<edm::InputTag>("src");
    srcPV_       =  cfg.getParameter<edm::InputTag>("srcPrimaryVertex") ;

    label_ = cfg.getParameter<std::string>("resultLabel");

    printf("Will use NSV FIt\n");
    edm::ParameterSet cfg_config = cfg.getParameter<edm::ParameterSet>("config");
    edm::ParameterSet cfg_event = cfg_config.getParameter<edm::ParameterSet>("event");

    edm::ParameterSet cfg_algorithm = cfg.getParameter<edm::ParameterSet>("algorithm");
    cfg_algorithm.addParameter<edm::ParameterSet>("event", cfg_event);
    std::string pluginType = cfg_algorithm.getParameter<std::string>("pluginType");
    algorithm_ = NSVfitAlgorithmPluginFactory::get()->create(pluginType, cfg_algorithm);

    produces<CompositePtrCandidateCollection>();
  }

  ~PATCandidatePairNSVFitter(){}

  void beginJob()
  {
    algorithm_->beginJob();

  }


  void produce(edm::Event& evt, const edm::EventSetup& es) {
    std::auto_ptr<CompositePtrCandidateCollection> out(new CompositePtrCandidateCollection);
	std::cout << "I'm in the pair producer!" << std::endl;
    // Get primary vertex
    const reco::Vertex* pv = NULL;
    if ( srcPV_.label() != "" ) {
       edm::Handle<reco::VertexCollection> pvs;
       pf::fetchCollection(pvs, srcPV_, evt);
       pv = &((*pvs)[0]);
    }

    algorithm_->beginEvent(evt, es);

    edm::Handle<std::vector<CompositePtrCandidateT1T2MEt<T1,T2> > > cands;

    if(evt.getByLabel(src_,cands)) {

      for (unsigned int i=0;i<cands->size();++i) {

        CompositePtrCandidateT1T2MEt<T1,T2> compositePtrCandidate = cands->at(i);

        typedef edm::Ptr<reco::Candidate> CandidatePtr;
        typedef std::map<std::string, CandidatePtr> InputParticleMap;
        // Define the names of the input Ptrs
        InputParticleMap inputs;
        inputs["leg1"] = CandidatePtr(compositePtrCandidate.leg1());
        inputs["leg2"] = CandidatePtr(compositePtrCandidate.leg2());
        inputs["met"] = CandidatePtr(compositePtrCandidate.met());

        NSVfitEventHypothesisBase* result =
          algorithm_->fit(inputs, pv);
        assert(result);
        NSVfitResonanceHypothesisSummary summary(*result->resonance(0));
        summary.setName(label_);
        compositePtrCandidate.addNSVfitSolution(summary);
	//	std::cout << "Added NSV: m = " << summary.mass() << std::endl;;
        out->push_back(compositePtrCandidate);
      }
    }

    evt.put(out);
  }

 private:
  edm::InputTag src_;
  edm::InputTag srcPV_;
  std::string label_;
  NSVfitAlgorithmBase* algorithm_;
  typedef std::vector<int> vint;

};


#endif
