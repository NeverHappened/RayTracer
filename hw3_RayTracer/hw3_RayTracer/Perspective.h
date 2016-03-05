#pragma once

class Perspective {
private:
	int w, h; // width and height 
	float fovy; // For field of view
	float aspect;
	float zNear;
	float zFar;

public:
	Perspective(int w, int h, float fovy, float zNear, float zFar);
	~Perspective();

	int getW();
	int getH();
	float getFovy();
	float getAspect();
	float getZNear();
	float getZFar();
};