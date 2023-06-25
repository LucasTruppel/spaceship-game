#include "collision_handler.h"


CollisionHandler::CollisionHandler() {

}

CollisionHandler::~CollisionHandler() {

}

bool CollisionHandler::detect_vertical_collision(PlayerSpaceShip* player, EnemySpaceShip* enemy[4]) {



    return player->getSprite().getGlobalBounds().intersects(enemy[0]->getSprite().getGlobalBounds());

}

bool CollisionHandler::detect_horizontal_collision(PlayerSpaceShip* player, EnemySpaceShip* enemy[4]) {

    return player->getSprite().getGlobalBounds().intersects(enemy[0]->getSprite().getGlobalBounds());

}
