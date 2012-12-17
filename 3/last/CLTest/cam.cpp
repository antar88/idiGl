//
//  cam.cpp
//  IDIGL
//
//  Created by Antar - SSD on 14/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#include "cam.h"

Cam::Cam() {
    
}

Cam::Cam(int mode, Point pos2, Point up2, Point rot, Point trans, Point euler) {
    paintMode = mode;
    type = AXONOMETRIC_CAM;
    pos = {pos2.x, pos2.y, pos2.z};
    up = {up2.x, up2.y, up2.z};
    rotateVector = {rot.x, rot.y, rot.z};
    translateCamVector = {trans.x, trans.y, trans.z};
    eulerInitAngles = {euler.x, euler.y, euler.z};
    fovy = zomm = 1.f;
}


Cam::Cam(int mode, Point pos2, Point up2, Point rot, Point trans, Point euler, ContainSphere c, double with, double heigth) {
    paintMode = mode;
    type = PRESPECTIVE_CAM;
    pos = {pos2.x, pos2.y, pos2.z};
    up = {up2.x, up2.y, up2.z};
    rotateVector = {rot.x, rot.y, rot.z};
    translateCamVector = {trans.x, trans.y, trans.z};
    eulerInitAngles = {euler.x, euler.y, euler.z};
    distance = c.centre.distanceToAnotherPoinr(pos2);
    fovy = 2.f*(asin(c.radi/distance)*180./M_PI);
    if (with/heigth < 1) {
        fovy = (fovy/2)*M_PI/180.;
        double ratio = with/heigth;
        fovy = 2*(atan(tan(fovy)/ratio))*180./M_PI;
    }
    zomm = 1.f;
    cout << "centre(" <<c.centre.x  << ", " << c.centre.y  << ", " << c.centre.z << ") i radi = " << c.radi << endl;
    cout << "fovy = " << fovy << endl;
}

void Cam::updateCamera(double x, double y) {
    GLdouble rawX = x / SCREEN_W;
    GLdouble rawY = y / SCREEN_H;
    GLdouble minRawXY = min(rawX,rawY);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //Cam Type
    if(type == AXONOMETRIC_CAM) glOrtho(-rawX/minRawXY*zomm,rawX/minRawXY*zomm,-rawY/minRawXY*zomm,rawY/minRawXY*zomm,0.1,30.0);
    else if (type == PRESPECTIVE_CAM) gluPerspective(fovy+zomm, x/y, 0.1, 30);
    
    //Cam posicionament type
    if(paintMode == CAM_MOVEMENT_LOOKAT) gluLookAt(pos.x+translateCamVector.x, pos.y+translateCamVector.y, pos.z+translateCamVector.z, translateCamVector.x, translateCamVector.y, translateCamVector.z, up.x, up.y, up.z);
    else {
        cerr << "entro" << endl;
        glTranslated(-translateCamVector.x, -translateCamVector.y, -translateCamVector.z);
        GLdouble m[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, m);
        glRotated(eulerInitAngles.x, 1, 0, 0);
        glRotated(-eulerInitAngles.y, 0, 1, 0);
        glRotated(-eulerInitAngles.z, 0, 0, 1);
        glMultMatrixd(m);
        glTranslated(-pos.x, -pos.y, -pos.z);
        
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

void Cam::rotateCam(Point angles, double aWidth, double aheigth) {
    rotateVector.x += angles.x;
    rotateVector.y += angles.y;
    rotateVector.z += angles.z;
    
    
    if(rotateVector.x > 360) rotateVector.x -= 360;
    else if(rotateVector.x < 360) rotateVector.x += 360;
    if(rotateVector.y < 360) rotateVector.y += 360;
    else if(rotateVector.y > 360) rotateVector.y -= 360;
    if(rotateVector.z < 360) rotateVector.z += 360;
    else if(rotateVector.z > 360) rotateVector.z -= 360;
    
    updateCamera(aWidth, aheigth);
    
}

void Cam::moveCam(Point dist, double aWidth, double aheigth){
    //S'ha de mirar cap on es mou exactament
    
    translateCamVector.x += dist.x;
    translateCamVector.y += dist.y;
    translateCamVector.z += dist.z;
    //cerr << "move cam " <<  translateCamVector.x << " " << translateCamVector.y << " " << translateCamVector.z << endl;
    updateCamera(aWidth, aheigth);
    
}

void Cam::applyZoom(double z, double aWidth, double aheigth) {
    if(type == AXONOMETRIC_CAM) zomm += z;
    else zomm += z*15;
    updateCamera(aWidth, aheigth);
}

