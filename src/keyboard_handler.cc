#include "keyboard_handler.h"

KeyboardHandler::KeyboardHandler(PlayerSpaceShip* playerShip) {
    playerSpaceShip = playerShip;
}

KeyboardHandler::~KeyboardHandler() {
    delete clock;
    
}

void KeyboardHandler::run(KeyboardHandler* keyboard_handler) {
    keyboard_handler->clock = new sf::Clock();
    while(true) {
        int delta_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds() - keyboard_handler->last_movement;
        int delta_shot = keyboard_handler->clock->getElapsedTime().asMilliseconds() - keyboard_handler->last_shot;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            std::cout << "Tecla de Pause" << std::endl;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            std::cout << "Tecla de Quit" << std::endl;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            std::cout << "Tecla de Restart" << std::endl;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && delta_movement > 300) {
            keyboard_handler->playerSpaceShip->makeMoveUP();
            keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && delta_movement > 300) {
            keyboard_handler->playerSpaceShip->makeMoveDOWN();
            keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && delta_movement > 300) {
            keyboard_handler->playerSpaceShip->makeMoveLEFT();
            keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && delta_movement > 300) {
            keyboard_handler->playerSpaceShip->makeMoveRIGHT();
            keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && delta_shot > 750) {
            keyboard_handler->playerSpaceShip->shoot(); 
            keyboard_handler->last_shot = keyboard_handler->clock->getElapsedTime().asMilliseconds();
        }
        Thread::yield();
    }  
}

