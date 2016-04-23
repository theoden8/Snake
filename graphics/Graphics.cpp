#include <cstdlib>
#include <cmath>

#include "Functions.hpp"
#include "Graphics.hpp"

void Graphics::SetOpenGLContext(State *s, Snake *sn, Wall *w, Fruit *f, int &argc, char **argv) {
	state_ = s;
	sn_ = sn;
	wl_ = w;
	fr_ = f;

	int template_size = fmin(40, state_->width) * 50 - 1100;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(template_size, template_size * 0.75);
	glutInitWindowPosition(500 - state_->width * 4, 400 - state_->height * 4);
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

void Graphics::renderBitmapString(float x, float y, void *font, const char *string) {
	glRasterPos2f(x, y);
	for (const char *c = string; *c != '\0'; ++c)
		glutBitmapCharacter(font, *c);
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
	glOrtho(-0.5, state_->x_Display, -0.5, state_->y_Display, -10, 10);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);

	const float
		W = state_->width,
		H = state_->height;

	renderBitmapString(W + 1, H * 0.97, GLUT_BITMAP_TIMES_ROMAN_24, std::string("Points   " + str(fr_->frufru) + "..").c_str());
	renderBitmapString(W + 1, H * 0.93, GLUT_BITMAP_TIMES_ROMAN_24, std::string("Fruit   < " + str(fr_->fruit_Storage.size()) + " >").c_str());
	renderBitmapString(W + 1, H * 0.89, GLUT_BITMAP_TIMES_ROMAN_24, std::string("Latency   < " + str(state_->latency) + " >").c_str());
	if(state_->pause)
		renderBitmapString(W * 0.45, H * 0.75, GLUT_BITMAP_TIMES_ROMAN_24, "[Paused]");
	if(state_->running)
		renderBitmapString(W * 0.45, H * 0.25, GLUT_BITMAP_TIMES_ROMAN_24, "[Running]");
	if(sn_->safe)
		renderBitmapString(W + 1, H * 0.10, GLUT_BITMAP_TIMES_ROMAN_24, "   [Insurance]");
	renderBitmapString(W + 1, H * 0.06, GLUT_BITMAP_TIMES_ROMAN_24, std::string(" MODE <  " + str(sn_->mode) + " :: " + Router::GetName(sn_->mode, sn_->strategy) + "  >").c_str());
	renderBitmapString(W + 1, H * 0.02, GLUT_BITMAP_TIMES_ROMAN_24, std::string(" AIM     <  " + str(sn_->aim) + " :: " + Aimer::GetName(sn_->aim) + "  >").c_str());
	glEnable(GL_TEXTURE_2D);
//	Cursor
//	DrawObject(Image(),,)
//	Snake
	for (int i = 0; i < sn_->snake.size(); ++i) {
		GLuint id;
		double degree = 90;
		if (!i) {
			id = sn_->skins[sn_->ID].head.id;
			degree = sn_->currentDirection.degree();
		} else if(i == sn_->snake.size() - 1) {
			id = sn_->skins[sn_->ID].body.id;
			degree = (sn_->snake[i - 1] - sn_->snake[i]).degree();
		} else {
			id = sn_->skins[sn_->ID].tail.id;
			degree = (sn_->snake[i - 1] - sn_->snake[i]).degree();
		}
		DrawObject(sn_->snake[i].x, sn_->snake[i].y, id, degree);
	}

//	Wall
	for (auto wall : wl_->walls) {
		double degree = 90;
		DrawObject(wall.x, wall.y, wl_->cageGallery[0].id, degree);
	}
//	Fruit
	for (auto fruit : fr_->fruit_Storage) {
		double degree = 90;
		DrawObject(fruit.x, fruit.y, fr_->fruitsGallery[sn_->ID].id, degree);
	}
	glutSwapBuffers();
}

void Graphics::Timer(int) {
	if (!state_->pause) {
		if(!sn_->mode) {
			sn_->AutoCorrection(sn_->currentDirection, wl_, fr_);
		}
		if(!state_->running) {
			sn_->DoStep();
		} if (
			FreeSpot(sn_->snake.front(), wl_->walls)
			|| FreeSpot(sn_->snake.front(), sn_->snake)
		) {
			system(std::string("toilet -t --metal " + std::to_string(fr_->frufru)).c_str());
			exit(0);
		}
	}
	if (FreeSpot(sn_->snake.front(), fr_->fruit_Storage)) {
		fr_->DeleteFruit(sn_->snake.front());
		fr_->Push_Back(wl_, sn_, 1);
		sn_->Push_Back();
		++fr_->frufru;
	}
	if(sn_->aim) {
//		switch(sn_->mode) {
//			case 4:
//				sn_->AutoCD_C(wl_, fr_);
//				break;
//			default:
				sn_->ArtificialMove(wl_, fr_);
//				break;
//		}
	}
	Display();
	glutTimerFunc(state_->latency, Timer, 0);
}

void Graphics::Keyboard(unsigned char key, int x, int y) {
	if (state_->DoSteps.count(key) > 0) {
		sn_->AutoCorrection(state_->DoSteps[key], wl_, fr_);
		return;
	}
	if(key == 27  || process_key("ptoi", key)) {
		state_->Keyboard(key);
	}
	if(process_key("gzxc", key)) {
		sn_->Keyboard(key);
		return;
	}
	if(process_key("mn", key)) {
		fr_->Keyboard(key);
		if(key == 'm') {
			fr_->Push_Back(wl_, sn_, (fr_->fru_delta >> 2) + 1);
		}
		return;
	}
	if(process_key("01234", key)) {
		state_->Keyboard(key);
		sn_->Keyboard(key);
		return;
	}
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
