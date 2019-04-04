#pragma once

#include "SDL.h"

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; }

private:
	bool isRunning = false;

	int windowW = 0;
	int windowH = 0;

	int cnt = -1;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};

