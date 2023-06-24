#ifndef spaceship_h
#define spaceship_h

#include <iostream>
#include "thread.h"
#include "semaphore.h"
#include "window.h"

using namespace SOLUTION;

class SpaceShip
{
public:

    //SpaceShip State
    enum State {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        DEAD,
    };
    


    SpaceShip(int x, int y);
    ~SpaceShip();

    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();

    void shoot();

    State getState() {return _state;}

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
