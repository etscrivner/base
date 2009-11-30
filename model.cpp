////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-29 17:42:41 by Eric Scrivner>
//
// Description:
//   Represents a model loaded from an OBJ file and provides methods for
// drawing it.
////////////////////////////////////////////////////////////////////////////////

#include "draw_line.hpp"
#include "model.hpp"

void Base::Model::draw(const Base::Vector3& pos) {
	// Translate all the vertices to the given position
	for (size_t i = 0; i < vertices_.size(); i++) {
		vertices_[i] += pos;
	}

	// Loop through each of the faces
	for (size_t i = 0; i < faces_.size(); i++) {
		// Loop through each triple of vertices in the face
		size_t numIndices = faces_[i].size();

		for (size_t j = 0; j < numIndices; j++) {
			_drawTriangle(faces_[i][j],
			              faces_[i][(j + 1) % numIndices],
			              faces_[i][(j + 2) % numIndices]);
		}
	}

	// Untranslate all the vertices
	for (size_t i = 0; i < vertices_.size(); i++) {
		vertices_[i] -= pos;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Base::Model::_drawTriangle(size_t& v1, size_t& v2, size_t& v3) {
	Base::DrawLine(vertices_[v1], vertices_[v2], color_);
	Base::DrawLine(vertices_[v2], vertices_[v3], color_);
	Base::DrawLine(vertices_[v3], vertices_[v1], color_);
}
