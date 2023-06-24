#include "player_spaceship.h"

PlayerSpaceShip::PlayerSpaceShip(int x, int y) {
    //Carrega as texturas
    spaceship_up.loadFromFile("sprites/space_ships/space_ship1.png");
    spaceship_down.loadFromFile("sprites/space_ships/space_ship3.png");
    spaceship_left.loadFromFile("sprites/space_ships/space_ship2.png");
    spaceship_right.loadFromFile("sprites/space_ships/space_ship4.png");

    //Inicializa atributos do sprite
    _state = UP;
    spaceship_tex = spaceship_up;
    spaceship_sprite.setTexture(spaceship_tex);
    spaceship_sprite.setPosition(x,y);
    spaceship_sprite.scale(0.5, 0.5);
}

void PlayerSpaceShip::run(PlayerSpaceShip* playerSpaceShip) {
    while (true) {
        Thread::yield();
    }
}

