#include "Light.h"

Light::Light(vec4 position, vec4 color) : position(position), color(color)
{}

Light::~Light()
{}

bool Light::isDirectional() const {
	return position.w == 0;
}

vec3 Light::getPosition() const {
	return vec3(position.x, position.y, position.z);
}

vec4 Light::getColor() const {
	return color;
}
