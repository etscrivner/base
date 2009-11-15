////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-14 11:25:51 by Eric Scrivner>
//
// Description:
//  Defines line drawing algorithms and one circle drawing algorithm.
////////////////////////////////////////////////////////////////////////////////

#include "plot.hpp"
#include "draw_line.hpp"

void Base::DrawLineDDA(Real x1, Real y1, Real x2, Real y2) {
  // First we compute the change in the x and y directions as the difference
  // between the given x and y coordinates.
  Real dx = x2 - x1;
  Real dy = y2 - y1;
  Real x  = x1;
  Real y  = y1;

  // If the coordinates change more rapidly in the x direction than in the y
  // direction.
  unsigned int steps = 0;

  if (fabs(dx) > fabs(dy)) {
    // Then change at unit intervals in the x direction
    steps = static_cast<int>(fabs(dx));
  } else {
    // Otherwise, change at unit intervals in the y direction
    steps = static_cast<int>(fabs(dy));
  }

  // Now we determine the increments in the x and y directions by dividing
  // the change in the corresponding direction by the number of steps the
  // line will be divided into. Notice that whichever direction is changing
  // at unit intervals will have an increment of 1. For example if steps = dx
  // then xIncrement = dx / steps = dx / dx = 1.
  Real xIncrement = dx / steps;
  Real yIncrement = dy / steps;

  // Plot successive pixels onto the screen until the line is completely
  // drawn.
  for (unsigned int k = 0; k < steps; k++) {
    Plot(round(x), round(y));
    x += xIncrement;
    y += yIncrement;
  }
}

////////////////////////////////////////////////////////////////////////////////

void Base::DrawLineBresenham(Real x1, Real y1, Real x2, Real y2) {
  // Determine whether or not the line is steep (e.g. has a slope > 1.0)
  bool steep = fabs(y2 - y1) > fabs(x2 - x1);
	
  // If the line is steep then the x and y values should be swapped
  if (steep) {
    swap(x1, y1);
    swap(x2, y2);
  }

  // If the x coordinates are decreasing then swap the starting x coordinates
  // and then swap the y coordinates.
  if (x1 > x2) {
    swap(x2, x1);
    swap(y2, y1);
  }

  // Initialize our line plotting variables
  int	dx    = x2 - x1;
  int	dy    = fabs(y2 - y1);
  int	error = dx / 2;
  int	ystep = -1;
  int	y     = y1;
  int   x     = x1;

  // If the y coordinates are increasing then the ystep is one otherwise it
  // is negative one
  if (y1 < y2) {
    ystep = 1;
  }

  // While we haven't reached the final x coordinate
  while (x < x2) {
    // If the line was steep then we have swapped the y and x coordinates
    if (steep) {
      Plot(y, x);
    } else {
      // Otherwise plot normally
      Plot(x, y);
    }

    // Update the error term
    error -= dy;

    // If the error term is negative step in the y direction
    if (error < 0) {
      y++;
      error += dx;
    }

    // Update the x coordinate
    x++;
  }
}

////////////////////////////////////////////////////////////////////////////////

void Base::DrawCircleMidpoint(const Real& x_c, const Real& y_c, const Real& r) {
  // Determine the initial coordinates and plot the first point
  int  x = 0;
  int  y = static_cast<int>(r);
  Real p = 1.25 - r; // The decision parameter

  // Now advance until x and y are equal
  while (x < y) {
    // Plot a single point in each octant of the circle, and shift each
    // point around the true center of the circle at (x_c, y_c).
    Plot(x + x_c, y + y_c);
    Plot(y + x_c, x + y_c);
    Plot(-y + x_c, x + y_c);
    Plot(-x + x_c, y + y_c);
    Plot(-x + x_c, -y + y_c);
    Plot(-y + x_c, -x + y_c);
    Plot(y + x_c, -x + y_c);
    Plot(x + x_c, -y + y_c);

    // Now determine the decision paramter at the next step based on its
    // previous value. If the decision parameter was less than zero then
    // the previously plotted point was inside the circle and the y coordinate
    // need not change. If, however, the decision parameter is greater than
    // zero our previously plotted point was outside the circle and thus we
    // should reduce y to compensate. If the previous decision parameter was
    // equal to zero then we were exactly on the circle and any choice we make
    // to modify y is equally accurate for plotting the next point.
    if (p <= 0) {
      p = p + (2 * x + 2) + 1;
      x++;
    } else {
      p = p + (2 * x + 2) + 1 - (2 * y - 2);
      x++;
      y--;
    }
  }
}
