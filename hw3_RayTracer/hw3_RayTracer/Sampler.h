#pragma once

#include "PixelSample.h"

class Sampler {
private:
	bool samplesLeft;

	int width;
	int height;

	int currentPixelRow;
	int currentPixelColumn;
public:
	Sampler(int width, int height);

	PixelSample getSample();
	bool anySamples();
};