#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *filename, SDL_Renderer *ren)
{
    SDL_Surface *tempSurface = IMG_Load(filename);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

SDL_Texture *TextureManager::LoadText(const char* text, SDL_Renderer* ren, SDL_Color color, int ptsize)
{
    TTF_Font* font = TTF_OpenFont("AtariST8x16SystemFont.ttf", ptsize);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    return Message;
}


