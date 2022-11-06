#pragma once
#include "Surface.h"

class Cuboid : public Surface 
{

public:

	Cuboid(vec3 a_midpoint, vec3 a_rotationDegrees, vec3 a_halfsize, Material a_material);

	const HitResult IntersectsWithRay(const Ray& a_ray) const override;
	vec3 GetNormalAt(const vec3& a_position) const;

private:

	vec3 halfsize;

protected:

	const BoundingBox CalculateBoundingBox() const override;

};