#ifndef cpu_h
#define cpu_h

#include <bits/stdc++.h>
#include <ucontext.h>
#include <iostream>
#include "traits.h"
#include "debug.h"

__BEGIN_API

class CPU
{
    public:

        class Context
        {
        private:
            static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;
        public:
            Context() { _stack = 0; }

            template<typename ... Tn>
            Context(void (* func)(Tn ...), Tn ... an);

            ~Context();

            void save();
            void load();

        private:            
            char *_stack;
        public:
            ucontext_t _context;
        };

    public:

        static int switch_context(Context *from, Context *to);
        static int finc(volatile int & number);
        static int fdec(volatile int & number);

};

template<typename ... Tn>
CPU::Context::Context(void (* func)(Tn ...), Tn ... an)
{
    db<CPU>(TRC) << "CPU::Context::Context(void (* func)(Tn ...), Tn ... an) chamado\n";
    getcontext(&_context);
    _stack = new char[STACK_SIZE];

    if (_stack) {
        db<CPU>(INF) << "Stack alocado com sucesso no construtor de Context\n";
        _context.uc_stack.ss_size = STACK_SIZE;
        _context.uc_stack.ss_sp = _stack;
        _context.uc_stack.ss_flags = 0;
        _context.uc_link = 0;
        makecontext(&_context, (void (*)()) func, sizeof...(an), an...);
    } else {
        db<CPU>(ERR) << "Falha na alocação da stack no construtor de Context!\n";
        exit(-1);
    }
}

__END_API

#endif

