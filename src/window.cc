#include "window.h"

Window::Window() {
    initialize();
}

Window::~Window() {
    // Deleting Clock
    delete clock;

    // Deleting Player Spaceship and Player Thread
    delete thread_player_spaceship;
    delete playerSpaceShip;

    // Deleting all 4 Enemy Spaceships and Enemy Threads
    for (int i = 0; i < 4; i++) {
        delete thread_enemy_spaceship;
        delete enemySpaceShip[i];
    }

    // Deleting Keyboard Handler and its Thread
    delete thread_keyboard_handler;
    delete keyboard_handler;

    // Deleting Shot Handler and its Thread
    delete thread_shot_handler;
    delete shot_handler;

}

void Window::draw_texture(unsigned int texture, int length, int height, float angle) {}

void Window::run() {
    sf::RenderWindow window(sf::VideoMode(Constants::WIDTH, Constants::HEIGHT), "Spaceship Game!");
    window.setKeyRepeatEnabled(false);

    // Main Window loop
    while (window.isOpen() and GameHandler::quit_game == false) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    GameHandler::quit_game = true;
                    break;
            }
        }
        if (clock->getElapsedTime().asMilliseconds() > 1000/60) {
            // Drawing Window elements
            window.clear();
            window.draw(maze_sprite);
            window.draw(playerSpaceShip->getSprite());     
            for (int i = 0; i < 4; i++) {
                if (enemySpaceShip[i]->getState() != EnemySpaceShip::State::DEAD) {
                    window.draw(enemySpaceShip[i]->getSprite());
                }
            }
            for (auto const& shot: GameHandler::shot_list) {
                window.draw(shot->getSprite());
            }
            
            // Drawing Game Score in the Window
            window.draw(score_text);
            std::string score =  std::to_string(GameHandler::score);
            while (score.length() < 6) {
                score = "0" + score;
            }
            score_counter_text.setString(score);
            window.draw(score_counter_text);

            // Drawing Player Life in the Window
            window.draw(life_text);
            std::string life = std::to_string(GameHandler::player_life);
            life_counter_text.setString(life);
            window.draw(life_counter_text);

            // Drawing Speed in the Window
            window.draw(speed_text);
            std::string speed = std::to_string(GameHandler::speed);
            speed_counter_text.setString(speed);
            window.draw(speed_counter_text);

            // Finishing main loop
            window.display();
            clock->restart();
            
            
        }
        Thread::yield();
    }

    // Aqui roda quando GameHandler::quit_game == true
    

    // Calling thread_exit() for Player Spaceship Thread
    thread_player_spaceship->thread_exit(100);

    // Calling thread_exit() for all 4 Enemy Spaceship Threads
    for (int i = 0; i < 4; i++) {
        thread_enemy_spaceship[i]->thread_exit(200 + i);
    }

    // Calling thread_exit() for Keyboard Handler Thread
    thread_keyboard_handler->thread_exit(300);
    
    // Calling thread_exit() for Shot Handler Thread
    thread_shot_handler->thread_exit(400);

    // thread_join() (Na main);

    window.close();
}

void Window::initialize() {   

    // Initializing Maze
    maze_tex.loadFromFile("sprites/maze/screen.png");
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(1.5, 1.5);

    // Loading text font
    if (!font.loadFromFile("sprites/ui/pixeltype.ttf")) {
        std::cout << "Failed to read text font" << std::endl;
    }

    // Initializing Score text elements
    score_text.setFont(font);
    score_text.setString("SCORE");
    score_text.setCharacterSize(35);
    score_text.setFillColor(sf::Color::White);
    score_text.setOrigin(score_text.getGlobalBounds().width/2, 0);
    score_text.setPosition(690,75);

    // Initializing Score counter elements
    score_counter_text.setFont(font);
    score_counter_text.setString("000000");
    score_counter_text.setCharacterSize(35);
    score_counter_text.setFillColor(sf::Color::White);
    score_counter_text.setOrigin(score_counter_text.getGlobalBounds().width/2, 0);
    score_counter_text.setPosition(690,100);

    // Initializing Player Life text elements
    life_text.setFont(font);
    life_text.setString("LIFE");
    life_text.setCharacterSize(35);
    life_text.setFillColor(sf::Color::White);
    life_text.setOrigin(life_text.getGlobalBounds().width/2, 0);
    life_text.setPosition(690, 250);
    
    // Initializing Player Life counter elements
    life_counter_text.setFont(font);
    life_counter_text.setString("3");
    life_counter_text.setCharacterSize(35);
    life_counter_text.setFillColor(sf::Color::White);
    life_counter_text.setOrigin(life_counter_text.getGlobalBounds().width/2, 0);
    life_counter_text.setPosition(690,275);

    // Initializing Speed text elements
    speed_text.setFont(font);
    speed_text.setString("SPEED");
    speed_text.setCharacterSize(35);
    speed_text.setFillColor(sf::Color::White);
    speed_text.setOrigin(speed_text.getGlobalBounds().width/2, 0);
    speed_text.setPosition(690, 400);
    
    // Initializing Speed counter elements
    speed_counter_text.setFont(font);
    speed_counter_text.setString("1");
    speed_counter_text.setCharacterSize(35);
    speed_counter_text.setFillColor(sf::Color::White);
    speed_counter_text.setOrigin(speed_counter_text.getGlobalBounds().width/2, 0);
    speed_counter_text.setPosition(690,425);

    // Initializing Clock and rendering Game Window
    clock = new sf::Clock();

    // Initializing Player Spaceship and Player Thread
    playerSpaceShip = new PlayerSpaceShip(Constants::PLAYER_INITIAL_X, Constants::PLAYER_INITIAL_Y);
    thread_player_spaceship = new Thread(PlayerSpaceShip::run, playerSpaceShip);

    // Updating Game Handler atribute
    GameHandler::player_ship = playerSpaceShip;

    // Initializing all 4 Enemy Spaceships and Enemy Threads
    for (int i = 0; i < 4; i++) {
        switch(i) {
            case 0:
                enemySpaceShip[i] = new EnemySpaceShip(Constants::ENEMY_INITIAL_X[0], 
                                                       Constants::ENEMY_INITIAL_Y[0], 
                                                       i);  // Upper Right start position
                break;
            case 1:
                enemySpaceShip[i] = new EnemySpaceShip(Constants::ENEMY_INITIAL_X[1], 
                                                       Constants::ENEMY_INITIAL_Y[1], 
                                                       i); // Upper Left start position
                break;
            case 2:
                enemySpaceShip[i] = new EnemySpaceShip(Constants::ENEMY_INITIAL_X[2], 
                                                       Constants::ENEMY_INITIAL_Y[2], 
                                                       i); // Lower Right start position
                break;
            default:
                enemySpaceShip[i] = new EnemySpaceShip(Constants::ENEMY_INITIAL_X[3], 
                                                       Constants::ENEMY_INITIAL_Y[3], 
                                                       i); // Lower Left start position
        }
        // Pushing spaceship into Game Handler list
        GameHandler::spaceship_list[i] = enemySpaceShip[i];
        
         // The value is 0 for the Random Strategy and 1 for the Dummy/Follow Strategy
        enemySpaceShip[i]->setStrategy(i % 2);
        
        // Initializing Thread
        thread_enemy_spaceship[i] = new Thread(EnemySpaceShip::run, enemySpaceShip[i]);
    }

    // Initializing Keyboard Handler and its Thread
    keyboard_handler = new KeyboardHandler();
    thread_keyboard_handler = new Thread(KeyboardHandler::run, keyboard_handler);

    // Initializing Shot Handler
    shot_handler = new ShotHandler();
    thread_shot_handler = new Thread(ShotHandler::run, shot_handler);

}

