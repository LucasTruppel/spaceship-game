#include "enemy_spaceship.h"
#include <iostream>
#include <cstdlib>

void EnemySpaceShip::run(){
    // TODO: Lógica da execução da Thread

}

void EnemySpaceShip::makeMove(){
    if (_strategy == RANDOM){
        srand(time(0));
        int movement = rand()%4;  //0 to 3, representing the four sides

        if (movement == _state) {
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