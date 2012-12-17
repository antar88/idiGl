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
    double moonRadius, moonDistance, moonActualAngle, moonRotationAngle;
    Point color;
};

class Planet {
private:
    //translation
    double translationAngle, actualTranslationAngle;
    
    //Rotation
    double rotationAngle, actualRotationAngle;
    
    //moon
    Moon moon;

public:
    Planet();
    Planet(double radius, double rotAngle, Point pos, Point planetColor, double transAngle);
    Planet(double radius, double rotAngle, Point pos, Point planetColor, double transAngle, Moon m);
    
    //main characteristics
    double radis;
    Point color;
    Point position;
    
    //Translation
    double applyTranslate();
    double getTranslationAngle();
    
    //Rotation
    double applyRotate();
    double getRotationAngle();
    
    //Moon
    bool hasMoon();
    void drawMoon();
};

#endif /* defined(__IDIGL__planet__) */
