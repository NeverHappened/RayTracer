#pragma once

#include "Ray.h"

class GameObject {
protected:
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
	mat4 transform;
public:
	virtual vec3 getNormal(vec3 point) = 0;
	virtual double intersectionDistance(Ray ray) = 0;
	virtual vec4 getAmbient() const;
	virtual vec4 getDiffuse() const;
	virtual vec4 getSpecular() const;
	virtual vec4 getEmission() const;
	virtual float getShininess() const;
	virtual mat4 getTransform() const;
};
