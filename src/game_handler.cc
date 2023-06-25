#include "game_handler.h"

int GameHandler::score = 0;
int GameHandler::velocity = 1;
int GameHandler::player_life = 3;
bool GameHandler::player_invincible = false;

std::queue<Shot> GameHandler::shot_queue = {};
//std::list<EnemySpaceShip>  GameHandler::spaceship_list = {};
PlayerSpaceShip* GameHandler::player_ship = nullptr;

GameHandler::GameHandler() {

}
    
GameHandler::~GameHandler() {

}