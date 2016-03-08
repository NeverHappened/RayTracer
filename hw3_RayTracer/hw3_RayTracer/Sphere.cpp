#include "Sphere.h"

Sphere::Sphere(vec3 location, double radius, vec4 _ambient, vec4 _diffuse, vec4 _specular, float _shininess, vec4 _emission, mat4 _transform) :
	location(location), radius(radius)
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	emission = _emission;
	shininess = _shininess;
	transform = _transform;
}

Sphere::~Sphere()
{}

double Sphere::intersectionDistance(Ray ray) {
	double dist = withTransformations(ray);
	return dist > 0.01 ? dist : -1.0;
}

vec3 Sphere::getNormal(vec3 point) { // point is already transformed (real coordinates)
	vec3 notTransformedPoint = vec3(inverse(getTransform()) * vec4(point, 1.0));
	return normalize(notTransformedPoint - location);
}

double vectorDistance(vec3 o) {
	return sqrt(o.x * o.x + o.y * o.y + o.z * o.z);
}

double Sphere::withTransformations(Ray ray) {
	mat4 M = getTransform();
	Ray R = ray;
	Sphere* P = this;

	// apply inverse transform to the original ray
	vec3 origin_prime = vec3(inverse(M) * vec4(R.getStart(), 1.0));
	vec3 direction_prime = normalize(vec3(inverse(M) * vec4(normalize(R.getDirection()), 0.0)));
	Ray R_prime = Ray(origin_prime, direction_prime);
	// compute intersection between original object and R'
	float distance = (float)intersectionHelper(R_prime);

	if (distance <= 0.0) {
		return -1.0;
	}
	vec3 P_prime_star = R_prime.getStart() + R_prime.getDirection() * distance;
	// find intersection point in the actual world
	vec3 actual_world_point = vec3(M * vec4(P_prime_star, 1.0f));
	double distance_to_actual_world_point = vectorDistance(R.getStart() - actual_world_point);
	return distance_to_actual_world_point;
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
