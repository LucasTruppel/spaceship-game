#include "window.h"
#include "spaceship.h"

class Shot {

//Represent the direction of the shots
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };


public:
    // Construtor
    Shot(int x, int y, sf::Texture image, Direction direction);

    ~Shot();
    // Outros membros da classe

    void updatePosition() {
    };

private:
    sf::Sprite shot_sprite;
    Direction _direction;
};

