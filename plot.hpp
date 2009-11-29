////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-29 15:00:03 by Eric Scrivner>
//
// Description:
//   Defines methods for plotting a single pixel on the screen at a given
// position and possibly color.
////////////////////////////////////////////////////////////////////////////////

#ifndef PLOT_HPP__
#define PLOT_HPP__

#include "color.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Function: Plot
  //
  // Parameters:
  //   x - The x coordinate of the point to be plotted
  //   y - The y coordinate of the point to be plotted
  //   color - The color of the point to be plotted
  //
  // Plots a point of the given color at the given coordinates on the screen
  void Plot(const int& x, const int& y, const Color& color);

  //////////////////////////////////////////////////////////////////////////////
  // Function: Plot
  //
  // Paramters:
  //   x - The x coordinate of the point to be plotted
  //   y - The y coordinate of the point to be plotted
  //
  // Plots a single point at the given coordinates on the screen
  void Plot(const int& x, const int& y);
}

#endif // PLOT_HPP__
