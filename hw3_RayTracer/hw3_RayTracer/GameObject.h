#pragma once

#include "Ray.h"

class GameObject {
protected:
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
public:
	virtual double intersectionDistance(Ray ray) = 0;
	virtual vec4 getAmbient() const;
	virtual vec4 getDiffuse() const;
	virtual vec4 getSpecular() const;
	virtual float getShininess() const;
};
