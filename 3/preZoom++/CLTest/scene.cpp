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
        Planet(0.15f, 0.01f, Point(0.0f,0.0f), Point(0.8f,0.8f,0.0f), 0),
        
        Planet(0.05f, 0.05f, Point(0.2f, 0.0f, 0.2f) , Point(0.2f,0.7f,0.1f), 0.03f),
        
        Planet(0.08f, 0.03f, Point(0.4f,0.0f,0.4f), Point(0.8f,0.f,0.0f), 0.02f, Moon{0.01, 0.001, 0.f, 0.21f, Point(104.f, 104.f, 104.f)}),
        
        Planet(0.1f, 0.02f, Point(-0.6f, 0.0f, 0.6f), Point(0.8f,0.8f,0.8f), 0.01f),
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
        glTranslatef(trans.x, trans.y, trans.z);
        
        //Moon
        planets[i].drawMoon();
        
        //posicionem els planetes mirant cap a dalt
        glRotated(-90, 1, 0, 0);
        
        //Rotació
        glRotated(planets[i].applyRotate(), 0, 0, 1);
        
        //Carreguem l'esfera i la pintem
        glColor3f(col.x, col.y, col.z);
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
