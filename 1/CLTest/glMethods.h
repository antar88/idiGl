//
//  glMethods.h
//  CLTest
//
//  Created by Antar - SSD on 08/12/12.
//  Copyright (c) 2012 Àlex Vergara. All rights reserved.
//

#ifndef __CLTest__glMethods__
#define __CLTest__glMethods__


#include <iostream>
#include "includes.h"


struct triangleColor{
    float r;
    float g;
    float b;
};

struct trianlePos{
    Point p1, p2, p3;
};



    //other methods
    void updateCamera(float x, float y);
    triangleColor getColorTriangle();

    //Callback methods
    void refresh(void);
    void reshape(int x, int y);
    void mouseInteraction(int mouseButton, int type, int xClic, int yClic);
    void mouseMovement(int xMouse, int yMouse);
    void keyboardInteraction(unsigned char key, int xMouse, int yMouse);


#endif /* defined(__CLTest__glMethods__) */




