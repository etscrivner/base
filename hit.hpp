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
    Hit(const Real& fDistance,
        const Vector3& vNormal,
	Material* mat)
      : distance(fDistance), normal(vNormal), material(mat)
    { }

    Real distance;  // The distance from the origin to the hit
    Vector3 normal; // The surface normal
    Material* material;  // The material properties of the surface hit
  };
}

#endif // HIT_HPP__
