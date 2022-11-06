#pragma once
#include "../../../MathLibrary/MathLibrary.h"

class Ray;

class BoundingBox {

public:

	BoundingBox();
	BoundingBox(vec3 a_midpoint, vec3 a_halfsize);

	const bool IntersectsWithRay(const Ray& a_ray, float& a_result) const;
	const BoundingBox Combine(const BoundingBox& a_right) const;
	const vec3 GetMinBound() const;
	const vec3 GetMaxBound() const;
	const vec3& GetMidpoint() const;

private:
	vec3 midpoint;
	vec3 halfsize;

};