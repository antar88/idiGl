//
//  planet.cpp
//  IDIGL
//
//  Created by Antar - SSD on 10/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#include "planet.h"
#include <math.h>

//Main init
Planet::Planet() {
    radis=0.1f;
    color = Point(0.f,0.f,0.f);
    position = Point(0.f,0.f,0.f);
    
    rotationAngle = 1.f;
    actualRotationAngle = 0;
    
    translationAngle = 1.f;
    actualTranslationAngle = 0;
    
    moon = {0.f,0.f,0.f, 0.f};
}

//Init without moon
Planet::Planet(float radius, float rotAngle, Point pos, Point planetColor, float transAngle) {
    radis= radius;
    position = pos;
    color = planetColor;
    
    rotationAngle = rotAngle;
    translationAngle = transAngle;
    actualRotationAngle = actualTranslationAngle = 0.f;
    
    moon = {0.f, 0.f, 0.f, 0.f};
}

//Init with Moon
Planet::Planet(float radius, float rotAngle, Point pos, Point planetColor, float transAngle, Moon m) {
    radis= radius;
    position = pos;
    color = planetColor;
    
    rotationAngle = rotAngle;
    translationAngle = transAngle;
    actualTranslationAngle = actualRotationAngle = 0;
    
    moon = m;
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
    if(moon.moonRadius != 0) return true;
    return false;
}

void Planet::drawMoon() {
    if(moon.moonRadius != 0) {
        glPushMatrix();
        
        //translació
        moon.moonActualAngle += moon.moonRotationAngle;
        if(moon.moonActualAngle > 360) moon.moonActualAngle -= 360;
        glRotated(moon.moonActualAngle, 0, 1, 0);
        
        //posicionament dels planetes
        float dis = sqrt(radis*radis);
        glTranslatef(dis+moon.moonDistance , 0.0f, dis+moon.moonDistance);
        
        //posicionem els planetes mirant cap a dalt
        glRotated(-90, 1, 0, 0);
        
        //Rotació
        //glRotated(planets[i].applyRotate(), 0, 0, 1);
        
        //Carreguem l'esfera i la pintem
        glColor3f(moon.color.x, moon.color.y, moon.color.z);
        glutWireSphere(moon.moonRadius, 20, 10);
        
        glPopMatrix();
    }
}

float Planet::getRotationAngle() {
    return rotationAngle;
}

float Planet::getTranslationAngle() {
    return translationAngle;
}