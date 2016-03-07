#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>

using namespace glm;

class Triangle : public GameObject {
private:
	vec3 v1;
	vec3 v2;
	vec3 v3;

	vec3 normal;

public:
	Triangle(vec3 v1, vec3 v2, vec3 v3); // assumed to be in counter-clockwise order
	~Triangle();

	vec3 getNormal(vec3 point);
	double intersectionDistance(Ray ray);
};