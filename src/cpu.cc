#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    //adicionar implementação
    getcontext(&_context);
}

void CPU::Context::load()
{
    //adicionar implementação
    setcontext(&_context);
}

CPU::Context::~Context()
{
    //adicionar implementação
    delete _stack;
}

int CPU::switch_context(Context *from, Context *to)
{
     //implementação do método
     return swapcontext(&from->_context, &to->_context); 
}

__END_API
