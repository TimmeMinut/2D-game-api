#include <SDL2/SDL.h>

// #include "System.h"
#include "BackgroundSprite.h"

namespace twoD
{
    BackgroundSprite::BackgroundSprite(int x, int y, int w, int h, int direction, int speed, std::initializer_list<std::string> ss) : MovingSprite(x, y, w, h, direction, speed, ss)
    {
        switch (getDirection())
        {
        case UP:
            rect2 = SDL_Rect{0, h, w, h};
            break;
        case RIGHT:
            rect2 = SDL_Rect{-w, 0, w, h};
            break;
        case DOWN:
            rect2 = SDL_Rect{0, -h, w, h};
            break;
        case LEFT:
            rect2 = SDL_Rect{w, 0, w, h};
        default:
            break;
        }
    }

    void BackgroundSprite::draw() const
    {
        SDL_RenderCopy(sys.getRen(), getTexture(), NULL, getRect());
        SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &rect2);
    }

    void BackgroundSprite::tick()
    {
        switch (getDirection())
        {
        case UP:
            getRect()->y -= getSpeed();
            rect2.y -= getSpeed();

            if (getRect()->y <= -sys.getH())
                getRect()->y = sys.getH();

            if (rect2.y <= -sys.getH())
                rect2.y = sys.getH();
            break;
        case RIGHT:
            getRect()->x += getSpeed();
            rect2.x += getSpeed();

            if (getRect()->x >= sys.getW())
                getRect()->x = -sys.getW();

            if (rect2.x >= sys.getW())
                rect2.x = -sys.getW();
            break;
        case DOWN:
            getRect()->y += getSpeed();
            rect2.y += getSpeed();

            if (getRect()->y >= sys.getH())
                getRect()->y = -sys.getH();

            if (rect2.y >= sys.getH())
                rect2.y = -sys.getH();
            break;
        case LEFT:
            getRect()->x -= getSpeed();
            rect2.x -= getSpeed();

            if (getRect()->x <= -sys.getW())
                getRect()->x = sys.getW();

            if (rect2.x <= -sys.getW())
                rect2.x = sys.getW();
        default:
            break;
        }
    }
}