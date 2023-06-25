#ifndef collision_handler_h
#define collision_handler_h

#include <iostream>
#include <list>
#include <queue>
#include "thread.h"
#include "shot.h"
#include "player_spaceship.h"
#include "enemy_spaceship.h"

using namespace SOLUTION;

class CollisionHandler {
 public:
   CollisionHandler();
    
   ~CollisionHandler();

 public:
   // Method that verifies the bullet queue and the spaceship list to detect collision
   bool detect_vertical_collision(PlayerSpaceShip* player, EnemySpaceShip* enemy[4]);
   bool detect_horizontal_collision(PlayerSpaceShip* player, EnemySpaceShip* enemy[4]);
};

#endif