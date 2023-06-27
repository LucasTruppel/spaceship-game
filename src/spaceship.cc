#include "spaceship.h"


void SpaceShip::turnUp(){
    _state = UP;
    spaceship_sprite.setTexture(spaceship_up);
}

void SpaceShip::turnDown(){
    _state = DOWN;
    spaceship_sprite.setTexture(spaceship_down);
}

void SpaceShip::turnLeft(){
    _state = LEFT;
    spaceship_sprite.setTexture(spaceship_left);
}

void SpaceShip::turnRight(){
    _state = RIGHT;
    spaceship_sprite.setTexture(spaceship_right);
}

void SpaceShip::shoot() {
    sf::Vector2f position = spaceship_sprite.getPosition();

    switch(_state) {
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
    
    Shot * shot = new Shot(position.x, position.y, shot_tex, _state, _is_enemy);
    GameHandler::shot_list_sem->p();
    GameHandler::shot_list.push_front(shot);
    GameHandler::shot_list_sem->v();
}