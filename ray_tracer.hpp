////////////////////////////////////////////////////////////////////////////////
// Base: A Computer Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-01 11:31:25 by Eric Scrivner>
//
// Description:
//   Class for tracing the path of rays and computing shading.
////////////////////////////////////////////////////////////////////////////////
#ifndef RAY_TRACER_HPP__
#define RAY_TRACER_HPP__

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: RayTracer
  //
  // Traces rays into a scene and computes the color of the light at a given
  // point in the scene.
  class RayTracer {
  public:
  private:
    int maxDepth_; // The maximum recursive depth for tracing rays
  };
}

#endif // RAY_TRACER_HPP__
