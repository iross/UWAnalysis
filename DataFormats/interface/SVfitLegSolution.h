#ifndef AnalysisDataFormats_TauAnalysis_SVfitLegSolution_h
#define AnalysisDataFormats_TauAnalysis_SVfitLegSolution_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include <TMath.h>

class SVfitLegSolution
{
 public:
  enum polarizationHypothesisType { kLeftHanded, kRightHanded, kUnknown };

  SVfitLegSolution();
  SVfitLegSolution(polarizationHypothesisType);
  ~SVfitLegSolution();

  /// access to momentum of visible + invisible decay products
  /// in laboratory frame
  reco::Candidate::LorentzVector p4() const { return (p4Vis_ + p4Invis_); }

  /// access ratio of visible to total tau lepton momentum
  double x() const { return p4Vis_.energy()/(p4Vis_.energy() + p4Invis_.energy()); }

  /// access flag indicating if estimats for uncertainties are available
  bool hasErrorEstimates() const { return hasErrorEstimates_; }

  /// access uncertainty on reconstructed visible to total tau lepton momentum ratio
  double xErrUp() const { return xErrUp_; }
  double xErrDown() const { return xErrDown_; }
  double xErr() const { return TMath::Sqrt(0.5*(xErrUp()*xErrUp() + xErrDown()*xErrDown())); }

  /// access to momentum of visible decay products,
  /// in laboratory and tau lepton rest-frame
  const reco::Candidate::LorentzVector& p4Vis() const { return p4Vis_; }
  const reco::Candidate::LorentzVector& p4VisRestFrame() const { return p4VisRestFrame_; }

  /// access to momentum of invisible decay products (neutrinos produced in tau decay);
  /// reconstructed by SVfit algorithm,
  /// in laboratory and tau lepton rest-frame
  const reco::Candidate::LorentzVector& p4Invis() const { return p4Invis_; }
  const reco::Candidate::LorentzVector& p4InvisRestFrame() const { return p4InvisRestFrame_; }

  /// access to position of secondary vertex (tau lepton decay vertex)
  const AlgebraicVector3& decayVertexPos() const { return decayVertexPos_; }

  /// access to polarization hypothesis used by SVfit in reconstruction of this solution
  polarizationHypothesisType polarizationHypothesis() const { return polarizationHypothesis_; }

  /// access to decay angle in tau lepton rest frame
  double thetaRest() const { return TMath::ACos(p4VisRestFrame().Vect().Unit().Dot(p4().Vect().Unit())); }

  /// The tracks associated to the leg.
  const std::vector<reco::TrackBaseRef>& tracks() const { return tracks_; }

  /// Return the secondary vertex (for three prong taus) returned by a direct
  /// vertex fit of the associated tracks.
  const reco::Vertex& recoDecayVertex() const { return recoVertex_; }

  /// access to additional fit paramaters needed to fit
  ///  rho- --> pi- pi0 and a1- --> pi- pi0 pi0, a1- --> pi- pi+ pi- decays
  /// in case likelihood functions for decays of polarized tau leptons are used
  double thetaVMrho() const { return thetaVMrho_; }
  double thetaVMa1()  const { return thetaVMa1_;  }
  double thetaVMa1r() const { return thetaVMa1r_; }
  double phiVMa1r()   const { return phiVMa1r_;   }

  template<typename T1, typename T2> friend class SVfitAlgorithm;

  std::string polarizationHypothesisName() const
  {
    if      ( polarizationHypothesis_ == kLeftHanded  ) return "L";
    else if ( polarizationHypothesis_ == kRightHanded ) return "R";
    else return "Unknown";
  }

 private:
  /// polarization hypothesis used by SVfit in reconstruction of this solution
  polarizationHypothesisType polarizationHypothesis_;

  /// momentum of visible decay products,
  /// in laboratory and tau lepton rest-frame
  reco::Candidate::LorentzVector p4Vis_;
  reco::Candidate::LorentzVector p4VisRestFrame_;

  /// momentum of invisible decay products (neutrinos produced in tau decay);
  /// reconstructed by SVfit algorithm,
  /// in laboratory and tau lepton rest-frame
  reco::Candidate::LorentzVector p4Invis_;
  reco::Candidate::LorentzVector p4InvisRestFrame_;

  /// position of reconstructed tau lepton decay vertex
  AlgebraicVector3 decayVertexPos_;

  /// flag indicating if estimats for uncertainties are available
  bool hasErrorEstimates_;

  /// uncertainty on reconstructed visible to total tau lepton momentum ratio
  double xErrUp_;
  double xErrDown_;

  std::vector<reco::TrackBaseRef> tracks_;
  reco::Vertex recoVertex_;

  /// additional fit paramaters needed to fit
  ///  rho- --> pi- pi0 and a1- --> pi- pi0 pi0, a1- --> pi- pi+ pi- decays
  /// in case likelihood functions for decays of polarized tau leptons are used
  double thetaVMrho_;
  double thetaVMa1_;
  double thetaVMa1r_;
  double phiVMa1r_;
};

#endif
