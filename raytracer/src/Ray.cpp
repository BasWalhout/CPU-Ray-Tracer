#include "headers/Ray.h"

Ray::Ray():
	origin(vec3()),
	unitDirection(vec3())
{}

Ray::Ray(vec3 a_origin, vec3 a_unitDirection):
	origin(a_origin),
	unitDirection(a_unitDirection.normalize())
{}

const vec3& Ray::getOrigin() const {

	return this->origin;

}

const vec3& Ray::getDirection() const {

	return this->unitDirection;

}