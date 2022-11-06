#include "headers/Surface.h"

Surface::Surface(const vec3& a_translation, const vec3& a_rotationDegrees, Material a_material, bool a_hasBoundingbox):
	material(a_material),
	hasBounds(a_hasBoundingbox)
{

	translation = mat4::translate(a_translation);

	mat4 temporaryOrientation = mat4(
		vec3(1.f, 0.f, 0.f), 0.f,
		vec3(0.f, 1.f, 0.f), 0.f,
		vec3(0.f, 0.f, 1.f), 0.f,
		vec3(0.f, 0.f, 0.f), 1.f);

	mat4 rotation =
		mat4::rotateZ(a_rotationDegrees.m_Z * MathUtilities::DEG2RAD) *
		mat4::rotateY(a_rotationDegrees.m_Y * MathUtilities::DEG2RAD) *
		mat4::rotateX(a_rotationDegrees.m_X * MathUtilities::DEG2RAD);

	orientation = temporaryOrientation * rotation;

}

const Material& Surface::GetMaterial() const{

	return this->material;

}

const bool Surface::HasBoundingBox() const {

	return this->hasBounds;

}

const BoundingBox& Surface::GetBoundingBox() const{

	return this->bounds;

}

const mat4& Surface::GetTranslation() const {

	return this->translation;

}

mat4 Surface::SetTranslation(const vec3& a_translation) {

	this->translation = mat4::translate(a_translation);
	return this->translation;

}

const mat4& Surface::GetOrientation() const {

	return this->orientation;

}

mat4 Surface::SetOrientation(const vec3& a_rotationDegrees) {

	mat4 temporaryOrientation = mat4(
		vec3(1.f, 0.f, 0.f), 0.f,
		vec3(0.f, 1.f, 0.f), 0.f,
		vec3(0.f, 0.f, -1.f), 0.f,
		vec3(0.f, 0.f, 0.f), 1.f);

	mat4 rotation =
		mat4::rotateZ(a_rotationDegrees.m_Z * MathUtilities::DEG2RAD) *
		mat4::rotateY(a_rotationDegrees.m_Y * MathUtilities::DEG2RAD) *
		mat4::rotateX(a_rotationDegrees.m_X * MathUtilities::DEG2RAD);

	this->orientation = temporaryOrientation * rotation;
	return this->orientation;

}