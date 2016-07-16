#include "Graphics.hpp"
#include "glut_config.h"

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
