#include "window.h"

Window::Window()
{
    load_and_bind_textures();
}

Window::~Window() {
    delete keyboard_handler;
    delete playerSpaceShip;
    for (int i = 0; i < 4; i++) {
        delete enemySpaceShip[i];
    }
}

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::run()
{
    sf::RenderWindow window(sf::VideoMode(900, 560), "Spaceship Game!");

    // https://www.sfml-dev.org/tutorials/2.5/window-events.php
    // https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php

    window.setKeyRepeatEnabled(false);

    keyboard_handler = new KeyboardHandler();
    playerSpaceShip = new PlayerSpaceShip(0, 0);

    for (int i = 0; i < 4; i++) {
        enemySpaceShip[i] = new EnemySpaceShip(100*i, 365);
    }
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            switch (event.type) {
            case sf::Event::Closed:
                 window.close();
                 break;
            
            // Push only the selected keys into the queue
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)  || 
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)     || 
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::P)      || 
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Q)     || sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                        keyboard_handler->key_queue_sem->p();
                        keyboard_handler->key_queue.push(event.key.code);
                        keyboard_handler->key_queue_sem->v();
                        std::cout << event.key.code << std::endl;
                }
                break;
            }
        }
        

        window.clear();
        window.draw(maze_sprite);
        window.draw(playerSpaceShip->getSprite());     
        for (int i = 0; i < 4; i++) {
            window.draw(enemySpaceShip[i]->getSprite());
        }
        window.display();
    }
}

void Window::load_and_bind_textures() {
    // Bind map textures    
    maze_tex.loadFromFile("sprites/maze/screen.png");
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(1.5, 1.5);

    shot_tex.loadFromFile("sprites/space_ships/shot.png");
    shot_sprite.setTexture(shot_tex);
    shot_sprite.scale(-0.5, -0.5);

    space_ship_tex.loadFromFile("sprites/space_ships/space_ship1.png");
    space_ship_sprite.setTexture(space_ship_tex);
    space_ship_sprite.scale(-0.5, -0.5);

    enemy_ship_tex.loadFromFile("sprites/space_ships/enemy_space_ship1.png");
    enemy_ship_sprite.setTexture(enemy_ship_tex);
    enemy_ship_sprite.scale(-0.5, -0.5);
}
