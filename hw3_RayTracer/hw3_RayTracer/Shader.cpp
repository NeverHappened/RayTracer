#include "Shader.h"

Shader::Shader(vector<Light> lights, int maxReflectionDepth) : lights(lights), maxReflectionDepth(maxReflectionDepth)
{}

Shader::~Shader()
{}

void Shader::addLight(Light light) {
	lights.push_back(light);
}

float distance(vec3 vect) {
	return sqrt(vect.x * vect.x +
		vect.y * vect.y +
		vect.z * vect.z);
}

vec3 correctPosition(vec3 initialPosition, vec3 directionOfCorrection, float epsilon = 0.005f) {
	return initialPosition + epsilon * directionOfCorrection;
}

Ray Shader::mirrorRay(Ray viewRay, Intersection intersection) {
	GameObject* obj = intersection.getObject();
	vec3 d = viewRay.getDirection();
	vec3 n = transformNormal(obj->getNormal(intersection.getPosition()), obj->getTransform());
	vec3 r = normalize(d - 2.0f * dot(d, n) * n);

	vec3 correctedStart = correctPosition(intersection.getPosition(), r);

	Ray bounce = Ray(correctedStart, r);
	return bounce;
}

vec4 Shader::computeReflections(Camera camera, Intersection intersection, Ray viewRay, PixelSample sample, vector<GameObject*> objects, int currentDepth) {
	GameObject* obj = intersection.getObject();
	Ray _mirrorRay = mirrorRay(viewRay, intersection);
	Intersection bounceIntersection = IntersectionHelper::findClosestIntersection(_mirrorRay, objects);
		
	return obj->getSpecular() * shade(camera, bounceIntersection, _mirrorRay, sample, objects, currentDepth + 1);
}

vec4 Shader::shade(Camera camera, Intersection intersection, Ray ray, PixelSample sample, vector<GameObject*> objects, int currentDepth) {
	if (intersection.isIntersection()) {
		bool recurseFurther = currentDepth < maxReflectionDepth;
		return computeLightOnHit(intersection, ray, objects) +
			(recurseFurther ? computeReflections(camera, intersection, ray, sample, objects, currentDepth) : vec4(0, 0, 0, 1));
		
	}
	else {
		return vec4(0, 0, 0, 1);
	}
}

bool Shader::lightVisibleFromHere(Intersection intersection, Light light, vector<GameObject*> objects) {
	vec3 lookToLightSource = light.getPosition() - intersection.getPosition();
	Ray rayToLightSource(correctPosition(intersection.getPosition(), lookToLightSource), normalize(lookToLightSource));

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


float Shader::computeDistanceFromTo(Intersection intersection, Light light) {
	vec3 lookToLightSource = light.getPosition() - intersection.getPosition();
	return distance(lookToLightSource);
}

vec4 Shader::computeLightOnHit(Intersection intersection, Ray ray, vector<GameObject*> objects) {
	GameObject* obj = intersection.getObject();
	vec4 resultLight = obj->getAmbient() + obj->getEmission();
	
	for (Light& light : lights) {
		if (!lightVisibleFromHere(intersection, light, objects)) {
			continue;
		}
		
		resultLight += standardShadingFormula(ray, light, intersection);
	}
	
	return resultLight;
}

vec3 Shader::transformNormal(vec3 normal, mat4 transform) {
	return normalize(vec3(transpose(inverse(transform)) * vec4(normalize(normal), 0.0)));
}

vec4 Shader::standardShadingFormula(Ray viewRay, Light light, Intersection intersection) {

	GameObject* obj = intersection.getObject();

	vec3 lightDirection;
	float attenuation = 1.0f;
	if (light.isDirectional()) {
		lightDirection = normalize(light.getPosition());
	}
	else {
		vec3 _light_direction = light.getPosition() - intersection.getPosition();
		lightDirection = normalize(_light_direction);
		float d = computeDistanceFromTo(intersection, light);
		float constant = light.getAttenuation().x;
		float linear = light.getAttenuation().y;
		float quadratic = light.getAttenuation().z;
		float attenuationFactor = constant + linear * d + quadratic * d * d;
		attenuation = 1.0f / attenuationFactor;
	}

	// initially its a camera position, but when its reflected - its a rays origin
	vec3 eyeDirection = normalize(viewRay.getStart() - intersection.getPosition());
	vec3 halfAngle = normalize(lightDirection + eyeDirection);
	vec3 surfaceNormal = transformNormal(obj->getNormal(intersection.getPosition()), obj->getTransform());

	float dotL = dot(surfaceNormal, lightDirection);
	float dotH = dot(surfaceNormal, halfAngle);

	float diffuse_coeff = max(0.0f, dotL);
	float specular_coeff = pow(max(0.0f, dotH), obj->getShininess());

	vec4 diffuse_part = obj->getDiffuse() * light.getColor() * diffuse_coeff;
	vec4 specular_part = obj->getSpecular() * light.getColor() * specular_coeff; // phong illumination

	return attenuation * (diffuse_part + specular_part);
}
