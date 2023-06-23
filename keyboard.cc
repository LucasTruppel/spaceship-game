#include "keyboard.h"

// Declaração das variáveis estáticas
Semaphore key_list_sem = Semaphore();
std::list<int> Keyboard::key_list = {};

Keyboard::Keyboard() {

}

Keyboard::~Keyboard() {

}

void Keyboard::run() {
    key_list_sem.p();
    int key = key_list.back();
    key_list.pop_back();
    key_list_sem.v();
    std::cout << "Tecla na lista: " << key;
}