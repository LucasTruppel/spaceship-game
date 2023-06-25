#ifndef player_spaceship_h
#define player_spaceship_h

#include "thread.h"
#include "spaceship.h"
#include "enemy_spaceship.h"
#include "game_handler.h"

using namespace SOLUTION;

class PlayerSpaceShip : public SpaceShip
{
public:
    PlayerSpaceShip(int x, int y);
    // virtual ~PlayerSpaceShip();

    // Implementando as virtual functions.
    static void run(PlayerSpaceShip *playerSpaceShip);

    // Funcoes especificas da PlayerSpaceShip
    void makeMoveUP();
    void makeMoveDOWN();
    void makeMoveLEFT();
    void makeMoveRIGHT();
};

#endif
