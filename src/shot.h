#ifndef shot_h
#define shot_h

#include <iostream>
#include <SFML/Graphics.hpp>

class Shot {

    //Represent the direction of the shots
public:
    enum State {
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

    sf::Sprite getSprite() {return shot_sprite;}
    State getState() {return _state;}
    Info getIsEnemy() {return _is_enemy;}

private:

    sf::Sprite shot_sprite;
    State _state;
    Info _is_enemy;
};


#endif
