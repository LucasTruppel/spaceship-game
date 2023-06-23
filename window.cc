#include "window.h"

int cont = 0;

Window::Window()
{
    load_and_bind_textures();
}

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::run()
{
    sf::RenderWindow window(sf::VideoMode(900, 560), "SFML works!");

    //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
    window.setKeyRepeatEnabled(false);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            switch (event.type) {
            case sf::Event::Closed:
                 window.close();
                 break;
            
            // key pressed
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    std::cout << "Keyboard esquerda!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    std::cout << "Keyboard direita!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    std::cout << "Keyboard para baixo!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    std::cout << "Keyboard para cima!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    std::cout << "Espaço apertado!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    std::cout << "Você apertou o P!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    std::cout << "Você apertou o Q!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                    std::cout << "Você apertou o R!" << std::endl;
                } else
                    std::cout << "Keyboard pressed = " << event.key.code << std::endl;
                break;
            
            }
        }

        window.clear();
        window.draw(maze_sprite);
        
        space_ship_sprite.setPosition(220, 365);
        window.draw(space_ship_sprite);
        
        enemy_ship_sprite.setPosition(245, 150);
        window.draw(enemy_ship_sprite);

        shot_sprite.setPosition(204, 400);
        window.draw(shot_sprite);
        
        window.display();
    }
}

void Window::load_and_bind_textures()
{
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
