#include "GameEngine.h"
#include "Sprite.h"
namespace twoD
{

    Sprite::Sprite(int x, int y, int w, int h, std::string path) : rect(new SDL_Rect{x, y, w, h}), tx(twoD::ge.createTexture(path)){};

    void Sprite::draw() const
    {
        SDL_RenderCopy(ge.getRen(), getTexture(), NULL, getRect());
    }

    Sprite::~Sprite()
    {
        SDL_DestroyTexture(tx);
        delete rect;
    }
}