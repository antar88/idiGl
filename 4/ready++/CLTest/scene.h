//
//  scene.h
//  IDIGL
//
//  Created by Antar - SSD on 10/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//


#ifndef __IDIGL__scene__
#define __IDIGL__scene__

#include <iostream>
using namespace std;
#include "includes.h"
#include "object.h"
#include <vector>
#include <math.h>


class Scene {
    ContainSphere manualDrawsSphere;
    std::vector<Object> objects;
    
public:
    Scene();
    void drawScene(int lightMode);
    void drawAxes();
    void drawExam();
    
    void setUpLights();
    
    ContainSphere calculateSphere();
    ContainSphere recalculaSphere(Point p, ContainSphere c);
    ContainSphere recalculaSphere(ContainSphere nova, ContainSphere c);
    
    ContainSphere carregaObjecte(std::string obj);
};


#endif /* defined(__IDIGL__scene__) */
