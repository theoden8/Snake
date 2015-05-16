#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <map>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "Ball.h"
#include "Wall.h"
#include "Fruit.h"
#include "Snake.h"
#include "Functions.h"
#include "State.h"
#include "Aimer.h"

State *state;
Snakes *s;
Walls *w;
Fruits *f;
Aimer *aimer;

void renderBitmapString(float x, float y, void *font, const char *string) {
	glRasterPos2f(x, y);
	for (const char *c = string; *c != '\0'; ++c) {
		glutBitmapCharacter(font, *c);
	}
}

void DrawObject(int x, int y, GLuint id, double degree) {
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

void Display () {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-0.5, state->x_Display, -0.5, state->y_Display, -10, 10);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);

	renderBitmapString(state->width + 1, state->height * 0.97, GLUT_BITMAP_TIMES_ROMAN_24, std::string("Points   " + str(f->frufru) + "..").c_str());
	renderBitmapString(state->width + 1, state->height * 0.93, GLUT_BITMAP_TIMES_ROMAN_24, std::string("Fruits   < " + str(f->fruit_Storage.size()) + " >").c_str());
	renderBitmapString(state->width + 1, state->height * 0.89, GLUT_BITMAP_TIMES_ROMAN_24, std::string("Latency   < " + str(state->latency) + " >").c_str());
	if(state->pause1) {
		renderBitmapString(state->width * 0.45, state->height * 0.75, GLUT_BITMAP_TIMES_ROMAN_24, "[Paused]");
	}
	if(state->running) {
		renderBitmapString(state->width * 0.45, state->height * 0.25, GLUT_BITMAP_TIMES_ROMAN_24, "[Running]");
	}
	if(s->safe) {
		renderBitmapString(state->width + 1, state->height * 0.10, GLUT_BITMAP_TIMES_ROMAN_24, "   [Insurance]");
	}
	renderBitmapString(state->width + 1, state->height * 0.06, GLUT_BITMAP_TIMES_ROMAN_24, std::string(" MODE <  " + str(s->mode) + " :: " + s->ModeName[s->mode] + "  >").c_str());
	renderBitmapString(state->width + 1, state->height * 0.02, GLUT_BITMAP_TIMES_ROMAN_24, std::string(" AIM     <  " + str(s->aim) + " :: " + s->AimName[s->aim] + "  >").c_str());
	glEnable(GL_TEXTURE_2D);
//	Cursor
//	DrawObject(Imagg(),,)
//	Snakes
	for (int i = 0; i < s->snake.size(); ++i) {
		GLuint id;
		double degree = 90;
		if (!i) {
			id = s->head[s->ID].id;
			degree = s->varDirection.degree();
		} else if(i == s->snake.size() - 1) {
			id = s->tail[s->ID].id;
			degree = (s->snake[i - 1] - s->snake[i]).degree();
		} else {
			id = s->body[s->ID].id;
			degree = (s->snake[i - 1] - s->snake[i]).degree();
		}
		DrawObject(s->snake[i].x, s->snake[i].y, id, degree);
	}

//	Walls
	for (auto wall : w->walls) {
		double degree = 90;
		DrawObject(wall.x, wall.y, w->cageGallery[0].id, degree);
	}
//	Fruits
	for (auto fruit : f->fruit_Storage) {
		double degree = 90;
		DrawObject(fruit.x, fruit.y, f->fruitsGallery[s->ID].id, degree);
	}
	glutSwapBuffers();
}

void Timer(int) {
	if (!state->pause1) {
		if(!s->mode) {
			s->AutoCorrection(s->varDirection, w, f);
		}
		if(!state->running) {
			s->DoStep();
		} if (
			FreeSpot(s->snake.front(), w->walls)
			|| FreeSpot(s->snake.front(), s->snake)
		) {
			system(std::string("toilet -t --metal " + str(f->frufru)).c_str());
			exit(0);
		}
	}
	if (FreeSpot(s->snake.front(), f->fruit_Storage)) {
		f->DeleteFruit(s->snake.front());
		f->Push_Back(w, s, 1);
		s->Push_Back();
		++f->frufru;
	}
	if(s->aim) {
//		switch(s->mode) {
//			case 4:
//				s->AutoCD_C(w, f);
//				break;
//			default:
				s->ArtificialMove(w, f);
//				break;
//		}
	}
	Display();
	glutTimerFunc(state->latency, Timer, 0);
}

void Keyboard(unsigned char key, int x, int y) {
	if (state->DoSteps.count(key) > 0) {
		s->AutoCorrection(state->DoSteps[key], w, f);
		return;
	}
	if(key == 27  || process_key(std::string("ptoi"), key)) {
		state->Keyboard(key);
	}
	if(process_key("gzxc", key)) {
		s->Keyboard(key);
		return;
	}
	if(process_key("mn", key)) {
		f->Keyboard(key);
		if(key == 'm') {
			f->Push_Back(w, s, (f->fru_delta >> 2) + 1);
		}
		return;
	}
	if(process_key("01234", key)) {
		state->Keyboard(key);
		s->Keyboard(key);
		return;
	}
}

void Arrow_Keys(int key, int x, int y) {
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

void Mouse(int button, int state, int x, int y) {
}

void Reshape(int new_width, int new_height) {
	glViewport(0, 0, new_width, new_height);
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	srand(time(NULL));

	Ball *size = new Ball((argc >= 3) ? Ball(atoi(argv[1]), atoi(argv[2])) : Ball(50, 50));
	state = new State(40, 1, size->x, size->y);
	delete(size);
	std::string exec = argv[0];
	state->folder = exec.substr(0, exec.length() - 5);

	int template_size = fmin(40, state->width) * 50 - 1100;
	state->x_Display = state->width * 1.4;
	state->y_Display = state->height + 0.5;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(template_size, template_size * 0.75);
	glutInitWindowPosition(500 - state->width * 4, 400 - state->height * 4);
	glutCreateWindow("Snake");

	glutDisplayFunc(Display);
	glutTimerFunc(1000, Timer, 0);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Arrow_Keys);
	glutSetCursor(GLUT_CURSOR_NONE);

	s = new Snakes(state->folder, state->width, state->height);
	w = new Walls(state->folder, state->width, state->height);
	f = new Fruits(state->folder, state->width, state->height, 2);
	aimer = new Aimer();
	f->Push_Back(w, s, 2);
	if(argc == 4) {
		f->Push_Back(w, s, atoi(argv[3]));
	}
	system("toilet -tf mono12 --gay Snake");

	glutMainLoop();

	return 0;
}
