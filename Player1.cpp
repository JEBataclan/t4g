#include "Player1.h"
#include "TextureManager.h"
#include <iostream>

Player1::Player1(const char* filename, SDL_Renderer *ren, float x, float y, float w, float h)
{
    renderer = ren;

    objTexture = TextureManager::LoadTexture(filename, renderer);

    xpos = x;
    ypos = y;

    width = w;
    height = h;

    collider.w = width;
    collider.h = height;

   // hitbox.x = x+5;
   // hitbox.y = y;
    hitbox.w = width - 10;
    hitbox.h = height;

    std::cout<<hitbox.x<<hitbox.y<<hitbox.w<<hitbox.h<<std::endl;
}

Player1::~Player1()
{}

void Player1::HandleEvents(SDL_Event event)
{

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                if (grounded&&!crouching) {
                    yvel = -4.75;
                    grounded = false;
                    onGravity = true;
                    jumpTime = SDL_GetTicks();
                }
                break;
            case SDLK_a:
                if(!crouching){
                animated = true;
                xvel = -1*minSpeed;
                accelerating = true;
                startRun = SDL_GetTicks();}
                spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_d:
                if(!crouching){animated = true;
                xvel = minSpeed;
                accelerating = true;
                startRun = SDL_GetTicks();}
                spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_s:
                if(grounded){
                crouching = true;
                xvel = 0;
                accelerating = false;};
                break;
            default:
                break;
        }
    }

    if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                if (!keystate[SDL_SCANCODE_D]&&!crouching){
                        animated = false;
                        spriteFlip = SDL_FLIP_HORIZONTAL;
                        xvel = 0;
                        accelerating = false;}
                else if (!crouching){spriteFlip = SDL_FLIP_NONE;
                        xvel = minSpeed;
                        accelerating = true;}
                break;
            case SDLK_d:
                if (!keystate[SDL_SCANCODE_A]&&!crouching){
                        animated = false;
                        spriteFlip = SDL_FLIP_NONE;
                        xvel = 0;
                        accelerating = false;}
                else if(!crouching){spriteFlip = SDL_FLIP_HORIZONTAL;
                        xvel = -1*minSpeed;
                        accelerating = true;}
                break;
                case SDLK_s:
                    crouching = false;
                    animated = false;
                    if(keystate[SDL_SCANCODE_D]||keystate[SDL_SCANCODE_A]){
                        animated = true;
                        accelerating = true;}

                break;
            default:
                break;
        }
    }


    if(onGravity){
        airTime = SDL_GetTicks();
        dyTime = (airTime - jumpTime)/1000;
        yvel += (dyTime*gravity);

        if(yvel >= 0 && falling == false){
            falling = true;
            jumpTime = SDL_GetTicks();
        }
        if(yvel > 10.0f)
            yvel = 10.0f;
        if(grounded){
            onGravity = false;
            falling = false;
        }
    }

    if (!grounded && !onGravity) {
            jumpTime = SDL_GetTicks();
            onGravity = true;
    }
    if (!grounded || onGravity) {
            hitbox.h = height - 30;
    }

    if (grounded && !crouching) {
        yvel = 4.0;
        hitbox.h = height;
    }
    if(crouching){
        hitbox.y = ypos + 30;
    }
    else
    hitbox.y = ypos;
    hitbox.x = xpos + 5;

    if(accelerating){
        duringRun = SDL_GetTicks();
        dxTime = (duringRun - startRun)/1000;
        if(keystate[SDL_SCANCODE_D])
        xvel += dxTime*accel;
        if (xvel >= maxSpeed)
            xvel = maxSpeed;
        if(keystate[SDL_SCANCODE_A])
        xvel -= dxTime*accel;
        if (xvel <= -1*maxSpeed)
            xvel = -1*maxSpeed;
    }

    if (onPowerup == 1)
    {
        minSpeed = 3.0f;
        maxSpeed = 6.0f;
        accel = .4f;
    }
    if (onPowerup == 0)
    {
        minSpeed = 2.5f;
        maxSpeed = 4.5f;
        accel = .3f;
    }
    if (onPowerup == -1)
    {
        minSpeed = 1.0f;
        maxSpeed = 3.0f;
        accel = .2f;
    }

}

void Player1::Update()
{
    srcRect.w = width;
    srcRect.h = height;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;;
    destRect.w = width;
    destRect.h = height;

    if (!animated && grounded) {
        srcRect.x = 0;
    }

    if (!grounded || onGravity) {
        srcRect.x = 41;
    }

    if (animated && grounded) {
        srcRect.x = 120 + (srcRect.w * static_cast<int>((SDL_GetTicks() / fspeed ) % frames));
    }
    if (crouching){
        srcRect.x = 82;
    }
}

void Player1::Render()
{
    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, NULL, NULL, spriteFlip);
}

void Player1::RestartPos(int rounds)
{
    if(rounds%2){
    xpos = 10;
    ypos = 0;
    }
    else{
    xpos = 10;
    ypos = 400;
    }

    xvel = 0;
    jumpTime = SDL_GetTicks();
    onGravity = true;
    spawnTime = SDL_GetTicks();
    SDL_SetTextureColorMod(objTexture, 255, 255 ,255);
}
