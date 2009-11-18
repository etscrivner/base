////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-17 23:29:56 by Eric Scrivner>
//
// Description:
//  Sample application entry point
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include <cstdlib>

#include "base.hpp"
#include "color.hpp"
#include "matrix44.hpp"
#include "plot.hpp"
using namespace Base;

////////////////////////////////////////////////////////////////////////////////
// Constants

const unsigned int kWindowWidth  = 640;
const unsigned int kWindowHeight = 480;
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
	//glClear(GL_COLOR_BUFFER_BIT);

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
Base::Color** pixBuf;

void Update() {
	Base::Plot(kXMin, kXMax, kYMin, kYMax, pixBuf);
	glBegin(GL_POINTS);
	  for(size_t x = 0; x < kWindowWidth; x++) {
			for (size_t y = 0; y < kWindowHeight; y++) {
				glColor3f(pixBuf[x][y].r,
				          pixBuf[x][y].b,
				          pixBuf[x][y].g);
				glVertex2i(kXMin + x, kYMin + y);
			}
		}
	glEnd();
	glutPostRedisplay();
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
	pixBuf = (Color**)malloc(sizeof(Color) * kWindowHeight * kWindowWidth);
	for (size_t i = 0; i < kWindowWidth; i++) {
		pixBuf[i] = new Color[kWindowHeight];
	}
  InitGlut(argc, argv);

  glutMainLoop();
	free(pixBuf);
  return 0;
}
