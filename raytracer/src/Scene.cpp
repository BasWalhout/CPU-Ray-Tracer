#include "headers/Scene.h"

const std::vector<Surface*>& Scene::GetFiniteSurfaces() const {

	return this->finiteSurfaces;

}

const std::vector<Surface*>& Scene::GetInfiniteSurfaces() const {

	return this->infiniteSurfaces;

}

const std::vector<Light*>& Scene::GetLights() const {

	return this->ligths;

}

void Scene::AddSurface(Surface& a_surface) {

	if (a_surface.HasBoundingBox()) {
		this->finiteSurfaces.push_back(&a_surface);
	}
	else {
		this->infiniteSurfaces.push_back(&a_surface);
	}
	
}

void Scene::AddLight(Light& a_light) {

	this->ligths.push_back(&a_light);

}