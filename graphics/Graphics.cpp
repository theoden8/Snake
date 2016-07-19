#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Graphics.hpp"
#include "Object.hpp"
#include "State.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"

#define LOG(msg) std::cerr << msg << std::endl;
void Graphics::Init(int &argc, char **argv) {
	int template_size = fmin(40, WIDTH) * 50 - 1100;

	State::Init(argc, argv);

	glutInit(&argc, argv);
	/* glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); */
	glutInitWindowSize(template_size, template_size * 0.75);
	glutInitWindowPosition(500 - WIDTH * 4, 400 - HEIGHT * 4);
	glutCreateWindow("Snake");

	glutDisplayFunc(Display);
	glutTimerFunc(1000, Timer, 0);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutSetCursor(GLUT_CURSOR_NONE);

	WALLS = new Wall();
	assert(WALLS != NULL);
	SNAKE = new Snake();
	assert(SNAKE != NULL);
	FRUITS = new Fruit((argc == 4) ? atoi(argv[3]) : 2);
	assert(FRUITS != NULL);

	glutMainLoop();

	delete SSNAKE;
	delete (Wall *)WALLS;
	delete FFRUITS;
}


void Graphics::DisplayText(float x, float y, const char *s) {
	glDisable(GL_TEXTURE_2D);
	glRasterPos2f(x, y);
	for(const char *c = s; *c != '\0'; ++c)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void Graphics::DisplayObject(Ball ball, GLuint id, double degree) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(1.0f , 1.0f, 1.0f);
	glTranslatef(ball.x, ball.y, 0);
	glRotatef(degree, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3f(-0.5,-0.5,0.0);
	glTexCoord2f(1, 1); glVertex3f(0.5,-0.5,0.0);
	glTexCoord2f(0, 1); glVertex3f(0.5,0.5,0.0);
	glTexCoord2f(0, 0); glVertex3f(-0.5,0.5,0.0);
	glEnd();
	glPopMatrix();
}


#define str(x) std::to_string(x)
void Graphics::Display () {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	glOrtho(-0.5, State::x_Display, -0.5, State::y_Display, -10, 10);

	State::Display();

//	Cursor
//	DisplayObject(Image(),,)

	WALLS->Display();
	FRUITS->Display();
	SNAKE->Display();

	glutSwapBuffers();
}

void Graphics::Timer(int) {
	State::Timer();
	Display();
	glutTimerFunc(State::latency, Timer, 0);
}

void Graphics::Keyboard(unsigned char key, int x, int y) {
	State::Keyboard(key);
}

void Graphics::Special(int key, int x, int y) {
	switch(key) {
		case 100 :
			Keyboard('a', x, y);
		break;
		case 101 :
			Keyboard('w', x, y);
		break;
		case 102 :
			Keyboard('d', x, y);
		break;
		case 103 :
			Keyboard('s', x, y);
		break;
	}
}

void Graphics::Mouse(int button, int state, int x, int y) {
}

void Graphics::Reshape(int new_width, int new_height) {
	glViewport(0, 0, new_width, new_height);
	glutPostRedisplay();
}
