#ifndef UWAnalysis_DataFormats_CompositePtrCandidateT1T2MEtFwd_h
#define UWAnalysis_DataFormats_CompositePtrCandidateT1T2MEtFwd_h


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/RefVector.h"

#include <vector>

/// collection of CompositeRefCandidateT1T2MEt objects
typedef std::vector<DiCandidatePair> DiCandidatePairCollection;
typedef std::vector<PATElecPair> PATElecPairCollection;
typedef std::vector<PATMuPair> PATMuPairCollection;
typedef std::vector<PATElecTauPair> PATElecTauPairCollection;
typedef std::vector<PATElecSCPair> PATElecSCPairCollection;
typedef std::vector<PATMuTauPair> PATMuTauPairCollection;
typedef std::vector<PATMuTrackPair> PATMuTrackPairCollection;
typedef std::vector<PATEleTrackPair> PATEleTrackPairCollection;
typedef std::vector<PATDiTauPair> PATDiTauPairCollection;
typedef std::vector<PATTrackTrackPair> PATTrackTrackPairCollection;
typedef std::vector<PATElecMuPair> PATElecMuPairCollection;
typedef std::vector<PATMuMuMuTauQuad> PATMuMuMuTauQuadCollection;
typedef std::vector<PATMuMuTauTauQuad> PATMuMuTauTauQuadCollection;
typedef std::vector<PATMuMuEleTauQuad> PATMuMuEleTauQuadCollection;
typedef std::vector<PATMuMuEleMuQuad> PATMuMuEleMuQuadCollection;
typedef std::vector<PATMuMuMuMuQuad> PATMuMuMuMuQuadCollection;
typedef std::vector<PATMuMuEleEleQuad> PATMuMuEleEleQuadCollection;
typedef std::vector<PATEleEleEleTauQuad> PATEleEleEleTauQuadCollection;
typedef std::vector<PATEleEleTauTauQuad> PATEleEleTauTauQuadCollection;
typedef std::vector<PATEleEleEleEleQuad> PATEleEleEleEleQuadCollection;
typedef std::vector<PATEleEleMuTauQuad> PATEleEleMuTauQuadCollection;
typedef std::vector<PATEleEleEleMuQuad> PATEleEleEleMuQuadCollection;
typedef std::vector<PATEleEleMuMuQuad> PATEleEleMuMuQuadCollection;
typedef std::vector<PATMuMuMuNuQuad> PATMuMuMuNuQuadCollection;
typedef std::vector<PATMuMuEleNuQuad> PATMuMuEleNuQuadCollection;
typedef std::vector<PATEleEleMuNuQuad> PATEleEleMuNuQuadCollection;
typedef std::vector<PATEleEleEleNuQuad> PATEleEleEleNuQuadCollection;
typedef std::vector<PATEleEleEleTri> PATEleEleEleTriCollection;
typedef std::vector<PATEleEleMuTri> PATEleEleMuTriCollection;
typedef std::vector<PATMuMuEleTri> PATMuMuEleTriCollection;
typedef std::vector<PATMuMuMuTri> PATMuMuMuTriCollection;

/// persistent reference to a CompositeRefCandidateT1T2MEt object
typedef edm::Ref<DiCandidatePairCollection> DiCandidatePairRef;
typedef edm::Ref<PATElecPairCollection> PATElecPairRef;
typedef edm::Ref<PATMuPairCollection> PATMuPairRef;
typedef edm::Ref<PATElecTauPairCollection> PATElecTauPairRef;
typedef edm::Ref<PATElecSCPairCollection> PATElecSCPairRef;
typedef edm::Ref<PATMuTauPairCollection> PATMuTauPairRef;
typedef edm::Ref<PATMuTrackPairCollection> PATMuTrackPairRef;
typedef edm::Ref<PATEleTrackPairCollection> PATEleTrackPairRef;
typedef edm::Ref<PATTrackTrackPairCollection> PATTrackTrackRef;
typedef edm::Ref<PATDiTauPairCollection> PATDiTauPairRef;
typedef edm::Ref<PATElecMuPairCollection> PATElecMuPairRef;
typedef edm::Ref<PATMuMuMuTauQuadCollection> PATMuMuMuTauQuadRef;
typedef edm::Ref<PATMuMuTauTauQuadCollection> PATMuMuTauTauQuadRef;
typedef edm::Ref<PATMuMuEleTauQuadCollection> PATMuMuEleTauQuadRef;
typedef edm::Ref<PATMuMuEleMuQuadCollection> PATMuMuEleMuQuadRef;
typedef edm::Ref<PATMuMuMuMuQuadCollection> PATMuMuMuMuQuadRef;
typedef edm::Ref<PATMuMuEleEleQuadCollection> PATMuMuEleEleQuadRef;
typedef edm::Ref<PATEleEleEleTauQuadCollection> PATEleEleEleTauQuadRef;
typedef edm::Ref<PATEleEleTauTauQuadCollection> PATEleEleTauTauQuadRef;
typedef edm::Ref<PATEleEleEleEleQuadCollection> PATEleEleEleEleQuadRef;
typedef edm::Ref<PATEleEleMuTauQuadCollection> PATEleEleMuTauQuadRef;
typedef edm::Ref<PATEleEleEleMuQuadCollection> PATEleEleEleMuQuadRef;
typedef edm::Ref<PATEleEleMuMuQuadCollection> PATEleEleMuMuQuadRef;
typedef edm::Ref<PATMuMuMuNuQuadCollection> PATMuMuMuNuQuadRef;
typedef edm::Ref<PATMuMuEleNuQuadCollection> PATMuMuEleNuQuadRef;
typedef edm::Ref<PATEleEleMuNuQuadCollection> PATEleEleMuNuQuadRef;
typedef edm::Ref<PATEleEleEleNuQuadCollection> PATEleEleEleNuQuadRef;
typedef edm::Ref<PATEleEleEleTriCollection> PATEleEleEleTriRef;
typedef edm::Ref<PATEleEleMuTriCollection> PATEleEleMuTriRef;
typedef edm::Ref<PATMuMuEleTriCollection> PATMuMuEleTriRef;
typedef edm::Ref<PATMuMuMuTriCollection> PATMuMuMuTriRef;

/// references to CompositeRefCandidateT1T2MEt collection
typedef edm::RefProd<DiCandidatePairCollection> DiCandidatePairRefProd;
typedef edm::RefProd<PATElecPairCollection> PATElecPairRefProd;
typedef edm::RefProd<PATMuPairCollection> PATMuPairRefProd;
typedef edm::RefProd<PATElecTauPairCollection> PATElecTauPairRefProd;
typedef edm::RefProd<PATElecSCPairCollection> PATElecSCPairRefProd;
typedef edm::RefProd<PATMuTauPairCollection> PATMuTauPairRefProd;
typedef edm::RefProd<PATMuTrackPairCollection> PATMuTrackPairRefProd;
typedef edm::RefProd<PATEleTrackPairCollection> PATEleTrackPairRefProd;
typedef edm::RefProd<PATTrackTrackPairCollection> PATTrackTrackPairRefProd;
typedef edm::RefProd<PATDiTauPairCollection> PATDiTauPairRefProd;
typedef edm::RefProd<PATElecMuPairCollection> PATElecMuPairRefProd;
typedef edm::RefProd<PATMuMuMuTauQuadCollection> PATMuMuMuTauQuadRefProd;
typedef edm::RefProd<PATMuMuTauTauQuadCollection> PATMuMuTauTauQuadRefProd;
typedef edm::RefProd<PATMuMuEleTauQuadCollection> PATMuMuEleTauQuadRefProd;
typedef edm::RefProd<PATMuMuEleMuQuadCollection> PATMuMuEleMuQuadRefProd;
typedef edm::RefProd<PATMuMuMuMuQuadCollection> PATMuMuMuMuQuadRefProd;
typedef edm::RefProd<PATMuMuEleEleQuadCollection> PATMuMuEleEleQuadRefProd;
typedef edm::RefProd<PATEleEleEleTauQuadCollection> PATEleEleEleTauQuadRefProd;
typedef edm::RefProd<PATEleEleTauTauQuadCollection> PATEleEleTauTauQuadRefProd;
typedef edm::RefProd<PATEleEleEleEleQuadCollection> PATEleEleEleEleQuadRefProd;
typedef edm::RefProd<PATEleEleMuTauQuadCollection> PATEleEleMuTauQuadRefProd;
typedef edm::RefProd<PATEleEleEleMuQuadCollection> PATEleEleEleMuQuadRefProd;
typedef edm::RefProd<PATEleEleMuMuQuadCollection> PATEleEleMuMuQuadRefProd;
typedef edm::RefProd<PATMuMuMuNuQuadCollection> PATMuMuMuNuQuadRefProd;
typedef edm::RefProd<PATMuMuEleNuQuadCollection> PATMuMuEleNuQuadRefProd;
typedef edm::RefProd<PATEleEleMuNuQuadCollection> PATEleEleMuNuQuadRefProd;
typedef edm::RefProd<PATEleEleEleNuQuadCollection> PATEleEleEleNuQuadRefProd;
typedef edm::RefProd<PATEleEleEleTriCollection> PATEleEleEleTriRefProd;
typedef edm::RefProd<PATEleEleMuTriCollection> PATEleEleMuTriRefProd;
typedef edm::RefProd<PATMuMuEleTriCollection> PATMuMuEleTriRefProd;
typedef edm::RefProd<PATMuMuMuTriCollection> PATMuMuMuTriRefProd;

/// vector of references to CompositeRefCandidateT1T2MEt objects all in the same collection
typedef edm::RefVector<DiCandidatePairCollection> DiCandidatePairRefVector;
typedef edm::RefVector<PATElecPairCollection> PATElecPairRefVector;
typedef edm::RefVector<PATMuPairCollection> PATMuPairRefVector;
typedef edm::RefVector<PATMuTrackPairCollection> PATMuTrackPairRefVector;
typedef edm::RefVector<PATEleTrackPairCollection> PATEleTrackPairRefVector;
typedef edm::RefVector<PATTrackTrackPairCollection> PATTrackTrackPairRefVector;
typedef edm::RefVector<PATElecTauPairCollection> PATElecTauPairRefVector;
typedef edm::RefVector<PATElecSCPairCollection> PATElecSCPairRefVector;
typedef edm::RefVector<PATMuTauPairCollection> PATMuTauPairRefVector;
typedef edm::RefVector<PATDiTauPairCollection> PATDiTauPairRefVector;
typedef edm::RefVector<PATElecMuPairCollection> PATElecMuPairRefVector;
typedef edm::RefVector<PATMuMuMuTauQuadCollection> PATMuMuMuTauQuadRefVector;
typedef edm::RefVector<PATMuMuTauTauQuadCollection> PATMuMuTauTauQuadRefVector;
typedef edm::RefVector<PATMuMuEleTauQuadCollection> PATMuMuEleTauQuadRefVector;
typedef edm::RefVector<PATMuMuEleEleQuadCollection> PATMuMuEleEleQuadRefVector;
typedef edm::RefVector<PATMuMuEleMuQuadCollection> PATMuMuEleMuQuadRefVector;
typedef edm::RefVector<PATMuMuMuMuQuadCollection> PATMuMuMuMuQuadRefVector;
typedef edm::RefVector<PATEleEleEleTauQuadCollection> PATEleEleEleTauQuadRefVector;
typedef edm::RefVector<PATEleEleTauTauQuadCollection> PATEleEleTauTauQuadRefVector;
typedef edm::RefVector<PATEleEleEleEleQuadCollection> PATEleEleEleEleQuadRefVector;
typedef edm::RefVector<PATEleEleMuTauQuadCollection> PATEleEleMuTauQuadRefVector;
typedef edm::RefVector<PATEleEleEleMuQuadCollection> PATEleEleEleMuQuadRefVector;
typedef edm::RefVector<PATEleEleMuMuQuadCollection> PATEleEleMuMuQuadRefVector;
typedef edm::RefVector<PATMuMuMuNuQuadCollection> PATMuMuMuNuQuadRefVector;
typedef edm::RefVector<PATMuMuEleNuQuadCollection> PATMuMuEleNuQuadRefVector;
typedef edm::RefVector<PATEleEleMuNuQuadCollection> PATEleEleMuNuQuadRefVector;
typedef edm::RefVector<PATEleEleEleNuQuadCollection> PATEleEleEleNuQuadRefVector;
typedef edm::RefVector<PATEleEleEleTriCollection> PATEleEleEleTriRefVector;
typedef edm::RefVector<PATEleEleMuTriCollection> PATEleEleMuTriRefVector;
typedef edm::RefVector<PATMuMuEleTriCollection> PATMuMuEleTriRefVector;
typedef edm::RefVector<PATMuMuMuTriCollection> PATMuMuMuTriRefVector;
#endif
