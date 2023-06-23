#ifndef window_h
#define window_h

#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>

class Window
{
public:
    Window();

    void run();

    void draw_texture(unsigned int texture, int length, int height, float angle);

private:
    void load_and_bind_textures();


private:

    // Maze Texture
    sf::Texture maze_tex;
    sf::Sprite maze_sprite;
    
    //Shot texture
    sf::Texture shot_tex;
    sf::Sprite shot_sprite;
    
    //Space ship texture
    sf::Texture space_ship_tex;
    sf::Sprite space_ship_sprite;

    //Enemy space ship texture
    sf::Texture enemy_ship_tex;
    sf::Sprite enemy_ship_sprite;
};

#endif