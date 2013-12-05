#include "MyScene.h"

static GLfloat cameraX = initCameraX;
static GLfloat cameraY = initCameraY;
static GLfloat cameraZ = initCameraZ;
static GLfloat yRotateAngle = 0.0f;
static GLfloat yRotateAngleStep = 0.0f;
static GLfloat xRotateAngle = 0.0f;
static GLfloat xRotateAngleStep = 0.0f;


//Render the scene.
void RenderScene(void){
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(yRotateAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(xRotateAngle, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	
	//Draw the bottom circle.
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f, -1.0f, 0.0f);
		for(int i = 0; i < capSegs; i++)
			glVertex3f(R * cos(2 * Pi * i / capSegs), -1.0f, R * sin(2 * Pi * i / capSegs));
		glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	//Draw the lines bwtween bottom and top circle.
	glBegin(GL_LINES);
		for(int i = 0; i < capSegs; i++){
			glVertex3f(R * cos(2 * Pi * i / capSegs), -1.0f, R * sin(2 * Pi * i / capSegs));
			glVertex3f(R * cos(2 * Pi * i / capSegs), 1.0f, R * sin(2 * Pi * i / capSegs));
		}
		glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	//Draw the top circle.
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f, 1.0f, 0.0f);
		for(int i = 0; i < capSegs; i++)
			glVertex3f(R * cos(2 * Pi * i / capSegs), 1.0f, R * sin(2 * Pi * i / capSegs));
		glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();

	yRotateAngle += yRotateAngleStep;
	xRotateAngle += xRotateAngleStep;


	glutSwapBuffers();
}

//Setup  Render Context
void setupRC(void){
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(100,100);
	glutCreateWindow("OpenGL");
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void processSpecialKeys(int key, int mouseX, int mouseY){
	switch (key){
	case GLUT_KEY_RIGHT:
		yRotateAngleStep -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		yRotateAngleStep += 0.1;
		break;
	case GLUT_KEY_UP:
		xRotateAngleStep += 0.1;
		break;
	case GLUT_KEY_DOWN:
		xRotateAngleStep -= 0.1;
		break;
	default:
		break;
	}
}

void changeSize(GLsizei w, GLsizei h){
	GLfloat aspectRatio = static_cast<GLfloat>(w) / static_cast<GLfloat>(h);
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(visualAngle, (static_cast<GLfloat>(windowWidth) / static_cast<GLfloat>(windowHeight)), 1.0f, 100.0f);
	gluLookAt(
		cameraX, cameraY, cameraZ,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void animationControl(int id){
	RenderScene();
	glutTimerFunc(msPerFrame,animationControl,1);  
}

void main(int argc, char** argv){
	glutInit(&argc, argv);
	setupRC();

	glutDisplayFunc(RenderScene);
	glutTimerFunc(msPerFrame,animationControl,1);  
	glutReshapeFunc(changeSize);
	glutSpecialUpFunc(processSpecialKeys);
	
	glutMainLoop();
}