////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-03 17:46:35 by Eric Scrivner>
//
// Description:
//   Class for a 3x3 real matrix.
////////////////////////////////////////////////////////////////////////////////
#ifndef MATRIX33_HPP__
#define MATRIX33_HPP__

namespace Base {
	//////////////////////////////////////////////////////////////////////////////
	// Class: Matrix33
	//
	// Represents a 3x3 real matrix
	class Matrix33 {
	protected:
		union {
			Real m[3][3];
			Real _m[9];
		};
	public:
		inline Matrix33()
		{ }

		inline Matrix33(Real m00, Real m01, Real m02,
		                Real m10, Real m11, Real m12,
		                Real m20, Real m21, Real m22) {
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
		}

		inline Real* operator [] (size_t iRow) {
			assert(iRow < 3);
			return m[iRow];
		}

		inline const Real* const operator [] (size_t iRow) const {
			assert(iRow < 3);
			return m[iRow];
		}

		////////////////////////////////////////////////////////////////////////////
		// Function: determinant
		//
		// Returns the determinant of this 3x3 matrix.
		inline Real determinant() const {
			return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
			  m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) +
			  m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
		}
	};
}

#endif // MATRIX33_HPP__
