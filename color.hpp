////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-14 13:48:23 by Eric Scrivner>
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

		inline Color operator * (const Real& fMult) {
			return Color(r * fMult,
			             g * fMult,
			             b * fMult);
		} 
  };
}

#endif // COLOR_HPP__
