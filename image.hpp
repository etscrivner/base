////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-02 01:26:32 by Eric Scrivner>
//
// Description:
//   Class for maniuplating an image as an array of pixels
////////////////////////////////////////////////////////////////////////////////

#ifndef IMAGE_HPP__
#define IMAGE_HPP__

#include "base.hpp"
#include "color.hpp"

#include <string>

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Image
  //
  // Represents an image as an array of colored pixels and allows for saving
  // the image into the TGA file format (not copy or exception safe).
  class Image {
  public:
    Image(const int& w, const int& h)
      : width_(w), height_(h), data_(new Color[width_ * height_])
    { }

    ~Image() {
      delete [] data_;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: width
    //
    // Returns the width of the image in pixels
    const size_t width() const { return width_; }

    ////////////////////////////////////////////////////////////////////////////
    // Function: height
    //
    // Returns the height of the image in pixels
    const size_t height() const { return height_; }

    ////////////////////////////////////////////////////////////////////////////
    // Function: pixelAt
    //
    // Parameters:
    //   x - The x coordinate (should be positive)
    //   y - The y coordinate (should be positive)
    //
    // Returns the color of the pixel at the given coordinates
    const Color pixelAt(const int& x, const int& y) {
      assert(x >= 0 && x < width_);
      assert(y >= 0 && y < height_);
      return data_[y * width_ + x];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: fill
    //
    // Sets all the pixels in the image to the given color
    void fill(const Color& color) {
      for (int i = 0; i < width_ * height_; i++) {
	data_[i] = color;
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: setPixel
    //
    // Sets the pixel at the given position to the given color
    void setPixel(const int& x, const int& y, const Color& color) {
      assert(x >= 0 && x < width_);
      assert(y >= 0 && y < height_);
      data_[y * width_ + x] = color;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: draw
    // 
    // Draws the image onto the screen starting at position (xMin, yMin).
    void draw(const int& xMin, const int& yMin);

    ////////////////////////////////////////////////////////////////////////////
    // Function: saveAsTga
    //
    // Parameters:
    //   fileName - The name of the file to which the image will be saved
    //
    // Saves this image to a file in Truevision-TGA format.
    void saveAsTga(std::string fileName);
  private:
    int width_; // The width of the image
    int height_; // The height of the image
    Color* data_; // The image data itself
  };
}

#endif // IMAGE_HPP__
