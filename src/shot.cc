#include "shot.h"

Shot::Shot(float x, float y, sf::Texture &image, int direction, int is_enemy) {
    shot_sprite.setTexture(image);
    shot_sprite.setPosition(x, y);
    shot_sprite.scale(0.5, 0.5);

    _direction = static_cast<Direction>(direction);
    _is_enemy = static_cast<Info>(is_enemy);
}

void Shot::updatePosition() {
    sf::Vector2f position = shot_sprite.getPosition();

   if (_direction == UP) {
        if (position.y - 50 >= 10) {
            shot_sprite.move(0.0, -50.0);
        } else {
            _direction = FINISHING;
            shot_sprite.setPosition(position.x, 10.0);
        }
   } else if (_direction == DOWN) {
        if (position.y + 50 <= 500) {
            shot_sprite.move(0.0, +50.0);
        } else {
            shot_sprite.setPosition(position.x, 500);
        }
   } else if (_direction == LEFT) {
        if (position.x - 50 >= 10) {
            shot_sprite.move(-50.0, 0.0);
        } else {
            shot_sprite.setPosition(10.0, position.y);
        }
   } else if (_direction == RIGHT) {
        if (position.x + 50 <= 515) {
            shot_sprite.move(+50.0, 0.0);
        } else {
            shot_sprite.setPosition(515, position.y);
        }
   } 


}