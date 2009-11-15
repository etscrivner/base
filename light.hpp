////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-15 13:31:51 by Eric Scrivner>
//
// Description:
//   Defines a simple point light source model
////////////////////////////////////////////////////////////////////////////////

#ifndef LIGHT_HPP__
#define LIGHT_HPP__

#include "color.hpp"
#include "vector4.hpp"

namespace Base {
	//////////////////////////////////////////////////////////////////////////////
	// Class: Light
	//
	// Models a point light source with a position and color.
	class Light {
	public:
		Light()
		{ }

		Light(const Color& col, const Vector4& pos)
			: color(col), position(pos)
		{ }

		Color   color;
		Vector4 position;
	};

	//////////////////////////////////////////////////////////////////////////////
	// Class: AmbientLight
	//
	// Defines ambient lighting given by a color and intesity.
	class AmbientLight {
	public:
		AmbientLight()
		{ }

		AmbientLight(const Color& col, const Real& intense)
			: color(col), intensity(intense)
		{ }

		Color color;
		Real  intensity;
	};
}

#endif // LIGHT_HPP__
