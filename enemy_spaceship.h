#ifndef enemy_spaceship_h
#define enemy_spaceship_h

#include "window.h"
#include "spaceship.h"
#include "thread.h"

class EnemySpaceShip: public SpaceShip
{
public:

    
    SpaceShip(int x, int y);
    virtual ~SpaceShip();


    //Pure virtual functions
    virtual void run() = 0;
    virtual void makeMove() = 0;          
   

protected:
    volatile State _state;

    sf::Texture spaceship_up;
    sf::Texture spaceship_down;
    sf::Texture spaceship_left;
    sf::Texture spaceship_right;

    sf::Texture spaceship_tex;
    sf::Sprite spaceship_sprite;
};

#endif
