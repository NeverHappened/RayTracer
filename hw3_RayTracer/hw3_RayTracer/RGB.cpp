#include "RGB.h"
#include <glm/glm.hpp>

using namespace glm;

RGB::RGB(BYTE r, BYTE g, BYTE b) : r(r), g(g), b(b) 
{}

RGB::RGB(vec3 color) : 
	r(floatTo255(color.x)), g(floatTo255(color.y)), b(floatTo255(color.z))
{}

RGB::RGB(vec4 color) :
	r(floatTo255(color.x)), g(floatTo255(color.y)), b(floatTo255(color.z))
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

int RGB::floatTo255(float color) const {
	return color * 255.0f;
}
