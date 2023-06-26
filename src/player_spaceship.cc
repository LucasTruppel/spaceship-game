#include "player_spaceship.h"

PlayerSpaceShip::PlayerSpaceShip(int x, int y) {
    // Loading textures
    spaceship_up.loadFromFile("sprites/space_ships/space_ship1.png");
    spaceship_down.loadFromFile("sprites/space_ships/space_ship3.png");
    spaceship_left.loadFromFile("sprites/space_ships/space_ship2.png");
    spaceship_right.loadFromFile("sprites/space_ships/space_ship4.png");

    // Initializing sprite atributes
    _state = UP;
    spaceship_tex = spaceship_up;
    spaceship_sprite.setTexture(spaceship_tex);
    spaceship_sprite.setPosition(x,y);
    spaceship_sprite.scale(0.5, 0.5);

     // Defining shot origin
    _is_enemy = 0;
    shot_tex.loadFromFile("sprites/space_ships/player_shot.png"); 
}

void PlayerSpaceShip::run(PlayerSpaceShip* playerSpaceShip) {
     playerSpaceShip->clock = new sf::Clock();
     while (true) {   
          if (GameHandler::quit_game == false and GameHandler::pause_game == false and GameHandler::end_game == false) {
               if (GameHandler::player_life == 0) {
                    GameHandler::end_game = true;
                    sf::Sprite sprite = playerSpaceShip->getSprite(); //Just for testing
                    sprite.setPosition(250, 250);
                    playerSpaceShip->setSprite(sprite);
                    //std::cout << "CHEGOU, X e Y: "<< playerSpaceShip->getSprite().getPosition().x << " " << playerSpaceShip->getSprite().getPosition().y << std::endl;
               }
               float elapsed_time = playerSpaceShip->clock->getElapsedTime().asMilliseconds();
               if (elapsed_time > 500) {
                    playerSpaceShip->setInvencibleTimer(playerSpaceShip->getInvencibleTimer() + elapsed_time);
                    if (playerSpaceShip->getInvencibleTimer() >= 2500) {  //2.5s de invencibilidade
                         GameHandler::player_invincible = false;
                         playerSpaceShip->resetTimer();
                    }
                    playerSpaceShip->clock->restart();
               }
          }
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
                         if (not GameHandler::player_invincible) {
                              receiveDamage();
                         }
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
                         if (not GameHandler::player_invincible) {
                              receiveDamage();
                         }
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
                         if (not GameHandler::player_invincible) {
                              receiveDamage();
                         }
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
                         if (not GameHandler::player_invincible) {
                              receiveDamage();
                         }
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


void PlayerSpaceShip::receiveDamage() {
     if (GameHandler::player_life) {
          if (GameHandler::player_invincible == false) {
               GameHandler::player_life -= 1;
               GameHandler::player_invincible = true;                
          }   
     }
}