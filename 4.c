#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

GLfloat house[3][9] = {
	{100.0, 100.0, 175.0, 250.0, 250.0, 150.0, 150.0, 200.0, 200.0}, 
	{100.0, 300.0, 400.0, 300.0, 100.0, 100.0, 150.0, 150.0, 100.0}, 
	{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}
};
GLfloat rot_mat[3][3]={
	{0}, 
	{0}, 
	{0}
};
GLfloat result[3][9]={
	{0}, 
	{0}, 
	{0}};

GLfloat h = 100.0;
GLfloat k = 100.0;
GLfloat theta;

void multiply() {
	int i, j, l;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 9; j++) {
			result[i][j] = 0;
			for(l = 0; l < 3; l++)
				result[i][j] = result[i][j] + rot_mat[i][l] * house[l][j];
		}
}

void rotate() {
	GLfloat m, n;
	m = -h * (cos(theta) - 1) + k * (sin(theta));
	n = -k * (cos(theta) - 1) - h * (sin(theta));
	rot_mat[0][0] = cos(theta);
	rot_mat[0][1] = -sin(theta);
	rot_mat[0][2] = m;
	rot_mat[1][0] = sin(theta);
	rot_mat[1][1] = cos(theta);
	rot_mat[1][2] = n;
	rot_mat[2][0] = 0;
	rot_mat[2][1] = 0;
	rot_mat[2][2] = 1;
	multiply();
}

void drawHouse(GLfloat matrix[3][9]) { 
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(matrix[0][0], matrix[1][0]);
		glVertex2f(matrix[0][1], matrix[1][1]);
		glVertex2f(matrix[0][3], matrix[1][3]);
		glVertex2f(matrix[0][4], matrix[1][4]);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(matrix[0][5], matrix[1][5]);
		glVertex2f(matrix[0][6], matrix[1][6]);
		glVertex2f(matrix[0][7], matrix[1][7]);
		glVertex2f(matrix[0][8], matrix[1][8]);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(matrix[0][1], matrix[1][1]);
		glVertex2f(matrix[0][2], matrix[1][2]);
		glVertex2f(matrix[0][3], matrix[1][3]);
	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawHouse(house);
	rotate();
	drawHouse(result);
	glFlush();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

int main(int argc, char **argv) {
	printf("Enter the rotation angle\n");
	scanf("%f", &theta);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("House rotation");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
} 