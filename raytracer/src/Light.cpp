#include "headers/Light.h"

Light::Light(Color a_color, float a_intensity) :
	color(a_color),
	intesity(a_intensity)
{}

Color Light::GetIntensityAt(const vec3& a_position) const{

	a_position;
	return Color();

}