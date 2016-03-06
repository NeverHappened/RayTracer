#pragma once

#include "GameObject.h"

class Sphere : public GameObject {
private:
	vec3 location;
	double radius;
	double intersectionHelper(Ray ray);
public:
	Sphere(vec3 location, double radius, vec4 _ambient, vec4 _diffuse, vec4 _specular, float _shininess);
	~Sphere();

	double intersectionDistance(Ray ray);

	virtual vec3 getNormal(vec3 point);
};
