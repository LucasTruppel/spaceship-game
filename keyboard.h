#ifndef keyboard_h
#define keyboard_h

#include <iostream>
#include <list>
#include "window.h"
#include "thread.h"
#include "semaphore.h"

class Keyboard {
 public:
    Keyboard();

    ~Keyboard();

    void run();

 public:
    static Semaphore key_list_sem;
    static std::list<int> key_list;

 private:
    // Declaração dos métodos privados do Keyboard Handler

 private:
    // Declaração dos atributos do Keyboard Handler
    
};

#endif
