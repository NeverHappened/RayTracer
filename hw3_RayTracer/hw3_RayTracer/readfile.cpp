using namespace std;
#include "readfile.h"
#include "Sphere.h"
#include "Perspective.h"
#include "WorldInit.h"
#include "Triangle.h"


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

WorldInit readfile(const char* filename)
{
	vec3 eyeinit(0.0, 0.0, 5.0);
	vec3 upinit(0.0, 1.0, 0.0);
	vec3 center(0.0, 0.0, 0.0);
	int w = 600, h = 400; // width and height 
	float fovy = 90.0; // For field of view

	vec3 attenuation = vec3(1.0, 0.0, 0.0);

	vec4 ambient(0.2, 0.2, 0.2, 1.0);
	vec4 specular(0.0, 0.0, 0.0, 1.0);
	vec4 diffuse(0.0, 0.0, 0.0, 1.0);
	vec4 emission(0.0, 0.0, 0.0, 1.0);
    float shininess = 1.0f;
	int maxdepth = 5;

	vector<GameObject*> objects = vector<GameObject*>();
	vector<Light> lights = vector<Light>();

	vec3 *vertices = NULL; // array of vertices
	int verticesCreated = 0;

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
				float values[10]; // Position and color for light, colors for others
									// Up to 10 params for cameras.  
				bool validinput; // Validity of input 

								 // Process the light, add it to database.
								 // Lighting Command
				if (cmd == "directional") {
					validinput = readvals(s, 6, values); // Position/color for lts.
					if (validinput) {
						float x = values[0];
						float y = values[1];
						float z = values[2];
						float w = 0.0f;

						float r = values[4];
						float g = values[5];
						float b = values[6];
						float a = 1.0f;
						vec4 position(x, y, z, w);
						vec4 color(r, g, b, a);
						Light light(position, color, attenuation);
						lights.push_back(light);
					}
				}
				else if (cmd == "point") {
					validinput = readvals(s, 6, values); // Position/color for lts.
					if (validinput) {
						float x = values[0];
						float y = values[1];
						float z = values[2];
						float w = 1.0f;

						float r = values[4];
						float g = values[5];
						float b = values[6];
						float a = 1.0f;
						vec4 position(x, y, z, w);
						vec4 color(r, g, b, a);
						Light light(position, color, attenuation);
						lights.push_back(light);
					}
				}
				else if (cmd == "attenuation") {
					validinput = readvals(s, 3, values); // Position/color for lts.
					if (validinput) {
						float constant = values[0];
						float linear = values[1];
						float quadratic = values[2];
						
						attenuation = vec3(constant, linear, quadratic);
					}
				}
				else if (cmd == "ambient") {
					validinput = readvals(s, 3, values); // colors 
					if (validinput) {
						ambient = vec4(values[0], values[1], values[2], 1.0);
					}
				}
				else if (cmd == "diffuse") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						diffuse = vec4(values[0], values[1], values[2], 1.0);
					}
				}
				else if (cmd == "specular") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						specular = vec4(values[0], values[1], values[2], 1.0);
					}
				}
				else if (cmd == "emission") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						emission = vec4(values[0], values[1], values[2], 1.0);
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
				else if (cmd == "maxdepth") {
					validinput = readvals(s, 1, values); // 10 values eye cen up fov
					if (validinput) {
						maxdepth = (int)values[0];
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

				else if (cmd == "sphere") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						float x = values[0];
						float y = values[1];
						float z = values[2];
						vec3 location(x, y, z);
						float radius = values[3];
						mat4 transform = transfstack.top();

						Sphere* sphere = new Sphere(location, radius, ambient, diffuse, specular, shininess, emission, transform);
						objects.push_back(sphere);
					}
				}
				else if (cmd == "maxverts") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						int maxverts = values[0];
						vertices = new vec3[maxverts];
					}
				}
				else if (cmd == "maxvertnorms") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						int maxvertnorms = values[0];
					}
				}
				else if (cmd == "vertex") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						float x = values[0];
						float y = values[1];
						float z = values[2];

						vertices[verticesCreated++] = vec3(x, y, z);
					}
				}
				else if (cmd == "vertexnormal") {
					validinput = readvals(s, 6, values);
					if (validinput) {
						float x = values[0];// vertex coordinate
						float y = values[1];
						float z = values[2];

						float nx = values[3];// vertex normal
						float ny = values[4];
						float nz = values[5];

						// create VertexNormal(x, y, z, nx, ny, nz) and put it somewhere
					}
				}
				else if (cmd == "tri") {
					validinput = readvals(s, 6, values);
					if (validinput) {
						int v1 = (int)values[0];// vertex indexes that form a triangle
						int v2 = (int)values[1];
						int v3 = (int)values[2];

						// create Triangle(v1, v2, v3)
						Triangle* triangle = new Triangle(vertices[v1], vertices[v2], vertices[v3], ambient, diffuse, specular, shininess, emission, transform);
						objects.push_back(triangle);
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
	}
	else {
		cerr << "Unable to Open Input Data File " << filename << "\n";
		throw 2;
	}

	Camera camera(eyeinit, upinit, center);

	float aspect = w / (float)h;
	float fovyRadians = radians(fovy);
	float fovx = degrees(2 * atan(tan(fovyRadians / 2.0f) * aspect));
	float zNear = 0.1f;
	float zFar = 99.0f;
	Perspective perspective(w, h, fovy, fovx, zNear, zFar);

	return WorldInit(camera, perspective, objects, lights, maxdepth);
}
