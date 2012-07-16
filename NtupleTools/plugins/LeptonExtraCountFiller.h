// Count the number of taus passing a selection at least dR away from the 2l2tau candidate leptons
//
//
#include <memory>

#include "DataFormats/Candidate/interface/Candidate.h"
#include <TTree.h>

#include "DataFormats/PatCandidates/interface/Tau.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"

template<typename T, typename U>

class LeptonExtraCountFiller : public NtupleFillerBase {
    public:
        LeptonExtraCountFiller(){
        }


        LeptonExtraCountFiller(const edm::ParameterSet& iConfig, TTree* t):
            src_(iConfig.getParameter<edm::InputTag>("src")),
            candSrc_(iConfig.getParameter<edm::InputTag>("candSrc")),
            tag_(iConfig.getParameter<std::string>("tag")),
            mindR_(iConfig.getParameter<double>("mindR")),
            var_(iConfig.getParameter<std::string>("method"))
    {
        value = 0;
        t->Branch(tag_.c_str(),&value,(tag_+"/I").c_str());
        function = new StringCutObjectSelector<pat::Tau>(var_,true);
    }


        ~LeptonExtraCountFiller()
        { 
            if(function != 0) delete function;
        }


        void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
            edm::Handle<edm::View<pat::Tau> > handle;
            edm::Handle<std::vector<T> > candHandle;
            value = 0;
            if(iEvent.getByLabel(src_,handle)) {
                if(iEvent.getByLabel(candSrc_,candHandle)){
                    //loop over handle, sum those passing the requirements
                    for (unsigned int i = 0; i < handle->size(); i++) {
                        if ((*function)(handle->at(i))){
                            if (reco::deltaR( handle->at(i).p4(),candHandle->at(0).leg1()->leg1()->p4() ) > mindR_){
                                if (reco::deltaR( handle->at(i).p4(),candHandle->at(0).leg1()->leg2()->p4() ) > mindR_){
                                    if (reco::deltaR( handle->at(i).p4(),candHandle->at(0).leg2()->leg1()->p4() ) > mindR_){
                                        if (reco::deltaR( handle->at(i).p4(),candHandle->at(0).leg2()->leg2()->p4() ) > mindR_){
                                            value++; 
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    protected:
        edm::InputTag src_;
        edm::InputTag candSrc_;
        std::string tag_;
        std::string var_;
        double mindR_;
        int value;
        StringCutObjectSelector<pat::Tau>*function;

};

typedef LeptonExtraCountFiller<PATMuMuMuTauQuad, pat::Tau> PATMuMuMuTauQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuTauTauQuad, pat::Tau> PATMuMuTauTauQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleTauQuad, pat::Tau> PATMuMuEleTauQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleMuQuad, pat::Tau> PATMuMuEleMuQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleEleQuad, pat::Tau> PATMuMuEleEleQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuMuMuQuad, pat::Tau> PATMuMuMuMuQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleTauTauQuad, pat::Tau> PATEleEleTauTauQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleTauQuad, pat::Tau> PATEleEleEleTauQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleMuTauQuad, pat::Tau> PATEleEleMuTauQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleMuQuad, pat::Tau> PATEleEleEleMuQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleEleQuad, pat::Tau> PATEleEleEleEleQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleMuMuQuad, pat::Tau> PATEleEleMuMuQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleSCQuad, pat::Tau> PATEleEleEleSCQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleSCEleEleQuad, pat::Tau> PATEleSCEleEleQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleSCQuad, pat::Tau> PATMuMuEleSCQuadTauExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleSCMuMuQuad, pat::Tau> PATEleSCMuMuQuadTauExtraCountFiller;

typedef LeptonExtraCountFiller<PATMuMuMuTauQuad, pat::Muon> PATMuMuMuTauQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuTauTauQuad, pat::Muon> PATMuMuTauTauQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleTauQuad, pat::Muon> PATMuMuEleTauQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleMuQuad, pat::Muon> PATMuMuEleMuQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleEleQuad, pat::Muon> PATMuMuEleEleQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuMuMuQuad, pat::Muon> PATMuMuMuMuQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleTauTauQuad, pat::Muon> PATEleEleTauTauQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleTauQuad, pat::Muon> PATEleEleEleTauQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleMuTauQuad, pat::Muon> PATEleEleMuTauQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleMuQuad, pat::Muon> PATEleEleEleMuQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleEleQuad, pat::Muon> PATEleEleEleEleQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleMuMuQuad, pat::Muon> PATEleEleMuMuQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleSCQuad, pat::Muon> PATEleEleEleSCQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleSCEleEleQuad, pat::Muon> PATEleSCEleEleQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleSCQuad, pat::Muon> PATMuMuEleSCQuadMuExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleSCMuMuQuad, pat::Muon> PATEleSCMuMuQuadMuExtraCountFiller;

typedef LeptonExtraCountFiller<PATMuMuMuTauQuad, pat::Electron> PATMuMuMuTauQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuTauTauQuad, pat::Electron> PATMuMuTauTauQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleTauQuad, pat::Electron> PATMuMuEleTauQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleMuQuad, pat::Electron> PATMuMuEleMuQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleEleQuad, pat::Electron> PATMuMuEleEleQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuMuMuQuad, pat::Electron> PATMuMuMuMuQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleTauTauQuad, pat::Electron> PATEleEleTauTauQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleTauQuad, pat::Electron> PATEleEleEleTauQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleMuTauQuad, pat::Electron> PATEleEleMuTauQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleMuQuad, pat::Electron> PATEleEleEleMuQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleEleQuad, pat::Electron> PATEleEleEleEleQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleMuMuQuad, pat::Electron> PATEleEleMuMuQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleEleEleSCQuad, pat::Electron> PATEleEleEleSCQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleSCEleEleQuad, pat::Electron> PATEleSCEleEleQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATMuMuEleSCQuad, pat::Electron> PATMuMuEleSCQuadEleExtraCountFiller;
typedef LeptonExtraCountFiller<PATEleSCMuMuQuad, pat::Electron> PATEleSCMuMuQuadEleExtraCountFiller;
