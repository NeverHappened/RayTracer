#pragma once

#include "GameObject.h"

class Sphere : public GameObject {
private:
	vec3 location;
	double radius;
public:
	Sphere(vec3 location, double radius);

	bool intersects(Ray ray);
};