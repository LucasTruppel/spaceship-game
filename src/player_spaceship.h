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

    void receiveDamage();

    float getInvencibleTimer() {return _invencible_timer;};
    void setInvencibleTimer(float new_timer) {_invencible_timer = new_timer;}
    void resetTimer() {_invencible_timer = 0;}

private:
    float _invencible_timer;
    sf::Clock* clock;
};

#endif
