#include "UWAnalysis/RecoTools/interface/SVfitTrackTools.h"
#include "TMath.h"
#include <TRotation.h>
#include <iostream>

using namespace TMath;

namespace SVfit { namespace track {

GlobalPoint propagateLine(const GlobalPoint& origin,
                           const GlobalVector& tangent,
                           double pathLength) {
  return origin + tangent*pathLength;
}


// Get the correct path length solution of the quadratic equation.
// We always prefer the closest solution that is not negative - i.e. below the
// the cone vertex.
double solveQuadraticForPathLength(double a, double b, double c, int& status) {
  // Check if solutions are real and finite.
  if ( b*b - 4*a*c < 0 || c == 0 ) {
    //std::cout << "imaginary solutions!" << std::endl;
    status = 0;
    return 0;
  }
  // We always want the smaller one, if it is above zero
  double firstSolution =  (-b + Sqrt(b*b - 4*a*c))/(2*a);
  double secondSolution =  (-b - Sqrt(b*b - 4*a*c))/(2*a);
  bool oppositeSignSolutions = ((firstSolution * secondSolution) < 0);
//  std::cout << "first soln: " << firstSolution <<
//      "second soln: " << secondSolution << std::endl;
  // If one is negative, and one is positive, return the positive one.
  if (oppositeSignSolutions) {
    status = 1;
    double output = std::max(firstSolution, secondSolution);
//    std::cout << "opp sign-returning: " << output << std::endl;
    return output;
  }
  // Check if the solutions are both negative, that's an error.
  if (firstSolution < 0) {
    status = 0;
//    std::cout << "both negative!" << std::endl;
    return 0;
  }
  // The solutions are both positive.  Take the one that is closer to the origin
  status = 1;
  double output = std::min(firstSolution, secondSolution);
//  std::cout << "returning: " << output << std::endl;
  return output;
}


GlobalPoint intersectionOfLineAndCone(
    const GlobalPoint &lineOffsetIn, const GlobalVector &lineDirectionIn,
    const GlobalPoint &coneVertexIn, const GlobalVector &coneDirectionIn,
    double alpha /* cone angle */, int &status) {

//  std::cout << "cone dir in: " << coneDirectionIn << " line dir in" << lineDirectionIn << std::endl;
  // Shift coordinates such that the cone vertex is at the origin.
  GlobalPoint lineOffset = transform(coneVertexIn, coneDirectionIn,
                                     lineOffsetIn);

  // Now rotate so the cone is aligned along Z
  GlobalVector lineDirection = transform(coneVertexIn, coneDirectionIn,
                                         lineDirectionIn);

//  std::cout << "after transform: " << lineDirection << std::endl;

  // Okay, now we are ready to go.  Define our variables.  These match up to the
  // variable names in the corresponding Mathematic derivation.
  double trackDirX = lineDirection.x();
  double trackDirY = lineDirection.y();
  double trackDirZ = lineDirection.z();
  double trackOffsetX = lineOffset.x();
  double trackOffsetY = lineOffset.y();
  double trackOffsetZ = lineOffset.z();

  // Get quadratic coefficients
  double a = Power(trackDirX,2) + Power(trackDirY,2) - Power(trackDirZ,2)*Power(Tan(alpha),2);

  double b = 2*trackDirX*trackOffsetX + 2*trackDirY*trackOffsetY - 2*trackDirZ*trackOffsetZ*Power(Tan(alpha),2);

  double c = Power(trackOffsetX,2) + Power(trackOffsetY,2) - Power(trackOffsetZ,2)*Power(Tan(alpha),2);

  // If the line starts *exactly* at the origin, that is the intersection.
  if ( !trackOffsetX && !trackOffsetY && !trackOffsetZ ) {
    status = 1;
    return untransform(coneVertexIn, coneDirectionIn, GlobalPoint(0, 0, 0));
  }

  // Find the correct solution to our quadratic equation.
  double solution = solveQuadraticForPathLength(a, b, c, status);
  // If it is a good solution, find the corresponding point in space and then
  // transform back to the original coordinate system.
  if (status) {
    return untransform(coneVertexIn, coneDirectionIn,
                       propagateLine(lineOffset, lineDirection, solution));
  } else
    return GlobalPoint();
}

GlobalPoint pcaOfLineToCone(
    const GlobalPoint &lineOffsetIn, const GlobalVector &lineDirectionIn,
    const GlobalPoint &coneVertexIn, const GlobalVector &coneDirectionIn,
    double alpha /* cone angle */, int &status) {

  // Shift coordinates such that the cone vertex is at the origin.
  GlobalPoint lineOffset = transform(coneVertexIn, coneDirectionIn,
                                     lineOffsetIn);

  // Now rotate so the cone is aligned along Z
  GlobalVector lineDirection = transform(coneVertexIn, coneDirectionIn,
                                         lineDirectionIn);

  double trackDirX = lineDirection.x();
  double trackDirY = lineDirection.y();
  double trackDirZ = lineDirection.z();
  double trackOffsetX = lineOffset.x();
  double trackOffsetY = lineOffset.y();
  //double trackOffsetZ = lineOffset.z();

  // Get quadratic coefficients for the equation to solve.
  double a = -((Power(trackDirX,2) + Power(trackDirY,2))*
               (Power(trackDirX,2) + Power(trackDirY,2) - Power(trackDirZ,2) +
                (Power(trackDirX,2) + Power(trackDirY,2) +
                 Power(trackDirZ,2))*Cos(2*alpha))) /
      (2.*Power(trackDirZ,2));

  double b = -(((trackDirX*trackOffsetX + trackDirY*trackOffsetY)*
                (Power(trackDirX,2) + Power(trackDirY,2) - Power(trackDirZ,2) +
                 (Power(trackDirX,2) + Power(trackDirY,2) + Power(trackDirZ,2))
                 *Cos(2*alpha)))/Power(trackDirZ,2));

  double c = (-Power(trackDirX*trackOffsetX + trackDirY*trackOffsetY,2) + (Power(trackDirX,2)*Power(trackOffsetX,2) + 2*trackDirX*trackDirY*trackOffsetX*trackOffsetY +
        Power(trackDirY,2)*Power(trackOffsetY,2) + Power(trackDirZ,2)*(Power(trackOffsetX,2) + Power(trackOffsetY,2)))*Power(Sin(alpha),2))/Power(trackDirZ,2);

  // Find the correct solution to our quadratic equation.  This will give us the
  // t parameter that gives the point on the line closest to the
  // cone.
  double solution = solveQuadraticForPathLength(a, b, c, status);

  // Check if a solution exists
  if (!status)
    return GlobalPoint();

  GlobalPoint linePCA = propagateLine(lineOffset, lineDirection, solution);

  // Now find the point on the cone closest to this point.  Note that we've
  // already transformed our coordinates, we don't need to do it again.
  GlobalPoint conePCA = pcaOfConeToPoint(linePCA, GlobalPoint(0,0,0),
                                         GlobalVector(0, 0, 1), alpha, status);
  return untransform(coneVertexIn, coneDirectionIn, conePCA);
}

GlobalPoint pcaOfConeToPoint(
    const GlobalPoint& pointIn,
    const GlobalPoint &coneVertex, const GlobalVector &coneDirection,
    double alpha, int &status) {

  // Shift coordinates such that the cone vertex is at the origin.
  GlobalPoint point = transform(coneVertex, coneDirection, pointIn);

  // Now we need to find the point on the cone.  We do this by first finding the
  // z0 position of the apex of the inverted cone (with angle 90-alpha) that
  // contains our point.
  double z0 = point.z() +
      Sqrt(point.x()*point.x() + point.y()*point.y())*Tan(alpha);

  GlobalPoint z0point(0, 0, z0);

  // Construct a vector from the z0 point to the point.  The
  // intersection of this line to the cone is the PCA for the CONE.  This line
  // is by construction perpindicular to the cone at the intersection.
  GlobalVector displacementDirection = point - z0point;

  // Note that when we call this function, we have already transformed into a
  // coordinate system where the cone apex is at the origin and the cone
  // direction is along the z axis.
  GlobalPoint conePCA = intersectionOfLineAndCone(z0point,
                                                  displacementDirection,
                                                  GlobalPoint(0,0,0),
                                                  GlobalVector(0,0,1),
                                                  alpha, status);
  if (!status) {
    return GlobalPoint();
  }
  // Get back to our original coordinate system.
  return untransform(coneVertex, coneDirection,conePCA);
}

// Stupid type conversion
template<typename Out, typename In>
inline Out convert(const In& in) { return Out(in.x(), in.y(), in.z()); }

GlobalPoint transform(const GlobalPoint& newOrigin, const GlobalVector &newUz,
                      const GlobalPoint& toTransform) {
  // Shift origin
  GlobalPoint shifted = toTransform;
  shifted -= convert<GlobalVector>(newOrigin);
  // Rotate
  TRotation rotation;
  rotation.SetZAxis(convert<TVector3>(newUz).Unit());
  TVector3 rotated = rotation.Inverse()*convert<TVector3>(shifted);
  return convert<GlobalPoint>(rotated);
}

GlobalVector transform(const GlobalPoint& newOrigin, const GlobalVector &newUz,
                      const GlobalVector& toTransform) {
  // We can ignore the origin shift for vectors.
  TRotation rotation;
  rotation.SetZAxis(convert<TVector3>(newUz).Unit());
  TVector3 rotated = rotation.Inverse()*convert<TVector3>(toTransform);
  return convert<GlobalVector>(rotated);
}

GlobalPoint untransform(const GlobalPoint& newOrigin, const GlobalVector &newUz,
                      const GlobalPoint& toTransform) {
  // Rotate
  TRotation rotation;
  rotation.SetZAxis(convert<TVector3>(newUz).Unit());
  // Invert rotation.
  TVector3 unrotated = rotation*convert<TVector3>(toTransform);
  // Shift origin back
  GlobalPoint output = convert<GlobalPoint>(unrotated);
  output += convert<GlobalVector>(newOrigin);
  return output;
}

GlobalVector untransform(const GlobalPoint& newOrigin, const GlobalVector &newUz,
                         const GlobalVector& toTransform) {
  TRotation rotation;
  rotation.SetZAxis(convert<TVector3>(newUz).Unit());
  // Invert rotation.
  return convert<GlobalVector>(
      rotation*convert<TVector3>(toTransform));
}

}}  // end namespace SVfit::track
