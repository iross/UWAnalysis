#ifndef TauAnalysis_CandidateTools_SVfitVMlineShapeIntegrand_h
#define TauAnalysis_CandidateTools_SVfitVMlineShapeIntegrand_h

/** \class SVfitVMlineShapeIntegrand
 *
 * Auxiliary class for computing decay distributions for polarized tau leptons
 * averaged over vector-meson (either rho or a1) line-shape factors
 *
 * The class implements formulas taken from the papers
 *  [1] "Tau polarization and its correlations as a probe of new physics",
 *      B.K. Bullock, K. Hagiwara and A.D. Martin,
 *      Nucl. Phys. B395 (1993) 499.
 *     (formulas 2.16 to 2.25)
 *  [2] "Charged Higgs boson search at the TeVatron upgrade using tau polarization",
 *      S. Raychaudhuri and D.P. Roy,
 *      Phys. Rev.  D52 (1995) 1556.           
 *     (formulas 32 to 38)
 *
 * \author Christian Veelken, UC Davis
 *
 * \version $Revision: 1.1 $
 *
 * $Id: SVfitVMlineShapeIntegrand.h,v 1.1 2010/12/11 23:49:58 bachtis Exp $
 *
 */

#include <Math/IFunction.h>
#include <Math/IFunctionfwd.h>

class SVfitVMlineShapeIntegrand : public ROOT::Math::IGenFunction
{
 public:
  enum VMtype { kVMtypeUndefined, kVMrho, kVMa1 };
  enum VMmode { kVMmodeUndefined, kVMlineShape, kVMnorm };
  enum VMpol  { kVMpolUndefined, kVMlongitudinalPol, kVMtransversePol };

  SVfitVMlineShapeIntegrand(bool, double);
  SVfitVMlineShapeIntegrand(const SVfitVMlineShapeIntegrand&);
  virtual ~SVfitVMlineShapeIntegrand();

  SVfitVMlineShapeIntegrand& operator=(const SVfitVMlineShapeIntegrand&);
  
  void SetParameterTheta(double);
  void SetParameterTauLeptonPol(double);

  void SetVMtype(VMtype);
  void SetVMpol(VMpol);

  void SetMode(VMmode mode);

  virtual ROOT::Math::IGenFunction* Clone () const { return new SVfitVMlineShapeIntegrand(*this); }

 private:
  double DoEval(double) const;

  double DvNorm2(double) const;
  double Gammav(double) const;
  double fv(double) const;
  double Fv(double) const;
  double HL(double, double, double, double, double) const;
  double HT(double, double, double, double, double) const;
  double decayL(double, double, double, double, double) const; 
  double decayT(double, double, double, double, double) const;

  bool useCollApproxFormulas_;

  double minMass2_;     // minimum value for mass^2 for which integrand is to be computed

  VMtype vmType_;
  VMpol  vmPol_;

  VMmode mode_;

  double theta_;        // angle between direction of vector meson in tau lepton rest-frame and tau momentum vector in laboratory frame
  double tauLeptonPol_; // tau lepton polarization 

//--- temporary variables to speed-up computations
//    (recomputed every time one of the parameters gets set)
  double m0_;           // resonance mass of vector meson
  double m0square_;
  double Gamma0_;       // width of vector meson resonance
  double cosTheta_;
  double sinTheta_;
  double tanTheta_;
  double fv0_;
};

#endif
