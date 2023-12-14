#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <random>

#include "Constants.h" //gResPath-contains path to your resources.
#include "GameEngine.h"
#include "Session.h"
#include "Sprite.h"
#include "MovingSprite.h"
#include "Background.h"

/*
Background::Background()
    Directions:
        1 = up
        2 = right
        3 = down
        4 = left
    Speed:
        Must be positive int
*/
using namespace twoD;

Session ses(60);

class Bullet : public MovingSprite
{
public:
    Bullet(int x, int y, int w, int h, std::string path, int direction, int speed) : MovingSprite(x, y, w, h, path, direction, speed) {}

    void tick()
    {
        if (getRect()->y < -10 || getRect()->y > ge.getH())
            ses.remove(this);

        switch (getDirection())
        {
        case 1:
            getRect()->y -= 4;
            break;
        case 2:
            getRect()->x += 4;
            break;
        case 3:
            getRect()->y += 4;
            break;
        case 4:
            getRect()->x -= 4;
            break;
        }
    }
};

class Player : public Sprite
{
public:
    Player(int x, int y, int w, int h, std::string path) : Sprite(x, y, w, h, path) {}

    void tick() override
    {
    }

    void keyDown(const SDL_Event &eve)
    {
        switch (eve.key.keysym.sym)
        {
        case SDLK_LEFT:
            if (getRect()->x > 0)
            {
                getRect()->x -= 8;
            }
            break;
        case SDLK_RIGHT:
            if (getRect()->x < ge.getW() - getRect()->w)
            {
                getRect()->x += 8;
            }
            break;
        case SDLK_SPACE:
            // play sound and shoot, creating a bullet object
            Mix_PlayChannel(-1, lazer, 0);
            Bullet *b = new Bullet(getRect()->x + 40, ge.getH() - 120, 10, 50, "images/bullet.png", 1, 10);
            ses.add(b);
        }
    }

private:
    Mix_Chunk *lazer = Mix_LoadWAV((constants::gResPath + "sounds/lazer.wav").c_str());
};

class Ghost : public Sprite
{
public:
    Ghost(int x, int y, int w, int h, std::string path) : Sprite(x, y, w, h, path), generator(std::random_device{}()), distribution(0, 500) {}

    void tick()
    {
        int roll = distribution(generator);
        if (roll == 1)
        {
            Mix_PlayChannel(-1, lazer, 0);
            Bullet *b = new Bullet(getRect()->x + 20, 120, 10, 50, "images/bullet-down.png", 3, 10);
            ses.add(b);
        }
    }

private:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

    Mix_Chunk *lazer = Mix_LoadWAV((constants::gResPath + "sounds/lazer.wav").c_str());
};

class MovingGhost : public MovingSprite
{
public:
    MovingGhost(int x, int y, int w, int h, std::string path, int d, int s) : MovingSprite(x, y, w, h, path, d, s), generator(std::random_device{}()), distribution(0, 500) {}

    void tick() override
    {
        MovingSprite::tick();

        if (getRect()->x > 1200 - 40)
        {
            setDirection(4);
        }

        if (getRect()->x < 0)
        {
            setDirection(2);
        }

        int roll = distribution(generator);
        if (roll == 1)
        {
            Mix_PlayChannel(-1, lazer, 0);
            Bullet *b = new Bullet(getRect()->x + 20, 200 + 40, 10, 50, "images/bullet-down.png", 3, 10);
            ses.add(b);
        }
    }

private:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

    Mix_Chunk *lazer = Mix_LoadWAV((constants::gResPath + "sounds/lazer.wav").c_str());
};

int main(int argc, char **argv)
{
    ge.setWindow("Blastar", 1200, 800, 0);
    ge.setMusic("sounds/8bit-menu-slow.mp3");

    Background *bg = new Background(0, 0, ge.getW(), ge.getH(), "images/space.jpg", 3, 1);
    ses.add(bg);

    Ghost *s1 = new Ghost(ge.getW() * 0.20, 80, 40, 40, "images/red-ghost.png");
    Ghost *s2 = new Ghost(ge.getW() * 0.4, 80, 40, 40, "images/pink-ghost.png");
    Ghost *s3 = new Ghost(ge.getW() * 0.6, 80, 40, 40, "images/yellow-ghost.png");
    Ghost *s4 = new Ghost(ge.getW() * 0.8, 80, 40, 40, "images/blue-ghost.png");

    ses.add(s1);
    ses.add(s2);
    ses.add(s3);
    ses.add(s4);

    MovingGhost *ms1 = new MovingGhost(500, 200, 40, 40, "images/blue-ghost.png", 4, 5);
    ses.add(ms1);

    Player *player = new Player(500, ge.getH() - 100, 100, 100, "images/ship.png");
    ses.add(player);

    ses.run();

    return 0;
}
