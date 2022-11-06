#pragma once
#include "Surface.h"

class Plane : public Surface {

public:

	Plane(vec3 a_midpoint, vec3 a_rotationDegrees, Material a_material, bool a_hasboundingbox = false);

	virtual const HitResult IntersectsWithRay(const Ray& a_ray) const override;
	vec3 GetNormalAt(const vec3& a_position) const override;

protected:

	const BoundingBox CalculateBoundingBox() const override;

};