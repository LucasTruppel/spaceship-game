#include "player_spaceship.h"

PlayerSpaceShip::PlayerSpaceShip(int x, int y) {
     // Loading textures
     spaceship_up.loadFromFile("sprites/space_ships/space_ship1.png");
     spaceship_down.loadFromFile("sprites/space_ships/space_ship3.png");
     spaceship_left.loadFromFile("sprites/space_ships/space_ship2.png");
     spaceship_right.loadFromFile("sprites/space_ships/space_ship4.png");

     //Loading afterdamage textures
     after_damage_up.loadFromFile("sprites/space_ships/after_damage1.png");
     after_damage_down.loadFromFile("sprites/space_ships/after_damage3.png");
     after_damage_left.loadFromFile("sprites/space_ships/after_damage2.png");
     after_damage_right.loadFromFile("sprites/space_ships/space_ship4.png");



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

PlayerSpaceShip::~PlayerSpaceShip() {
     if (clock)
          delete clock;
}

void PlayerSpaceShip::run(PlayerSpaceShip* playerSpaceShip) {
     playerSpaceShip->clock = new sf::Clock();
     while (not GameHandler::quit_game) {   
          if (not GameHandler::pause_game and not GameHandler::end_game) {
               if (GameHandler::player_life == 0) {
                    GameHandler::end_game = true;
                    sf::Sprite sprite = playerSpaceShip->getSprite(); //Just for testing
                    sprite.setPosition(250, 250);
                    playerSpaceShip->setSprite(sprite);
                    //std::cout << "CHEGOU, X e Y: "<< playerSpaceShip->getSprite().getPosition().x << " " << playerSpaceShip->getSprite().getPosition().y << std::endl;
               }
               float current_time = playerSpaceShip->clock->getElapsedTime().asMilliseconds();
               float elapsed_time = current_time - playerSpaceShip->_last_tick;
               if (elapsed_time > 500) {
                    if (GameHandler::player_invincible) {
                         playerSpaceShip->setInvencibleTimer(playerSpaceShip->getInvencibleTimer() + elapsed_time);
                         if (playerSpaceShip->getInvencibleTimer() >= 2500) {  //2.5s de invencibilidade
                              playerSpaceShip->nonDamagedSprite();
                              GameHandler::player_invincible = false;
                              playerSpaceShip->resetTimer();
                         }
                    }
                    playerSpaceShip->_last_tick = current_time;
               }
          }
          Thread::yield();
     }
     Thread* thread = GameHandler::player_thread;
     GameHandler::player_thread = nullptr;
     thread->thread_exit(5);

}

void PlayerSpaceShip::makeMoveUP() {
     if (_state == UP) {
          sf::Vector2f position = spaceship_sprite.getPosition();
          if (position.y - _movement_pixels >= 10) {
               spaceship_sprite.move(0.0, - _movement_pixels);
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
          if (GameHandler::player_invincible) {
               _state = UP;
               damagedSprite();
          } else {
               turnUp();
          }
     }
}

void PlayerSpaceShip::makeMoveDOWN() {
     if (_state == DOWN) {
          sf::Vector2f position = spaceship_sprite.getPosition();
          if (position.y + _movement_pixels <= 500) {
               spaceship_sprite.move(0.0, + _movement_pixels);
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
          if (GameHandler::player_invincible) {
               _state = DOWN;
               damagedSprite();
          } else {
               turnDown();
          }
     }
}

void PlayerSpaceShip::makeMoveLEFT() {
     if (_state == LEFT) {
          sf::Vector2f position = spaceship_sprite.getPosition();
          if (position.x - _movement_pixels >= 10) {
               spaceship_sprite.move(-_movement_pixels, 0.0);
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
          if (GameHandler::player_invincible) {
               _state = LEFT;
               damagedSprite();
          } else {
               turnLeft();
          }
     }
}

void PlayerSpaceShip::makeMoveRIGHT() {
     if (_state == RIGHT) {
          sf::Vector2f position = spaceship_sprite.getPosition();
          if (position.x + _movement_pixels <= 515) {
               spaceship_sprite.move(+_movement_pixels, 0.0);
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
          if (GameHandler::player_invincible) {
               _state = RIGHT;
               damagedSprite();
          } else {
               turnRight();
          }
     }
}


void PlayerSpaceShip::receiveDamage() {
     if (GameHandler::player_life) {
          if (GameHandler::player_invincible == false) {
               GameHandler::player_life -= 1;
               GameHandler::player_invincible = true;  
               damagedSprite();       
          }   
     }
}


void PlayerSpaceShip::damagedSprite(){
     switch(_state) {
          case UP:
               spaceship_tex = after_damage_up;
               spaceship_sprite.setTexture(spaceship_tex);
               break;
          case DOWN:
               spaceship_tex = after_damage_down;
               spaceship_sprite.setTexture(spaceship_tex);
               break;
          case LEFT:
               spaceship_tex = after_damage_left;
               spaceship_sprite.setTexture(spaceship_tex);
               break;
          
          case RIGHT:
               spaceship_tex = after_damage_right;
               spaceship_sprite.setTexture(spaceship_tex);
               break;
     }

}

void PlayerSpaceShip::nonDamagedSprite() {
     switch(_state) {
          case UP:
               turnUp();
               break;
          case DOWN:
               turnDown();
               break;
          case LEFT:
               turnLeft();
               break;
          case RIGHT:
               turnRight();
               break;
     }
}