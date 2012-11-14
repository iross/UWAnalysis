#ifndef __UWAnalysis_DataFormats_Analysis_CompositeRefCandidateT1T2MEt_h__
#define __UWAnalysis_DataFormats_Analysis_CompositeRefCandidateT1T2MEt_h__


#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "DataFormats/Common/interface/Ptr.h"

#include "AnalysisDataFormats/TauAnalysis/interface/NSVfitResonanceHypothesisSummary.h"

#include "UWAnalysis/DataFormats/interface/tauAnalysisAuxFunctions.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"


template<typename T1, typename T2>
class CompositePtrCandidateT1T2MEt : public reco::LeafCandidate
{
    typedef edm::Ptr<T1> T1Ptr;
    typedef edm::Ptr<T2> T2Ptr;
    typedef edm::Ptr<pat::Jet> JetPtr;
    typedef edm::Ptr<pat::MET> METPtr;

    public:

    /// default constructor
    CompositePtrCandidateT1T2MEt() {}

    /// constructor with MEt
    CompositePtrCandidateT1T2MEt(const T1Ptr leg1, const T2Ptr leg2, const reco::CandidatePtr met)
        : leg1_(leg1), leg2_(leg2), met_(met) {}

    /// constructor without MEt
    CompositePtrCandidateT1T2MEt(const T1Ptr leg1, const T2Ptr leg2)
        : leg1_(leg1), leg2_(leg2) {}

    /// destructor
    ~CompositePtrCandidateT1T2MEt() {}

    /// access to daughter particles
    const T1Ptr leg1() const { return leg1_; }
    const T2Ptr leg2() const { return leg2_; }


    const int genPdg1() const {return pdg1_; }
    const int genPdg2() const {return pdg2_; }

    /// access to gen. momenta
    reco::Candidate::LorentzVector p4gen() const { return p4Leg1gen() + p4Leg2gen(); }
    reco::Candidate::LorentzVector p4VisGen() const { return p4VisLeg1gen() + p4VisLeg2gen(); }

    /// access to gen. mother particles
    /// (undecayed tau leptons)
    const reco::Candidate::LorentzVector& p4Leg1gen() const { return p4Leg1gen_; }
    const reco::Candidate::LorentzVector& p4Leg2gen() const { return p4Leg2gen_; }

    /// access to visible gen. daughter particles
    /// (electrons, muons, kaons, charged and neutral pions produced in tau decay)
    const reco::Candidate::LorentzVector& p4VisLeg1gen() const { return p4VisLeg1gen_; }
    const reco::Candidate::LorentzVector& p4VisLeg2gen() const { return p4VisLeg2gen_; }

    /// energy ratio of visible gen. daughter/mother particles
    double x1gen() const { return ( p4Leg1gen_.energy() > 0. ) ? p4VisLeg1gen_.energy()/p4Leg1gen_.energy() : -1.; }
    double x2gen() const { return ( p4Leg2gen_.energy() > 0. ) ? p4VisLeg2gen_.energy()/p4Leg2gen_.energy() : -1.; }

    /// return the number of source particle-like Candidates
    /// (the candidates used to construct this Candidate)
    /// MET does not count.
    size_t numberOfSourceCandidatePtrs() const { return 2; }

    /// return a Ptr to one of the source Candidates
    /// (the candidates used to construct this Candidate)
    reco::CandidatePtr sourceCandidatePtr( size_type i ) const {
        if(i==0) return leg1();
        else if(i==1) return leg2();
        else assert(0);
    }

    /// access to missing transverse momentum
    const METPtr met() const { return met_; }

    // get sum of charge of visible decay products
    // (not need to declare it in CompositePtrCandidateT1T2MEt;
    //  already declared in Candidate base-class)

    /// get four-momentum of visible decay products
    const reco::Candidate::LorentzVector& p4Vis() const { return p4Vis_; }

    /// get four-momentum and scaling factors for momenta of visible decay products
    /// computed by collinear approximation
    const reco::Candidate::LorentzVector& p4CollinearApprox() const { return p4CollinearApprox_; }
    double x1CollinearApprox() const { return x1CollinearApprox_; }
    double x2CollinearApprox() const { return x2CollinearApprox_; }
    bool collinearApproxIsValid() const { return collinearApproxIsValid_; }

    /// get "pseudo" four-momentum computed by CDF method
    /// (for a description of the method, see e.g. CDF note 8972)
    const reco::Candidate::LorentzVector& p4CDFmethod() const { return p4CDFmethod_; }

    /// get transverse mass of visible decay products + missing transverse momentum
    double mt12MET() const { return mt12MET_; }

    /// get transverse mass of first/second
    /// visible decay product + missing transverse momentum
    double mt1MET() const { return mt1MET_; }
    double mt2MET() const { return mt2MET_; }

    /// get acoplanarity angle (angle in transverse plane) between visible decay products
    double dPhi12() const { return dPhi12_; }

    /// get separation in eta-phi between visible decay products
    double dR12() const { return dR12_; }

    /// get minimal/maximal pseudo-rapidity of visible decay products
    double visEtaMin() const { return visEtaMin_; }
    double visEtaMax() const { return visEtaMax_; }

    /// get acoplanarity angle (angle in transverse plane) between first/second
    /// visible decay product and missing transverse momentum
    double dPhi1MET() const { return dPhi1MET_; }
    double dPhi2MET() const { return dPhi2MET_; }

    /// get values of CDF-"zeta" variables
    /// (indicating the consistency of the missing transverse momentum observed in an event
    ///  with the hypothesis of originating from tau neutrinos)
    double pZeta() const { return pZeta_; }
    double pZetaVis() const { return pZetaVis_; }

    // MET projected along the direction of the nearest lepton if within pi/2 otherwise just full MET
    double projMET() const { return projMET_; }

    //FSR variables
    double phoPt() const {return phoPt_;}
    double phoEta() const {return phoEta_;}
    double phoPhi() const {return phoPhi_;}
    double lepDR() const {return lepDR_;}
    double lepPt() const {return lepPt_;}
    double leg1PhotonIso() const {return leg1PhotonIso_;}
    double leg2PhotonIso() const {return leg2PhotonIso_;}
    const reco::Candidate::LorentzVector& noPhoP4() const { return noPhoP4_;}
    double massNoFSR() const {return noPhoMass_;}

    void setFSRVariables(double phoPt, double phoEta, double phoPhi, double lepDR, double lepPt, reco::Candidate::LorentzVector noPhoP4, double leg1PhotonIso, double leg2PhotonIso){
        phoPt_ = phoPt;
        phoEta_ = phoEta;
        phoPhi_ = phoPhi;
        lepDR_ = lepDR;
        lepPt_ = lepPt;
        noPhoP4_ = noPhoP4;
        leg1PhotonIso_ = leg1PhotonIso;
        leg2PhotonIso_ = leg2PhotonIso;
    }

    double invM12() const {return M12_;}
    double invM13() const {return M13_;}
    double invM14() const {return M14_;}
    double invM23() const {return M23_;}
    double invM24() const {return M24_;}
    double invM34() const {return M34_;}
    double fourFour() const {return fourFour_;}
    double sixSix() const {return sixSix_;}

    void setInvMasses(reco::Candidate::LorentzVector p411, reco::Candidate::LorentzVector p412, reco::Candidate::LorentzVector p421, reco::Candidate::LorentzVector p422, bool fourFour, bool sixSix){
        M12_ = (p411+p412).M();
        M13_ = (p411+p421).M();
        M14_ = (p411+p422).M();
        M23_ = (p412+p421).M();
        M24_ = (p412+p422).M();
        M34_ = (p421+p422).M();
        fourFour_ = fourFour;
        sixSix_ = sixSix;
    }

    void setNoFSRMass(double mass){
        noPhoMass_ = mass;
    }

    //ZZ system angles
    float costheta1() const{ return costheta1_;}
    float costheta2() const{ return costheta2_;}
    float Phi() const{ return Phi_;}
    float costhetaStar() const{ return costhetaStar_;}
    float phiStar1() const{ return phiStar1_;}
    float phiStar2() const{ return phiStar2_;}
    float phiStar12() const{ return phiStar12_;}
    float phi1() const{ return phi1_;}
    float phi2() const{ return phi2_;}
    //MELA crap
    float kd() const{ return kd_;}
    float psig() const{ return psig_;}
    float pbkg() const{ return pbkg_;}
    float kdPS() const{ return kdPS_;}
    float psigPS() const{ return psigPS_;}
    float psigAltPS() const{ return psigAltPS_;}
    float kdS2M() const{ return kdS2M_;}
    float psigS2M() const{ return psigS2M_;}
    float psigAltS2M() const{ return psigAltS2M_;}

    void setAngles(float costheta1, float costheta2, float phi, float costhetastar, float phistar1, float phistar2, float phistar12, float phi1, float phi2, float kd, float psig, float pbkg, float kdPS, float psigPS, float psigAltPS, float kdS2M, float psigS2M, float psigAltS2M){
        costheta1_ = costheta1;
        costheta2_ = costheta2;
        Phi_ = phi;
        costhetaStar_ = costhetastar;
        phiStar1_ = phistar1;
        phiStar2_ = phistar2;
        phiStar12_ = phistar12;
        phi1_ = phi1;
        phi2_ = phi2;
        kd_ = kd;
        psig_ = psig;
        pbkg_ = pbkg;
        kdPS_ = kdPS;
        psigPS_ = psigPS;
        psigAltPS_ = psigAltPS;
        kdS2M_ = kdS2M;
        psigS2M_ = psigS2M;
        psigAltS2M_ = psigAltS2M;
    }

    // set Z masses
    void setBestZmasses(double best, double subBest)
    {
        bestZmass_ = best;
        subBestZmass_ = subBest;
    }

    //Vertex variables

    //Z difference of the first and second leg after propagation of tracks to the beamspot
    double dz() const {return dZ12_;}
    //Z Position of the first leg and second leg
    double z1() const {return z1_;}
    double z2() const {return z2_;}
    //Distance of closest approach of the two tracks
    double dca() const {return dca_;}
    //Transverse Distance from beamspot of the crossing point of the two track trajectories
    double crossingPointDistance() const {return crossingPointDistance_;}


    //////RECOIL
    reco::Candidate::LorentzVector recoil() const {return recoil_;}
    reco::Candidate::LorentzVector calibratedMET() const {return calibratedMET_;}
    double recoilDPhi() const {return recoilDPhi_;}


    //Jet variables
    int nJets() const {return jets_.size();}
    std::vector<JetPtr>  jets() const {return jets_;}
    double  ht() const {return ht_;}


    //VBF Variables
    float vbfMass() const {return vbfMass_;}
    float vbfDEta() const {return vbfDEta_;}
    float vbfPt1() const {return vbfPt1_;}
    float vbfPt2() const {return vbfPt2_;}
    float vbfEta1() const {return vbfEta1_;}
    float vbfEta2() const {return vbfEta2_;}

    int   vbfNJetsGap20() const {return vbfNJetsGap20_;}
    int   vbfNJetsGap30() const {return vbfNJetsGap30_;}


    double bestZmass() const { return bestZmass_; }
    double subBestZmass() const { return subBestZmass_; }

    //M JJ variables
    double mJJ() const {return mjj_;}
    double ptJJ() const {return ptjj_;}
    void setJJVariables(double mjj,double ptjj) {
        mjj_ = mjj;
        ptjj_ = ptjj;
    }

    /// clone  object
    CompositePtrCandidateT1T2MEt<T1,T2>* clone() const { return new CompositePtrCandidateT1T2MEt<T1,T2>(*this); }

    friend std::ostream& operator<<(std::ostream& out, const CompositePtrCandidateT1T2MEt<T1,T2>& dic) {
        out << "Di-Candidate m = " << dic.mass();
        return out;
    }


    // NSVFit getters and setters.  From C. Veelken
    /// get Mtautau solutions reconstructed by NSVfit algorithm
    void addNSVfitSolution(const NSVfitResonanceHypothesisSummary& solution) {
        nSVfitSolutions_.push_back(solution);
    }

    bool hasNSVFitSolutions() const { return (nSVfitSolutions_.begin() != nSVfitSolutions_.end()); }

    const NSVfitResonanceHypothesisSummary* nSVfitSolution(
            const std::string& algorithm, int* errorFlag = 0) const {
        const NSVfitResonanceHypothesisSummary* retVal = 0;
        for (std::vector<NSVfitResonanceHypothesisSummary>::const_iterator
                nSVfitSolution = nSVfitSolutions_.begin();
                nSVfitSolution != nSVfitSolutions_.end(); ++nSVfitSolution ) {
            if ( nSVfitSolution->name() == algorithm ) {
                retVal = &(*nSVfitSolution);
                break;
            }
        }

        if ( !retVal ) {
            if ( errorFlag ) {
                (*errorFlag) = 1;
            }
        }

        return retVal;
    }



    private:

    /// allow only CompositePtrCandidateT1T2MEtAlgorithm to change values of data-members
    template<typename T1_type, typename T2_type> friend class CompositePtrCandidateT1T2MEtAlgorithm;
    template<typename T1_type, typename T2_type> friend class CompositePtrCandidateT1T2MEtVertexAlgorithm;
    template<typename T1_type, typename T2_type> friend class PATCandidatePairSVFitter;


    /// set gen. four-momenta
    void setP4Leg1gen(const reco::Candidate::LorentzVector& p4) { p4Leg1gen_ = p4; }
    void setP4Leg2gen(const reco::Candidate::LorentzVector& p4) { p4Leg2gen_ = p4; }
    void setP4VisLeg1gen(const reco::Candidate::LorentzVector& p4) { p4VisLeg1gen_ = p4; }
    void setP4VisLeg2gen(const reco::Candidate::LorentzVector& p4) { p4VisLeg2gen_ = p4; }

    void setPdg1(int pdg) {pdg1_ = pdg;}
    void setPdg2(int pdg) {pdg2_ = pdg;}

    /// set four-momentum of visible decay products
    void setP4Vis(const reco::Candidate::LorentzVector& p4) { p4Vis_ = p4; }
    /// set four-momentum and scaling factors for momenta of visible decay products
    /// computed by collinear approximation
    void setCollinearApproxQuantities(const reco::Candidate::LorentzVector& p4, double x1, double x2, bool isValid)
    {
        p4CollinearApprox_ = p4;
        x1CollinearApprox_ = x1;
        x2CollinearApprox_ = x2;
        collinearApproxIsValid_ = isValid;
    }
    /// set "pseudo" four-momentum computed by CDF method
    /// (for a description of the method, see e.g. CDF note 8972)
    void setP4CDFmethod(const reco::Candidate::LorentzVector& p4) { p4CDFmethod_ = p4; }
    /// set transverse mass of visible decay products + missing transverse momentum
    void setMt12MET(double mt) { mt12MET_ = mt; }
    /// set transverse mass of first/second
    /// visible decay product + missing transverse momentum
    void setMt1MET(double mt) { mt1MET_ = mt; }
    void setMt2MET(double mt) { mt2MET_ = mt; }
    /// set acoplanarity angle (angle in transverse plane) between visible decay products
    void setDPhi12(double dPhi) { dPhi12_ = dPhi; }
    /// set separation in eta-phi between visible decay products
    void setDR12(double dR) { dR12_ = dR; }
    /// set minimal/maximal pseudo-rapidity of visible decay products
    void setVisEtaMin(double eta) { visEtaMin_ = eta; }
    void setVisEtaMax(double eta) { visEtaMax_ = eta; }
    /// set acoplanarity angle (angle in transverse plane) between first/second
    /// visible decay product and missing transverse momentum
    void setDPhi1MET(double dPhi) { dPhi1MET_ = dPhi; }
    void setDPhi2MET(double dPhi) { dPhi2MET_ = dPhi; }
    /// set values of CDF-"zeta" variables
    void setPzeta(double pZeta) { pZeta_ = pZeta; }
    void setPzetaVis(double pZetaVis) { pZetaVis_ = pZetaVis; }
    /// set value of Projected MET
    void setProjMET(double projMET) { projMET_ = projMET; }
    void setCalibratedMET(const reco::Candidate::LorentzVector& met) { calibratedMET_ = met; }



    /// set vertex variables
    void setVertexVariables(double dca,double crossingPointDistance, double dZ12, double Z1, double Z2) {
        dca_ = dca;
        crossingPointDistance_ = crossingPointDistance;
        dZ12_ = dZ12;
        z1_ = Z1;
        z2_ = Z2;
    }

    //set VBF Variables
    void setVBFVariables(float mass, float deta, int jets20,int jets30,float pt1, float pt2, float eta1, float eta2 ) {
        vbfMass_ = mass;
        vbfDEta_ = deta;
        vbfNJetsGap20_ = jets20;
        vbfNJetsGap30_ = jets30;
        vbfPt1_=pt1;
        vbfPt2_=pt2;
        vbfEta1_=eta1;
        vbfEta2_=eta2;
    }





    /// set values of recoil
    void setRecoil(reco::Candidate::LorentzVector recoil) { recoil_ = recoil; }
    void setRecoilDPhi(double recoilDPhi) { recoilDPhi_ = recoilDPhi; }


    //jet variables
    void setJetVariables(std::vector<JetPtr> jets,double ht) {
        jets_ = jets;
        ht_ = ht;
    }
    /// references/pointers to decay products
    T1Ptr leg1_;
    T2Ptr leg2_;
    METPtr met_;
    reco::Candidate::LorentzVector calibratedMET_;

    /// gen. four-momenta
    reco::Candidate::LorentzVector p4Leg1gen_;
    reco::Candidate::LorentzVector p4Leg2gen_;
    reco::Candidate::LorentzVector p4VisLeg1gen_;
    reco::Candidate::LorentzVector p4VisLeg2gen_;


    //gen Pdg Id
    int pdg1_;
    int pdg2_;


    /// four-momentum of visible decay products
    reco::Candidate::LorentzVector p4Vis_;
    /// four-momentum and scaling factors for momenta of visible decay products computed by collinear approximation
    reco::Candidate::LorentzVector p4CollinearApprox_;
    bool collinearApproxIsValid_;
    double x1CollinearApprox_;
    double x2CollinearApprox_;
    /// "pseudo" four-momentum computed by CDF method
    reco::Candidate::LorentzVector p4CDFmethod_;
    /// transverse mass of visible decay products + missing transverse momentum
    double mt12MET_;
    /// transverse mass of first/second visible decay product + missing transverse momentum
    double mt1MET_;
    double mt2MET_;
    /// acoplanarity angle (angle in transverse plane) between visible decay products
    double dPhi12_;
    /// separation in eta-phi between visible decay products
    double dR12_;
    /// minimal/maximal pseudo-rapidity of visible decay products
    double visEtaMin_;
    double visEtaMax_;
    /// acoplanarity angle (angle in transverse plane) between first/second
    /// visible decay product and missing transverse momentum
    double dPhi1MET_;
    double dPhi2MET_;
    /// CDF-"zeta" variables
    double pZeta_;
    double pZetaVis_;
    /// Projected MET Variable
    double projMET_;

    //FSR vars
    double phoPt_;
    double phoEta_;
    double phoPhi_;
    double lepPt_;
    double lepDR_;
    reco::Candidate::LorentzVector noPhoP4_;
    double leg1PhotonIso_;
    double leg2PhotonIso_;
    double noPhoMass_;

    double M12_;
    double M13_;
    double M14_;
    double M23_;
    double M24_;
    double M34_;
    bool fourFour_;
    bool sixSix_;
    //MELA crap
    float kd_;
    float psig_;
    float pbkg_;
    float kdPS_;
    float psigPS_;
    float psigAltPS_;
    float kdS2M_;
    float psigS2M_;
    float psigAltS2M_;

    //Angles
    float costheta1_;
    float costheta2_;
    float Phi_;
    float costhetaStar_;
    float phiStar1_;
    float phiStar2_;
    float phiStar12_;
    float phi1_;
    float phi2_;

    // Z cand masses
    double bestZmass_;
    double subBestZmass_;

    /// Vertex variables
    double dca_;
    double crossingPointDistance_;
    double dZ12_;
    double z1_;
    double z2_;


    //JJ variables
    double mjj_,ptjj_;

    //recoil
    reco::Candidate::LorentzVector recoil_;
    double recoilDPhi_;

    //jets
    std::vector<JetPtr> jets_;
    double ht_;

    //VBF
    double vbfMass_;
    double vbfDEta_;

    double vbfPt1_;
    double vbfPt2_;
    double vbfEta1_;
    double vbfEta2_;

    int vbfNJetsGap20_;
    int vbfNJetsGap30_;

    /// Mtautau solutions reconstructed by NSVfit algorithm
    std::vector<NSVfitResonanceHypothesisSummary> nSVfitSolutions_;

};

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

typedef CompositePtrCandidateT1T2MEt<reco::Candidate, reco::Candidate> DiCandidatePair;
typedef CompositePtrCandidateT1T2MEt<pat::Electron, pat::Tau> PATElecTauPair;
typedef CompositePtrCandidateT1T2MEt<pat::Muon, pat::Tau> PATMuTauPair;
typedef CompositePtrCandidateT1T2MEt<pat::Muon, pat::Jet> PATMuJetPair;
typedef CompositePtrCandidateT1T2MEt<pat::Muon, reco::RecoChargedCandidate> PATMuTrackPair;
typedef CompositePtrCandidateT1T2MEt<pat::Tau, pat::Tau> PATDiTauPair;
typedef CompositePtrCandidateT1T2MEt<pat::Electron, pat::Muon> PATElecMuPair;
typedef CompositePtrCandidateT1T2MEt<pat::Electron, pat::Electron> PATElecPair;
typedef CompositePtrCandidateT1T2MEt<pat::Electron, reco::RecoChargedCandidate> PATEleTrackPair;
typedef CompositePtrCandidateT1T2MEt<pat::Muon, pat::Muon> PATMuPair;
typedef CompositePtrCandidateT1T2MEt<pat::Electron, pat::Photon> PATElecSCPair;

//For ZZ
typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATMuTauPair> PATMuMuMuTauQuad;
typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATDiTauPair> PATMuMuTauTauQuad;
typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATElecTauPair> PATMuMuEleTauQuad;
typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATElecMuPair> PATMuMuEleMuQuad;
typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATMuPair> PATMuMuMuMuQuad;
typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATElecPair> PATMuMuEleEleQuad;
typedef CompositePtrCandidateT1T2MEt<PATElecPair,PATElecTauPair> PATEleEleEleTauQuad;
typedef CompositePtrCandidateT1T2MEt<PATElecPair,PATDiTauPair> PATEleEleTauTauQuad;
typedef CompositePtrCandidateT1T2MEt<PATElecPair,PATElecPair> PATEleEleEleEleQuad;
typedef CompositePtrCandidateT1T2MEt<PATElecPair, PATMuTauPair> PATEleEleMuTauQuad;
typedef CompositePtrCandidateT1T2MEt<PATElecPair, PATElecMuPair> PATEleEleEleMuQuad;
typedef CompositePtrCandidateT1T2MEt<PATElecPair, PATMuPair> PATEleEleMuMuQuad;
typedef CompositePtrCandidateT1T2MEt<PATElecSCPair, PATElecPair> PATEleSCEleEleQuad;
typedef CompositePtrCandidateT1T2MEt<PATElecPair, PATElecSCPair> PATEleEleEleSCQuad;
typedef CompositePtrCandidateT1T2MEt<PATMuPair, PATElecSCPair> PATMuMuEleSCQuad;
typedef CompositePtrCandidateT1T2MEt<PATElecSCPair, PATMuPair> PATEleSCMuMuQuad;

//Z+1 lepton
typedef CompositePtrCandidateT1T2MEt<PATElecPair, pat::Electron> PATEleEleEleTri;
typedef CompositePtrCandidateT1T2MEt<PATElecPair, pat::Muon> PATEleEleMuTri;
typedef CompositePtrCandidateT1T2MEt<PATMuPair, pat::Electron> PATMuMuEleTri;
typedef CompositePtrCandidateT1T2MEt<PATMuPair, pat::Muon> PATMuMuMuTri;

#endif
