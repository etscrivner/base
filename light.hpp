////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-04 19:50:27 by Eric Scrivner>
//
// Description:
//   Defines a simple point light source model
////////////////////////////////////////////////////////////////////////////////

#ifndef LIGHT_HPP__
#define LIGHT_HPP__

#include "color.hpp"
#include "vector4.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Light
  //
  // Models a simple directional light source
  class Light {
  public:
    Light()
    { }

    Light(const Color& col, const Vector3& dir)
      : color_(col), direction_(dir)
    { }

    void illuminationAt(const Vector3& pnt, Vector3& dir,
                        Color& col) {
      col = color_;
      dir = -1.0 * direction_;
    } 
  private:
    Color   color_;
    Vector3 direction_;
  };
}

#endif // LIGHT_HPP__
