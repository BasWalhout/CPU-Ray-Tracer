#include "headers/HitResult.h"

HitResult::HitResult() :
	hit(false),
	distance(0.f),
	ray(Ray()),
	surface(nullptr)
{}

HitResult::HitResult(bool a_hit, float a_distance, const Ray& a_ray, const Surface& a_surface):
	hit(a_hit),
	distance(a_distance),
	ray(a_ray),
	surface(&a_surface)
{}

const vec3 HitResult::GetPosition() const{

	return this->ray.getOrigin() + this->ray.getDirection() * this->distance;

}