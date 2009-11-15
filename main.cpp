////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-14 12:12:22 by Eric Scrivner>
//
// Description:
//  Sample application entry point
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include "base.hpp"
#include "matrix44.hpp"
using namespace Base;

////////////////////////////////////////////////////////////////////////////////
// Constants

const unsigned int kWindowWidth  = 640;
const unsigned int kWindowHeight = 480;
const char*        kWindowTitle  = "Symphony App";
const Real         kPi = 3.1415926535;

////////////////////////////////////////////////////////////////////////////////
// Function: Redraw
//
// Redraws the screen on an update
void Redraw() {
  // Clear the screen
	//  glClear(GL_COLOR_BUFFER_BIT);

  // Swap the redraw buffer onto the screen
  glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////
// Function: Reshape
//
// Reshapes the viewport so that (0, 0, 0) is the center of the screen and the
// x-coordinates go from -(width/2) to width/2 while the y-coordinates go from
// -(height/2) to height/2.
void Reshape(int width, int height) {
  float xMax = width / 2.0F;
  float yMax = xMax * height / width; // Preserve aspect ratio

  // Setup the viewport to map physical pixels to GL "logical" pixels
  glViewport(0, 0, (GLint)width, (GLint)height);

  // Adjust the region of 3D space projected onto the window
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluOrtho2D(-xMax, xMax,
             -yMax, yMax);

  glMatrixMode(GL_MODELVIEW);
}

////////////////////////////////////////////////////////////////////////////////
// Function: OnKeyPress
//
// Handles a key press from the user
void OnKeyPress(unsigned char key, int, int) {
  switch(key) {
  case 27: // Exit (ESC)
    exit(0);
    break;
  default: break;
  }

  glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////
// Function: Update
//
// Handles the idle loop updating of the simulation components
void Update() {
	// Do your updating here.
}

////////////////////////////////////////////////////////////////////////////////
// Function: InitGlut
//
// Initialize the GLUT
void InitGlut(int& argc, char* argv[]) {
  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(kWindowWidth, kWindowHeight);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(kWindowTitle);

  // Setup callbacks
  glutDisplayFunc(Redraw);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(OnKeyPress);
	glutIdleFunc(Update);
}

int main(int argc, char* argv[]) {
  InitGlut(argc, argv);

  glutMainLoop();
  return 0;
}
