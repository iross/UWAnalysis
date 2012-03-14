
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEtFwd.h"
#include "DataFormats/Common/interface/Wrapper.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "UWAnalysis/DataFormats/interface/SVfitDiTauSolution.h"
#include "UWAnalysis/DataFormats/interface/SVfitLegSolution.h"

namespace {
  struct UWanalysis_DataFormats_dictionary {
    /// create dictionaries for DiCandidatePair objects
    DiCandidatePair dummyDiCandidatePair;
    edm::Wrapper<DiCandidatePair> dummyDiCandidatePairWrapper;
    DiCandidatePairCollection dummyDiCandidatePairCollection;
    edm::Wrapper<DiCandidatePairCollection> dummyDiCandidatePairCollectionWrapper;

    /// create dictionaries for 
    ///  o edm::Ptr<pat::Electron> 
    ///  o edm::Ptr<pat::Muon> 
    ///  o edm::Ptr<pat::Tau>
    ///  o edm::Ptr<pat::Jet>
    /// as these dictionaries are not yet created in DataFormats/PatCandidates/src/classes.h
    //    edm::Ptr<pat::Electron> dummyPATElectronPtr;
    //  edm::Ptr<pat::Muon> dummyPATMuonPtr;
    //    edm::Ptr<pat::Tau> dummyPATTauPtr;
    //  edm::Ptr<pat::Jet> dummyPATJetPtr;
    // edm::Ptr<pat::MET> dummyPATMETPtr;
    edm::Ptr<reco::RecoChargedCandidate> dummyRecoChargeCandPtr;
    edm::Ptr<reco::RecoEcalCandidate> dummyRecoEcalCandPtr;
    std::vector<edm::Ptr<pat::Jet> > dummyPATJetPtrVector;




    /// create dictionaries for 
    ///  o edm::Ptr<reco::CaloJet>
    ///  o edm::Ptr<reco::PFJet>
    /// as these dictionaries are not yet created in DataFormats/JetReco/src/classes.h
    edm::Ptr<reco::CaloJet> dummyCaloJetPtr;
    edm::Ptr<reco::PFJet> dummyPFJetPtr;

    /// create dictionaries for
    ///  o edm::Ptr<reco::GenParticle>
    /// as these dictionaries are not yet created in DataFormats/HepMCCandidate/src/classes.h
    edm::Ptr<reco::GenParticle> dummyGenParticlePtr;

    /// create dictionaries for
    ///  o edm::Ptr<reco::Track>
    ///  o edm::Ptr<reco::GsfTrack>
    /// as these dictionaries are not yet created in DataFormats/TrackReco/src/classes.h (DataFormats/GsfTrackReco/src/classes.h)
    edm::Ptr<reco::Track> dummyTrackPtr;
    edm::Ptr<reco::GsfTrack> dummyGsfTrackPtr;

    /// create dictionaries for PATElecPair objects
    PATElecPair dummyPATElecPair;
    edm::Wrapper<PATElecPair> dummyPATElecPairWrapper;
    PATElecPairCollection dummyPATElecPairCollection;
    edm::Wrapper<PATElecPairCollection> dummyPATElecPairCollectionWrapper;
    edm::Ptr<PATElecPair> dummyPATElecPairPtr;



    /// create dictionaries for PATMuPair objects
    PATMuPair dummyPATMuPair;
    edm::Wrapper<PATMuPair> dummyPATMuPairWrapper;
    PATMuPairCollection dummyPATMuPairCollection;
    edm::Wrapper<PATMuPairCollection> dummyPATMuPairCollectionWrapper;
    edm::Ptr<PATMuPair> dummyPATMuPairPtr;


    /// create dictionaries for PATElecTauPair objects
    PATElecTauPair dummyPATElecTauPair;
    edm::Wrapper<PATElecTauPair> dummyPATElecTauPairWrapper;
    PATElecTauPairCollection dummyPATElecTauPairCollection;
    edm::Wrapper<PATElecTauPairCollection> dummyPATElecTauPairCollectionWrapper;
    edm::Ref<PATElecTauPairCollection> dummyPATElecTauPairRef;
    edm::RefVector<PATElecTauPairCollection> dummyPATElecTauPairRefVector;
    edm::RefProd<PATElecTauPairCollection> dummyPATElecTauPairRefProd;
    edm::Ptr<PATElecTauPair> dummyPATElecTauPairPtr;


    /// create dictionaries for PATElecSCPair objects
    PATElecSCPair dummyPATElecSCPair;
    edm::Wrapper<PATElecSCPair> dummyPATElecSCPairWrapper;
    PATElecSCPairCollection dummyPATElecSCPairCollection;
    edm::Wrapper<PATElecSCPairCollection> dummyPATElecSCPairCollectionWrapper;
    edm::Ref<PATElecSCPairCollection> dummyPATElecSCPairRef;
    edm::RefVector<PATElecSCPairCollection> dummyPATElecSCPairRefVector;
    edm::RefProd<PATElecSCPairCollection> dummyPATElecSCPairRefProd;
    edm::Ptr<PATElecSCPair> dummyPATElecSCPairPtr;



    /// create dictionaries for PATMuTauPair objects
    PATMuTauPair dummyPATMuTauPair;
    edm::Wrapper<PATMuTauPair> dummyPATMuTauPairWrapper;
    PATMuTauPairCollection dummyPATMuTauPairCollection;
    edm::Wrapper<PATMuTauPairCollection> dummyPATMuTauPairCollectionWrapper;
    edm::Ref<PATMuTauPairCollection> dummyPATMuTauPairRef;
    edm::RefVector<PATMuTauPairCollection> dummyPATMuTauPairRefVector;
    edm::RefProd<PATMuTauPairCollection> dummyPATMuTauPairRefProd;
    edm::Ptr<PATMuTauPair> dummyPATMuTauPairPtr;


    /// create dictionaries for PATMuTauPair objects
    PATMuTrackPair dummyPATMuTrackPair;
    edm::Wrapper<PATMuTrackPair> dummyPATMuTrackPairWrapper;
    PATMuTrackPairCollection dummyPATMuTrackPairCollection;
    edm::Wrapper<PATMuTrackPairCollection> dummyPATMuTrackPairCollectionWrapper;
    edm::Ref<PATMuTrackPairCollection> dummyPATMuTrackPairRef;
    edm::RefVector<PATMuTrackPairCollection> dummyPATMuTrackPairRefVector;
    edm::RefProd<PATMuTrackPairCollection> dummyPATMuTrackPairRefProd;
    edm::Ptr<PATMuTrackPair> dummyPATMuTrackPairPtr;


    /// create dictionaries for PATEleTrackPair objects
    PATEleTrackPair dummyPATEleTrackPair;
    edm::Wrapper<PATEleTrackPair> dummyPATEleTrackPairWrapper;
    PATEleTrackPairCollection dummyPATEleTrackPairCollection;
    edm::Wrapper<PATEleTrackPairCollection> dummyPATEleTrackPairCollectionWrapper;
    edm::Ref<PATEleTrackPairCollection> dummyPATEleTrackPairRef;
    edm::RefVector<PATEleTrackPairCollection> dummyPATEleTrackPairRefVector;
    edm::RefProd<PATEleTrackPairCollection> dummyPATEleTrackPairRefProd;
    edm::Ptr<PATEleTrackPair> dummyPATEleTrackPairPtr;

/// create dictionaries for PATEleTrackPair objects
    PATTrackTrackPair dummyPATrackTrackPair;
    edm::Wrapper<PATTrackTrackPair> dummyPATTrackTrackPairWrapper;
    PATTrackTrackPairCollection dummyPATTrackTrackPairCollection;
    edm::Wrapper<PATTrackTrackPairCollection> dummyPATTrackTrackPairCollectionWrapper;
    edm::Ref<PATTrackTrackPairCollection> dummyPATTrackTrackPairRef;
    edm::RefVector<PATTrackTrackPairCollection> dummyPATTrackTrackPairRefVector;
    edm::RefProd<PATTrackTrackPairCollection> dummyPATTrackTrackPairRefProd;
    edm::Ptr<PATTrackTrackPair> dummyPATTrackTrackPairPtr;

    /// create dictionaries for PATDiTauPair objects
    PATDiTauPair dummyPATDiTauPair;
    edm::Wrapper<PATDiTauPair> dummyPATDiTauPairWrapper;
    PATDiTauPairCollection dummyPATDiTauPairCollection;
    edm::Wrapper<PATDiTauPairCollection> dummyPATDiTauPairCollectionWrapper;
    edm::Ref<PATDiTauPairCollection> dummyPATDiTauPairRef;
    edm::RefVector<PATDiTauPairCollection> dummyPATDiTauPairRefVector;
    edm::RefProd<PATDiTauPairCollection> dummyPATDiTauPairRefProd;
    edm::Ptr<PATDiTauPair> dummyPATDiTauPairPtr;
    

    /// create dictionaries for PATElecMuPair objects
    PATElecMuPair dummyPATElecMuPair;
    edm::Wrapper<PATElecMuPair> dummyPATElecMuPairWrapper;
    PATElecMuPairCollection dummyPATElecMuPairCollection;
    edm::Wrapper<PATElecMuPairCollection> dummyPATElecMuPairCollectionWrapper;
    edm::Ref<PATElecMuPairCollection> dummyPATElecMuPairRef;
    edm::RefVector<PATElecMuPairCollection> dummyPATElecMuPairRefVector;
    edm::RefProd<PATElecMuPairCollection> dummyPATElecMuPairRefProd;
    edm::Ptr<PATElecMuPair> dummyPATElecMuPairPtr;


    /// create dictionaries for PATTauNuPair objects
    PATTauNuPair dummyPATTauNuPair;
    edm::Wrapper<PATTauNuPair> dummyPATTauNuPairWrapper;
    PATTauNuPairCollection dummyPATTauNuPairCollection;
    edm::Wrapper<PATTauNuPairCollection> dummyPATTauNuPairCollectionWrapper;
    edm::Ptr<PATTauNuPair> dummyPATTauNuPairPtr;

    /// create dictionaries for PATMuonNuPair objects
    PATMuonNuPair dummyPATMuonNuPair;
    edm::Wrapper<PATMuonNuPair> dummyPATMuonNuPairWrapper;
    PATMuonNuPairCollection dummyPATMuonNuPairCollection;
    edm::Wrapper<PATMuonNuPairCollection> dummyPATMuonNuPairCollectionWrapper;
    edm::Ptr<PATMuonNuPair> dummyPATMuonNuPairPtr;

    /// create dictionaries for PATMuonNuPair objects
    PATElectronNuPair dummyPATElectronNuPair;
    edm::Wrapper<PATElectronNuPair> dummyPATElectronNuPairWrapper;
    PATElectronNuPairCollection dummyPATElectronNuPairCollection;
    edm::Wrapper<PATElectronNuPairCollection> dummyPATElectronNuPairCollectionWrapper;
    edm::Ptr<PATElectronNuPair> dummyPATElectronNuPairPtr;

    /// create dictionaries for PATMuonNuPair objects
    PATCandNuPair dummyPATCandNuPair;
    edm::Wrapper<PATCandNuPair> dummyPATCandNuPairWrapper;
    PATCandNuPairCollection dummyPATCandNuPairCollection;
    edm::Wrapper<PATCandNuPairCollection> dummyPATCandNuPairCollectionWrapper;

	//Di-boson candidate dictionaries
	
    /// create dictionaries for PATMuMuMuTauQuad objects
    PATMuMuMuTauQuad dummyPATMuMuMuTauQuad;
    edm::Wrapper<PATMuMuMuTauQuad> dummyPATMuMuMuTauTauQuadWrapper;
    PATMuMuMuTauQuadCollection dummyPATMuMuMuTauQuadCollection;
    edm::Wrapper<PATMuMuMuTauQuadCollection> dummyPATMuMuMuTauQuadCollectionWrapper;
    edm::Ref<PATMuMuMuTauQuadCollection> dummyPATMuMuMuTauQuadRef;
    edm::RefVector<PATMuMuMuTauQuadCollection> dummyPATMuMuMuTauQuadRefVector;
    edm::RefProd<PATMuMuMuTauQuadCollection> dummyPATMuMuMuTauQuadRefProd;
    edm::Ptr<PATMuMuMuTauQuad> dummyPATMuMuMuTauQuadPtr;

    /// create dictionaries for PATMuMuTauTauQuad objects
    PATMuMuTauTauQuad dummyPATMuMuTauTauQuad;
    edm::Wrapper<PATMuMuTauTauQuad> dummyPATMuMuTauTauTauQuadWrapper;
    PATMuMuTauTauQuadCollection dummyPATMuMuTauTauQuadCollection;
    edm::Wrapper<PATMuMuTauTauQuadCollection> dummyPATMuMuTauTauQuadCollectionWrapper;
    edm::Ref<PATMuMuTauTauQuadCollection> dummyPATMuMuTauTauQuadRef;
    edm::RefVector<PATMuMuTauTauQuadCollection> dummyPATMuMuTauTauQuadRefVector;
    edm::RefProd<PATMuMuTauTauQuadCollection> dummyPATMuMuTauTauQuadRefProd;
    edm::Ptr<PATMuMuTauTauQuad> dummyPATMuMuTauTauQuadPtr;

    /// create dictionaries for PATMuMuEleTauQuad objects
    PATMuMuEleTauQuad dummyPATMuMuEleTauQuad;
    edm::Wrapper<PATMuMuEleTauQuad> dummyPATMuMuEleTauQuadWrapper;
    PATMuMuEleTauQuadCollection dummyPATMuMuEleTauQuadCollection;
    edm::Wrapper<PATMuMuEleTauQuadCollection> dummyPATMuMuEleTauQuadCollectionWrapper;
    edm::Ref<PATMuMuEleTauQuadCollection> dummyPATMuMuEleTauQuadRef;
    edm::RefVector<PATMuMuEleTauQuadCollection> dummyPATMuMuEleTauQuadRefVector;
    edm::RefProd<PATMuMuEleTauQuadCollection> dummyPATMuMuEleTauQuadRefProd;
    edm::Ptr<PATMuMuEleTauQuad> dummyPATMuMuEleTauQuadPtr;

    /// create dictionaries for PATMuMuEleEleQuad objects
    PATMuMuEleEleQuad dummyPATMuMuEleEleQuad;
    edm::Wrapper<PATMuMuEleEleQuad> dummyPATMuMuEleEleQuadWrapper;
    PATMuMuEleEleQuadCollection dummyPATMuMuEleEleQuadCollection;
    edm::Wrapper<PATMuMuEleEleQuadCollection> dummyPATMuMuEleEleQuadCollectionWrapper;
    edm::Ref<PATMuMuEleEleQuadCollection> dummyPATMuMuEleEleQuadRef;
    edm::RefVector<PATMuMuEleEleQuadCollection> dummyPATMuMuEleEleQuadRefVector;
    edm::RefProd<PATMuMuEleEleQuadCollection> dummyPATMuMuEleEleQuadRefProd;
    edm::Ptr<PATMuMuEleEleQuad> dummyPATMuMuEleEleQuadPtr;

    /// create dictionaries for PATMuMuEleMuQuad objects
    PATMuMuEleMuQuad dummyPATMuMuEleMuQuad;
    edm::Wrapper<PATMuMuEleMuQuad> dummyPATMuMuEleMuTauQuadWrapper;
    PATMuMuEleMuQuadCollection dummyPATMuMuEleMuQuadCollection;
    edm::Wrapper<PATMuMuEleMuQuadCollection> dummyPATMuMuEleMuQuadCollectionWrapper;
    edm::Ref<PATMuMuEleMuQuadCollection> dummyPATMuMuEleMuQuadRef;
    edm::RefVector<PATMuMuEleMuQuadCollection> dummyPATMuMuEleMuQuadRefVector;
    edm::RefProd<PATMuMuEleMuQuadCollection> dummyPATMuMuEleMuQuadRefProd;
    edm::Ptr<PATMuMuEleMuQuad> dummyPATMuMuEleMuQuadPtr;

    /// create dictionaries for PATMuMuMuMuQuad objects
    PATMuMuMuMuQuad dummyPATMuMuMuMuQuad;
    edm::Wrapper<PATMuMuMuMuQuad> dummyPATMuMuMuMuTauQuadWrapper;
    PATMuMuMuMuQuadCollection dummyPATMuMuMuMuQuadCollection;
    edm::Wrapper<PATMuMuMuMuQuadCollection> dummyPATMuMuMuMuQuadCollectionWrapper;
    edm::Ref<PATMuMuMuMuQuadCollection> dummyPATMuMuMuMuQuadRef;
    edm::RefVector<PATMuMuMuMuQuadCollection> dummyPATMuMuMuMuQuadRefVector;
    edm::RefProd<PATMuMuMuMuQuadCollection> dummyPATMuMuMuMuQuadRefProd;
    edm::Ptr<PATMuMuMuMuQuad> dummyPATMuMuMuMuQuadPtr;


    /// create dictionaries for PATEleEleEleTauQuad objects
    PATEleEleEleTauQuad dummyPATEleEleEleTauQuad;
    edm::Wrapper<PATEleEleEleTauQuad> dummyPATEleEleEleTauTauQuadWrapper;
    PATEleEleEleTauQuadCollection dummyPATEleEleEleTauQuadCollection;
    edm::Wrapper<PATEleEleEleTauQuadCollection> dummyPATEleEleEleTauQuadCollectionWrapper;
    edm::Ref<PATEleEleEleTauQuadCollection> dummyPATEleEleEleTauQuadRef;
    edm::RefVector<PATEleEleEleTauQuadCollection> dummyPATEleEleEleTauQuadRefVector;
    edm::RefProd<PATEleEleEleTauQuadCollection> dummyPATEleEleEleTauQuadRefProd;
    edm::Ptr<PATEleEleEleTauQuad> dummyPATEleEleEleTauQuadPtr;

    /// create dictionaries for PATEleEleTauTauQuad objects
    PATEleEleTauTauQuad dummyPATEleEleTauTauQuad;
    edm::Wrapper<PATEleEleTauTauQuad> dummyPATEleEleTauTauTauQuadWrapper;
    PATEleEleTauTauQuadCollection dummyPATEleEleTauTauQuadCollection;
    edm::Wrapper<PATEleEleTauTauQuadCollection> dummyPATEleEleTauTauQuadCollectionWrapper;
    edm::Ref<PATEleEleTauTauQuadCollection> dummyPATEleEleTauTauQuadRef;
    edm::RefVector<PATEleEleTauTauQuadCollection> dummyPATEleEleTauTauQuadRefVector;
    edm::RefProd<PATEleEleTauTauQuadCollection> dummyPATEleEleTauTauQuadRefProd;
    edm::Ptr<PATEleEleTauTauQuad> dummyPATEleEleTauTauQuadPtr;

    /// create dictionaries for PATEleEleEleEleQuad objects
    PATEleEleEleEleQuad dummyPATEleEleEleEleQuad;
    edm::Wrapper<PATEleEleEleEleQuad> dummyPATEleEleEleEleTauQuadWrapper;
    PATEleEleEleEleQuadCollection dummyPATEleEleEleEleQuadCollection;
    edm::Wrapper<PATEleEleEleEleQuadCollection> dummyPATEleEleEleEleQuadCollectionWrapper;
    edm::Ref<PATEleEleEleEleQuadCollection> dummyPATEleEleEleEleQuadRef;
    edm::RefVector<PATEleEleEleEleQuadCollection> dummyPATEleEleEleEleQuadRefVector;
    edm::RefProd<PATEleEleEleEleQuadCollection> dummyPATEleEleEleEleQuadRefProd;
    edm::Ptr<PATEleEleEleEleQuad> dummyPATEleEleEleEleQuadPtr;

    /// create dictionaries for PATEleEleMuTauQuad objects
    PATEleEleMuTauQuad dummyPATEleEleMuTauQuad;
    edm::Wrapper<PATEleEleMuTauQuad> dummyPATEleEleMuTauTauQuadWrapper;
    PATEleEleMuTauQuadCollection dummyPATEleEleMuTauQuadCollection;
    edm::Wrapper<PATEleEleMuTauQuadCollection> dummyPATEleEleMuTauQuadCollectionWrapper;
    edm::Ref<PATEleEleMuTauQuadCollection> dummyPATEleEleMuTauQuadRef;
    edm::RefVector<PATEleEleMuTauQuadCollection> dummyPATEleEleMuTauQuadRefVector;
    edm::RefProd<PATEleEleMuTauQuadCollection> dummyPATEleEleMuTauQuadRefProd;
    edm::Ptr<PATEleEleMuTauQuad> dummyPATEleEleMuTauQuadPtr;

    /// create dictionaries for PATEleEleEleMuQuad objects
    PATEleEleEleMuQuad dummyPATEleEleEleMuQuad;
    edm::Wrapper<PATEleEleEleMuQuad> dummyPATEleEleEleMuQuadWrapper;
    PATEleEleEleMuQuadCollection dummyPATEleEleEleMuQuadCollection;
    edm::Wrapper<PATEleEleEleMuQuadCollection> dummyPATEleEleEleMuQuadCollectionWrapper;
    edm::Ref<PATEleEleEleMuQuadCollection> dummyPATEleEleEleMuQuadRef;
    edm::RefVector<PATEleEleEleMuQuadCollection> dummyPATEleEleEleMuQuadRefVector;
    edm::RefProd<PATEleEleEleMuQuadCollection> dummyPATEleEleEleMuQuadRefProd;
    edm::Ptr<PATEleEleEleMuQuad> dummyPATEleEleEleMuQuadPtr;

    /// create dictionaries for PATEleEleMuMuQuad objects
    edm::Wrapper<PATEleEleMuMuQuad> dummyPATEleEleMuMuQuadWrapper;
    PATEleEleMuMuQuadCollection dummyPATEleEleMuMuQuadCollection;
    edm::Wrapper<PATEleEleMuMuQuadCollection> dummyPATEleEleMuMuQuadCollectionWrapper;
    edm::Ref<PATEleEleMuMuQuadCollection> dummyPATEleEleMuMuQuadRef;
    edm::RefVector<PATEleEleMuMuQuadCollection> dummyPATEleEleMuMuQuadRefVector;
    edm::RefProd<PATEleEleMuMuQuadCollection> dummyPATEleEleMuMuQuadRefProd;
    edm::Ptr<PATEleEleMuMuQuad> dummyPATEleEleMuMuQuadPtr;
	
    /// create dictionaries for PATMuMuMuNuQuad objects
    edm::Wrapper<PATMuMuMuNuQuad> dummyPATMuMuMuNuQuadWrapper;
    PATMuMuMuNuQuadCollection dummyPATMuMuMuNuQuadCollection;
    edm::Wrapper<PATMuMuMuNuQuadCollection> dummyPATMuMuMuNuQuadCollectionWrapper;
    edm::Ref<PATMuMuMuNuQuadCollection> dummyPATMuMuMuNuQuadRef;
    edm::RefVector<PATMuMuMuNuQuadCollection> dummyPATMuMuMuNuQuadRefVector;
    edm::RefProd<PATMuMuMuNuQuadCollection> dummyPATMuMuMuNuQuadRefProd;
    edm::Ptr<PATMuMuMuNuQuad> dummyPATMuMuMuNuQuadPtr;
    /// create dictionaries for PATEleEleMuNuQuad objects
    edm::Wrapper<PATEleEleMuNuQuad> dummyPATEleEleMuNuQuadWrapper;
    PATEleEleMuNuQuadCollection dummyPATEleEleMuNuQuadCollection;
    edm::Wrapper<PATEleEleMuNuQuadCollection> dummyPATEleEleMuNuQuadCollectionWrapper;
    edm::Ref<PATEleEleMuNuQuadCollection> dummyPATEleEleMuNuQuadRef;
    edm::RefVector<PATEleEleMuNuQuadCollection> dummyPATEleEleMuNuQuadRefVector;
    edm::RefProd<PATEleEleMuNuQuadCollection> dummyPATEleEleMuNuQuadRefProd;
    edm::Ptr<PATEleEleMuNuQuad> dummyPATEleEleMuNuQuadPtr;
    /// create dictionaries for PATMuMuEleNuQuad objects
    edm::Wrapper<PATMuMuEleNuQuad> dummyPATMuMuEleNuQuadWrapper;
    PATMuMuEleNuQuadCollection dummyPATMuMuEleNuQuadCollection;
    edm::Wrapper<PATMuMuEleNuQuadCollection> dummyPATMuMuEleNuQuadCollectionWrapper;
    edm::Ref<PATMuMuEleNuQuadCollection> dummyPATMuMuEleNuQuadRef;
    edm::RefVector<PATMuMuEleNuQuadCollection> dummyPATMuMuEleNuQuadRefVector;
    edm::RefProd<PATMuMuEleNuQuadCollection> dummyPATMuMuEleNuQuadRefProd;
    edm::Ptr<PATMuMuEleNuQuad> dummyPATMuMuEleNuQuadPtr;
    /// create dictionaries for PATEleEleEleNuQuad objects
    edm::Wrapper<PATEleEleEleNuQuad> dummyPATEleEleEleNuQuadWrapper;
    PATEleEleEleNuQuadCollection dummyPATEleEleEleNuQuadCollection;
    edm::Wrapper<PATEleEleEleNuQuadCollection> dummyPATEleEleEleNuQuadCollectionWrapper;
    edm::Ref<PATEleEleEleNuQuadCollection> dummyPATEleEleEleNuQuadRef;
    edm::RefVector<PATEleEleEleNuQuadCollection> dummyPATEleEleEleNuQuadRefVector;
    edm::RefProd<PATEleEleEleNuQuadCollection> dummyPATEleEleEleNuQuadRefProd;
    edm::Ptr<PATEleEleEleNuQuad> dummyPATEleEleEleNuQuadPtr;


    /// create dictionaries for PATEleEleEleQuad objects                                                                                                                                               
    PATEleEleEle dummyPATEleEleEle;
    edm::Wrapper<PATEleEleEle> dummyPATEleEleEleWrapper;
    PATEleEleEleCollection dummyPATEleEleEleCollection;
    edm::Wrapper<PATEleEleEleCollection> dummyPATEleEleEleCollectionWrapper;
    edm::Ref<PATEleEleEleCollection> dummyPATEleEleEleRef;
    edm::RefVector<PATEleEleEleCollection> dummyPATEleEleEleRefVector;
    edm::RefProd<PATEleEleEleCollection> dummyPATEleEleEleRefProd;
    edm::Ptr<PATEleEleEle> dummyPATEleEleElePtr;
    //create dictionaries for SVFit
    SVfitDiTauSolution dummySVfitDiTauSolution;
    std::vector<SVfitDiTauSolution> dummySVfitDiTauSolutionCollection;
    std::vector<SVfitLegSolution> dummySVfitLegSolutionCollection;
    std::map<std::string, double> dummySVfitDiTauSolutionLogLikeMap;
    std::map<std::string, std::map<std::string, double> > dummySVfitDiTauSolutionLogLikeMapMap;
    std::map<std::string, SVfitDiTauSolution> dummySVfitDiTauSolutionMap;
    std::map<std::string, std::map<std::string, SVfitDiTauSolution> > dummySVfitDiTauSolutionMapMap;



  };
}
