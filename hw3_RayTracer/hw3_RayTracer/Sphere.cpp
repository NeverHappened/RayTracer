#include "Sphere.h"

Sphere::Sphere(vec3 location, double radius, vec3 _diffuse) : location(location), radius(radius)
{
	diffuse = _diffuse;
}

Sphere::~Sphere()
{}

double Sphere::intersectionDistance(Ray ray) {

	vec3 P0 = ray.getStart();
	vec3 P1 = ray.getDirection();
	vec3 C = location;
	double r = radius;
	vec3 vectorToCenter = P0 - C;

	double a = dot(P1, P1);
	double b = 2 * dot(P1, vectorToCenter);
	double c = dot(vectorToCenter, vectorToCenter) - r * r;

	double disc = b * b - 4 * a * c;
	if (disc < 0) {
		return -1; // no intersection
	}
	else if (disc == 0) {
		return -b / (2 * a);
	}
	else {
		// two roots, pick closest to the ray origin
		double t1 = (-b + sqrt(disc)) / (2 * a);
		double t2 = (-b - sqrt(disc)) / (2 * a);
		return min(t1, t2);
	}
	// consider cases when one root is negative - that means that the camera is inside the sphere
}
