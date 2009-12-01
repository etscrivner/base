////////////////////////////////////////////////////////////////////////////////
// Base: A Computer Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-30 23:27:16 by Eric Scrivner>
//
// Description:
//   Represents a mathematical vector with four components for a homogeneous
// three-dimensional coordinate system.
////////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR4_HPP__
#define VECTOR4_HPP__

#include <cmath>

#include "base.hpp"
#include "vector3.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Vector4
  //
  // A mathematical vector with four-coordinates to represent a homogenous
  // coordinate system vector. (Based on the Ogre3D Vector Classes)
  class Vector4 {
  public:
    Real x, y, z, w;
  public:
    inline Vector4()
    { }

    inline Vector4(const Real fX, const Real fY, const Real fZ, const Real fW)
      : x(fX), y(fY), z(fZ), w(fW)
    { }

    inline explicit Vector4(const Vector3& vec3)
      : x(vec3.x),
        y(vec3.y),
        z(vec3.z),
        w(1.0F)
    { }

    inline explicit Vector4(const Real afCoordinate[4])
      : x(afCoordinate[0]),
        y(afCoordinate[1]),
        z(afCoordinate[2]),
        w(afCoordinate[3])
    { }

    inline Vector4& operator = (const Vector4& rhs) {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
      w = rhs.w;
      return *this;
    }

    inline Vector4& operator = (const Vector3& rhs) {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
      w = 1.0F;
      return *this;
    }

    inline bool operator == (const Vector4& rhs) {
      return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
    }

    inline bool operator != (const Vector4& rhs) {
      return (x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w);
    }

    inline Vector4 operator - () const {
      return Vector4(-x, -y, -z, -w);
    }

    inline Vector4 operator + (const Vector4& rhs) {
      return Vector4(x + rhs.x,
                     y + rhs.y,
                     z + rhs.z,
                     w + rhs.w);
    }

    inline Vector4 operator - (const Vector4& rhs) {
      return Vector4(x - rhs.x,
                     y - rhs.y,
                     z - rhs.z,
                     w - rhs.w);
    }

    inline Vector4 operator * (const Vector4& rhs) {
      return Vector4(x * rhs.x,
                     y * rhs.y,
                     z * rhs.z,
                     w * rhs.w);
    }

    inline Vector4 operator * (const Real& fScalar) {
      return Vector4(x * fScalar,
                     y * fScalar,
                     z * fScalar,
                     w * fScalar);
    }

    inline Vector4 operator / (const Vector4& rhs) {
      return Vector4(x / rhs.x,
                     y / rhs.y,
                     z / rhs.z,
                     w / rhs.w);
    }
		
    inline friend Vector4 operator * (const Real fScalar, const Vector4& vec) {
      return Vector4(fScalar * vec.x,
                     fScalar * vec.y,
                     fScalar * vec.z,
                     fScalar * vec.w);
    }

    inline Vector4& operator *= (const Real& fScalar) {
      x *= fScalar;
      y *= fScalar;
      z *= fScalar;
      w *= fScalar;	
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: magnitude
    //
    // Computes the magnitude of this vector as sqrt(x^2 + y^2 + z^2 + w^2).
    inline Real magnitude() const {
      return sqrt(x*x + y*y + z*z + w*w);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: normalize
    //
    // Computes the normal of this vector such that its magnitude becomes 1,
    // this is done by taking each of the components of this vector and dividing
    // it by the magnitude.
    inline Vector4 normalize() const {
      Real mag = magnitude();
      if (mag == 0) {
	return Vector4(0, 0, 0, 0);
      } else {
	return Vector4(x / mag,
	               y / mag,
	               z / mag,
	               w / mag);
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: dotProduct
    //
    // Parameters:
    //   vec - Vector4 with which to calculate the dot product.
    //
    // Computes the dot (scalar) product of this vector with another, returning
    // a real value representing the dot product.
    inline Real dotProduct(const Vector4& vec) const {
      return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
    }
  };
}

#endif // VECTOR4_HPP__
