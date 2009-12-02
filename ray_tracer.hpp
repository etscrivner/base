////////////////////////////////////////////////////////////////////////////////
// Base: A Computer Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-02 12:35:48 by Eric Scrivner>
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
    //
    // Initializes the ray-tracer with the given scene and depth.
    RayTracer(Scene* scene, int maxDepth)
      : scene_(scene), maxDepth_(maxDepth)
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
    //   hit - The hit information in regards to the ray being traced
    //
    // Traces the given ray into the scene given that it does not exceed the
    // maximum recursion depth.
    Color traceRay(Ray& ray, int depth, Hit& hit) const {
      // If the current depth exceeds the maximum depth
      if (depth > maxDepth_) {
	// Return the background color
	return scene_->getBackgroundColor();
      }

      // Put the hit very far away initially
      hit.setDistance(RealLimits::infinity());

      // If there was an intersection with an object in the scene
      if (scene_->getPrimitives()->intersection(ray, hit)) {
	Color result = Color::Black;
	Vector3 lightDir;
	Color lightCol;

	// For each light in the scene
	for (size_t i = 0; i < scene_->numLights(); i++) {
	  // Compute the illumination of this light
	  Vector3 hitPoint = ray.positionAtTime(hit.getDistance());
	  scene_->getLight(i)->illuminationAt(hitPoint, lightDir, lightCol);

	  // If the ray to the light hits any objects
	  Hit tmp;
	  tmp.setDistance(RealLimits::infinity());
	  if (scene_->getPrimitives()->intersection(Ray(hitPoint, lightDir), tmp)) {
	    // We're in the shadow so return black
	    return Color::Black;
	  }

	  // Add the contribution of this light to the final color
	  result += hit.getMaterial()->shade(ray, hit, lightDir, lightCol);
	}

	return result;
      }

      return scene_->getBackgroundColor();
    }
  private:
    Scene* scene_; // The scene to be ray-traced
    int maxDepth_; // The maximum recursive depth for tracing rays
  };
}

#endif // RAY_TRACER_HPP__
