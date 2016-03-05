#include "Sampler.h"

Sampler::Sampler(int width, int height) :
	width(width), height(height), currentPixelRow(0), currentPixelColumn(0), samplesLeft(true)
{ }

PixelSample Sampler::getSample() {
	PixelSample sample(currentPixelRow, currentPixelColumn);

	if (currentPixelColumn == width - 1 && currentPixelRow == height - 1) {
		samplesLeft = false;
	}
	else if (currentPixelColumn == width - 1) {
		currentPixelRow++;
		currentPixelColumn = 0;
	}
	else {
		currentPixelColumn++;
	}

	return sample;
};

bool Sampler::anySamples() {
	return samplesLeft;
}
