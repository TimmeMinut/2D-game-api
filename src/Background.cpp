#include "GameEngine.h"
#include "Sprite.h"
#include "MovingSprite.h"
#include "Background.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace twoD
{
    Background::Background(int x, int y, int w, int h, std::string path, int direction, int speed) : MovingSprite(x, y, w, h, path, direction, speed)
    {
        if (getSpeed() <= 0)
        {
            throw std::invalid_argument("Speed needs to be a positive integer!");
        }
        if (getDirection() < 1 || getDirection() > 4)
        {
            throw std::invalid_argument("Direction needs to be an integer between 1-4!");
        }

        switch (getDirection())
        {
        case 1: // up
            rect2 = SDL_Rect{0, h, w, h};
            break;
        case 2: // right
            rect2 = SDL_Rect{-w, 0, w, h};
            break;
        case 3: // down
            rect2 = SDL_Rect{0, -h, w, h};
            break;
        case 4: // left
            rect2 = SDL_Rect{w, 0, w, h};
        default:
            break;
        }
    }

    void Background::draw() const
    {
        SDL_RenderCopy(ge.getRen(), getTexture(), NULL, getRect());
        SDL_RenderCopy(ge.getRen(), getTexture(), NULL, &rect2);
    }

    void Background::tick()
    {
        switch (getDirection())
        {
        case 1: // up
            getRect()->y -= getSpeed();
            rect2.y -= getSpeed();

            if (getRect()->y <= -ge.getH())
                getRect()->y = ge.getH();

            if (rect2.y <= -ge.getH())
                rect2.y = ge.getH();
            break;
        case 2: // right
            getRect()->x += getSpeed();
            rect2.x += getSpeed();

            if (getRect()->x >= ge.getW())
                getRect()->x = -ge.getW();

            if (rect2.x >= ge.getW())
                rect2.x = -ge.getW();
            break;
        case 3: // down
            getRect()->y += getSpeed();
            rect2.y += getSpeed();

            if (getRect()->y >= ge.getH())
                getRect()->y = -ge.getH();

            if (rect2.y >= ge.getH())
                rect2.y = -ge.getH();
            break;
        case 4: // left
            getRect()->x -= getSpeed();
            rect2.x -= getSpeed();

            if (getRect()->x <= -ge.getW())
                getRect()->x = ge.getW();

            if (rect2.x <= -ge.getW())
                rect2.x = ge.getW();
        default:
            break;
        }
    }
}