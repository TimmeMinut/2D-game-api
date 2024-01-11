#ifndef MOVINGSPRITE_H
#define MOVINGSPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include "Sprite.h"

namespace twoD
{
    class MovingSprite : public Sprite
    {
    public:
        static MovingSprite *getInstance(int x, int y, int w, int h, int direction, int speed, std::initializer_list<std::string> ss)
        {
            return new MovingSprite(x, y, w, h, direction, speed, ss);
        }
        
        void tick() override;

        void setDirection(int d);
        void setSpeed(int s);

        int &getDirection() { return direction; }
        int &getSpeed() { return speed; }

    protected:
        MovingSprite(int x, int y, int w, int h, int direction, int speed, std::initializer_list<std::string> ss);

    private:
        int direction, speed;
    };
}

#endif