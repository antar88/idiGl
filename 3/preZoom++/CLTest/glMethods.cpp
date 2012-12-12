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

//Cam properties
static Point rotateVector, translateCamVector, camEulerInitAngles  = Point (0,0,0);
static int cam = AXONOMETRIC_CAM;
static int camMov = CAM_MOVEMENT_LOOKAT;
static Point obsPos = Point(0.f,0.f,2.f);
static Point up = Point(0.f,1.f,0.f);


//globals
static int mode = NORMAL_MODE;
static float aWidth = SCREEN_W, aheigth = SCREEN_H;
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
    planets.drawAxes();
    
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
    planets.drawAxes();
    
    //End zone
    glutSwapBuffers();
    
}

void updateCamera(float x, float y) {
    GLfloat rawX = x / SCREEN_W;
    GLfloat rawY = y / SCREEN_H;
    GLfloat minRawXY = min(rawX,rawY);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //Cam Type
    if(cam == AXONOMETRIC_CAM) glOrtho(-rawX/minRawXY,rawX/minRawXY,-rawY/minRawXY,rawY/minRawXY,0.1,30.0);
    else if (cam == PRESPECTIVE_CAM) gluPerspective(55.0, x/y, 0.1, 30);
    
    //Cam posicionament type
    if(camMov == CAM_MOVEMENT_LOOKAT) gluLookAt(obsPos.x+translateCamVector.x, obsPos.y+translateCamVector.y, obsPos.z+translateCamVector.z, translateCamVector.x, translateCamVector.y, translateCamVector.z, up.x, up.y, up.z);
    else {
        
        GLdouble m[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, m);
        glRotated(camEulerInitAngles.x, 1, 0, 0);
        glRotated(-camEulerInitAngles.y, 0, 1, 0);
        glRotated(-camEulerInitAngles.z, 0, 0, 1);
        glMultMatrixd(m);
        glTranslatef(-obsPos.x, -obsPos.y, -obsPos.z);
        glTranslatef(-translateCamVector.x, -translateCamVector.y, -translateCamVector.z);
    }
    
    //cam movement
    GLdouble m[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, m);
    glRotated(rotateVector.x, 1, 0, 0);
    glRotated(-rotateVector.y, 0, 1, 0);
    glMultMatrixd(m);
   
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(int x, int y) {
    glViewport(0,0,x,y);
    updateCamera(aWidth, aheigth);
    glutPostRedisplay();
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
            
            if (abs(yMouse - yO) > 5 and (yMouse - yO) > 0) rotateVector.x += 3;
            else if(abs(yMouse - yO) > 5)rotateVector.x -= 3;
            else refresh2 = false;
            break;
    }
    
    if(rotateVector.x > 360) rotateVector.x -= 360;
    if(rotateVector.x < 360) rotateVector.x += 360;
    if(rotateVector.y < 360) rotateVector.y += 360;
    if(rotateVector.y > 360) rotateVector.y -= 360;
    if(refresh or refresh2) {
        updateCamera(aWidth , aheigth);
        glutPostRedisplay();
    }
    xO = xMouse;
    yO = yMouse;    
}

void keyboardSpecialKeysInteraction(int key, int xMouse, int yMouse) {
    bool refresh, updateCam = true;
    switch (key) {
        case GLUT_KEY_UP:
            translateCamVector.y += 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            translateCamVector.x += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            translateCamVector.y -= 0.1f;
            break;
        case GLUT_KEY_LEFT:
            translateCamVector.x -= 0.1f;
            break;
        default:
            refresh = false;
            break;
    }
    if(updateCam) updateCamera(aWidth, aheigth);
    if(refresh) glutPostRedisplay();
} 

void keyboardInteraction(unsigned char key, int xMouse, int yMouse) {

    bool refresh = true;
    bool updateCam = false;
    switch (key) {
        case 'h':
            cout << "This are the keys avilable:" << endl;
            cout << "-------------------------- KEYBOARD --------------------------" << endl;
            cout << "· ESC: quit the app" << endl;
            cout << "· UP / DOWN: move the cam in the y axis" << endl;
            cout << "· LEFT / RIGHT: move the camera in the x axis" << endl;
            cout << "· 1: Move the cam to the position (0,0,2)" << endl;
            cout << "· 2: Move the cam to the position (0,2,0)" << endl;
            cout << "· 3: Move the cam to the position (2,2,2)" << endl;
            cout << "· x: Change the cam type to axonometric" << endl;
            cout << "· p: Change the cam type to perspective" << endl;
            cout << "· a: Change the cam posicionament to glLookAt" << endl;
            cout << "· e: Change the cam posicionament to Euler transformations" << endl << endl;
            cout << "--------------------------- MOUSE ----------------------------" << endl;
            cout << "· Move with left clic: change the X / Y angle of the camera" << endl;
            break;
        case 27:
            exit(0);
            break;
        case 'x':
            cout << "Changed cam to axonometric" << endl;
            cam = AXONOMETRIC_CAM;
            updateCam = true;
            break;
        case 'p':
            cout << "Changed cam to prespective" << endl;
            cam = PRESPECTIVE_CAM;
            updateCam = true;
            break;
        case 'n':
            cerr << "Normal mode activated" << endl;
            mode = NORMAL_MODE;
            break;
        case 'a':
            cout << "Changed cam positionament mode to glLookAt" << endl;
            camMov = CAM_MOVEMENT_LOOKAT;
            updateCam = true;
            break;
        case 'e':
            cout << "Changed cam positionament mode to Euler tranformations" << endl;
            camMov = CAM_MOVEMENT_EULER;
            updateCam = true;
            break;
        case 'w':
            translateCamVector.z -= 0.1f;
            updateCam = true;
            break;
        case 's':
            translateCamVector.z += 0.1f;
            updateCam = true;
            break;
        case '1':
            cout << "Changed cam position 1(0,0,2)" << endl;
            obsPos = {0.0f,0.0f,2.0f};
            up = {0,1,0};
            updateCam = true;
            rotateVector = {0.f,0.f,0.f};
            if(camMov == CAM_MOVEMENT_EULER) camEulerInitAngles = {0.f,0.f,0.f};
            break;
        case '2':
            cout << "Changed cam position 2(0,2,0)" << endl;
            obsPos = {0.0f,2.0f,0.0f};
            up = {0,0,-1};
            updateCam = true;
            if(camMov == CAM_MOVEMENT_EULER) camEulerInitAngles = {90.f,0.f,0.f};
            rotateVector = {0.f,0.f,0.f};
            break;
        case '3':
            cout << "Changed cam position 3(2,2,2)" << endl;
            obsPos = {1.0f,1.0f,1.0f} ;
            up = {0,1,0};
            updateCam = true;
            if(camMov == CAM_MOVEMENT_EULER) camEulerInitAngles = {45.f,45.f,0.f};
            rotateVector = {0.f,0.f,0.f};
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

