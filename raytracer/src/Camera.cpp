#include "headers/Camera.h"
#include <cmath>

Camera::Camera(vec3 a_viewPoint, vec3 a_rotationDegrees, float a_aspectRatio, float a_FOVY) :
	translation(mat4::translate(a_viewPoint)),
	focalLength(1.f)
{

	this->imageframeSize = CalculateImageframeSize(a_aspectRatio, a_FOVY);
	this->SetOrientation(a_rotationDegrees);

}

const mat4& Camera::GetTranslation() const {

	return this->translation;

}

void Camera::SetTranslation(const vec3& a_viewpoint) {

	this->translation.translation3 = a_viewpoint;

}

const mat4& Camera::GetOrientation() const{

	return this->orientation;

}

void Camera::SetOrientation(const vec3& a_rotationDegrees) {

	mat4 temporaryOrientation = mat4(
		vec3(1.f, 0.f, 0.f), 0.f,
		vec3(0.f, 1.f, 0.f), 0.f,
		vec3(0.f, 0.f, 1.f), 0.f,
		vec3(0.f, 0.f, 0.f), 1.f);

	mat4 rotation =
		mat4::rotateZ(a_rotationDegrees.m_Z * MathUtilities::DEG2RAD) *
		mat4::rotateY(a_rotationDegrees.m_Y * MathUtilities::DEG2RAD) *
		mat4::rotateX(a_rotationDegrees.m_X * MathUtilities::DEG2RAD);

	this->orientation = temporaryOrientation * rotation;

}

const vec2& Camera::GetImageframeSize() const {

	return this->imageframeSize;

}

const float& Camera::GetFocalLength() const {

	return this->focalLength;

}

vec2 Camera::CalculateImageframeSize(float a_aspectRatio, float a_FoVY) {

	float frameWidth = 2.f * (std::tanf((a_FoVY * 0.5f) * MathUtilities::DEG2RAD) * this->focalLength);
	float frameHeight = frameWidth / a_aspectRatio;

	return vec2(frameWidth, frameHeight);

}