#include "Enemy.h"
#include "TextureManager.h"

Enemy::Enemy(int x, int y, SDL_Texture* tex)
{
    this->xpos = x;
    this->ypos = y;
    this->objTexture = tex;
}


void Enemy::update()
{
    //std::cout << "Moving: " << xpos << "," << ypos << std::endl;

    frame = (SDL_GetTicks() / 130) % frameCount;

    if(!hasTarget)
        

    if (!hasTarget) return;

    xpos += dx * 2;
    ypos += dy * 2;

    double dist = sqrt((targetCoordinates.x - xpos) * (targetCoordinates.x - xpos) +
        (targetCoordinates.y - ypos) * (targetCoordinates.y - ypos));

    if (dist < 2.0)
    {
        xpos = targetCoordinates.x;
        ypos = targetCoordinates.y;

        hasTarget = false;

    }
    //cout << xpos << " " << ypos << endl;

}


void Enemy::dig(Map& map)
{
    
}


void Enemy::render(SDL_Renderer* renderer)
{
    SDL_Rect src = { frame * width, 0 , width, height };
    SDL_Rect dest = { xpos, ypos, width, height };
    SDL_RenderCopy(renderer, objTexture, &src, &dest);

}

//no change
void Enemy::changeAnimation(Direction direction)
{}



void Enemy::chase(Map& map, int playerX, int playerY)
{
   // cout << "Has target set\n";
    //if (hasTarget) return;

    SDL_Point playerCoordinates = { playerX, playerY };
    SDL_Point enemyCoordinates = { (xpos + width /2) / TILE,  (ypos + height /2 - MAP_OFFSET_Y) / TILE };


    std::cout << "Enemy tile walkable: "
        << map.isWalkable(enemyCoordinates.x, enemyCoordinates.y)
        << std::endl;


    SDL_Point nextStep = map.getNextStep( enemyCoordinates, playerCoordinates);

    if (nextStep.x == enemyCoordinates.x && nextStep.y == enemyCoordinates.y)
    {
        dx = dy = 0;
        //hasTarget = false;
        return;
    }

    SDL_Point target = { nextStep.x * TILE + TILE / 2, MAP_OFFSET_Y + nextStep.y * TILE + TILE / 2 };

    /*std::cout << "Enemy pos: " << xpos << "," << ypos << std::endl;
    std::cout << "Target pos: " << target.x << "," << target.y << std::endl;*/

    dx = target.x - xpos;
    dy = target.y - ypos;

    double len = sqrt(dx * dx + dy * dy);
    
    if (len == 0.0)
    {
        //hasTarget = false;
        return;
    }
    dx /= len;
    dy /= len;

    targetCoordinates = target;
    hasTarget = true;
}





const bool Enemy::hasTargetNow() const
{
    return hasTarget;
}