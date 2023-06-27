#include "player_spaceship.h"

PlayerSpaceShip::PlayerSpaceShip(int x, int y) {
     // Loading textures
     not_damaged_up.loadFromFile("sprites/space_ships/space_ship1.png");
     not_damaged_down.loadFromFile("sprites/space_ships/space_ship3.png");
     not_damaged_left.loadFromFile("sprites/space_ships/space_ship2.png");
     not_damaged_right.loadFromFile("sprites/space_ships/space_ship4.png");

     //Loading afterdamage textures
     damaged_up.loadFromFile("sprites/space_ships/after_damage1.png");
     damaged_down.loadFromFile("sprites/space_ships/after_damage3.png");
     damaged_left.loadFromFile("sprites/space_ships/after_damage2.png");
     damaged_right.loadFromFile("sprites/space_ships/after_damage4.png");


     // Initializing current texture
     spaceship_up = not_damaged_up;
     spaceship_down = not_damaged_down;
     spaceship_left = not_damaged_left;
     spaceship_right = not_damaged_right;
     

    // Initializing sprite atributes
    _state = UP;
    spaceship_sprite.setTexture(spaceship_up);
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
                    GameHandler::end_game_sem->p();
                    GameHandler::end_game = true;
                    GameHandler::end_game_sem->v();
                    playerSpaceShip->nonDamagedSprite();
                    sf::Sprite sprite = playerSpaceShip->getSprite();
                    sprite.setPosition(250, 250);
                    playerSpaceShip->setSprite(sprite);
               }
               float current_time = playerSpaceShip->clock->getElapsedTime().asMilliseconds();
               float elapsed_time = current_time - playerSpaceShip->_last_tick;
               if (elapsed_time > 500) {
                    if (GameHandler::player_invincible) {
                         if (current_time - playerSpaceShip->getInvencibleTimer() >= 2500) {  //2.5s de invencibilidade
                              GameHandler::player_invincible = false;
                              playerSpaceShip->nonDamagedSprite();
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
          turnUp();
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
          turnDown();
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
          turnLeft();
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
          turnRight();
     }
}


void PlayerSpaceShip::receiveDamage() {
     if (GameHandler::player_life) {
          if (GameHandler::player_invincible == false) {
               GameHandler::player_life -= 1;
               GameHandler::player_invincible = true;
               _invencible_timer = clock->getElapsedTime().asMilliseconds();
               damagedSprite();       
          }   
     }
}


void PlayerSpaceShip::damagedSprite(){
     spaceship_up = damaged_up;
     spaceship_down = damaged_down;
     spaceship_left = damaged_left;
     spaceship_right = damaged_right;
     switch(_state) {
          case UP:
               spaceship_sprite.setTexture(spaceship_up);
               break;
          case DOWN:
               spaceship_sprite.setTexture(spaceship_down);
               break;
          case LEFT:
               spaceship_sprite.setTexture(spaceship_left);
               break;
          case RIGHT:
               spaceship_sprite.setTexture(spaceship_right);
     }
}

void PlayerSpaceShip::nonDamagedSprite() {
     spaceship_up = not_damaged_up;
     spaceship_down = not_damaged_down;
     spaceship_left = not_damaged_left;
     spaceship_right = not_damaged_right;
     switch(_state) { 
          case UP:
               spaceship_sprite.setTexture(spaceship_up);
               break;
          case DOWN:
               spaceship_sprite.setTexture(spaceship_down);
               break;
          case LEFT:
               spaceship_sprite.setTexture(spaceship_left);
               break;
          case RIGHT:
               spaceship_sprite.setTexture(spaceship_right);
     }
}

