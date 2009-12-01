////////////////////////////////////////////////////////////////////////////////
// Base: A Computer Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-01 00:23:08 by Eric Scrivner>
//
// Description:
//   Class for representing a material's hit by light rays
////////////////////////////////////////////////////////////////////////////////

#ifndef MATERIAL_HPP__
#define MATERIAL_HPP__

#include "base.hpp"
#include "color.hpp"
#include "hit.hpp"
#include "ray.hpp"

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Class: Material
  //
  // Base class for material properties of objects used to shade them
  class Material {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Function: Material
    //
    // Parameters:
    //   diffuseColor - The color of the diffuse reflection of this material
    //   refractionColor - The color of light passing through this material
    //   reflectionColor - The color of light reflecting off this material
    //   indexOfRefraction - The index of refraction used in lighting
    //
    // Initializes this material with the given properties
    Material(const Color& diffuseColor,
             const Color& refractionColor,
             const Color& reflectionColor,
             const Real& indexOfRefraction)
      : diffuse(diffuseColor),
        refraction(refractionColor),
        reflection(reflectionColor),
        indexOfRefraction(indexOfRefraction)
    { }

    virtual ~Material()
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: shade
    //
    // Parameters:
    //   ray - The light ray hitting this material
    //   hit - The information about the light ray hit on a surface
    //   dirToLight - The direction of the light source shading this object
    //   lightColor - The color of the light hitting this object
    //
    // Returns the color of this material when hit by the given ray from the
    // given light
    virtual Color shade(const Ray& ray,
                        const Hit& hit,
                        const Vector3& dirToLight,
                        const Color& lightColor) const = 0;

    Color diffuse, refraction, reflection;
    Real  indexOfRefraction;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Class: PhongMaterial
  //
  // A material which can be used in Phong shading calculations
  class PhongMaterial : public Material {
  public:
    PhongMaterial(const Color& diffuseColor,
                  const Color& specularColor,
                  const Real& fShininess,
                  const Color& refractionColor,
                  const Color& reflectionColor,
                  const Real& indexOfRefraction)
      : Material(diffuseColor,
                 refractionColor,
                 reflectionColor,
                 indexOfRefraction),
        specular(specularColor),
        shininess(fShininess)
    { }

    ////////////////////////////////////////////////////////////////////////////
    // Function: shade
    //
    // Shades the material according to the Phong shading model.
    Color shade(const Ray& ray,
                const Hit& hit,
                const Vector3& dirToLight,
                const Color& lightColor) const {
      // Diffuse lighting as C_d * (L . N)
      Vector3 l = dirToLight;
      Vector3 n = hit.normal;
      Color result = lightColor * diffuse * (l.dotProduct(n));

      // Specular lighting as C_s * (V . R)
      Vector3 v = ray.direction;
      Vector3 r = l - 2 * l.dotProduct(n) * n;
      result += lightColor * specular * (v.dotProduct(r));

      return result;
    }

    Color specular;
    Real  shininess;
  };
}

#endif // MATERIAL_HPP__
