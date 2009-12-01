////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-30 22:18:21 by Eric Scrivner>
//
// Description:
//   2D vector class.
////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR2_HPP__
#define VECTOR2_HPP__

#include "base.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Vector2
  //
  // Represents a 2-dimension vector
  class Vector2 {
  public:
    Real x, y;
  public:
    Vector2()
    { }

    Vector2(const Real& fX, const Real& fY)
      : x(fX), y(fY)
    { }
  };
}

#endif // VECTOR2_HPP__
