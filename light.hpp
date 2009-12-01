////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-30 23:57:11 by Eric Scrivner>
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
  // Models a point light source with a position and color.
  class Light {
  public:
    Light()
    { }

    Light(const Color& col, const Vector4& pos)
      : color(col), position(pos)
    { }

    Color   color;
    Vector4 position;
  };
}

#endif // LIGHT_HPP__
