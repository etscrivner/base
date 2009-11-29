////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-29 14:37:04 by Eric Scrivner>
//
// Description:
//  Defines a class for representing and manipulating colors
////////////////////////////////////////////////////////////////////////////////

#include "color.hpp"

const Base::Color Base::Color::Black = Color(0.0F, 0.0F, 0.0F);
const Base::Color Base::Color::Red   = Color(1.0F, 0.0F, 0.0F);
const Base::Color Base::Color::Green = Color(0.0F, 1.0F, 0.0F);
const Base::Color Base::Color::Blue  = Color(0.0F, 0.0F, 1.0F);
const Base::Color Base::Color::White = Color(1.0F, 1.0F, 1.0F);

////////////////////////////////////////////////////////////////////////////////

Base::Byte Base::ColorToByte(Real color) {
  if (color > 1.0F) {
    color = 1.0F;
  } else if (color < 0.0F) {
    color = 0.0F;
  }

  return static_cast<Byte>(color * 255);
}
