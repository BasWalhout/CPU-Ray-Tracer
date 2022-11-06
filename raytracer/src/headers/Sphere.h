#pragma once
#include "Surface.h"

class Sphere : public Surface{

public:

	Sphere(vec3 a_midpoint, float a_radius, Material a_material);

	const HitResult IntersectsWithRay(const Ray& a_ray) const override;
	vec3 GetNormalAt(const vec3& a_position) const override;

private:

	float radius;

protected:

	const BoundingBox CalculateBoundingBox() const override;
	
};