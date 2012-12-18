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
#include "planet.h"
#include <vector>
#include <math.h>

struct ContainSphere {
    Point centre;
    float radi;
};

class Scene {

    std::vector<Planet> planets;
    
public:
    Scene();
    void drawScene();
    void drawAxes();
    ContainSphere calculateSphere();
};


#endif /* defined(__IDIGL__scene__) */
