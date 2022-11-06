#pragma once
#include "../../../MathLibrary/MathLibrary.h"

class Camera {

public:

	Camera(vec3 a_viewPoint, vec3 a_rotationDegrees, float a_aspectRatio, float a_FOV_Y);

	const mat4& GetTranslation() const;
	void SetTranslation(const vec3& a_viewpoint);

	const mat4& GetOrientation() const;
	void SetOrientation(const vec3& a_rotationDegrees);

	const vec2& GetImageframeSize() const;
	const float& GetFocalLength() const;

private:
 
	vec2 CalculateImageframeSize(float a_aspectRatiom, float a_FoVY);

	mat4 translation;
	mat4 orientation;

	vec2 imageframeSize;
	const float focalLength;


};