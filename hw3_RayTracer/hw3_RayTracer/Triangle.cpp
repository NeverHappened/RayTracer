#include "Triangle.h"

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3) : v1(v1), v2(v2), v3(v3)
{
	vec3 a = v2 - v1;
	vec3 b = v3 - v1;
	normal = normalize(cross(a, b));
}

Triangle::~Triangle()
{}

vec3 Triangle::getNormal(vec3 point) {
	return normal; // TODO - needs to transform normal (inverse transform!) (or inverse transpose???)
}

double Triangle::intersectionDistance(Ray ray) {
	return 0.0; // TODO

	// find plane
	// find is inside triangle
	// find distance of intersection
}
