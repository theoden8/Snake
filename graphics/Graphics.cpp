#include <cstdlib>
#include <cmath>

#include "Functions.hpp"
#include "Graphics.hpp"

void Graphics::SetOpenGLContext(State *st, int &argc, char **argv) {
	state = st;
	sn = st->snake;
	wls = st->walls;
	frs = st->fruits;

	int template_size = fmin(40, state->width) * 50 - 1100;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(template_size, template_size * 0.75);
	glutInitWindowPosition(500 - state->width * 4, 400 - state->height * 4);
	glutCreateWindow("Snake");
}

void Graphics::SetOpenGLFunctions() {
	glutDisplayFunc(Display);
	glutTimerFunc(1000, Timer, 0);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Arrow_Keys);
	glutSetCursor(GLUT_CURSOR_NONE);
}

void Graphics::StartGraphics() {
	glutMainLoop();
}

void Graphics::DrawText(float x, float y, char *text) {
	glRasterPos2f(x, y);
	for(const char *c = string; *c != '\0'; ++c)
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

	state->Display();

//	Cursor
//	DrawObject(Image(),,)
//	Snake
	for(int i = 0; i < sn->snake.size(); ++i) {
		GLuint id;
		double degree = 90;
		if(i == 0) {
			id = sn->skins[sn->ID].head.id;
			degree = sn->currentDirection.degree();
		} else if(i == sn->snake.size() - 1) {
			id = sn->skins[sn->ID].body.id;
			degree = (sn->snake[i - 1] - sn->snake[i]).degree();
		} else {
			id = sn->skins[sn->ID].tail.id;
			degree = (sn->snake[i - 1] - sn->snake[i]).degree();
		}
		DrawObject(sn->snake[i].x, sn->snake[i].y, id, degree);
	}

//	Wall
	for(auto wall : wls->walls) {
		double degree = 90;
		DrawObject(wall.x, wall.y, wls->cageGallery[0].id, degree);
	}
//	Fruit
	for(auto fruit : frs->fruitStorage) {
		double degree = 90;
		DrawObject(fruit.x, fruit.y, frs->fruitsGallery[sn->ID].id, degree);
	}
	glutSwapBuffers();
}

void Graphics::Timer(int) {
	if(!state->pause) {
		if(!sn->mode)
			sn->AutoCorrection(sn->currentDirection, wls, frs);

		if(!state->running)
			sn->DoStep();
		if(
			Ball::FreeSpot(sn->snake.front(), wls->walls)
			|| Ball::FreeSpot(sn->snake.front(), sn->snake)
		)
		{
			std::cout << std::to_string(frs->frufru) << std::endl;
			exit(0);
		}
	}
	if(Ball::FreeSpot(sn->snake.front(), frs->fruitStorage)) {
		frs->DeleteFruit(sn->snake.front());
		frs->Push_Back(wls, sn, 1);
		sn->Push_Back();
		++frs->frufru;
	}
	if(sn->aim) {
//		switch(sn->mode) {
//			case 4:
//				sn->AutoCD_C(wls, frs);
//				break;
//			default:
				sn->AutomaticMove(wls, frs);
//				break;
//		}
	}
	Display();
	glutTimerFunc(state->latency, Timer, 0);
}

void Graphics::Keyboard(unsigned char key, int x, int y) {
	state->Keyboard(key);
	sn->Keyboard(key);
	frs->Keyboard(key);
}

void Graphics::Arrow_Keys(int key, int x, int y) {
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
