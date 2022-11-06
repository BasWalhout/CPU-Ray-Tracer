#pragma once
#include <vector>
#include "Surface.h"
#include "SphericalLight.h"
#include "DirectionalLight.h"
#include "../../../MathLibrary/MathLibrary.h"

class Scene {

public:

	const std::vector<Surface*>& GetFiniteSurfaces() const;
	const std::vector<Surface*>& GetInfiniteSurfaces() const;
	const std::vector<Light*>& GetLights() const;

	void AddSurface(Surface& a_surface);
	void AddLight(Light& a_light);

private:

	std::vector<Surface*> finiteSurfaces;
	std::vector<Surface*> infiniteSurfaces;
	std::vector<Light*> ligths;

};