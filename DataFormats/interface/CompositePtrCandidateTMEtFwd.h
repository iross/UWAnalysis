#ifndef UWAnalysis_DataFormats_CompositePtrCandidateTMEtFwd_h
#define UWAnalysis_DataFormats_CompositePtrCandidateTMEtFwd_h

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/RefVector.h"

#include <vector>

/// collection of CompositeRefCandidateTMEt objects
typedef std::vector<PATTauNuPair> PATTauNuPairCollection;
typedef std::vector<PATMuonNuPair> PATMuonNuPairCollection;
typedef std::vector<PATElectronNuPair> PATElectronNuPairCollection;
typedef std::vector<PATCandNuPair> PATCandNuPairCollection;

/// persistent reference to a CompositeRefCandidateTMEt object
typedef edm::Ref<PATTauNuPairCollection> PATTauNuPairRef;
typedef edm::Ref<PATMuonNuPairCollection> PATMuonNuPairRef;
typedef edm::Ref<PATElectronNuPairCollection> PATElectronNuPairRef;


/// references to CompositeRefCandidateTMEt collection
typedef edm::RefProd<PATTauNuPairCollection> PATTauNuPairRefProd;
typedef edm::RefProd<PATMuonNuPairCollection> PATMuonNuPairRefProd;
typedef edm::RefProd<PATElectronNuPairCollection> PATElectronNuPairRefProd;


/// vector of references to CompositeRefCandidateTMEt objects all in the same collection
typedef edm::RefVector<PATTauNuPairCollection> PATTauNuPairRefVector;
typedef edm::RefVector<PATMuonNuPairCollection> PATMuonNuPairRefVector;
typedef edm::RefVector<PATElectronNuPairCollection> PATElectronNuPairRefVector;


#endif
