#include "game_handler.h"

int GameHandler::score = 0;
int GameHandler::speed = 1;
int GameHandler::player_life = 3;
bool GameHandler::player_invincible = false;
bool GameHandler::quit_game = false;
bool GameHandler::pause_game = false;
bool GameHandler::reset_game = false;


std::list<Shot*> GameHandler::shot_list = {};
EnemySpaceShip*  GameHandler::spaceship_list[4] = {nullptr, nullptr, nullptr, nullptr};
PlayerSpaceShip* GameHandler::player_ship = nullptr;

GameHandler::GameHandler() {

}
    
GameHandler::~GameHandler() {
    for (int i = 0; i < GameHandler::shot_list.size(); i++) {
        Shot* shot = GameHandler::shot_list.front();
        GameHandler::shot_list.pop_front();
        delete shot;
    }
}