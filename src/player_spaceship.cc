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

    _is_enemy = 0;

    //shot_tex.loadFromFile("../sprites/space_ships/player_shot.png"); 
}

void PlayerSpaceShip::run(PlayerSpaceShip* playerSpaceShip) {
    while (true) {
        Thread::yield();
    }
}

void PlayerSpaceShip::makeMoveUP() {
   if (_state == UP) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.y - 50 >= 10) {
            spaceship_sprite.move(0.0, -50.0);
            for (int i = 0; i < 4; i++) {
               sf::Sprite enemy_sprite = GameHandler::spaceship_list[i]->getSprite();
               if (getSprite().getGlobalBounds().intersects(enemy_sprite.getGlobalBounds())) {
                    spaceship_sprite.setPosition(position.x, enemy_sprite.getPosition().y+50);
                    break;
               }
          }
        } else {
          spaceship_sprite.setPosition(position.x, 10.0);
        }
   } else {
        turnUp();
   }
}

void PlayerSpaceShip::makeMoveDOWN() {
   if (_state == DOWN) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.y + 50 <= 500) {
            spaceship_sprite.move(0.0, +50.0);
            for (int i = 0; i < 4; i++) {
               sf::Sprite enemy_sprite = GameHandler::spaceship_list[i]->getSprite();
               if (getSprite().getGlobalBounds().intersects(enemy_sprite.getGlobalBounds())) {
                    spaceship_sprite.setPosition(position.x, enemy_sprite.getPosition().y-50);
                    break;
               }
          }
        } else {
            spaceship_sprite.setPosition(position.x, 500);
        }
   } else {
        turnDown();
   }
}

void PlayerSpaceShip::makeMoveLEFT() {
   if (_state == LEFT) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.x - 50 >= 10) {
          spaceship_sprite.move(-50.0, 0.0);
          for (int i = 0; i < 4; i++) {
               sf::Sprite enemy_sprite = GameHandler::spaceship_list[i]->getSprite();
               if (getSprite().getGlobalBounds().intersects(enemy_sprite.getGlobalBounds())) {
                    spaceship_sprite.setPosition(enemy_sprite.getPosition().x+50, position.y);
                    break;
               }
          }
        } else {
            spaceship_sprite.setPosition(10.0, position.y);
        }
   } else {
        turnLeft();
   }
}

void PlayerSpaceShip::makeMoveRIGHT() {
   if (_state == RIGHT) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.x + 50 <= 515) {
          spaceship_sprite.move(+50.0, 0.0);
          for (int i = 0; i < 4; i++) {
               sf::Sprite enemy_sprite = GameHandler::spaceship_list[i]->getSprite();
               if (getSprite().getGlobalBounds().intersects(enemy_sprite.getGlobalBounds())) {
                    spaceship_sprite.setPosition(enemy_sprite.getPosition().x-50, position.y);
                    break;
               }
          }
          } else {
            spaceship_sprite.setPosition(515, position.y);
        }
   } else {
        turnRight();
   }

}


