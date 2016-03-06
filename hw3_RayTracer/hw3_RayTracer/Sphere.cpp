#include "Sphere.h"

Sphere::Sphere(vec3 location, double radius, vec4 _ambient, vec4 _diffuse, vec4 _specular, float _shininess, mat4 _transform) :
	location(location), radius(radius)
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
	transform = _transform;
}

Sphere::~Sphere()
{}

double Sphere::intersectionDistance(Ray ray) {
//	double dist = intersectionHelper(ray);
	double dist = withTransformations(ray);
	return dist > 0.01 ? dist : -1.0;
}

vec3 Sphere::getNormal(vec3 point) { // TODO - interpolate normal as it needs to be
	return normalize(location - point);
}

double Sphere::withTransformations(Ray ray) {
	mat4 transf = getTransform();
	vec4 transformedPoint = inverse(transf) * vec4(ray.getStart(), 1.0);
	//vec4 transformedDirection = transform * vec4(ray.getDirection(), 0.0); // NO ! rays dont transform

	Ray transformedRay = Ray(vec3(transformedPoint), ray.getDirection());
	float distance = (float)intersectionHelper(transformedRay);
	vec3 transformedIntersectionPoint = ray.getStart() + distance * normalize(ray.getDirection());
	vec4 originalPoint = transf * vec4(transformedIntersectionPoint, 1.0);
	vec3 o = vec3(originalPoint) - ray.getStart();

	return sqrt(o.x * o.x + o.y * o.y + o.z * o.z); // distance to point
}

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
