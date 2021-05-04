#include "Player2.h"
#include "TextureManager.h"
#include <SDL.h>

Player2::Player2(const char* filename, SDL_Renderer *ren, float x, float y, float w, float h)
{
    renderer = ren;

    objTexture = TextureManager::LoadTexture(filename, renderer);

    xpos = x;
    ypos = y;

    width = w;
    height = h;

    collider.w = width;
    collider.h = height;

    hitbox.w = width - 10;
    hitbox.h = height;
}

Player2::~Player2()
{}

void Player2::HandleEvents(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                if (grounded&&!crouching) {
                    yvel = -4.75;
                    grounded = false;
                    onGravity = true;
                    jumpTime = SDL_GetTicks();
                }
                break;
            case SDLK_LEFT:
                if(!crouching){
                animated = true;
                xvel = -1*minSpeed;
                accelerating = true;
                startRun = SDL_GetTicks();}
                spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_RIGHT:
                if(!crouching){animated = true;
                xvel = minSpeed;
                accelerating = true;
                startRun = SDL_GetTicks();}
                spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_DOWN:
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
            case SDLK_LEFT:
                if (!keystate[SDL_SCANCODE_RIGHT]&&!crouching){
                        animated = false;
                        spriteFlip = SDL_FLIP_HORIZONTAL;
                        xvel = 0;
                        accelerating = false;}
                else if(!crouching){spriteFlip = SDL_FLIP_NONE;
                        xvel = minSpeed;
                        accelerating = true;}
                break;
            case SDLK_RIGHT:
                if (!keystate[SDL_SCANCODE_LEFT]&&!crouching){
                        animated = false;
                        spriteFlip = SDL_FLIP_NONE;
                        xvel = 0;
                        accelerating = false;}
                else if(!crouching){spriteFlip = SDL_FLIP_HORIZONTAL;
                        xvel = -1*minSpeed;
                        accelerating = true;}
                break;
                case SDLK_DOWN:
                    crouching = false;
                    if(keystate[SDL_SCANCODE_LEFT]||keystate[SDL_SCANCODE_RIGHT]){
                        animated = true;
                        accelerating = true;
                        }
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

    if (grounded & !crouching) {
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
        if(keystate[SDL_SCANCODE_RIGHT])
        xvel += dxTime*accel;
        if (xvel >= maxSpeed)
            xvel = maxSpeed;
        if(keystate[SDL_SCANCODE_LEFT])
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

void Player2::Update()
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

void Player2::Render()
{
    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &destRect, NULL, NULL, spriteFlip);
}

void Player2::RestartPos(int rounds)
{
    if(rounds%2){
    xpos = 750;
    ypos = 400;
    }
    else{
    xpos = 750;
    ypos = 0;
    }

    xvel = 0;
    jumpTime = SDL_GetTicks();
    onGravity = true;
   // animated = false;
    spawnTime = SDL_GetTicks();
    SDL_SetTextureColorMod(objTexture, 255, 255 ,255);
}
