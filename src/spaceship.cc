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
    std::cout << "Atirou!" << std::endl;
}

void SpaceShip::makeMoveUP() {
   if (_state == UP) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.y - 50 >= 10) {
            spaceship_sprite.move(0.0, -50.0);
        } else {
          spaceship_sprite.setPosition(position.x, 10.0);
        }
   } else {
        turnUp();
   }
}

void SpaceShip::makeMoveDOWN() {
   if (_state == DOWN) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.y + 50 <= 500) {
            spaceship_sprite.move(0.0, +50.0);
        } else {
            spaceship_sprite.setPosition(position.x, 500);
        }
   } else {
        turnDown();
   }
}

void SpaceShip::makeMoveLEFT() {
   if (_state == LEFT) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.x - 50 >= 10) {
          spaceship_sprite.move(-50.0, 0.0);
        } else {
            spaceship_sprite.setPosition(10.0, position.y);
        }
   } else {
        turnLeft();
   }
}

void SpaceShip::makeMoveRIGHT() {
   if (_state == RIGHT) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.x + 50 <= 515) {
          spaceship_sprite.move(+50.0, 0.0);
          } else {
            spaceship_sprite.setPosition(515, position.y);
        }
   } else {
        turnRight();
   }

}