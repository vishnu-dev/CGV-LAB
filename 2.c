#include<stdio.h>
#include<GL/glut.h>

double xmin = 50, xmax = 100, ymax = 100, ymin = 50;	
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;		
double xa, ya, xb, yb;

int cliptest(double p, double q, double *t1, double *t2) 
{
	double t=q/p;
	if(p < 0.0)	{
		if(t > *t1)
			*t1 = t;
		if(t > *t2)
			return 0;
	}
	else if(p > 0.0) {
		if(t < *t2)
			*t2 = t;
		if(t < *t1)
			return 0;
	}
	return 1;
}

void liang(double x0, double y0, double x1, double y1) 
{
	double dx = x1 - x0, dy = y1 - y0, tc = 0.0, t1 = 1.0;
	if(cliptest(-dx, x0-xmin, &tc, &t1))	
		if(cliptest(dx, xmax-x0, &tc, &t1))	
			if(cliptest(-dy, y0-ymin, &tc, &t1))
				if(cliptest(dy, ymax-y0, &tc, &t1))	
				{
					if(t1 < 1.0) {
						x1 = x0 + t1 * dx;
						y1 = y0 + t1 * dy;
					}
					if(tc > 0.0)
					{
						x0 = x0 + tc * dx;
						y0 = y0 + tc * dy;
					}
			
					double sx=(xvmax-xvmin)/(xmax-xmin);
					double sy=(yvmax-yvmin)/(ymax-ymin);
					double vx0=xvmin+(x0-xmin)*sx;
					double vy0=yvmin+(y0-ymin)*sy;
  					double vx1=xvmin+(x1-xmin)*sx;
  					double vy1=yvmin+(y1-ymin)*sy;
					
  					glColor3f(1.0, 0.0, 0.0);
					glBegin(GL_LINE_LOOP);		
						glVertex2f(xvmin, yvmin);
						glVertex2f(xvmax, yvmin);
						glVertex2f(xvmax, yvmax);
						glVertex2f(xvmin, yvmax);
  					glEnd();
  					glColor3f(0.0, 0.0, 1.0);
  					glBegin(GL_LINES);			
						glVertex2d(vx0, vy0);
						glVertex2d(vx1, vy1);
  					glEnd();
				}
}
	
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);			
		glVertex2d(xa, ya);
		glVertex2d(xb, yb);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);		
		glVertex2f(xmin, ymin);
  		glVertex2f(xmax, ymin);
  		glVertex2f(xmax, ymax);
  		glVertex2f(xmin, ymax);
	glEnd();
	liang(xa, ya, xb, yb);		
	glFlush();
}

void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
	
int main(int argc, char **argv)
{
	printf("Enter coordinates (x0, y0, x1, y1)\n");
	scanf("%lf%lf%lf%lf", &xa, &ya, &xb, &yb);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Liang Barksy Line Clipping");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
	return 0;
}