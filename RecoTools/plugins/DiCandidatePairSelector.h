//
// $Id: DiCandidatePairSelector.h,v 1.13 2011/10/21 18:36:49 bachtis Exp $
//

#ifndef UWAnalysis_RecoTools_DiCandidatePairSelector_h
#define UWAnalysis_RecoTools_DiCandidatePairSelector_h

#include "DataFormats/Common/interface/RefVector.h"

#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/ObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleElementCollectionSelector.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"

#include <vector>

typedef SingleObjectSelector<
            std::vector<DiCandidatePair>,
            StringCutObjectSelector<DiCandidatePair>
        > DiCandidatePairSelector;

typedef SingleObjectSelector<
            std::vector<DiCandidatePair>,
            StringCutObjectSelector<DiCandidatePair>,
            edm::RefVector<std::vector<DiCandidatePair> >
        > DiCandidatePairRefSelector;

typedef SingleObjectSelector<
            std::vector<PATMuTauPair>,
            StringCutObjectSelector<PATMuTauPair>
        > PATMuTauPairSelector;

typedef SingleObjectSelector<
            std::vector<PATMuJetPair>,
            StringCutObjectSelector<PATMuJetPair>
        > PATMuJetPairSelector;


typedef SingleObjectSelector<
            std::vector<PATDiTauPair>,
            StringCutObjectSelector<PATDiTauPair>
        > PATDiTauPairSelector;


typedef SingleObjectSelector<
            std::vector<PATMuPair>,
            StringCutObjectSelector<PATMuPair>
        > PATMuPairSelector;

typedef SingleObjectSelector<
            std::vector<PATElecTauPair>,
            StringCutObjectSelector<PATElecTauPair>
        > PATEleTauPairSelector;

typedef SingleObjectSelector<
            std::vector<PATElecSCPair>,
            StringCutObjectSelector<PATElecSCPair>
        > PATEleSCPairSelector;

typedef SingleObjectSelector<
            std::vector<PATElecPair>,
            StringCutObjectSelector<PATElecPair>
        > PATElePairSelector;


typedef SingleObjectSelector<
            std::vector<PATElecMuPair>,
            StringCutObjectSelector<PATElecMuPair>
        > PATEleMuPairSelector;



typedef SingleObjectSelector<
            std::vector<PATMuTrackPair>,
            StringCutObjectSelector<PATMuTrackPair>
        > PATMuTrackPairSelector;

typedef SingleObjectSelector<
            std::vector<PATEleTrackPair>,
            StringCutObjectSelector<PATEleTrackPair>
        > PATEleTrackPairSelector;

//Quad typedefs

typedef SingleObjectSelector<
            std::vector<PATMuMuMuTauQuad>,
            StringCutObjectSelector<PATMuMuMuTauQuad>
        > PATMuMuMuTauQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATMuMuTauTauQuad>,
            StringCutObjectSelector<PATMuMuTauTauQuad>
        > PATMuMuTauTauQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATMuMuEleTauQuad>,
            StringCutObjectSelector<PATMuMuEleTauQuad>
        > PATMuMuEleTauQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATMuMuEleMuQuad>,
            StringCutObjectSelector<PATMuMuEleMuQuad>
        > PATMuMuEleMuQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATMuMuMuMuQuad>,
            StringCutObjectSelector<PATMuMuMuMuQuad>
        > PATMuMuMuMuQuadSelector;
        
typedef SingleObjectSelector<
            std::vector<PATMuMuEleEleQuad>,
            StringCutObjectSelector<PATMuMuEleEleQuad>
        > PATMuMuEleEleQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATEleEleEleTauQuad>,
            StringCutObjectSelector<PATEleEleEleTauQuad>
        > PATEleEleEleTauQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATEleEleTauTauQuad>,
            StringCutObjectSelector<PATEleEleTauTauQuad>
        > PATEleEleTauTauQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATEleEleEleEleQuad>,
            StringCutObjectSelector<PATEleEleEleEleQuad>
        > PATEleEleEleEleQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATEleEleMuTauQuad>,
            StringCutObjectSelector<PATEleEleMuTauQuad>
        > PATEleEleMuTauQuadSelector;
	
typedef SingleObjectSelector<
            std::vector<PATEleEleEleMuQuad>,
            StringCutObjectSelector<PATEleEleEleMuQuad>
        > PATEleEleEleMuQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATEleEleMuMuQuad>,
            StringCutObjectSelector<PATEleEleMuMuQuad>
        > PATEleEleMuMuQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATEleEleEleSCQuad>,
            StringCutObjectSelector<PATEleEleEleSCQuad>
        > PATEleEleEleSCQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATMuMuEleSCQuad>,
            StringCutObjectSelector<PATMuMuEleSCQuad>
        > PATMuMuEleSCQuadSelector;

typedef SingleObjectSelector<
            std::vector<PATEleEleEleTri>,
            StringCutObjectSelector<PATEleEleEleTri>
        > PATEleEleEleTriSelector;

typedef SingleObjectSelector<
            std::vector<PATEleEleMuTri>,
            StringCutObjectSelector<PATEleEleMuTri>
        > PATEleEleMuTriSelector;

typedef SingleObjectSelector<
            std::vector<PATMuMuEleTri>,
            StringCutObjectSelector<PATMuMuEleTri>
        > PATMuMuEleTriSelector;

typedef SingleObjectSelector<
            std::vector<PATMuMuMuTri>,
            StringCutObjectSelector<PATMuMuMuTri>
        > PATMuMuMuTriSelector;

#endif
