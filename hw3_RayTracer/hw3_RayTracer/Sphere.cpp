#pragma once
#include "Sphere.h"

class Sphere : public GameObject {
private:
	vec3 location;
	double radius;
public:
	Sphere(vec3 location, double radius) : location(location), radius(radius)
	{}

	bool intersects(Ray ray) {
		return false; // TODO
	}
};