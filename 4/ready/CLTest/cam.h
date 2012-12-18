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
    
    Point pos, up, rotateVector, vrp;
    double zomm;
    int paintMode;
    
    //Prespective
    double fovy, distance;
    
public:
    int type;
    Cam();
    Cam(int mode, Point up2, Point rot, ContainSphere c);
    Cam(int mode, Point up2, Point rot, ContainSphere c, double with, double heigth);
    
    void updateCamType(double x, double y);
    void updateCamPos();
    void updateCamSphere(ContainSphere c, double with, double heigth);
    
    void changePaintMode(int pm);
    void moveCam(Point dist, double aWidth, double aheigth);
    void rotateCam(Point angles, double aWidth,double  aheigth);
    void applyZoom(double z, double aWidth, double aheigth);
    void applyPAN(Point dist);
};


#endif /* defined(__IDIGL__cam__) */
