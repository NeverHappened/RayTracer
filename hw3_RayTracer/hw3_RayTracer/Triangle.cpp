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
	vec3 a = vec3(transformVertex(v2) - transformVertex(v1));
	vec3 b = vec3(transformVertex(v3) - transformVertex(v1));
	normal = normalize(cross(a, b));
	return normal;
}

vec3 Triangle::transformVertex(vec3 vertex) {
	return vec3(getTransform() * vec4(vertex, 1.0));
}

double Triangle::intersectionDistance(Ray ray) {
	vec3 A = transformVertex(v1);
	vec3 B = transformVertex(v2);
	vec3 C = transformVertex(v3);
	vec3 N = getNormal(vec3(0, 0, 0));

	vec3 P0 = ray.getStart();
	vec3 P1 = ray.getDirection();

	// find plane
	float t = (dot(A, N) - dot(P0, N)) / (dot(P1, N));
	vec3 P = P0 + P1 * t;

	vec3 BC = C - B;
	vec3 CA = A - C;
	vec3 AB = B - A;

	vec3 Apnormal = cross(N, BC) / dot(cross(N, BC), CA);
	float Apw = dot(-Apnormal, C);
	float a = dot(Apnormal, P) + Apw;

	vec3 Bpnormal = cross(N, CA) / dot(cross(N, CA), AB);
	float Bpw = dot(-Bpnormal, A);
	float b = dot(Bpnormal, P) + Bpw;

	//vec3 Cpnormal = cross(N, AB) / dot(cross(N, AB), BC);
	//float Cpw = dot(-Cpnormal, B);
	//float c = dot(Cpnormal, P) + Cpw;
	float c = 1 - a - b; // optimize, because a + b + c == 1

	if (a >= 0 && b >= 0 && c >= 0) {
		return t;
	}
	else {
		return -1.0;
	}
}
