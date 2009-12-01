////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-30 17:48:00 by Eric Scrivner>
//
// Description:
//   Class representing a ray to be traced
////////////////////////////////////////////////////////////////////////////////
#ifndef RAY_HPP__
#define RAY_HPP__

#include "base.hpp"
#include "vector3.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Ray
  //
  // Represents a single ray to be used in a ray-tracer
  struct Ray {
  public:
    Vector3 origin; // The starting point of the ray
    Vector3 direction; // The direction the ray will travel in

    Ray(const Vector3& o, const Vector3& d)
      : origin(o), direction(d)
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: positionAtTime
    //
    // Parameters:
    //   t - The parametric value for the position of the ray
    //
    // Returns the position of the ray at the given time (parametric value).
    Vector3 positionAtTime(const Real& t) { 
      return origin + t * direction;
    }
  };
}

#endif // RAY_HPP__
