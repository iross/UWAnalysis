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

class LeptonExtraCountTriFiller : public NtupleFillerBase {
    public:
        LeptonExtraCountTriFiller(){
        }


        LeptonExtraCountTriFiller(const edm::ParameterSet& iConfig, TTree* t):
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


        ~LeptonExtraCountTriFiller()
        { 
            if(function!=0) delete function;
        }


        void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
            edm::Handle<edm::View<pat::Tau> > handle;
            edm::Handle<std::vector<T> > candHandle;
            value=0;
            if(iEvent.getByLabel(src_,handle)) {
                if(iEvent.getByLabel(candSrc_,candHandle)){
                    //loop over handle, sum those passing the requirements
                    for (unsigned int i = 0; i < handle->size(); i++) {
                        if ((*function)(handle->at(i))){
                            if (reco::deltaR( handle->at(i).p4(),candHandle->at(0).leg1()->leg1()->p4() ) > mindR_){
                                if (reco::deltaR( handle->at(i).p4(),candHandle->at(0).leg1()->leg2()->p4() ) > mindR_){
                                    if (reco::deltaR( handle->at(i).p4(),candHandle->at(0).leg2()->p4() ) > mindR_){
                                        value++; 
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

typedef LeptonExtraCountTriFiller<PATMuMuMuTri, pat::Tau> PATMuMuMuTriTauExtraCountFiller;
typedef LeptonExtraCountTriFiller<PATMuMuEleTri, pat::Tau> PATMuMuEleTriTauExtraCountFiller;
typedef LeptonExtraCountTriFiller<PATEleEleMuTri, pat::Tau> PATEleEleMuTriTauExtraCountFiller;
typedef LeptonExtraCountTriFiller<PATEleEleEleTri, pat::Tau> PATEleEleEleTriTauExtraCountFiller;

typedef LeptonExtraCountTriFiller<PATMuMuMuTri, pat::Muon> PATMuMuMuTriMuExtraCountFiller;
typedef LeptonExtraCountTriFiller<PATMuMuEleTri, pat::Muon> PATMuMuEleTriMuExtraCountFiller;
typedef LeptonExtraCountTriFiller<PATEleEleMuTri, pat::Muon> PATEleEleMuTriMuExtraCountFiller;
typedef LeptonExtraCountTriFiller<PATEleEleEleTri, pat::Muon> PATEleEleEleTriMuExtraCountFiller;

typedef LeptonExtraCountTriFiller<PATMuMuMuTri, pat::Electron> PATMuMuMuTriEleExtraCountFiller;
typedef LeptonExtraCountTriFiller<PATMuMuEleTri, pat::Electron> PATMuMuEleTriEleExtraCountFiller;
typedef LeptonExtraCountTriFiller<PATEleEleMuTri, pat::Electron> PATEleEleMuTriEleExtraCountFiller;
typedef LeptonExtraCountTriFiller<PATEleEleEleTri, pat::Electron> PATEleEleEleTriEleExtraCountFiller;

