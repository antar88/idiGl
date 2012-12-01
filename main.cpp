//
//  main.cpp
//  
//
//  Created by Antar - SSD on 01/12/12.
//
//

#include "main.h"

int main(int argc, char const *argv[])
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Practica IDI 2012/2013");
	glutDisplayFunc(refresh);
	glutMainLoop();
	return 0;
}


