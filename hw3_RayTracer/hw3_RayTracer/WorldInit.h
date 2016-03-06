#pragma once

#include "Camera.h"
#include "Perspective.h"
#include "GameObject.h"
#include "Light.h"
#include <vector>

using namespace std;

class WorldInit {

public:
	Camera camera;
	Perspective perspective;
	vector<GameObject*> objects;
	vector<Light> lights;
	int maxdepth;

	class WorldInit(Camera camera, Perspective perspective, vector<GameObject*> objects, vector<Light> lights, int maxdepth) :
		camera(camera), perspective(perspective), objects(objects), lights(lights), maxdepth(maxdepth)
	{}
};