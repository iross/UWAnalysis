//
// $Id: CandidateMETPairSelector.h,v 1.1 2010/09/03 10:39:25 bachtis Exp $
//

#ifndef UWAnalysis_RecoTools_CandidateMETPairSelector_h
#define UWAnalysis_RecoTools_CandidateMETPairSelector_h

#include "DataFormats/Common/interface/RefVector.h"

#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/ObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleElementCollectionSelector.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

#include <vector>

typedef SingleObjectSelector<
            std::vector<PATMuonNuPair>,
            StringCutObjectSelector<PATMuonNuPair>
        > PATMuonNuPairSelector;



#endif
