#pragma once

#include "glut_config.h"
#include <string>

struct Imagg {
	int width;
	int height;
	GLuint id;

	Imagg();
	bool load(const std::string &filename);
};
