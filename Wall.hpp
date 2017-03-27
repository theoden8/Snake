#pragma once

#include <vector>
#include <string>

#include "Object.hpp"
#include "State.hpp"

class Wall : public Object {
public:
	Image wallsGallery[1];
	Wall();

	void Display();
};
