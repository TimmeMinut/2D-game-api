#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "System.h"

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
		void setTexture(std::string path);

		std::vector<std::string> getSpriteSheet() const { return spriteSheet; }
		void setSpriteSheet(std::initializer_list<std::string> ss) { spriteSheet = ss; }

	protected:
		Sprite(int x, int y, int w, int h, std::initializer_list<std::string> ss);

	private:
		SDL_Rect *rect;
		std::vector<std::string> spriteSheet;
		SDL_Texture *tx;

		Sprite(const Sprite &) = delete;
		const Sprite &operator=(const Sprite &) = delete;
	};
}

#endif