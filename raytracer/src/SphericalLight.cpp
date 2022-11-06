#include "headers/SphericalLight.h"

SphericalLight::SphericalLight(vec3 a_position, Color a_color, float a_intensity) :
	position(a_position), Light(a_color, a_intensity)
{}

Color SphericalLight::GetIntensityAt(const vec3& a_position) const {

	a_position;
	return this->color * this->intesity;

}

vec3 SphericalLight::GetDirectionTo(const vec3& a_from) const {

	return vec3(this->position - a_from).normalize();

}

float SphericalLight::GetMaximalDistanceTo(const vec3& a_from) const {

	return vec3(this->position - a_from).length();

}