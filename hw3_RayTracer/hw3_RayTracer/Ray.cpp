#pragma once

#include "Ray.h"

using namespace glm;

class Ray {
private:
	vec3 P;
	vec3 direction;
public:
	Ray(vec3 P, vec3 direction) : P(P), direction(direction)
	{}
	~Ray()
	{}
};