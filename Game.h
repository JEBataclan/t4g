#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

class Game
{

public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    void menuEvents();
    void menuUpdate();
    void menuRender();
    bool activeMenu;


    bool running() {return isRunning;}


private:
    bool isRunning;

    std::vector<SDL_Rect> gColliders;
    std::vector<int> pxLoc;
    std::vector<int> pyLoc;
    int rounds = 1;

    int Mx;
    int My;
    bool selectPlay = false;
    bool selectHelp = false;
    bool selectBack = false;
    bool helpDisplay = false;
    float gameStartTime;
    float winTime;

    SDL_Window* window;
    SDL_Renderer* renderer;

};

#endif // GAME_H
