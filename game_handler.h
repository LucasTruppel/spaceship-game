#ifndef game_handler_h
#define game_handler_h

#include <iostream>
#include <list>
#include <queue>
#include "thread.h"
#include "semaphore.h"
#include "window.h"
#include "shot.h"
#include "spaceship.h"

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
    static std::list<SpaceShip>  spaceship_list;
};

#endif