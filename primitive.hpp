////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-03 00:47:37 by Eric Scrivner>
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
    //   tmin - The smallest distance value which constitutes an intersection
    //
    // Returns true if an intersection between the given ray and this primitive
    // occurs and hit is filled with the information regarding the hit. False
    // otherwise.
    virtual bool intersection(const Ray& ray, Hit& hit, Real tmin) = 0;

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
	delete *it;
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
    bool intersection(const Ray& ray, Hit& hit, Real tmin) {
      bool didHit = false;

      for (size_t i = 0; i < primitives_.size(); i++) {
	if (primitives_[i]->intersection(ray, hit, tmin)) {
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
    bool intersection(const Ray& ray, Hit& hit, Real tmin) {
      Vector3 co = center_ - ray.origin;
      Real rayCos = co.dotProduct(ray.direction);
      Real distance = -1;
      
      // Since this gives us the distance of the closest point from the sphere,
      // if this value is less than zero then we can detect a non-intersection
      // early.
      if (rayCos < 0) {
	return false;
      }

      // Compute the discriminant
      Real discTmp = (co - (co.dotProduct(ray.direction) * ray.direction)).magnitude();
      Real disc = pow(radius_, 2) - pow(discTmp, 2);
      
      // Now we must ensure that we have two real solutions to this equation.
      // If the discriminant is less than zero we know we have two imagniary
      // solutions, and if it is exactly zero then we have the degenerate
      // case of a ray tangent to the sphere. Due to floating point rounding
      // errors we must ensure that the discriminant is greater than some
      // epsilon value in order to catch the degenerate case.
      if (disc > 0.0001) {
	// Now we can compute the solutions, however we must still check for
	// the case of a ray originating inside a sphere. To do this we check
	// for one negative and one positive solution, in this case we take the
	// positive solution, otherwise we take the minimum of the two solutions
	if (rayCos - sqrt(disc) < 0) {
	  distance = rayCos + sqrt(disc);
	} else {
	  distance = min(rayCos + sqrt(disc), rayCos - sqrt(disc));
	}

	// If the distance was positive and closer than the closest hit
	if (distance >= tmin && distance < hit.getDistance()) {
	  // Compute the surface normal
	  Vector3 normal = ray.positionAtTime(distance) - center_;
	  
	  // Fill in the hit information and indicate an intersection
	  hit.setDistance(distance);
	  hit.setNormal(normal.normalize());
	  hit.setMaterial(material);

	  return true;
	}
      }

      return false;
    }
  private:
    Vector3 center_;
    Real    radius_;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Class: Plane
  //
  // A plane primitive which can be used to check for ray-plane intersection
  class Plane : public Primitive {
  public:
    Plane(const Vector3& normal, Real offset, Material* mat)
      : Primitive(mat), normal_(normal), offset_(offset)
    { }

    bool intersection(const Ray& ray, Hit& hit, Real tmin) {
      // Ensure that the ray and plane are not parallel
      Real vd = normal_.dotProduct(ray.direction);

      if (fabs(vd) > 0.0001) {
	// Compute the distance
	Real v0 = normal_.dotProduct(ray.origin) + offset_;
	Real distance = -(v0 / vd);

	// Return the intersection hit
	if (distance >= tmin && distance < hit.getDistance()) {
	  if (vd >= 0.0) {
	    hit.setNormal(-normal_);
	  } else {
	    hit.setNormal(normal_);
	  }
	  hit.setDistance(distance);
	  hit.setMaterial(material);

	  return true;
	}
      }

      return false;
    }
  private:
    Vector3 normal_; // The normal of the plane
    Real offset_; // The offset from the origin
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

    bool intersection(const Ray& ray, Hit& hit, Real tmin) {
      
      return false;
    }
  private:
    Vector3 v1_, v2_, v3_; // The vertices of this triangle
  };
}

#endif // PRIMITIVE_HPP__
