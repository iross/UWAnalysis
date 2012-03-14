#ifndef TauAnalysis_CandidateTools_SVfitLikelihoodDiTauKinematics_h
#define TauAnalysis_CandidateTools_SVfitLikelihoodDiTauKinematics_h

/** \class SVfitLikelihoodDiTauKinematics
 *
 * Plugin for computing likelihood for decay kinematics of tau lepton pair;
 * different types of likelihoods (isotropic/unpolarized/polarized decay) 
 * can be specified via plugins for the two tau lepton decay "legs";
 * plugin is used by SVfit algorithm
 * 
 * \author Evan Friis, Christian Veelken; UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitLikelihoodDiTauKinematics.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UWAnalysis/RecoTools/interface/SVfitDiTauLikelihoodBase.h"
#include "UWAnalysis/RecoTools/interface/SVfitLegLikelihoodBase.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/SVfitDiTauSolution.h"

#include <iomanip>

template <typename T1, typename T2>
  class SVfitLikelihoodDiTauKinematics : public SVfitDiTauLikelihoodBase<T1,T2>
{
 public:
  SVfitLikelihoodDiTauKinematics(const edm::ParameterSet&);
  ~SVfitLikelihoodDiTauKinematics();

  virtual void beginJob();
  virtual void beginEvent(edm::Event&, const edm::EventSetup&);
  virtual void beginCandidate(const CompositePtrCandidateT1T2MEt<T1,T2>&);

  void print(std::ostream&) const;

  bool isFittedParameter(int) const;
  bool supportsPolarization() const;

  double operator()(const CompositePtrCandidateT1T2MEt<T1,T2>&, const SVfitDiTauSolution&) const;

 private:
  SVfitLegLikelihoodBase<T1>* leg1Likelihood_;
  SVfitLegLikelihoodBase<T2>* leg2Likelihood_;
};

#endif
