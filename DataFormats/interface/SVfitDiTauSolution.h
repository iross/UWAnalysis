#ifndef AnalysisDataFormats_TauAnalysis_SVfitDiTauSolution_h
#define AnalysisDataFormats_TauAnalysis_SVfitDiTauSolution_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"

#include "UWAnalysis/DataFormats/interface/SVfitLegSolution.h"
#include "UWAnalysis/DataFormats/interface/tauAnalysisAuxFunctions.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include <TMath.h>

#include <string>
#include <iostream>

class SVfitDiTauSolution
{
 public:
  SVfitDiTauSolution();
  SVfitDiTauSolution(SVfitLegSolution::polarizationHypothesisType, SVfitLegSolution::polarizationHypothesisType);
  ~SVfitDiTauSolution();

  /// access to position of primary event vertex (tau lepton production vertex);
  /// refitted by SVfit algorithm after excluding from fit tracks associated to tau lepton decay products
  ///
  /// NB: error on position returned by eventVertexErrSVrefitted method not 100% correct,
  ///     as uncertainty on "correction" to primary event vertex position
  ///     determined by SVfit algorithm is not taken into account
  ///
  bool eventVertexSVrefittedIsValid() const { return eventVertexIsValid_; }
  AlgebraicVector3 eventVertexPosSVrefitted() const { return (eventVertexPosition_ + eventVertexPositionShift_); }
  const AlgebraicSymMatrix33& eventVertexErrSVrefitted() const { return eventVertexPositionErr_; }

  const AlgebraicVector3& eventVertexShiftSVrefitted() const { return eventVertexPositionShift_; }

  double leg1DecayDistance() const {
    return TauAnalysis_namespace::compDecayDistance(eventVertexPosSVrefitted(), leg1_.decayVertexPos());
  }
  double leg2DecayDistance() const {
    return TauAnalysis_namespace::compDecayDistance(eventVertexPosSVrefitted(), leg2_.decayVertexPos());
  }

  /// access to momentum of both tau lepton decay "legs"
  reco::Candidate::LorentzVector p4() const { return (leg1_.p4() + leg2_.p4()); }
  reco::Candidate::LorentzVector p4Vis() const { return leg1_.p4Vis() + leg2_.p4Vis(); }
  reco::Candidate::LorentzVector p4Invis() const { return leg1_.p4Invis() + leg2_.p4Invis(); }

  /// access to reconstructed invariant mass
  double mass() const { return p4().mass(); }

  /// access flag indicating if estimats for uncertainties are available
  bool hasErrorEstimates() const { return hasErrorEstimates_; }

  /// access uncertainty on reconstructed mass
  double massErrUp() const { return massErrUp_; }
  double massErrDown() const { return massErrDown_; }
  double massErr() const { return TMath::Sqrt(0.5*(massErrUp()*massErrUp() + massErrDown()*massErrDown())); }

  /// access to individual tau lepton decay "legs"
  const SVfitLegSolution& leg1() const { return leg1_; }
  const SVfitLegSolution& leg2() const { return leg2_; }

  /// access likelihood values of all/individual plugins
  /// used by SVfit to reconstruct this solution
  double negLogLikelihood() const;
  double negLogLikelihood(const std::string&) const;

  const std::map<std::string, double>& negLogLikelihoods() const {
    return negLogLikelihoods_;
  }

  bool isValidSolution() const { return (minuitStatus_ == 0); }
  int minuitStatus() const { return minuitStatus_; }

  template<typename T1, typename T2> friend class SVfitAlgorithm;

  std::string polarizationHypothesisName() const
  {
    SVfitLegSolution::polarizationHypothesisType leg1PolarizationHypothesis = leg1_.polarizationHypothesis();
    SVfitLegSolution::polarizationHypothesisType leg2PolarizationHypothesis = leg2_.polarizationHypothesis();

    if      ( leg1PolarizationHypothesis == SVfitLegSolution::kLeftHanded  &&
	      leg2PolarizationHypothesis == SVfitLegSolution::kLeftHanded  ) return "LL";
    else if ( leg1PolarizationHypothesis == SVfitLegSolution::kLeftHanded  &&
              leg2PolarizationHypothesis == SVfitLegSolution::kRightHanded ) return "LR";
    else if ( leg1PolarizationHypothesis == SVfitLegSolution::kRightHanded &&
	      leg2PolarizationHypothesis == SVfitLegSolution::kLeftHanded  ) return "RL";
    else if ( leg1PolarizationHypothesis == SVfitLegSolution::kRightHanded  &&
              leg2PolarizationHypothesis == SVfitLegSolution::kRightHanded ) return "RR";
    else return "Unknown";
  }

 private:
  /// position of primary event vertex (tau lepton production vertex);
  /// refitted by SVfit algorithm after excluding from fit tracks associated to tau lepton decay products
  AlgebraicVector3 eventVertexPosition_;
  AlgebraicSymMatrix33 eventVertexPositionErr_;
  AlgebraicVector3 eventVertexPositionShift_;
  bool eventVertexIsValid_;

  /// individual tau lepton decay "legs"
  SVfitLegSolution leg1_;
  SVfitLegSolution leg2_;

  /// likelihood values of individual plugins
  /// used by SVfit to reconstruct this solution
  std::map<std::string, double> negLogLikelihoods_; // key = name of plugin; value = -log(likelihood)

  /// convergence status of Minuit log-likelihood minimization
  /// (1 = fit suceeded to converge, 0 = fit failed to converged)
  int minuitStatus_;

  /// flag indicating if estimats for uncertainties are available
  bool hasErrorEstimates_;

  /// uncertainty on reconstructed mass
  double massErrUp_;
  double massErrDown_;
};

std::ostream& operator<<(std::ostream& stream, const SVfitDiTauSolution& solution);

#endif

