#include "Light.h"

Light::Light(vec4 position, vec4 color, vec3 attenuation) : position(position), color(color), attenuation(attenuation)
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

vec3 Light::getAttenuation() const {
	return attenuation;
}
