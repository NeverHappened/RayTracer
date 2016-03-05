#pragma once

class PixelSample {

private:
	int pixelRow;
	int pixelColumn;

public:
	PixelSample(int pixelRow, int pixelColumn);
	~PixelSample();
	float getPixelYCenter() const;
	float getPixelXCenter() const;

	int rowPixel() const;
	int columnPixel() const;
};