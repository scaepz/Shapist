#include <sdl.h>

#include <iostream>
#include "LevelReader.h"
#include "Game.h"
#include "Campaign.h"
using namespace std;
#undef main

int main()
{
	//init SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "audio failed";
	}
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		std::cout << "sdl_init_everything failed";
	}
	if (TTF_Init() == -1)
	{
		std::cout << "TTF failed to init";
	}

	int resolution[2] = { 1280, 720};
	SDL_Window * window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolution[0], resolution[1], NULL);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, NULL);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	

	//game
	CCampaign campaign("res/campaigns/shapist/levelList.txt", renderer, window, resolution[0], resolution[1]);
	campaign.LoadLevel(0);

	//de-init SDL
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	system("Pause");

	return 0;
}