#include "Game.h"
#include <stdio.h>

SDL_Rect cell;

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
		
		cell.h = 8;
		cell.w = 8;

		isRunning = true;
	}
}

void Game::Update()
{

	cell.x += cell.w;
	if (cell.x >= windowW)
	{
		cell.y += cell.h;
		cell.x = 0;
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &cell);
	SDL_RenderDrawRect(renderer, &cell);
	
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