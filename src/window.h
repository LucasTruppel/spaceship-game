#ifndef window_h
#define window_h

#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>
#include "game_handler.h"
#include "player_spaceship.h"
#include "enemy_spaceship.h"
#include "keyboard_handler.h"
#include "thread.h"
#include "traits.h"
#include "shot_handler.h"

__USING_API

class Window
{
public:
    Window();

    ~Window();

    void run();

    void draw_texture(unsigned int texture, int length, int height, float angle);

private:
    void initialize();



private:

    // Maze texture
    sf::Texture maze_tex;
    sf::Sprite maze_sprite;
    
    // Shot texture
    sf::Texture shot_tex;
    sf::Sprite shot_sprite;
    
    // SpaceShip texture
    sf::Texture space_ship_tex;
    sf::Sprite space_ship_sprite;

    // Enemy SpaceShip texture
    sf::Texture enemy_ship_tex;
    sf::Sprite enemy_ship_sprite;

    // Keyboard Handler and its Thread
    KeyboardHandler* keyboard_handler;
    Thread* thread_keyboard_handler;

    // Shot Handler and its Thread
    ShotHandler* shot_handler;
    Thread* thread_shot_handler;

    // Player Spaceship and Thread
    PlayerSpaceShip* playerSpaceShip;
    Thread* thread_player_spaceship;

    // Enemy SpaceShips and Threads
    EnemySpaceShip* enemySpaceShip[4];
    Thread* thread_enemy_spaceship[4];

    // Clock
    sf::Clock* clock;
};



#endif