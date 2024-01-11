#include "System.h"
#include "Sprite.h"
namespace twoD
{

    Sprite::Sprite(int x, int y, int w, int h, std::initializer_list<std::string> ss) : rect(new SDL_Rect{x, y, w, h}), spriteSheet(ss), tx(sys.createTexture(spriteSheet[0])) {};

    void Sprite::draw() const
    {
        SDL_RenderCopy(sys.getRen(), getTexture(), NULL, getRect());
    }

    void Sprite::setTexture(std::string path)
    {
        if (tx)
            SDL_DestroyTexture(tx);
        tx = sys.createTexture(path);
    }

    Sprite::~Sprite()
    {
        SDL_DestroyTexture(tx);
        delete rect;
    }
}