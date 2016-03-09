#include <iostream>
#include "FreeImageHelper.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <chrono>
#include <ctime>

#include "readfile.h"
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


using namespace std;
using namespace glm;

Ray findRayForPixel(Camera camera, Perspective perspective, PixelSample sample) {

	vec3 rayStart = camera.getEye();
	vec3 lookVector = camera.getEye() - camera.getCenter();

	vec3 w = normalize(lookVector);
	vec3 u = normalize(cross(camera.getUp(), w));
	vec3 v = normalize(cross(w, u));

	float tanX = (float)tan(radians(perspective.getFovx()) / 2.0);
	float tanY = (float)tan(radians(perspective.getFovy()) / 2.0);

	float widthCenter = perspective.getW() / 2.0f;
	float heightCenter = perspective.getH() / 2.0f;

	float normalizedXLocation = ((sample.getPixelXCenter() - widthCenter) / widthCenter);
	float normalizedYLocation = ((heightCenter - sample.getPixelYCenter()) / heightCenter);

	float alpha = tanX * normalizedXLocation;
	float beta = tanY * normalizedYLocation;
	vec3 _rayDirection = alpha * u + beta * v - w;
	vec3 rayDirection = normalize(_rayDirection);

	return Ray(rayStart, rayDirection);
}

void countProgress(PixelSample sample, ImageToRender image, Perspective perspective, 
	std::chrono::time_point<std::chrono::system_clock> start) {
	static int reached = -1;
	static bool onepercentmessage = false;

	int pixelsProcessed = (sample.rowPixel() + 1) * perspective.getW() + (sample.columnPixel() + 1);
	int percent = (int) floor((pixelsProcessed / (double)image.getTotalPixels()) * 100);
	if (percent / 10 != reached && percent % 10 == 0) {
		reached += 1;
		cout << percent << " % complete." << endl;
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		cout << "It took about " << (elapsed_seconds.count() / 60) << " minutes." << endl;
	}

	if (percent >= 1.0 && percent < 2.0 && !onepercentmessage) {
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		cout << "About 1 % rendered." << endl;
		cout << "It took about " << elapsed_seconds.count() << " seconds." << endl;
		onepercentmessage = true;
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
	int maxReflectionDepth = init.maxdepth;
	Shader shader = Shader(lights, maxReflectionDepth);

	cout << "Start rendering..." << endl;
	auto start = std::chrono::system_clock::now();
	while (sampler.anySamples()) {
		PixelSample sample = sampler.getSample();
		int x = sample.rowPixel();
		int y = sample.columnPixel();
		Ray viewRay = findRayForPixel(camera, perspective, sample);
		Intersection closestIntersection = IntersectionHelper::findClosestIntersection(viewRay, objects);
		RGB color = RGB(shader.shade(camera, closestIntersection, viewRay, sample, objects));

		image.fill(sample, color);
		countProgress(sample, image, perspective, start);
	}

	string fileOutput = init.fileOutput;
	image.outputToFile(fileOutput);
}


void main() {
	rayTracer();
	return;
}
