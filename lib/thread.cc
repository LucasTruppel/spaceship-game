#include "thread.h"
#include <iostream>

__BEGIN_API

    // Declaração das variáveis estáticas do thread.h
    Thread Thread::_main;
    int Thread::_id_count = 0;
    Thread* Thread::_running = nullptr;
    Thread Thread::_dispatcher;
    Ordered_List<Thread> Thread::_ready;
    Ordered_List<Thread> Thread::_suspended;
    CPU::Context Thread::_main_context;

    void Thread::init(void (*main)(void *)) {
        db<Thread>(INF) << "Thread main:\n";

        // Observação: Utilização de placement new
        new (&_main) Thread(main, (void *)"main");
        new (&_main_context) CPU::Context();

        db<Thread>(INF) << "Thread dispatcher:\n";
        new (&_dispatcher) Thread(dispatcher);

        _running = &_main;
        _main._state = RUNNING;
        
        CPU::switch_context(&_main_context, _main.context());
    }

    Thread::Context* Thread::context() volatile {
        db<Thread>(TRC) << "Thread::Context* Thread::context() chamado\n";

        return _context;
    }

    int Thread::id() {
        db<Thread>(TRC) << "Thread::id() chamado\n";

        return _id;
    }

    int Thread::switch_context(Thread * prev, Thread * next) {
        db<Thread>(TRC) << "Thread::switch_context(Thread * prev, Thread * next) chamado\n";

        if (prev == next) {
            // CPU::switch_context() retorna 0 quando a operação é bem sucedida, senão retorna -1
            return 0;
        }

        return CPU::switch_context(prev->context(), next->context());
    }

    void Thread::thread_exit(int exit_code) {
        db<Thread>(TRC) << "Thread::thread_exit(int exit_code) chamado\n";

        _state = FINISHING;
        _exit_code = exit_code;
        for (unsigned int i = 0; i < _suspended.size(); i++) {
            Thread* thread = _suspended.remove_head()->object();
            if (thread->get_suspended_by() == _id) {
                thread->resume();
            } else {
                _suspended.insert_tail(thread->link());
            }
        }

        if (_waiting_queue_pointer != nullptr) {
            _waiting_queue_pointer->remove(this);
        }

        db<Thread>(INF) << "Thread " << _id << " FINISHING! \n";
        yield();
    }

    Thread::~Thread() {
        db<Thread>(TRC) << "Thread::~Thread() chamado\n";

        if (_context) {
            delete _context;
        }

        db<Thread>(INF) << "Thread " << _id << " destruída! \n";
    }

    void Thread::dispatcher() {
        db<Thread>(TRC) << "Thread::dispatcher() chamado\n";

        // Seleciona a próxima thread a ser executada até esvaziar a lista de prontos
        while (!_ready.empty()) {
            Thread* next = _ready.remove()->object();

            if (_ready.empty() && next == &_main) {
                break;
            }

            _dispatcher._state = READY;
            _running = next;
            next->_state = RUNNING;
            switch_context(&_dispatcher, next);

            if (next->_state == FINISHING) {
                _ready.remove(&next->_link);
            }
        }

        // Finaliza o dispatcher
        db<Thread>(INF) << "Dispatcher finalizado\n";
        _dispatcher._state = FINISHING;
        _main._state = RUNNING;
        switch_context(&_dispatcher, &_main);
    }

    void Thread::yield() {
        db<Thread>(TRC) << "Thread::yield() chamado\n";

        Thread* next = &_dispatcher;
        if (_running->_state != SUSPENDED && _running->_state != WAITING) {
            if (true || _running != &_main) {
                if (_running->_state != FINISHING) {
                    int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
                    _running->_link.rank(now);
                    _running->_state = READY;
                    db<Thread>(INF) << "novo rank da Thread " << _running->_id << ": "<< _running->_link.rank() <<"\n";
                }   
                _ready.insert(&_running->_link);
            } else {
                _running->_state = READY;
            }
        }

        Thread* prev = _running;
        _running = next;
        next->_state = RUNNING;
        switch_context(prev, next);
    }
 
    int Thread::join() {
        db<Thread>(TRC) << "Thread::join() chamado\n";

        if (this == _running) {
            db<Thread>(WRN) << "Thread join nela mesma\n";
            return -1;
        }
        
        if (_state != FINISHING) {
            _running->set_suspended_by(_id);
            _running->suspend();
        }

        return _exit_code;
    }

    void Thread::suspend() {
        db<Thread>(TRC) << "Thread::suspend() chamado\n";

        if (_state == FINISHING or _state == SUSPENDED) {
            return;
        }
        if (_state == READY) {
            _ready.remove(&_link);
        }
        _state = SUSPENDED;
        int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        _link.rank(now);
        _suspended.insert(&_link);
        if (this == _running) {
            yield();
        }
    }

    void Thread::resume() {
        db<Thread>(TRC) << "Thread::resume() chamado\n";

        if (_state == SUSPENDED) {
            _suspended_by = -1;
            _suspended.remove(&_link);
            _state = READY;
            int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            _link.rank(now);
            _ready.insert_head(&_link);
        }
    }

    void Thread::sleep(Ordered_List<Thread> * waiting_queue) {
        db<Thread>(TRC) << "Thread::sleep() chamado\n";
        _waiting_queue_pointer = waiting_queue;
        int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        _link.rank(now);
        waiting_queue->insert(&_link);
        _state = WAITING;
        yield();
    }

    void Thread::wakeup() {
        db<Thread>(TRC) << "Thread::wakeup() chamado\n";
        
        _waiting_queue_pointer = nullptr;
        _state = READY;
        int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        _link.rank(now);
        _ready.insert(&_link);
    }

__END_API
