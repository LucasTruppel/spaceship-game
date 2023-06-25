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
    };

    enum Info {         //Para dizer de quem eh o tiro e se ele deve ser deletado ()  
        PLAYER,
        ENEMY,
        FINISHING,
    };

public:
    // Construtor
    Shot(float x, float y, sf::Texture &image, Direction direction, Info is_enemy);

    // Outros membros da classe

    void updatePosition();

private:
    sf::Sprite shot_sprite;
    Direction _direction;
};


#endif
