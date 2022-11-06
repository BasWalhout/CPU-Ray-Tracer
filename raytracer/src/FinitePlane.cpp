#include "headers/FinitePlane.h"

FinitePlane::FinitePlane(vec3 a_midpoint, vec3 a_rotationDegrees, vec2 a_halfSize, Material a_material) :
	Plane(a_midpoint, a_rotationDegrees, a_material, true),
	halfsize(a_halfSize)
{
	this->bounds = this->CalculateBoundingBox();
}

const HitResult FinitePlane::IntersectsWithRay(const Ray& a_ray) const{

	HitResult result = Plane::IntersectsWithRay(a_ray);

	if (result.hit) {

		vec3 hitpoint = result.GetPosition();
		vec3 origin = this->translation.translation3;

		vec3 originToPoint = hitpoint - origin;

		vec3 U = this->orientation.axis_X3;
		vec3 W = this->orientation.axis_Z3;

		float distanceU = U.dot(originToPoint);
		float distanceW = W.dot(originToPoint);

		if (fabsf(distanceU) <= halfsize.m_X && fabsf(distanceW) <= halfsize.m_Y) {
			return result;
		}
		else {
			result.hit = false;
			result.distance = 0.f;
		}

	}
	
	return result;

}

const BoundingBox FinitePlane::CalculateBoundingBox() const {

	const vec3 midpoint = this->translation.translation3;
	vec3 points[4] = {};

	const vec3 U = this->orientation.axis_X3 * this->halfsize.m_X;
	const vec3 W = this->orientation.axis_Z3 * this->halfsize.m_Y;

	
	points[0] = midpoint - (U - W);
	points[1] = midpoint - (U + W);
	points[2] = midpoint + (U - W);
	points[3] = midpoint + (U + W);

	vec3 minbound = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	vec3 maxbound = vec3(FLT_MIN, FLT_MIN, FLT_MIN);

	for (int point = 0; point < 4; ++point) {

		for (int axis = 0; axis < 3; ++axis) {
			
			if (points[point].v[axis] < minbound.v[axis]) {
				minbound.v[axis] = points[point].v[axis];
			}
			if (points[point].v[axis] > maxbound.v[axis]) {
				maxbound.v[axis] = points[point].v[axis];
			}

		}

	}

	vec3 boundshalfsize = (maxbound - minbound) * 0.5f;
	vec3 boundsmidpoint = minbound + boundshalfsize;

	return BoundingBox(boundsmidpoint, boundshalfsize);

}