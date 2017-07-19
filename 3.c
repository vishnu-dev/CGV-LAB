#include <GL/glut.h>

typedef float point[3];
GLfloat theta[] = {0.0, 0.0, 0.0};
GLfloat viewer[3];
GLint axis = 2;

GLfloat vertices [][3] = {
			{-1.0, -1.0, -1.0}, 
			{ 1.0, -1.0, -1.0}, 
			{ 1.0,  1.0, -1.0}, 
			{-1.0,  1.0, -1.0}, 
			{-1.0, -1.0,  1.0}, 
			{ 1.0, -1.0,  1.0}, 
			{ 1.0,  1.0,  1.0}, 
			{-1.0,  1.0,  1.0} };

GLfloat colors [][3] = {
			{0.0, 0.0, 0.0}, 
			{1.0, 0.0, 0.0}, 
			{1.0, 1.0, 0.0}, 
			{0.0, 1.0, 0.0}, 
			{0.0, 0.0, 1.0}, 
			{1.0, 0.0, 1.0}, 
			{1.0, 1.0, 1.0}, 
			{0.0, 1.0, 1.0} };

void polygon(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);		
		glVertex3fv(vertices[a]);

		glColor3fv(colors[b]);		
		glVertex3fv(vertices[b]);

		glColor3fv(colors[c]);		
		glVertex3fv(vertices[c]);

		glColor3fv(colors[d]);	
		glVertex3fv(vertices[d]);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube() {
	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(1,2,6,5);
	polygon(0,1,5,4);
	polygon(0,3,7,4);
	polygon(4,7,6,5);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// glOrtho(-2.0,2.0,-2.0,2.0,-10.0,10.0); // If reshape is not used
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glScalef(0.5,0.5,0.5);
	colorcube();
	glutSwapBuffers();
}	

void spincube() {
	theta[axis] += 2.0;
	if (theta[axis] > 360.0)
		theta[axis] -= 360;
	glutPostRedisplay();
}

void mouse(int btn, int state, int x,int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
	spincube();
}

void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w, 2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);  
	else
		glOrtho(-2.0 * (GLfloat) w / (GLfloat) h, 2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
	glutPostRedisplay();
}

void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Cube-Spin");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spincube);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}