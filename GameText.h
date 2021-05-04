#pragma once

#include "Game.h"

class GameText {
public:
    GameText(const char* text, SDL_Renderer* ren, int x, int y, int w, int h, SDL_Color color, int ptsize, int tFrame);
    ~GameText();

    void Update();
    void Render();

    bool RoundWin = false;
    void GameEnd();
    int rectX;

    SDL_Texture *objText;
    int xpos;
private:

    int ypos;
    int width;
    int height;
    int textFrame;




    SDL_Rect srcRect, destRect;
    SDL_Renderer *renderer;

};

