#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Camera::Camera(vec3 eye, vec3 up, vec3 center) : eye(eye), up(up), center(center)
{}

Camera::~Camera()
{}

vec3 Camera::getEye() const {
	return eye;
}

vec3 Camera::getUp() const {
	return up;
}

vec3 Camera::getCenter() const {
	return center;
}

mat4 Camera::lookAtTransformMatrix() const {
	return Transform::lookAt(eye, center, up);
}
