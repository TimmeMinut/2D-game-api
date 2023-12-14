

// #include <iostream>
// #include <string>
// #include "Constants.h"

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_ttf.h>

// using namespace std;
// #define FPS 60

// int main(int argc, char *argv[])
// {

// 	SDL_Init(SDL_INIT_EVERYTHING);
// 	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 1024);

// 	// Sounds
// 	Mix_Chunk *lazer = Mix_LoadWAV((constants::gResPath + "sounds/lazer.wav").c_str());

// 	const int SCREEN_W = 640;
// 	const int SCREEN_H = 480;

// 	const int PLAYER_W = 60;
// 	const int PLAYER_H = 60;
// 	const int START_POSX = (SCREEN_W / 2) - (PLAYER_W / 2);
// 	const int START_POSY = SCREEN_H - PLAYER_H;

// 	const int BULLET_W = 10;
// 	const int BULLET_H = 15;

// 	SDL_Window *win = SDL_CreateWindow("Blastar", 100, 100, SCREEN_W, SCREEN_H, 0);
// 	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);

// 	// Background
// 	SDL_Surface *bg_sur = IMG_Load((constants::gResPath + "images/stars.jpg").c_str());
// 	SDL_Texture *bg_tx = SDL_CreateTextureFromSurface(ren, bg_sur);
// 	SDL_FreeSurface(bg_sur);

// 	// Player
// 	SDL_Surface *player_sur = IMG_Load((constants::gResPath + "images/spaceship.png").c_str());
// 	SDL_Texture *player_tx = SDL_CreateTextureFromSurface(ren, player_sur);
// 	SDL_Rect player_rect = {START_POSX, START_POSY, PLAYER_W, PLAYER_H};
// 	SDL_FreeSurface(player_sur);

// 	// Bullet
// 	SDL_Surface *bullet_sur = IMG_Load((constants::gResPath + "images/bullet.png").c_str());
// 	SDL_Texture *bullet_tx = SDL_CreateTextureFromSurface(ren, bullet_sur);
// 	SDL_FreeSurface(bullet_sur);

// 	const int tickInterval = 1000 / FPS;
// 	bool running = true;

// 	while (running)
// 	{
// 		Uint32 nextTick = SDL_GetTicks64() + tickInterval;

// 		SDL_Event eve;
// 		while (SDL_PollEvent(&eve))
// 		{
// 			switch (eve.type)
// 			{
// 			case SDL_QUIT:
// 				running = false;
// 				break;
// 			case SDL_KEYDOWN:
// 				switch (eve.key.keysym.sym)
// 				{
// 				case SDLK_LEFT:
// 					if (player_rect.x > 0)
// 					{
// 						player_rect.x -= 8;
// 					}
// 					break;
// 				case SDLK_RIGHT:
// 					if (player_rect.x < SCREEN_W - PLAYER_W)
// 					{
// 						player_rect.x += 8;
// 					}
// 					break;
// 				case SDLK_SPACE:
// 					// play sound and shoot
// 					Mix_PlayChannel(-1, lazer, 0);

// 					SDL_Rect bullet_rect = {player_rect.x + 22, START_POSY, BULLET_W, BULLET_H};
// 					for (int i = 0; i < SCREEN_H; i++)
// 					{
// 						bullet_rect.y--;
// 						SDL_RenderClear(ren);
// 						SDL_RenderCopy(ren, bg_tx, NULL, NULL);
// 						SDL_RenderCopy(ren, player_tx, NULL, &player_rect);
// 						SDL_RenderCopy(ren, bullet_tx, NULL, &bullet_rect);
// 						SDL_RenderPresent(ren);

// 						int delay = nextTick - SDL_GetTicks64();
// 						if (delay > 0)
// 						{
// 							SDL_Delay(delay);
// 						}
// 					}
// 					break;
// 				}
// 			}
// 		}

// 		SDL_RenderClear(ren);
// 		SDL_RenderCopy(ren, bg_tx, NULL, NULL);
// 		SDL_RenderCopy(ren, player_tx, NULL, &player_rect);
// 		SDL_RenderPresent(ren);

// 		int delay = nextTick - SDL_GetTicks64();
// 		if (delay > 0)
// 		{
// 			SDL_Delay(delay);
// 		}
// 	}

// 	// Städa!

// 	SDL_DestroyTexture(bg_tx);
// 	SDL_DestroyTexture(player_tx);
// 	SDL_DestroyRenderer(ren);
// 	SDL_DestroyWindow(win);

// 	Mix_CloseAudio();
// 	TTF_Quit();
// 	SDL_Quit();

// 	return EXIT_SUCCESS;
// }