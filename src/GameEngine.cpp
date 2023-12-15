#include "GameEngine.h"
#include "Constants.h"
#include "Sprite.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

namespace twoD
{
	GameEngine::GameEngine()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("GameDemo", SDL_WINDOWPOS_CENTERED,
							   SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
		TTF_Init();

		font = TTF_OpenFont((constants::gResPath + "fonts/Pixeboy.ttf").c_str(), 24);

		Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
	}

	GameEngine::~GameEngine()
	{
		Mix_FreeChunk(music);
		Mix_CloseAudio();
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
	}

	SDL_Texture *GameEngine::createTexture(std::string path)
	{
		SDL_Surface *sur = IMG_Load((constants::gResPath + path).c_str());
		SDL_Texture *tx = SDL_CreateTextureFromSurface(ren, sur);
		SDL_FreeSurface(sur);
		return tx;
	}

	void GameEngine::setWindow(std::string title, int w, int h, Uint32 flags)
	{
		this->w = w;
		this->h = h;
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
		ren = SDL_CreateRenderer(win, -1, 0);
	}

	void GameEngine::setMusic(std::string path)
	{
		Mix_FreeChunk(music);

		music = Mix_LoadWAV((constants::gResPath + path).c_str());

		if (music == NULL)
		{
			std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
			return;
		}
		Mix_PlayChannel(-1, music, -1);
	}

	GameEngine ge; // Statiskt globalt objekt (definierad utanför funktioner.)
}