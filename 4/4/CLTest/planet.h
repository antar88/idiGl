//
//  planet.h
//  IDIGL
//
//  Created by Antar - SSD on 10/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#ifndef __IDIGL__planet__
#define __IDIGL__planet__

#include <iostream>
#include "includes.h"

struct Moon {
    float moonRadius;
    float moonDistance;
    float moonActualAngle;
    float moonRotationAngle;
    Point color;
};

class Planet {
private:
    //translation
    float translationAngle;
    float actualTranslationAngle;
    
    //Rotation
    float rotationAngle;
    float actualRotationAngle;
    
    //moon
    Moon moon;

public:
    Planet();
    Planet(float radius, float rotAngle, Point pos, Point planetColor, float transAngle);
    Planet(float radius, float rotAngle, Point pos, Point planetColor, float transAngle, Moon m);
    
    //main characteristics
    float radis;
    Point color;
    Point position;
    
    //Translation
    float applyTranslate();
    float getTranslationAngle();
    
    //Rotation
    float applyRotate();
    float getRotationAngle();
    
    //Moon
    bool hasMoon();
    void drawMoon();
};

#endif /* defined(__IDIGL__planet__) */
