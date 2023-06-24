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

void PlayerSpaceShip::makeMoveUP() {
   if (_state == UP) {
        //if vendo se esta no mapa
        spaceship_sprite.move(0.0, -50.0);
   } else {
        turnUp();
   }
}
void PlayerSpaceShip::makeMoveDOWN() {
   if (_state == DOWN) {
        //if vendo se esta no mapa
        spaceship_sprite.move(0.0, +50.0);
   } else {
        turnDown();
   }
}
void PlayerSpaceShip::makeMoveLEFT() {
   if (_state == LEFT) {
        //if vendo se esta no mapa
        spaceship_sprite.move(-50.0, 0.0);
   } else {
        turnLeft();
   }
}
void PlayerSpaceShip::makeMoveRIGHT() {
   if (_state == RIGHT) {
        //if vendo se esta no mapa
        spaceship_sprite.move(+50.0, 0.0);
   } else {
        turnRight();
   }
}