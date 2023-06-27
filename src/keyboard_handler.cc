#include "keyboard_handler.h"

KeyboardHandler::~KeyboardHandler() {
    if (clock)
        delete clock;
    
}

void KeyboardHandler::run(KeyboardHandler* keyboard_handler) {
    keyboard_handler->clock = new sf::Clock();
    while(not GameHandler::quit_game) {

        int delta_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds() - keyboard_handler->last_movement;
        int delta_shot = keyboard_handler->clock->getElapsedTime().asMilliseconds() - keyboard_handler->last_shot;

        if (GameHandler::end_game) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && delta_movement > movement_min_delta) {
                if (GameHandler::end_game) { // So pode resetar se o jogo tiver acabado
            
                    GameHandler::reset();
                    for (int i = 0; i < 4; i++) {
                        GameHandler::spaceship_list[i]->revive();
                    }
                    keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
                }

                
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && delta_movement > movement_min_delta) {
                GameHandler::quit_game_sem->p();
                GameHandler::quit_game = true;
                GameHandler::quit_game_sem->v();
                keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
            }

        } else {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && delta_movement > movement_min_delta) {
                GameHandler::pause_game_sem->p();
                if (GameHandler::pause_game) {
    
                    GameHandler::pause_game = false;
                } else {
                    GameHandler::pause_game = true;
                }
                GameHandler::pause_game_sem->v();
                keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && delta_movement > movement_min_delta) {
                GameHandler::quit_game_sem->p();
                GameHandler::quit_game = true;
                GameHandler::quit_game_sem->v();
                
                //Movimentos fora do pause e do fim de jogo
            } else if (GameHandler::quit_game == false and GameHandler::pause_game == false) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && delta_movement > movement_min_delta) {
                    GameHandler::player_ship->makeMoveUP();
                    keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && delta_movement > movement_min_delta) {
                    GameHandler::player_ship->makeMoveDOWN();
                    keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && delta_movement > movement_min_delta) {
                    GameHandler::player_ship->makeMoveLEFT();
                    keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && delta_movement > movement_min_delta) {
                    GameHandler::player_ship->makeMoveRIGHT();
                    keyboard_handler->last_movement = keyboard_handler->clock->getElapsedTime().asMilliseconds();
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && delta_shot > shot_min_delta) {
                    GameHandler::player_ship->shoot(); 
                    keyboard_handler->last_shot = keyboard_handler->clock->getElapsedTime().asMilliseconds();
                }
            }
        }
        Thread::yield();
    }
    Thread* thread = GameHandler::keyboard_handler_thread;
    GameHandler::keyboard_handler_thread = nullptr;
    thread->thread_exit(6);

}
