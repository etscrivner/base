////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-02 02:15:47 by Eric Scrivner>
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
#include "light.hpp"
#include "material.hpp"
#include "primitive.hpp"
#include "ray_tracer.hpp"
#include "scene.hpp"
using namespace Base;

////////////////////////////////////////////////////////////////////////////////
// Constants

const unsigned int kWindowWidth  = 200;
const unsigned int kWindowHeight = 200;
const char*        kWindowTitle  = "Symphony App";

const int kXMax = (kWindowWidth / 2);
const int kYMax = (kWindowHeight / 2);
const int kXMin = -kXMax;
const int kYMin = -kYMax;

////////////////////////////////////////////////////////////////////////////////
// Scene
RayTracer* rt = 0;
Image img(kWindowWidth, kWindowHeight);

////////////////////////////////////////////////////////////////////////////////
// Function: Redraw
//
// Redraws the screen on an update
void Redraw() {
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw the image
  img.draw(kXMin, kYMin);

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
Real normalizeX(int x) { return (x < 0) ? -(Real)(kXMax + x) / kXMax : (Real)x / kXMax; }
Real normalizeY(int y) { return (y < 0) ? -(Real)(kYMax + y) / kYMax : (Real)y / kYMax; }
Vector2 normalized(int x, int y) { return Vector2(normalizeX(x), normalizeY(y)); }

void Update() {
  Ray nextRay(Vector3(0,0,0), Vector3(0,0,0));
  Hit hit;
  Color pixVal;

  for (int y = kYMin; y < kYMax; y++) {
    for (int x = kXMin; x < kXMax; x++) {
      nextRay = rt->getScene()->getCamera()->generateRay(normalized(x, y));
      pixVal = rt->traceRay(nextRay, 0, hit);
      img.setPixel(x + kXMax, y + kYMax, pixVal);
    }
  }

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
  Scene* scene;
  Camera* cam = new OrthographicCamera(Vector3(0, 0, 10),
                                       Vector3(0, 0, -1),
                                       Vector3(0, 1, 0),
                                       5);

  scene = new Scene(cam);
  PhongMaterial mat(Color(0.7, 0.7, 0.7), Color::Black, 0, Color::Black, Color::Black, 0);
  scene->getPrimitives()->addPrimitive(new Sphere(Vector3(0, 0, 0), 1, &mat));
  scene->addLight(new Light(Color::White, Vector3(0, 0, -1)));
  rt = new RayTracer(scene, 1);

  Update();
  img.saveAsTga("result.tga");
  InitGlut(argc, argv);
  glutMainLoop();

  delete rt;

  return 0;
}
