#pragma once

#include <glm/glm.hpp>
#include "RGB.h"

class Light {
private:
	vec4 position;
	vec4 color;
public:
	Light(vec4 position, vec4 color);
	~Light();

	bool isDirectional() const;
	vec3 getPosition() const;
	vec4 getColor() const;
};
