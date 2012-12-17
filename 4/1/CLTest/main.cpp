//
//  main.cpp
//  CLTest
//
//  Created by Àlex Vergara Nebot on 04/12/12.
//  Copyright (c) 2012 Àlex Vergara. All rights reserved.
//

#include <iostream>
using namespace std;
#include "includes.h"
#include "glMethods.h"


int main(int argc, char const *argv[])
{
    //Inicialitzacions
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_W, SCREEN_H);
	glutCreateWindow("Practica IDI 2012/2013");
    
    //Callbacks
	glutDisplayFunc(firstPaint);
	glutReshapeFunc(reshape);
    glutMouseFunc(mouseInteraction);
    glutMotionFunc(mouseMovement);
    glutKeyboardFunc(keyboardInteraction);
    glutSpecialFunc(keyboardSpecialKeysInteraction);
    glutIdleFunc(refresh);
    
    //main Loop and App end
	glutMainLoop();
	return 0;
}

