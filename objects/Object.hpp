#pragma once

#include <vector>

#include "Image.hpp"
#include "Ball.hpp"

class Object {
protected:
	std::vector <Ball> objects;

protected:
	Object();
public:
	std::vector <Ball> GetObjects() const;
	virtual void Keyboard(char key);
	virtual void Display() = 0;
};
