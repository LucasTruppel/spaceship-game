#include "keyboard.h"

// Declaração das variáveis estáticas
Semaphore key_list_sem;
std::list<int> Keyboard::key_list = {};

Keyboard::Keyboard() {
    key_list_sem = new Semaphore();
    new (&key_list_sem) Keyboard();
}

Keyboard::~Keyboard() {

}

void Keyboard::run() {
    key_list.pop_back();
}