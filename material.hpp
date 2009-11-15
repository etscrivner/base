////////////////////////////////////////////////////////////////////////////////
// Base: A Computer Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-15 14:01:11 by Eric Scrivner>
//
// Description:
//   Class for representing a material's light reflection properties
////////////////////////////////////////////////////////////////////////////////

#ifndef MATERIAL_HPP__
#define MATERIAL_HPP__

#include "base.hpp"
#include "color.hpp"

namespace Base {
	//////////////////////////////////////////////////////////////////////////////
	// Class: Material
	//
	// Represents a color using four properties color, specular intensity,
	// diffuse intensity and shininess. These properties can then be applied to
	// the object according to the Phong or Blinn-Phong lighting models.
	struct Material {
		Material()
		{ }

		Material(const Color& col, const Real& spec,
		         const Real& diff, const Real& shiny)
			: color(col), specular(spec), diffuse(diff), shininess(shiny)
		{ }

		Color color;
		Real  specular;
		Real  diffuse;
		Real  shininess;
	};
}

#endif // MATERIAL_HPP__
