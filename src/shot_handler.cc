#include "shot_handler.h"

ShotHandler::ShotHandler() {

}

ShotHandler::~ShotHandler() {
    delete clock;
}



void ShotHandler::run(ShotHandler* shotHandler) {
    shotHandler->clock = new sf::Clock();
    while(true) {
        if (GameHandler::quit_game == false and GameHandler::pause_game == false and GameHandler::end_game == false) {
            if (shotHandler->clock->getElapsedTime().asMilliseconds() > 1000/60) {
                shotHandler->moveShots();
                shotHandler->verifyColisionShotShot();
                shotHandler->verifyColisionShotSpaceship();
                shotHandler->clock->restart();
            }
        }
        Thread::yield();
    }
}

void ShotHandler::moveShots() {
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
}

void ShotHandler::verifyColisionShotShot() {
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
}

void ShotHandler::verifyColisionShotSpaceship() {
    for (int i = 0; i < GameHandler::shot_list.size(); i++) {
        Shot* shot = GameHandler::shot_list.front();
        GameHandler::shot_list.pop_front();
        bool shot_deleted = false;
        for (int j = 0; j < 4; j++) {
            EnemySpaceShip* enemyShip = GameHandler::spaceship_list[j];
            if (shot->getSprite().getGlobalBounds().intersects(enemyShip->getSprite().getGlobalBounds())) {
                delete shot;
                shot_deleted = true;
                if (not shot->getIsEnemy()) {
                    enemyShip->receiveDamage();
                }
                break;
            }
        }
        if (not shot_deleted) {
            PlayerSpaceShip* playerShip = GameHandler::player_ship;
            if (shot->getSprite().getGlobalBounds().intersects(playerShip->getSprite().getGlobalBounds())) {
                playerShip->receiveDamage();
                delete shot;
            } else {
                GameHandler::shot_list.push_back(shot);
            }
        }
    }
}
