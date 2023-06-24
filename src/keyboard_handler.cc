#include "keyboard_handler.h"

KeyboardHandler::KeyboardHandler() {
    key_queue_sem = new Semaphore();
}

KeyboardHandler::~KeyboardHandler() {
    if (key_queue_sem) {
        delete key_queue_sem;
    }
}

void KeyboardHandler::run() {

    // Removing the first key from the queue
    //new (&key_queue_sem) Semaphore();

    // while(game_running)
    while(true) {
        key_queue_sem->p();
        int key = key_queue.front();
        key_queue.pop();
        key_queue_sem->v();

        // Calls the appropriate method based on the received key
        if (key == sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            std::cout << "Tecla de Pause na fila: " << key;
        } else if (key == sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            std::cout << "Tecla de Quit na fila: " << key;
        } else if (key == sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            std::cout << "Tecla de Restart na fila: " << key;
        } else {
            std::cout << "Tecla de Comando na fila: " << key;
        }
    }
}
