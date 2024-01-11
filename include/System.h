#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <unordered_map>


#include "Sprite.h"
#include "System.h"

namespace twoD
{
	class System
	{
	public:
		System();
		~System();

		SDL_Texture *createTexture(std::string path);
		Mix_Chunk *createSound(const std::string &path);

		void setWindow(const std::string &title, int w, int h, Uint32 flags);
		void setMusic(const std::string &path);

		int getW() const { return w; }
		int getH() const { return h; }

		SDL_Window *getWindow() const { return win; }
		SDL_Renderer *getRen() const { return ren; }
		TTF_Font *getFont() const { return font; }
		Mix_Chunk *getMusic() const { return music; }

		void addSound(const std::string &name, const std::string &path);
		void removeSound(const std::string &name);
		void playSound(const std::string &name);

	private:
		int w = 640;
		int h = 480;

		SDL_Window *win;
		SDL_Renderer *ren;
		TTF_Font *font;

		Mix_Chunk *music;
		std::unordered_map<std::string, Mix_Chunk *> sounds;
	};

	extern System sys;

	enum direction { UP, RIGHT, DOWN, LEFT };

}
#endif