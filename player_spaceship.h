#ifndef enemy_spaceship_h
#define enemy_spaceship_h

#include "window.h"
#include "spaceship.h"
#include "thread.h"

class PlayerSpaceShip: public SpaceShip
{
public:

    //PlayerSpaceShip(int x, int y);
    //virtual ~PlayerSpaceShip();

    //Implementando as virtual functions.
    virtual void run();
    virtual void makeMove();

    //Funcoes especificas da PlayerSpaceShip


   

protected:
    ;
};

#endif
