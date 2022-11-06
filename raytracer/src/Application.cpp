#include "headers/Application.h"
#include "headers/Raytracer.h"
#include "headers/Camera.h"
#include "headers/Scene.h"
#include "headers/Sphere.h"
#include "headers/Plane.h"
#include "headers/FinitePlane.h"
#include "headers/SphericalLight.h"
#include "headers/Cuboid.h"
#include <SDL.h>
#include <iostream>
#include <stdio.h>

Application::Application() :
	maxFPS(60),
	frameDelay(1000 / maxFPS),\
	lastFrameTime(0),
	windowBordered(true),
	windowFullscreen(false),
	windowRatio(16.f/9.f),
	windowHeight(720),
	windowWidth((int)(windowRatio * windowHeight))
{}

Application::~Application() {

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();

}

bool Application::InitializeWindow() {

	//Set the windowflags to be the right value.
	int windowFlags = 0;

	if (windowFullscreen) {
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	}

	if (!windowBordered) {


		windowFlags |= SDL_WINDOW_BORDERLESS;

	}

	printf("Initializing SDL Library...\n");


	//Initialize SDL's video system and check if there are no errors.
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {

		printf("Succesfully instantiated SDL library \n\n");
		printf("Initializing window...\n");


		window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, windowFlags);

		if (!window) {
			printf("Error while initializing the window... \n Error: %s", SDL_GetError());
			return false;
		}

		SDL_GetWindowSize(this->window, &this->clientWidth, &this->clientHeight);

		printf("Succesfully initialized the window (width: %i, height: %i)\n\n", this->windowWidth, this->windowHeight);
		printf("Creating renderer...\n");
		
		renderer = SDL_CreateRenderer(this->window, -1, 0);

		if (!renderer) {
			printf("Error while creating the renderer... \n Error: %s", SDL_GetError());
			return false;
		}
		else {

			SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
			printf("Succesfully created renderer \n\n");

		}

		mat4 test = mat4::translate(vec3(10, 5, 1));
		vec3 point = vec3();

		float maxUint8 = SDL_MAX_UINT8;

		this->raytracer = new Raytracer(false);
		this->camera = new Camera(vec3(0.f, 3.f, -5.f), vec3(-2.f, 180.f, 0.f), this->windowRatio, 90.f);
		this->scene = new Scene();

		//Plane& plane0 = *new Plane(vec3(0.f, -4.f, 0.f), vec3(-2.f, 0.f, 0.f), Material(Color(ColorType::WHITE), 10.f, 0.4f));
		//this->scene->AddSurface(plane0);

		FinitePlane& finitePlane0 = *new FinitePlane(vec3(0.f, -4.f, 20.f), vec3(), vec2(20, 20), Material(Color(ColorType::WHITE), 100.f, 0.8f, 0.8f));
		this->scene->AddSurface(finitePlane0);

		Cuboid& cuboid0 = *new Cuboid(vec3(0.f, -2.f, 10.f), vec3(-45.f, 0.f, 0.f), vec3(1.f, 1.f, 1.f), Material(Color(ColorType::SILVER), 10000.f, 1.f));
		this->scene->AddSurface(cuboid0);

		Sphere& sphere0 = *new Sphere(vec3(0.f, 8.f, 10.f), 1.f, Material(Color(ColorType::WHITE), 10.f, 0.4f));
		this->scene->AddSurface(sphere0);

		Sphere& sphere1 = *new Sphere(vec3(-10.f, 0.f, 20.f), 4.f, Material(Color(ColorType::RED), 1000.f, 1.f, 0.0f));
		this->scene->AddSurface(sphere1);

		Sphere& sphere2 = *new Sphere(vec3(0.f, 0.f, 20.f), 4.f, Material(Color(ColorType::WHITE), 1000.f, 1.f, 0.8f, 1.8f));
		this->scene->AddSurface(sphere2);

		Sphere& sphere3 = *new Sphere(vec3(10.f, 0.f, 20.f), 4.f, Material(Color(ColorType::BLUE), 1000.f, 1.f, 0.0f));
		this->scene->AddSurface(sphere3); 

		Sphere& sphere4 = *new Sphere(vec3(0.f, 0.f, 30.f), 4.f, Material(Color(ColorType::GOLD), 1000.f, 1.f, 0.0f));
		this->scene->AddSurface(sphere4);

		//Sphere& sphere4 = *new Sphere(vec3(0.f, 0.f, 34.f), 4.f, Material(Color(ColorType::WHITE), 1000.f, 1.f));
		//this->scene->AddSurface(sphere4);

		//Sphere& sphere5 = *new Sphere(vec3(-10.f, 0.f, 10.f), 2.f, Material(Color(ColorType::RED), 1000.f, 1.f));
		//this->scene->AddSurface(sphere5);

		SphericalLight& light0 = *new SphericalLight(vec3(-8.f, 3.6f, 0.f), Color(ColorType::WHITE), 0.4f);
		this->scene->AddLight(light0);
		
		//SphericalLight& light1 = *new SphericalLight(vec3(0.f, 12.f, 14.f), Color(255.f / maxUint8, 255.f / maxUint8, 255.f / maxUint8));
		//this->scene->AddLight(light1);

		SphericalLight& light2 = *new SphericalLight(vec3(8.f, 3.6f, 0.f), Color(ColorType::WHITE), 0.4f);
		this->scene->AddLight(light2);

		//SphericalLight& light3 = *new SphericalLight(vec3(0.f, 0.f, 40.f), Color(255.f / maxUint8, 255.f / maxUint8, 255.f / maxUint8));
		//this->scene->AddLight(light3);

		//SphericalLight& light1 = *new SphericalLight(vec3(0.f, 20.f, 20.f), Color(0, 255, 0));
		//this->scene->AddLight(light1);

		//SphericalLight& light2 = *new SphericalLight(vec3(28.f, 0.f, 15.f), Color(0, 0, 255));
		//this->scene->AddLight(light2);

		SDL_Surface* surface = SDL_CreateRGBSurface(0, this->clientWidth, this->clientHeight, 32, 0, 0, 0, 0);

		int bytesPerPixel = surface->format->BytesPerPixel;

		SDL_PixelFormat* format = surface->format;

		Uint8* pixels = (Uint8*)surface->pixels;

		int timeBeforeRendering = SDL_GetTicks();

		std::vector<Color> result = this->raytracer->RenderScene(*this->scene, *this->camera, vec2(static_cast<float>(this->clientWidth), static_cast<float>(this->clientHeight)));

		std::cout << "Rendering took: " << SDL_GetTicks() - timeBeforeRendering << " ms \n";

		for (int y = 0; y < clientHeight; ++y) {
			for (int x = 0; x < clientWidth; ++x) {

				Uint8* targetPixel = pixels + (y * surface->pitch) + x * bytesPerPixel;

				Color color = result[y * clientWidth + x];

				*(Uint32*)targetPixel = SDL_MapRGBA(format, 
													(Uint8)(color.GetComponentR() * maxUint8), 
													(Uint8)(color.GetComponentG() * maxUint8), 
													(Uint8)(color.GetComponentB() * maxUint8), 
													SDL_ALPHA_OPAQUE);

			}
		}

		image = SDL_CreateTextureFromSurface(this->renderer, surface);

		SDL_FreeSurface(surface);

		return true;
	}
	else {
		printf("Error while initializing everything... \n Error: %s", SDL_GetError());
		return false;
	}

}

void Application::Loop() {

	this->running = true;

	while (this->running) {

		this->deltaTime = SDL_GetTicks() - this->lastFrameTime;

		//Limit the updates and draw calls to be a certain amount per second.
		if (deltaTime >= frameDelay) {

			this->lastFrameTime = SDL_GetTicks();

			this->Update();
			this->Draw();

		}

	}

}

void Application::Update() {
	
	this->currentFPS = 1000 / this->deltaTime;
	char titleBuffer[64];
	sprintf_s(titleBuffer, 64, "Raytracer - (FPS: %i)", currentFPS);
	SDL_SetWindowTitle(this->window, titleBuffer);

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {

		switch (event.type) {

		case SDL_QUIT:
			this->running = false;
			break;

		case SDL_KEYDOWN:
			
			switch (event.key.keysym.sym)
			{

			case SDLK_ESCAPE:
				this->running = false;
				break;

			default:
				break;
			}

		}

	}

	/*this->elapsedTime += this->deltaTime;
	
	if (elapsedTime <= 400) {
		this->elapsedTime -= 00;
		
		vec3 viewpoint = this->camera->getViewpoint();
		if (viewpoint.m_X >= 30.f) {
			right = false;
		}
		if (viewpoint.m_X <= 0.f) {
			right = true;
		}

		if (right) {
			viewpoint.m_X += 1.f;
		}
		else {
			viewpoint.m_X -= 1.f;
		}

		this->camera->setViewPoint(viewpoint);

	}

	float maxUint8 = SDL_MAX_UINT8;

	SDL_Surface* surface = SDL_CreateRGBSurface(0, this->clientWidth, this->clientHeight, 32, 0, 0, 0, 0);

	int bytesPerPixel = surface->format->BytesPerPixel;

	SDL_PixelFormat* format = surface->format;

	Uint8* pixels = (Uint8*)surface->pixels;

	int timeBeforeRendering = SDL_GetTicks();

	std::vector<vec3> result = this->raytracer->RenderScene(*this->scene, *this->camera, vec2(static_cast<float>(this->clientWidth), static_cast<float>(this->clientHeight)));

	std::cout << "Rendering took: " << SDL_GetTicks() - timeBeforeRendering << " ms \n";

	for (int y = 0; y < clientHeight; ++y) {
		for (int x = 0; x < clientWidth; ++x) {

			Uint8* targetPixel = pixels + (y * surface->pitch) + x * bytesPerPixel;

			vec3 color = result[y * clientWidth + x];

			*(Uint32*)targetPixel = SDL_MapRGBA(format, (Uint8)(color.m_X * maxUint8), (Uint8)(color.m_Y * maxUint8), (Uint8)(color.m_Z * maxUint8), SDL_ALPHA_OPAQUE);

		}
	}

	SDL_DestroyTexture(image);
	image = SDL_CreateTextureFromSurface(this->renderer, surface);

	SDL_FreeSurface(surface);*/

	return;
}

void Application::Draw() {

	SDL_RenderClear(this->renderer);

	//Draw the current image the raytracer has calculated yet.
	SDL_RenderCopy(this->renderer, this->image, NULL, NULL);

	SDL_RenderPresent(this->renderer);
	return;

}

int Application::lerp(int a, int b, float t) {
	return (int)((b - a) * t + a);
}

