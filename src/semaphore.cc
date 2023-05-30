#include "semaphore.h"
#include <iostream>

__BEGIN_API

Semaphore::~Semaphore() {
    wakeup_all();
}

void Semaphore::p() {
    if (fdec(_count) < 1) {
        sleep();
    }
}

void Semaphore::v() {
    if (finc(_count) < 0) {
        wakeup();
    }
}

int Semaphore::finc(volatile int & number) {
    return CPU::finc(number);
}

int Semaphore::fdec(volatile int & number) {
    return CPU::fdec(number);
}

void Semaphore::sleep() {
    Thread* running = Thread::running();
    int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    running->link()->rank(now);
    _waiting.insert(running->link());
    running->sleep();
}

void Semaphore::wakeup() {
    Thread* waked = _waiting.remove()->object();
    waked->wakeup();
}

void Semaphore::wakeup_all() {
    while (!_waiting.empty()) {
        Thread* waked = _waiting.remove()->object();
        waked->wakeup();
    }
}

__END_API