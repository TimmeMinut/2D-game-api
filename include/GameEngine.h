#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

#include "Sprite.h"
#include "GameEngine.h"

namespace twoD
{
	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		SDL_Texture *createTexture(std::string path);

		int getW() const { return w; }
		int getH() const { return h; }

		SDL_Window *getWindow() const { return win; }
		SDL_Renderer *getRen() const { return ren; }
		TTF_Font *getFont() const { return font; }
		Mix_Chunk *getMusic() const { return music; }

		void setWindow(std::string title, int w, int h, Uint32 flags);

		void setMusic(std::string path);

	private:
		int w = 640;
		int h = 480;
		
		SDL_Window *win;
		SDL_Renderer *ren;
		TTF_Font *font;
		Mix_Chunk *music;
	};

	extern GameEngine ge;
}
#endif