#include "Constants.h"

#include <string>
#include <random>

#include "System.h"
#include "Session.h"
#include "CollisionHandler.h"

#include "Sprite.h"
#include "MovingSprite.h"
#include "BackgroundSprite.h"

using namespace twoD;

Session ses(60);

// BULLET
class Bullet : public MovingSprite
{
public:
    Bullet(int x, int y, int w, int h, int direction, int speed, std::initializer_list<std::string> ss) : MovingSprite(x, y, w, h, direction, speed, ss) {}

    void tick()
    {
        MovingSprite::tick();
        if (getRect()->y < -10 || getRect()->y > sys.getH())
            ses.remove(this);
    }
};

// CHECK COLLISION
void checkCollision(Sprite *sprite)
{
    auto sprites = ses.getSprites();
    for (Sprite *s : sprites)
    {
        if (Bullet *b = dynamic_cast<Bullet *>(s))
        {
            if (CollisionHandler::collided(b->getRect(), sprite->getRect()))
            {
                ses.remove(b);
                ses.remove(sprite);
            }
        }
    }
};

// PLAYER
// SPEL-KLASS
class Player : public Sprite
{
public:
    Player(int x, int y, int w, int h, std::initializer_list<std::string> ss) : Sprite(x, y, w, h, ss) {}

    void tick() override
    {
        handleMovement();
        checkCollision(this);
        counter++;
        if (counter == 8)
        {
            setTexture(getSpriteSheet()[1]);
        }
        if (counter == 12)
        {
            setTexture(getSpriteSheet()[0]);
            counter = 0;
        }
    }

    void keyDown(const SDL_Event &eve)
    {
        switch (eve.key.keysym.sym)
        {
        case SDLK_LEFT:
            moveLeft = true;
            break;
        case SDLK_RIGHT:
            moveRight = true;
            break;
        case SDLK_SPACE:
            if (!spacePressed)
            {
                spacePressed = true;
                sys.playSound("lazer");
                Bullet *b = new Bullet(getRect()->x + 40, getRect()->y - 51, 10, 50, UP, 10, {"images/bullet.png"});
                ses.add(b);
            }
        default:
            break;
        }
    }

    void keyUp(const SDL_Event &eve)
    {
        switch (eve.key.keysym.sym)
        {
        case SDLK_LEFT:
            moveLeft = false;
            break;
        case SDLK_RIGHT:
            moveRight = false;
            break;
        case SDLK_SPACE:
            spacePressed = false;
            break;
        default:
            break;
        }
    }

private:
    bool spacePressed = false;
    bool moveLeft = false;
    bool moveRight = false;
    int counter = 0;

    void handleMovement()
    {
        if (moveLeft)
        {
            if (getRect()->x > 0)
            {
                getRect()->x -= 6;
            }
        }
        if (moveRight)
        {
            if (getRect()->x < sys.getW() - getRect()->w)
            {
                getRect()->x += 6;
            }
        }
    }
};

// SPEL-KLASS
class RandomInterval
{
public:
    void setInterval(int from, int to) { std::uniform_int_distribution<int>(from, to); }

protected:
    RandomInterval() : generator(std::random_device{}()), distribution(0, 500) {}

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
};

// GHOST
// SPEL-KLASS
class Ghost : public Sprite, private RandomInterval
{
public:
    Ghost(int x, int y, int w, int h, std::initializer_list<std::string> ss) : Sprite(x, y, w, h, ss) {}

    void tick()
    {
        checkCollision(this);

        int roll = distribution(generator);
        if (roll == 1)
        {
            sys.playSound("lazer");
            Bullet *b = new Bullet(getRect()->x + 20, getRect()->y + getRect()->h + 1, 10, 50, DOWN, 10, {"images/bullet-down.png"});
            ses.add(b);
        }
        if (roll > 1 && roll < 10)
        {
            setTexture(getSpriteSheet()[0]);
        }
        else if (roll > 10 && roll < 20)
        {
            setTexture(getSpriteSheet()[1]);
        }
    }
};

// MOVINGGHOST
// SPEL-KLASS
class MovingGhost : public MovingSprite, private RandomInterval
{
public:
    MovingGhost(int x, int y, int w, int h, int d, int s, std::initializer_list<std::string> ss) : MovingSprite(x, y, w, h, d, s, ss) {}

    void tick() override
    {
        MovingSprite::tick();

        if (getRect()->x > 1200 - 40)
        {
            setDirection(LEFT);
            setTexture(getSpriteSheet()[0]);
        }

        if (getRect()->x < 0)
        {
            setDirection(RIGHT);
            setTexture(getSpriteSheet()[1]);
        }

        checkCollision(this);

        int roll = distribution(generator);
        if (roll == 1)
        {
            sys.playSound("lazer");
            Bullet *b = new Bullet(getRect()->x + 20, getRect()->y + getRect()->h + 1, 10, 50, DOWN, 10, {"images/bullet-down.png"});
            ses.add(b);
        }
    }
};

int main(int argc, char **argv)
{
    sys.setWindow("Blastar", 1200, 800, 0);

    sys.setMusic("sounds/8bit-menu-slow.mp3");

    sys.addSound("lazer", "sounds/lazer.wav");

    BackgroundSprite *bg = BackgroundSprite::getInstance(0, 0, sys.getW(), sys.getH(), DOWN, 1, {"images/space.jpg"});
    ses.add(bg);

    Ghost *s1 = new Ghost(sys.getW() * 0.20, 80, 40, 40, {"images/red-ghost.png", "images/pink-ghost-2.png"});
    Ghost *s2 = new Ghost(sys.getW() * 0.4, 80, 40, 40, {"images/pink-ghost.png", "images/pink-ghost-2.png"});
    Ghost *s3 = new Ghost(sys.getW() * 0.6, 80, 40, 40, {"images/yellow-ghost.png", "images/pink-ghost-2.png"});
    Ghost *s4 = new Ghost(sys.getW() * 0.8, 80, 40, 40, {"images/blue-ghost.png", "images/pink-ghost-2.png"});

    ses.add(s1);
    ses.add(s2);
    ses.add(s3);
    ses.add(s4);

    MovingGhost *ms1 = new MovingGhost(500, 200, 40, 40, LEFT, 5, {"images/blue-ghost.png", "images/blue-ghost-2.png"});
    ses.add(ms1);

    Player *player = new Player(500, sys.getH() - 100, 100, 100, {"images/ship.png", "images/ship-idle-2.png"});
    ses.add(player);

    ses.run();

    return 0;
}
