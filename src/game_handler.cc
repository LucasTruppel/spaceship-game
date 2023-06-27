#include "game_handler.h"

int GameHandler::score = 0;
int GameHandler::speed = 1;
int GameHandler::player_life = 3;
bool GameHandler::player_invincible = false;
bool GameHandler::quit_game = false;
bool GameHandler::pause_game = false;
bool GameHandler::end_game = false;

std::list<Shot*> GameHandler::shot_list = {};
EnemySpaceShip*  GameHandler::spaceship_list[4] = {nullptr, nullptr, nullptr, nullptr};
PlayerSpaceShip* GameHandler::player_ship = nullptr;

Thread* GameHandler::player_thread = nullptr;
Thread* GameHandler::enemy_thread[4] {nullptr, nullptr, nullptr, nullptr};
Thread* GameHandler::shot_handler_thread = nullptr;
Thread* GameHandler::keyboard_handler_thread = nullptr;

Semaphore* GameHandler::shot_list_sem = new Semaphore();
Semaphore* GameHandler::quit_game_sem = new Semaphore();
Semaphore* GameHandler::pause_game_sem = new Semaphore();
Semaphore* GameHandler::end_game_sem = new Semaphore();
Semaphore* GameHandler::score_sem = new Semaphore();
Semaphore* GameHandler::player_sem = new Semaphore();
Semaphore* GameHandler::enemy_sem[4] = {new Semaphore(), new Semaphore(), new Semaphore(), new Semaphore()};

GameHandler::~GameHandler() {
    for (int i = 0; i < GameHandler::shot_list.size(); i++) {
        Shot* shot = GameHandler::shot_list.front();
        GameHandler::shot_list.pop_front();
        if (shot)
            delete shot;
    }
    if (GameHandler::shot_list_sem)
        delete shot_list_sem;
    if (GameHandler::quit_game_sem)
        delete quit_game_sem;
    if (GameHandler::pause_game_sem)
        delete pause_game_sem;
    if (GameHandler::end_game_sem)
        delete end_game_sem;
    if (GameHandler::score_sem)
        delete score_sem;
    if (GameHandler::player_sem)
        delete player_sem; 
    for (int i = 0; i < 4; i++) {
        if (enemy_sem[i])
            delete enemy_sem[i];
    }
}

void GameHandler::reset() {

    for (int i = 0; i < GameHandler::shot_list.size(); i++) {
        Shot* shot = GameHandler::shot_list.front();
        GameHandler::shot_list.pop_front();
        delete shot;
    }

    GameHandler::score_sem->p();
    GameHandler::score = 0;
    GameHandler::score_sem->v();

    GameHandler::speed = 1;
    GameHandler::player_life = 3;
    GameHandler::player_invincible = false;

    GameHandler::quit_game_sem->p();
    GameHandler::quit_game = false;
    GameHandler::quit_game_sem->v();

    GameHandler::pause_game_sem->p();
    GameHandler::pause_game = false;
    GameHandler::pause_game_sem->v();

    GameHandler::end_game_sem->p();
    GameHandler::end_game = false;
    GameHandler::end_game_sem->v();
}