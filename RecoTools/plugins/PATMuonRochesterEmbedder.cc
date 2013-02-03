/*  ---------------------
File: PATMuonRochesterEmbedder
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Create a muon collection with rochester corrections applied. These are done(ish) at the pattuple level, but SOME SYNCH EXERCISES use older corrections, so here we are. IAR 23.Jan.2013
*/

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "UWAnalysis/RecoTools/interface/rochcor.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

class PATMuonRochesterEmbedder : public edm::EDProducer {
    public:
        PATMuonRochesterEmbedder(const edm::ParameterSet& pset);
        virtual ~PATMuonRochesterEmbedder(){}
        void produce(edm::Event& evt, const edm::EventSetup& es);
    private:
        edm::InputTag src_;
        bool isMC_;
        bool isSync_;
        rochcor corrector_;
};

PATMuonRochesterEmbedder::PATMuonRochesterEmbedder(
        const edm::ParameterSet& pset):
    src_(pset.getParameter<edm::InputTag>("src")),
    isMC_(pset.getParameter<bool>("isMC")),
    isSync_(pset.getParameter<bool>("isSync"))
            {
        produces<pat::MuonCollection>();
    }

void PATMuonRochesterEmbedder::produce(edm::Event& evt, const edm::EventSetup& es) {
    int runNo = evt.id().run();
    int runopt = (runNo < 173693 ? 0 : 1 );

    edm::Handle<edm::View<pat::Muon> > muons;
    evt.getByLabel(src_, muons);

    std::auto_ptr<pat::MuonCollection> out(new pat::MuonCollection);
    out->reserve(muons->size());

    for (size_t i = 0; i < muons->size(); ++i) {
        pat::Muon muon(muons->at(i));
        TLorentzVector p4(muon.px(),muon.py(),muon.pz(),muon.energy());
        //runopt = 0 --> 2011A
        //runopt = 1 --> 2011B
        if (isMC_) corrector_.momcor_mc(p4, muon.charge(), 0.0, 0, isSync_); //runopt == 0 for MC?
        else corrector_.momcor_data(p4, muon.charge(), 0.0, runopt);
        math::XYZTLorentzVector corr_p4(p4.Px(),p4.Py(),p4.Pz(),p4.Energy());
        muon.setP4(corr_p4);
        out->push_back(muon);
    }
    evt.put(out);
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(PATMuonRochesterEmbedder);
