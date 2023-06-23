#ifndef game_handler_h
#define game_handler_h

#include <iostream>
#include "thread.h"
#include "semaphore.h"

class GameHandler {
 public:
    GameHandler();
    
    ~GameHandler();

    // Loop that update all game variables
    static void run();

 public:

    // Player Score that appears at the side of the screen
    int static score;

    // Enemy spaceship velocity
    int static velocity;

    // Player Life that appears at the side of the screen
    int static player_life;
};

#endif