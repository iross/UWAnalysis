#include "UWAnalysis/RecoTools/plugins/SmearedTauProducer.h"

SmearedTauProducer::SmearedTauProducer(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),  
    smearConstituents_(iConfig.getParameter<bool>("smearConstituents")),  
    hadronEnergyScale_(iConfig.getParameter<double>("hadronEnergyScale")),
    gammaEnergyScale_(iConfig.getParameter<double>("gammaEnergyScale"))
    {
      smearingModule = new SmearedParticleMaker<pat::Tau,GenJetRetriever<pat::Tau> >(iConfig);
      produces<std::vector<pat::Tau> >();
    }


SmearedTauProducer::~SmearedTauProducer()
{}

void 
SmearedTauProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
    //std::cout << "<SmearedTauProducer::produce>:" << std::endl;
    //std::cout << "(label = " << moduleLabel_ << ")" << std::endl;

    using namespace edm;
    using namespace reco;

    std::auto_ptr<std::vector<pat::Tau> > out(new std::vector<pat::Tau> );
    Handle<std::vector<pat::Tau> > srcH;
    if(iEvent.getByLabel(src_,srcH) &&srcH->size()>0) 
      for(unsigned int i=0;i<srcH->size();++i) {
	pat::Tau object = srcH->at(i);
	//std::cout << " original object(" << i << "): Pt = " << object.pt() << "," 
	//	    << " eta = " << object.eta() << ", phi = " << object.phi() << std::endl;

	smearingModule->smear(object);

        if(smearConstituents_) {
	  math::XYZTLorentzVector hadronLV;
	  PFCandidateRefVector hadrons = object.signalPFChargedHadrCands();

	  if(hadrons.size()>0)
	    for(unsigned int i=0;i<hadrons.size();++i)
	      hadronLV+=hadrons.at(i)->p4();
	  //apply hadron energy scale
	  hadronLV=hadronEnergyScale_*hadronLV;
	  math::XYZTLorentzVector gammaLV;
	  PFCandidateRefVector gammas = object.signalPFGammaCands();

	  if(gammas.size()>0)
	    for(unsigned int i=0;i<gammas.size();++i)
	      gammaLV+=gammas.at(i)->p4();
	  gammaLV=gammaEnergyScale_*gammaLV;
 	  object.setP4(gammaLV+hadronLV);
	}
	
	//std::cout << "smeared object(" << i << "): Pt = " << object.pt() << "," 
	//	    << " eta = " << object.eta() << ", phi = " << object.phi() << std::endl;

	out->push_back(object);
      }
    iEvent.put(out);
} 




#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(SmearedTauProducer);
