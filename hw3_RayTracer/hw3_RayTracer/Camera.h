#pragma once

#include "Transform.h"

using namespace glm;

class Camera {
private:
	vec3 eye;
	vec3 up;
	vec3 center;
public: 
	Camera(vec3 eye, vec3 up, vec3 center);
	~Camera();

	vec3 getEye() const;
	vec3 getUp() const;
	vec3 getCenter() const;
	vec3 getDirection() const;

	mat4 lookAtTransformMatrix() const;
};
