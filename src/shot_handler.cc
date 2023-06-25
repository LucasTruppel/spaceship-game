#include "shot_handler.h"

ShotHandler::ShotHandler() {

}

ShotHandler::~ShotHandler() {

}



void ShotHandler::run(ShotHandler* shotHandler) {
    shotHandler->clock = new sf::Clock();
    while(true) {
        if (shotHandler->clock->getElapsedTime().asMilliseconds() > 300) {
            for (int i = 0; i < GameHandler::shot_list.size(); i++) {
                Shot* shot = GameHandler::shot_list.front();
                GameHandler::shot_list.pop_front();
                shot->updatePosition();
                if (shot->getState() == Shot::State::FINISHING) {
                    delete shot;
                } else {
                    GameHandler::shot_list.push_back(shot);
                }
            }
            shotHandler->clock->restart();
        }
        Thread::yield();
    }

    // Pensar num algoritmo para ver as colisoes. 
}