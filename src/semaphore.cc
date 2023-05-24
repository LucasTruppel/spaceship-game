#include "semaphore.h"
#include <iostream>

__BEGIN_API

Semaphore::~Semaphore() {
    // Destrutor.
}

void Semaphore::p() {
    if (_count > 0) {
        fdec(_count);
    } else {
        sleep();
    }
}

void Semaphore::v() {
    if (_waiting.empty()) {
        finc(_count);
    } else {
        wakeup();
    }
}

int Semaphore::finc(volatile int & number) {
    // asm ("lock xadd $1, %2");
    // Chamar no CPU.
}

int Semaphore::fdec(volatile int & number) {
    // asm ("lock xadd $0, %2");
    // Chamar no CPU.
}

void Semaphore::sleep() {
    Thread* running = Thread::running();
    // Adiciona na cabeça da fila.
    // Chama running->Thread::sleep();
}

void Semaphore::wakeup() {
    Thread* running = Thread::running();
    // Retira da cabeça da fila.
    // Chama running->Thread::wakeup();
}

void Semaphore::wakeup_all() {
    while (!_waiting.empty()) {
        // Chama wakeup() para cada thread.
    }
}

__END_API