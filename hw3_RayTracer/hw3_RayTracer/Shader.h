#pragma once

#include <vector>
#include "Light.h"
#include "RGB.h"
#include "GameObject.h"

using namespace std;

class Shader {
protected:
	vector<Light> lights;
	bool hit(GameObject* obj);

public:
	Shader(vector<Light> lights);
	~Shader();

	void addLight(Light light);
	RGB Shader::shade(GameObject* obj, Ray ray);
};