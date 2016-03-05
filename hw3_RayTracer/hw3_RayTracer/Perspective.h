#pragma once

class Perspective {
private:
	int w, h; 
	float fovy;
	float fovx;
	float aspect;
	float zNear;
	float zFar;

public:
	Perspective(int w, int h, float fovy, float fovx, float zNear, float zFar);
	~Perspective();

	int getW();
	int getH();
	float getFovy();
	float getFovx();
	float getAspect();
	float getZNear();
	float getZFar();
};