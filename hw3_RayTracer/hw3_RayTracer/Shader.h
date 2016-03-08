#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "Light.h"
#include "RGB.h"
#include "PixelSample.h"
#include "Intersection.h"
#include "IntersectionHelper.h"
#include "Camera.h"

using namespace std;

class Shader {
protected:
	vector<Light> lights;
	int maxReflectionDepth;

private:
	vec4 computeLightOnHit(Camera camera, Intersection intersection, Ray ray, vector<GameObject*> objects);
	bool lightVisibleFromHere(Intersection intersection, Light light, vector<GameObject*> objects);
	double computeDistanceFromTo(Intersection intersection, Light light);
	vec4 standardShadingFormula(Camera camera, Light light, Intersection intersection);
	vec4 computeReflections(int currentDepth);

public:
	Shader(vector<Light> lights, int maxReflectionDepth);
	~Shader();

	void addLight(Light light);
	RGB Shader::shade(Camera camera, Intersection intersection, Ray ray, PixelSample sample, vector<GameObject*> objects, int currentDepth = 0);
};