#ifndef UWAnalysis_PatTools_CompositePtrCandidateTMEtAlgorithm_h
#define UWAnalysis_PatTools_CompositePtrCandidateTMEtAlgorithm_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/normalizedPhi.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 

#include <TMath.h>

template<typename T>
class CompositePtrCandidateTMEtAlgorithm 
{
  typedef edm::Ptr<T> TPtr;
  typedef edm::Ptr<reco::Candidate> METPtr;
  typedef edm::Ptr<pat::Jet> JetPtr;
  typedef std::vector<JetPtr> JetPtrVector;

 public:

  CompositePtrCandidateTMEtAlgorithm()
  {
    verbosity_ = 0;
  }
  ~CompositePtrCandidateTMEtAlgorithm() {}

  CompositePtrCandidateTMEt<T> buildCompositePtrCandidate(const TPtr visDecayProducts, 
							  METPtr met,
							  JetPtrVector pfJets,
							  edm::View<T> visProductCollection)
  {
    CompositePtrCandidateTMEt<T> compositePtrCandidate(visDecayProducts, met);
  
    if ( visDecayProducts.isNull() ) {
      edm::LogError ("CompositePtrCandidateTMEtAlgorithm") << " Pointer to visible Decay products invalid !!";
      return compositePtrCandidate;
    }

    if ( met.isNull() ) {
      edm::LogError ("CompositePtrCandidateTMEtAlgorithm") << " Pointer to missing transverse momentum invalid !!";
      return compositePtrCandidate;
    }

    reco::Candidate::LorentzVector recoil(-met->px()-visDecayProducts->px(),-met->py()-visDecayProducts->py(),0.0,sqrt(pow(met->px()+visDecayProducts->px(),2)+pow(met->py()+visDecayProducts->py(),2)));

    compositePtrCandidate.setRecoil(recoil);
    compositePtrCandidate.setRecoilDPhi(deltaPhi(recoil.phi(),visDecayProducts->phi()));
    compositePtrCandidate.setCharge(visDecayProducts->charge());
    compositePtrCandidate.setMt(compMt(visDecayProducts->p4(), met->px(), met->py()));
    compositePtrCandidate.setDPhi(TMath::Abs(normalizedPhi(visDecayProducts->phi() - met->phi())));

    //Jets
    JetPtrVector cleanedJets;
    for(unsigned int i=0;i<pfJets.size();++i)
      if(reco::deltaR(pfJets.at(i)->p4(),visDecayProducts->p4())>0.15 )
	cleanedJets.push_back(pfJets.at(i));

    //sort them by Pt
    sortRefVectorByPt(cleanedJets);
    unsigned int nJets = cleanedJets.size();
 
   //find the nearest jet to leg1
    double ht = visDecayProducts->pt();
    for(unsigned int k=0;k<nJets;++k)
      ht+=cleanedJets.at(k)->pt();


    compositePtrCandidate.setJetValues(cleanedJets,ht);




    return compositePtrCandidate;
  }

 private: 

  double compMt(const reco::Candidate::LorentzVector& visParticle, 
		double metPx, double metPy)
  {
    double px = visParticle.px() + metPx;
    double py = visParticle.py() + metPy;
    double et = visParticle.Et() + TMath::Sqrt(metPx*metPx + metPy*metPy);
    double mt2 = et*et - (px*px + py*py);
    if ( mt2 < 0 ) {
      edm::LogWarning ("compMt") << " mt2 = " << mt2 << " must not be negative !!";
      return 0.;
    }
    return TMath::Sqrt(mt2);
  }

  class refVectorPtSorter {
  public:
    refVectorPtSorter(const JetPtrVector vec)
      {
	vec_ = vec;
      }

    refVectorPtSorter()
      {
      }


    ~refVectorPtSorter()
      {}

    bool operator()(size_t a , size_t b) {
      return (vec_.at(a)->pt() > vec_.at(b)->pt());
    }
  private:
    JetPtrVector vec_;
  };



  void sortRefVectorByPt(JetPtrVector& vec)
  {
    std::vector<size_t> indices;
    indices.reserve(vec.size());
    for(unsigned int i=0;i<vec.size();++i)
      indices.push_back(i);
    
    refVectorPtSorter sorter(vec);
    std::sort(indices.begin(),indices.end(),sorter);
        
    JetPtrVector sorted;
    sorted.reserve(vec.size());
    
    for(unsigned int i=0;i<indices.size();++i)
      sorted.push_back(vec.at(indices.at(i)));

    vec = sorted;
  }


  int verbosity_;
};

#endif 

