#include "thread.h"
#include <iostream>

__BEGIN_API

    // Declara as variáveis estáticas do thread.h
    Thread Thread::_main;
    Thread* Thread::_running = nullptr;
    Thread Thread::_dispatcher;
    Ordered_List<Thread> Thread::_ready;
    CPU::Context Thread::_main_context;

    int Thread::_id_count = 0;
    Ordered_List<Thread> Thread::_sleeping;

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

    int Thread::id(){
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

        _exit_code = exit_code;
        _state = FINISHING;

        for (unsigned int i = 0; i < _sleeping.size(); i++) {
            Thread* next = _sleeping.remove()->object();
            next->resume();
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
            _dispatcher._state = READY;
            _running = next;
            next->_state = RUNNING;
            switch_context(&_dispatcher, next);

            if (next->_state == FINISHING) {
                _ready.remove(&next->_link);
            }
        }

        // Finaliza o dispatcher
        _dispatcher._state = FINISHING;
        _ready.remove(&_dispatcher._link);
        switch_context(&_dispatcher, &_main);
    }

    void Thread::yield() {
        db<Thread>(TRC) << "Thread::yield() chamado\n";

        Thread* next = &_dispatcher;
        if (_running != &_main) {
            if (_running->_state != FINISHING) {
                int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
                _running->_link.rank(now);
                _running->_state = READY;
            }
            _ready.insert(&_running->_link);
        } else {
            _running->_state = READY;
        }

        Thread* prev = _running;
        _running = next;
        next->_state = RUNNING;
        switch_context(prev, next);
    }

    int Thread::join() {
        db<Thread>(TRC) << "Thread::join() chamado\n";

        if (_state != FINISHING && this != _running) {
            _running->suspend();
        } else {
            db<Thread>(ERR) << "Erro em Thread::join()\n";
            return -1;
        }

        return _exit_code;
    }

    void Thread::suspend() {
        db<Thread>(TRC) << "Thread::suspend() chamado\n";

        if (this != &_main && this != &_dispatcher) {
            _ready.remove(this);
        }

        _state = SLEEPING;
        _sleeping.insert(&(this->_link));
        yield();
    }

    void Thread::resume() {
        db<Thread>(TRC) << "Thread::resume() chamado\n";

        if (_state == SLEEPING) {
            _state = READY;
            if (this != &_main && this != &_dispatcher) {
                _ready.insert(&_link);
            }
        }
    }

__END_API
