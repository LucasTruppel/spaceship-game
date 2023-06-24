#ifndef collision_handler_h
#define collision_handler_h

#include <iostream>
#include <list>
#include <queue>
#include "thread.h"
#include "semaphore.h"
#include "window.h"
#include "shot.h"
#include "spaceship.h"

using namespace SOLUTION;

class CollisionHandler {
 public:
   CollisionHandler();
    
   ~CollisionHandler();

 public:
   // Method that verifies the bullet queue and the spaceship list to detect collision
   bool detect_collision();
};

#endif