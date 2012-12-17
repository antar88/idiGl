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
        Object("a3dbass.obj",Point(0,0,0))
    };
}

void Scene::drawScene() {
    for (int i = 0; i < objects.size(); ++i) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST);
        objects[i].render();
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

