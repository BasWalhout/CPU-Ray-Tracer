#include "headers/DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 a_direction, Color a_color, float a_intensity) :
	direction(a_direction), Light(a_color, a_intensity)
{}

Color DirectionalLight::GetIntensityAt(const vec3& a_position) const {

	a_position;
	return this->color * this->intesity;

}

vec3 DirectionalLight::GetDirectionTo(const vec3& a_from) const {

	a_from;

	return this->direction * -1.f;

}

float DirectionalLight::GetMaximalDistanceTo(const vec3& a_from) const {

	a_from;

	return FLT_MAX;

}