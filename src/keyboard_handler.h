#ifndef keyboard_handler_h
#define keyboard_handler_h

#include <iostream>
#include <queue>
#include "thread.h"
#include "semaphore.h"
#include <SFML/Graphics.hpp>
#include <player_spaceship.h>

using namespace SOLUTION;


class KeyboardHandler {
 public:
   KeyboardHandler(PlayerSpaceShip* playerShip);

   ~KeyboardHandler();

   // Loop where the thread receives a queue of keyboard keys
   static void run(KeyboardHandler* keyboard_handler);

   // Semaphore for the keyboard key queue
    Semaphore* key_queue_sem;

   // Queue that stores the keyboard keys
    std::queue<int> key_queue;

 private:
    PlayerSpaceShip* playerSpaceShip;
};


#endif
