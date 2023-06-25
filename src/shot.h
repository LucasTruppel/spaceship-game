#ifndef shot_h
#define shot_h

#include <SFML/Graphics.hpp>

class Shot {

    //Represent the direction of the shots
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        FINISHING,
    };

    enum Info {  
        PLAYER,
        ENEMY,    
    };

public:

    Shot(float x, float y, sf::Texture & image, int direction, int is_enemy); 
    void updatePosition();

private:

    sf::Sprite shot_sprite;
    Direction _direction;
    Info _is_enemy;
};


#endif
