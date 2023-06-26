#ifndef keyboard_handler_h
#define keyboard_handler_h

#include <iostream>
#include <queue>
#include "thread.h"
#include "semaphore.h"
#include <SFML/Graphics.hpp>
#include "player_spaceship.h"
#include "enemy_spaceship.h"
#include "game_handler.h"


using namespace SOLUTION;


class KeyboardHandler {
 public:
   ~KeyboardHandler();

   // Loop where the thread receives a queue of keyboard keys
   static void run(KeyboardHandler* keyboard_handler);

 private:

   // Clock for the keyboard key queue
   sf::Clock* clock;

   int last_movement = 0;
   int last_shot = 0;
   static int const movement_min_delta = 300;
   static int const shot_min_delta = 750;
};


#endif
