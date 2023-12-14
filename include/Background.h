#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>

#include <string>
#include <iostream>

#include "Sprite.h"
#include "MovingSprite.h"
#include "GameEngine.h"

namespace twoD
{
    class Background : public MovingSprite
    {
    public:
        Background(int x, int y, int w, int h, std::string path, int direction, int speed);

        void draw() const override;
        void tick() override;

    private:
        SDL_Rect rect2;
    };
}

#endif