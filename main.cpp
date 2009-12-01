////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-30 23:25:53 by Eric Scrivner>
//
// Description:
//  Sample application entry point
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include <cstdlib>

#include "base.hpp"
#include "camera.hpp"
#include "image.hpp"
using namespace Base;

////////////////////////////////////////////////////////////////////////////////
// Constants

const unsigned int kWindowWidth  = 600;
const unsigned int kWindowHeight = 600;
const char*        kWindowTitle  = "Symphony App";

const int kXMax = (kWindowWidth / 2);
const int kYMax = (kWindowHeight / 2);
const int kXMin = -kXMax;
const int kYMin = -kYMax;

////////////////////////////////////////////////////////////////////////////////
// Function: Redraw
//
// Redraws the screen on an update
void Redraw() {
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);

  // Render stuff here...

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
  // Setup the viewport to map physical pixels to GL "logical" pixels
  glViewport(0, 0, (GLint)width, (GLint)height);

  // Adjust the region of 3D space projected onto the window
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluOrtho2D(kXMin, kXMax,
             kYMin, kYMax);

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
  // Do nothing...
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
  Base::OrthographicCamera cam(Vector3(0, 0, 0), Vector3(0, 0, -1),
                               Vector3(0, 1, 0), kWindowHeight);

  for (Real y = 0.0; y <= 1.0F; y += 0.50F) {
    for (Real x = 0.0; x <= 1.0F; x += 0.50F) {
      Ray next = cam.generateRay(Vector2(x, y));
      cout<< next.origin.x << ", " << next.origin.y << endl;
    }
  }

  InitGlut(argc, argv);
  glutMainLoop();

  return 0;
}
