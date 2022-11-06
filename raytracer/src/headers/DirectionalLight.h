#pragma once
#include "Light.h"

class DirectionalLight : public Light {

public:

	DirectionalLight(vec3 a_direction, Color a_color, float a_intensity = 1.f);

	Color GetIntensityAt(const vec3& a_position) const override;
	vec3 GetDirectionTo(const vec3& a_from) const override;
	float GetMaximalDistanceTo(const vec3& a_from) const override;

private:

	vec3 direction;

};