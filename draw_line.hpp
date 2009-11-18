////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-15 14:10:33 by Eric Scrivner>
//
// Description:
//  Defines line drawing algorithms and one circle drawing algorithm
////////////////////////////////////////////////////////////////////////////////

#ifndef DRAW_LINE_HPP__
#define DRAW_LINE_HPP__

#include "base.hpp"

namespace Base {
  ////////////////////////////////////////////////////////////////////////////////
  // Function: DrawLineDDA
  //
  // Parameters:
  //   x1 - The x-coordinate of the first point
  //   y1 - The y-coordinate of the first point
  //   x2 - The x-coordinate of the second point
  //   y2 - The y-coordinate of the second point
  //
  // Plots a series of individual points which approximate the line from (x1, y1)
  // to (x2, y2) using the Digital Differential Analyzer (DDA) algorithm. This
  // algorithm eliminates the multiplication needed to compute the points on a
  // line using the slope-intercept equation y = mx + b.
  void DrawLineDDA(Real x1, Real y1, Real x2, Real y2);

  ////////////////////////////////////////////////////////////////////////////////
  // Function: DrawLineBresenham
  //
  // Parameters:
  //   x1 - The x-coordinate of the first point
  //   y1 - The y-coordinate of the first point
  //   x2 - The x-coordinate of the second point
  //   y2 - The y-coordinate of the second point
  //
  // Plots a series of individual points which approximate the line from (x1, y1)
  // to (x2, y2) using Bresenham's midpoint algorithm. This algorithm uses the
  // midpoint of the line to determine the next pixel to plot and eliminates
  // the rounding operation from DDA and all multiplications from other
  // algorithms.
  void DrawLineBresenham(Real x1, Real y1, Real x2, Real y2);

  ////////////////////////////////////////////////////////////////////////////////
  // Function: DrawCircleMidpoint
  //
  // Paramters:
  //   x_c - The x-coordinate of the circles center
  //   y_c - The y-coordinate of the circles center
  //   r   - The radius of the circle
  //
  // Uses the midpoint circle algorithm to plot a circle of radius r centered at
  // the position (x, y).
  void DrawCircleMidpoint(const Real& x_c, const Real& y_c, const Real& r);
}

#endif // DRAW_LINE_HPP__
