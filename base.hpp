////////////////////////////////////////////////////////////////////////////////
// Base: A Simple Graphics Suite
// Author: Eric Scrivner
//
// Time-stamp: <Last modified 2009-11-14 11:09:57 by Eric Scrivner>
//
// Description:
//   Contains basic type definitions
////////////////////////////////////////////////////////////////////////////////

#ifndef BASE_HPP__
#define BASE_HPP__

// C++ includes
#include <string>

// C includes

// OpenGL includes
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

namespace Base {
  //////////////////////////////////////////////////////////////////////////////
  // Integer Types
  typedef unsigned char  Byte;
  typedef unsigned char	 U8;
  typedef unsigned short U16;
  typedef unsigned long	 U32;
	
  typedef signed char  S8;
  typedef signed short S16;
  typedef signed long S32;

  //////////////////////////////////////////////////////////////////////////////
  // Real Number Types
  typedef float  F32;
  typedef double F64;
  typedef double Real;
}

#endif // BASE_HPP__
