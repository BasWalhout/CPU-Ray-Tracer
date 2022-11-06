#pragma once
#include "../../../MathLibrary/MathLibrary.h"
#include "BoundingBox.h"
#include "HitResult.h"
#include "Material.h"

class Ray;

class Surface {

public: 

	virtual const HitResult IntersectsWithRay(const Ray& a_ray) const = 0;
	virtual vec3 GetNormalAt(const vec3& a_position) const = 0;
	const BoundingBox& GetBoundingBox() const;
	const Material& GetMaterial() const;
	const bool HasBoundingBox() const;

protected:

	Surface(const vec3& a_translation, const vec3& a_rotationDegrees, Material a_material, bool a_hasBoundingBox = true);

	const mat4& GetTranslation() const;
	mat4 SetTranslation(const vec3& a_translation);

	const mat4& GetOrientation() const;
	mat4 SetOrientation(const vec3& a_rotationDegrees);

	virtual const BoundingBox CalculateBoundingBox() const = 0;

	Material material;

	mat4 translation;
	mat4 orientation;

	const bool hasBounds;
	BoundingBox bounds;

};