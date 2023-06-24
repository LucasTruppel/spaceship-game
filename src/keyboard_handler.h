#ifndef keyboard_handler_h
#define keyboard_handler_h

#include <iostream>
#include <queue>
#include "semaphore.h"
#include <SFML/Graphics.hpp>

using namespace SOLUTION;


class KeyboardHandler {
 public:
   KeyboardHandler();

   ~KeyboardHandler();

   // Loop where the thread receives a queue of keyboard keys
    void run();

   // Semaphore for the keyboard key queue
    Semaphore* key_queue_sem; //----> Talvez tenha que ser um ponteiro

   // Queue that stores the keyboard keys
    std::queue<int> key_queue;
};


#endif
