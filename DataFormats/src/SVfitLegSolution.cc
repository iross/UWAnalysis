#include "UWAnalysis/DataFormats/interface/SVfitLegSolution.h"

SVfitLegSolution::SVfitLegSolution()
  : polarizationHypothesis_(kUnknown),
    hasErrorEstimates_(false)
{}

SVfitLegSolution::SVfitLegSolution(polarizationHypothesisType polarizationHypothesis)
  : polarizationHypothesis_(polarizationHypothesis),
    hasErrorEstimates_(false)
{}

SVfitLegSolution::~SVfitLegSolution()
{
// nothing to be done yet
}

