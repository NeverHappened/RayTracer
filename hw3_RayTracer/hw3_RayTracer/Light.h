#pragma once

#include <glm/glm.hpp>
#include "RGB.h"

class Light {
private:
	vec4 position;
	vec4 color;
	vec3 attenuation;
public:
	Light(vec4 position, vec4 color, vec3 attenuation);
	~Light();

	bool isDirectional() const;
	vec3 getPosition() const;
	vec4 getColor() const;
	vec3 getAttenuation() const; // constant, linear, quadratic
};
