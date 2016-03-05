#pragma once

#include "FreeImage.h"
#include <string>

using namespace std;

class FreeImageHelper {
private:
	FIBITMAP* img;
public:
	FreeImageHelper(BYTE* pixels, int width, int height);
	~FreeImageHelper();

	void save(string withName);
};
