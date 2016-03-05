#pragma once

#include "FreeImageHelper.h"
#include <glm/glm.hpp>

using namespace glm;

class RGB {
private:
	BYTE r;
	BYTE g;
	BYTE b;

public:
	RGB(BYTE r, BYTE g, BYTE b);
	RGB(vec3 color);
	~RGB();

	BYTE getR() const;
	BYTE getG() const;
	BYTE getB() const;
};
