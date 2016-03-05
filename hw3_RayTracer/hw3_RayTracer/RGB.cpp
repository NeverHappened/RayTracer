#include "RGB.h"
#include <glm/glm.hpp>

using namespace glm;

RGB::RGB(BYTE r, BYTE g, BYTE b) : r(b), g(g), b(r) 
{}

RGB::RGB(vec3 color) : r(color.x), g(color.y), b(color.z)
{}

RGB::~RGB()
{}

BYTE RGB::getR() const {
	return r;
}

BYTE RGB::getG() const {
	return g;
}

BYTE RGB::getB() const {
	return b;
}
