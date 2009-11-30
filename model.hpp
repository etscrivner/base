////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-29 18:11:35 by Eric Scrivner>
//
// Description:
//   Represents a model loaded from an OBJ file and provides methods for
// drawing it.
////////////////////////////////////////////////////////////////////////////////

#ifndef MODEL_HPP__
#define MODEL_HPP__

#include "color.hpp"
#include "vector3.hpp"

#include <vector>

namespace Base {
	//////////////////////////////////////////////////////////////////////////////
	// Type definitions
	typedef Vector3 Vertex;

	//////////////////////////////////////////////////////////////////////////////
	// Class: Face
	//
	// Defines a single face of model as a set of indices into a vertex list
	class Face {
	public:
		////////////////////////////////////////////////////////////////////////////
		// Function: addIndex
		//
		// Parameters:
		//   index - An index into a list of vertices
		//
		// Adds the given index to this face
		void addIndex(const size_t& index)
		{ index_.push_back(index); }

		////////////////////////////////////////////////////////////////////////////
		// Function: operator []
		//
		// Parameters:
		//   index - An index into the index list
		//
		// Returns the given vertex index
		size_t& operator [] (const size_t& index) {
			assert(index < index_.size());
			return index_[index];
		}

		//////////////////////////////////////////////////////////////////////////////
		// Function: size
		//
		// Returns the number of indices which compose this face
		size_t size() const
		{ return index_.size();}
	private:
		std::vector<size_t> index_; // The indices which compose the face
	};

	//////////////////////////////////////////////////////////////////////////////
	// Class: Model
	//
	// Represents a model loaded from a file in OBJ format.
	class Model {
	public:
		////////////////////////////////////////////////////////////////////////////
		// Function: load
		//
		// Parameters:
		//   fileName - The name of the file to be loaded
		//
		// Loads the OBJ model from the given file into the class, returning true
		// if the model was loaded and false otherwise.
		bool load(const std::string& fileName);

		////////////////////////////////////////////////////////////////////////////
		// Function: draw
		//
		// Parameters:
		//   pos - The position at which to draw the model
		//
		// Draws the model at the given position on the screen
		void draw(const Vector3& pos);

		//////////////////////////////////////////////////////////////////////////////
		// Function: addVertex
		//
		// Parameters:
		//   vertex - A vertex to be added
		//
		// Adds the given vertex to this model's vertex list
		void addVertex(const Vertex& vertex)
		{ vertices_.push_back(vertex); }

		////////////////////////////////////////////////////////////////////////////////
		// Function: addFace
		//
		// Parameters:
		//   face - A face to be added
		//
		// Adds the given face to this model's face list
		void addFace(const Face& face)
		{ faces_.push_back(face); }

		////////////////////////////////////////////////////////////////////////////////
		// Function: setColor
		//
		// Parameters:
		//    color - A color
		//
		// Sets the color of the model when rendered to the color given
		void setColor(const Color& color)
		{ color_ = color; }
	private:
		////////////////////////////////////////////////////////////////////////////
		// Function: _drawTriangle
		//
		// Parameters:
		//   v1, v2, v3 - The vertex indices forming the triangle
		//
		// Renders a triangle using the given vertices and Bresenham's line
		// drawing algorithm.
		void _drawTriangle(size_t& v1, size_t& v2, size_t& v3);

		////////////////////////////////////////////////////////////////////////////
		// Type definition
		typedef std::vector<Face>		FaceList;
		typedef std::vector<Vertex> VertexList;

		Color				color_;					// The color used to render the model.
		FaceList		faces_;					// The faces making up the model
		VertexList	vertices_;			// The list of vertices composing the model
	};
}

#endif // MODEL_HPP__
