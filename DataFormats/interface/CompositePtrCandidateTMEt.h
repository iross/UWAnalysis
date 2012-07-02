#ifndef __UWAnalysis_DataFormats_CompositeRefCandidateTMEt_h__
#define __UWAnalysis_DataFormats_CompositeRefCandidateTMEt_h__

/** \class CompositeRefCandidateTMEt
 *
 * Combination of visible tau decay products with missing transverse momentum 
 * (representing the undetected momentum carried away 
 *  the neutrino produced in a W --> tau nu decay and the neutrinos produced in the tau decay)
 * 
 * \authors Christian Veelken
 *
 * \version $Revision: 1.3 $
 *
 * $Id: CompositePtrCandidateTMEt.h,v 1.3 2010/11/20 00:13:32 bachtis Exp $
 *
 */

#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/Candidate/interface/LeafCandidate.h" 
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

template<typename T>

class CompositePtrCandidateTMEt : public reco::LeafCandidate 
{
    typedef edm::Ptr<T> TPtr;
    typedef edm::Ptr<reco::Candidate> METPtr;
    typedef edm::Ptr<pat::Jet> JetPtr;
    typedef std::vector<edm::Ptr<pat::Jet> > JetPtrVector;

    public:

    /// default constructor
    CompositePtrCandidateTMEt() {}

    /// constructor with MEt
    CompositePtrCandidateTMEt(const TPtr visDecayProducts, const METPtr met)
        : visDecayProducts_(visDecayProducts), met_(met) {recoilDPhi_=0;}

    /// destructor
    ~CompositePtrCandidateTMEt() {}

    /// access to daughter particles
    const TPtr lepton() const { return visDecayProducts_; }

    /// access to missing transverse momentum
    const METPtr met() const { return met_; }

    /// get transverse mass of visible decay products + missing transverse momentum
    double mt() const { return mt_; }

    /// get acoplanarity angle (angle in transverse plane) between visible decay products 
    /// and missing transverse momentum 
    double dPhi() const { return dPhi_; } 
    const reco::Candidate::LorentzVector recoil() const {return recoil_;}
    double recoilDPhi() const {return recoilDPhi_;}

    ///Jet variables
    const JetPtrVector jets() const {return jets_;}
    int nJets() const {return jets_.size();}
    double ht() const {return ht_;}
    const JetPtr jet(int i) const {return jets_.at(i);}

    /// clone  object
    CompositePtrCandidateTMEt<T>* clone() const { return new CompositePtrCandidateTMEt<T>(*this); }

    private:

    void setJetValues(const JetPtrVector& jets,double ht) {
        jets_ = jets;
        ht_   = ht;
    }

    /// allow only CompositePtrCandidateTMEtAlgorithm to change values of data-members
    template<typename T_type> friend class CompositePtrCandidateTMEtAlgorithm; 

    /// set transverse mass of visible decay products + missing transverse momentum
    void setMt(double mt) { mt_ = mt; }
    /// set acoplanarity angle (angle in transverse plane) between visible decay products 
    /// and missing transverse momentum
    void setDPhi(double dPhi) { dPhi_ = dPhi; }

    void setRecoil(const reco::Candidate::LorentzVector& recoil) {recoil_ = recoil; }
    void setRecoilDPhi(double dPhi) {recoilDPhi_ = dPhi;}

    /// references/pointers to decay products and missing transverse momentum
    reco::Candidate::LorentzVector recoil_;
    double recoilDPhi_;

    TPtr visDecayProducts_;
    METPtr met_;
    /// transverse mass of visible decay products + missing transverse momentum
    double mt_;
    /// acoplanarity angle (angle in transverse plane) between visible decay products
    /// and missing transverse momentum
    double dPhi_;

    JetPtrVector jets_;
    double ht_;


};

#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

typedef CompositePtrCandidateTMEt<pat::Tau> PATTauNuPair;
typedef CompositePtrCandidateTMEt<pat::Muon> PATMuonNuPair;
typedef CompositePtrCandidateTMEt<pat::Electron> PATElectronNuPair;
typedef CompositePtrCandidateTMEt<reco::Candidate> PATCandNuPair;

#endif
