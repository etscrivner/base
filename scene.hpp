////////////////////////////////////////////////////////////////////////////////
// Base: A Computer Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-01 12:23:08 by Eric Scrivner>
//
// Description:
//   Class for managing a scene which is to be ray-traced.
////////////////////////////////////////////////////////////////////////////////

#ifndef SCENE_HPP__
#define SCENE_HPP__

#include "base.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "primitive.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Scene
  //
  // Encapsulates information about a scene which is to be ray-traced.
  class Scene {
  public:
    Scene(Camera* camera)
      : camera_(camera)
    { }

    ~Scene() {
      if (camera_ != 0) {
	delete camera_;
      }

      if (primitives_ != 0) {
	delete primitives_;
      }

      for (LightSetT::iterator it = lights_.begin();
	   it != lights_.end(); it++) {
	delete *it;
      }
      lights_.clear();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: addLight
    //
    // Adds the given light to this scene
    addLight(const Light* light) {
      lights_.push_back(light);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: setCamera
    //
    // Sets the camera looking in at this scene
    void setCamera(Camera* camera) {
      if (camera_ != 0) {
	delete camera_;
      }

      if (primitives_ != 0) {
	delete primitives_;
      }

      camera_ = camera;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: numLights
    //
    // Returns the number of lights in this scene
    size_t numLights() const { return lights_.size(); }

    ////////////////////////////////////////////////////////////////////////////
    // Function: getLight
    //
    // Returns the light at the given index
    Light* getLight(const size_t& index) const {
      assert(index < numLights());
      return lights_[index];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Function: getCamera
    //
    // Returns the camera looking on this scene
    Camera* getCamera() const { return camera_; }
  private:
    ////////////////////////////////////////////////////////////////////////////
    // Type definitions
    typedef std::vector<Light*> LightSetT;

    LightSetT lights_; // All the lights in a scene.
    Group*    primitives_; // All the primitives in a scene.
    Camera*   camera_; // The camera looking onto the scene.
  };
}

#endif // SCENE_HPP__
