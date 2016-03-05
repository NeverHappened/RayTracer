#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Ray {
private:
	vec3 P;
	vec3 direction;
public:
	Ray(vec3 P, vec3 direction);
	~Ray();

	vec3 getStart() const;
	vec3 getDirection() const;
};
