//
//  glMethods.cpp
//  
//
//  Created by Antar - SSD on 01/12/12.
//
//

#include "glMethods.h"

#include <iostream>
using namespace std;

float width, height;

void refresh(void)
{
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float raw = width / height;
	glOrtho(-1.0,1.0,-1.0,1.0,1.0,10.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.,0.,1.0,0.,0.,0.,0.,1.,0.);
	*/

	
	glBegin(GL_TRIANGLES);
		glColor3f(1.,0.,0.);
		glVertex3f(-0.5f,(1.0f/3.0f)*(-1.0f),0.0f);
		glVertex3f(0.5f,(1.0f/3.0f)*(-1.0f),0.0f);
		glVertex3f(0.0f,2.0f/3.0f,0.0f);
	glEnd();
	

	
	
	glutSwapBuffers();

}

void reshape(int x, int y) {
	width = (float) x;
	height = (float) y;
	glViewport(0,0,x,y);
}






