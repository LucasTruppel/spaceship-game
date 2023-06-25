#ifndef shot_handler_h
#define shot_handler_h

#include <list>
#include "shot.h"
#include "enemy_spaceship.h"
#include "player_spaceship.h"
#include "spaceship.h"
#include "game_handler.h"
#include "thread.h"
#include "traits.h"

__USING_API

// Spaceships poem os Shots na shot_list do GameHandler.
// ShotHandler tem uma referencia a essa lista, assim ele pode ir modificando ela.

class ShotHandler {

 public:
   ShotHandler();
   ~ShotHandler();

   static void run(ShotHandler* shotHandler);
   void moveShots(); 
   void verifyColisionShotShot();
   void verifyColisionShotSpaceship();

 private:
    sf::Clock* clock;
};

#endif