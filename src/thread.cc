#include "thread.h"
#include <iostream>

__BEGIN_API

    int Thread::_id_count = 0;
    Thread* Thread::_running = nullptr;

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
        _running = next;
        return CPU::switch_context(prev->context(), next->context());
    }

    void Thread::thread_exit(int exit_code) {
        db<Thread>(TRC) << "Thread::thread_exit(int exit_code) chamado\n";
        if (_context)
            delete _context;
        db<Thread>(INF) << "Thread " << _id << " destruída! \n";
    }
    

__END_API