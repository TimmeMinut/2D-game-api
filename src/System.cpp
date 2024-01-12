#include "Constants.h"
#include "System.h"
#include "Sprite.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>
#include <iostream>
#include <string>

namespace twoD
{
	System::System()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("GameDemo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
		TTF_Init();
		font = TTF_OpenFont((constants::gResPath + "fonts/Pixeboy.ttf").c_str(), 24);
		Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
	}

	System::~System()
	{
		for (auto c : sounds)
		{
			Mix_FreeChunk(c.second);
		}
		Mix_FreeChunk(music);
		Mix_CloseAudio();
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
	}

	SDL_Texture *System::createTexture(std::string path)
	{
		SDL_Surface *sur = IMG_Load((constants::gResPath + path).c_str());
		SDL_Texture *tx = SDL_CreateTextureFromSurface(ren, sur);
		SDL_FreeSurface(sur);
		return tx;
	}

	Mix_Chunk *System::createSound(const std::string &path)
	{
		Mix_Chunk *sound = Mix_LoadWAV((constants::gResPath + path).c_str()); // TODO: sound is 0x0 when creating lazer...
		// Mix_Chunk *sound = Mix_LoadWAV(("./resources/" + path).c_str()); // Temporär workaround
		if (sound == nullptr)
		{
			std::cout << "Failed to load sound: " << Mix_GetError() << std::endl;
		}
		return sound;
	}

	void System::setWindow(const std::string &title, int w, int h, Uint32 flags)
	{
		this->w = w;
		this->h = h;
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
		ren = SDL_CreateRenderer(win, -1, 0);
	}

	void System::setMusic(const std::string &path)
	{
		Mix_FreeChunk(music);

		music = createSound(path);

		if (music == NULL)
		{
			std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
			return;
		}
		Mix_PlayChannel(-1, music, -1);
	}

	void System::addSound(const std::string &name, const std::string &path)
	{
		sounds[name] = createSound(path);
	}

	void System::removeSound(const std::string &name)
	{
		sounds.erase(name);
	}

	void System::playSound(const std::string &name)
	{
		Mix_PlayChannel(-1, sounds[name], 0);
	}

	System sys; // Static global object
}