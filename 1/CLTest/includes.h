//
//  includes.h
//  CLTest
//
//  Created by Antar - SSD on 08/12/12.
//  Copyright (c) 2012 Àlex Vergara. All rights reserved.
//

#if defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#define SCREEN_W    800.0f
#define SCREEN_H    600.0f
#define NORMAL_MODE      0
#define DRAWING_MODE     1

#include "point.h"
