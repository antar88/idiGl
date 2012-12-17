//
//  point.cpp
//  IDIGL
//
//  Created by Antar - SSD on 09/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#include "point.h"

Point::Point(double x1, double y1, double z1) {
    x = x1;
    y = y1;
    z = z1;
}

Point::Point(double x1, double y1) {
    x = x1;
    y = y1;
    z = 0;
}

Point::Point() {
    x = y = z = 0.0f;
}

double Point::distanceToAnotherPoinr(Point p) {
   return sqrt(((p.x-x)*(p.x-x)) + ((p.y-y)*(p.y-y)) + ((p.z-z)*(p.z-z)));
}