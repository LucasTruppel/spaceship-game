#include "thread.h"
#include <iostream>

__BEGIN_API

    /* Inicializar as variaveis estáticas do thread.h */
    int Thread::_id_count = 0;
    Thread* Thread::_running = nullptr;
    Thread Thread::_main;
    Thread Thread::_dispatcher;
    CPU::Context Thread::_main_context;
    Ordered_List<Thread> Thread::_ready;

    void Thread::init(void (*main)(void *)) {

        _main = *(new Thread( (void (*)()) main));
        _dispatcher = *(new Thread( (void (*)()) &dispatcher));

        _main_context = *(new CPU::Context());
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
            return 0; //CPU::switch_context returns 0 when sucessfull. Otherwise returns -1
        }

        return CPU::switch_context(prev->context(), next->context());
    }

    void Thread::thread_exit(int exit_code) {
        db<Thread>(TRC) << "Thread::thread_exit(int exit_code) chamado\n";
        _state = FINISHING;
        db<Thread>(INF) << "Thread " << _id << " FINISHING! \n";
    }

    Thread::~Thread() {
        db<Thread>(TRC) << "Thread::~Thread() chamado\n";
        if (_context)
            delete _context;
        db<Thread>(INF) << "Thread " << _id << " destruída! \n";
    }


    void Thread::dispatcher() {
        db<Thread>(TRC) << "Thread::dispatcher() chamado\n";

        while (_ready.size() > 1) {  //Não sabemos se está certo
            // 1
            Thread* next = _ready.remove()->object();

            // 2
            _dispatcher._state = READY;
            _ready.insert_first(&_dispatcher._link);
            
            // 3
            _running = next;

            // 4
            next->_state = RUNNING;
            
            // 5
            switch_context(&_dispatcher, next);

            // 6
            if (next->_state == FINISHING) {
                _ready.remove(&next->_link);
            }
            
        }
        _dispatcher._state = FINISHING;
        _ready.remove(&_dispatcher._link);
        switch_context(&_dispatcher, &_main);

        /*
        enquanto existir thread do usuário:
            1) escolha uma próxima thread a ser executada
            2) atualiza o status da própria thread dispatacher para READY e reinsire a mesma em _ready
            3) atualiza o ponteiro _running para apontar para a próxima thread a ser executada
            4) atualiza o estado da próxima thread a ser executada
            5) troca o contexto entre as duas threads
            6) testa se o estado da próxima thread é FINISHING e caso afirmativo a remova de _ready
        muda o estado da thread dispatcher para FINISHING
        remova a thread dispatcher da fila de prontos
        troque o contexto da thread dispatcher para main
        */

    }

    void Thread::yield() {
        db<Thread>(TRC) << "Thread::yield() chamado\n";

        //1
        Thread* next = _ready.remove()->object();

        //2
        if (_running != &_main) {
            if (_running->_state != FINISHING) {
                int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
                _running->_link.rank(now);
                _running->_state = READY;
            }
            _ready.insert(&_running->_link);
        }

        //3
        Thread* prev = _running;

        //4
        _running = next;

        //5
        next->_state = RUNNING;

        //6
        switch_context(prev, next);

        /*
        1) escolha uma próxima thread a ser executada (dispatcher) --> pega da fila de prontos.
        2) atualiza a prioridade da tarefa que estava sendo executada (aquela que chamou yield) com o timestamp atual, a fim de reinserí-la na fila de prontos atualizada (cuide de casos especiais, como estado ser FINISHING ou Thread main que não devem ter suas prioridades alteradas)
        3) reinsira a thread que estava executando na fila de prontos
        4) atualiza o ponteiro _running
        5) atualiza o estado da próxima thread a ser executada
        6) troque o contexto entre as threads
        */

    }


__END_API
