////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-17 23:28:36 by Eric Scrivner>
//
// Description:
//   Defines methods for plotting a single pixel on the screen at a given
// position and possibly color.
////////////////////////////////////////////////////////////////////////////////

#include "plot.hpp"

void Base::Plot(const int& xMin, const int& xMax,
                const int& yMin, const int& yMax,
                Base::Color** pixelBuffer)
{
	size_t xPosMax = abs(xMax - xMin);
	size_t yPosMax = abs(yMax - yMin);

	glBegin(GL_POINTS);
	for (size_t x = 0; x < xPosMax; x++) {
		for (size_t y = 0; y < yPosMax; y++) {
			glColor3f(pixelBuffer[x][y].r,
			          pixelBuffer[x][y].g,
			          pixelBuffer[x][y].b);
			glVertex2i(xMin + x, yMin + y);
		}
	}
	glEnd();
}

////////////////////////////////////////////////////////////////////////////////

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
	
