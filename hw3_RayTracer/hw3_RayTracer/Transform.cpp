#include "Transform.h"

mat3 matrix_scale(mat3 m, double s) {
	mat3 scaleMatrix = mat3(s, 0, 0, 0, s, 0, 0, 0, s);
	return m * scaleMatrix;
}

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	mat3 identity = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	mat3 first_part = matrix_scale(identity, cos(glm::radians(degrees)));

	const vec3 a = glm::normalize(axis);

	mat3 squared_matrix = mat3(a.x * a.x, a.x * a.y, a.x * a.z,
		a.x * a.y, a.y * a.y, a.y * a.z,
		a.x * a.z, a.y * a.z, a.z * a.z);

	mat3 second_part = matrix_scale(squared_matrix, (1 - cos(glm::radians(degrees))));

	mat3 A_star_matrix = mat3(0, a.z, -a.y, -a.z, 0, a.x, a.y, -a.x, 0);
	mat3 third_part = matrix_scale(A_star_matrix, sin(glm::radians(degrees)));

	return first_part + second_part + third_part;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
	auto center = vec3(0.0, 0.0, 0.0);
	auto look_vector_norm = glm::normalize(eye - center);
	auto new_y = upvector(up, look_vector_norm);

	mat3 R = rotate(degrees, new_y);
	eye = R * eye;
	up = R * new_y;
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
	auto center = vec3(0.0, 0.0, 0.0);
	auto look_vector_norm = glm::normalize(eye - center);
	auto up_norm = glm::normalize(up);
	auto new_x = glm::cross(look_vector_norm, up_norm);
	auto new_y = glm::cross(new_x, look_vector_norm);

	mat3 R = rotate(degrees, new_x);
	eye = R * eye;
	up = R * new_y;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
	vec3 lookVector = glm::normalize(eye - center);
	vec3 leftVector = glm::normalize(glm::cross(up, lookVector));

	vec3 w = lookVector;
	vec3 u = leftVector;
	vec3 v = glm::cross(w, u);

	mat4 translation = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye.x, -eye.y, -eye.z, 1);
	mat4 rotation = mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
	return rotation * translation;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float A = -((zNear + zFar) / (zFar - zNear));
	float B = -((2.0f * zFar * zNear) / (zFar - zNear));

	float theta = glm::radians(fovy / 2.0f);
	float d = 1.0f / (glm::tan(theta));

	mat4 res = mat4(d / aspect, 0.0f, 0.0f, 0.0f,
		0.0f, d, 0.0f, 0.0f,
		0.0f, 0.0f, A, -1,
		0.0f, 0.0f, B, 0.0f);
	return res;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 ret = mat4(sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1);
	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	mat4 ret = mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		tx, ty, tz, 1);
	return ret;
}

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
