#include "enemy_spaceship.h"

EnemySpaceShip::EnemySpaceShip(int x, int y) {
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

}

void EnemySpaceShip::run(EnemySpaceShip* enemySpaceShip){
    while (true) {
        Thread::yield();
    }
}

void EnemySpaceShip::makeMove(){
    if (_strategy == RANDOM){
        srand(time(0));
        int movement = rand()%4;  //0 to 3, representing the four sides

        if (movement == _state) {  //Nao atira, deve só se mover
            //TODO: shoot
        } else {
            //change side
            switch(movement) {
                case UP:
                    turnUp();
                    break;
                case DOWN:
                    turnDown();
                    break;
                case LEFT:
                    turnLeft();
                    break;
                default:         //case RIGHT
                    turnRight();
            }
        }


    } else {
        //TODO: Dummy Strategy
    }
    
}


void EnemySpaceShip::setStrategy(int chosen_strategy){    //0 for RANDOM, 1 for DUMMY
    if (chosen_strategy) {
        _strategy = DUMMY;
    } else {
        _strategy = RANDOM;
    }

}