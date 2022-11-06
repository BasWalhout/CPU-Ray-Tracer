#include "headers/Cuboid.h"

Cuboid::Cuboid(vec3 a_midpoint, vec3 a_rotationDegrees, vec3 a_halfsize, Material a_material):
	Surface(a_midpoint, a_rotationDegrees, a_material),
	halfsize(a_halfsize)
{
	this->bounds = this->CalculateBoundingBox();
}

const HitResult Cuboid::IntersectsWithRay(const Ray& a_ray) const{

	bool hit = true;
	float distance = 0.f;

	vec3 minBound = halfsize * -1.f; //Bottom-near-left corner, since we want to calculate this in objectspace, the midpoint is the origin(0,0,0).
	vec3 maxBound = halfsize; //Top-far-right corner

	mat4 toObjectSpace = (this->translation * this->orientation).inverse();

	vec3 rayOrigin = (toObjectSpace * vec4(a_ray.getOrigin(), 1.f)).toVec3();
	vec3 rayDirection = toObjectSpace * a_ray.getDirection();

	float tFirst = FLT_MIN, tLast = FLT_MAX;
	float tempFirst, tempLast;

	for (int i = 0; i < 3; ++i) {

		if (rayDirection.v[i] == 0.f) {
			if (rayOrigin.v[i] < minBound.v[i] || rayOrigin.v[i] > maxBound.v[i]) { // If the ray's origin is before the minbound or behind the maxbound.
				hit = false;
			}
		}
		else {

			float inverseDirectionI = 1.f / rayDirection.v[i]; // This makes sure that -0.f returns the right infinite amount.

			tempFirst = (minBound.v[i] - rayOrigin.v[i]) * inverseDirectionI;
			tempLast = (maxBound.v[i] - rayOrigin.v[i]) * inverseDirectionI;

			if (tempFirst > tempLast) { // The order is important for next comparisons. The first value has to be smaller than the last value.
				std::swap(tempFirst, tempLast);
			}

			if (tempFirst > tFirst) {
				tFirst = tempFirst;
			}
			if (tempLast < tLast) {
				tLast = tempLast;
			}

			if (tFirst > tLast || tLast < 0.f) {
				hit = false;
			}

		}

	}

	if (hit) {
		distance = tFirst;
	}

	return HitResult(hit, distance, a_ray, *this);

}

vec3 Cuboid::GetNormalAt(const vec3& a_position) const {

	mat4 scale = mat4::scale(this->halfsize * 2.f);
	mat4 toObjectspace = (this->translation * this->orientation * scale).inverse();

	vec3 positionInObjectspace = (toObjectspace * vec4(a_position, 1.f)).toVec3();

	float largestDistance = 0.f;
	int axis = -1;

	for (int i = 0; i < 3; ++i) {

		if (fabsf(positionInObjectspace.v[i]) > fabsf(largestDistance)) {
			largestDistance = positionInObjectspace.v[i];
			axis = i;
		}

	}

	if (!(axis < 0) && (axis < 3)) {
		vec4 normal4 = this->orientation.axes[axis];
		vec3 normal3 = normal4.toVec3();
		if (largestDistance < 0.f) {
			normal3 *= -1.f;
		}
		return normal3;
	}
	
	
	return vec3();

}

const BoundingBox Cuboid::CalculateBoundingBox() const {

	const vec3 midpoint = this->translation.translation3;
	vec3 points[8] = {};

	const vec3 U = this->orientation.axis_X3 * this->halfsize.m_X;
	const vec3 V = this->orientation.axis_Y3 * this->halfsize.m_Y;
	const vec3 W = this->orientation.axis_Z3 * this->halfsize.m_Z;

	points[0] = midpoint - V - U - W;
	points[1] = midpoint - V - U + W;
	points[2] = midpoint - V + U - W;
	points[3] = midpoint - V + U + W;
	points[4] = midpoint + V - U - W;
	points[5] = midpoint + V - U + W;
	points[6] = midpoint + V + U - W;
	points[7] = midpoint + V + U + W;

	vec3 minbound = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	vec3 maxbound = vec3(FLT_MIN, FLT_MIN, FLT_MIN);

	for (int point = 0; point < 8; ++point) {
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