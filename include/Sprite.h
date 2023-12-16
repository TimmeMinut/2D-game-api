#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>

#include "GameEngine.h"

namespace twoD
{
	class Sprite
	{
	public:
		virtual ~Sprite();
		virtual void mouseDown(const SDL_Event &) {}
		virtual void mouseUp(const SDL_Event &) {}
		virtual void keyDown(const SDL_Event &) {}
		virtual void keyUp(const SDL_Event &) {}
		virtual void draw() const;
		virtual void tick() = 0;

		SDL_Rect *getRect() const { return rect; }
		SDL_Texture *getTexture() const { return tx; };

	protected:
		Sprite(int x, int y, int w, int h, std::string path);

	private:
		SDL_Rect* rect;
		SDL_Texture *tx;

		Sprite(const Sprite &) = delete;
		const Sprite &operator=(const Sprite &) = delete;
	};
}

#endif