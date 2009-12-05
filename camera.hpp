////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-04 23:10:24 by Eric Scrivner>
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
  class OrthographicCamera : public Camera {
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
      : center_(center),
        direction_(direction.normalize()), 
        up_(up.normalize()),
        horizontal_(up_.crossProduct(direction_).normalize()),
        size_(size)        
    {
      // Form an orthonormal basis with the up vector
      up_ = direction_.crossProduct(horizontal_).normalize();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: generateRay
    //
    // Parameters:
    //   point - The point from which to cast the ray (should be on [0, 1]).
    //
    // Returns a ray traveling from point into the scene
    Ray generateRay(const Vector2& point) {
      Vector3 origin = center_;
      origin += (point.x - 0.5) * size_ * horizontal_;
      origin += (point.y - 0.5) * size_ * up_;
      return Ray(origin, direction_);
    }
  private:
    Vector3 center_;
    Vector3 direction_;
    Vector3 up_;
    Vector3 horizontal_;
    Real size_;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Class: PerspectiveCamera
  //
  // A camera which converges towards a single point creating a perspective
  // appearance.
  class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera(Vector3 center,
                      Vector3 direction,
                      Vector3 up,
                      int height,
                      Real aspect,
                      Real angle)
      : center_(center),
        direction_(direction.normalize()),
        horizontal_(up.crossProduct(direction_).normalize()),
        up_(direction_.crossProduct(horizontal_).normalize()),
        angle_(angle * 3.14159 / 180)
    {
      horizontal_ = 2 * aspect *  horizontal_ * tan(angle_ / 2);
      up_ = 2 * up_ * tan(angle_ / 2);
    }

    Ray generateRay(const Vector2& point) {
      Vector3 dir = direction_;
      dir += (point.x - 0.5) * horizontal_;
      dir += (point.y - 0.5) * up_;
      return Ray(center_, dir.normalize());
    }
  private:
    Vector3 center_;
    Vector3 direction_;
    Vector3 horizontal_;
    Vector3 up_;
    Real angle_;
    Real height_;
  };
}

#endif // CAMERA_HPP__
