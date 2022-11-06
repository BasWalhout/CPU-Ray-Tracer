#pragma once
#include "../../../MathLibrary/MathLibrary.h"

class Ray {

public:

	Ray();
	Ray(vec3 a_origin, vec3 a_unitDirection);

	const vec3& getOrigin() const;
	const vec3& getDirection() const;

private:

	vec3 origin;
	vec3 unitDirection;

};