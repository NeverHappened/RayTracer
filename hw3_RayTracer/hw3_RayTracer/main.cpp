#include <iostream>
#include "FreeImageHelper.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "GameObject.h"
#include "Sphere.h"
#include "Camera.h"
#include "Perspective.h"
#include "RGB.h"
#include "Sampler.h"
#include "ImageToRender.h"
#include "Shader.h"
#include "Intersection.h"
#include "IntersectionHelper.h"
#include "WorldInit.h"
#include "readfile.h"

using namespace std;
using namespace glm;

Ray findRayForPixel(Camera camera, Perspective perspective, PixelSample sample) {

	vec3 rayStart = camera.getEye();
	vec3 lookVector = camera.getEye() - camera.getCenter();

	vec3 w = normalize(lookVector);
	vec3 u = normalize(cross(camera.getUp(), w));
	vec3 v = normalize(cross(w, u));

	double tanX = tan(radians(perspective.getFovx()) / 2.0);
	double tanY = tan(radians(perspective.getFovy()) / 2.0);

	double widthCenter = perspective.getW() / 2.0f;
	double heightCenter = perspective.getH() / 2.0f;

	double normalizedXLocation = ((widthCenter - sample.getPixelXCenter()) / widthCenter);
	double normalizedYLocation = ((sample.getPixelYCenter() - heightCenter) / heightCenter);

	float alpha = tanX * normalizedXLocation;
	float beta = tanY * normalizedYLocation;
	vec3 _rayDirection = alpha * u + beta * v - w;
	vec3 rayDirection = normalize(_rayDirection);

	return Ray(rayStart, rayDirection);
}

void countProgress(PixelSample sample, ImageToRender image, Perspective perspective) {
	static int reached = -1;

	int pixelsProcessed = (sample.rowPixel() + 1) * perspective.getW() + (sample.columnPixel() + 1);
	int percent = (int) floor((pixelsProcessed / (double)image.getTotalPixels()) * 100);
	if (percent / 10 != reached && percent % 10 == 0) {
		reached += 1;
		cout << percent << " % of pixels processed." << endl;
	}
}

void rayTracer() {

	WorldInit init = readfile("scene.test");

	vector<GameObject*> objects = init.objects;
	Camera camera = init.camera;
	Perspective perspective = init.perspective;
	Sampler sampler(perspective.getW(), perspective.getH());
	ImageToRender image(perspective);
	vector<Light> lights = init.lights;
	Shader shader = Shader(lights);

	while (sampler.anySamples()) {
		PixelSample sample = sampler.getSample();
		Ray ray = findRayForPixel(camera, perspective, sample);
		Intersection closestIntersection = IntersectionHelper::findClosestIntersection(ray, objects);
		RGB color = shader.shade(camera, closestIntersection, ray, sample, objects);

		image.fill(sample, color);
		countProgress(sample, image, perspective);
	}

	image.outputToFile("test_image.png");
}


void main() {
	rayTracer();
	return;
}
