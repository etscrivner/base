#ifndef PRIMITIVE_HPP__
#define PRIMITIVE_HPP__

#include "hit.hpp"
#include "ray.hpp"
#include "vector3.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Forward definitions
  class Material;

  //////////////////////////////////////////////////////////////////////////////
  // Class: Primitive
  //
  // Represents a primitive to be rendered by a ray-tracer and checked for
  // ray-surface intersections.
  class Primitive {
  public:
    Primitive(const Material& mat)
      : material(mat)
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: intersections
    //
    // Parameters:
    //   ray - The ray to be checked for intersection
    //   hit - The hit if an intersection is found
    //
    // Returns true if an intersection between the given ray and this primitive
    // occurs and hit is filled with the information regarding the hit. False
    // otherwise.
    virtual bool intersection(const Ray& ray, const Hit& hit) = 0;

    Material material; // The material properties of the primitive
  };

  //////////////////////////////////////////////////////////////////////////////
  // Class: Sphere
  //
  // A sphere primitive which can be used to check for ray-sphere intersection
  class Sphere : public Primitive {
  public:
    Sphere(const Vector3& center,
           Real radius,
           const Material& mat)
      : Primitive(mat), center_(center), radius_(radius)
    { }

    bool intersection(const Ray& ray, const Hit& hit) {
      // TODO: Write ray-sphere intersection code
    }
  private:
    Vector3 center_;
    Real    radius_;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Class: Triangle
  //
  // A triangle primitive which can be used to check for ray-triangle
  // intersection.
  class Triangle : public Primitive {
  public:
    Triangle(const Vector3& v1,
             const Vector3& v2,
             const Vector3& v3,
             const Material& mat)
      : Primitive(mat), v1_(v1), v2_(v2), v3_(v3)
    { }

    bool intersection(const Ray& ray, const Hit& hit) {
      // TODO: Write ray-triangle intersection code
    }
  private:
    Vector3 v1_, v2_, v3; // The vertices of this triangle
  };
}

#endif // PRIMITIVE_HPP__
