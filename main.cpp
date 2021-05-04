#include <iostream>
#include <stack>
#include "Game.h"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

Game *game = NULL;

int main(int argc, char *argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("T4G", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
               SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while (game->running()) {
        frameStart = SDL_GetTicks();

        if(game->activeMenu == false){
        game->handleEvents();

        game->update();
        game->render();
        }

        if(game->activeMenu == true){
        game->menuEvents();

        game->menuUpdate();
        game->menuRender();
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
}
