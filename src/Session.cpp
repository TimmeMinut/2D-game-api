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
        // delete bg_rect1;
        // delete bg_rect2;
    }

    void Session::add(Sprite *s)
    {
        sprites.push_back(s);
    }

    void Session::remove(Sprite *s)
    {
        removed.push_back(s);
    }

    /*
        void Session::setBackground(std::string path)
        {
            SDL_Surface *bg_sur = IMG_Load((constants::gResPath + path).c_str());
            bg_tx = SDL_CreateTextureFromSurface(ge.getRen(), bg_sur);
            SDL_FreeSurface(bg_sur);

            bg_rect1 = new SDL_Rect{0, 0, 640, 480};
        }

        void Session::setBackground(std::string path, int direction, int speed)
        {
            if (speed <= 0)
            {
                throw std::invalid_argument("Speed needs to be a positive integer!");
                std::cout << "At Session::set_background()";
            }

            SDL_Surface *bg_sur = IMG_Load((constants::gResPath + path).c_str());
            bg_tx = SDL_CreateTextureFromSurface(ge.getRen(), bg_sur);
            SDL_FreeSurface(bg_sur);

            bg_direction = direction;
            bg_speed = speed;

            bg_rect1 = new SDL_Rect{0, 0, 640, 480}; // TODO: constants for W H
            switch (bg_direction)
            {
            case 1: // down
                bg_rect2 = new SDL_Rect{0, -480, 640, 480};
                break;
            case 2: // left
                bg_rect2 = new SDL_Rect{640, 0, 640, 480};
                break;
            case 3: // up
                bg_rect2 = new SDL_Rect{0, 480, 640, 480};
                break;
            case 4: // right
                bg_rect2 = new SDL_Rect{-640, 0, 640, 480};
            default:
                break;
            }
        }
    */

    /*
    void Session::loopBackground()
    {
        switch (bg_direction)
        {
        case 1: // down
            bg_rect1->y += bg_speed;
            bg_rect2->y += bg_speed;

            if (bg_rect1->y >= 480)
                bg_rect1->y = -480;

            if (bg_rect2->y >= 480)
                bg_rect2->y = -480;
            break;
        case 2: // left
            bg_rect1->x -= bg_speed;
            bg_rect2->x -= bg_speed;

            if (bg_rect1->x <= -640)
                bg_rect1->x = 640;

            if (bg_rect2->x <= -640)
                bg_rect2->x = 640;
            break;
        case 3: // up
            bg_rect1->y -= bg_speed;
            bg_rect2->y -= bg_speed;

            if (bg_rect1->y <= -480)
                bg_rect1->y = 480;

            if (bg_rect2->y <= -480)
                bg_rect2->y = 480;
            break;
        case 4: // right
            bg_rect1->x += bg_speed;
            bg_rect2->x += bg_speed;

            if (bg_rect1->x >= 640)
                bg_rect1->x = -640;

            if (bg_rect2->x >= 640)
                bg_rect2->x = -640;
        default:
            break;
        }
    }
    */

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

            // Draw background
            // loopBackground();
            // SDL_RenderCopy(ge.getRen(), bg_tx, NULL, bg_rect1);
            // SDL_RenderCopy(ge.getRen(), bg_tx, NULL, bg_rect2);

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