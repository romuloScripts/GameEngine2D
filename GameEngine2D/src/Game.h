#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../lib/Lua535/include/sol.hpp"
#include "EntityManager.h"
#include "Entity.h"
#include "Component.h"

class AssetManager;

class Game
{

private:
	bool isRunning;
	SDL_Window *window;

public:
	Game();
	~Game();
	int ticksLastFrame = 0;
	bool IsRunning() const;
	static SDL_Renderer *renderer;
	static AssetManager* assetManager;
	static SDL_Event event;
	static SDL_Rect camera;
	void LoadLevel(int levelNumber);
	void Initialize(int width, int height);
	void ProcessInput();
	void ProcessNextLevel(int levelNumber);
	void ProcessGameOver();
	void Update();
	void Render();
	void Destroy();
	void HandleCameraMovement();
	void CheckCollisions();
};

