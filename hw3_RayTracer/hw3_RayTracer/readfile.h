#pragma once

#include <stack>
#include <sstream>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include "Transform.h" 
#include "Light.h"
#include "Camera.h"
#include "WorldInit.h"

using namespace glm;
using namespace std;

void matransform(stack<mat4> &transfstack, float * values);
void rightmultiply(const mat4 & M, stack<mat4> &transfstack);
bool readvals(stringstream &s, const int numvals, float * values);
WorldInit readfile(const char * filename);
