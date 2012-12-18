//
//  point.h
//  IDIGL
//
//  Created by Antar - SSD on 09/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#ifndef __IDIGL__point__
#define __IDIGL__point__

#include <iostream>
#include <math.h>

class Point {
public:
    double x;
    double y;
    double z;
    Point(double x1, double y1, double z1);
    Point(double x1, double y1);
    Point();
    double distanceToAnotherPoinr(Point p);
};


struct ContainSphere {
    Point centre,max,min;
    double radi;
};

#endif /* defined(__IDIGL__point__) */
