#ifndef enemy_spaceship_h
#define enemy_spaceship_h

#include "thread.h"
#include "spaceship.h"
#include <iostream>
#include <cstdlib>

using namespace SOLUTION;

class EnemySpaceShip : public SpaceShip {
public:

    enum Strategy {
        RANDOM,
        DUMMY,
    };
    
    EnemySpaceShip(int x, int y);
    //virtual ~EnemySpaceShip();


    static void run(EnemySpaceShip* enemySpaceShip);

    //Funcoes especificas da EnemySpaceShip
    void setStrategy(int chosen_strategy);   //0 for RANDOM, 1 for DUMMY
    void makeMove();

   

protected:
    volatile Strategy _strategy;
};

#endif