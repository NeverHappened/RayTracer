#include "Shader.h"

Shader::Shader(vector<Light> lights) : lights(lights)
{}

Shader::~Shader()
{}

void Shader::addLight(Light light) {
	lights.push_back(light);
}

RGB Shader::shade(GameObject* obj, Ray ray) {
	if (hit(obj)) {
		return shade(obj);
	}
	else {
		return RGB(25, 25, 25);
	}
}

bool Shader::hit(GameObject* obj) {
	return obj != NULL;
}

/*

vec4 ComputeLight(vec3 fragment_position, vec3 surface_normal, vec3 eye_direction) {
	vec4 result = ambient + emission;

	for (int i = 0; i < numused; i++) {
		vec4 light_position = lightposn[i];
		vec4 light_color = lightcolor[i];

		vec3 light_direction;
		if (light_position.w == 0) {
			light_direction = normalize(light_position.xyz);
		}
		else {
			vec3 _light_direction = light_position.xyz - fragment_position;
			light_direction = normalize(_light_direction);
		}

		vec3 half_angle = normalize(light_direction + eye_direction);

		vec4 diffuse_part = diffuse * light_color * max(0.0, dot(surface_normal, light_direction));
		vec4 specular_part = specular * light_color * pow(max(0.0, dot(surface_normal, half_angle)), shininess); // phong illumination

		vec4 total_light_intensity_part = diffuse_part + specular_part;
		result += total_light_intensity_part;
	}

	return result;
}

vec3 fragment_position() {
	vec4 _mypos = gl_ModelViewMatrix * myvertex;
	return _mypos.xyz / _mypos.w;
}

vec3 eye_position() {
	return vec3(0, 0, 0);
}

vec3 eye_direction() {
	return normalize(eye_position() - fragment_position());
}

vec3 fragment_normal() {
	vec3 _normal = (gl_ModelViewMatrixInverseTranspose * vec4(mynormal, 0.0)).xyz;
	vec3 normal = normalize(_normal);
	return normal;
}
*/