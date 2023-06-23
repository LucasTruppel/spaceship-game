#ifndef keyboard_h
#define keyboard_h

#include <iostream>
#include <list>
#include "thread.h"
#include "semaphore.h"

class Keyboard {
 public:
    Keyboard();

    ~Keyboard();

    void run();

 public:
    static Semaphore *lista_sem;
    static std::list<int> keys;

 private:
    // Declaração dos métodos privados do Keyboard Handler

 private:
    // Declaração dos atributos do Keyboard Handler
    
};

#endif
