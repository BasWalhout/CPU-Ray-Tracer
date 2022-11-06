#pragma once
#include "Plane.h"

class FinitePlane : public Plane
{

public:

	FinitePlane(vec3 a_midpoint, vec3 a_rotationDegrees, vec2 a_halfSize, Material a_material);

	const HitResult IntersectsWithRay(const Ray& a_ray) const override;

private:

	vec2 halfsize;

protected:

	const BoundingBox CalculateBoundingBox() const override;

};