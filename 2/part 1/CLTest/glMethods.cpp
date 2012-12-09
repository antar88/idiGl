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
static trianlePos tp2 = { Point(-0.3f,0.3f,0.0f) , Point(0.2f,0.5f,0.0f), Point(0.3f,-0.4f,0.0f)};
static Point scaleVector = Point(1,1,1);
static Point rotateVector = Point (0,0,0);

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
    
    
    
    //Triangle 1
    glPushMatrix();
    glRotated(rotateVector.x, 1, 0, 0);
    glRotated(rotateVector.y, 0, 1, 0);
    glRotated(rotateVector.z, 0, 0, 1);
    glScaled(scaleVector.x, scaleVector.y, scaleVector.z);
    
    glBegin(GL_TRIANGLES);
    glColor3f(tc.r,tc.g,tc.b);
    glVertex3f(tp.p1.x,tp.p1.y,tp.p1.z);
    glVertex3f(tp.p2.x,tp.p2.y,tp.p2.z);
    glVertex3f(tp.p3.x,tp.p3.y,tp.p3.z);
    glEnd();
    
    glPopMatrix();
    
    //Triangle 2    
    glPushMatrix();
    glTranslated(0.5f, 0.5f, 0.f);
    glRotated(rotateVector.x * (-1), 1, 0, 0);
    glRotated(rotateVector.y * (-1), 0, 1, 0);
    glRotated(rotateVector.z * (-1), 0, 0, 1);
    
    glBegin(GL_TRIANGLES);
    glVertex3f(tp2.p1.x,tp2.p1.y,tp2.p1.z);
    glVertex3f(tp2.p2.x,tp2.p2.y,tp2.p2.z);
    glVertex3f(tp2.p3.x,tp2.p3.y,tp2.p3.z);
    glEnd();
    
    
    glPopMatrix();
    
    updateCamera(aWidth, aheigth);
    
    glutSwapBuffers();
    
}

void updateCamera(float x, float y) {
    GLfloat rawX = x / SCREEN_W;
    GLfloat rawY = y / SCREEN_H;
    GLfloat minRawXY = min(rawX,rawY);
    glLoadIdentity();
    glOrtho(-rawX/minRawXY,rawX/minRawXY,-rawY/minRawXY,rawY/minRawXY,0.0,10.0);
}

void reshape(int x, int y) {
    glViewport(0,0,x,y);
    aWidth = x;
    aheigth = y;
    glutPostRedisplay();
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
        xO = xClic;
        yO = yClic;
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
                scaleVector = Point(1,1,1);
                glutPostRedisplay();
            }
        }
    }
}

void mouseMovement(int xMouse, int yMouse) {

    
    if(abs(xMouse - xO) > 5) {
        if ((xMouse - xO) > 0) {
            rotateVector.z += 3;
            if(rotateVector.z > 360) rotateVector.z -= 360;
        }
        else {
            rotateVector.z -= 3;
            if(rotateVector.z < 360) rotateVector.z += 360;
        }
        
        glutPostRedisplay();
    }
    xO = xMouse;
    yO = yMouse;
}

void keyboardSpecialKeysInteraction(int key, int xMouse, int yMouse) {
    bool refresh = false;
    if (key == GLUT_KEY_UP) {
        cerr << "UP"<< endl;
        scaleVector.y += 0.1;
        refresh =  true;
    }
    else if (key == GLUT_KEY_LEFT) {
        scaleVector.x -= 0.1;
        refresh =  true;
    }
    else if (key == GLUT_KEY_DOWN) {
        scaleVector.y -= 0.1;
        refresh =  true;
    }
    else if (key == GLUT_KEY_RIGHT) {
        scaleVector.x += 0.1;
        refresh =  true;
    }
    if(refresh) glutPostRedisplay();
}

void keyboardInteraction(unsigned char key, int xMouse, int yMouse) {
    bool refresh = false;
    if(key == 'h' or key == 'H') cout << "HEEEEELP ME" << endl;
    else if (key == 27) exit(0);
    else if (key == 'f') {
        mode = DRAWING_MODE;
        cerr << "Drawing mode activated" << endl;
    }
    else if (key == 'r') {
        rotateVector.z -= 10;
        if(rotateVector.z < 360) rotateVector.z += 360;
        refresh =  true;
    }
    else if (key == 'l') {
        rotateVector.z += 10;
        if(rotateVector.z > 360) rotateVector.z -= 360;
        refresh =  true;
    }
    else if (key == 'z') {
        scaleVector.z += 0.1;
        refresh =  true;
    }
    else if (key == 'x') {
        scaleVector.z -= 0.1;
        refresh =  true;
    }
    
    if(refresh) glutPostRedisplay();
}

