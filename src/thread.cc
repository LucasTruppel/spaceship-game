#include "thread.h"
#include <iostream>

__BEGIN_API

    int Thread::_id_count = 0;
    Thread* Thread::_running = nullptr;

    static void Thread::init(void (*main)(void *)) {
        
        _main = new Thread(main);
        _dispatcher = new Thread(&Thread::dispatcher);
        /*
        1) Criar thread main
        2) Cria thread dispatcher
        3) Troca o contexto para a Thread main
        */
    }

    Thread::Context* Thread::context() volatile {
        db<Thread>(TRC) << "Thread::Context* Thread::context() chamado\n";
        return _context;
    }

    int Thread::id(){
        db<Thread>(TRC) << "Thread::id() chamado\n";
        return _id;
    }

    int Thread::switch_context(Thread * prev, Thread * next) {
        db<Thread>(TRC) << "Thread::switch_context(Thread * prev, Thread * next) chamado\n";
        if (prev == next) {
            return 0; //CPU::switch_context returns 0 when sucessfull. Otherwise returns -1
        }
        _running = next;
        return CPU::switch_context(prev->context(), next->context());
    }

    void Thread::thread_exit(int exit_code) {
        db<Thread>(TRC) << "Thread::thread_exit(int exit_code) chamado\n";
        if (_context)
            delete _context;
        db<Thread>(INF) << "Thread " << _id << " destruída! \n";
    }

    void Thread::dispatcher() {
        db<Thread>(TRC) << "Thread::dispatcher() chamado\n";
    }

    void Thread::yield() {
        db<Thread>(TRC) << "Thread::yield() chamado\n";
    }


__END_API
