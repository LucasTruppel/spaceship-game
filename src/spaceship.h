#ifndef spaceship_h
#define spaceship_h

#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>
#include "shot.h"
#include "game_handler.h"


class SpaceShip
{
public:

    // SpaceShip State
    enum State {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        DEAD,
    };
    

    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();

    void shoot();


    State getState() {return _state;}
    sf::Sprite getSprite() {return spaceship_sprite;}
    sf::Sprite setSprite(sf::Sprite sprite) {spaceship_sprite = sprite;}
   

protected:
    volatile State _state;

    sf::Texture spaceship_up;
    sf::Texture spaceship_down;
    sf::Texture spaceship_left;
    sf::Texture spaceship_right;

    sf::Sprite spaceship_sprite;

    sf::Texture shot_tex;

    int _is_enemy;  // The value is 1 for Enemy Spaceship and 0 for Player Spaceship
                    // Not bool because it represents the Info Enum in class Shot
};

#endif
