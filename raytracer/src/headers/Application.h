#pragma once

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Scene;
class Camera;
class Raytracer;

class Application {

public:

	Application();
	~Application();

	void Loop();
	void Update();
	void Draw();

	bool InitializeWindow();
	

private:

	bool running;

	const int maxFPS;
	const int frameDelay;

	int lastFrameTime;
	int deltaTime;
	int currentFPS;

	const bool windowBordered;
	const bool windowFullscreen;
	const float windowRatio;

	int windowHeight;
	int windowWidth;

	int clientHeight;
	int clientWidth;
	
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* image;

	Scene* scene;
	Camera* camera;

	Raytracer* raytracer;

	int lerp(int a, int b, float t);

};