//
//  scene.cpp
//  IDIGL
//
//  Created by Antar - SSD on 10/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#include "scene.h"


Scene::Scene() {
    planets = {
        Planet(0.15, 0.01, Point(0.0,0.0), Point(0.8,0.8,0.0), 0),
        
        Planet(0.05, 0.05, Point(0.2, 0.0, 0.2) , Point(0.2,0.7,0.1), 0.03),
        
        Planet(0.08, 0.03, Point(0.4,0.0,0.4), Point(0.8,0.0,0.0), 0.02, Moon{0.01, 0.001, 0.0, 0.21, Point(104.0, 104.0, 104.0)}),
        
        Planet(0.1, 0.02, Point(-0.6, 0.0, 0.6), Point(0.8,0.8,0.8), 0.01),
    };
}

void Scene::drawScene() {
    for (int i = 0; i < planets.size(); ++i) {
        
        Point trans = planets[i].position;
        Point col = planets[i].color;
        planets[i].applyTranslate();

        glPushMatrix();
        
        //Efecte de translació en vers al sol
        glRotated(planets[i].applyTranslate(), 0, 1, 0);
        
        //posicionament del planeta
        glTranslated(trans.x, trans.y, trans.z);
        
        //Moon
        planets[i].drawMoon();
        
        //posicionem els planetes mirant cap a dalt
        glRotated(-90, 1, 0, 0);
        
        //Rotació
        glRotated(planets[i].applyRotate(), 0, 0, 1);
        
        //Carreguem l'esfera i la pintem
        glColor3d(col.x, col.y, col.z);
        glutWireSphere(planets[i].radis, 20, 10);
        
        glPopMatrix();
        
    }
}
void Scene::drawAxes() {
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
}

ContainSphere Scene::calculateSphere() {
    ContainSphere c;
    Point max;
    for (int i = 0; i < planets.size() ; ++i) {
        Point p = planets[i].position;
        if(i == 0) c.centre = max = p;
        else {
            c.centre = {(c.centre.x+p.x)/2.0, (c.centre.y+p.y)/2.0, (c.centre.z+p.z)/2.0};
            if(p.x > max.x) max.x = p.x;
            if(p.y > max.y) max.y = p.y;
            if(p.z > max.z) max.z = p.z;
        }
    }
    c.radi = max.distanceToAnotherPoinr(c.centre);
    return c;
}

