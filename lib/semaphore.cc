#include "semaphore.h"
#include <iostream>

__BEGIN_API

Semaphore::~Semaphore() {
    db<Semaphore>(TRC) << "~Semaphore() chamado\n";
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
    db<Semaphore>(TRC) << "Semaphore::finc(volatile int & number) chamadon";
    return CPU::finc(number);
}

int Semaphore::fdec(volatile int & number) {
    db<Semaphore>(TRC) << "Semaphore::fdec(volatile int & number) chamado\n";
    return CPU::fdec(number);
}

void Semaphore::sleep() {
    db<Semaphore>(TRC) << "Semaphore::sleep() chamado\n";
    Thread* running = Thread::running();
    running->sleep(&_waiting);
}

void Semaphore::wakeup() {
    db<Semaphore>(TRC) << "Semaphore::wakeup() chamado\n";
    if (!_waiting.empty()) {
        Thread* waked = _waiting.remove()->object();
        waked->wakeup();
    }
}

void Semaphore::wakeup_all() {
    db<Semaphore>(TRC) << "Semaphore::wakeup_all() chamado\n";
    while (!_waiting.empty()) {
        Thread* waked = _waiting.remove()->object();
        waked->wakeup();
    }
}

__END_API