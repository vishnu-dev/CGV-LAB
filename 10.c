#include <stdio.h>
#include <GL/glut.h>
#define maxx 20
#define maxy 20
#define dx 30
#define dy 30
GLfloat x[maxx],y[maxy];
GLfloat x0=50,y0=50;
GLint i,j;
void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 999.0, 0.0, 999.0);
	glutPostRedisplay();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for(i=0;i<maxx;i++)
		x[i]=x0+i*dx;
	for(j=0;j<maxy;j++)
		y[j]=y0+j*dy;
	for(i=0;i<maxx-1;i++)
	for(j=0;j<maxy-1;j++){
	glColor3f((rand()%100)/100.0,(rand()%100)/100.0,(rand()%100)/100.0);
	//glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(x[i],y[j]);
			glVertex2f(x[i+1],y[j]);
			glVertex2f(x[i+1],y[j+1]);
			glVertex2f(x[i],y[j+1]);
		glEnd();
		glFlush();
	}
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rectangular Mesh");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}