#include "UWAnalysis/RecoTools/plugins/SmearedJetProducer.h"

SmearedJetProducer::SmearedJetProducer(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),  
    energyScaleDB_(iConfig.getParameter<double>("energyScaleDB"))
    {
      smearingModule = new SmearedParticleMaker<pat::Jet,GenJetRetriever<pat::Jet> >(iConfig);
      produces<std::vector<pat::Jet> >();
    }


SmearedJetProducer::~SmearedJetProducer()
{}

void 
SmearedJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
    //std::cout << "<SmearedJetProducer::produce>:" << std::endl;
    //std::cout << "(label = " << moduleLabel_ << ")" << std::endl;

    using namespace edm;
    using namespace reco;

    edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
    iSetup.get<JetCorrectionsRecord>().get("AK5PF",JetCorParColl); 
    JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
    JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(JetCorPar);

    std::auto_ptr<std::vector<pat::Jet> > out(new std::vector<pat::Jet> );
    Handle<std::vector<pat::Jet> > srcH;
    if(iEvent.getByLabel(src_,srcH) &&srcH->size()>0) 
      for(unsigned int i=0;i<srcH->size();++i) {
	pat::Jet object = srcH->at(i);
	//std::cout << " original object(" << i << "): Pt = " << object.pt() << "," 
	//	    << " eta = " << object.eta() << ", phi = " << object.phi() << std::endl;

	smearingModule->smear(object);

	//smear from database!
	jecUnc->setJetEta(object.eta());
	jecUnc->setJetPt(object.pt()); // here you must use the CORRECTED jet pt
	double unc = jecUnc->getUncertainty((energyScaleDB_>0));
	object.setP4(object.p4()*(1.+energyScaleDB_*unc));
	out->push_back(object);
      }
    iEvent.put(out);
    delete jecUnc;
} 




#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(SmearedJetProducer);
