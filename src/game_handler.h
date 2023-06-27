#ifndef game_handler_h
#define game_handler_h

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <traits.h>
#include "thread.h"
#include "semaphore.h"

__USING_API

class EnemySpaceShip;
class PlayerSpaceShip;
class Shot;

class GameHandler {
 public:
   ~GameHandler();
  static void reset();

 public:

   // Player Score that appears at the side of the screen
   static int score;

   // Enemy spaceship speed
   static int speed;

   // Player Life that appears at the side of the screen
   static int player_life;

   // Is player invincible
   static bool player_invincible;

   // List that contains all shots
   static std::list<Shot*> shot_list;

   // List that contains all Spaceships
   static EnemySpaceShip* spaceship_list[4];

   // Player position
   static PlayerSpaceShip* player_ship;

   // The keyboard Q key was pressed and the Game will close
   static bool quit_game;

   // The keyboard P key was pressed and the Game will pause
   static bool pause_game;

  // The player died
   static bool end_game;

  // Threads
   static Thread* player_thread;
   static Thread* enemy_thread[4];
   static Thread* shot_handler_thread;
   static Thread* keyboard_handler_thread;

   // Semaphores
   static Semaphore* shot_list_sem;
   static Semaphore* quit_game_sem;
   static Semaphore* score_sem;
   static Semaphore* pause_game_sem;
   static Semaphore* end_game_sem;
   static Semaphore* player_sem;
   static Semaphore* enemy_sem[4];
  

};

#endif