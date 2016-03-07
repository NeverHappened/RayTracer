#include "Triangle.h"

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, vec4 _ambient, vec4 _diffuse, vec4 _specular, float _shininess, vec4 _emission, mat4 _transform) : 
	v1(v1), v2(v2), v3(v3)
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
	emission = _emission;
	transform = _transform;
	normal = getNormal(vec3(0, 0, 0));
}

Triangle::~Triangle()
{}

vec3 Triangle::getNormal(vec3 point) {
	vec3 a = vec3(getTransform() * vec4(v2, 1.0) - getTransform() * vec4(v1, 1.0));
	vec3 b = vec3(getTransform() * vec4(v3, 1.0) - getTransform() * vec4(v1, 1.0));
	normal = normalize(cross(a, b));
	return normal; // TODO - needs to transform normal (inverse transform!) (or inverse transpose???)
}

double Triangle::intersectionDistance(Ray ray) {
	vec3 A = vec3(getTransform() * vec4(v2, 1.0) - getTransform() * vec4(v1, 1.0));
	vec3 B = vec3(getTransform() * vec4(v3, 1.0) - getTransform() * vec4(v2, 1.0));
	vec3 C = vec3(getTransform() * vec4(v3, 1.0) - getTransform() * vec4(v1, 1.0));
	vec3 P0 = ray.getStart();
	vec3 P1 = ray.getDirection();

	// find plane
	vec3 n = getNormal(vec3(0, 0, 0)); // dont need actually to use a point
	// find distance of intersection
	float t = (dot(A, n) - dot(P0, n)) / (dot(P1, n));
	vec3 P = P0 + P1 * t;
	// find is inside triangle
	bool inside = dot((cross(B - A, P - A)), n) >= 0 &&
				  dot((cross(C - B, P - B)), n) >= 0 &&
				  dot((cross(A - C, P - C)), n) >= 0;

	if (inside) {
		return t;
	}
	else {
		return -1;
	}
}
