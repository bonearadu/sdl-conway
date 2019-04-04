#include "Game.h"

int main(const int argc, char* argv[])
{
	Game* game = new Game();

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameLast;
	int frameTime;

	game->Init("Conway's Game of Life", 800, 600, false);

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