#include <iostream>
#include "window.h"
#include "spaceship.h"

SpaceShip::SpaceShip() {
    spaceship_up.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
    spaceship_down.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
    spaceship_left.loadFromFile("sprites/space_ships/enemy_space_ship1.png")
    spaceship_right.loadFromFile("sprites/space_ships/enemy_space_ship1.png")
}
