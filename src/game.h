#ifndef game_h
#define game_h

#include <iostream>
#include "window.h"

class Game
{
    public:
        Game(){
        }
        ~Game(){}

        static void run(void * name) {
            Window window;
            window.run();
        }

    private:
       ; //testando
};




#endif