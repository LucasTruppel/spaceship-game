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

 private:

   // Clock for the keyboard key queue
   sf::Clock* clock;

   // Player Spaceship reference
   PlayerSpaceShip* playerSpaceShip;

   int last_movement = 0;
   int last_shot = 0;
};


#endif
