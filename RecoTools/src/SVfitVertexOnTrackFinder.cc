#include "UWAnalysis/RecoTools/interface/SVfitVertexOnTrackFinder.h"
#include "UWAnalysis/RecoTools/interface/SVfitTrackTools.h"

#include "UWAnalysis/RecoTools/interface/SVfitTrackExtrapolation.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"

#include <TRotation.h>

namespace SVfit { namespace track {

const TransientTrackBuilder* VertexOnTrackFinder::builder_ = NULL;

VertexOnTrackFinder::VertexOnTrackFinder(const SVfitLegSolution& soln)
    :soln_(soln) {
  // Build transient tracks only if there is only one track we are using.
  if (soln.tracks().size() == 1) {
    track_ = builder_->build(soln.tracks()[0].castTo<reco::TrackRef>());
  }
}

GlobalPoint VertexOnTrackFinder::decayVertex(const GlobalPoint& pv,
                                             double angleVisLabFrame) {
  GlobalVector visibleDirection(soln_.p4Vis().px(), soln_.p4Vis().py(),
                                soln_.p4Vis().pz());
//  std::cout << "Finding point on trk for " << pv << " visdir: " << visibleDirection << " angle: " << angleVisLabFrame << std::endl;
  // Linearize our track, then find the intersection of the cone and the line.
  if (soln_.tracks().size() == 1) {
//    std::cout << "Finding intersection of line and cone" << std::endl;
    AlgebraicVector3 refPoint(pv.x(), pv.y(), pv.z());
    TrackExtrapolation extrapolation(track_, refPoint);

    GlobalPoint lineOffset(extrapolation.dcaPosition().At(0),
                           extrapolation.dcaPosition().At(1),
                           extrapolation.dcaPosition().At(2));

    GlobalVector lineDirection(extrapolation.tangent().At(0),
                               extrapolation.tangent().At(1),
                               extrapolation.tangent().At(2));
//    std::cout << "line offset: " << lineOffset << " dir: " << lineDirection << std::endl;

    int status = 0;
    GlobalPoint output;
    // See if the line intersects with our cone.
    output = intersectionOfLineAndCone(lineOffset, lineDirection,
                                       pv, visibleDirection,
                                       angleVisLabFrame, status);
//    std::cout << "found intersection? " << status << " " << output << std::endl;
    if (status)
      return output;

    // Otherwise it didn't intersect, or intersected "behind" the PV. Try and
    // find the point of closest approach.
    output = pcaOfLineToCone(lineOffset, lineDirection, pv, visibleDirection,
                             angleVisLabFrame, status);
    // Okay, we found the point on the line closest to the cone.  Now we return
    // the point on the *cone* closest to this point.
//    std::cout << "found pca? " << status << " " << output << std::endl;
    if (status) {
      output = pcaOfConeToPoint(output, pv, visibleDirection,
                                angleVisLabFrame, status);
//      std::cout << "found final? " << status << " " << output << std::endl;
      if (status) {
        return output;
      }
    }
  } else {
    // Otherwise, this is a three prong and we've fitted a vertex for this leg.
    // Just take PCA of the cone to the fitted vertex.
    // How could this fail
//    std::cout << "Finding intersection of line and vertex" << std::endl;
    int status = 1;
    reco::Candidate::Point fittedPoint = soln_.recoDecayVertex().position();
    GlobalPoint fittedGlobalPoint(fittedPoint.x(), fittedPoint.y(),
                                  fittedPoint.z());
    GlobalPoint output = pcaOfConeToPoint(fittedGlobalPoint,
                                          pv, visibleDirection,
                                          angleVisLabFrame, status);
//    std::cout << "found point? " << status << " " << output << std::endl;
    if (status) {
      return output;
    }
  }
  // If we didn't find a solution by now, we are in trouble!!
//  std::cout << "ERROR: no solutions found in SVfitVertexOnTrackFinder::decayVertex"
//      << ", returning the PV!" << std::endl;
  return pv;
}

// Version where a correction is applied on the the phi and flight path.
GlobalPoint VertexOnTrackFinder::decayVertex(
    const GlobalPoint& pv, double angleVisLabFrame,
    double phiCorrection, double flightCorrection) {
  GlobalPoint uncorrected = decayVertex(pv, angleVisLabFrame);
  // Get the relative offset to the PV
  TVector3 outputTVector(uncorrected.x() - pv.x(),
                         uncorrected.y() - pv.y(),
                         uncorrected.z() - pv.z());
  if (outputTVector.Mag() == 0)
    return uncorrected;
  // Rotate by phiCorrection about the visible momentum
  TRotation rot;
  reco::Candidate::Vector visDirection = soln_.p4Vis().Vect().Unit();
  TVector3 visDirectionTVector(visDirection.x(), visDirection.y(),
                               visDirection.z());
  rot.Rotate(phiCorrection, visDirectionTVector);
  outputTVector = rot * outputTVector;
  // Apply the flight path correction
  outputTVector.SetMag(outputTVector.Mag() + flightCorrection);
  return GlobalPoint(outputTVector.x() + pv.x(),
                     outputTVector.y() + pv.y(),
                     outputTVector.z() + pv.z());
}


GlobalPoint VertexOnTrackFinder::decayVertex(
    const AlgebraicVector3& pv, double angleVisLabFrame,
    double phiCorrection, double flightCorrection) {
  return decayVertex(GlobalPoint(pv.At(0), pv.At(1), pv.At(2)),
                     angleVisLabFrame,
                     phiCorrection,
                     flightCorrection);
}


}}  // end namespace SVfit::track
