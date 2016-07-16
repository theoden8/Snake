#include <cmath>

#include "Graphics.hpp"
#include "Object.hpp"
#include "State.hpp"
#include "Common.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"

void Graphics::Init(int &argc, char **argv) {
	int template_size = fmin(40, WIDTH) * 50 - 1100;

	State::Init(argc, argv);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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

	Common::Init(argc, argv);

	glutMainLoop();

	delete SSNAKE;
	delete (Wall *)WALLS;
	delete FFRUITS;
}

#define str(x) std::to_string(x)
void Graphics::Display () {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	glOrtho(-0.5, State::x_Display, -0.5, State::y_Display, -10, 10);

	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	State::Display();

	glEnable(GL_TEXTURE_2D);
//	Cursor
//	DisplayObject(Image(),,)

	SNAKE->Display();
	WALLS->Display();
	FRUITS->Display();

	glutSwapBuffers();
}

void Graphics::Timer(int) {
	Common::Timer();
	Display();
	glutTimerFunc(State::latency, Timer, 0);
}

void Graphics::Keyboard(unsigned char key, int x, int y) {
	State::Keyboard(key);
	SNAKE->Keyboard(key);
	WALLS->Keyboard(key);
	FRUITS->Keyboard(key);
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
