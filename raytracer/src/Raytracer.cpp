#include "headers/Raytracer.h"
#include "headers/Ray.h"
#include "headers/Camera.h"
#include "headers/Scene.h"
#include "headers/Surface.h"
#include "headers/BVHNodes.h"
#include <MathLibrary.h>

Raytracer::Raytracer(bool a_useBVH):
	useBVH(a_useBVH)
{}

std::vector<Color> Raytracer::RenderScene(const Scene& a_scene, const Camera& a_camera, const vec2 a_screensize){

	if (this->useBVH) { //A BVH structure is to be used, first create the structure of the scene.

		this->bvhRoot = new InternalNode(a_scene.GetFiniteSurfaces());

	}

	const int screenwidth = static_cast<int>(a_screensize.m_X);
	const int screenHeigth = static_cast<int>(a_screensize.m_Y);

	std::vector<Color> result = std::vector<Color>();
	result.reserve(screenwidth * screenHeigth);



	const vec2 imageframeSize = a_camera.GetImageframeSize();
	const vec2 pixelDistance = vec2(imageframeSize.m_X / screenwidth, imageframeSize.m_Y / screenHeigth);

	const vec3 cameraOrigin = a_camera.GetTranslation().translation3;

	const vec3 imageplaneTopLeft = vec3(	cameraOrigin.m_X - (imageframeSize.m_X * 0.5f) + (pixelDistance.m_X * 0.5f),
									cameraOrigin.m_Y + (imageframeSize.m_Y * 0.5f) - (pixelDistance.m_Y * 0.5f),
									cameraOrigin.m_Z - a_camera.GetFocalLength());

	vec3 ray_IntersectionpointImageplane = vec3(0, 0, imageplaneTopLeft.m_Z);

	for (int y = 0; y < screenHeigth; ++y) {
		for (int x = 0; x < screenwidth; ++x) {

			//Determine the point at which it is going to intersect with the imageplane.
			ray_IntersectionpointImageplane.m_X = imageplaneTopLeft.m_X + (x * pixelDistance.m_X);
			ray_IntersectionpointImageplane.m_Y = imageplaneTopLeft.m_Y - (y * pixelDistance.m_Y);

			//Construct the ray using the viewpoint of the camera and the direction. 
			//The direction is constructed using the viewpoint of the camera and the intersection point on the imageplane.
			vec3 ray_Direction = vec3(ray_IntersectionpointImageplane - cameraOrigin).normalize();
			//Then the direction is brought to world space.
			ray_Direction = a_camera.GetOrientation() * ray_Direction;

			Ray viewray = Ray(cameraOrigin, ray_Direction);

			//Calculate the color for the pixel.
			Color pixelColor = Trace(a_scene, viewray, 0, MathUtilities::EPSILON, backgroundColor);

			//Return the result of the pixelcolor.
			result.push_back(pixelColor);

		}
	}

	return result;

}

Color Raytracer::Trace(const Scene& a_scene, const Ray& a_ray, unsigned int a_recursiondepth, float a_offset, const Color& a_backgroundcolor) const{

	Color result = Color();
	HitResult hitresult = HitResult();

	if (a_recursiondepth < this->maxRecursionDepth) {
		
		if (RayIntersectsWithScene(a_scene, a_ray, hitresult)) {

			Material surfaceMaterial = hitresult.surface->GetMaterial();

			vec3 hitpoint = hitresult.GetPosition();
			vec3 normalAtHitpoint = hitresult.surface->GetNormalAt(hitpoint);

			float reflectionRatio = Fresnel(hitresult);

			if (surfaceMaterial.refractionIndex > 0.f && reflectionRatio < 1.f) {

				float refractionRatio = 1.f - reflectionRatio;

				vec3 refractionDirection = vec3();
				if (Refract(hitresult, refractionDirection)) {

					float NdotI = normalAtHitpoint.dot(hitresult.ray.getDirection());
					vec3 offset = normalAtHitpoint * a_offset;

					vec3 refractionOrigin = (NdotI < 0.f) ? hitpoint - offset : hitpoint + offset;

					Ray refractionRay = Ray(refractionOrigin, refractionDirection.normalize());
					result += refractionRatio * Trace(a_scene, refractionRay, ++a_recursiondepth, a_offset, a_backgroundcolor);

				}

			}
			
			if(surfaceMaterial.reflectiveness > 0.f){

				vec3 reflectionDirection = vec3();
				if (Reflect(hitresult, reflectionDirection)) {

					vec3 reflectionOrigin = hitpoint + normalAtHitpoint * a_offset;

					Ray reflectionRay = Ray(reflectionOrigin, reflectionDirection.normalize());
					result += reflectionRatio * surfaceMaterial.albedo * Trace(a_scene, reflectionRay, ++a_recursiondepth, a_offset, a_backgroundcolor);
				}

			}

			result += BlinnPhong(a_scene, hitresult, a_offset);
			
			return result;

		}

	}

	return a_backgroundcolor;

}

bool Raytracer::RayIntersectsWithScene(const Scene& a_scene, const Ray& a_ray, HitResult& a_hitresult) const{

	float lastHitDistance = FLT_MAX;

	for (Surface* surface : a_scene.GetInfiniteSurfaces()) { //test the rays agains infinite surfaces.

		HitResult hitresult = surface->IntersectsWithRay(a_ray);

		if (hitresult.hit && hitresult.distance < lastHitDistance) {

			lastHitDistance = hitresult.distance;
			a_hitresult = hitresult;

		}

	}
	
	if (this->useBVH) {

		HitResult hitresult = HitResult();
		float hitDistance = 0.f;
		bool hitsSurface = this->bvhRoot->IntersectsWithRay(a_ray, hitDistance, hitresult);

		if (hitsSurface && hitresult.distance < lastHitDistance) {
			a_hitresult = hitresult;
		}

	}
	else {

		for (Surface* surface : a_scene.GetFiniteSurfaces()) {

			HitResult hitresult = surface->IntersectsWithRay(a_ray);

			if (hitresult.hit && hitresult.distance < lastHitDistance) {

				lastHitDistance = hitresult.distance;
				a_hitresult = hitresult;

			}

		}

	}

	return a_hitresult.hit;

}

bool Raytracer::CanHitLight(const Scene& a_scene, const Ray& a_ray, float a_maxDistance) const {

	for (Surface* surface : a_scene.GetInfiniteSurfaces()) { //test the rays agains infinite surfaces.

		HitResult hitresult = surface->IntersectsWithRay(a_ray);

		if (hitresult.hit && hitresult.distance < a_maxDistance) {

			return false;
		}

	}

	if (this->useBVH) {

		HitResult hitresult = HitResult();
		float hitDistance = 0.f;
		bool hitsSurface = this->bvhRoot->IntersectsWithRay(a_ray, hitDistance, hitresult);

		if (hitsSurface && hitresult.distance < a_maxDistance) {
			
			return false;

		}

	}
	else {

		for (Surface* surface : a_scene.GetFiniteSurfaces()) {

			HitResult hitresult = surface->IntersectsWithRay(a_ray);

			if (hitresult.hit && hitresult.distance < a_maxDistance) {

				return false;

			}

		}

	}
	
	return true;

}

Color Raytracer::BlinnPhong(const Scene& a_scene, const HitResult& a_hitresult, float a_offset) const{

	Material surfaceMaterial = a_hitresult.surface->GetMaterial();

	Color shadingColor = Color();
	Color surfaceColor = surfaceMaterial.albedo;

	vec3 hitpoint = a_hitresult.GetPosition();
	vec3 normalAtHitpoint = a_hitresult.surface->GetNormalAt(hitpoint);

	Ray shadowRay;
	vec3 shadowrayOrigin = hitpoint + normalAtHitpoint * a_offset;;
	vec3 shadowrayDirection;

	for (Light* light : a_scene.GetLights()) {

		shadowrayDirection = light->GetDirectionTo(shadowrayOrigin);

		shadowRay = Ray(shadowrayOrigin, shadowrayDirection);
		float maxDistance = light->GetMaximalDistanceTo(shadowrayOrigin);

		if (this->CanHitLight(a_scene, shadowRay, maxDistance)) {

			float NdotL = normalAtHitpoint.dot(shadowRay.getDirection());

			Color lightIntensity = light->GetIntensityAt(hitpoint);
			shadingColor += surfaceColor * (lightIntensity * std::fmaxf(0.f, NdotL));

			vec3 halfVector = (shadowRay.getDirection() + (a_hitresult.ray.getDirection() * -1)).normalize();

			float NdotH = normalAtHitpoint.dot(halfVector);
			float specularCoefficient = surfaceMaterial.specularCoefficient;
			float phongExponent = surfaceMaterial.phongComponent;

			shadingColor+= specularCoefficient * lightIntensity * std::powf(std::fmaxf(0.f, NdotH), phongExponent);

		}

	}

	return shadingColor;

}

bool Raytracer::Reflect(const HitResult& a_hitresult, vec3& a_direction) const{

	if (a_hitresult.hit) {
		vec3 normalAtHitpoint = a_hitresult.surface->GetNormalAt(a_hitresult.GetPosition());
		vec3 incomingDirection = a_hitresult.ray.getDirection();
		vec3 R = incomingDirection - (normalAtHitpoint * normalAtHitpoint.dot(incomingDirection)) * 2.f;
		a_direction = R;
		return true;
	}
	else {
		return false;
	}


}

bool Raytracer::Refract(const HitResult& a_hitresult, vec3& a_direction) const {

	if (a_hitresult.hit) {

		vec3 normalAtHitpoint = a_hitresult.surface->GetNormalAt(a_hitresult.GetPosition());
		vec3 incomingDirection = a_hitresult.ray.getDirection();
		
		float NdotI = normalAtHitpoint.dot(incomingDirection);
		float iorCurrentMedium = 1.f;
		float iorEnteringMedium = a_hitresult.surface->GetMaterial().refractionIndex;

		if (NdotI < 0.f) { // the ray comes from outside the surface. The cosine returns negative, we want to make it positive.
			NdotI = -NdotI;
		}
		else { //the ray comes from the inside. The cosine is already positive, we want to swap the refraction indices and reverse the normal.

			normalAtHitpoint *= -1.f;
			std::swap(iorCurrentMedium, iorEnteringMedium);

		}

		float ior = iorCurrentMedium / iorEnteringMedium;
		float c2 = 1 - (ior * ior) * (1 - (NdotI * NdotI));

		if (c2 < 0.f) {
			//total internal reflection. There is no refraction in this case.
			return false;
		}
		else {

			a_direction = incomingDirection * ior + normalAtHitpoint * (ior * NdotI - sqrtf(c2));
			return true;

		}

	}
	else return false;

}

float Raytracer::Fresnel(const HitResult& a_hitresult) const {

	if (a_hitresult.hit) {

		if (a_hitresult.surface->GetMaterial().refractionIndex == 0.0f) {
			return 1.f;
		}

		vec3 normalAtHitpoint = a_hitresult.surface->GetNormalAt(a_hitresult.GetPosition());
		vec3 incomingDirection = a_hitresult.ray.getDirection();

		float NdotI = normalAtHitpoint.dot(incomingDirection);
		float iorCurrentMedium = 1.f;
		float iorEnteringMedium = a_hitresult.surface->GetMaterial().refractionIndex;

		if (NdotI > 0.f) { // The ray comes from the inside of the object. We want to swap the refractive indices.
			std::swap(iorCurrentMedium, iorEnteringMedium);
		}

		float ior = iorCurrentMedium / iorEnteringMedium;
		float c2 = 1 - (ior * ior) * (1 - (NdotI * NdotI));

		if (c2 < 0.f) { // There is total internal refraction. We want to reflect all light.
			return 1.f;
		}
		else {

			float cosRefractionAngle = sqrtf(c2);
			NdotI = abs(NdotI);

			float Rparallel = ((iorEnteringMedium * NdotI) - (iorCurrentMedium * cosRefractionAngle)) / ((iorEnteringMedium * NdotI) + (iorCurrentMedium * cosRefractionAngle));
			float Rperpendicular = ((iorCurrentMedium * NdotI) - (iorEnteringMedium * cosRefractionAngle)) / ((iorCurrentMedium * NdotI) + (iorEnteringMedium * cosRefractionAngle));

			return 0.5f * (Rparallel * Rparallel + Rperpendicular * Rperpendicular);

		}

	}
	else return -1.f;

}