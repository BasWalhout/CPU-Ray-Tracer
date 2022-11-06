#pragma once
#include "Color.h"

struct Material
{

	Material(Color a_albedo, float a_phongCoefficient, float a_specularComponent, float a_reflectiveness = 0.f,  float a_refractionIndex = 0.f, bool a_conductor = false);

	float phongComponent;
	float specularCoefficient;

	float refractionIndex;
	bool conductor;
	
	float reflectiveness;

	Color albedo;

};