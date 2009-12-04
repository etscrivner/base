////////////////////////////////////////////////////////////////////////////////
// Base: A Computer Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-03 17:44:47 by Eric Scrivner>
//
// Description:
//   Class for tracing the path of rays and computing shading.
////////////////////////////////////////////////////////////////////////////////
#ifndef RAY_TRACER_HPP__
#define RAY_TRACER_HPP__

#include "color.hpp"
#include "hit.hpp"
#include "ray.hpp"
#include "scene.hpp"

#include <cstdio>

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: RayTracer
  //
  // Traces rays into a scene and computes the color of the light at a given
  // point in the scene. Based on MIT OCW design.
  class RayTracer {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Function: RayTracer
    //
    // Parameters:
    //   scene - The scene to be ray-traced.
    //   maxDepth - The maximum ray-trace recursion depth
    //   minWeight - The minimum weight of a ray contribution
    //
    // Initializes the ray-tracer with the given scene and depth.
    RayTracer(Scene* scene, int maxDepth, Real minWeight)
      : scene_(scene), maxDepth_(maxDepth), minWeight_(minWeight)
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: getScene
    //
    // Returns the scene being ray-traced
    Scene* getScene() const { return scene_; }

    ////////////////////////////////////////////////////////////////////////////
    // Function: traceRay
    //
    // Parameters:
    //   ray - The ray projected into the scene
    //   depth - The current recursion depth
    //   tmin - The epsilon on distance for hits
    //   weight - The current weight of the light ray
    //   indexOfRefraction - The current index of refraction
    //   hit - The hit information in regards to the ray being traced
    //
    // Traces the given ray into the scene given that it does not exceed the
    // maximum recursion depth.
    Color traceRay(Ray& ray, int depth, Real tmin, Real weight,
                   Real indexOfRefraction, Hit& hit) const {
      // If the current depth exceeds the maximum depth
      if (depth > maxDepth_ || fabs(weight - minWeight_) < 0.001) {
	// Return the background color
	return scene_->getBackgroundColor();
      }

      // Put the hit very far away initially
      hit.setDistance(RealLimits::infinity());

      // If there was an intersection with an object in the scene
      if (scene_->getPrimitives()->intersection(ray, hit, tmin)) {
	Color result = scene_->getAmbient() * hit.getMaterial()->diffuse;
	Vector3 lightDir;
	Color lightCol;

	// For each light in the scene
	for (size_t i = 0; i < scene_->numLights(); i++) {
	  // Compute the illumination of this light
	  Vector3 hitPoint = ray.positionAtTime(hit.getDistance());
	  scene_->getLight(i)->illuminationAt(hitPoint, lightDir, lightCol);

	  // If we're not in any shadows
	  if (!inShadow(hitPoint, lightDir, tmin)) {
	    // Add the contribution of this light to the final color
	    result += hit.getMaterial()->shade(ray, hit, lightDir, lightCol);
	  }

	  Ray nextRay(Vector3(0,0,0), Vector3(0,0,0));

	  // If the material is reflective
	  if (hit.getMaterial()->isReflective()) {
	    // Construct a new ray
	    nextRay.origin = hitPoint;
	    nextRay.direction = getReflectionDir(ray.direction, hit.getNormal());

	    // Recursively compute the color
	    Hit hit2;
	    result += hit.getMaterial()->reflection * traceRay(nextRay,
	                                                       depth + 1,
	                                                       tmin,
	                                                       weight * hit.getMaterial()->reflection.magnitude(),
	                                                       indexOfRefraction, hit2);
	  }

	  // If the material is transparent
	  if (hit.getMaterial()->isTransparent()) {
	    // Construct a new ray
	    nextRay.origin = hitPoint;
	    nextRay.direction = getRefractionDir(ray,
	                                         hit.getNormal(),
	                                         indexOfRefraction,
	                                         hit.getMaterial()->indexOfRefraction);

	    Real mag = Vector3(hit.getMaterial()->refraction.r,
	                       hit.getMaterial()->refraction.g,
	                       hit.getMaterial()->refraction.b).magnitude();
	    Hit hit3;
	    result += hit.getMaterial()->refraction * traceRay(nextRay,
	                                                       depth + 1,
	                                                       tmin,
	                                                       weight * mag,
	                                                       hit.getMaterial()->indexOfRefraction,
	                                                       hit3);
	  }
	}

	return weight * result;
      }

      return scene_->getBackgroundColor();
    }
  private:
    ////////////////////////////////////////////////////////////////////////////
    // Function: inShadow
    //
    // Indicates whether an object is in the shadow of another object given
    // a point of intersection and a direction to a light.
    bool inShadow(const Vector3& hitPoint, const Vector3& lightDir, Real tmin) const {
      // Set the nearest hit to infinitely far away
      Hit h;
      h.setDistance(RealLimits::infinity());

      // Determine whether or not an intersection occurred
      Vector3 hp = hitPoint;
      return scene_->getPrimitives()->intersection(Ray(hitPoint, lightDir), h, tmin);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: getReflectionDir
    //
    // Returns the direction of a ray's reflection given a direction and a 
    // surface normal.
    Vector3 getReflectionDir(const Vector3& rayDir, const Vector3& norm) const {
      // Perfect mirror reflection
      return rayDir - (2 * rayDir.dotProduct(norm)) * norm;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: getRefractionDir
    //
    // Returns the direction of the refracted ray the current ray, a surface
    // normal and the incident and material indices of refraction using Snell's
    // refraction law.
    Vector3 getRefractionDir(const Ray& ray, const Vector3& normal,
                             Real incidentRefraction, Real materialRefraction) const {
      // Use snells law to compute the index of refraction
      Real n_r = incidentRefraction / materialRefraction;

      // Compute the eye ray, add a small offset to avoid self-intersection
      Vector3 eyeRay = -ray.direction;
      eyeRay.x += 0.0001;
      eyeRay.y += 0.0001;
      eyeRay.z += 0.0001;

      // Compute the refracted ray direction
      Real cosIncident = eyeRay.dotProduct(normal);
      Real cosMaterial = (n_r * cosIncident);
      cosMaterial -= sqrt(1 - pow(n_r, 2) * (1 - pow(cosIncident, 2)));
      return (cosMaterial * normal) - (n_r * eyeRay);
    }

    Scene* scene_; // The scene to be ray-traced
    int maxDepth_; // The maximum recursive depth for tracing rays
    Real minWeight_; // The minimum weighting of a ray contribution
  };
}

#endif // RAY_TRACER_HPP__
