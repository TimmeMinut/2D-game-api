#include <SDL2/SDL.h>
#include <iostream>

#include "GameEngine.h"
#include "Sprite.h"
#include "MovingSprite.h"
#include "Constants.h"

namespace twoD
{
    MovingSprite::MovingSprite(int x, int y, int w, int h, std::string path, int direction, int speed) : Sprite(x, y, w, h, path)
    {
        if (speed < 0)
        {
            throw std::invalid_argument("MovingSprite:: Speed needs to be a positive integer!");
        }
        if (direction < 1 || direction > 4)
        {
            throw std::invalid_argument("MovingSprite:: Direction needs to be an integer between 1-4!");
        }

        this->direction = direction;
        this->speed = speed;
    }

    void MovingSprite::setDirection(int d)
    {
        direction = d;
    }

    void MovingSprite::setSpeed(int s)
    {
        speed = s;
    }

    void MovingSprite::tick()
    {
        switch (direction)
        {
        case 1: // up
            getRect()->y -= speed;
            break;
        case 2: // right
            getRect()->x += speed;
            break;
        case 3: // down
            getRect()->y += speed;
            break;
        case 4: // left
            getRect()->x -= speed;
        default:
            break;
        }
    }
}