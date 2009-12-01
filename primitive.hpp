////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-01 12:22:03 by Eric Scrivner>
//
// Description:
//   Primitive shapes for ray-surface intersections
////////////////////////////////////////////////////////////////////////////////
#ifndef PRIMITIVE_HPP__
#define PRIMITIVE_HPP__

#include "hit.hpp"
#include "ray.hpp"
#include "vector3.hpp"

#include <memory>
#include <vector>

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
    Primitive(Material* mat)
      : material(mat)
    { }

    virtual ~Primitive()
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
    virtual bool intersection(const Ray& ray, Hit& hit) = 0;

    Material* material; // The material properties of the primitive
  };

  //////////////////////////////////////////////////////////////////////////////
  // Class: Group
  //
  // Represents a group of primitive objects
  class Group : public Primitive {
  public:
    Group()
      : Primitive(0)
    { }

    ~Group() {
      for (std::vector<Primitive*>::iterator it = primitives_.begin();
	   it != primitives_.end(); it++) {
	delete *it;;
      }
      primitives_.clear();
    }
    ////////////////////////////////////////////////////////////////////////////
    // Function: addPrimitive
    //
    // Adds a primitive to this primitive group
    void addPrimitive(Primitive* p) {
      primitives_.push_back(p);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: intersection
    //
    // Computes the closest intersecting primitive in this group
    bool intersection(const Ray& ray, Hit& hit) {
      bool didHit = false;

      for (size_t i = 0; i < primitives_.size(); i++) {
	if (primitives_[i]->intersection(ray, hit)) {
	  didHit = true;
	}
      }

      return didHit;
    }
  private:
    std::vector<Primitive*> primitives_; // The internal primitives
  };

  //////////////////////////////////////////////////////////////////////////////
  // Class: Sphere
  //
  // A sphere primitive which can be used to check for ray-sphere intersection
  class Sphere : public Primitive {
  public:
    Sphere(const Vector3& center,
           Real radius,
           Material* mat)
      : Primitive(mat), center_(center), radius_(radius)
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: intersection
    //
    // Computes the ray-sphere intersection returning true if an intersection
    // occurred or false otherwise.
    bool intersection(const Ray& ray, Hit& hit) {
      Vector3 co = center_ - ray.origin;
      Real rayCos = co.dotProduct(ray.direction);
      Real distance = -1;

      // If the angle is between 0 and 90 degrees
      if (rayCos >= 0) {
	// Compute the discriminant
	Real disc = pow(radius_, 2) - (co.dotProduct(co) - pow(rayCos, 2));

	// If the value is non-imaginary compute the distance
	distance = (disc < 0) ? 0 : rayCos - sqrt(disc);
      }

      // If the distance was positive and closer than the closest hit
      if (distance >= 0 && distance < hit.getDistance()) {
	// Compute the surface normal
	Vector3 normal = ray.positionAtTime(distance) - center_;

	// Fill in the hit information and indicate an intersection
	hit.setDistance(distance);
	hit.setNormal(normal.normalize());
	hit.setMaterial(material);

	return true;
      }

      return false;
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
             Material* mat)
      : Primitive(mat), v1_(v1), v2_(v2), v3_(v3)
    { }

    bool intersection(const Ray& ray, Hit& hit) {
      // TODO: Write ray-triangle intersection code
      return false;
    }
  private:
    Vector3 v1_, v2_, v3_; // The vertices of this triangle
  };
}

#endif // PRIMITIVE_HPP__
