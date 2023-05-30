#include "semaphore.h"
#include <iostream>

__BEGIN_API

Semaphore::~Semaphore() {
    wakeup_all();
}

void Semaphore::p() {
    db<Semaphore>(TRC) << "Semaphore::p() chamado\n";

    if (fdec(_count) < 1) {
        sleep();
    }
}

void Semaphore::v() {
    db<Semaphore>(TRC) << "Semaphore::v() chamado\n";

    if (finc(_count) < 0) {
        wakeup();
    }
}

int Semaphore::finc(volatile int & number) {
    db<Semaphore>(TRC) << "Semaphore::finc() chamado\n";

    return CPU::finc(number);
}

int Semaphore::fdec(volatile int & number) {
    db<Semaphore>(TRC) << "Semaphore::fdec() chamado\n";

    return CPU::fdec(number);
}

void Semaphore::sleep() {
    Thread* running = Thread::running();
    running->Thread::sleep();
    _waiting.insert_tail(running->link());
    Thread::yield();
}

void Semaphore::wakeup() {
    if (!_waiting.empty()) {
        Thread *next = _waiting.remove_head()->object();
        next->Thread::wakeup();
        Thread::yield();
    }
}

void Semaphore::wakeup_all() {
    while (!_waiting.empty()) {
        Thread *next = _waiting.remove_head()->object();
        next->Thread::wakeup();
    }
    Thread::yield();
}

__END_API