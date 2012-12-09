//
//  point.cpp
//  IDIGL
//
//  Created by Antar - SSD on 09/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#include "point.h"

Point::Point(float x1, float y1, float z1) {
    x = x1;
    y = y1;
    z = z1;
}

Point::Point(float x1, float y1) {
    x = x1;
    y = y1;
    z = 0;
}

Point::Point() {
    x = y = z = 0.0f;
}