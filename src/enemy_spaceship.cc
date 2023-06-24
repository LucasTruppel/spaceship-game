#include "enemy_spaceship.h"

EnemySpaceShip::EnemySpaceShip(int x, int y, int random) {
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

    _random = random;

}

void EnemySpaceShip::run(EnemySpaceShip* enemySpaceShip){
    while (true) {
        enemySpaceShip->makeMove();
        Thread::yield();
    }
}

void EnemySpaceShip::makeMove() {
 
    if (_strategy == RANDOM) {
        srand(time(0) + static_cast<time_t>(_random * 100000));
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
        //TODO: Dummy Strategy
    }  
}

void EnemySpaceShip::setStrategy(int chosen_strategy) {    //0 for RANDOM, 1 for DUMMY
    if (chosen_strategy) {
        _strategy = DUMMY;
    } else {
        _strategy = RANDOM;
    }

}