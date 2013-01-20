// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "Math/GenVector/VectorUtil.h"

#include <TTree.h>

#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"

/**
 * This class is used to count the number of jets passing VBF criteria, and
 * store the count in the n-tuple.
 *
 * @author D. Austin Belknap
 *
 * @file VBFjetCountFiller.h
 */
template<typename T>
class VBFjetCountFiller : public NtupleFillerBase
{
    // rename 4-vector for convenience
    typedef reco::Candidate::LorentzVector FourVec; 

    protected:
        int VBFcounts;
        edm::InputTag src_; // input collection
        std::string sel_;   // string-based cuts
        std::string tag_;   // name for this n-tuple branch

        StringCutObjectSelector<pat::Jet>*function; // for jet selections
        

    public:
        VBFjetCountFiller()
        {
        }

        /**
         * Initialize the input source collection, the jet selectrion string,
         * and the n-tuple branch name (tag). Also create the new branch and
         * the jet selection functor.
         */
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


        /**
         * Assign the number of VBF candidate jets to 'VBFcounts'.
         */
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
                        // apply string-based cuts
                        if( (*function)(*(cands->at(0).jets().at(i))) )
                        {
                            // apply cross-cleaning against the 4 leptons and
                            // FSR photons (if any).
                            
                            FourVec jet_p4 = cands->at(0).jets().at(i)->p4();

                            // store lepton and FSR 4-vectors
                            std::vector<FourVec> leptons_FSR;

                            leptons_FSR.push_back( cands->at(0).leg1()->leg1()->p4() );
                            leptons_FSR.push_back( cands->at(0).leg1()->leg2()->p4() );
                            leptons_FSR.push_back( cands->at(0).leg2()->leg1()->p4() );
                            leptons_FSR.push_back( cands->at(0).leg2()->leg2()->p4() );

                            FourVec FSR1 = cands->at(0).leg1()->p4() - cands->at(0).leg1()->noPhoP4();
                            FourVec FSR2 = cands->at(0).leg2()->p4() - cands->at(0).leg2()->noPhoP4();

                            // only add the FSR photons if they exist
                            if ( FSR1.Pt() > 1 )
                                leptons_FSR.push_back( FSR1 );
                            if ( FSR2.Pt() > 1 )
                                leptons_FSR.push_back( FSR2 );

                            bool passed = true;
                            for ( unsigned int i = 0; i < leptons_FSR.size(); ++i )
                                if ( ROOT::Math::VectorUtil::DeltaR( leptons_FSR.at(i), jet_p4 ) <= 0.5 )
                                    passed = false;

                            if ( passed )
                                VBFcounts++;
                        }
                    }
                }
            }
        }
};


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

// typedef VBFjetCountFiller<PATMuTauPair> PATMuTauPairVBFjetCountFiller;
// typedef VBFjetCountFiller<PATMuJetPair> PATMuJetPairVBFjetCountFiller;
// typedef VBFjetCountFiller<PATElecTauPair> PATEleTauPairVBFjetCountFiller;
// typedef VBFjetCountFiller<PATElecMuPair> PATEleMuPairVBFjetCountFiller;
// typedef VBFjetCountFiller<PATMuPair> PATMuPairVBFjetCountFiller;
// typedef VBFjetCountFiller<PATDiTauPair> PATDiTauPairVBFjetCountFiller;

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

// typedef VBFjetCountFiller<PATMuMuMuTri> PATMuMuMuTriVBFjetCountFiller;
// typedef VBFjetCountFiller<PATMuMuEleTri> PATMuMuEleTriVBFjetCountFiller;
// typedef VBFjetCountFiller<PATEleEleMuTri> PATEleEleMuTriVBFjetCountFiller;
// typedef VBFjetCountFiller<PATEleEleEleTri> PATEleEleEleTriVBFjetCountFiller;
