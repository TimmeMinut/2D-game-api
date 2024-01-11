#ifndef BACKGROUNDSPRITE_H
#define BACKGROUNDSPRITE_H

#include <SDL2/SDL.h>

#include <string>
#include <iostream>

#include "MovingSprite.h"

namespace twoD
{
    class BackgroundSprite : public MovingSprite
    {
    public:
        static BackgroundSprite *getInstance(int x, int y, int w, int h, int direction, int speed, std::initializer_list<std::string> ss)
        {
            return new BackgroundSprite(x, y, w, h, direction, speed, ss);
        }
        void draw() const override;
        void tick() override;

    protected:
        BackgroundSprite(int x, int y, int w, int h, int direction, int speed, std::initializer_list<std::string> ss);

    private:
        SDL_Rect rect2;
    };
}

#endif