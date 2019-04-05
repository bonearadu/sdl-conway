#include "Game.h"
#include "Cells.h"
#include <stdio.h>

Cells* cells;

Game::Game()
{}

Game::~Game()
{}

void Game::Init(const char* title, int width, int height, bool fullscreen)
{
	Uint32 flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		windowW = width;
		windowH = height;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowW, windowH, flags);
		printf_s("Window Created!\n");

		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		printf_s("Renderer Created!\n");

		isRunning = true;
	}

	cells = new Cells(windowW, windowH);

	cells->GenRandomArray(cells->arrayH, cells->arrayW, "rand.txt");
	cells->LoadArray("rand.txt");
}

void Game::Update()
{
	cells->UpdateArray();
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	cells->PrintCurrentGeneration(renderer);

	SDL_RenderPresent(renderer);
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	printf_s("Cleaned and quitted...");
}