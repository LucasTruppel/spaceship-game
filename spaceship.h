#ifndef spaceship_h
#define spaceship_h

#include <iostream>
#include "window.h"
#include "spaceship.h"

class SpaceShip
{
public:
    SpaceShip();
    virtual ~SpaceShip();

    //Pure virtual functions
    virtual void run() = 0;          
    virtual void turnUp() = 0;
    virtual void turnDown() = 0;
    virtual void turnLeft() = 0;
    virtual void turnRight() = 0;

protected:
    sf::Texture spaceship_up;
    sf::Texture spaceship_down;
    sf::Texture spaceship_left;
    sf::Texture spaceship_right;

    sf::Texture spaceship_tex;
    sf::Sprite spaceship_sprite;
};

#endif
