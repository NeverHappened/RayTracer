#include "Sphere.h"

Sphere::Sphere(vec3 location, double radius, vec4 _ambient, vec4 _diffuse, vec4 _specular, float _shininess) :
	location(location), radius(radius)
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
}

Sphere::~Sphere()
{}

double Sphere::intersectionHelper(Ray ray) {
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
		return -1.0; // no intersection
	}
	else if (disc == 0) {
		double t1 = -b / (2 * a);
		if (t1 > 0) {
			return t1;
		}
		else {
			return -1.0;
		}
	}
	else {
		// two roots, pick closest to the ray origin
		double t1 = (-b + sqrt(disc)) / (2 * a);
		double t2 = (-b - sqrt(disc)) / (2 * a);
		if (t1 < 0.0 && t2 < 0.0) {
			return -1.0;
		}
		else if (min(t1, t2) < 0.0) {
			return -1.0;
		}
		else {
			return min(t1, t2);
		}
	}
}

double Sphere::intersectionDistance(Ray ray) {
	double dist = intersectionHelper(ray);
	return  dist > 0.01 ? dist : -1.0;
}

vec3 Sphere::getNormal(vec3 point) {
	return point - location;
}