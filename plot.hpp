////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-17 23:27:40 by Eric Scrivner>
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
	// Paramters:
	//   xMin - The minimum x coordinate of the screen
	//   xMax - The maximum x coordinate of the screen
	//   yMin - The minimum y coordinate of the screen
	//   yMax - The maximum y coordinate of the screen
	//   pixelBuf - A list x by y array containing all the pixels (colors) to be
	//              display. A pixel at position pixelBuf[i][j] is rendered at
	//              pixel (xMin + i, yMin + j) on the screen
	//
	// Renders an entire pixel buffer to the frame buffer.
	void Plot(const int& xMin, const int& xMax,
	          const int& yMin, const int& yMax,
	          Color** pixelBuffer);

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
