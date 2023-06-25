#ifndef game_handler_h
#define game_handler_h

#include <iostream>
#include <list>
#include <queue>
#include <SFML/Graphics.hpp>
#include "shot.h"
//#include "enemy_spaceship.h"
#include "player_spaceship.h"


class GameHandler {
 public:
    GameHandler();
    
    ~GameHandler();

 public:

    // Player Score that appears at the side of the screen
    static int score;

    // Enemy spaceship velocity
    static int velocity;

    // Player Life that appears at the side of the screen
    static int player_life;

    static bool player_invincible;

    // Queue that contains all shots
    static std::queue<Shot> shot_queue;

    // List that contains all Spaceships
    //static std::list<EnemySpaceShip>  spaceship_list;

   // Player position
    static PlayerSpaceShip* player_ship;
};

#endif