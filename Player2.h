#pragma once

#include "Game.h"

class Player2 {
public:
    Player2(const char* filename, SDL_Renderer* ren, float x, float y, float w, float h);
    ~Player2();

    void HandleEvents(SDL_Event);
    void Update();
    void Render();
    void RestartPos(int rounds);

    float xpos, ypos;
    float width, height;
    float xvel = 0, yvel = 0;
    float speed = 4.0;
    float defSpeed = 4.0;

    float gravity = .5;
    float jumpTime;
    float airTime;
    float dyTime;
    bool onGravity;
    bool falling;

    float minSpeed;
    float maxSpeed;
    float accel;
    bool accelerating;
    float startRun;
    float duringRun;
    float dxTime;

    int onPowerup = 0;

    float spawnTime;

    int pts = 0;

    SDL_Rect collider;
    SDL_Rect hitbox;

    bool grounded = false;
    bool crouching = false;
    SDL_Texture *objTexture;
private:

    bool animated = false;
    int frames = 9;
    int fspeed = 50;
    int jumpHeight;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    SDL_RendererFlip spriteFlip;

    const char* texture;


    SDL_Rect srcRect, destRect;
    SDL_Renderer *renderer;

};
