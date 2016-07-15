#include <iostream>
#include <cstdlib>

#include "Graphics.hpp"
#include "State.hpp"

#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"


#define str(x) std::to_string(x)
void Graphics::Display () {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	const int
		&height = State::height,
		&width = State::width;

	glOrtho(-0.5, State::x_Display, -0.5, State::y_Display, -10, 10);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
//	Cursor
//	DisplayObject(Image(),,)

	SNAKE->Display();
	WALLS->Display();
	FRUITS->Display();

	glutSwapBuffers();
}

void Graphics::Timer(int) {
	if(!State::pause) {
		/* if(!SSNAKE->mode) */
		/* 	SSNAKE->AutoCorrection(SSNAKE->currentDirection); */

		if(!State::running)
			SSNAKE->DoStep();
		if(
			Ball::FreeSpot(SNAKE->GetObjects().front(), WALLS->GetObjects())
			|| Ball::FreeSpot(SNAKE->GetObjects().front(), SNAKE->GetObjects())
		)
		{
			std::cout << std::to_string(FFRUITS->frufru) << std::endl;
			exit(0);
		}
	}
	if(Ball::FreeSpot(SNAKE->GetObjects().front(), FRUITS->GetObjects())) {
		FFRUITS->DeleteFruit(SNAKE->GetObjects().front());
		FFRUITS->PushBack(1);
		SSNAKE->PushBack();
		++FFRUITS->frufru;
	}
	/* if(SSNAKE->aim) { */
	/* 	switch(SSNAKE->mode) { */
	/* 		case 4: */
	/* 			SSNAKE->AutoCD_C(); */
	/* 			break; */
	/* 		default: */
	/* 			/1* SSNAKE->AutomaticMove(); *1/ */
	/* 			break; */
	/* 	} */
	/* } */
	Display();
	glutTimerFunc(State::latency, Timer, 0);
}
