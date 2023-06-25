#include "shot_handler.h"

ShotHandler::ShotHandler() {

}

ShotHandler::~ShotHandler() {
    delete clock;
}



void ShotHandler::run(ShotHandler* shotHandler) {
    shotHandler->clock = new sf::Clock();
    while(true) {
        if (shotHandler->clock->getElapsedTime().asMilliseconds() > 1000/60) {
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

            // Colisões entre tiros
            for (int i = 0; i < GameHandler::shot_list.size(); i++) {
                Shot* shot1 = GameHandler::shot_list.front();
                GameHandler::shot_list.pop_front();
                bool shot1_deleted = false;
                for (int j = 0; j < GameHandler::shot_list.size() - i; j++) {
                    Shot* shot2 = GameHandler::shot_list.front();
                    GameHandler::shot_list.pop_front();
                    if (shot1->getSprite().getGlobalBounds().intersects(shot2->getSprite().getGlobalBounds())) {
                        delete shot1;
                        delete shot2;
                        shot1_deleted = true;
                        break;
                    } else {
                        GameHandler::shot_list.push_back(shot2);
                    }
                }
                if (not shot1_deleted) {
                    GameHandler::shot_list.push_back(shot1);
                }
            }

            // Colisão entre tiro e nave inimiga
            for (int i = 0; i < GameHandler::shot_list.size(); i++) {
                Shot* shot = GameHandler::shot_list.front();
                GameHandler::shot_list.pop_front();
                bool shot_deleted = false;
                for (int j = 0; j < 4; j++) {
                    sf::Sprite enemySprite = GameHandler::spaceship_list[j]->getSprite();
                    if (shot->getSprite().getGlobalBounds().intersects(enemySprite.getGlobalBounds())) {
                        if (shot->getIsEnemy()) {
                            delete shot;
                            shot_deleted = true;
                            break;
                        } else {
                            // spaceship dies
                        }  
                    }
                }
                if (not shot_deleted) {
                    GameHandler::shot_list.push_back(shot);
                }
            }
            shotHandler->clock->restart();
        }
        Thread::yield();
    }
}