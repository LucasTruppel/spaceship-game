#include <iostream>
#include "window.h"
#include "spaceship.h"

SpaceShip::SpaceShip(int x, int y) {
    //Carrega as texturas
    spaceship_up.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
    spaceship_down.loadFromFile("sprites/space_ships/enemy_space_ship3.png");
    spaceship_left.loadFromFile("sprites/space_ships/enemy_space_ship2.png");
    spaceship_right.loadFromFile("sprites/space_ships/enemy_space_ship4.png");

    //Inicializa atributos do sprite
    _state = UP;
    spaceship_tex = spaceship_up;
    spaceship_sprite.setTexture(spaceship_tex);
    spaceship_sprite.setPosition(x,y);
    spaceship_sprite.scale(-0.5, -0.5);

}

SpaceShip::~SpaceShip() {
}

void SpaceShip::turnUp(){
    _state = UP;
    spaceship_tex = spaceship_up;
    spaceship_sprite.setTexture(spaceship_tex);
    spaceship_sprite.scale(-0.5, -0.5);
}

void SpaceShip::turnDown(){
    _state = DOWN;
    spaceship_tex = spaceship_down;
    spaceship_sprite.setTexture(spaceship_tex);
    spaceship_sprite.scale(-0.5, -0.5);
}

void SpaceShip::turnLeft(){
    _state = LEFT;
    spaceship_tex = spaceship_left;
    spaceship_sprite.setTexture(spaceship_tex);
    spaceship_sprite.scale(-0.5, -0.5);
}

void SpaceShip::turnRight(){
    _state = RIGHT;
    spaceship_tex = spaceship_right;
    spaceship_sprite.setTexture(spaceship_tex);
    spaceship_sprite.scale(-0.5, -0.5);
}

void SpaceShip::shoot(){
    ;
}