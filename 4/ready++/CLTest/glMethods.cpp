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
static Scene scene = Scene();
static ContainSphere contSphere = scene.calculateSphere();

//Cams
static Cam camera = Cam(CAM_MOVEMENT_LOOKAT, Point (0,1,0), Point (0,0,0), contSphere, SCREEN_W, SCREEN_H);
static int zoomMode = CAM_ZOOM_FOVYORTHO;
static int lightMode = GL_FILL;

//mouse
static int xO, yO;


void firstPaint(void)
{
    //Clear Zone
    glClearColor(0.0 , 0.0, 0.0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set Up Enables Only first time
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    //Cam Set Up
    camera.updateCamType(aWidth, aheigth);
    camera.updateCamPos();
    
    //Drawing Zone
    scene.setUpLights();
    scene.drawScene(lightMode);
    scene.drawExam();
    //scene.drawAxes();
    
    contSphere = scene.calculateSphere();
    camera.updateCamSphere(contSphere, aWidth, aheigth);
    
    //End zone
    glutSwapBuffers();
    
}

void refresh(void)
{
    //Clear Zone
    glClearColor(0.0 , 0.0, 0.0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Drawing Zone
    //scene.setUpLights(); // si la llum és dinàmica
    scene.drawScene(lightMode);
    scene.drawExam();
    //scene.drawAxes();
    
    //End zone
    glutSwapBuffers();
    
}

void reshape(int x, int y) {
    glViewport(0,0,x,y);
    camera.updateCamType(aWidth, aheigth);
    glutPostRedisplay();
    aWidth = x;
    aheigth = y;
}

void mouseInteraction(int mouseButton, int type, int xClic, int yClic) {
    if(type) { //Clic Out
        mode = NORMAL_MODE;
    }
    else { //Clic In
        xO = xClic;
        yO = yClic;
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) mode = ZOOM_MODE;
        else if (glutGetModifiers() == GLUT_ACTIVE_ALT) mode = PAN_MODE;
    }
}

void mouseMovement(int xMouse, int yMouse) {
    Point rotate = {0.0,0.0,0.0};
    switch (mode) {
        case ZOOM_MODE:
            double z;
            if((yO - yMouse) > 0) z = -1;
            else if((yO - yMouse) < 0) z = 1;
            else z = 0;
            
            if(zoomMode == CAM_ZOOM_MOVEMENT) {
                if(camera.type == AXONOMETRIC_CAM) cerr << "Axonometric camera with fovy change zoom type has no effect" << endl;
                else camera.moveCam(Point(0.0,0.0,z), aWidth, aheigth);
            }
            else camera.applyZoom(z, aWidth, aheigth);
            break;
        case PAN_MODE:
            double x,y;
            if((yO - yMouse) > 2) y = -1;
            else if((yO - yMouse) < -2) y = 1;
            else y = 0.0;
            
            if((xO - xMouse) > 2) x = 1;
            else if((xO - xMouse) < -2) x = -1;
            else x = 0.0;
            
            camera.applyPAN(Point(x,y,0.0)); 
            
            break;
        default:
            if (abs(xMouse - xO) > 5 and (xMouse - xO) > 0) rotate.y = -3.0;
            else if (abs(xMouse - xO) > 5) rotate.y = 3.0;
            
            if (abs(yMouse - yO) > 5 and (yMouse - yO) > 0) rotate.x = 3.0;
            else if(abs(yMouse - yO) > 5) rotate.x = -3.0;
            break;
    }
    
    if(rotate.x != 0.0 or rotate.y != 0.0 or rotate.z != 0.0) {
        camera.rotateCam(rotate, aWidth, aheigth);
        glutPostRedisplay();
    }
    xO = xMouse;
    yO = yMouse;    
}

void keyboardSpecialKeysInteraction(int key, int xMouse, int yMouse) {

    bool refresh, updateCam = true;
    Point trans = Point(0.0, 0.0, 0.0);
    switch (key) {
        case GLUT_KEY_UP:
            trans.y -= 1;
            break;
        case GLUT_KEY_RIGHT:
            trans.x = 1;
            break;
        case GLUT_KEY_DOWN:
            trans.y += 1;
            break;
        case GLUT_KEY_LEFT:
            trans.x -= 1;
            break;
        default:
            refresh = false;
            break;
    }
    if(updateCam) camera.moveCam(trans, aWidth, aheigth);
    if(refresh) glutPostRedisplay();
} 

void keyboardInteraction(unsigned char key, int xMouse, int yMouse) {
    
    bool refresh = true;
    bool updateCam = false;
    ContainSphere c;
                std::string nomO;
    switch (key) {
        case 'h':
            cout << "This are the keys avilable:" << endl;
            cout << "-------------------------- KEYBOARD --------------------------" << endl;
            cout << "· ESC: quit the app" << endl;
            cout << "· UP / DOWN: move the cam in the y axis" << endl;
            cout << "· LEFT / RIGHT: move the camera in the x axis" << endl;
            cout << "· x / p: Change the cam type to axonometric / perspective" << endl;
            cout << "· a / e: Change the cam posicionament glLookAt / euler transformations" << endl;
            cout << "· f / l: Change the paint mode fill or lines" << endl;
            cout << "· z: Change the zoom type: zomm modifing ortho/fovy or move the cam" << endl;
            cout << "· c: Load an external .obj" << endl;
            cout << "· 1: Move the cam to the position (0,0,distance)" << endl;
            cout << "· 2: Move the cam to the position (0,distance,0)" << endl << endl;
            cout << "--------------------------- MOUSE ----------------------------" << endl;
            cout << "· Move with left clic: change the X / Y angle of the camera" << endl;
            cout << "· SHIFT + movement: zoom" << endl;
            cout << "· ALT + movement: apply PAN" << endl;
            break;
        case 27:
            exit(0);
            break;
        case 'x':
            cout << "Changed cam to axonometric" << endl;
            camera.type = AXONOMETRIC_CAM;
            updateCam = true;
            break;
        case 'p':
            cout << "Changed cam to prespective" << endl;
            camera.type = PRESPECTIVE_CAM;
            updateCam = true;
            break;
        case 'a':
            cout << "Changed cam positionament mode to glLookAt" << endl;
            camera.changePaintMode(CAM_MOVEMENT_LOOKAT);
            break;
        case 'e':
            cout << "Changed cam positionament mode to Euler tranformations" << endl;
            camera.changePaintMode(CAM_MOVEMENT_EULER);
            break;
        case 'l':
            cout << "Change Light mode to lines" << endl;
            lightMode = GL_LINE;
            refresh = true;
            break;
        case 'f':
            cout << "Change Light mode to fill" << endl;
            lightMode = GL_FILL;
            refresh = true;
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
        case 'c':
            cout << "Introdueix el nom de l'objecte amb l'extensió: ";
            cin >> nomO;
            cout << "Carregant objecte..." << endl;
            contSphere = scene.carregaObjecte(nomO);
            camera.updateCamSphere( contSphere, aWidth, aheigth);
            break;
        case '1':
            cout << "Changed cam position 1(0,0,X)" << endl;
            camera = Cam(CAM_MOVEMENT_LOOKAT, Point(0.0,1.0,0.0), Point (0,0,0), contSphere, SCREEN_W, SCREEN_H);
            updateCam = true;
            break;
        case '2':
            cout << "Changed cam position 2(0,X,0)" << endl;
            camera = Cam(CAM_MOVEMENT_LOOKAT, Point(0.0,0.0,-1.0), Point (-90,0,0), contSphere, SCREEN_W, SCREEN_H);
            updateCam = true;
            break;
        default:
            refresh = false;
            break;
    }
    
    if(updateCam) camera.updateCamType(aWidth, aheigth);
    if(refresh) glutPostRedisplay();
}