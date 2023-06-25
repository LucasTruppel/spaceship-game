#include "window.h"

Window::Window() {
    initialize();
}

Window::~Window() {
    // Deleting Clock
    delete clock;

    // Deleting Player Spaceship and Player Thread
    thread_player_spaceship->thread_exit(100);
    delete thread_player_spaceship;
    delete playerSpaceShip;

    // Deleting all 4 Enemy Spaceships and Enemy Threads
    for (int i = 0; i < 4; i++) {
        thread_enemy_spaceship[i]->thread_exit(200 + i);
        delete thread_enemy_spaceship;
        delete enemySpaceShip[i];
    }

    // Deleting Keyboard Handler and its Thread
    thread_keyboard_handler->thread_exit(300);
    delete thread_keyboard_handler;
    delete keyboard_handler;

    // Deleting Shot Handler and its Thread
    thread_shot_handler->thread_exit(400);
    delete thread_shot_handler;
    delete shot_handler;
}

void Window::draw_texture(unsigned int texture, int length, int height, float angle) {}

void Window::run() {
    sf::RenderWindow window(sf::VideoMode(815, 560), "Spaceship Game!");
    window.setKeyRepeatEnabled(false);

    // Main Window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                 window.close();
                 break;
            }
        }
        if (clock->getElapsedTime().asMilliseconds() > 1000/60) {
            // Drawing Window elements
            window.clear();
            window.draw(maze_sprite);
            window.draw(playerSpaceShip->getSprite());     
            for (int i = 0; i < 4; i++) {
                window.draw(enemySpaceShip[i]->getSprite());
            }
            for (auto const& shot: GameHandler::shot_list) {
                window.draw(shot->getSprite());
            }
            window.display();
            clock->restart();
        }
        Thread::yield();
    }
}

void Window::initialize() {   

    // Initializing Maze
    maze_tex.loadFromFile("sprites/maze/screen.png");
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(1.5, 1.5);

    // Initializing Clock and rendering Game Window
    clock = new sf::Clock();

    // Initializing Player Spaceship and Player Thread
    playerSpaceShip = new PlayerSpaceShip(250, 250);
    thread_player_spaceship = new Thread(PlayerSpaceShip::run, playerSpaceShip);

    // Ipdating Game Hnadler atribute
    GameHandler::player_ship = playerSpaceShip;

    // Initializing all 4 Enemy Spaceships and Enemy Threads
    for (int i = 0; i < 4; i++) {
        switch(i) {
            case 0:
                enemySpaceShip[i] = new EnemySpaceShip(100, 100, i);  // Upper Right start position
                break;
            case 1:
                enemySpaceShip[i] = new EnemySpaceShip(100, 400, i); // Upper Left start position
                break;
            case 2:
                enemySpaceShip[i] = new EnemySpaceShip(400, 100, i); // Lower Right start position
                break;
            default:
                enemySpaceShip[i] = new EnemySpaceShip(400, 400, i);// Lower Left start position
        }
        // Pushing spaceship into Game Handler list
        GameHandler::spaceship_list[i] = enemySpaceShip[i];
        
         // The value is 0 for the Random Strategy and 1 for the Dummy/Follow Strategy
        enemySpaceShip[i]->setStrategy(i % 2);
        
        // Initializing Thread
        thread_enemy_spaceship[i] = new Thread(EnemySpaceShip::run, enemySpaceShip[i]);
    }

    // Initializing Keyboard Handler and its Thread
    keyboard_handler = new KeyboardHandler(playerSpaceShip);
    thread_keyboard_handler = new Thread(KeyboardHandler::run, keyboard_handler);

    // Initializing Shot Handler
    shot_handler = new ShotHandler();
    thread_shot_handler = new Thread(ShotHandler::run, shot_handler);

}

