//HadronicTauEfficiencyAnalyzer
//Module that  measures performance of final  
//selected Tau candidates


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <TTree.h>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "Math/GenVector/VectorUtil.h"

#include "DataFormats/PatCandidates/interface/TriggerPath.h"

//
// class decleration
//

template <typename T,typename W>
class TagAndProbePlotter : public edm::EDAnalyzer {
   public:
  explicit TagAndProbePlotter(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),
    vertices_(iConfig.getParameter<edm::InputTag>("vertices")),
    ref_(iConfig.getParameter<edm::InputTag>("ref")),
    patTrigger_(iConfig.getParameter<edm::InputTag>("patTrigger")),
    selections_(iConfig.getParameter<std::vector<std::string> >("id")),
    methods_(iConfig.getParameter<std::vector<std::string> >("methods")),
    triggers_(iConfig.getParameter<std::vector<std::string> >("triggers")),
    triggersProbe_(iConfig.getParameter<std::vector<std::string> >("triggersProbe")),
    matchDR_(iConfig.getUntrackedParameter<double>("MatchDR",0.15))
      {
	vertices=0;

	for(unsigned int i=0;i<selections_.size()+2;++i){ //add 2 for hlt +matching
	  valuesPass.push_back(-1);
	}

	mass=-1.;
	pt=-1;
	eta=-1;
	t = fs->make<TTree>( "tagAndProbeTree"  , "");
	for(unsigned int i=0;i<selections_.size();++i) {
	  selectors.push_back(new StringCutObjectSelector<W>(methods_[i],true));
	  t->Branch((selections_[i]+"Pass").c_str(),&valuesPass.at(i),(selections_[i]+"Pass/I").c_str());

	  t->Branch((selections_[i]+"Pass").c_str(),&valuesPass.at(i),(selections_[i]+"Pass/I").c_str());

	  t->Branch("vertices",&vertices,"vertices/I");

	}


	t->Branch("hltPass",&valuesPass.at(selections_.size()),"hltPass/I");
	t->Branch("matchPass",&valuesPass.at(selections_.size()+1),"matchPass/I");

	t->Branch("mass",&mass,"mass/F");
	t->Branch("pt",&pt,"pt/F");
	t->Branch("eta",&eta,"eta/F");

	  
      }

    ~TagAndProbePlotter() {}


   private:

    virtual void analyze(const edm::Event& iEvent, const edm::EventSetup&) {
      vertices=0;

      edm::Handle<reco::VertexCollection> verticesH;
      if(iEvent.getByLabel(vertices_,verticesH))
	vertices = verticesH->size();


/*  	edm::Handle<pat::TriggerPathCollection> paths;  */
/*  	if(iEvent.getByLabel(patTrigger_, paths))  */
/*  	    for(unsigned int j=0;j<paths->size();++j)   */
/*  	      printf("Paths = %s\n",paths->at(j).name().c_str());  */


	edm::Handle<std::vector<T> >ref;
	edm::Handle<std::vector<W> >src;
	

	    ////RESET
      for(unsigned int j=0;j<selections_.size()+2;++j){ //add 2 for hlt +matching
	valuesPass.at(j)=-1;
      }
      mass=-1.;
      pt=-1;
      eta=-1;
      if(iEvent.getByLabel(ref_,ref)&&ref->size()>0) 
	for(unsigned int i=0;i<ref->size();++i) {
	    ////RESET
	    for(unsigned int j=0;j<selections_.size()+2;++j){ //add 2 for hlt +matching
	      valuesPass.at(j)=-1;
	    }

	    mass=ref->at(i).mass();
	    pt=ref->at(i).leg2()->pt();
	    eta=ref->at(i).leg2()->eta();
	    
	    //	    massHistos.at(0)->Fill(ref->at(i).mass());
	    //check if the first leg fired the trigger
	    bool legFired=false;
	    for(unsigned int j=0;j<triggers_.size();++j) 
	      if(ref->at(i).leg1()->userFloat(triggers_[j])>0)
		legFired=true;
	    

	
           //get the src and match src to the ref leg2
	    if(legFired)
	    if(iEvent.getByLabel(src_,src)) {

	      for(unsigned int j=0;j<src->size();++j) {
		if(ROOT::Math::VectorUtil::DeltaR(src->at(j).p4(),ref->at(i).leg2()->p4())<matchDR_) {
		  //matched. Loop on the discriminators
		  valuesPass[selections_.size()+1] = 1;

		  
		  bool passed=true;
		  bool passedPrev=true;

		  for(unsigned int k=0;k<methods_.size();++k) {
		    for(unsigned int l=0;l<=k;++l) {
		      if(!(*(selectors.at(l)))(src->at(j))) {
			if(l<k)
			  passedPrev=false;
			passed=false;
		      }
		    }


		    if(passed&&passedPrev)
		      valuesPass[k] = 1;
		    else if(passedPrev)
		      valuesPass[k] = 0;
		  }


		  //check if leg2 fired
		  bool leg2Fired=false;
		  for(unsigned int k=0;k<triggersProbe_.size();++k) 
		    if(src->at(j).userFloat(triggersProbe_[k])>0)
		      leg2Fired=true;
		  if(leg2Fired&&passed) 
		    valuesPass[selections_.size()] = 1;
		  else if(passed)
		    valuesPass[selections_.size()] = 0;
		  break;
		  
		}
		else
		  {
		    valuesPass[selections_.size()+1] = 0;
		  }
		
	      }
	    t->Fill();
	
	    }
	  }

    }
    


    virtual void endJob() {


    }
      
    edm::InputTag src_;
    edm::InputTag vertices_;
    edm::InputTag ref_;
    edm::InputTag patTrigger_;
    std::vector<std::string> selections_;
    std::vector<std::string> methods_;
    std::vector<std::string> triggers_;
    std::vector<std::string> triggersProbe_;

    float mass;
    float pt;
    float eta;
    std::vector<int> valuesPass;
    
    double matchDR_;
    std::vector<StringCutObjectSelector<W>* > selectors;
    edm::Service<TFileService> fs;

    int vertices;

    TTree *t;

};
      
