LIBRARIES = Imagg.hpp Wall.hpp Ball.hpp Snake.hpp Fruit.hpp Functions.hpp State.hpp Aimer.hpp
OBJECTS = main_snake.cpp Imagg.cpp Wall.cpp Ball.cpp Snake.cpp Fruit.cpp Functions.cpp State.cpp Aimer.cpp

all : $(OBJECTS) $(LIBRARIES)
	g++ $(OBJECTS) -std=c++11 -Wall -g -I./include -o snake -framework OpenGL -framework GLUT
go :
	while [ 1 ]; do ./snake; done
run :
	./snake
