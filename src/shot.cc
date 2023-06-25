#include "shot.h"

Shot::Shot(float x, float y, sf::Texture &image, int state, int is_enemy) {
    shot_sprite.setTexture(image);
    shot_sprite.setPosition(x, y);
    shot_sprite.scale(0.5, 0.5);

    _state = static_cast<State>(state);
    _is_enemy = static_cast<Info>(is_enemy);
}

void Shot::updatePosition() {
    sf::Vector2f position = shot_sprite.getPosition();

    switch(_state) {
        case UP:
            if (position.y - 14 >= 10) {
                shot_sprite.move(0.0, -14.0);
            } else {
                _state = FINISHING;
                shot_sprite.setPosition(position.x, 10.0);
            }
            break;
        case DOWN:
            if (position.y + 14 <= 535) {
                shot_sprite.move(0.0, +14.0);
            } else {
                _state = FINISHING;
                shot_sprite.setPosition(position.x, 535);
            }
            break;
        case LEFT:
            if (position.x - 14 >= 10) {
                shot_sprite.move(-14.0, 0.0);
            } else {
                _state = FINISHING;
                shot_sprite.setPosition(10.0, position.y);
            }
            break;
        case RIGHT:
            if (position.x + 14 <= 550) {
                shot_sprite.move(+14.0, 0.0);
            } else {
                _state = FINISHING;
                shot_sprite.setPosition(550, position.y);
            }
    }
}