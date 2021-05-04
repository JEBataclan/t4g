#include "GameText.h"
#include "TextureManager.h"
#include <string>

GameText::GameText(const char *text, SDL_Renderer *ren, int x, int y, int w, int h, SDL_Color color, int ptsize, int tFrame)
{
    renderer = ren;

    objText = TextureManager::LoadText(text, ren, color, ptsize);

    xpos = x;
    ypos = y;

    width = w;
    height = h;
    textFrame = tFrame;

    rectX = 0;
}

GameText::~GameText()
{
    SDL_DestroyTexture(objText);
}

void GameText::Update()
{
    if (RoundWin) {
        rectX += 10;
    }
    RoundWin = false;



    srcRect.w = width/textFrame;
    srcRect.h = height;
    srcRect.x = 0 + rectX;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;;
    destRect.w = width;
    destRect.h = height;
}

void GameText::Render()
{
    SDL_RenderCopy(renderer, objText, &srcRect, &destRect);
}
