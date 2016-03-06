#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>

class Intersection {
private:
	double distance = -1;
	GameObject* obj;
	vec3 position;
	
public:
	Intersection(GameObject* obj, double distance, vec3 position);
	~Intersection();

	bool isIntersection() const;
	vec3 getPosition() const;
	GameObject* getObject() const;
	double getDistance() const;
};
