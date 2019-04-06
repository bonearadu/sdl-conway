#include "Game.h"
#include <stdio.h>

int main(const int argc, char* argv[])
{
	Game* game = new Game();

	const int FPS = 20;
	const int frameDelay = 1000 / FPS;

	const int windowW = 1024;
	const int windowH = 768;

	const bool fullscreen = false;

	Uint32 frameLast;
	int frameTime;

	game->Init("Conway's Game of Life", windowW, windowH, fullscreen);

	while (game->Running())
	{
		frameLast = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameLast;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->Clean();

	return 0;
}