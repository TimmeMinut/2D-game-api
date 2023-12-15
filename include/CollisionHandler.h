#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <SDL2/SDL.h>

#include "GameEngine.h"

namespace twoD
{
    class CollisionHandler
    {
    public:
        static bool collided(const SDL_Rect &rect1, const SDL_Rect &rect2);

    private:

    };
}

#endif