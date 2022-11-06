#pragma once
#include <vector>
#include "Color.h"

class vec2;
class Scene;
class Camera;
class Ray;
class BVHNode;
struct HitResult;

class Raytracer {

public:

	Raytracer(bool a_useBVH = true);

	std::vector<Color> RenderScene(const Scene& a_scene, const Camera& a_camera, const vec2 a_screensize);

private:

	Color Trace(const Scene& a_scene, const Ray& a_ray, unsigned int a_recursiondepth, float a_offset, const Color& backgroundColor = Color()) const;

	//Tests whether a ray intersects with the scene and returns the closest intersection when it has intersected with the scene.
	bool RayIntersectsWithScene(const Scene& a_scene, const Ray& a_ray, HitResult& a_hitresult) const;

	//Tests whether a hit point can be reached from a light.
	bool CanHitLight(const Scene& a_scene, const Ray& a_ray, float a_maxDistance) const;

	//Gets the color of the blinn-phong shading for a certain point.
	Color BlinnPhong(const Scene& a_scene, const HitResult& a_hitresult, float a_offset) const;

	//Returns a vector that represents the outgoing reflection direction.
	bool Reflect(const HitResult& a_hitresult, vec3& a_direction) const;

	//Returns a vector that represents the refraction direction of a ray hitting a surface.
	bool Refract(const HitResult& a_hitresult, vec3& a_direction) const;

	//Returns the ratio of reflected light.
	float Fresnel(const HitResult& a_hitresult) const;

	const Color backgroundColor = Color(10.f / 255.f, 10.f / 255.f, 10.f / 255.f);
	const unsigned int maxRecursionDepth = 10;

	const bool useBVH;

	BVHNode* bvhRoot;

};