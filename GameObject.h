#pragma once

#include "Game.h"

class GameObject {
public:
    GameObject(const char *texturesheet, SDL_Renderer* ren, float x, float y, float w, float h);
    ~GameObject();

    void Update();
    void Render();

    SDL_Rect collider;
    float xpos;
    float ypos;
    float width;
    float height;


private:

    SDL_Texture *objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer *renderer;

};
