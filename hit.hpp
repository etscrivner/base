////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-01 11:25:10 by Eric Scrivner>
//
// Description:
//   Class representing a ray hit on a surface.
////////////////////////////////////////////////////////////////////////////////

#ifndef HIT_HPP__
#define HIT_HPP__

#include "base.hpp"
#include "vector3.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Forward definitions
  class Material;

  //////////////////////////////////////////////////////////////////////////////
  // Class: Hit
  //
  // Represents a ray-surface intersection.
  class Hit {
  public:
    Hit(const Real& distance,
        const Vector3& normal,
	Material* material)
      : distance_(distance), normal_(normal), material_(material)
    { }

    Real getDistance() const { return distance_; }
    Vector3 getNormal() const { return normal_; }
    Material* getMaterial() const { return material_; }

    void setDistance(const Real& d) { distance_ = d; }
    void setNormal(const Vector3& n) { normal_ = n; }
    void setMaterial(Material* m) { material_ = m; }
  private:
    Real distance_;  // The distance from the origin to the hit
    Vector3 normal_; // The surface normal
    Material* material_;  // The material properties of the surface hit
  };
}

#endif // HIT_HPP__
