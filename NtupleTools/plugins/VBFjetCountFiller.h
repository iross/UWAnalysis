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
class VBFjetCountFiller : public NtupleFillerBase
{
    protected:
        int VBFcounts;
        edm::InputTag src_; // input collection
        std::string sel_;   // string-based cuts
        std::string tag_;   // name for this n-tuple branch

        StringCutObjectSelector<pat::Jet>*function;
        

    public:
        VBFjetCountFiller()
        {
        }

        VBFjetCountFiller(const edm::ParameterSet& iConfig, TTree* t):
             src_(iConfig.getParameter<edm::InputTag>("src")),
             sel_(iConfig.getParameter<std::string>("method")),
             tag_(iConfig.getParameter<std::string>("tag"))
        {
            VBFcounts = 0;
            t->Branch(tag_.c_str(), &VBFcounts, (tag_+"/I").c_str());
            function = new StringCutObjectSelector<pat::Jet>(sel_,true);
        }


        ~VBFjetCountFiller()
        { 
            if( function != 0 )
                delete function;
        }


        void fill(const edm::Event& iEvent, const edm::EventSetup &iSetup)
        {
            edm::Handle<std::vector<T> > cands;

            VBFcounts = 0;

            if( iEvent.getByLabel(src_, cands) )
            {
                if( cands->size() > 0 )
                {
                    for( unsigned int i = 0; i < cands->at(0).jets().size(); ++i )
                    {
                        if( (*function)(*(cands->at(0).jets().at(i))) )
                            VBFcounts++;
                    }
                }
            }
        }
};


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef VBFjetCountFiller<PATMuTauPair> PATMuTauPairVBFjetCountFiller;
typedef VBFjetCountFiller<PATMuJetPair> PATMuJetPairVBFjetCountFiller;
typedef VBFjetCountFiller<PATElecTauPair> PATEleTauPairVBFjetCountFiller;
typedef VBFjetCountFiller<PATElecMuPair> PATEleMuPairVBFjetCountFiller;
typedef VBFjetCountFiller<PATMuPair> PATMuPairVBFjetCountFiller;
typedef VBFjetCountFiller<PATDiTauPair> PATDiTauPairVBFjetCountFiller;

typedef VBFjetCountFiller<PATMuMuTauTauQuad> PATMuMuTauTauQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATMuMuMuTauQuad> PATMuMuMuTauQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATMuMuEleTauQuad> PATMuMuEleTauQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATMuMuEleMuQuad> PATMuMuEleMuQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATMuMuMuMuQuad> PATMuMuMuMuQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATMuMuEleEleQuad> PATMuMuEleEleQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleEleTauTauQuad> PATEleEleTauTauQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleEleEleTauQuad> PATEleEleEleTauQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleEleMuTauQuad> PATEleEleMuTauQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleEleEleMuQuad> PATEleEleEleMuQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleEleEleEleQuad> PATEleEleEleEleQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleEleMuMuQuad> PATEleEleMuMuQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleEleEleSCQuad> PATEleEleEleSCQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleSCEleEleQuad> PATEleSCEleEleQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATMuMuEleSCQuad> PATMuMuEleSCQuadVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleSCMuMuQuad> PATEleSCMuMuQuadVBFjetCountFiller;

typedef VBFjetCountFiller<PATMuMuMuTri> PATMuMuMuTriVBFjetCountFiller;
typedef VBFjetCountFiller<PATMuMuEleTri> PATMuMuEleTriVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleEleMuTri> PATEleEleMuTriVBFjetCountFiller;
typedef VBFjetCountFiller<PATEleEleEleTri> PATEleEleEleTriVBFjetCountFiller;
