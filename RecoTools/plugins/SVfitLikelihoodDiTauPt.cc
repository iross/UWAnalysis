#include "UWAnalysis/RecoTools/plugins/SVfitLikelihoodDiTauPt.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include "UWAnalysis/RecoTools/interface/SVfitAlgorithm.h"
#include "UWAnalysis/RecoTools/interface/svFitAuxFunctions.h"
#include "UWAnalysis/RecoTools/interface/candidateAuxFunctions.h"

#include <TPRegexp.h>
#include <TString.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TMath.h>

#include <string>

using namespace SVfit_namespace;

template <typename T1, typename T2>
SVfitLikelihoodDiTauPt<T1,T2>::SVfitLikelihoodDiTauPt(const edm::ParameterSet& cfg)
  : SVfitDiTauLikelihoodBase<T1,T2>(cfg),
    parseError_(0)
{
  //std::cout << "<SVfitLikelihoodDiTauPt::SVfitLikelihoodDiTauPt>:" << std::endl;

  std::string pdf_string = cfg.getParameter<std::string>("pdf");
  //std::cout << " pdf_string = " << pdf_string << std::endl;

  pdf_ = new TFormula("pdf", pdf_string.data());  

  TPRegexp regexpParser_pdfParameter("\\[([[:digit:]]+)\\]");
  
  size_t pos_start = 0;
  while ( (pos_start = pdf_string.find("[", pos_start)) != std::string::npos ) {
    size_t pos_end = pdf_string.find("]", pos_start);

    if ( pos_end == std::string::npos ) {
      edm::LogError ("SVfitLikelihoodDiTauPt") << " Failed to decode pdf = " << pdf_string << " !!";
      parseError_ = 1;
      break;
    }

    std::string pdfParameter_string = std::string(pdf_string, pos_start, (pos_end - pos_start) + 1);
    //std::cout << " pdfParameter_string = " << pdfParameter_string << std::endl;

    TString pdfParameter_tstring = pdfParameter_string;
    if ( regexpParser_pdfParameter.Match(pdfParameter_tstring) == 2 ) {
      TObjArray* subStrings = regexpParser_pdfParameter.MatchS(pdfParameter_tstring);
      
      std::string subString = ((TObjString*)subStrings->At(1))->GetString().Data();
      //std::cout << " subString " << subString << std::endl;
      
      int pdfParameter_index = atoi(subString.data());

//--- only create new parameter object if it does not yet exists
//    (the same parameter object may well appear twice in pdf formula...)
      if ( pdfParameters_.find(pdfParameter_index) == pdfParameters_.end() ) {
	std::string pdfParameterName = std::string("par").append(subString);
	//std::cout << " pdfParameterName = " << pdfParameterName << std::endl;
	
	std::string pdfParameterValue = cfg.getParameter<std::string>(pdfParameterName);
	//std::cout << " pdfParameterValue = " << pdfParameterValue << std::endl;
	
	pdfParameters_.insert(std::make_pair(pdfParameter_index, new TFormula(pdfParameterName.data(), pdfParameterValue.data())));
      }
    } else {
      edm::LogError ("SVfitLikelihoodDiTauPt") << " Failed to decode pdf = " << pdf_string << " !!";
      parseError_ = 1;
      break;
    }
    
    pos_start = pos_end;
  }

  //print(std::cout);
}

template <typename T1, typename T2>
SVfitLikelihoodDiTauPt<T1,T2>::~SVfitLikelihoodDiTauPt()
{
  delete pdf_;
  for ( std::map<int, TFormula*>::iterator it = pdfParameters_.begin();
	it != pdfParameters_.end(); ++it ) {
    delete it->second;
  }
}

template <typename T1, typename T2>
void SVfitLikelihoodDiTauPt<T1,T2>::print(std::ostream& stream) const
{
  stream << "<SVfitLikelihoodDiTauPt::print>:" << std::endl;
  stream << " pdf = " << pdf_->GetTitle() << std::endl;
  for ( std::map<int, TFormula*>::const_iterator pdfParameter = pdfParameters_.begin();
	pdfParameter != pdfParameters_.end(); ++pdfParameter ) {
    stream << " " << pdfParameter->second->GetName() << " = " << pdfParameter->second->GetTitle() << std::endl;
  }
}

template <typename T1, typename T2>
double SVfitLikelihoodDiTauPt<T1,T2>::operator()(const CompositePtrCandidateT1T2MEt<T1,T2>& diTau, 
						 const SVfitDiTauSolution& solution) const
{
//--- compute negative log-likelihood for tau+ tau- pair to have a certain transverse momentum
//
//    NB: the form of the likelihood function has been obtained by fitting the distribution of Z boson transverse momentum
//        in simulated Z --> tau+ tau- events with an Exponential function smeared by a Gaussian 
//       ( a.k.a. "Exponentially Modified Gaussian (EMG)"; 
//        c.f. http://www.chromandspec.com/Docs/Pittcon2010%20EMG%20Reconstruction%20of%20peaks.pdf )
//
  //std::cout << "SVfitLikelihoodDiTauPt::operator()>:" << std::endl;

  if ( parseError_ ) return 0.;
  
  double diTauMass = solution.p4().mass();
  //std::cout << " diTauMass = " << diTauMass << std::endl;

  for ( std::map<int, TFormula*>::const_iterator pdfParameter = pdfParameters_.begin();
	pdfParameter != pdfParameters_.end(); ++pdfParameter ) {
    double pdfParameterValue = pdfParameter->second->Eval(diTauMass);
    pdf_->SetParameter(pdfParameter->first, pdfParameterValue);
  }

  double diTauPt = solution.p4().pt();
  //std::cout << " diTauPt = " << diTauPt << std::endl;

  double pdfValue = pdf_->Eval(diTauPt);
  if ( !(pdfValue > 0.) ) {
    edm::LogWarning ("SVfitLikelihoodDiTauPt::operator()") << " Failed to evaluate pdf !!";
    return 0.;
  }

  double negLogLikelihood = -TMath::Log(pdfValue);
  //std::cout << "--> negLogLikelihood = " << negLogLikelihood << std::endl;
  
  return negLogLikelihood;
}

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/Candidate/interface/Candidate.h"

typedef SVfitLikelihoodDiTauPt<pat::Electron, pat::Tau> SVfitLikelihoodElecTauPairPt;
typedef SVfitLikelihoodDiTauPt<pat::Muon, pat::Tau> SVfitLikelihoodMuTauPairPt;
typedef SVfitLikelihoodDiTauPt<pat::Tau, pat::Tau> SVfitLikelihoodDiTauPairPt;
typedef SVfitLikelihoodDiTauPt<pat::Electron, pat::Muon> SVfitLikelihoodElecMuPairPt;
typedef SVfitLikelihoodDiTauPt<reco::Candidate, reco::Candidate> SVfitLikelihoodDiCandidatePairPt;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_EDM_PLUGIN(SVfitElecTauPairLikelihoodBasePluginFactory, SVfitLikelihoodElecTauPairPt, "SVfitLikelihoodElecTauPairPt");
DEFINE_EDM_PLUGIN(SVfitMuTauPairLikelihoodBasePluginFactory, SVfitLikelihoodMuTauPairPt, "SVfitLikelihoodMuTauPairPt");
DEFINE_EDM_PLUGIN(SVfitDiTauPairLikelihoodBasePluginFactory, SVfitLikelihoodDiTauPairPt, "SVfitLikelihoodDiTauPairPt");
DEFINE_EDM_PLUGIN(SVfitElecMuPairLikelihoodBasePluginFactory, SVfitLikelihoodElecMuPairPt, "SVfitLikelihoodElecMuPairPt");
DEFINE_EDM_PLUGIN(SVfitDiCandidatePairLikelihoodBasePluginFactory, SVfitLikelihoodDiCandidatePairPt, "SVfitLikelihoodDiCandidatePairPt");
