#include "shot_handler.h"

ShotHandler::ShotHandler() {

}

ShotHandler::~ShotHandler() {

}



void ShotHandler::run(ShotHandler* shotHandler) {
    shotHandler->clock = new sf::Clock();
    while(true) {
        if (shotHandler->clock->getElapsedTime().asMilliseconds() > 300) {
            // for (int i = 0; i < GameHandler::shot_list.size(); i++) {
            //     Shot* shot = GameHandler::shot_list.front();
            //     GameHandler::shot_list.pop_front();
            //     shot->updatePosition();
            //     GameHandler::shot_list.push_back(shot);
            // }

            for (auto const& shot: GameHandler::shot_list) {
                shot->updatePosition();
                if (shot->getState() == Shot::State::FINISHING) {
                    //GameHandler::shot_list.remove(shot);
                    //delete shot;
                }
            }
            shotHandler->clock->restart();

            //Shot Collision
        }
        Thread::yield();
        

    }

    //pensar num algoritmo para ver as colisoes.
    //Lembrando que o shot tem o _direction que pode ser setado para FINISHING.

}