#include "enemy_spaceship.h"

EnemySpaceShip::EnemySpaceShip(int x, int y, int id) {
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
    spaceship_sprite.scale(0.5, 0.5);

    _id = id;

    _is_enemy = 1;

    shot_tex.loadFromFile("sprites/space_ships/enemy_shot.png");
}

EnemySpaceShip::~EnemySpaceShip() {
    delete clock;
}

void EnemySpaceShip::run(EnemySpaceShip* enemySpaceShip) {
    enemySpaceShip->clock = new sf::Clock();
    while (true) {
        if (enemySpaceShip->clock->getElapsedTime().asMilliseconds() > 500) {
            if (enemySpaceShip->getState() != DEAD) {
                enemySpaceShip->makeMove();     
            }
            enemySpaceShip->clock->restart();
        }
        Thread::yield();
    }
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

        if ((rand() % 10) < 100) {   // change to 100 to 3
            shoot();
        } else if (abs(deltay) < abs(deltax)) {
            if (abs(deltax) > 100) {
                if (deltax > 0) {
                    makeMoveRIGHT();
                } else {
                    makeMoveLEFT();
                }
            }
        } else {
            if (abs(deltay) > 100) {
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
        if (position.y - 50 >= 10) {
            spaceship_sprite.move(0.0, -50.0);
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
        if (position.y + 50 <= 500) {
            spaceship_sprite.move(0.0, +50.0);
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
        if (position.x - 50 >= 10) {
            spaceship_sprite.move(-50.0, 0.0);
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
        if (position.x + 50 <= 515) {
            spaceship_sprite.move(+50.0, 0.0);
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
            }
        } else {
            spaceship_sprite.setPosition(515, position.y);
        }
    } else {
        turnRight();
    }
}

void EnemySpaceShip::revive() {
    turnUp();    //Not dead anymore.
    spaceship_sprite.setPosition(100 * _id, 700);
    //voltar a nave para o jogo em uma posicao valida
}

void EnemySpaceShip::receiveDamage() {
    _state = DEAD;
    spaceship_sprite.setPosition(100 * _id, 700);
}

