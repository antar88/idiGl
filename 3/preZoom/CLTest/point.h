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

class Point {
public:
    float x;
    float y;
    float z;
    Point(float x1, float y1, float z1);
    Point(float x1, float y1);
    Point();
};

#endif /* defined(__IDIGL__point__) */
