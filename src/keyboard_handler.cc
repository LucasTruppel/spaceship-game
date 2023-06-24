#include "keyboard_handler.h"

KeyboardHandler::KeyboardHandler(PlayerSpaceShip* playerShip) {
    key_queue_sem = new Semaphore();
    playerSpaceShip = playerShip;
}

KeyboardHandler::~KeyboardHandler() {
    if (key_queue_sem) {
        delete key_queue_sem;
    }
}

void KeyboardHandler::run(KeyboardHandler* keyboard_handler) {

    while(true) {
        if (not keyboard_handler->key_queue.empty()) {
            //keyboard_handler->key_queue_sem->p();
            int key = keyboard_handler->key_queue.front();
            keyboard_handler->key_queue.pop();
            //keyboard_handler->key_queue_sem->v();
        
            if (key == sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                std::cout << "Tecla de Pause na fila: " << key << std::endl;
            } else if (key == sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                std::cout << "Tecla de Quit na fila: " << key << std::endl;
            } else if (key == sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                std::cout << "Tecla de Restart na fila: " << key << std::endl;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keyboard_handler->playerSpaceShip->makeMoveUP();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keyboard_handler->playerSpaceShip->makeMoveDOWN();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keyboard_handler->playerSpaceShip->makeMoveLEFT();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keyboard_handler->playerSpaceShip->makeMoveRIGHT();
            } else {
                keyboard_handler->playerSpaceShip->shoot();
            }
        }
        Thread::yield();
    }
}

