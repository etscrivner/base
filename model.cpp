////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-04 16:36:36 by Eric Scrivner>
//
// Description:
//   Represents a model loaded from an OBJ file and provides methods for
// drawing it.
////////////////////////////////////////////////////////////////////////////////

#include "draw_line.hpp"
#include "material.hpp"
#include "model.hpp"
#include "primitive.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// OBJ Parser

enum eLineType {
  eVertex,
  eFace,
  eOther
};

////////////////////////////////////////////////////////////////////////////////

eLineType LineType(const std::string& line) {
  // Accumulate the first word in a string
  std::string firstWord;

  // Loop through each character in the string
  for (size_t i = 0; i < line.length(); i++) {
    // If we have reached the end of word character
    if (line[i] == ' ') {
      // Exit the loop
      break;
    }

    // Add the character to the first word
    firstWord += line[i];
  }

  if (firstWord == "v") {
    return eVertex;
  } else if (firstWord == "f") {
    return eFace;
  }

  return eOther;
}

////////////////////////////////////////////////////////////////////////////////

Base::Vertex VertexFromString(const std::string& vertStr) {
  Base::Vertex result;
  string firstWord;

  std::stringstream s(vertStr);
  s >> firstWord >> result.x >> result.y >> result.z;

  return result;
}


////////////////////////////////////////////////////////////////////////////////

Base::Face FaceFromString(const std::string& faceStr) {
  // Create a substring removing the first word from the string
  std::string parsableFace;
  parsableFace = faceStr.substr(faceStr.find(" "), faceStr.length());

  // Attempt to tokenize the given string
  Base::Face result;
  char* token = strtok(const_cast<char*>(parsableFace.c_str()), " \t\n\r");
  std::string nextNum;

  // While there are still tokens left
  while (token != NULL) {
    // Parse the first number from the triplet of the form v/vt/vn
    std::string curToken = token;
    nextNum = curToken.substr(0, curToken.find("/"));

    // Add the number to the facial indices, subtracting one since they
    // will become array indices.
    result.addIndex(atoi(nextNum.c_str()) - 1);

    // Retrieve the next number
    token = strtok(NULL, " \t\n\r");
  }

  return result;
}

////////////////////////////////////////////////////////////////////////////////
// Model

bool Base::Model::load(const std::string& fileName) {
  // Ensure the string has characters in it
  if (fileName.length() == 0) {
    return false;
  }

  // Attempt to open the given file
  std::ifstream modelFile(fileName.c_str());

  // If the file could not be opened
  if (!modelFile.is_open() || !modelFile.good()) {
    // Return an error
    return false;
  }

  // Clear the vertices and faces from this model
  vertices_.clear();
  faces_.clear();

  // While there are lines left to read
  std::string nextLine;
  while (std::getline(modelFile, nextLine)) {
    // If the type of data on the next line is ...
    switch (LineType(nextLine)) {
    case eVertex: // a vertex
      addVertex(VertexFromString(nextLine));
      break;
    case eFace: // a face
      addFace(FaceFromString(nextLine));
      break;
    default: break;
    }
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////

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

Base::Group* Base::Model::toPrimitive(Material* material) {
  Base::Group* group = new Base::Group();
  
  // Loop through each of the faces
  for (size_t i = 0; i < faces_.size(); i++) {
    // Loop through each triple of vertices in the face
    size_t numIndices = faces_[i].size();
    
    for (size_t j = 0; j < numIndices; j++) {
      group->addPrimitive(_makeTriangle(faces_[i][j],
                                        faces_[i][(j + 1) % numIndices],
                                        faces_[i][(j + 2) % numIndices],
                                        material));
    }
  }

  return group;
}

////////////////////////////////////////////////////////////////////////////////

void Base::Model::transform(const Matrix44& transformation) {
  Vector4 result;
  for (size_t i = 0; i < vertices_.size(); i++) {
    result = transformation * Vector4(vertices_[i]);
    vertices_[i].x = result.x;
    vertices_[i].y = result.y;
    vertices_[i].z = result.z;
  }
}

////////////////////////////////////////////////////////////////////////////////

void Base::Model::_drawTriangle(size_t& v1, size_t& v2, size_t& v3) {
  Base::DrawLine(vertices_[v1], vertices_[v2], color_);
  Base::DrawLine(vertices_[v2], vertices_[v3], color_);
  Base::DrawLine(vertices_[v3], vertices_[v1], color_);
}

////////////////////////////////////////////////////////////////////////////////

Base::Triangle* Base::Model::_makeTriangle(size_t& v1,
                                           size_t& v2,
                                           size_t& v3,
                                           Material* mat) {
  return new Base::Triangle(vertices_[v1], vertices_[v2], vertices_[v3], mat);
}
