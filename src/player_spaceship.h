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
    ~PlayerSpaceShip();

    // Implementando as virtual functions.
    static void run(PlayerSpaceShip *playerSpaceShip);

    // Funcoes especificas da PlayerSpaceShip
    void makeMoveUP();
    void makeMoveDOWN();
    void makeMoveLEFT();
    void makeMoveRIGHT();

    void receiveDamage();

    void damagedSprite();
    void nonDamagedSprite();

    float getInvencibleTimer() { return _invencible_timer; };

private:
    float _invencible_timer;
    float _last_tick = 0;
    sf::Clock *clock;
    static int const _movement_pixels = 25;

    sf::Texture damaged_up;
    sf::Texture damaged_down;
    sf::Texture damaged_left;
    sf::Texture damaged_right;

    sf::Texture not_damaged_up;
    sf::Texture not_damaged_down;
    sf::Texture not_damaged_left;
    sf::Texture not_damaged_right;
};

#endif
