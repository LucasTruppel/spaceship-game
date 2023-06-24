#include "collision_handler.h"


CollisionHandler::CollisionHandler() {

}

CollisionHandler::~CollisionHandler() {

}

bool CollisionHandler::detect_player_collision(PlayerSpaceShip* player, EnemySpaceShip* enemy) {

    return player->getSprite().getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds());

}

bool CollisionHandler::detect_enemy_collision(EnemySpaceShip* enemy01, EnemySpaceShip* enemy02) {

    return enemy01->getSprite().getGlobalBounds().intersects(enemy02->getSprite().getGlobalBounds());

}
