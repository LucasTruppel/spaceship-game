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

    // List that contains all shots
    static std::list<Shot*> shot_list;

    // List that contains all Spaceships
    static EnemySpaceShip* spaceship_list[4];

   // Player position
    static PlayerSpaceShip* player_ship;
};

#endif