////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-02 14:07:38 by Eric Scrivner>
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

const Real kStepSize = 1.0F / (Real)kWindowWidth;

////////////////////////////////////////////////////////////////////////////////
// Ray Tracer
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
  img.draw(kXMin, kYMax);

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
// Function: ToPixelX
//
// Translates the given real coordinate value on [0, 1] to a pixel position
// in terms of the number of horizontal and vertical pixels on the screen.
int ToPixelX(const Real& coord) {
  return (coord - 0.5) * kWindowWidth + kXMax;
}

////////////////////////////////////////////////////////////////////////////////
// Function: ToPixelY
//
// Same as ToPixelY but for the y pixel coordinates.
int ToPixelY(const Real& coord) {
  return (coord - 0.5) * kWindowHeight + kYMax;
}

////////////////////////////////////////////////////////////////////////////////
// Function: Update
//
// Handles the idle loop updating of the simulation components
void Update() {
  Ray nextRay(Vector3(0,0,0), Vector3(0,0,0));
  Hit hit;
  Color pixVal;

  // For each pixel on the screen
  for (Real y = 0; y < 1.0F; y += kStepSize) {
    for (Real x = 0; x < 1.0F; x += kStepSize) {
      // Generate a ray from that pixel into the scene
      nextRay = rt->getScene()->getCamera()->generateRay(Vector2(x, y));
      
      // Compute the color of the pixel illuminated by that ray
      pixVal = rt->traceRay(nextRay, 0, hit);
      img.setPixel(ToPixelX(x), ToPixelY(y), pixVal);
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
  // Camera setup
  Camera* cam = new OrthographicCamera(Vector3(0, 0, 10),
                                       Vector3(0, 0, -1),
                                       Vector3(0, 1, 0),
                                       5);

  // Scene initialization
  Scene* scene = new Scene(cam);
  scene->setBackgroundColor(Color(0.2, 0.2, 0.2));

  // Scene lights
  scene->addLight(new Light(Color::White, Vector3(1, 1, -1)));

  // Scene primitives
  PhongMaterial bigSphere(Color::Red, Color::Black, 0, Color::Black, Color::Black, 0);
  PhongMaterial tinySphere1(Color::Green, Color::Black, 0, Color::Black, Color::Black, 0);
  PhongMaterial tinySphere2(Color::Blue, Color::Black, 0, Color::Black, Color::Black, 0);

  Group* group = scene->getPrimitives();
  group->addPrimitive(new Sphere(Vector3(0, 0, -1), 1, &bigSphere));
  group->addPrimitive(new Sphere(Vector3(1, 1, 0), 0.75, &tinySphere1));
  group->addPrimitive(new Sphere(Vector3(-1, -1, 0), 0.75, &tinySphere1));
  group->addPrimitive(new Sphere(Vector3(-1, 1, -2), 0.75, &tinySphere2));
  group->addPrimitive(new Sphere(Vector3(1, -1, -2), 0.75, &tinySphere2));

  // Ray tracer setup
  rt = new RayTracer(scene, 1);

  Update();
  img.saveAsTga("result.tga");

  InitGlut(argc, argv);
  glutMainLoop();

  delete rt;

  return 0;
}
