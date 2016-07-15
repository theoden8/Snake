#include <cmath>

#include "Graphics.hpp"
#include "Object.hpp"
#include "State.hpp"


void Graphics::StartGraphics(int &argc, char **argv) {
	int template_size = fmin(40, State::width) * 50 - 1100;

	State::InitState(argc, argv);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(template_size, template_size * 0.75);
	glutInitWindowPosition(500 - State::width * 4, 400 - State::height * 4);
	glutCreateWindow("Snake");

	glutDisplayFunc(Display);
	glutTimerFunc(1000, Timer, 0);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutSetCursor(GLUT_CURSOR_NONE);

	State::InitStateFin(argc, argv);

	glutMainLoop();

	delete SNAKE; delete WALLS; delete FRUITS;
}

void Graphics::Keyboard(unsigned char key, int x, int y) {
	State::Keyboard(key);
	SNAKE->Keyboard(key);
	FRUITS->Keyboard(key);
}

void Graphics::DisplayText(float x, float y, char *s) {
	glRasterPos2f(x, y);
	for(const char *c = s; *c != '\0'; ++c)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void Graphics::DisplayObject(Ball ball, GLuint id, double degree) {
	glPushMatrix();
	glColor3f(1 , 1, 1);
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
