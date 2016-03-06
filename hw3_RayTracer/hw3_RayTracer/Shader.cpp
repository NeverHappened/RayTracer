#include "Shader.h"

Shader::Shader(vector<Light> lights) : lights(lights)
{}

Shader::~Shader()
{}

void Shader::addLight(Light light) {
	lights.push_back(light);
}

RGB Shader::shade(Camera camera, Intersection intersection, Ray ray, PixelSample sample, vector<GameObject*> objects) {
	if (intersection.isIntersection()) {
		return computeLightOnHit(camera, intersection, ray, objects);
	}
	else {
		return RGB(0, 0, 0);
	}
}

double distance(vec3 vect) {
	return sqrt(vect.x * vect.x +
		vect.y * vect.y +
		vect.z * vect.z);
}

bool Shader::lightVisibleFromHere(Intersection intersection, Light light, vector<GameObject*> objects) {

	vec3 lookToLightSource = intersection.getPosition() - light.getPosition();
	Ray rayToLightSource(intersection.getPosition(), normalize(lookToLightSource));

	double distanceToLightSource = distance(lookToLightSource);
	Intersection onThePathToLight = IntersectionHelper::findClosestIntersection(rayToLightSource, objects);

	if (!onThePathToLight.isIntersection()) {
		return true;
	}
	else if (onThePathToLight.getDistance() > distanceToLightSource) {
		return true;
	}
	else {
		return false;
	}
}


double Shader::computeDistanceFromTo(Intersection intersection, Light light) {
	vec3 lookToLightSource = light.getPosition() - intersection.getPosition();
	return distance(lookToLightSource);
}

//double attenuate(RGB color, double distanceToLight); // TODO! // FOR NOW COMPUTE LIGHT WITHOUT ATTENUATION MODEL!

RGB Shader::computeLightOnHit(Camera camera, Intersection intersection, Ray ray, vector<GameObject*> objects) {
	GameObject* obj = intersection.getObject();
	vec4 resultLight = obj->getAmbient(); //+ obj->getEmission(); // no support for emission for now
	
	for (Light& light : lights) {
//		if (!lightVisibleFromHere(intersection, light, objects)) {// TURN OFF SHADOWS FOR NOW
//			continue;
//		}
		
		resultLight += standardShadingFormula(camera, light, intersection);
	}
	
	return RGB(resultLight);
}

vec4 Shader::standardShadingFormula(Camera camera, Light light, Intersection intersection) {

	GameObject* obj = intersection.getObject();

	vec3 lightDirection;
	double attenuation = 1.0f;
	if (light.isDirectional()) {
		lightDirection = normalize(light.getPosition());
	}
	else {
		vec3 _light_direction = light.getPosition() - intersection.getPosition();
		lightDirection = normalize(_light_direction);
		attenuation = 1.0f / computeDistanceFromTo(intersection, light); // FIX THIS IF NEEDED (USE FUNCTION AND MAYBE DIFFERENT FORMULA (1/r^2)???)
	}

	vec3 half_angle = normalize(lightDirection + camera.getDirection());
	vec3 surfaceNormal = normalize(obj->getNormal(intersection.getPosition()));

	vec4 diffuse_part = obj->getDiffuse() * light.getColor() * max(0.0f, dot(surfaceNormal, lightDirection));
	vec4 specular_part = obj->getSpecular() * light.getColor() * pow(max(0.0f, dot(surfaceNormal, half_angle)), obj->getShininess()); // phong illumination

	return diffuse_part + specular_part;
}
