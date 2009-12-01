////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-30 22:10:13 by Eric Scrivner>
//
// Description:
//   3D vector class.
////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR3_HPP__
#define VECTOR3_HPP__

#include "base.hpp"
#include "vector2.hpp"

#include <cmath>

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Vector3
  //
  // Represents a 3-dimensional vector
  class Vector3 {
  public:
    double x, y, z;
  public:
    Vector3()
    { }

    Vector3(const Vector2& v)
      : x(v.x), y(v.y), z(0)
    { }

    Vector3(const double& fX, const double& fY, const double& fZ)
      : x(fX), y(fY), z(fZ)
    { }

    inline Vector3 operator - () const {
      return Vector3(-x, -y, -z);
    }

    inline Vector3 operator + (const Vector3& rhs) const {
      return Vector3(x + rhs.x,
                     y + rhs.y,
                     z + rhs.z);
    }

    inline Vector3& operator += (const Vector3& rhs) {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;

      return *this;
    }

    inline Vector3 operator - (const Vector3& rhs) const {
      return Vector3(x - rhs.x,
                     y - rhs.y,
                     z - rhs.z);
    }

    inline Vector3& operator -= (const Vector3& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;
			
      return *this;
    }

    inline Vector3 operator * (const Real& fScalar) const {
      return Vector3(x * fScalar,
                     y * fScalar,
                     z * fScalar);
    }

    inline friend Vector3 operator * (const Real& fScalar, const Vector3& v) {
      return Vector3(v.x * fScalar,
                     v.y * fScalar,
                     v.z * fScalar);
    }

    inline  Vector3 operator / (const Real& fScalar) {
      return Vector3(x / fScalar,
                     y / fScalar,
                     z / fScalar);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: magnitude
    //
    // Computes the magnitude of the vector as sqrt(x^2 + y^2 + z^2).
    inline Real magnitude() const {
      return sqrt(x*x + y*y + z*z);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: normalize
    //
    // Converts this vector to a unit vector
    inline Vector3 normalize() const {
      Real mag = magnitude();
      if (mag == 0) {
	return Vector3(0, 0, 0);
      } else {
	return Vector3(x / mag,
	               y / mag,
	               z / mag);
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: dotProduct
    //
    // Returns the dot (scalar) product of this vector with another
    inline Real dotProduct(const Vector3& rhs) {
      return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: crossProduct
    //
    // Returns the cross (vector) product of this vector with another
    inline Vector3 crossProduct(const Vector3& rhs) {
      return Vector3(y * rhs.z - z * rhs.y,
                     z * rhs.x - x * rhs.z,
                     x * rhs.y - y * rhs.x);
    }
  };
}

#endif // VECTOR3_HPP__
