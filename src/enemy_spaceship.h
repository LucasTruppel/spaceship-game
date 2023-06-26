#ifndef enemy_spaceship_h
#define enemy_spaceship_h

#include "thread.h"
#include "spaceship.h"
#include <iostream>
#include <cstdlib>
#include "game_handler.h"
#include "player_spaceship.h"
#include "constants.h"

using namespace SOLUTION;

class EnemySpaceShip : public SpaceShip {
 public:

    enum Strategy {
        RANDOM,
        DUMMY,
    };
    
    EnemySpaceShip(int x, int y, int random);
    ~EnemySpaceShip();


    static void run(EnemySpaceShip* enemySpaceShip);


    //Funcoes especificas da EnemySpaceShip
    void setStrategy(int chosen_strategy);   //0 for RANDOM, 1 for DUMMY
    void makeMove();

    void makeMoveUP();
    void makeMoveDOWN();
    void makeMoveLEFT();
    void makeMoveRIGHT();

    void receiveDamage();

    void revive();
    float getReviveTimer() {return _revive_timer;};
    void setReviveTimer(float new_timer) {_revive_timer = new_timer;}
    void resetTimer() {_revive_timer = 0;}

 private:
    Strategy _strategy;
    int _id;
    sf::Clock* clock;
    
    float _revive_timer = 0;
    static const int _movement_pixels = 25;
};

#endif