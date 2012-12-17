//
//  cam.h
//  IDIGL
//
//  Created by Antar - SSD on 14/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#ifndef __IDIGL__cam__
#define __IDIGL__cam__

#include <iostream>
using namespace std;
#include <math.h>
#include "includes.h"


class Cam {
    //All cams
    int type;
    Point pos, up, rotateVector, vrp, eulerInitAngles;
    double zomm;
    int paintMode;
    
    //Prespective
    double fovy, distance;
    
public:
    
    Cam();
    Cam(int mode, Point pos2, Point up2, Point rot, Point trans, Point euler);
    Cam(int mode, Point up2, Point rot, ContainSphere c, double with, double heigth);
    
    void updateCamType(double x, double y);
    void updateCamPos();
    void changePaintMode(int pm);
    
    void moveCam(Point dist, double aWidth, double aheigth);
    void rotateCam(Point angles, double aWidth,double  aheigth);
    void applyZoom(double z, double aWidth, double aheigth);
};


#endif /* defined(__IDIGL__cam__) */
