#ifndef game_handler_h
#define game_handler_h

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

class EnemySpaceShip;
class PlayerSpaceShip;
class Shot;

class GameHandler {
 public:
   ~GameHandler();

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
    
   // The keyboard R key was pressed and the Game will reset
   static bool reset_game;

  // The player died
   static bool end_game;

};

#endif