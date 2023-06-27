#include "enemy_spaceship.h"

EnemySpaceShip::EnemySpaceShip(int x, int y, int id) {
    //Carrega as texturas
    spaceship_up.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
    spaceship_down.loadFromFile("sprites/space_ships/enemy_space_ship3.png");
    spaceship_left.loadFromFile("sprites/space_ships/enemy_space_ship2.png");
    spaceship_right.loadFromFile("sprites/space_ships/enemy_space_ship4.png");

    //Inicializa atributos do sprite
    _state = UP;
    spaceship_sprite.setTexture(spaceship_up);
    spaceship_sprite.setPosition(x,y);
    spaceship_sprite.scale(0.5, 0.5);

    _id = id;

    _is_enemy = 1;

    shot_tex.loadFromFile("sprites/space_ships/enemy_shot.png");
}

EnemySpaceShip::~EnemySpaceShip() {
    if (clock)
        delete clock;
}

void EnemySpaceShip::run(EnemySpaceShip* enemySpaceShip) {
    enemySpaceShip->clock = new sf::Clock();
    while (not GameHandler::quit_game) {
        if (GameHandler::quit_game == false and GameHandler::pause_game == false and GameHandler::end_game == false) {
            float elapsed_time = enemySpaceShip->clock->getElapsedTime().asMilliseconds();
            float speed_multiplier;
            switch(GameHandler::speed) {
                case 1:
                    speed_multiplier = 2.5;
                    break;
                case 2:
                    speed_multiplier = 1.7;
                    break;
                default:
                    speed_multiplier = 1;
            }

            if (elapsed_time > 500/2 * speed_multiplier) {
                if (enemySpaceShip->getState() != DEAD) {
                    enemySpaceShip->makeMove();     
                } else {
                    enemySpaceShip->setReviveTimer(enemySpaceShip->getReviveTimer() + elapsed_time);
                    if (enemySpaceShip->getReviveTimer() >= 2000) {
                        enemySpaceShip->revive();
                        enemySpaceShip->resetTimer();
                    }
                }
                enemySpaceShip->clock->restart();
            }
        }
        Thread::yield();
    }
    Thread* thread = GameHandler::enemy_thread[enemySpaceShip->_id];
    GameHandler::enemy_thread[enemySpaceShip->_id] = nullptr;
    thread->thread_exit(enemySpaceShip->_id);
}

void EnemySpaceShip::makeMove() {
    srand(time(0) + static_cast<time_t>(_id * 100000));
    if (_strategy == RANDOM) {
        int movement = rand() % 5;  //0 to 4, representing the four sides (4 representa a ação de atirar)
        switch(movement) {
            case UP:
                makeMoveUP();
                break;
            case DOWN:
                makeMoveDOWN();
                break;
            case LEFT:
                makeMoveLEFT();
                break;
            case RIGHT:
                makeMoveRIGHT();
                break;
            default:
                shoot();
               
        }
    } else {
        sf::Vector2f player_position = GameHandler::player_ship->getSprite().getPosition();
        sf::Vector2f enemy_position = spaceship_sprite.getPosition();
        float deltax = abs(player_position.x) - abs(enemy_position.x);
        float deltay = abs(player_position.y) - abs(enemy_position.y);

        if ((rand() % 10) < 3) {   // 30% of shooting change 
            shoot();
        } else if (abs(deltay) < abs(deltax)) {
            if (abs(deltax) > 75) {
                if (deltax > 0) {
                    makeMoveRIGHT();
                } else {
                    makeMoveLEFT();
                }
            } 
        } else {
            if (abs(deltay) > 75) {
                if (deltay > 0) {
                    makeMoveDOWN();
                } else {
                    makeMoveUP();
                }
            }
        }
    }  
}

void EnemySpaceShip::setStrategy(int chosen_strategy) {    //0 for RANDOM, 1 for DUMMY
    if (chosen_strategy) {
        _strategy = DUMMY;
    } else {
        _strategy = RANDOM;
    }

}

void EnemySpaceShip::makeMoveUP() {
   if (_state == UP) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.y - _movement_pixels >= 10) {
            spaceship_sprite.move(0.0, - _movement_pixels);
            for (int i = 0; i < 4; i++) { 
               sf::Sprite enemy_sprite = GameHandler::spaceship_list[i]->getSprite();
               if (i != _id && getSprite().getGlobalBounds().intersects(enemy_sprite.getGlobalBounds())) {
                    spaceship_sprite.setPosition(position.x, position.y);
                    break;
               }
            }
            sf::Sprite player_sprite = GameHandler::player_ship->getSprite();
            if (getSprite().getGlobalBounds().intersects(player_sprite.getGlobalBounds())) {
                spaceship_sprite.setPosition(position.x, position.y);
                if(not GameHandler::player_invincible) {
                    GameHandler::player_ship->receiveDamage();
                }
            }
        } else {
          spaceship_sprite.setPosition(position.x, 10.0);
        }
   } else {
        turnUp();
   }
}

void EnemySpaceShip::makeMoveDOWN() {
   if (_state == DOWN) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.y + _movement_pixels <= 500) {
            spaceship_sprite.move(0.0, _movement_pixels);
            for (int i = 0; i < 4; i++) {
                sf::Sprite enemy_sprite = GameHandler::spaceship_list[i]->getSprite();
                if (i != _id && getSprite().getGlobalBounds().intersects(enemy_sprite.getGlobalBounds())) {
                    spaceship_sprite.setPosition(position.x, position.y);
                    break;
                }
            }
            sf::Sprite player_sprite = GameHandler::player_ship->getSprite();
            if (getSprite().getGlobalBounds().intersects(player_sprite.getGlobalBounds())) {
                spaceship_sprite.setPosition(position.x, position.y);
                if(not GameHandler::player_invincible) {
                    GameHandler::player_ship->receiveDamage();
                }
            }
        } else {
            spaceship_sprite.setPosition(position.x, 500); 
        }
   } else {
        turnDown();
   }
}

void EnemySpaceShip::makeMoveLEFT() {
   if (_state == LEFT) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.x - _movement_pixels >= 10) {
            spaceship_sprite.move(-_movement_pixels, 0.0);
            for (int i = 0; i < 4; i++) {
                sf::Sprite enemy_sprite = GameHandler::spaceship_list[i]->getSprite();
                if (i != _id && getSprite().getGlobalBounds().intersects(enemy_sprite.getGlobalBounds())) {
                    spaceship_sprite.setPosition(position.x, position.y);
                    break;
                }
            }
            sf::Sprite player_sprite = GameHandler::player_ship->getSprite();
            if (getSprite().getGlobalBounds().intersects(player_sprite.getGlobalBounds())) {
                spaceship_sprite.setPosition(position.x, position.y);
                if(not GameHandler::player_invincible) {
                    GameHandler::player_ship->receiveDamage();
                }
            }
        } else {
            spaceship_sprite.setPosition(10.0, position.y);
        }
   } else {
        turnLeft();
   }
}

void EnemySpaceShip::makeMoveRIGHT() {
    if (_state == RIGHT) {
        sf::Vector2f position = spaceship_sprite.getPosition();
        if (position.x + _movement_pixels <= 515) {
            spaceship_sprite.move(_movement_pixels, 0.0);
            for (int i = 0; i < 4; i++) {
                sf::Sprite enemy_sprite = GameHandler::spaceship_list[i]->getSprite();
                if (i != _id && getSprite().getGlobalBounds().intersects(enemy_sprite.getGlobalBounds())) {
                    spaceship_sprite.setPosition(position.x, position.y);
                    break;
               }
            }
            sf::Sprite player_sprite = GameHandler::player_ship->getSprite();
            if (getSprite().getGlobalBounds().intersects(player_sprite.getGlobalBounds())) {
                spaceship_sprite.setPosition(position.x, position.y);
                if(not GameHandler::player_invincible) {
                    GameHandler::player_ship->receiveDamage();
                }
            }
        } else {
            spaceship_sprite.setPosition(515, position.y);
        }
    } else {
        turnRight();
    }
}

void EnemySpaceShip::revive() {
    turnUp();   // Not dead anymore
    switch(_id) {
            case 0:
                spaceship_sprite.setPosition(Constants::ENEMY_INITIAL_X[0], Constants::ENEMY_INITIAL_Y[0]);  // Upper Right start position
                break;
            case 1:
                spaceship_sprite.setPosition(Constants::ENEMY_INITIAL_X[1], Constants::ENEMY_INITIAL_Y[1]); // Upper Left start position
                break;
            case 2:
                spaceship_sprite.setPosition(Constants::ENEMY_INITIAL_X[2], Constants::ENEMY_INITIAL_Y[2]); // Lower Right start position
                break;
            default:
                spaceship_sprite.setPosition(Constants::ENEMY_INITIAL_X[3], Constants::ENEMY_INITIAL_Y[3]);// Lower Left start position
    }
    if (spaceship_sprite.getGlobalBounds().intersects(GameHandler::player_ship->getSprite().getGlobalBounds())) {
        spaceship_sprite.setPosition(250, 250);
    }
}

void EnemySpaceShip::receiveDamage() {
    _state = DEAD;
    spaceship_sprite.setPosition(100 * _id, 700);
    GameHandler::score_sem->p();
    GameHandler::score += 100;
    GameHandler::score_sem->v();
    if (GameHandler::score == 400 or GameHandler::score == 800) {
        GameHandler::speed += 1;
    }
}
 
