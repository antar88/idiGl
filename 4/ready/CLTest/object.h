//
//  object.h
//  IDIGL
//
//  Created by Antar - SSD on 16/12/12.
//  Copyright (c) 2012 FIB. All rights reserved.
//

#ifndef __IDIGL__object__
#define __IDIGL__object__

#include <iostream>
#include "includes.h"
#include "model.h"

struct  Box {
    Point max, min, center;
};

class Object {
    Model model;
    
public:
    Box box;
    Point pos;
    Object();
    Object(std::string nomM);
    void render(int lm);
};

#endif /* defined(__IDIGL__object__) */
