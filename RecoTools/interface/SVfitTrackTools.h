#ifndef TauAanlysis_CandidateTools_SVfitTrackTools_h
#define TauAanlysis_CandidateTools_SVfitTrackTools_h

/*
 * Geometrical tools used in the SV fit method.  Specifically, functions to find
 * the intersection or point of closest approach between lines and cones.
 *
 * Authors: Evan K. Friis, Christian Veelken (UC Davis)
 *
 */

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"

namespace SVfit { namespace track {

/// Find the point of intersection between a line and a cone.  status = 1 if a
/// solution found, 0 if not.
GlobalPoint intersectionOfLineAndCone(
    const GlobalPoint &lineOffset, const GlobalVector &lineDirection,
    const GlobalPoint &coneVertex, const GlobalVector &coneDirection,
    double coneAngle, int &status);


/// Find the point of closest approach of a line to a cone.  status = 1 if
/// solution found, 0 if not.
GlobalPoint pcaOfLineToCone(
    const GlobalPoint &lineOffset, const GlobalVector &lineDirection,
    const GlobalPoint &coneVertex, const GlobalVector &coneDirection,
    double coneAngle, int &status);


/// Find the point *on the cone* closest to the input point.
GlobalPoint pcaOfConeToPoint(
    const GlobalPoint& point,
    const GlobalPoint &coneVertex, const GlobalVector &coneDirection,
    double coneAngle, int &status);

GlobalPoint transform(const GlobalPoint& newOrigin, const GlobalVector &newUz,
                      const GlobalPoint& toTransform);
GlobalPoint untransform(const GlobalPoint& newOrigin, const GlobalVector &newUz,
                      const GlobalPoint& toTransform);

GlobalVector transform(const GlobalPoint& newOrigin, const GlobalVector &newUz,
                      const GlobalVector& toTransform);
GlobalVector untransform(const GlobalPoint& newOrigin, const GlobalVector &newUz,
                      const GlobalVector& toTransform);

}}  // end namespace SVfit::track

#endif
