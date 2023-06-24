#include "spaceship.h"


void SpaceShip::turnUp(){
    _state = UP;
    spaceship_tex = spaceship_up;
    spaceship_sprite.setTexture(spaceship_tex);
}

void SpaceShip::turnDown(){
    _state = DOWN;
    spaceship_tex = spaceship_down;
    spaceship_sprite.setTexture(spaceship_tex);
}

void SpaceShip::turnLeft(){
    _state = LEFT;
    spaceship_tex = spaceship_left;
    spaceship_sprite.setTexture(spaceship_tex);
}

void SpaceShip::turnRight(){
    _state = RIGHT;
    spaceship_tex = spaceship_right;
    spaceship_sprite.setTexture(spaceship_tex);
}

void SpaceShip::shoot(){
    ;
}