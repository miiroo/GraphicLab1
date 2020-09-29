
#include<math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator> 


#if defined(linux) || defined(_WIN32)
#include<GL/glut.h>/*ДляLinux и Windows*/
#else
#include<GLUT/GLUT.h>/*Для Mac OS*/
#endif


using namespace std;

struct Point {
	float x;
	float y;
};


list <Point> points;
list <int> code;
Point currPoint;


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
	gluOrtho2D(-10, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void readFromFile()
{
	fstream f("points.txt", ios::in);
	if (f.is_open()) {
		int pointNumber;
		Point p;
		f >> pointNumber;
		for (int i = 0; i < pointNumber;i++)
		{
			f >> p.x >> p.y;
			points.push_back(p);
			cout << p.x << " " << p.y << endl;
		}
		cout << endl;
		int movesNumber, m;
		f >> movesNumber;
		for (int i = 0; i < movesNumber; i++)
		{
			f >> m;
			code.push_back(m);
			cout << m << endl;
		}
	}
	f.close();
}


void moveTo(int mto) {
	mto = abs(mto) - 1;
	list <Point> ::iterator it = points.begin();
	for (int i = 0; i < mto; i++) {
		it++;
	}
	currPoint.x = (*it).x;
	currPoint.y = (*it).y;

}

void drawTo(int dto) {
	dto = abs(dto) - 1;
	list <Point> ::iterator it = points.begin();
	for (int i = 0; i < dto; i++) {
		it++;
	}
	Point p = (*it);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2i(currPoint.x, currPoint.y);
	glVertex2i(p.x, p.y);

	glEnd();
	currPoint = p;
}

void display() {
	readFromFile();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto it = code.begin(); it != code.end(); it++) {
		if ((*it) < 0) {
			moveTo((*it));
		}
		else {
			drawTo((*it));
		}
	}
	glutSwapBuffers();
}