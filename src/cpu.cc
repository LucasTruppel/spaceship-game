#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    db<CPU>(TRC) << "CPU::Context::save() chamado\n";
    getcontext(&_context);
}

void CPU::Context::load()
{
    db<CPU>(TRC) << "CPU::Context::load() chamado\n";
    setcontext(&_context);
}

CPU::Context::~Context()
{
    if (_stack) {
        db<CPU>(INF) << "Stack desalocada no destrutor de Context\n";
        delete _stack;
    }
}

int CPU::switch_context(Context *from, Context *to)
{
    db<CPU>(TRC) << "CPU::switch_context(Context *from, Context *to) chamado\n";
    return swapcontext(&from->_context, &to->_context); 
}

int CPU::finc(volatile int & number) {
    db<CPU>(TRC) << "CPU::finc(volatile int & number)\n";
    int inc = 1;
    asm("lock xadd %0, %2" : "=a"  (inc) : "a" (inc) , "m" (number));
    db<CPU>(INF) << "Valor do semáforo de " << inc << " para " << number << "\n";
    return inc;
}

int CPU::fdec(volatile int & number) {
    db<CPU>(TRC) << "CPU::fdec(volatile int & number)\n";
    int inc = -1;
    asm("lock xadd %0, %2" : "=a"  (inc) : "a" (inc) , "m" (number));
    db<CPU>(INF) << "Valor do semáforo de " << inc << " para " << number << "\n";
    return inc;
}

__END_API
