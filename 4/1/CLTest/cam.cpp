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

Cam::Cam(int mode, Point pos2, Point up2, Point rot, Point vrp2, Point euler) {
    paintMode = mode;
    type = AXONOMETRIC_CAM;
    pos = {pos2.x, pos2.y, pos2.z};
    up = {up2.x, up2.y, up2.z};
    rotateVector = {rot.x, rot.y, rot.z};
    vrp = {vrp2.x, vrp2.y, vrp2.z};
    eulerInitAngles = {euler.x, euler.y, euler.z};
    fovy = zomm = 0.f;
}


Cam::Cam(int mode, Point up2, Point rot, ContainSphere c, double with, double heigth) {
    paintMode = mode;
    type = PRESPECTIVE_CAM;
    
    up = {up2.x, up2.y, up2.z};
    rotateVector = {rot.x, rot.y, rot.z};
    vrp = {c.centre.x, c.centre.y, c.centre.z};

    distance = 1.5*c.radi;
   
    pos = {-vrp.x,-vrp.y,-distance};
    
    fovy = 2.0*(atan(c.radi/distance)*180.0/M_PI);
    
    if (with/heigth < 1 ) {
        fovy = (fovy/2)*M_PI/180.;
        double ratio = with/heigth;
        fovy = 2*(atan(tan(fovy)/ratio))*180./M_PI;
    }
    
    zomm = 1.f;
    cout << "centre(" <<c.centre.x  << ", " << c.centre.y  << ", " << c.centre.z << ") i radi = " << c.radi << endl;
    cout << "fovy = " << fovy << endl;
}

void Cam::updateCamType(double x, double y) {
    GLdouble rawX = x / SCREEN_W;
    GLdouble rawY = y / SCREEN_H;
    GLdouble minRawXY = min(rawX,rawY);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //Cam Type
    if(type == AXONOMETRIC_CAM) glOrtho((-distance/2) *zomm,(distance/2)*zomm,-(distance/2)*zomm,(distance/2)*zomm,0.1,100.0);
    else if (type == PRESPECTIVE_CAM) gluPerspective(fovy+zomm, x/y, 0.1, 100);
    
    glMatrixMode(GL_MODELVIEW);
}

void Cam::updateCamPos() {
    glLoadIdentity();
    
    //Cam posicionament type
    if(paintMode == CAM_MOVEMENT_LOOKAT) {
        GLdouble m[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, m);
        glRotated(rotateVector.x, 1, 0, 0);
        glRotated(-rotateVector.y, 0, 1, 0);
        glMultMatrixd(m);
        gluLookAt(pos.x, pos.y, pos.z, vrp.x, vrp.y, vrp.z, up.x, up.y, up.z);
        
    }
    else {
        glTranslated(pos.x, pos.y, pos.z);
        GLdouble m[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, m);
        glRotated(-rotateVector.z, 0, 0, 1);
        glRotated(rotateVector.x, 1, 0, 0);
        glRotated(-rotateVector.y, 0, 1, 0);
        glMultMatrixd(m);
        glTranslated(-vrp.x, -vrp.y, -vrp.z);
        
    }
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
    
    updateCamPos();
    
}

void Cam::moveCam(Point dist, double aWidth, double aheigth){
    //S'ha de mirar cap on es mou exactament
    
    pos.x += dist.x;
    pos.y += dist.y;
    pos.z += dist.z;
    
    vrp.x += dist.x;
    vrp.y += dist.y;
    vrp.z += dist.z;
    
    //cerr << "move cam " <<  translateCamVector.x << " " << translateCamVector.y << " " << translateCamVector.z << endl;
    updateCamPos();
    
}

void Cam::applyZoom(double z, double aWidth, double aheigth) {
    zomm += z;
    updateCamType(aWidth, aheigth);
}

void Cam::changePaintMode(int pm) {
    paintMode = pm;
    updateCamPos();
}

