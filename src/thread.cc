#include "thread.h"
#include <iostream>

__BEGIN_API

    int Thread::_id_count = 0;
    Thread* Thread::_running = nullptr;

    Thread::Context* Thread::context() volatile {
        return _context;
    }

    int Thread::id(){
        return _id;
    }

    int Thread::switch_context(Thread * prev, Thread * next) {
        _running = next;
        return CPU::switch_context(prev->context(), next->context());
    }

    void Thread::thread_exit(int exit_code) {
        delete _context;
    }
    

__END_API
