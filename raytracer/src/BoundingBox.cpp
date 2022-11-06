#include "headers/BoundingBox.h"
#include "headers/Ray.h"

BoundingBox::BoundingBox(){}

BoundingBox::BoundingBox(vec3 a_midpoint, vec3 a_halfsize):
	midpoint(a_midpoint),
	halfsize(a_halfsize)
{}

const bool BoundingBox::IntersectsWithRay(const Ray& a_ray, float& a_result) const {

	bool hit = true;

	vec3 minBound = this->midpoint - this->halfsize; //Bottom-near-left corner.
	vec3 maxBound = this->midpoint + this->halfsize; //Top-far-right corner

	vec3 rayDirection = a_ray.getDirection();
	vec3 rayOrigin = a_ray.getOrigin();

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
				a_result = 0.f;
				hit =  false;
			}

		}

	}

	if (hit) {
		a_result = tFirst;
		return true;
	}
	else return false;

}

const BoundingBox BoundingBox::Combine(const BoundingBox& a_right) const{

	vec3 points[4] = {};
	points[0] = this->GetMinBound();
	points[1] = this->GetMaxBound();
	points[2] = a_right.GetMinBound();
	points[3] = a_right.GetMaxBound();

	vec3 minpoint = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	vec3 maxpoint = vec3(FLT_MIN, FLT_MIN, FLT_MIN);

	for (int point = 0; point < 4; ++point) {
		for (int axis = 0; axis < 3; ++axis) {

			if (points[point].v[axis] < minpoint.v[axis]) {
				minpoint.v[axis] = points[point].v[axis];
			}
			if (points[point].v[axis] > maxpoint.v[axis]) {
				maxpoint.v[axis] = points[point].v[axis];
			}

		}
	}

	vec3 newHalfsize = (maxpoint - minpoint) *0.5f;
	vec3 newMidpoint = minpoint + newHalfsize;

	return BoundingBox(newMidpoint, newHalfsize);

}

const vec3 BoundingBox::GetMaxBound() const {

	return this->midpoint + this->halfsize;

}

const vec3 BoundingBox::GetMinBound() const {

	return this->midpoint - this->halfsize;

}

const vec3& BoundingBox::GetMidpoint() const {

	return this->midpoint;

}