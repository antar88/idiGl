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


static Point scaleVector = Point(1,1,1);
static Point rotateVector = Point (0,0,0);
static Point translateVector = Point (0,0,0);

//globals
static int mode = NORMAL_MODE;
static float aWidth = SCREEN_W, aheigth = SCREEN_H;
static Point obsPos = Point(0.f,0.f,10.f);
static Point up = Point(0.f,1.f,0.f);
static Scene planets = Scene();

//mouse
static int xO, yO;
static int numClic = 0;

void firstPaint(void)
{
    //Clear Zone
    glClearColor(0.0 , 0.0, 0.0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Drawing Zone
    planets.drawScene();
    
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0); glVertex3f(20,0,0); // X
    glColor3f(0,1,0);
    glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
    glColor3f(0,0,1);
    glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
    glEnd();
    glPopMatrix();
    
    //End zone
    glutSwapBuffers();
    
}

void refresh(void)
{
    //Clear Zone
    glClearColor(0.0 , 0.0, 0.0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Drawing Zone
    planets.drawScene();
    
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0); glVertex3f(20,0,0); // X
    glColor3f(0,1,0);
    glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
    glColor3f(0,0,1);
    glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
    glEnd();
    glPopMatrix();
    
    //End zone
    glutSwapBuffers();
    
}

void updateCamera(float x, float y) {
    GLfloat rawX = x / SCREEN_W;
    GLfloat rawY = y / SCREEN_H;
    GLfloat minRawXY = min(rawX,rawY);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(-rawX/minRawXY,rawX/minRawXY,-rawY/minRawXY,rawY/minRawXY,0.1,30.0);
    gluLookAt(obsPos.x, obsPos.y, obsPos.z, 0, 0, 0, up.x, up.y, up.z);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(int x, int y) {
    glViewport(0,0,x,y);
    aWidth = x;
    aheigth = y;
    //Camera Zone
    updateCamera(aWidth, aheigth);
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
    if(type) { //Clic IN
        if(mode == DRAWING_MODE) numClic++;
        xO = xClic;
        yO = yClic;
    }
    else { //Clic Out
                
        
    }
}

void mouseMovement(int xMouse, int yMouse) {
    
    bool refresh, refresh2;
    refresh = refresh2 = true;
    
    switch (mode) {
        case DRAWING_MODE:
            
            break;
        case ZOOM_MODE:
            refresh2 = false;
            if (abs(xMouse - xO) > 5 and (xMouse - xO) > 0) {
                rotateVector.y += 3;
                if(rotateVector.y > 360) rotateVector.y -= 360;
            }
            else if (abs(xMouse - xO) > 5){
                rotateVector.y -= 3;
                if(rotateVector.y < 360) rotateVector.y += 360;
            }
            else refresh = false;
            break;
        default:
            if (abs(xMouse - xO) > 5 and (xMouse - xO) > 0) rotateVector.y += 3;
            else if (abs(xMouse - xO) > 5) rotateVector.y -= 3;
            else refresh = false;
            
            if (abs(yMouse - yO) > 5 and (yMouse - yO) > 0) rotateVector.x += 5;
            else if(abs(yMouse - yO) > 5)rotateVector.x -= 5;
            else refresh2 = false;
            break;
    }
    
    if(rotateVector.x > 360) rotateVector.x -= 360;
    if(rotateVector.x < 360) rotateVector.x += 360;
    if(rotateVector.y < 360) rotateVector.y += 360;
    if(rotateVector.y > 360) rotateVector.y -= 360;
    if(refresh or refresh2) glutPostRedisplay();
    xO = xMouse;
    yO = yMouse;    
}

void keyboardSpecialKeysInteraction(int key, int xMouse, int yMouse) {
    bool refresh = true;
    switch (key) {
        case GLUT_KEY_UP:
            translateVector.y += 0.1;
            break;
        case GLUT_KEY_RIGHT:
            translateVector.x += 0.1;
            break;
        case GLUT_KEY_DOWN:
            translateVector.y -= 0.1;
            break;
        case GLUT_KEY_LEFT:
            translateVector.x -= 0.1;
            break;
        default:
            refresh = false;
            break;
    }
    if(refresh) glutPostRedisplay();
}

void keyboardInteraction(unsigned char key, int xMouse, int yMouse) {
    bool refresh = true;
    bool updateCam = false;
    switch (key) {
        case 'h':
            cout << "HEEEEELP ME" << endl;
            break;
        case 27:
            exit(0);
            break;
        case 'f':
            mode = DRAWING_MODE;
            cerr << "Drawing mode activated" << endl;
            break;
        case 'r':
            rotateVector.z -= 10;
            break;
        case 'l':
            rotateVector.z += 10;
            break;
        case 'n':
            cerr << "Normal mode activated" << endl;
            mode = NORMAL_MODE;
            break;
        case '-':
            scaleVector = Point(scaleVector.x - 0.1, scaleVector.y - 0.1, scaleVector.z - 0.1);
            break;
        case '+':
            scaleVector = Point(scaleVector.x + 0.1, scaleVector.y + 0.1, scaleVector.z + 0.1);
            break;
        case '1':
            obsPos = {0.0f,0.0f,10.0f};
            up = {0,1,0};
            updateCam = true;
            break;
        case '2':
            obsPos = {0.0f,10.0f,0.0f};
            up = {0,0,-1};
            updateCam = true;
            break;
        case '3':
            obsPos = {10.0f,10.0f,10.0f};
            up = {0,1,0};
            updateCam = true;
            break;
        default:
            refresh = false;
            break;
    }
    
    if(rotateVector.z < 360) rotateVector.z += 360;
    if(rotateVector.z > 360) rotateVector.z -= 360;
    if(updateCam)updateCamera(aWidth, aheigth);
    if(refresh) glutPostRedisplay();
}

