#include "headers/Plane.h"

Plane::Plane(vec3 a_midpoint, vec3 a_rotationDegrees, Material a_material, bool a_hasboundingbox) :
	Surface(a_midpoint, a_rotationDegrees, a_material, a_hasboundingbox)
{
	this->bounds = this->CalculateBoundingBox();
}

const HitResult Plane::IntersectsWithRay(const Ray& a_ray) const{

	bool intersection = false;
	float distance = 0.f;

	vec3 normal = this->orientation.axis_Y3;

	vec3 ray_direction = a_ray.getDirection();

	if (ray_direction.length() != 0.f) {
		ray_direction.normalize();
	}

	float DdotN = ray_direction.dot(normal);

	if (std::fabsf(DdotN) > 0.01f * MathUtilities::EPSILON) {

		float x = ((this->translation.translation3 - a_ray.getOrigin()).dot(normal)) / DdotN;
		if (x >= 0.f) {
			intersection = true;
			distance = x;
		}

	}
	
	return HitResult(intersection, distance, a_ray, *this);

}

vec3 Plane::GetNormalAt(const vec3& a_position) const{

	a_position;

	return this->orientation.axis_Y3;

}

const BoundingBox Plane::CalculateBoundingBox() const {

	return BoundingBox();

}