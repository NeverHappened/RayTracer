#include "GameObject.h"

 vec4 GameObject::getAmbient() const{
	return ambient;
}

 vec4 GameObject::getDiffuse() const {
	 return diffuse;
 }


 vec4 GameObject::getSpecular() const {
	 return specular;
 }

 float GameObject::getShininess() const {
	 return shininess;
 }

 mat4 GameObject::getTransform() const {
	 return transform;
 }