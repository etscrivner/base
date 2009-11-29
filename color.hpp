////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-29 14:37:12 by Eric Scrivner>
//
// Description:
//   Defines a class for representing and manipulating colors
////////////////////////////////////////////////////////////////////////////////

#ifndef COLOR_HPP__
#define COLOR_HPP__

#include <cmath>

#include "base.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Function: ColorToByte
  //
  // Converts a real-valued color component into the range [0, 255].
  Byte ColorToByte(Real color);

  //////////////////////////////////////////////////////////////////////////////
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

    Color operator - () const {
      return Color(-r, -g, -b);
    }

    Color operator * (const Real& fScalar) const {
      return Color(r * fScalar,
                   g * fScalar,
                   b * fScalar);
    }

    friend Color operator * (const Real& fScalar, const Color& color) {
      return Color(color.r * fScalar,
                   color.g * fScalar,
                   color.b * fScalar);
    }

    Color operator / (const Real& fScalar) {
      return Color(r / fScalar,
                   g / fScalar,
                   b / fScalar);
    }

    Color operator + (const Color& rhs) {
      return Color(r + rhs.r,
                   g + rhs.g,
                   b + rhs.b);
    }

    Color operator - (const Color& rhs) {
      return Color(r - rhs.r,
                   g - rhs.g,
                   b - rhs.b);
    }

    Color operator * (const Color& rhs) {
      return Color(r * rhs.r,
                   g * rhs.g,
                   b * rhs.b);
    }

    Color operator / (const Color& rhs) {
      return Color(r / rhs.r,
                   g / rhs.g,
                   b / rhs.b);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: gammaCorrect
    //
    // Performs gamma (brightness) correction by raising each internal color
    // component to the power (1 / gamma).
    inline Color gammaCorrect(const double& gamma) {
      return Color(pow(r, 1 / gamma),
                   pow(g, 1 / gamma),
                   pow(b, 1 / gamma));
    }
  };
}

#endif // COLOR_HPP__
