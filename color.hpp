////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-17 23:44:12 by Eric Scrivner>
//
// Description:
//   Defines a class for representing and manipulating colors
////////////////////////////////////////////////////////////////////////////////

#ifndef COLOR_HPP__
#define COLOR_HPP__

#include "base.hpp"

namespace Base {
  ////////////////////////////////////////////////////////////////////////////////
  // Class: Color
  //
  // Represents a color as different ratios of red, green and blue color
  // components.
  class Color {
  public:
    Real r, g, b; // The red, green and blue color components
  public:
		////////////////////////////////////////////////////////////////////////////
		// Standard Colors

		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color White;

    Color()
		  : r(1.0F), g(1.0F), b(1.0F)
    { }

		Color(const Color& copy)
			: r(copy.r), g(copy.g), b(copy.b)
		{ }

    Color(const Real& red, const Real& green, const Real& blue)
      : r(red), g(green), b(blue)
    { }

		Color& operator = (const Color& rhs) {
			r = rhs.r;
			g = rhs.g;
			b = rhs.b;
			return *this;
		}

		inline Color operator + (const Color& rhs) {
			return Color(r + rhs.r,
			             g + rhs.g,
			             b + rhs.b);
		}

		inline Color operator + (const Real& fAdd) {
			return Color(r + fAdd,
			             g + fAdd,
			             b + fAdd);
		}

		inline Color operator - (const Color& rhs) {
			return Color(r - rhs.r,
			             g - rhs.g,
			             b - rhs.b);
		}

		inline Color operator - (const Real& fSub) {
			return Color(r - fSub,
			             g - fSub,
			             b - fSub);
		}

		inline Color operator * (const Color& rhs) {
			return Color(r * rhs.r,
			             g * rhs.g,
			             b * rhs.b);
		}

		inline friend Color operator * (const Real& fMult, const Color& rhs) {
			return Color(fMult * rhs.r,
			             fMult * rhs.g,
			             fMult * rhs.b);
		}

		inline Color operator * (const Real& fMult) {
			return Color(r * fMult,
			             g * fMult,
			             b * fMult);
		}
		
		inline Color operator / (const Color& rhs) {
			return Color(r / rhs.r,
			             g / rhs.g,
			             b / rhs.b);
		}

		inline Color operator / (const Real& fDenom) {
			return Color(r / fDenom,
			             g / fDenom,
			             b / fDenom);
		}
  };
}

#endif // COLOR_HPP__
