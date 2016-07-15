#pragma once

#include <vector>

#include "Ball.hpp"

class Object {
protected:
	std::vector <Ball> objects;

protected:
	Object();
public:
	virtual ~Object() = 0;

	std::vector <Ball> GetObjects() const;
	virtual void Keyboard(char key);
	virtual void Display() = 0;
};
