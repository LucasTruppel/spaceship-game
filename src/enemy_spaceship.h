#ifndef enemy_spaceship_h
#define enemy_spaceship_h

#include "thread.h"
#include "spaceship.h"
#include <iostream>
#include <cstdlib>
//#include "game_handler.h"

using namespace SOLUTION;

class EnemySpaceShip : public SpaceShip {
public:

    enum Strategy {
        RANDOM,
        DUMMY,
    };
    
    EnemySpaceShip(int x, int y, int random);
    //virtual ~EnemySpaceShip();


    static void run(EnemySpaceShip* enemySpaceShip);

    /*
    void makeMoveUP();
    void makeMoveDOWN();
    void makeMoveLEFT();
    void makeMoveRIGHT();
    */

    //Funcoes especificas da EnemySpaceShip
    void setStrategy(int chosen_strategy);   //0 for RANDOM, 1 for DUMMY
    void makeMove();



   

protected:
    volatile Strategy _strategy;
    int _random;
};

#endif