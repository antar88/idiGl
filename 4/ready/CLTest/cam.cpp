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

Cam::Cam(int mode, Point up2, Point rot, ContainSphere c) {
    paintMode = mode;
    type = AXONOMETRIC_CAM;
    
    up = {up2.x, up2.y, up2.z};
    rotateVector = {rot.x, rot.y, rot.z};
    vrp = {c.centre.x, c.centre.y, c.centre.z};
    
    distance = 2*c.radi;
    pos = {0,0,distance};

    fovy = zomm = 1.0;
}

Cam::Cam(int mode, Point up2, Point rot, ContainSphere c, double with, double heigth) {
    paintMode = mode;
    type = PRESPECTIVE_CAM;
    
    up = {up2.x, up2.y, up2.z};
    rotateVector = {rot.x, rot.y, rot.z};
    vrp = {c.centre.x, c.centre.y, c.centre.z};

    distance = 2*c.radi;
   
    pos = {0,0,distance};
    
    fovy = 2.0*(atan(c.radi/distance)*180.0/M_PI);
    
    if (with/heigth < 1 ) {
        fovy = (fovy/2)*M_PI/180.;
        double ratio = with/heigth;
        fovy = 2*(atan(tan(fovy)/ratio))*180./M_PI;
    }
    
    zomm = 1.0;
}

void Cam::updateCamSphere(ContainSphere c, double with, double heigth) {
    vrp = {c.centre.x, c.centre.y, c.centre.z};
    distance = 2*c.radi;
    pos = {0,0,distance};
    fovy = 2.0*(atan(c.radi/distance)*180.0/M_PI);
    if (with/heigth < 1 ) {
        fovy = (fovy/2)*M_PI/180.;
        double ratio = with/heigth;
        fovy = 2*(atan(tan(fovy)/ratio))*180./M_PI;
    }
    updateCamPos();
    updateCamType(with, heigth);
}

void Cam::updateCamType(double x, double y) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //aspect ratio
    GLdouble ratio = x / y;
    double aux = 0;
    if(x > y) aux = ratio*((distance/2) *zomm);
    else if (x < y) aux = ratio*((distance/2) *zomm);

    //Cam Type
    if(type == AXONOMETRIC_CAM) glOrtho(((-distance/2) *zomm) -aux/2,((distance/2)*zomm)+aux/2,(-(distance/2)*zomm),((distance/2)*zomm),0.1,100.0);
    else if (type == PRESPECTIVE_CAM) gluPerspective(fovy+zomm, ratio, 0.1, 2*distance);
    glMatrixMode(GL_MODELVIEW);
}

void Cam::updateCamPos() {
    glLoadIdentity();
    
    //Cam posicionament type
    if(paintMode == CAM_MOVEMENT_LOOKAT) {
        GLdouble m[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, m);
        gluLookAt(pos.x, pos.y, pos.z, vrp.x, vrp.y, vrp.z, up.x, up.y, up.z);
        glRotated(-rotateVector.z, 0, 0, 1);
        glRotated(rotateVector.x, 1, 0, 0);
        glRotated(-rotateVector.y, 0, 1, 0);
        
        glMultMatrixd(m);
    }
    else {
        
        GLdouble m[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, m);
        glTranslated(-pos.x,-pos.y, -pos.z);
        glRotated(-rotateVector.z, 0, 0, 1);
        glRotated(rotateVector.x, 1, 0, 0);
        glRotated(-rotateVector.y, 0, 1, 0);
        glTranslated(-vrp.x, -vrp.y, -vrp.z);
        glMultMatrixd(m);
        
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
    
    updateCamPos();
}

void Cam::applyZoom(double z, double aWidth, double aheigth) {
    if(type==PRESPECTIVE_CAM)zomm += z;
    else zomm += (z*0.1);
    updateCamType(aWidth, aheigth);
}

void Cam::changePaintMode(int pm) {
    paintMode = pm;
    updateCamPos();
}

void Cam::applyPAN(Point dist ) {
    vrp.x += dist.x;
    vrp.y += dist.y;
    vrp.z += dist.z;
    
    pos.x += dist.x;
    pos.y += dist.y;
    pos.z += dist.z;
    
    updateCamPos();
}

