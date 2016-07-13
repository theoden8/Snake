#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Functions.hpp"
#include "Graphics.hpp"
#include "State.hpp"
#include "Fruit.hpp"
#include "Wall.hpp"
#include "Snake.hpp"

void Graphics::SetOpenGLContext(int &argc, char **argv) {
	int template_size = fmin(40, State::width) * 50 - 1100;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(template_size, template_size * 0.75);
	glutInitWindowPosition(500 - State::width * 4, 400 - State::height * 4);
	glutCreateWindow("Snake");
}

void Graphics::SetOpenGLFunctions() {
	glutDisplayFunc(Display);
	glutTimerFunc(1000, Timer, 0);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutSetCursor(GLUT_CURSOR_NONE);
}

void Graphics::StartGraphics() {
	glutMainLoop();
}

void Graphics::DrawText(float x, float y, char *s) {
	glRasterPos2f(x, y);
	for(const char *c = s; *c != '\0'; ++c)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void Graphics::DrawObject(int x, int y, GLuint id, double degree) {
	glPushMatrix();
	glColor3f(1 , 1, 1);
	glTranslatef(x, y, 0);
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

	State::Display();
//	Cursor
//	DrawObject(Image(),,)
	SNAKE->Display();
	WALLS->Display();
	FRUITS->Display();

	glutSwapBuffers();
}

void Graphics::Timer(int) {
	if(!State::pause) {
		if(!SNAKE->mode)
			SNAKE->AutoCorrection(SNAKE->currentDirection);

		if(!State::running)
			SNAKE->DoStep();
		if(
			Ball::FreeSpot(SNAKE->snake.front(), WALLS->walls)
			|| Ball::FreeSpot(SNAKE->snake.front(), SNAKE->snake)
		)
		{
			std::cout << std::to_string(FRUITS->frufru) << std::endl;
			exit(0);
		}
	}
	if(Ball::FreeSpot(SNAKE->snake.front(), FRUITS->fruitStorage)) {
		FRUITS->DeleteFruit(SNAKE->snake.front());
		FRUITS->Push_Back(1);
		SNAKE->Push_Back();
		++FRUITS->frufru;
	}
	if(SNAKE->aim) {
//		switch(SNAKE->mode) {
//			case 4:
//				SNAKE->AutoCD_C();
//				break;
//			default:
				SNAKE->AutomaticMove();
//				break;
//		}
	}
	Display();
	glutTimerFunc(State::latency, Timer, 0);
}

void Graphics::Keyboard(unsigned char key, int x, int y) {
	State::Keyboard(key);
	SNAKE->Keyboard(key);
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
