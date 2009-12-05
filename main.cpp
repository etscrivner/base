////////////////////////////////////////////////////////////////////////////////
// Project 2: A Simple Ray-Tracer
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-12-05 13:40:38 by Eric Scrivner>
//
// Description:
//   A simple ray-tracer to be used for tracing obj model files.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include <cstdlib>
#include <ctime>

#include "base.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "light.hpp"
#include "material.hpp"
#include "model.hpp"
#include "primitive.hpp"
#include "ray_tracer.hpp"
#include "scene.hpp"
using namespace Base;

////////////////////////////////////////////////////////////////////////////////
// Constants
unsigned int kWindowWidth  = 400;
unsigned int kWindowHeight = 200;
const char*  kWindowTitle  = "Symphony App";

const int kXMax = (kWindowWidth / 2);
const int kYMax = (kWindowHeight / 2);
const int kXMin = -kXMax;
const int kYMin = -kYMax;

Image gImage(kWindowWidth, kWindowHeight);

////////////////////////////////////////////////////////////////////////////////
// Function: Redraw
//
// Redraws the screen on an update
void Redraw() {
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw the image
  gImage.draw(kXMin, kYMin);

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
  // Need to add rounding to avoid floating-point to int conversion errors
  int result = static_cast<int>(roundf((coord - 0.5) * kWindowWidth + kXMax));
  return (result >= (int)kWindowWidth) ? (kWindowWidth - 1) : result;
}

////////////////////////////////////////////////////////////////////////////////
// Function: ToPixelY
//
// Same as ToPixelY but for the y pixel coordinates.
int ToPixelY(const Real& coord) {
  int result =  static_cast<int>(roundf((coord - 0.5) * kWindowHeight + kYMax));
  return (result >= (int)kWindowHeight) ? (kWindowHeight - 1) : result;
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

////////////////////////////////////////////////////////////////////////////////
// Function: TraceScene
//
// Uses the given ray-tracer to ray-trace a scene which is then saved to the
// given output file if given.
void TraceScene(const RayTracer& rayTracer,
                const size_t& sceneSize,
                Image& image) {
  // Compute the step size for the scene
  Real stepSize = 1.0F / (Real)sceneSize;
  
  // Create some useful variables for this procedure
  Camera* sceneCam = rayTracer.getScene()->getCamera();
  Ray nextRay(Vector3(0,0,0), Vector3(0,0,0));
  Hit rayHit;
  Color pixelColor;

  // Give the user some indication that things are happening
  cout << "Ray-tracing scene...";
  cout.flush();

  // Start timing the ray tracer
  clock_t start, stop;
  start = clock();

  // For each pixel in the scene
  for (Real y = 0.0F; y < 1.0F; y += stepSize) {
    for (Real x = 0.0F; x < 1.0F; x += stepSize) {
      // Generate the ray from the camera for the current pixel
      nextRay = sceneCam->generateRay(Vector2(x, y));
      
      // Compute the shading on the current pixel
      pixelColor = rayTracer.traceRay(nextRay, 0, 0.001, 1.0F, 1.0F, rayHit);
      image.setPixel(ToPixelX(x), ToPixelY(y), pixelColor);
    }
  }

  // Compute the total ellapsed time
  stop = clock() - start;
  cout << "Done!" << endl;
  
  int numSecs = (int)round((Real)stop / ((Real)CLOCKS_PER_SEC));
  int numMins = numSecs / 60;
  numSecs = numSecs % 60;

  // Display the ellapsed time to ray-trace the scene
  printf("Ellapsed Time %02d:%02d\n", (int)numMins, (int)numSecs);
}

int main(int argc, char* argv[]) {
  // If there were not enough command line arguments
  if (argc < 2) {
    // Display the usage message and abort
    cout << "Usage: raytrace [modelfile] [-output filename] [-size dimension]" << endl;
    cout << "  - output : Will write a TGA file with the ray traced scene." << endl;
    cout << "  - size : Sets the size of the square output image" << endl;
    return 1;
  }

  // Parse the model filename from the command line arguments
  string modelFile = argv[1];
  string outputFile;

  // Check for additional command line arguments
  if (argc > 2) {
    int i = 2;
    while (i < argc) {
      if (std::string(argv[i]) == "-output") { // Output image to a file
	if (argc < (i + 2)) { // No output file name
	  cout << "Error, -output command line argument requires filename" << endl;
	  return 1;
	} else {
	  outputFile = argv[i + 1];
	  i += 2;
	}
      } else if (std::string(argv[i]) == "-size") { // Output image size
	if (argc < (i + 2)) { // No dimension
	  cout << "Error, -size requires a numerical size value" << endl;
	  return 1;
	} else {
	  kWindowWidth = kWindowHeight = atoi(argv[i + 1]);
	  i += 2;
	}
      }
    }
  }

  // Camera setup
  Camera* cam  = new PerspectiveCamera(Vector3(0, 2, 8),
                                       Vector3(0, 0, -1),
                                       Vector3(0, 1, 0),
                                       kWindowHeight,
                                       2,
                                       60);
  
  // Load the model file(s)
  Model model;
  model.load(modelFile);
  Model bunny;
  bunny.load("./data/bunny_200.obj");

  // Scene initialization
  Scene* scene = new Scene(cam);
  scene->setAmbient(Color(0.1, 0.1, 0.1));
  scene->setBackgroundColor(Color(0.2, 0.1, 0.6));

  // Scene lights
  scene->addLight(new Light(Color(0.9, 0.9, 0.9), Vector3(-1, -2, 0)));
  scene->addLight(new Light(Color(0.6, 0.6, 0.6), Vector3(1, -2, 0)));

  // Scene materials
  PhongMaterial sphereOne(Color(0.1, 0.1, 0.1),
                          Color::Black,
                          50,
                          Color(0.5, 0.5, 0.5),
                          Color(0.9, 0.9, 0.9),
                          1.1);
  PhongMaterial sphereTwo(Color(0.9, 0.1, 0.1),
                          Color::Black,
                          0,
                          Color::Black,
                          Color(0.9, 0.1, 0.1),
                          1.2);
  PhongMaterial plane(Color(0.3, 0.3, 0.3),
                      Color::Black,
                      0,
                      Color::Black,
                      Color::Black,
                      1);

  PhongMaterial trashcan(Color(0.1, 0.1, 0.1),
                      Color::White,
                      50,
                      Color::Black,//Color(0.9, 0.9, 0.9),
                      Color(0.9, 0.9, 0.9),
                      1.1);
  PhongMaterial bunnyMat(Color(0.1, 0.1, 0.1),
                         Color::White,
                         50,
                         Color::Black,//Color(0.9, 0.9, 0.9),
                         Color::Black,
                         1);
                      
  // Scene primitives
  Group* group = scene->getPrimitives();
  //group->addPrimitive(new Sphere(Vector3(-2.3, 1.2, 2.0), 2, &sphereOne));
  //group->addPrimitive(new Sphere(Vector3(-5.2, 2, 0.2), 1, &sphereTwo));
  group->addPrimitive(new Plane(Vector3(0, 1, 0), 1, &plane));

  //x Translate the model provided.
  Matrix44 trans;
  trans.makeTranslate(0.03, -0.1666, 0);
  model.transform(trans);

  //trans.makeScale(8, 8, 8);
  //model.transform(trans);
  //bunny.transform(scale);

  group->addPrimitive(model.toPrimitive(&bunnyMat));
  //group->addPrimitive(bunny.toPrimitive(&bunnyMat));

  // Ray-trace the given scene
  Image image(kWindowWidth, kWindowHeight);
  RayTracer rayTracer(scene, 3, 0.01);

  TraceScene(rayTracer, kWindowWidth, image);

  // If an image file was given save the image
  if (outputFile.length()) {
    image.saveAsTga(outputFile);
  }

  gImage = image;

  InitGlut(argc, argv);
  glutMainLoop();

  return 0;
}
