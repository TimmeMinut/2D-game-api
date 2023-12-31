#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "Constants.h"
#include "GameEngine.h"
#include "Session.h"
#include "Sprite.h"

namespace twoD
{

    Session::Session(int fps)
    {
        this->fps = fps;
    }

    Session::~Session()
    {
    }

    void Session::add(Sprite *s)
    {
        sprites.push_back(s);
    }

    void Session::remove(Sprite *s)
    {
        removed.push_back(s);
    }

    void Session::run()
    {
        Uint32 tickInterval = 1000 / fps;

        bool running = true;
        while (running)
        {
            Uint32 nextTick = SDL_GetTicks() + tickInterval;
            SDL_Event eve;
            while (SDL_PollEvent(&eve))
            {
                switch (eve.type)
                {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for (Sprite *s : sprites)
                        s->mouseDown(eve);
                    break;
                case SDL_MOUSEBUTTONUP:
                    for (Sprite *s : sprites)
                        s->mouseUp(eve);
                    break;
                case SDL_KEYDOWN:
                    for (Sprite *s : sprites)
                        s->keyDown(eve);
                    break;
                case SDL_KEYUP:
                    for (Sprite *s : sprites)
                        s->keyUp(eve);
                    break;
                } // switch
            }     // inre while

            // Call tick functions
            for (Sprite *s : sprites)
                s->tick();

            // Add new sprites
            for (Sprite *s : added)
                sprites.push_back(s);
            added.clear();

            // Remove sprites
            for (Sprite *s : removed)
            {
                for (std::vector<Sprite *>::iterator i = sprites.begin(); i != sprites.end();)
                {
                    if (*i == s)
                    {
                        i = sprites.erase(i);
                        delete s;
                    }
                    else
                    {
                        i++;
                    }
                }
            }
            removed.clear();

            SDL_RenderClear(ge.getRen());

            // Draw sprites
            for (Sprite *s : sprites)
                s->draw();

            SDL_RenderPresent(ge.getRen());

            int delay = nextTick - SDL_GetTicks();
            if (delay > 0)
                SDL_Delay(delay);
        } // yttre while
    }
}