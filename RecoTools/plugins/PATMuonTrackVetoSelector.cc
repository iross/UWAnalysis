#include "UWAnalysis/RecoTools/plugins/PATMuonTrackVetoSelector.h"
#include "Math/GenVector/VectorUtil.h"
//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
PATMuonTrackVetoSelector::PATMuonTrackVetoSelector(const edm::ParameterSet& iConfig):
  src_(iConfig.getParameter<edm::InputTag>("src")),
  particles_(iConfig.getParameter<edm::InputTag>("particles")),
  minVetoValue_(iConfig.getParameter<double>("minVetoMass")),
  maxVetoValue_(iConfig.getParameter<double>("maxVetoMass"))

{

   produces<pat::MuonCollection>("");
  
}


PATMuonTrackVetoSelector::~PATMuonTrackVetoSelector()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
PATMuonTrackVetoSelector::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;

   Handle<reco::PFCandidateCollection> particles;
   bool particlesExist = iEvent.getByLabel(particles_,particles);

   std::auto_ptr<pat::MuonCollection> out(new pat::MuonCollection);

   Handle<pat::MuonCollection> muons;
   if(iEvent.getByLabel(src_,muons)) {
     for(pat::MuonCollection::const_iterator i=muons->begin();i!=muons->end();++i){
       double mass=0;
       if(particlesExist)
	 for(unsigned int p=0;p<particles->size();++p)
	   if(abs(particles->at(p).pdgId())==211 || abs(particles->at(p).pdgId())==11 || abs(particles->at(p).pdgId())==13) {
	     double minDr=1000;
	     double dr = ROOT::Math::VectorUtil::DeltaR(i->p4(),particles->at(p).p4());
	     if(dr>0.005&&dr<0.5 && dr<minDr) {
	       minDr=dr;
	       //Assign the Kaon mass to the particle
	       math::PtEtaPhiMLorentzVector v(particles->at(p).pt(),particles->at(p).eta(),particles->at(p).phi(),0.493);
	       mass = (i->p4()+v).M()/sqrt(i->pt());
	     }
	   }
       if(mass <minVetoValue_ || mass> maxVetoValue_) 
	 out->push_back(*i);
     }

   }



   iEvent.put(out);
 
}

// ------------ method called once each job just before starting event loop  ------------
void 
PATMuonTrackVetoSelector::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PATMuonTrackVetoSelector::endJob() {
}

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
DEFINE_FWK_MODULE(PATMuonTrackVetoSelector);
