#pragma once

#include "include/FreeImage.h"

using namespace std;

class FreeImageHelper {
private:
	FIBITMAP* img;
public:
	FreeImageHelper(int width, int height);
	~FreeImageHelper();

	void save();
};