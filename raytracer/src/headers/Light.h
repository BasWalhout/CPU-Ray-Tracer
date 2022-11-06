#pragma once
#include "../../../MathLibrary/MathLibrary.h"
#include "Color.h"

class Light {

public:

	virtual Color GetIntensityAt(const vec3& a_position) const = 0;
	virtual vec3 GetDirectionTo(const vec3& a_from) const = 0;
	virtual float GetMaximalDistanceTo(const vec3& a_from) const = 0;

protected:

	Light(Color a_color, float a_intesity = 1.f);
	Color color;
	float intesity;

};