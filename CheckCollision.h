#pragma once

#include "Game.h"

class CheckCollision
{

public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const SDL_Rect& recA, std::vector<SDL_Rect>& recB);
    static bool MousePos(int Mx, int My, SDL_Rect recA);

};
