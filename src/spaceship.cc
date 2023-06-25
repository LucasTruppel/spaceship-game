#include "spaceship.h"


void SpaceShip::turnUp(){
    _state = UP;
    spaceship_tex = spaceship_up;
    spaceship_sprite.setTexture(spaceship_tex);
}

void SpaceShip::turnDown(){
    _state = DOWN;
    spaceship_tex = spaceship_down;
    spaceship_sprite.setTexture(spaceship_tex);
}

void SpaceShip::turnLeft(){
    _state = LEFT;
    spaceship_tex = spaceship_left;
    spaceship_sprite.setTexture(spaceship_tex);
}

void SpaceShip::turnRight(){
    _state = RIGHT;
    spaceship_tex = spaceship_right;
    spaceship_sprite.setTexture(spaceship_tex);
}

void SpaceShip::shoot() {
    sf::Vector2f position = spaceship_sprite.getPosition();

    switch(_state) {
        //precisa ver se não é criado dentro do mapa
        case UP:
            position.y = position.y - 14;
            position.x = position.x + 18;
            break;
        case DOWN:
            position.y = position.y + 50;
            position.x = position.x + 18;
            break;
        case LEFT:
            position.x = position.x - 14;
            position.y = position.y + 18;
            break;
        case RIGHT:
            position.x = position.x + 50;
            position.y = position.y + 18;
            break;
    }

    //calcular posicao do tiro. (ver direcao do tiro)
    //ver se nao esta fora do mapa
    
    Shot * shot = new Shot(position.x, position.y, shot_tex, _state, _is_enemy);
    GameHandler::shot_list.push_front(shot);
}