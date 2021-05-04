#include "PowerUp.h"
#include "TextureManager.h"

PowerUp::PowerUp(const char *filename, SDL_Renderer *ren, int x, int y, int w, int h, int random)
{
    renderer = ren;

    objTexture = TextureManager::LoadTexture("assets/powerups.png", renderer);

    xpos = x;
    ypos = y;

    width = w;
    height = h;

    powerup = random;
}

PowerUp::~PowerUp()
{
    SDL_DestroyTexture(objTexture);
}

void PowerUp::Update()
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

    if (animated && powerup == 0) {
        srcRect.y = 0;
        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / fspeed ) % frames);
    }

    if (animated && powerup == 1) {
        srcRect.y = 30;
        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / fspeed ) % frames);
    }


}
void PowerUp::Effect(int *onPowerup, int powerup)
{
    if(onEffect){
        if(powerup == 0)
        *onPowerup = -1;
        else
        *onPowerup = 1;
    }
    else {
        *onPowerup = 0;
    }
}

void PowerUp::Render(bool isActive)
{

    if(isActive)
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
    else{
    SDL_DestroyTexture(objTexture);
    objTexture = NULL;}

}
