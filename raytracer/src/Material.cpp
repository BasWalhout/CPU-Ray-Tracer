#include "headers/Material.h"

Material::Material(Color a_albedo, float a_phongComponent, float a_specularCoefficient, float a_reflectiveness, float a_refractionIndex, bool a_conductor) :
	albedo(a_albedo), 
	phongComponent(std::fmaxf(0.f, a_phongComponent)), 
	specularCoefficient(MathUtilities::Clampf(a_specularCoefficient, 0.f, 1.f)), 
	conductor(a_conductor),
	refractionIndex(std::fmaxf(0.f, a_refractionIndex)), 
	reflectiveness(MathUtilities::Clampf(a_reflectiveness, 0.f, 1.f))
{}