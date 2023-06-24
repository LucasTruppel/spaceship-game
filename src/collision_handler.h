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
   bool detect_player_collision(PlayerSpaceShip* player, EnemySpaceShip* enemy);
   bool detect_enemy_collision(EnemySpaceShip* enemy01, EnemySpaceShip* enemy02);
};

#endif