//
//  scene.cpp
//  IDIGL
//
//  Created by Antar - SSD on 10/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#include "scene.h"


Scene::Scene() {
    objects = {
        Object("porsche.obj")
    };
}

void Scene::drawScene(int lightMode) {
    for (int i = 0; i < objects.size(); ++i) {
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST);
        objects[i].render(lightMode);
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
    glEnable(GL_LIGHTING);
}

ContainSphere Scene::calculateSphere() {
    ContainSphere c;
    Point max, min;
    max = min = Point(0.0,0.0,0.0);
    for (int i = 0; i < objects.size() ; ++i) {
        Point bmax = objects[i].box.max;
        Point bmin = objects[i].box.min;
        if(bmax.x > max.x) max.x = bmax.x;
        if(bmax.y > max.y) max.y = bmax.y;
        if(bmax.z > max.z) max.z = bmax.z;
        
        if(bmin.x < min.x) min.x = bmin.x;
        if(bmin.y < min.y) min.y = bmin.y;
        if(bmin.z < min.z) min.z = bmin.z;
    }
    cerr << "max(" << max.x << ", " << max.y << ", " << max.z << ") " << "  min(" << min.x << ", " << min.y << ", " << min.z << ") " << endl;
    c.centre = {(max.x+min.x)/2.0, (max.y+min.y)/2.0, (max.z+min.z)/2.0};
    c.radi = max.distanceToAnotherPoinr(c.centre);
    return c;
}

void Scene::setUpLights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
//    GLfloat ambLight0[ ] = {1.f, 1.f, 1.f, 1.0f};
//    GLfloat diffLight0[ ] = {1.f, 01.f, 1.f, 1.0f};
//    GLfloat specLight0[ ] = {1.0f, 1.0f, 1.0f, 1.0f};
//    GLfloat pos[ ] = {10, 0, 0, 1.0f};
//    glLightfv(GL_LIGHT0, GL_AMBIENT, ambLight0);
//    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffLight0);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, specLight0);
//    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    
}
