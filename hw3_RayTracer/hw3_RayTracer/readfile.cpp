/*****************************************************************************/
/* This is the program skeleton for homework 2 in CS 184 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix 
// transformations for a stack (matransform) and to rightmultiply the 
// top of a stack.  These functions are given to aid in setting up the 
// transformations properly, and to use glm functions in the right way.  
// Their use is optional in your program.  


// The functions readvals and readfile do basic parsing.  You can of course 
// rewrite the parser as you wish, but we think this basic form might be 
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE. 
// Read the other parts to get a context of what is going on. 

/*****************************************************************************/
// FOR NOW JUST CREATE HARDCODED OBJECTS AND TRANSFORMATIONS; WHEN ALL STUFF FOR RENDERING WILL BE IMPLEMENTED, UNCOMMENT AND FIX ALL ERRORS
/*
// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "Transform.h" 

using namespace std;
#include "variables.h" 
#include "readfile.h"

// You may not need to use the following two functions, but it is provided
// here for convenience

// The function below applies the appropriate transform to a 4-vector
void matransform(stack<mat4> &transfstack, float* values)
{
	mat4 transform = transfstack.top();
	vec4 valvec = vec4(values[0], values[1], values[2], values[3]);
	vec4 newval = transform * valvec;
	for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack)
{
	mat4 &T = transfstack.top();
	T = T * M;
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream &s, const int numvals, float* values)
{
	for (int i = 0; i < numvals; i++) {
		s >> values[i];
		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n";
			return false;
		}
	}
	return true;
}

void readfile(const char* filename)
{
	string str, cmd;
	ifstream in;
	in.open(filename);
	if (in.is_open()) {

		// I need to implement a matrix stack to store transforms.  
		// This is done using standard STL Templates 
		stack <mat4> transfstack;
		transfstack.push(mat4(1.0));  // identity

		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
				// Ruled out comment and blank lines 

				stringstream s(str);
				s >> cmd;
				int i;
				float values[10]; // Position and color for light, colors for others
									// Up to 10 params for cameras.  
				bool validinput; // Validity of input 

								 // Process the light, add it to database.
								 // Lighting Command
				if (cmd == "light") {
					if (numused == numLights) { // No more Lights 
						cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
					}
					else {
						validinput = readvals(s, 8, values); // Position/color for lts.
						if (validinput) {
							float x = values[0];
							float y = values[1];
							float z = values[2];
							float w = values[3];

							float r = values[4];
							float g = values[5];
							float b = values[6];
							float a = values[7];

							int lightOffset = 4 * numused;

							lightposn[lightOffset] = x;
							lightposn[lightOffset + 1] = y;
							lightposn[lightOffset + 2] = z;
							lightposn[lightOffset + 3] = w;

							lightcolor[lightOffset] = r;
							lightcolor[lightOffset + 1] = g;
							lightcolor[lightOffset + 2] = b;
							lightcolor[lightOffset + 3] = a;

							++numused;
						}
					}
				}
				else if (cmd == "ambient") {
					validinput = readvals(s, 4, values); // colors 
					if (validinput) {
						for (i = 0; i < 4; i++) {
							ambient[i] = values[i];
						}
					}
				}
				else if (cmd == "diffuse") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						for (i = 0; i < 4; i++) {
							diffuse[i] = values[i];
						}
					}
				}
				else if (cmd == "specular") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						for (i = 0; i < 4; i++) {
							specular[i] = values[i];
						}
					}
				}
				else if (cmd == "emission") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						for (i = 0; i < 4; i++) {
							emission[i] = values[i];
						}
					}
				}
				else if (cmd == "shininess") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						shininess = values[0];
					}
				}
				else if (cmd == "size") {
					validinput = readvals(s, 2, values);
					if (validinput) {
						w = (int)values[0]; h = (int)values[1];
					}
				}
				else if (cmd == "camera") {
					validinput = readvals(s, 10, values); // 10 values eye cen up fov
					if (validinput) {
						eyeinit = vec3(values[0], values[1], values[2]);
						center = vec3(values[3], values[4], values[5]);
						vec3 not_normalized_up_init = vec3(values[6], values[7], values[8]);
						upinit = Transform::upvector(not_normalized_up_init, eyeinit - center);
						fovy = values[9];
					}
				}

				else if (cmd == "sphere" || cmd == "cube" || cmd == "teapot") {
					if (numobjects == maxobjects) { // No more objects 
						cerr << "Reached Maximum Number of Objects " << numobjects << " Will ignore further objects\n";
					}
					else {
						validinput = readvals(s, 1, values);
						if (validinput) {
							object * obj = &(objects[numobjects]);
							obj->size = values[0];

							for (i = 0; i < 4; i++) {
								(obj->ambient)[i] = ambient[i];
								(obj->diffuse)[i] = diffuse[i];
								(obj->specular)[i] = specular[i];
								(obj->emission)[i] = emission[i];
							}
							obj->shininess = shininess;

							obj->transform = transfstack.top();

							if (cmd == "sphere") {
								obj->type = sphere;
							}
							else if (cmd == "cube") {
								obj->type = cube;
							}
							else if (cmd == "teapot") {
								obj->type = teapot;
							}
						}
						++numobjects;
					}
				}

				else if (cmd == "translate") {
					validinput = readvals(s, 3, values);
					if (validinput) {

						float tx = values[0];
						float ty = values[1];
						float tz = values[2];
						mat4 M = Transform::translate(tx, ty, tz);

						rightmultiply(M, transfstack);
					}
				}
				else if (cmd == "scale") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						float sx = values[0];
						float sy = values[1];
						float sz = values[2];
						mat4 M = Transform::scale(sx, sy, sz);

						rightmultiply(M, transfstack);
					}
				}
				else if (cmd == "rotate") {
					validinput = readvals(s, 4, values);
					if (validinput) {

						float x = values[0];
						float y = values[1];
						float z = values[2];
						vec3 axis = glm::normalize(vec3(x, y, z));
						float angle = values[3];

						mat3 M_3 = Transform::rotate(angle, axis);

						vec4 translationColumn = vec4(0.0f, 0.0f, 0.0f, 1.0f);
						mat4 M = mat4(vec4(M_3[0], 0.0f),
							vec4(M_3[1], 0.0f),
							vec4(M_3[2], 0.0f),
							translationColumn);

						rightmultiply(M, transfstack);
					}
				}

				// I include the basic push/pop code for matrix stacks
				else if (cmd == "pushTransform") {
					transfstack.push(transfstack.top());
				}
				else if (cmd == "popTransform") {
					if (transfstack.size() <= 1) {
						cerr << "Stack has no elements.  Cannot Pop\n";
					}
					else {
						transfstack.pop();
					}
				}

				else {
					cerr << "Unknown Command: " << cmd << " Skipping \n";
				}
			}
			getline(in, str);
		}

		// Set up initial position for eye, up and amount
		// As well as booleans 

		eye = eyeinit;
		up = upinit;
		amount = 5;
		sx = sy = 1.0;  // keyboard controlled scales in x and y 
		tx = ty = 0.0;  // keyboard controllled translation in x and y  
	}
	else {
		cerr << "Unable to Open Input Data File " << filename << "\n";
		throw 2;
	}
}
*/