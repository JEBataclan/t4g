#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *texturesheet, SDL_Renderer *ren, float x, float y, float w, float h)
{
    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet, ren);

    xpos = x;
    ypos = y;

    width = w;
    height = h;

    collider.x = xpos;
    collider.y = ypos;
    collider.w = width;
    collider.h = height;
}

GameObject::~GameObject()
{
    SDL_DestroyTexture(objTexture);
}

void GameObject::Update()
{
    srcRect.w = width;
    srcRect.h = height;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;;
    destRect.w = width;
    destRect.h = height;

    collider.x = xpos;
    collider.y = ypos;
    collider.w = width;
    collider.h = height;
}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
