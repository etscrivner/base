////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-02 23:57:57 by Eric Scrivner>
//
// Description:
//   Class for maniuplating an image as an array of pixels
////////////////////////////////////////////////////////////////////////////////

#include "image.hpp"
#include "plot.hpp"

#include <fstream>
using namespace std;

void Base::Image::draw(const int& xMin, const int& yMin) {
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      Plot(xMin + x, yMin + y, pixelAt(x, y));
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

void Base::Image::saveAsTga(string fileName) {
  // If we were not given a filename
  if (fileName.length() == 0) {
    // Exit
    return;
  }

  // If the file does not have the proper extension
  if (fileName.substr(fileName.length() - 4, 4) != ".tga") {
    // Add the .tga extension
    fileName += ".tga";
  }

  // Attempt to open the file
  ofstream tgaOut(fileName.c_str());

  // If the file couldn't be opened
  assert(tgaOut.is_open());
  if (!tgaOut.is_open()) {
    // Probably don't have write access, so exit
    return;
  }

  tgaOut.put(0); // No image ID
  tgaOut.put(0); // No color map
  tgaOut.put(2); // Uncompressed, true color
	
  for (size_t i = 0; i < 5; i++) { // Empty color map
    tgaOut.put(0);
  }

  tgaOut.put(0); // X-Origin at 0
  tgaOut.put(0);
  tgaOut.put(0); // Y-Origin at 0
  tgaOut.put(0);
  tgaOut.put(width_ & 0xFF); // Width (Little Endian)
  tgaOut.put((width_ >> 8) & 0xFF);
  tgaOut.put(height_ & 0xFF); // Height (Little Endian)
  tgaOut.put((height_ >> 8) & 0xFF);
  tgaOut.put(24); // 24 bits-per-pixel
  tgaOut.put(0); // No alpha

  // Output all the pixel colors in the image
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      Color c = pixelAt(x, y);
      tgaOut.put(ColorToByte(c.b));
      tgaOut.put(ColorToByte(c.g));
      tgaOut.put(ColorToByte(c.r));
    }
  }

  tgaOut.close();
}
