#include "headers/Sphere.h"
#include "headers/Ray.h"

Sphere::Sphere(vec3 a_midpoint, float a_radius, Material a_material):
	Surface(a_midpoint, vec3(), a_material),
	radius(a_radius)
{
	this->bounds = this->CalculateBoundingBox();
}

const HitResult Sphere::IntersectsWithRay(const Ray& a_ray) const{


	// The formula used is |O * tD|^2 - R^2 = 0
	// Written to the form: f(x) = ax^2 + bx + c
	// The formula is then : D^2*t^2 + 2*O*D*t + O^2 - R^2
	// a = D^2, b = 2*O*D, c = O^2 - R^2, x = t
	// Then we try to solve f(x) = 0 for x

	// This transforms the origin of the ray with the midpoint of the sphere.
	// It is done because we want to solve the formula when the sphere is centered at the origin of the axes.
	vec3 midpoint = this->translation.translation3;
	vec3 ray_transformedOrigin = a_ray.getOrigin() - midpoint;
	vec3 ray_direction = a_ray.getDirection();

	//Make sure the length of the vector is 1.
	if (ray_direction.length() != 1.f) {
		ray_direction.normalize();
	}

	float a = ray_direction.dot(ray_direction); // This returns the length of the vector squared. Since the formula that is calculated is: A * A = A*A*cos(0 deg) = A^2.
	float b = 2 * ray_direction.dot(ray_transformedOrigin); // The last part after the * returns O * D since it projects the length of the vector onto the other vector.
	float c = ray_transformedOrigin.dot(ray_transformedOrigin) - (this->radius * this->radius); //This part resembles O^2 - R^2. O^2 is calculated the same way as a.

	float discriminant = b * b - 4 * a * c;

	bool intersection = false;
	float distance = 0.f;

	 //There will be no solutions when calculating the roots if the discriminant is below 0 . This means that there is no intersection between the sphere and ray.
		
	if (discriminant == 0) { //There will only be one solution when calculating the roots. This means that there is one intersection between the sphere and ray.

		float x = -0.5f * b / a;
		
		if (x > 0) {
			distance = x;
			intersection = true;
		}
			
	}

	else {

		intersection = true;

		float q = (b > 0) ?
			-0.5f * (b + sqrtf(discriminant)) :
			-0.5f * (b - sqrtf(discriminant));

		float x0 = q / a;
		float x1 = c / q;

		if (x0 < 0 || x1 < 0) {
			if (x0 < 0 && x1 < 0) {
				distance = 0;
				intersection = false;
			}
			else if (x0 < 0) {
				distance = x1;
			}
			else {
				distance = x0;
			}
		}
		else {

			if (x0 < x1) {
				distance = x0;
			}
			else {
				distance = x1;
			}

		}

		

	}

	return HitResult(intersection, distance, a_ray, *this);

}

vec3 Sphere::GetNormalAt(const vec3& a_position) const{

	return (a_position - this->translation.translation3) / this->radius;

}

const BoundingBox Sphere::CalculateBoundingBox() const {

	vec3 halfsize = vec3(radius, radius, radius);
	vec3 midpoint = this->translation.translation3;

	return BoundingBox(midpoint, halfsize);

}