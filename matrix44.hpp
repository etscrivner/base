////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-04 16:42:25 by Eric Scrivner>
//
// Description:
//   Class for a 4x4 homogeneous matrix and its corresponding operations.
////////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX44_HPP__
#define MATRIX44_HPP__

#include <cassert>
#include <cmath>

#include "base.hpp"
#include "vector4.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Matrix44
  //
  // Represents a standard 4x4 homogeneous matrix
  class Matrix44 {
  protected:
    // The matrix entries, indexed by [row][col]
    union {
      Real m[4][4];
      Real _m[16];
    };
  public:
    inline Matrix44()
    { }
		
    ////////////////////////////////////////////////////////////////////////////
    // Function: Matrix44
    //
    // Initializes a 4x4 matrix from the given parameters as follows:
    //
    // [m00 m01 m02 m03]
    // [m10 m11 m12 m13]
    // [m20 m21 m22 m23]
    // [m30 m31 m32 m33]
    inline Matrix44(Real m00, Real m01, Real m02, Real m03,
                    Real m10, Real m11, Real m12, Real m13,
                    Real m20, Real m21, Real m22, Real m23,
                    Real m30, Real m31, Real m32, Real m33)	{
      m[0][0] = m00;
      m[0][1] = m01;
      m[0][2] = m02;
      m[0][3] = m03;
      m[1][0] = m10;
      m[1][1] = m11;
      m[1][2] = m12;
      m[1][3] = m13;
      m[2][0] = m20;
      m[2][1] = m21;
      m[2][2] = m22;
      m[2][3] = m23;
      m[3][0] = m30;
      m[3][1] = m31;
      m[3][2] = m32;
      m[3][3] = m33;
    }

    inline Real* operator [] (size_t iRow) {
      assert(iRow < 4);
      return m[iRow];
    }

    inline const Real* const operator [] (size_t iRow) const {
      assert(iRow < 4);
      return m[iRow];
    }

    inline Vector4 operator * (const Vector4& v) const {
      return Vector4(
		     m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
		     m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
		     m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
		     m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: transpose
    //
    // Computes the transpose of the current matrix (interchanges rows and
    // columns).
    inline Matrix44 transpose() const {
      return Matrix44(m[0][0], m[1][0], m[2][0], m[3][0],
                      m[0][1], m[1][1], m[2][1], m[3][1],
                      m[0][2], m[1][2], m[2][2], m[3][2],
                      m[0][3], m[1][3], m[2][3], m[3][3]);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: makeScale
    //
    // Converts this matrix to a scaling matrix with the given scaling factors
    inline void makeScale(const Real& sx, const Real& sy, const Real& sz) {
      m[0][0] = sx; m[0][1] =  0; m[0][2] =  0; m[0][3] = 0;
      m[1][0] =  0; m[1][1] = sy; m[1][2] =  0; m[1][3] = 0;
      m[2][0] =  0; m[2][1] =  0; m[2][2] = sz; m[2][3] = 0;
      m[3][0] =  0; m[3][1] =  0; m[3][2] =  0; m[3][3] = 1;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: makeTranslate
    //
    // Converts this matrix to a translation matrix with the given displacements
    inline void makeTranslate(const Real& dx, const Real& dy, const Real& dz) {
      m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = dx;
      m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = dy;
      m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = dz;
      m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: makeRot
    //
    // Parameters:
    //   theta - The angle (in radians) to rotate about
    //
    // Performs a rotation about the z-axis through the angle theta.
    inline void makeRot(const Real& theta) {
      m[0][0] = cos(theta); m[0][1] = -sin(theta); m[0][2] = 0;
      m[1][0] = sin(theta); m[1][1] = cos(theta); m[1][2] = 0;
      m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
    }
  };
}

#endif // MATRIX44_HPP__
