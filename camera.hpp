////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-30 23:24:03 by Eric Scrivner>
//
// Description:
//   Contains camera for use in the ray tracer.
////////////////////////////////////////////////////////////////////////////////
#ifndef CAMERA_HPP__
#define CAMERA_HPP__

#include "ray.hpp"
#include "vector2.hpp"
#include "vector3.hpp"

namespace Base {
  
  //////////////////////////////////////////////////////////////////////////////
  // Class: Camera
  //
  // Abstract base class for all cameras
  class Camera {
  public:
    virtual ~Camera()
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: generateRay
    //
    // Parameters:
    //   point - The origin point of the ray (should be on [0, 1]).
    //
    // Returns a ray traveling from the given point into the scene in an
    // appropriately chosen direction.
    virtual Ray generateRay(const Vector2& point) = 0;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Class: OrthographicCamera
  //
  // An orthographic camera which projects rays into the scene along a constant
  // direction and varying origin.
  class OrthographicCamera {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Function: OrthographicCamera
    //
    // Parameters:
    //   center - The center point of the screen
    //   direction - The projection direction for the ray
    //   up - A vector representing the upward direction
    //   size - The size of the screen (assumes a square screen)
    //
    // Initializes this orthographic camera by using the up and direction
    // vector to compute a horizontal vector which is then used in the ray
    // generation process.
    OrthographicCamera(Vector3 center, Vector3 direction,
                       Vector3 up, Real size)
      : center_(center.normalize()),
        direction_(direction.normalize()), 
        up_(up.normalize()),
        horizontal_(direction_.crossProduct(up_)),
        size_(size)        
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: generateRay
    //
    // Parameters:
    //   point - The point from which to cast the ray (should be on [0, 1]).
    //
    // Returns a ray traveling from point into the scene
    Ray generateRay(const Vector2& point) {
      Vector3 origin = center_;
      origin += size_ * (point.x - 0.5) * horizontal_;
      origin += size_ * (point.y - 0.5) * up_;
      return Ray(origin, direction_);
    }
  private:
    Vector3 center_;
    Vector3 direction_;
    Vector3 up_;
    Vector3 horizontal_;
    Real size_;
  };
}

#endif // CAMERA_HPP__
