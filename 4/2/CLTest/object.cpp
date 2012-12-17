//
//  object.cpp
//  IDIGL
//
//  Created by Antar - SSD on 16/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#include "object.h"
#include <iostream>
using namespace std;

Object::Object() {
    
}

Object::Object(std::string nomM) {
    model.load(nomM);
    
    
    double lX, lY, lZ, hX, hY, hZ;
    lX = lY = lZ = INT_MAX;
    hX = hY = hZ = INT_MIN;
    for (int i = 0; i*3 < model.vertices().size(); ++i) {
        lX = std::min(lX,model.vertices()[i*3+0]);
        lY = std::min(lY,model.vertices()[i*3+1]);
        lZ = std::min(lZ,model.vertices()[i*3+2]);
        hX = std::max(hX,model.vertices()[i*3+0]);
        hY = std::max(hY,model.vertices()[i*3+1]);
        hZ = std::max(hZ,model.vertices()[i*3+2]);
    }
    
    box = {Point(hX,hY,hZ),Point(lX,lY,lZ), Point((hX+lX)/2,(hY+lY)/2,(hZ+lZ)/2)};
    pos = Point((hX+lX)/2,(hY+lY)/2,(hZ+lZ)/2);
    
    
}

void Object::render(int lm) {
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    
    glPolygonMode(GL_FRONT_AND_BACK, lm);
    glBegin(GL_TRIANGLES);
    
    int lastMaterial = -1;
    for (int i = 0; i < model.faces().size(); ++i) {
        Face f = model.faces()[i];
        if (f.mat != lastMaterial) {
            //std::cerr << "Redefinig mat!" << std::endl;
            Material mat = model.materials[f.mat];
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat.ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat.diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat.specular);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat.shininess);
            lastMaterial = f.mat;
        }
        
        glNormal3dv(f.normalC);
        
        for (int j = 0; j < 3; ++j) {
            GLdouble x = model.vertices()[f.v[j]+0];
            GLdouble y = model.vertices()[f.v[j]+1];
            GLdouble z = model.vertices()[f.v[j]+2];
            glVertex3d(x, y, z);
        }
    }
    
    glEnd();
    glPopMatrix();
}