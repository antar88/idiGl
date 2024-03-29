//
//  glMethods.cpp
//  CLTest
//
//  Created by Antar - SSD on 08/12/12.
//  Copyright (c) 2012 Àlex Vergara. All rights reserved.
//

#include "glMethods.h"

#include <iostream>
#include <math.h>
using namespace std;

//triangle
static triangleColor tc = {1.0,0.0,0.0};
static trianlePos tp = { Point(-0.5f,-1.0f/3.0f,0.0f) , Point(0.5f,-1.0f/3.0f,0.0f), Point(0.0f,2.0f/3.0f,0.0f)};

//globals
static int mode = NORMAL_MODE;
static float aWidth = SCREEN_W, aheigth = SCREEN_H;

//mouse
static int xO, yO;
static int numClic = 0;

void refresh(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Drawing Zone
    glBegin(GL_TRIANGLES);
    
  
    glColor3f(tc.r,tc.g,tc.b);
    glVertex3f(tp.p1.x,tp.p1.y,tp.p1.z);
    glVertex3f(tp.p2.x,tp.p2.y,tp.p2.z);
    glVertex3f(tp.p3.x,tp.p3.y,tp.p3.z);
    glEnd();
    
    
    glutSwapBuffers();
    
}

void updateCamera(float x, float y) {
    GLfloat rawX = x / SCREEN_W;
    GLfloat rawY = y / SCREEN_H;
    GLfloat minRawXY = min(rawX,rawY);
    
    glLoadIdentity();
    glOrtho(-rawX/minRawXY,rawX/minRawXY,-rawY/minRawXY,rawY/minRawXY,0.0,10.0);
    
    cerr << "rezised windo " << x << " X " << y << " coord " << -rawX/minRawXY << " " << rawX/minRawXY << " " << -rawY/minRawXY << " " << rawY/minRawXY <<endl;
    
}

void reshape(int x, int y) {
    glViewport(0,0,x,y);
    updateCamera((float)x,(float)y);
    aWidth = x;
    aheigth = y;
}

Point viewPointToAppPoint(Point p) {
    Point retPoint = Point();
    
    if(p.x < (aWidth/2.0f)) retPoint.x = (p.x - (aWidth/2.0f));
    else retPoint.x = p.x - (aWidth/2.0f);
    
    if(p.y > (aheigth/2.0f)) retPoint.y= (aheigth/2.0f) - p.y;
    else retPoint.y = (aheigth/2.0f)-p.y;
    
    retPoint.x = retPoint.x/(aWidth/2.0);
    retPoint.y = retPoint.y/(aheigth/2.0);

    return retPoint;
}

void mouseInteraction(int mouseButton, int type, int xClic, int yClic) {
    cerr << xClic << " " << yClic << endl;
    if(type) {
        if(mode == DRAWING_MODE) numClic++;
    }
    else {
        if(mode == DRAWING_MODE) {
            Point mousePoint = Point(xClic, yClic);
            if(numClic == 0) tp.p1 = viewPointToAppPoint(mousePoint);
            else if (numClic == 1) tp.p2 = viewPointToAppPoint(mousePoint);
            else if (numClic == 2) {
                tp.p3 = viewPointToAppPoint(mousePoint);
                numClic = 0;
                mode = NORMAL_MODE;
                glutPostRedisplay();
            }
        }
        xO = xClic;
        yO = yClic;
    }
}

void mouseMovement(int xMouse, int yMouse) {
    
    /*
    int xdif = (xMouse - xO);
    int ydif = (yMouse - yO);
    
    xdif = abs(xdif);
    
    
    tc.r =  xdif / 10.0;
    
    xO = xMouse;
    yO = yMouse;
    cerr << tc.r << " " << tc.g << " " << tc.b << endl;
    
    glutPostRedisplay(); */
}

void keyboardInteraction(unsigned char key, int xMouse, int yMouse) {
    if(key == 'h' or key == 'H') cout << "HEEEEELP ME" << endl;
    else if (key == 27) exit(0);
    else if (key == 'f') {
        mode = DRAWING_MODE;
        cerr << "Drawing mode activated" << endl;
    }
}

