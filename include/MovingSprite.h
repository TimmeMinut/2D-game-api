#ifndef MOVINGSPRITE_H
#define MOVINGSPRITE_H

#include <string>
#include <SDL2/SDL.h>
#include "Sprite.h"

namespace twoD
{
    class MovingSprite : public Sprite
    {
    public:
        MovingSprite(int x, int y, int w, int h, std::string path, int direction, int speed);

        void tick() override;

        void setDirection(int d);
        void setSpeed(int s);

        int &getDirection() { return direction; }
        int &getSpeed() { return speed; }

    private:
        int direction, speed;
    };
}

#endif