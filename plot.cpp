////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-29 15:04:18 by Eric Scrivner>
//
// Description:
//   Defines methods for plotting a single pixel on the screen at a given
// position and possibly color.
////////////////////////////////////////////////////////////////////////////////

#include "plot.hpp"

void Base::Plot(const int& x, const int& y, const Base::Color& color) {
  glBegin(GL_POINTS);
  glColor3f(color.r, color.g, color.b);
  glVertex2i(x, y);
  glEnd();
}

////////////////////////////////////////////////////////////////////////////////

void Base::Plot(const int& x, const int& y) {
  Plot(x, y, Color::White);
}
	
