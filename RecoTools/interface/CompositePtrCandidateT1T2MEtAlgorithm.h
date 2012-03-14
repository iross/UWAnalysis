#ifndef UWAnalysis_RecoTools_CompositePtrCandidateT1T2MEtAlgorithm_h
#define UWAnalysis_RecoTools_CompositePtrCandidateT1T2MEtAlgorithm_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/normalizedPhi.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "UWAnalysis/RecoTools/interface/candidateAuxFunctions.h"
#include "UWAnalysis/RecoTools/interface/METCalibrator.h"

#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/VolumeBasedEngine/interface/VolumeBasedMagneticField.h"
#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/TrackerGeometryBuilder/interface/GluedGeomDet.h"



#include <TMath.h>

template<typename T1, typename T2>
class CompositePtrCandidateT1T2MEtAlgorithm 
{
  typedef edm::Ptr<T1> T1Ptr;
  typedef edm::Ptr<T2> T2Ptr;
  typedef edm::Ptr<pat::Jet> JetPtr;
  typedef std::vector<JetPtr> JetPtrVector;


 public:
  CompositePtrCandidateT1T2MEtAlgorithm(const edm::ParameterSet& cfg)
  {
    recoMode_ = cfg.getParameter<std::string>("recoMode");
    verbosity_ = cfg.getUntrackedParameter<int>("verbosity", 0);
  }
  ~CompositePtrCandidateT1T2MEtAlgorithm() {}


  void setMETCalibrator(METCalibrator * calibrator) {calibrator_ = calibrator;}

  CompositePtrCandidateT1T2MEt<T1,T2> buildCompositePtrCandidate(const T1Ptr leg1, 
								 const T2Ptr leg2,
 								 const JetPtrVector& pfJets, 
								 const reco::CandidatePtr met,
								 const reco::GenParticleCollection* genParticles) {
    CompositePtrCandidateT1T2MEt<T1,T2> compositePtrCandidate(leg1, leg2, met);
    
    if ( leg1.isNull() || leg2.isNull() ) {
      edm::LogError ("CompositePtrCandidateT1T2MEtAlgorithm") << " Pointers to visible Decay products invalid !!";
      return compositePtrCandidate;
    }




//--- compute quantities that are independent of MET	
    compositePtrCandidate.setCharge(leg1->charge() + leg2->charge());
    compositePtrCandidate.setP4Vis(leg1->p4() + leg2->p4());
    compositePtrCandidate.setDR12(reco::deltaR(leg1->p4(), leg2->p4()));
    compositePtrCandidate.setDPhi12(TMath::Abs(normalizedPhi(leg1->phi() - leg2->phi())));
    compositePtrCandidate.setVisEtaMin(TMath::Min(leg1->eta(), leg2->eta()));
    compositePtrCandidate.setVisEtaMax(TMath::Max(leg1->eta(), leg2->eta()));


    //calibrate the MET
    reco::Candidate::LorentzVector correctedMET = met->p4();
    if(calibrator_!=0)
      correctedMET = calibrator_->calibrate(met->p4(),leg1->p4(),leg2->p4(),genParticles);
    
    //--- compute quantities that do dependent on MET
    if ( met.isNonnull() ) {
      compositePtrCandidate.setCalibratedMET(correctedMET);
      compCollinearApprox(compositePtrCandidate, leg1->p4(), leg2->p4(), correctedMET.px(), correctedMET.py());
      compositePtrCandidate.setP4CDFmethod(compP4CDFmethod(leg1->p4(), leg2->p4(), correctedMET.px(), correctedMET.py()));
      compositePtrCandidate.setMt12MET(compMt(leg1->p4(), leg2->p4(), correctedMET.px(), correctedMET.py()));    
      compositePtrCandidate.setMt1MET(compMt(leg1->p4(), correctedMET.px(), correctedMET.py()));
      compositePtrCandidate.setMt2MET(compMt(leg2->p4(), correctedMET.px(), correctedMET.py()));
      compositePtrCandidate.setDPhi1MET(TMath::Abs(normalizedPhi(leg1->phi() - correctedMET.phi())));
      compositePtrCandidate.setDPhi2MET(TMath::Abs(normalizedPhi(leg2->phi() - correctedMET.phi())));
      compZeta(compositePtrCandidate, leg1->p4(), leg2->p4(), correctedMET.px(), correctedMET.py()); 
      compProjMET(compositePtrCandidate, leg1->p4(), leg2->p4(), correctedMET);
    } else {
      compositePtrCandidate.setCollinearApproxQuantities(reco::Candidate::LorentzVector(0,0,0,0), -1, -1, false);
    }
 
    //--- compute gen. level quantities
    if ( genParticles ) {
      compGenQuantities(compositePtrCandidate, genParticles);
    }
    
//--- set compositePtr four-momentum
//    (depending on recoMode configuration parameter)
    if ( recoMode_ == "collinearApprox" ) {
      if ( met.isNonnull() ) {
        compositePtrCandidate.setP4(compositePtrCandidate.p4CollinearApprox());
      } else {
        edm::LogError ("buildCompositePtrCandidate") << " Failed to set four-momentum:"
						     << " recoMode = " << recoMode_ << " requires MET pointer to be valid !!";
      }
    } else if ( recoMode_ == "cdfMethod" ) {
      if ( met.isNonnull() ) {
	compositePtrCandidate.setP4(compositePtrCandidate.p4CDFmethod());
      } else {
	edm::LogError ("buildCompositePtrCandidate") << " Failed to set four-momentum:"
						     << " recoMode = " << recoMode_ << " requires MET pointer to be valid !!";
      }
    } else if ( recoMode_ == "" ) {
      compositePtrCandidate.setP4(compositePtrCandidate.p4Vis());
    } else {
      edm::LogError ("buildCompositePtrCandidate") << " Failed to set four-momentum:"
						   << " recoMode = " << recoMode_ << " undefined !!";
    }  



    //Set recoil values
    reco::Candidate::LorentzVector recoilTMP = -leg1->p4() - leg2->p4() - correctedMET;
    reco::Candidate::LorentzVector recoil_(recoilTMP.px(),recoilTMP.py(),0.0,sqrt(recoilTMP.px()*recoilTMP.px()+recoilTMP.py()*recoilTMP.py()));
    compositePtrCandidate.setRecoil(recoil_);
    compositePtrCandidate.setRecoilDPhi(fabs(normalizedPhi(compositePtrCandidate.p4Vis().phi() - recoil_.phi())));
 
    
    ///Do Jet studies
    //cross clean jets from legs 
    JetPtrVector cleanedJets;
    for(unsigned int i=0;i<pfJets.size();++i)
      if(reco::deltaR(pfJets.at(i)->p4(),leg1->p4())>0.5 && reco::deltaR(pfJets.at(i)->p4(),leg2->p4())>0.5)
	cleanedJets.push_back(pfJets.at(i));
    //sort them by Pt
    sortRefVectorByPt(cleanedJets);
    int nJets = cleanedJets.size();


    //Calculate HT
    double ht = leg1->pt()+leg2->pt();
    for(int k=0;k<nJets;++k)
      ht+=cleanedJets.at(k)->pt();

    compositePtrCandidate.setJetVariables(cleanedJets,ht);
    computeVBFVariables(compositePtrCandidate,cleanedJets);
    return compositePtrCandidate;
  }

 private: 
  
  void compGenQuantities(CompositePtrCandidateT1T2MEt<T1,T2>& compositePtrCandidate, const reco::GenParticleCollection* genParticles)
  {
	 std::vector<int>* pdgIdsV = new std::vector<int>;
	 pdgIdsV->push_back(11); pdgIdsV->push_back(-11);
	 pdgIdsV->push_back(13); pdgIdsV->push_back(-13);
	 pdgIdsV->push_back(15); pdgIdsV->push_back(-15);
	 pdgIdsV->push_back(23); 
	const reco::GenParticle* genLeg1 = uw::findGenParticle(compositePtrCandidate.leg1()->p4(), *genParticles, 0.3, -1, pdgIdsV, true);
    if ( genLeg1 ) {
//      std::cout << "genLeg1: Pt = " << genLeg1->pt() << ", eta = " << genLeg1->eta() << "," 
//      	  << " phi = " << genLeg1->phi()*180./TMath::Pi() << std::endl;
      compositePtrCandidate.setP4Leg1gen(genLeg1->p4());
      compositePtrCandidate.setP4VisLeg1gen(getVisMomentum(genLeg1, genParticles));
      compositePtrCandidate.setPdg1(genLeg1->pdgId());
    }
    
    const reco::GenParticle* genLeg2 = uw::findGenParticle(compositePtrCandidate.leg2()->p4(), *genParticles, 0.3, -1, pdgIdsV, true);
    if ( genLeg2 ) {
//      std::cout << "genLeg2: Pt = " << genLeg2->pt() << ", eta = " << genLeg2->eta() << "," 
//      	  << " phi = " << genLeg2->phi()*180./TMath::Pi() << std::endl;
      compositePtrCandidate.setP4Leg2gen(genLeg2->p4());
      compositePtrCandidate.setP4VisLeg2gen(getVisMomentum(genLeg2, genParticles));
      compositePtrCandidate.setPdg2(genLeg2->pdgId());
    }
  }
  void compCollinearApprox(CompositePtrCandidateT1T2MEt<T1,T2>& compositePtrCandidate,
			   const reco::Candidate::LorentzVector& leg1,
			   const reco::Candidate::LorentzVector& leg2,
			   double metPx, double metPy)
  {
    double x1_numerator = leg1.px()*leg2.py() - leg2.px()*leg1.py();
    double x1_denominator = leg2.py()*(leg1.px() + metPx) - leg2.px()*(leg1.py() + metPy);
    double x1 = ( x1_denominator != 0. ) ? x1_numerator/x1_denominator : -1.;
    //std::cout << "x1 = " << x1 << std::endl;
    bool isX1withinPhysRange = true;
    double x1phys = getPhysX(x1, isX1withinPhysRange);

    double x2_numerator = x1_numerator;
    double x2_denominator = leg1.px()*(leg2.py() + metPy) - leg1.py()*(leg2.px() + metPx);
    double x2 = ( x2_denominator != 0. ) ? x2_numerator/x2_denominator : -1.;
    //std::cout << "x2 = " << x2 << std::endl;
    bool isX2withinPhysRange = true;
    double x2phys = getPhysX(x2, isX2withinPhysRange);

    if ( x1phys != 0. && x2phys != 0. ) {
      reco::Candidate::LorentzVector p4 = leg1/x1phys + leg2/x2phys;
      compositePtrCandidate.setCollinearApproxQuantities(p4, x1, x2, isX1withinPhysRange && isX2withinPhysRange);
    } else {
      compositePtrCandidate.setCollinearApproxQuantities(reco::Candidate::LorentzVector(0,0,0,0), x1, x2, false);
    }
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



  void compZeta(CompositePtrCandidateT1T2MEt<T1,T2>& compositePtrCandidate,
		const reco::Candidate::LorentzVector& leg1,
		const reco::Candidate::LorentzVector& leg2,
		double metPx, double metPy)
  {
    //std::cout << "<CompositePtrCandidateT1T2MEtAlgorithm::compZeta>:" << std::endl;

    double leg1x = cos(leg1.phi());
    double leg1y = sin(leg1.phi());
    double leg2x = cos(leg2.phi());
    double leg2y = sin(leg2.phi());
    double zetaX = leg1x + leg2x;
    double zetaY = leg1y + leg2y;
    double zetaR = TMath::Sqrt(zetaX*zetaX + zetaY*zetaY);
    if ( zetaR > 0. ) {
      zetaX /= zetaR;
      zetaY /= zetaR;
    }

    //std::cout << " leg1Phi = " << leg1.phi()*180./TMath::Pi() << std::endl;
    //std::cout << " leg2Phi = " << leg2.phi()*180./TMath::Pi() << std::endl;

    //std::cout << " zetaX = " << zetaX << std::endl;
    //std::cout << " zetaY = " << zetaY << std::endl;

    //std::cout << " zetaPhi = " << normalizedPhi(atan2(zetaY, zetaX))*180./TMath::Pi() << std::endl;

    double visPx = leg1.px() + leg2.px();
    double visPy = leg1.py() + leg2.py();
    double pZetaVis = visPx*zetaX + visPy*zetaY;

    //std::cout << " visPx = " << visPx << std::endl;
    //std::cout << " visPy = " << visPy << std::endl;

    double px = visPx + metPx;
    double py = visPy + metPy;
    double pZeta = px*zetaX + py*zetaY;

    //std::cout << " metPhi = " << normalizedPhi(atan2(metPy, metPx))*180./TMath::Pi() << std::endl;
    
    if ( verbosity_ ) {
      std::cout << "<CompositePtrCandidateT1T2MEtAlgorithm::compZeta>:" << std::endl;
      std::cout << " pZetaVis = " << pZetaVis << std::endl;
      std::cout << " pZeta = " << pZeta << std::endl;
    }

    //assert(pZetaVis >= 0.);

    compositePtrCandidate.setPzeta(pZeta);
    compositePtrCandidate.setPzetaVis(pZetaVis);
  }
  reco::Candidate::LorentzVector compP4CDFmethod(const reco::Candidate::LorentzVector& leg1, 
						 const reco::Candidate::LorentzVector& leg2, 
						 double metPx, double metPy)
  {
    double px = leg1.px() + leg2.px() + metPx;
    double py = leg1.py() + leg2.py() + metPy;
    double pz = leg1.pz() + leg2.pz();
    double e = leg1.energy() + leg2.energy() + TMath::Sqrt(metPx*metPx + metPy*metPy);
    reco::Candidate::LorentzVector p4(px, py, pz, e);
    return p4;
  }
  double compMt(const reco::Candidate::LorentzVector& leg1, 
		const reco::Candidate::LorentzVector& leg2, 
		double metPx, double metPy)
  {
    double px = leg1.px() + leg2.px() + metPx;
    double py = leg1.py() + leg2.py() + metPy;
    double et = leg1.Et() + leg2.Et() + TMath::Sqrt(metPx*metPx + metPy*metPy);
    double mt2 = et*et - (px*px + py*py);
    if ( mt2 < 0 ) {
      edm::LogWarning ("compMt") << " mt2 = " << mt2 << " must not be negative !!";
      return 0.;
    }
    return TMath::Sqrt(mt2);
  }
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


  void compProjMET(CompositePtrCandidateT1T2MEt<T1,T2>& compositePtrCandidate,
  		const reco::Candidate::LorentzVector& leg1,
  		const reco::Candidate::LorentzVector& leg2, 
  		const reco::Candidate::LorentzVector& METP4)
  {
  	double pi = 3.1415926;
  	double PMET = 0;
  	double dPhi1 = leg1.phi() - METP4.phi();
  	double dPhi2 = leg2.phi() - METP4.phi();
  	if (dPhi1 < 0) dPhi1 = -dPhi1;
  	if (dPhi2 < 0) dPhi2 = -dPhi2;
  	if (dPhi1 > pi) {
		dPhi1 = 2 * pi - dPhi1;
  	}
  	if (dPhi2 > pi) {
		dPhi2 = 2 * pi - dPhi2;
  	}
  	if(dPhi1 < dPhi2 && dPhi1 < pi/2){
  		PMET = TMath::Sqrt(pow((METP4.px()*leg1.px()*leg1.px()+METP4.py()*leg1.py()*leg1.px())/(leg1.pt()*leg1.pt()),2)
  							+pow((METP4.px()*leg1.px()*leg1.py()+METP4.py()*leg1.py()*leg1.py())/(leg1.pt()*leg1.pt()),2));
  	}
  	else if(dPhi2 < dPhi1 && dPhi2 < pi/2){
  		PMET = TMath::Sqrt(pow((METP4.px()*leg2.px()*leg2.px()+METP4.py()*leg2.py()*leg2.px())/(leg2.pt()*leg2.pt()),2)
  							+pow((METP4.px()*leg2.px()*leg2.py()+METP4.py()*leg2.py()*leg2.py())/(leg2.pt()*leg2.pt()),2));
  	}
  	else
  	{
  		PMET = METP4.pt();
  	}
  	
  	compositePtrCandidate.setProjMET(PMET);
  
  }



  //Complicated approach
  //  void computeVBFVariables(CompositePtrCandidateT1T2MEt<T1,T2>& compositePtrCandidate,const JetPtrVector& jets) {
  //    double deta=0.0;
  //    double mass=0.0;
  //    double gap=0.0;
  //    for( int i=0;i<(int)jets.size()-1;++i)
  //      for(int j=i+1;j<(int)jets.size();++j) {
  //	deta =fabs(jets.at(i)->eta()-jets.at(j)->eta()); 
  //	  if(deta>2.0&&jets.at(i)->eta()*jets.at(j)->eta()<0)
  //	    {
  //	      mass = (jets.at(i)->p4()+jets.at(j)->p4()).M();
  //	      float minEta = std::min(jets.at(i)->eta(),jets.at(j)->eta());
  //	      float maxEta = std::max(jets.at(i)->eta(),jets.at(j)->eta());
  //	      for(int k=0;k<(int)jets.size();++k)
  //		if(k!=i && k!=j)
  //		  if(jets.at(k)->eta()>minEta && jets.at(k)->eta()<maxEta)
  //		    gap+=jets.at(k)->pt();
  //	      break;
  //	    }
  //
  //	  
  //	  if(deta>2.0)
  //	    break;
  //	      
  //      }
  //
  //    if(deta<2.0) { deta=0.0; mass=0.0; gap=0.0;}
  //    compositePtrCandidate.setVBFVariables(mass,deta,gap);
  //  }


  //Simple approach -> Just highest 2 jets 

  void computeVBFVariables(CompositePtrCandidateT1T2MEt<T1,T2>& compositePtrCandidate,const JetPtrVector& jets) {
    double deta=0.0;
    double mass=0.0;
    double gap=0.0;
      if(jets.size()>1) 
	if(jets.at(0)->eta()*jets.at(1)->eta()<0) {
	  deta =fabs(jets.at(0)->eta()-jets.at(1)->eta()); 
	  mass = (jets.at(0)->p4()+jets.at(1)->p4()).M();
	  for(int k=2;k<(int)jets.size();++k)
	    gap+=jets.at(k)->pt();
      }
    compositePtrCandidate.setVBFVariables(mass,deta,gap);
  }
  




  std::string recoMode_;
  int verbosity_;


  METCalibrator *calibrator_;



 


};

#endif 

