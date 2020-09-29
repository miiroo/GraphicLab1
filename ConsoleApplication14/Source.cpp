#if defined(linux) || defined(_WIN32)
#include<GL/glut.h>/*ДляLinux и Windows*/
#else
#include<GLUT/GLUT.h>/*Для Mac OS*/
#endif
#include<math.h>

void reshape(int w, int h);
void display();

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 500);
	glutCreateWindow("OpenGL lesson 1");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(0, -100);
	glVertex2f(0, 100);
	glVertex2f(-100, 0);
	glVertex2f(100, 0);
	glEnd();

	glColor3d(0, 0, 1);
	
	glBegin(GL_LINE_STRIP);
	for (float x = -100; x < 100; x += 0.5) {
		double y = fabs(0.25*x + 3 * cos(100 * x)*sin(x));
		glVertex2f(x, y);
	}
	glEnd();

	glutSwapBuffers();
}