#ifndef SESSION_H
#define SESSION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <string>

#include "Sprite.h"

namespace twoD
{
  class Session
  {
  public:
    Session(int fps);
    ~Session();

    void add(Sprite *s);
    void remove(Sprite *s);
    void run();

    const std::vector<Sprite *> getSprites() { return sprites; }

    // void setBackground(std::string path);
    // void setBackground(std::string path, int direction, int speed);

  private:
    int fps;

    // int bg_direction, bg_speed;
    // SDL_Texture *bg_tx;
    // SDL_Rect *bg_rect1;
    // SDL_Rect *bg_rect2;
    // void loopBackground();

    std::vector<Sprite *> sprites, added, removed;
  };
}

#endif