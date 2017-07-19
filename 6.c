#include <GL/glut.h>
#include <math.h>

void drawPixel(GLint cx, GLint cy) {   
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2i(cx, cy);
	glEnd();
}

void plotPixels(GLint h, GLint k, GLint x, GLint y) {
	drawPixel(x+h,y+k);
	drawPixel(-x+h,y+k);
	drawPixel(x+h,-y+k);
	drawPixel(-x+h,-y+k);
	drawPixel(y+h,x+k);
	drawPixel(-y+h,x+k);
	drawPixel(y+h,-x+k);
	drawPixel(-y+h,-x+k);
}

void circleDraw(GLint h, GLint k, GLint r) {
	GLint d =  1-r, x=0, y=r;
	while(y > x) {
		plotPixels(h, k, x, y);
		if(d < 0) 
			d += 2 * x + 3;
		else {
			d += 2 * (x - y) + 5;
			--y;
		}
		++x;
	}
	//plotPixels(h, k, x, y);
	// int i;
	// for(i=0;i<=360;i+=5)
	// {
	// 	int x=h+r*cos(i),y=k+r*sin(i);
	// 	glBegin(GL_POINTS);
	// 		glVertex2f(x,y);
	// 	glEnd();
	// }
}

void cylinderDraw() {
	GLint xc=100, yc=100, r=50;
	GLint i, n=50;
	for(i = 0; i < n; i += 3)
		circleDraw(xc, yc+i, r);
}

void parallelepiped(int x1,int x2,int y1, int y2) {
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}

void parallelepipedDraw() {
	int x1=200, x2=300, y1=100, y2=175;
	GLint i, n=40;
	for(i = 0; i < n; i += 2)
		parallelepiped(x1+i, x2+i, y1+i, y2+i);
}

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);  
	glMatrixMode(GL_PROJECTION);  
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);  
}

void display(void) {   
	glClear(GL_COLOR_BUFFER_BIT);  
	glColor3f(1.0, 0.0, 0.0); 
	cylinderDraw(); 
	parallelepipedDraw();
	glFlush(); 
}

int main(int argc, char **argv) {   
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50); 
	glutInitWindowSize(400, 300); 
	glutCreateWindow("Cylinder and parallelepiped Display by Extruding Circle and Quadrilaterl"); 
	init();
	glutDisplayFunc(display); 
	glutMainLoop();
	return 0;
}