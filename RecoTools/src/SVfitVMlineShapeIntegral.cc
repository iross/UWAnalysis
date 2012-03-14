#include "UWAnalysis/RecoTools/interface/SVfitVMlineShapeIntegral.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "UWAnalysis/RecoTools/interface/svFitAuxFunctions.h"

using namespace SVfit_namespace;

#include <limits>

SVfitVMlineShapeIntegral::SVfitVMlineShapeIntegral(SVfitVMlineShapeIntegrand::VMtype vmType, 
						   SVfitVMlineShapeIntegrand::VMpol vmPol, bool useCollApproxFormulas)
{
  //std::cout << "<SVfitVMlineShapeIntegral::SVfitVMlineShapeIntegral>:" << std::endl;
  //std::cout << " vmType = " << vmType << std::endl;
  //std::cout << " vmPol = " << vmPol << std::endl;
  //std::cout << " useCollApproxFormulas = " << useCollApproxFormulas << std::endl;

//--- compute lower limit for normalization integral
//   = invariant mass of n-pion system
//   
//    CV: difference in mass between charged and neutral pions is ignored
//
  unsigned numPions = 0;
  if      ( vmType == SVfitVMlineShapeIntegrand::kVMrho ) numPions = 2;
  else if ( vmType == SVfitVMlineShapeIntegrand::kVMa1  ) numPions = 3;
  else {
    edm::LogError ("SVfitVMlineShapeIntegrand::update")
      << " Invalid vecor meson type = " << vmType << " !!";
  }
  minMass2_ = square(numPions*chargedPionMass);
  //std::cout << " minMass2 = " << minMass2_ << std::endl;

  integrand_ = new SVfitVMlineShapeIntegrand(useCollApproxFormulas, minMass2_);
  integrand_->SetVMtype(vmType);
  integrand_->SetVMpol(vmPol);
  integrand_->SetMode(SVfitVMlineShapeIntegrand::kVMnorm);

//--- CV: need to trigger update of ROOT::Math::Integrator by calling integrator->SetFunction
//        after calling any non-const function of SVfitVMlineShapeIntegrand 
  integrator_ = new ROOT::Math::Integrator(*integrand_);
  integrator_->SetFunction(*integrand_);

//--- compute vector meson line-shape normalization factor
  norm_ = integrator_->Integral(minMass2_, tauLeptonMass2); 
  //std::cout << " norm = " << norm_ << std::endl;

//--- set integrand to compute vector meson line-shape integrals in the following...  
  integrand_->SetMode(SVfitVMlineShapeIntegrand::kVMlineShape);
  integrator_->SetFunction(*integrand_);
}

SVfitVMlineShapeIntegral::SVfitVMlineShapeIntegral(const SVfitVMlineShapeIntegral& bluePrint)
{
  integrand_ = new SVfitVMlineShapeIntegrand(*bluePrint.integrand_);
  
  integrator_ = new ROOT::Math::Integrator(*integrand_);
  integrator_->SetFunction(*integrand_);

  minMass2_ = bluePrint.minMass2_;
  norm_ = bluePrint.norm_;
}

SVfitVMlineShapeIntegral::~SVfitVMlineShapeIntegral()
{
  delete integrator_;
  delete integrand_;
}

SVfitVMlineShapeIntegral& SVfitVMlineShapeIntegral::operator=(const SVfitVMlineShapeIntegral& bluePrint)
{
  delete integrator_;
  delete integrand_;

  integrand_ = new SVfitVMlineShapeIntegrand(*bluePrint.integrand_);
  
  integrator_ = new ROOT::Math::Integrator(*integrand_);
  integrator_->SetFunction(*integrand_);

  minMass2_ = bluePrint.minMass2_;
  norm_ = bluePrint.norm_;

  return (*this);
}

double SVfitVMlineShapeIntegral::operator()(double theta, double tauLeptonPol, double z) const
{
  //std::cout << "<SVfitVMlineShapeIntegral::operator()>:" << std::endl;
  //std::cout << " theta = " << theta << std::endl;
  //std::cout << " tauLeptonPol = " << tauLeptonPol << std::endl;
  //std::cout << " z = " << z << std::endl;

  integrand_->SetParameterTheta(theta);
  integrand_->SetParameterTauLeptonPol(tauLeptonPol);

  integrator_->SetFunction(*integrand_);

  double integral = integrator_->Integral(minMass2_, z*tauLeptonMass2)/norm_;
  //std::cout << "--> integral = " << integral << std::endl;

  return integral;
}  
