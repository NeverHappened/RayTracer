#pragma once

#include "Ray.h"

using namespace glm;

Ray::Ray(vec3 P, vec3 direction) : P(P), direction(direction)
{}

Ray::~Ray()
{}

vec3 Ray::getStart() const {
	return P;
}

vec3 Ray::getDirection() const {
	return direction;
}
