#include "Intersection.h"

Intersection::Intersection(GameObject* obj, double distance, vec3 position) : obj(obj), distance(distance), position(position) 
{}

Intersection::~Intersection() 
{}

bool Intersection::isIntersection() const {
	return distance > 0.0;
}

vec3 Intersection::getPosition() const {
	return position;
}

GameObject* Intersection::getObject() const {
	return obj;
}

double Intersection::getDistance() const {
	return distance;
}
