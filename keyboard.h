#ifndef keyboard_h
#define keyboard_h

#include <iostream>
#include <queue>
#include "thread.h"
#include "semaphore.h"
#include "window.h"

class Keyboard {
 public:
   Keyboard();

   ~Keyboard();

   // Loop where the thread receives a queue of keyboard keys
  static void run();

 public:

   // Semaphore for the keyboard key queue
   static Semaphore key_queue_sem; //----> Talvez tenha que ser um ponteiro

   // Queue that stores the keyboard keys
   static std::queue<int> key_queue;
};

#endif
