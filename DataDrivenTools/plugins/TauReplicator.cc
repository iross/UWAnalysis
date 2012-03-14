// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


//Pythia
#include "HepMC/GenEvent.h"
#include "GeneratorInterface/Pythia6Interface/interface/Pythia6Service.h"
#include "GeneratorInterface/Pythia6Interface/interface/Pythia6Declarations.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "HepPID/ParticleIDTranslations.hh"


using namespace gen;
//
// class decleration
//

class TauReplicator : public edm::EDProducer {
 public:
  explicit TauReplicator(const edm::ParameterSet&);
  ~TauReplicator();

 private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  void attachPy6DecaysToGenEvent();
  void loadEvent( edm::Event& );
  void generateEvent(const PATMuPairCollection&);

      
  // ----------member data ---------------------------
  edm::InputTag diLeptons_;

  Pythia6Service*  fPy6Service;
  HepMC::GenEvent* fEvt;
  bool             fHepMCVerbosity ;
  std::vector<int> fPartIDs ;
  int              fPylistVerbosity;
  int              fMaxEventsToPrint ;


};




#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

using namespace edm;
using namespace gen;


TauReplicator::TauReplicator(const edm::ParameterSet& iConfig):
  diLeptons_(iConfig.getParameter<edm::InputTag>("src")),
  fPy6Service( new Pythia6Service(iConfig) ),
  fEvt(0)
{
  fHepMCVerbosity   = iConfig.getUntrackedParameter<bool>("pythiaHepMCVerbosity", false ) ;
  fPylistVerbosity  = iConfig.getUntrackedParameter<int>( "pythiaPylistVerbosity", 0 ) ;
  fMaxEventsToPrint = iConfig.getUntrackedParameter<int>( "maxEventsToPrint", 0 );

  if (!call_pygive("MSTU(12)=12345")) 
    {
      throw edm::Exception(edm::errors::Configuration,"PythiaError") 
	<<" pythia did not accept MSTU(12)=12345";
    }

  produces<HepMCProduct>();
}


TauReplicator::~TauReplicator()
{
  if ( fPy6Service ) delete fPy6Service; 

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TauReplicator::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;

  Handle<PATMuPairCollection> diLeptons;
  if(iEvent.getByLabel(diLeptons_,diLeptons)&&diLeptons->size()>0)
    {
      generateEvent(*diLeptons) ;
   
      fEvt->set_beam_particles(0,0);
      fEvt->set_event_number(iEvent.id().event()) ;
      fEvt->set_signal_process_id(pypars.msti[0]) ;  
      attachPy6DecaysToGenEvent();
      if ( iEvent.id().event() <= (unsigned int)fMaxEventsToPrint )
	{
	  if ( fPylistVerbosity )
	    {
	      call_pylist(fPylistVerbosity);
	    }
	  if ( fHepMCVerbosity )
	    {
	      if ( fEvt ) fEvt->print();
	    }
	}
      loadEvent( iEvent );
    }
}

// ------------ method called once each job just before starting event loop  ------------
void 
TauReplicator::beginJob(const edm::EventSetup&)
{
  assert ( fPy6Service ) ;
  Pythia6Service::InstanceWrapper guard(fPy6Service);// grab Py6 instance
  fPy6Service->setGeneralParams();
  fPy6Service->setCSAParams();
  fPy6Service->setSLHAParams();
  call_pyinit("NONE", "", "", 0.0);

  return;

}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauReplicator::endJob() {
   
  // here put in GenRunInfoProduct
   
  call_pystat(1);
   
  return;

}


void 
TauReplicator::attachPy6DecaysToGenEvent()
{

   for ( int iprt=fPartIDs.size(); iprt<pyjets.n; iprt++ ) // the pointer is shifted by -1, c++ style
    {
      int parent = pyjets.k[2][iprt];
      if ( parent != 0 )
	{
	  // pull up parent particle
	  //
	  HepMC::GenParticle* parentPart = fEvt->barcode_to_particle( parent );
	  parentPart->set_status( 2 ); // reset status, to mark that it's decayed
	   
	  HepMC::GenVertex* DecVtx = new HepMC::GenVertex(HepMC::FourVector(pyjets.v[0][iprt],
									    pyjets.v[1][iprt],
									    pyjets.v[2][iprt],
									    pyjets.v[3][iprt]));
	  DecVtx->add_particle_in( parentPart ); // this will cleanup end_vertex if exists,
	  // and replace with the new one
	  // I presume barcode will be given automatically
	   
	  // attention: pyjets.k[1][iprt] is PYTHIA6 PID !!!
	  //            need to convert to standard PDG
	  //
	  HepMC::FourVector  pmom(pyjets.p[0][iprt],pyjets.p[1][iprt],
				  pyjets.p[2][iprt],pyjets.p[3][iprt] );
	   
	  HepMC::GenParticle* daughter = 
	    new HepMC::GenParticle(pmom,
				   HepPID::translatePythiatoPDT( pyjets.k[1][iprt] ),
				   1);
	  daughter->suggest_barcode( iprt+1 );
	  DecVtx->add_particle_out( daughter );
	  // give particle barcode as well !

	  int iprt1;
	  for ( iprt1=iprt+1; iprt1<pyjets.n; iprt1++ ) // the pointer is shifted by -1, c++ style
	    {
	      if ( pyjets.k[2][iprt1] != parent ) break; // another parent particle, break the loop
	      HepMC::FourVector  pmomN(pyjets.p[0][iprt1],pyjets.p[1][iprt1],
				       pyjets.p[2][iprt1],pyjets.p[3][iprt1] );
	      //
	      // same here with PID - need py6->pdg !!!
	      //
	      HepMC::GenParticle* daughterN = 
		new HepMC::GenParticle(pmomN,
				       HepPID::translatePythiatoPDT( pyjets.k[1][iprt1] ),
				       1);
	      daughterN->suggest_barcode( iprt1+1 );
	      DecVtx->add_particle_out( daughterN );     
	    }
	   
	  iprt = iprt1-1; // reset counter such that it doesn't go over the same child more than once
	  // don't forget to offset back into c++ counting, as it's already +1 forward

	  fEvt->add_vertex( DecVtx );
	}
    }
  return;
}

void 
TauReplicator::loadEvent( edm::Event& evt )
{

  std::auto_ptr<HepMCProduct> bare_product(new HepMCProduct());  
   
  if(fEvt)  bare_product->addHepMCData( fEvt );

  evt.put(bare_product);

   
  return;

}


void 
TauReplicator::generateEvent(const PATMuPairCollection& diMuons)
{
   
  Pythia6Service::InstanceWrapper guard(fPy6Service);// grab Py6 instance
  HepMC::GenVertex* Vtx = new HepMC::GenVertex( HepMC::FourVector(diMuons.at(0).leg1()->vertex().x(),
								  diMuons.at(0).leg1()->vertex().y(),
								  diMuons.at(0).leg1()->vertex().z()));
  fEvt = new HepMC::GenEvent() ;
  fPartIDs.clear();
    
  int ip=1;

  

  for ( size_t i=0; i<diMuons.size(); i++ )
    for(unsigned int j=0;j<diMuons[i].numberOfSourceCandidatePtrs();++j)
    {
      const reco::CandidatePtr  mu = diMuons.at(i).sourceCandidatePtr(j);
      int particleID;
      if(mu->charge()>0)
	particleID = 15;
      else
	particleID=-15;
      
      fPartIDs.push_back(particleID);

      int py6PID = HepPID::translatePDTtoPythia( particleID );

      double px = mu->px();
      double py = mu->py();
      double pz = mu->pz();
      double the = mu->theta();
      double phi = mu->phi();
      double mom = mu->p();
      double mass = pymass_(particleID);
      double ee = sqrt(mom*mom+mass*mass);

      py1ent_(ip, py6PID, ee, the, phi);
         
      HepMC::FourVector p(px,py,pz,ee) ;
      HepMC::GenParticle* Part = new HepMC::GenParticle(p,particleID,1);
      Part->suggest_barcode( ip ) ;
      Vtx->add_particle_out(Part);
      ip++;
    }

  fEvt->add_vertex(Vtx);
     
  // run pythia
  pyexec_();
   
  return;
}


#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"

DEFINE_FWK_MODULE(TauReplicator);
