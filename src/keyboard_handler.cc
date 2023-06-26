#include "keyboard_handler.h"

KeyboardHandler::~KeyboardHandler() {
    delete clock;
    
}

void KeyboardHandler::run(KeyboardHandler* keyboard_handler) {
    keyboard_handler->clock = new sf::Clock();
    while(true) {

        int delta_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds() - keyboard_handler->last_movement;
        int delta_shot = keyboard_handler->clock->getElapsedTime().asMilliseconds() - keyboard_handler->last_shot;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && delta_movement > 300) {
            if (GameHandler::pause_game) {
                GameHandler::pause_game = false;
            } else {
                GameHandler::pause_game = true;
            }
            keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && delta_movement > 300) {
            GameHandler::quit_game = true;
            keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
        } else if (GameHandler::quit_game == false and GameHandler::pause_game == false) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                if (GameHandler::end_game) {      //Só pode resetar se o jogo tiver acabado
                    GameHandler::reset_game = true;
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && delta_movement > 300) {
                GameHandler::player_ship->makeMoveUP();
                keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && delta_movement > 300) {
                GameHandler::player_ship->makeMoveDOWN();
                keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && delta_movement > 300) {
                GameHandler::player_ship->makeMoveLEFT();
                keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && delta_movement > 300) {
                GameHandler::player_ship->makeMoveRIGHT();
                keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && delta_shot > 750) {
                GameHandler::player_ship->shoot(); 
                keyboard_handler->last_shot = keyboard_handler->clock->getElapsedTime().asMilliseconds();
            }
        }
        Thread::yield();
    }  
}
