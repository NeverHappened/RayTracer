#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera {
private:
	vec3 eye;
	vec3 up;
	vec3 center;
public:
	Camera(vec3 eye, vec3 up, vec3 center) : eye(eye), up(up), center(center)
	{}
	~Camera()
	{}

	vec3 getEye() const {
		return eye;
	}

	vec3 getUp() const {
		return up;
	}

	vec3 getCenter() const {
		return center;
	}

	mat4 lookAtTransformMatrix() const {
		return Transform::lookAt(eye, center, up);
	}
};