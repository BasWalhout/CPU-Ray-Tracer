#pragma once
#include "Light.h"

class SphericalLight : public Light {

public:

	SphericalLight(vec3 a_position, Color a_color, float a_intensity = 1.f);

	Color GetIntensityAt(const vec3& a_position) const override;
	vec3 GetDirectionTo(const vec3& a_from) const override;
	float GetMaximalDistanceTo(const vec3& a_from) const override;

private:

	vec3 position;

};