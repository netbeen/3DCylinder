#include <gl/glut.h>
#include <iostream>

const GLint windowWidth = 800;
const GLint windowHeight = 600;

const GLfloat initCameraX = 0.0f;
const GLfloat initCameraY = 0.0f;
const GLfloat initCameraZ = 3.0f;
const GLfloat visualAngle = 60.0f;
const GLfloat R = 1.0f;
const GLfloat Pi = 3.1415926;
const GLint capSegs = 20;
const GLint heightSegs = 3;

const GLint msPerFrame = 1000/24;