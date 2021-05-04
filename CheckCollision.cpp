#include "CheckCollision.h"

bool CheckCollision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
    if (
        recA.x + recA.w > recB.x &&
        recB.x + recB.w > recA.x &&
        recA.y + recA.h > recB.y &&
        recB.y + recB.h > recA.y
        )
    {
        return true;
    }
    return false;
}

bool CheckCollision::AABB(const SDL_Rect& recA, std::vector<SDL_Rect>& recB)
{
    for (int set = 0; set < recB.size(); set++) {
        if (
            recA.x + recA.w > recB[set].x &&
            recB[set].x + recB[set].w > recA.x &&
            recA.y + recA.h > recB[set].y &&
            recB[set].y + recB[set].h > recA.y
            )
        {
            return true;
        }
    }
    return false;

}

bool CheckCollision::MousePos(int Mx, int My, SDL_Rect recA)
{
    if(
        Mx > recA.x          &&
        recA.x + recA.w > Mx &&
        My > recA.y          &&
        recA.y + recA.h > My
       )
        return true;
    else
    return false;
}
