//
//  planet.cpp
//  IDIGL
//
//  Created by Antar - SSD on 10/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#include "planet.h"
#include <math.h>

Planet::Planet() {
    radis=0.1f;
    color = Point(0.f,0.f,0.f);
    position = Point(0.f,0.f,0.f);
    
    rotationAngle = 1.f;
    actualRotationAngle = 0;
    
    translationAngle = 1.f;
    actualTranslationAngle = 0;
    
    moonDistance = 0.f;
    moonRadius = 0.f;
}

Planet::Planet(float radius, float rotAngle, Point pos, Point planetColor, float transAngle, float mR, float mD) {
    radis= radius;
    position = pos;
    color = planetColor;
    
    rotationAngle = rotAngle;
    actualRotationAngle = 0;
    
    translationAngle = transAngle;
    actualTranslationAngle = 0;
    
    moonDistance = mD;
    moonRadius = mR;
}

Planet::Planet(float radius, float rotAngle, Point pos, Point planetColor, float transAngle) {
    radis= radius;
    position = pos;
    color = planetColor;
    
    rotationAngle = rotAngle;
    translationAngle = transAngle;
    
    moonDistance = moonRadius = actualRotationAngle = actualTranslationAngle = 0.f;
}

float Planet::applyTranslate() {
    actualTranslationAngle -= translationAngle;
    if(actualTranslationAngle < 0) actualTranslationAngle += 360.0f;
    return actualTranslationAngle;
}

float Planet::applyRotate() {
    actualRotationAngle -= rotationAngle;
    if(actualRotationAngle < 0) actualRotationAngle += 360.0f;
    return actualRotationAngle;
}

bool Planet::hasMoon() {
    if(moonRadius != 0) return true;
    return false;
}

void Planet::drawMoon() {
    if(moonRadius != 0) {
        glPushMatrix();
        
        //translació
        moonRotationAngle += 0.21;
        if(moonRotationAngle > 360) moonRotationAngle -= 360;
        glRotated(moonRotationAngle, 0, 1, 0);
        
        //posicionament dels planetes
        float dis = sqrt(radis*radis);
        glTranslatef(dis+moonDistance , 0.0f, dis+moonDistance);
        
        //posicionem els planetes mirant cap a dalt
        glRotated(-90, 1, 0, 0);
        
        //Rotació
        //glRotated(planets[i].applyRotate(), 0, 0, 1);
        
        //Carreguem l'esfera i la pintem
        glColor3f(102, 102, 102);
        glutWireSphere(moonRadius, 20, 10);
        
        glPopMatrix();
    }
}

float Planet::getRotationAngle() {
    return rotationAngle;
}

float Planet::getTranslationAngle() {
    return translationAngle;
}