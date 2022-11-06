#pragma once
#include "../../../MathLibrary/MathLibrary.h"
#include "Ray.h"

class Surface;

struct HitResult {

	HitResult();
	HitResult(bool a_hit, float a_distance, const Ray& a_ray, const Surface& a_surface);

	const vec3 GetPosition() const;

	bool hit;
	float distance;

	Ray ray;
	const Surface* surface;

};