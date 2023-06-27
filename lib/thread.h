#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include "list.h"
#include <ctime>
#include <chrono>

__BEGIN_API

class Thread {

protected:

    typedef CPU::Context Context;

public:

    typedef Ordered_List<Thread> Ready_Queue;

    // Thread State
    enum State {
        RUNNING,
        READY,
        FINISHING,
        SUSPENDED,
        WAITING
    };

    /*
     * Construtor vazio. Necessário para inicialização, mas sem importância para a execução das Threads.
     */ 
    Thread() { }

    /*
     * Cria uma Thread passando um ponteiro para a função a ser executada e os parâmetros passados para a função, que podem variar.
     * Cria o contexto da Thread.
     * PS: devido ao template, este método deve ser implementado neste mesmo arquivo .h
     */ 
    template<typename ... Tn>
    Thread(void (* entry)(Tn ...), Tn ... an);

    /*
     * Retorna a Thread que está em execução.
     */ 
    static Thread * running() { return _running; }

    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev) e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno é negativo se houve erro, ou zero.
     */ 
    static int switch_context(Thread * prev, Thread * next);

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa.
     * Quando a thread encerra, o controle deve retornar à main. 
     */  
    void thread_exit (int exit_code);

    /*
     * Retorna o ID da thread.
     */ 
    int id();

    /*
     * Daspachante (disptacher) de threads. 
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
    static void dispatcher(); 

    /*
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */ 
    static void init(void (*main)(void *));

    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta para ser executada.
     */
    static void yield();

    /*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */ 
    ~Thread();

    /*
     * Retorna o contexto da Thread.
     */ 
    Context* context() volatile;

    /*
     * Suspende a Thread em execução até que a Thread “alvo” finalize.
     */  
    int join();

    /*
     * Suspende a Thread até que resume() seja chamado.
     */  
    void suspend();

    /*
     * Coloca uma Thread que estava suspensa de volta para a fila de prontos.
     */  
    void resume();

    /*
     * Põe uma Thread em espera até que wakeup() seja chamado.
     */  
    void sleep(Ordered_List<Thread> * waiting_queue);

    /*
     * Retira uma Thread da fila de espera.
     */  
    void wakeup();

    /*
     * Retorna o link da Thread.
     */  
    Ready_Queue::Element* link() {  return &_link; }

    void set_suspended_by(int id) {_suspended_by = id;}
    int get_suspended_by() {return _suspended_by;}


private:

    int _id;
    int _exit_code = -1;
    volatile State _state;
    Ready_Queue::Element _link;
    Context * volatile _context;
    int _suspended_by = -1;
    Ordered_List<Thread> * _waiting_queue_pointer = nullptr;
    
    static Thread _main;
    static int _id_count;
    static Thread * _running;
    static Thread _dispatcher;
    static Ready_Queue _ready;
    static Ready_Queue _suspended;
    static CPU::Context _main_context;

};

template<typename ... Tn>
inline Thread::Thread(void (* entry)(Tn ...), Tn ... an) : _link(this, (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count())) {
    db<Thread>(TRC) << "Thread::Thread(void (* entry)(Tn ...), Tn ... an) chamado\n";
    _context = new Context(entry, an...);
    _id = _id_count;
    _id_count++;
    _state = READY;
    if (_id > 1) {
        db<Thread>(INF) << "Thread " << _id <<  " inserida na fila\n";
        db<Thread>(INF) << "rank da Thread " << _id << ": "<< _link.rank() <<"\n";
        _ready.insert(&_link);
    } 
    db<Thread>(INF) << "Thread " << _id << " criada \n";
}

__END_API

#endif
