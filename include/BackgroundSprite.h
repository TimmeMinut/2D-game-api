#ifndef BACKGROUNDSPRITE_H
#define BACKGROUNDSPRITE_H

#include <SDL2/SDL.h>

#include <string>
#include <iostream>

#include "GameEngine.h"
#include "Sprite.h"
#include "MovingSprite.h"

namespace twoD
{
    class BackgroundSprite : public MovingSprite
    {
    public:
        BackgroundSprite(int x, int y, int w, int h, std::string path, int direction, int speed);

        void draw() const override;
        void tick() override;

    private:
        SDL_Rect rect2;
    };
}

#endif