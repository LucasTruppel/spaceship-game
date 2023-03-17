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

template<typename ... Tn>
CPU::Context::Context(void (* func)(Tn ...), Tn ... an)
{
    // Esse construtor deve alocar memória para a pilha do novo contexto a ser criado
    // Inicializar todos os campos da estrutura ucontext_t (através do atributo _context) 
    // Criar um novo contexto usando makecontext()
    
    _stack = new char[STACK_SIZE];
    _context.uc_stack.ss_size = STACK_SIZE;
    _context.uc_stack.ss_sp = _stack;
    _context.uc_stack.ss_flags = 0;
    _context.uc_link = 0;
    makecontext(&_context, func, sizeof...(Tn), an...);
    //makecontext(&_context, func(an...), size, ...);
    //makecontext(&_context, void (* func) (), int sizeof...an, ...);
}

CPU::Context::~Context()
{
    //adicionar implementação
    delete _context.uc_stack.ss_sp;
}

int CPU::switch_context(Context *from, Context *to)
{
     //implementação do método
     swapcontext(&from->_context, &to->_context);
}

__END_API
