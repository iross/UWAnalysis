// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include <TTree.h>

#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"

//
// class decleration
//
template<typename T>
class JetCountFiller : public NtupleFillerBase {
    public:
        JetCountFiller(){
        }

        JetCountFiller(const edm::ParameterSet& iConfig, TTree* t):
            NtupleFillerBase(iConfig,t),
            src_(iConfig.getParameter<edm::InputTag>("src")),
            var_(iConfig.getParameter<std::string>("method")),
            tag_(iConfig.getParameter<std::string>("tag")),
            leadingOnly_(iConfig.getUntrackedParameter<bool>("leadingOnly",true))
        {
            value = new std::vector<int>();
            singleValue=0;
            function = new StringCutObjectSelector<pat::Jet>(var_,true);

            if(!leadingOnly_)
                vbranch = t->Branch(tag_.c_str(),"std::vector<int>",&value);
            else
                vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/I").c_str());
        }


        ~JetCountFiller()
        { 
            if(function!=0) delete function;
        }


        void fill(const edm::Event& iEvent, const edm::EventSetup &iSetup)
        {
            edm::Handle<std::vector<T> > handle;

            singleValue=0;

            if(value->size()>0)
                value->clear();

            if(iEvent.getByLabel(src_,handle))
            {
                if(leadingOnly_)
                {
                    if(handle->size()>0)
                    {
                        singleValue=0;
                        for(unsigned int i=0;i<handle->at(0).jets().size();++i)
                            if((*function)(*(handle->at(0).jets().at(i))))
                                singleValue++;
                    }
                }
                else
                {
                    if(handle->size()>0)
                        for(unsigned int j=0;j<handle->size();++j)
                        {
                            singleValue=0;
                            for(unsigned int i=0;i<handle->at(j).jets().size();++i)
                                if((*function)(*(handle->at(j).jets().at(i))))
                                    singleValue ++;
                            value->push_back(singleValue);
                        }    
                }


            }
            else
            {
                printf("Obj not found \n");
            }
            //    vbranch->Fill();
        }


    protected:
        edm::InputTag src_;
        std::string var_;
        std::string tag_;
        bool leadingOnly_;
        std::vector<int>* value;
        int singleValue;
        StringCutObjectSelector<pat::Jet>*function;
        TBranch *vbranch;

};


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef JetCountFiller<PATMuTauPair> PATMuTauPairJetCountFiller;
typedef JetCountFiller<PATMuJetPair> PATMuJetPairJetCountFiller;
typedef JetCountFiller<PATElecTauPair> PATEleTauPairJetCountFiller;
typedef JetCountFiller<PATElecMuPair> PATEleMuPairJetCountFiller;
typedef JetCountFiller<PATMuPair> PATMuPairJetCountFiller;
typedef JetCountFiller<PATDiTauPair> PATDiTauPairJetCountFiller;

typedef JetCountFiller<PATMuMuTauTauQuad> PATMuMuTauTauQuadJetCountFiller;
typedef JetCountFiller<PATMuMuMuTauQuad> PATMuMuMuTauQuadJetCountFiller;
typedef JetCountFiller<PATMuMuEleTauQuad> PATMuMuEleTauQuadJetCountFiller;
typedef JetCountFiller<PATMuMuEleMuQuad> PATMuMuEleMuQuadJetCountFiller;
typedef JetCountFiller<PATMuMuMuMuQuad> PATMuMuMuMuQuadJetCountFiller;
typedef JetCountFiller<PATMuMuEleEleQuad> PATMuMuEleEleQuadJetCountFiller;
typedef JetCountFiller<PATEleEleTauTauQuad> PATEleEleTauTauQuadJetCountFiller;
typedef JetCountFiller<PATEleEleEleTauQuad> PATEleEleEleTauQuadJetCountFiller;
typedef JetCountFiller<PATEleEleMuTauQuad> PATEleEleMuTauQuadJetCountFiller;
typedef JetCountFiller<PATEleEleEleMuQuad> PATEleEleEleMuQuadJetCountFiller;
typedef JetCountFiller<PATEleEleEleEleQuad> PATEleEleEleEleQuadJetCountFiller;
typedef JetCountFiller<PATEleEleMuMuQuad> PATEleEleMuMuQuadJetCountFiller;
typedef JetCountFiller<PATEleEleEleSCQuad> PATEleEleEleSCQuadJetCountFiller;
typedef JetCountFiller<PATMuMuEleSCQuad> PATMuMuEleSCQuadJetCountFiller;

typedef JetCountFiller<PATMuMuMuTri> PATMuMuMuTriJetCountFiller;
typedef JetCountFiller<PATMuMuEleTri> PATMuMuEleTriJetCountFiller;
typedef JetCountFiller<PATEleEleMuTri> PATEleEleMuTriJetCountFiller;
typedef JetCountFiller<PATEleEleEleTri> PATEleEleEleTriJetCountFiller;
