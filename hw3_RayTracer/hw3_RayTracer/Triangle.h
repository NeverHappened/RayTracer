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
	Triangle(vec3 v1, vec3 v2, vec3 v3, vec4 ambient, // v1, v2, v3 assumed to be in counter-clockwise order
		vec4 diffuse, vec4 specular, float shininess, vec4 emission, mat4 transform); 
	~Triangle();

	vec3 getNormal(vec3 point);
	vec3 transformVertex(vec3 vertex);
	double intersectionDistance(Ray ray);
};