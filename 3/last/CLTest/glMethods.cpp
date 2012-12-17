//
//  glMethods.cpp
//  CLTest
//
//  Created by Antar - SSD on 08/12/12.
//  Copyright (c) 2012 Àlex Vergara. All rights reserved.
//

#include "glMethods.h"

//globals
static int mode = NORMAL_MODE;
static double aWidth = SCREEN_W, aheigth = SCREEN_H;
static Scene planets = Scene();
static ContainSphere contSphere = planets.calculateSphere();

//Cams
static Cam axoCam = Cam(CAM_MOVEMENT_LOOKAT,Point(0.f,0.f,2.f), Point(0.f,1.f,0.f), Point (0,0,0), Point (0,0,0), Point (0,0,0));
static Cam prespectiveCam = Cam(CAM_MOVEMENT_LOOKAT, Point(0.f,0.f,2.f), Point(0.f,1.f,0.f), Point (0,0,0), Point (0,0,0), Point (0,0,0), contSphere, SCREEN_W, SCREEN_H);
static int cam = AXONOMETRIC_CAM;
static int camMov = CAM_MOVEMENT_LOOKAT;
static int zoomMode = CAM_ZOOM_FOVYORTHO;

//mouse
static int xO, yO;


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
//    Fly throught
//    if(cam == PRESPECTIVE_CAM) prespectiveCam.rotateCam(Point(-0.1, 0, 0), aWidth, aheigth);

    
    //Clear Zone
    glClearColor(0.0 , 0.0, 0.0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Drawing Zone
    planets.drawScene();
    planets.drawAxes();
    
    //End zone
    glutSwapBuffers();
    
}

void reshape(int x, int y) {
    glViewport(0,0,x,y);
    if (cam == AXONOMETRIC_CAM) axoCam.updateCamera(aWidth, aheigth);
    else prespectiveCam.updateCamera(aWidth, aheigth);
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
    if(type) { //Clic Out
        mode = NORMAL_MODE;
    }
    else { //Clic In
        xO = xClic;
        yO = yClic;
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) mode = ZOOM_MODE;
        else if (glutGetModifiers() == GLUT_ACTIVE_ALT) mode = PAN_MODE;
        camMov = CAM_MOVEMENT_EULER;
    }
}

void moveCam(Point p) {
    if(cam == AXONOMETRIC_CAM) axoCam.moveCam(p, aWidth, aheigth);
    else prespectiveCam.moveCam(p, aWidth, aheigth);
}

void rotateCam (Point p) {
    if(cam == AXONOMETRIC_CAM) axoCam.rotateCam(p, aWidth, aheigth);
    else prespectiveCam.rotateCam(p, aWidth, aheigth);
}

void zoomCam(double z) {
    if(cam == AXONOMETRIC_CAM) axoCam.applyZoom(z, aWidth, aheigth);
    else prespectiveCam.applyZoom(z, aWidth, aheigth);
}

void paintModeCam(int paintMode) {
    if(cam == AXONOMETRIC_CAM) axoCam.paintMode = paintMode;
    else prespectiveCam.paintMode = paintMode;
}


void mouseMovement(int xMouse, int yMouse) {
    Point rotate = {0.0,0.0,0.0};
    switch (mode) {
        case ZOOM_MODE:
            double z;
            if((yO - yMouse) > 5) z = -0.1;
            else if((yO - yMouse) < -5) z = 0.1;
            else z = 0;
            
            if(zoomMode == CAM_ZOOM_MOVEMENT) moveCam(Point(0.0,0.0,z));
            else zoomCam(z);
            break;
        case PAN_MODE:
            double x,y;
            if((yO - yMouse) > 2) y = -0.08;
            else if((yO - yMouse) < -2) y = 0.08;
            else y = 0.0;
            
            if((xO - xMouse) > 2) x = 0.08;
            else if((xO - xMouse) < -2) x = -0.08;
            else x = 0.0;
            
            moveCam(Point(x,y,0.0));
            
            break;
        default:
            if (abs(xMouse - xO) > 5 and (xMouse - xO) > 0) rotate.y = -3.0;
            else if (abs(xMouse - xO) > 5) rotate.y = 3.0;
            
            if (abs(yMouse - yO) > 5 and (yMouse - yO) > 0) rotate.x = 3.0;
            else if(abs(yMouse - yO) > 5) rotate.x = -3.0;
            break;
    }
    
    if(rotate.x != 0.0 or rotate.y != 0.0 or rotate.z != 0.0) {
        rotateCam(rotate);
        glutPostRedisplay();
    }
    xO = xMouse;
    yO = yMouse;    
}

void keyboardSpecialKeysInteraction(int key, int xMouse, int yMouse) {

    bool refresh, updateCam = true;
    Point trans = Point(0.f, 0.f, 0.f);
    switch (key) {
        case GLUT_KEY_UP:
            trans.y -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            trans.x -= 0.1;
            break;
        case GLUT_KEY_DOWN:
            trans.y += 0.1;
            break;
        case GLUT_KEY_LEFT:
            trans.x += 0.1;
            break;
        default:
            refresh = false;
            break;
    }
    if(updateCam) moveCam(trans);
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
            cout << "· e: Change the cam posicionament to Euler transformations" << endl;
            cout << "· z: Change the zoom type: zomm modifing ortho/fovy or move the cam" << endl << endl;
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
            paintModeCam(CAM_MOVEMENT_LOOKAT);
            updateCam = true;
            break;
        case 'e':
            cout << "Changed cam positionament mode to Euler tranformations" << endl;
            paintModeCam(CAM_MOVEMENT_EULER);
            updateCam = true;
            break;
        case 'z':
            if(zoomMode == CAM_ZOOM_FOVYORTHO) {
                zoomMode = CAM_ZOOM_MOVEMENT;
                cout << "Zoom mode changed to 'moving the cam'" << endl;
            }
            else {
                zoomMode = CAM_ZOOM_FOVYORTHO;
                cout << "Zoom mode changed to 'modifying the fovy/glortho'" << endl;
            }
            updateCam = true;
            break;
        case '1':
            cout << "Changed cam position 1(0,0,2)" << endl;
            axoCam = Cam(CAM_MOVEMENT_LOOKAT,Point(0.0,0.0,2.0), Point(0.0,1.0,0.0), Point (0,0,0), Point (0,0,0), Point (0,0,0));
            prespectiveCam = Cam(CAM_MOVEMENT_LOOKAT, Point(0.0,0.0,2.0), Point(0.0,1.0,0.0), Point (0,0,0), Point (0,0,0), Point (0,0,0), contSphere, SCREEN_W, SCREEN_H);
            updateCam = true;
            break;
        case '2':
            cout << "Changed cam position 2(0,2,0)" << endl;
            axoCam = Cam(CAM_MOVEMENT_LOOKAT,Point(0.0,2.0,0.0), Point(0.0,0.0,-1.0), Point (0,0,0), Point (0,0,0), Point (0,0,0));
            prespectiveCam = Cam(CAM_MOVEMENT_LOOKAT, Point(0.0,2.0,0.0), Point(0.0,0.0,-1.0), Point (0,0,0), Point (0,0,0), Point (90.0,0.0,0.0), contSphere, SCREEN_W, SCREEN_H);
            updateCam = true;
            break;
        case '3':
            cout << "Changed cam position 3(2,2,2)" << endl;
            axoCam = Cam(CAM_MOVEMENT_LOOKAT,Point(1.0,1.0,1.0), Point(0,1,0), Point (0,0,0), Point (0,0,0), Point (0,0,0));
            prespectiveCam = Cam(CAM_MOVEMENT_LOOKAT, Point(1.0,1.0,1.0), Point(0,1,0), Point (0,0,0), Point (0,0,0), Point (45.0,45.0,0.0), contSphere, SCREEN_W, SCREEN_H);
            updateCam = true;
            break;
        default:
            
            refresh = false;
            break;
    }
    
    if(updateCam) {
       if(cam == AXONOMETRIC_CAM) axoCam.updateCamera(aWidth, aheigth);
        else prespectiveCam.updateCamera(aWidth, aheigth);
    }
    if(refresh) glutPostRedisplay();
}

