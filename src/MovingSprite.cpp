#include <SDL2/SDL.h>
#include <iostream>

#include "Sprite.h"
#include "MovingSprite.h"

namespace twoD
{
    MovingSprite::MovingSprite(int x, int y, int w, int h, int direction, int speed, std::initializer_list<std::string> ss) : Sprite(x, y, w, h, ss)
    {
        if (speed < 0)
        {
            throw std::invalid_argument("MovingSprite::speed Needs to be a positive integer!");
        }
        if (direction < 0 || direction > 3)
        {
            throw std::invalid_argument("MovingSprite::direction Please use enum UP, DOWN, LEFT, RIGHT");
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
        case UP: 
            getRect()->y -= speed;
            break;
        case RIGHT: 
            getRect()->x += speed;
            break;
        case DOWN: 
            getRect()->y += speed;
            break;
        case LEFT: 
            getRect()->x -= speed;
        default:
            break;
        }
    }
}