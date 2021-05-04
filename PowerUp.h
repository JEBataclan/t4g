#pragma once

#include "Game.h"

class PowerUp
{
public:
    PowerUp(const char *filename, SDL_Renderer* ren, int x, int y, int w, int h, int random);
    ~PowerUp();

    void Update();
    void Render(bool isActive);
    int CheckPlayer(int player)
     {return player;};
    void Effect(int *onPowerup, int powerup);
    bool onEffect;
    int player;
    int powerup;

    bool isActive;
    float pickUpTime;
    float pspawnTime;

    SDL_Rect collider;

private:
    int xpos;
    int ypos;
    int width;
    int height;



    bool animated = true;
    int frames = 13;
    int fspeed = 80;

    SDL_Texture *objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer *renderer;

};

