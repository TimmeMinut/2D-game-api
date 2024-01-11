#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <SDL2/SDL.h>

namespace twoD
{
    class CollisionHandler
    {
    public:
        static bool collided(SDL_Rect *r1, SDL_Rect *r2);

    private:
    };
}

#endif